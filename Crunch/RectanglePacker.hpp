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

        void reset(stick::UInt32 _startWidth, stick::UInt32 _startHeight);

        stick::Float32 maxWidth() const;

        stick::Float32 maxHeight() const;

    private:

        PlacementResult placeRectangleHelper(const RectangleType & _rect);

        RectangleArray m_freeRects;
        bool m_bPowerOfTwo;
        stick::UInt32 m_maxWidth;
        stick::UInt32 m_maxHeight;
        stick::UInt32 m_currentWidth;
        stick::UInt32 m_currentHeight;
    };

    /*namespace detail
    {
        template<class T>
        inline bool sortRectsByHeight(const Rectangle<T> & _a, const Rectangle<T> & _b)
        {
            return _a.height() > _b.height();
        }
    }*/

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
        m_freeRects.append(RectangleType(0, 0, m_currentWidth, m_currentHeight));
    }

    template<class T>
    typename RectanglePackerT<T>::PlacementResult RectanglePackerT<T>::placeRectangleHelper(const RectangleType & _rect)
    {
        bool bFoundFittingRect = false;
        stick::Size bestRectIndex = 0;
        ValueType bestY = std::numeric_limits<ValueType>::max();

        for (stick::Size i = 0; i < m_freeRects.count(); ++i)
        {

            //printf("TRYING TO FIT %f, %f, %f, %f\n", m_freeRects[i].min().x, m_freeRects[i].min().y, m_freeRects[i].max().x, m_freeRects[i].max().y);
            ValueType diffX = m_freeRects[i].width() - _rect.width();
            ValueType diffY = m_freeRects[i].height() - _rect.height();

            if (diffX >= 0 && diffY >= 0)
            {
                if (m_freeRects[i].min().y < bestY)
                {
                    bestY = m_freeRects[i].min().y;
                    bestRectIndex = i;
                    bFoundFittingRect = true;
                    if (bestY == 0)
                        break;
                }
            }
            /*else if (diffX == 0 && diffY == 0)
            {
                bFoundFittingRect = true;
                bestRectIndex = i;
                break;
            }*/
        }

        if (bFoundFittingRect)
        {
            RectangleType positionedRect(m_freeRects[bestRectIndex].min(),
                                         m_freeRects[bestRectIndex].min() + _rect.size());

            //check with which existing free rects the new positioned rect intersects
            RectangleArray newRects;
            newRects.reserve(m_freeRects.count());
            auto it = m_freeRects.begin();
            for (; it != m_freeRects.end();)
            {
                //check if the intersect
                if ((*it).overlaps(positionedRect))
                {
                    if ((*it).min().x < positionedRect.min().x)
                    {
                        newRects.append(RectangleType((*it).min(), PositionType(positionedRect.min().x, (*it).max().y)));
                    }

                    if ((*it).max().x > positionedRect.max().x)
                    {
                        newRects.append(RectangleType(PositionType(positionedRect.max().x, (*it).min().y), (*it).max()));
                    }

                    if ((*it).min().y < positionedRect.min().y)
                    {
                        newRects.append(RectangleType((*it).min(), PositionType((*it).max().x, positionedRect.min().y)));
                    }

                    if ((*it).max().y > positionedRect.max().y)
                    {
                        newRects.append(RectangleType(PositionType((*it).min().x, positionedRect.max().y), (*it).max()));
                    }
                    it = m_freeRects.remove(it);
                }
                else
                {
                    ++it;
                }
            }

            {
                auto sit = newRects.begin();
                RectangleArray final;
                final.reserve(newRects.count());
                for (; sit != newRects.end(); ++sit)
                {
                    bool bIsContained = false;
                    auto tit = newRects.begin();
                    for (; tit != newRects.end(); ++tit)
                    {
                        if (tit != sit)
                        {
                            if ((*tit).contains(*sit))
                            {
                                bIsContained = true;
                                break;
                            }
                        }
                    }
                    if (!bIsContained)
                        final.append(*sit);
                }

                m_freeRects.insert(m_freeRects.end(), final.begin(), final.end());
            }

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
                    //if we can't fit it, we resize the available space and adjust the freeRects accordingly
                    if (m_currentWidth < m_currentHeight)
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
    stick::Float32 RectanglePackerT<T>::maxWidth() const
    {
        return m_maxWidth;
    }

    template<class T>
    stick::Float32 RectanglePackerT<T>::maxHeight() const
    {
        return m_maxHeight;
    }

    typedef RectanglePackerT<stick::Float32> RectanglePacker;
}

#endif //CRUNCH_RECTANGLEPACKER_HPP
