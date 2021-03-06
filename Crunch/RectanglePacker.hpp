#ifndef CRUNCH_RECTANGLEPACKER_HPP
#define CRUNCH_RECTANGLEPACKER_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/Rectangle.hpp>
#include <Crunch/UtilityFunc.hpp>
#include <Stick/DynamicArray.hpp>
#include <Stick/Result.hpp>

namespace crunch
{
    //@TODO: REMOVE; THIS DOES NOT WORK!!!!!!1111
    /**
     * @brief A class that tightly packs rectangles in a bigger rectangular area.
     *
     * This is useful to for example generate texture atlases.
     *
     * @arg T The value type of the rectangle packer (i.e.stick::Float32)
     */
    template<class T>
    class RectanglePackerT
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief The position type.
         */
        typedef Vector2<T> PositionType;

        /**
         * @brief The rectangle type.
         */
        typedef Rectangle<T> RectangleType;

        /**
         * @brief The rectangle array type.
         */
        typedef stick::DynamicArray<RectangleType> RectangleArray;

        using PlacementResult = stick::Result<RectangleType>;


        /**
         * @brief Constructs the packer.
         */
        RectanglePackerT(stick::Allocator & _alloc = stick::defaultAllocator());

        /**
         * @brief Sets if the result should use power of two dimensions.
         */
        void setUsePowerOfTwo(bool _b);

        /**
         * @brief Sets if the result should use power of two dimensions.
         */
        void setMaxSize(stick::UInt32 _width, stick::UInt32 _height);

        PlacementResult placeRectangle(const RectangleType & _rect);

        stick::Error freeRectangle(const RectangleType & _rect);

        void reset(stick::UInt32 _startWidth, stick::UInt32 _startHeight);

        stick::Float32 maxWidth() const;

        stick::Float32 maxHeight() const;

        stick::Float32 currentWidth() const;

        stick::Float32 currentHeight() const;

        stick::Size freeRectangleCount() const;

        // private:

        PlacementResult placeRectangleHelper(const RectangleType & _rect);

        stick::Maybe<RectangleType> freeRectangleHelper(const RectangleType & _rect);

        RectangleArray m_freeRects;
        bool m_bPowerOfTwo;
        stick::UInt32 m_maxWidth;
        stick::UInt32 m_maxHeight;
        stick::UInt32 m_currentWidth;
        stick::UInt32 m_currentHeight;
    };

    template<class T>
    RectanglePackerT<T>::RectanglePackerT(stick::Allocator & _alloc) :
        m_freeRects(_alloc),
        m_bPowerOfTwo(false),
        m_maxWidth(1024),
        m_maxHeight(1024),
        m_currentWidth(128),
        m_currentHeight(128)
    {

    }

    template<class T>
    void RectanglePackerT<T>::setUsePowerOfTwo(bool _b)
    {
        m_bPowerOfTwo = _b;
    }

    template<class T>
    void RectanglePackerT<T>::setMaxSize(stick::UInt32 _width, stick::UInt32 _height)
    {
        m_maxWidth = _width;
        m_maxHeight = _height;
    }

    template<class T>
    void RectanglePackerT<T>::reset(stick::UInt32 _startWidth, stick::UInt32 _startHeight)
    {
        m_freeRects.clear();

        if (m_bPowerOfTwo)
        {
            m_currentWidth = upperPowerOfTwo32(_startWidth);
            m_currentHeight = upperPowerOfTwo32(_startHeight);
        }
        else
        {
            m_currentWidth = _startWidth;
            m_currentHeight = _startHeight;
        }

        m_currentWidth = std::min(m_maxWidth, m_currentWidth);
        m_currentHeight = std::min(m_maxHeight, m_currentHeight);
        if(m_currentHeight > m_maxHeight) m_maxHeight = m_currentHeight;
        if(m_currentWidth > m_maxWidth) m_maxWidth = m_currentWidth;
        m_freeRects.append(RectangleType(0, 0, m_currentWidth, m_currentHeight));
    }

    template<class T>
    typename RectanglePackerT<T>::PlacementResult RectanglePackerT<T>::placeRectangleHelper(const RectangleType & _rect)
    {
        stick::Size bestRectIndex = -1;
        ValueType bestX = std::numeric_limits<ValueType>::max();
        ValueType diffX = -std::numeric_limits<ValueType>::max();
        ValueType diffY = -std::numeric_limits<ValueType>::max();

        for (stick::Size i = 0; i < m_freeRects.count(); ++i)
        {
            ValueType dx = m_freeRects[i].width() - _rect.width();
            ValueType dy = m_freeRects[i].height() - _rect.height();

            if (dx >= 0 && dy >= 0)
            {
                if (m_freeRects[i].min().x < bestX)
                {
                    bestX = m_freeRects[i].min().x;
                    bestRectIndex = i;
                    diffX = dx;
                    diffY = dy;
                    if (bestX == 0)
                        break;
                }
            }
        }

        if (bestRectIndex != (stick::Size) - 1)
        {
            auto br = m_freeRects[bestRectIndex];
            RectangleType positionedRect(br.min(),
                                         br.min() + _rect.size());
            m_freeRects.remove(m_freeRects.begin() + bestRectIndex);

            RectangleArray newRects;
            newRects.reserve(2);
            if (diffY > 0)
            {
                newRects.append(RectangleType(PositionType(br.min().x, positionedRect.max().y), br.max()));
            }

            if (diffX > 0)
            {
                if (diffX > 0)
                {
                    newRects.append(RectangleType(PositionType(positionedRect.max().x, br.min().y),
                                                  PositionType(br.max().x, positionedRect.max().y)));
                }
                else
                {
                    newRects.append(RectangleType(PositionType(positionedRect.max().x, br.min().y),
                                                  br.max()));
                }
            }

            //check if the new rectangles can now be merged with other ones
            for(auto & r : newRects)
                freeRectangle(r);

            return positionedRect;
        }
        return stick::Error(stick::ec::InvalidOperation, "Could not place rectangle inside current dimensions", STICK_FILE, STICK_LINE);
    }

    template<class T>
    typename RectanglePackerT<T>::PlacementResult RectanglePackerT<T>::placeRectangle(const RectangleType & _rect)
    {
        PlacementResult result;
        do
        {
            //try to place it
            result = placeRectangleHelper(_rect);
            if (!result)
            {
                if (m_currentWidth < m_maxHeight || m_currentHeight < m_maxHeight)
                {
                    printf("RESIZE RECT PACKER\n");
                    //if we can't fit it, we resize the available space and adjust the freeRects accordingly
                    if (m_currentWidth <= m_currentHeight)
                    {
                        ValueType twice = std::min(m_currentWidth * 2, m_maxWidth);
                        if (m_freeRects.count())
                        {
                            auto sit = m_freeRects.begin();
                            for (; sit != m_freeRects.end(); ++sit)
                            {
                                if ((*sit).max().x == m_currentWidth)
                                {
                                    (*sit).max().x = twice;
                                }
                            }
                        }
                        else
                        {
                            m_freeRects.append(RectangleType(m_currentWidth, 0, twice, m_currentHeight));
                        }
                        m_currentWidth = twice;
                    }
                    else
                    {
                        ValueType twice = std::min(m_currentHeight * 2, m_maxHeight);
                        if (m_freeRects.count())
                        {
                            auto sit = m_freeRects.begin();
                            for (; sit != m_freeRects.end(); ++sit)
                            {
                                if ((*sit).max().y == m_currentHeight)
                                {
                                    (*sit).max().y = twice;
                                }
                            }
                        }
                        else
                        {
                            m_freeRects.append(RectangleType(0, m_currentHeight, m_currentWidth, twice));
                        }
                        m_currentHeight = twice;
                    }
                }
                else
                {
                    return stick::Error(stick::ec::InvalidOperation, "Could not place rectangle and the maximum size is reached", STICK_FILE, STICK_LINE);
                }
            }
        }
        while (!result);

        return result;
    }

    template<class T>
    stick::Maybe<typename RectanglePackerT<T>::RectangleType> RectanglePackerT<T>::freeRectangleHelper(const RectangleType & _rect)
    {
        for (auto it = m_freeRects.begin(); it != m_freeRects.end(); ++it)
        {
            if ((crunch::isClose((*it).topRight(), _rect.topLeft()) && crunch::isClose((*it).bottomRight(), _rect.bottomLeft()))  ||
                    (crunch::isClose((*it).topLeft(), _rect.topRight()) && crunch::isClose((*it).bottomLeft(), _rect.bottomRight())) ||
                    (crunch::isClose((*it).bottomLeft(), _rect.topLeft()) && crunch::isClose((*it).bottomRight(), _rect.topRight())) ||
                    (crunch::isClose((*it).topLeft(), _rect.bottomLeft()) && crunch::isClose((*it).topRight(), _rect.bottomRight())))
            {
                auto currentRect = crunch::merge(*it, _rect);
                m_freeRects.remove(it);
                return currentRect;
            }
        }
        m_freeRects.append(_rect);
        return stick::Maybe<RectangleType>();
    }

    template<class T>
    stick::Error RectanglePackerT<T>::freeRectangle(const RectangleType & _rect)
    {
        /*for (auto & rect : m_freeRects)
        {
            if (rect.overlaps(_rect))
            {
                printf("THEY OVERLAP %f %f %f %f, %f %f %f %f\n", rect.min().x, rect.min().y, rect.width(), rect.height(), _rect.min().x, _rect.min().y, _rect.width(), _rect.height());
            }
        }*/
        auto mergedRect = freeRectangleHelper(_rect);
        while (mergedRect)
        {
            mergedRect = freeRectangleHelper(*mergedRect);
        }
        return stick::Error();
    }

    template<class T>
    stick::Float32 RectanglePackerT<T>::maxWidth() const
    {
        return m_maxWidth;
    }

    template<class T>
    stick::Float32 RectanglePackerT<T>::maxHeight() const
    {
        return m_maxHeight;
    }

    template<class T>
    stick::Float32 RectanglePackerT<T>::currentWidth() const
    {
        return m_currentWidth;
    }

    template<class T>
    stick::Float32 RectanglePackerT<T>::currentHeight() const
    {
        return m_currentHeight;
    }

    template<class T>
    stick::Size RectanglePackerT<T>::freeRectangleCount() const
    {
        return m_freeRects.count();
    }

    typedef RectanglePackerT<stick::Float32> RectanglePacker;
}

#endif //CRUNCH_RECTANGLEPACKER_HPP
