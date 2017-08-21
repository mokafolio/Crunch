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
        ValueType bestX = std::numeric_limits<ValueType>::max();

        for (stick::Size i = 0; i < m_freeRects.count(); ++i)
        {
            ValueType diffX = m_freeRects[i].width() - _rect.width();
            ValueType diffY = m_freeRects[i].height() - _rect.height();

            if (diffX >= 0 && diffY >= 0)
            {
                if (m_freeRects[i].min().x < bestX)
                {
                    bestX = m_freeRects[i].min().x;
                    bestRectIndex = i;
                    bFoundFittingRect = true;
                    if (bestX == 0)
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
                    printf("OVERLAP\n");
                    if ((*it).min().x < positionedRect.min().x)
                    {
                        printf("A\n");
                        auto r = RectangleType((*it).min(), PositionType(positionedRect.min().x, (*it).max().y));
                        for (auto & rect : newRects)
                        {
                            if (r.overlaps(rect))
                            {
                                r.max().y = rect.min().y;
                            }
                        }
                        newRects.append(r);
                    }

                    if ((*it).max().x > positionedRect.max().x)
                    {
                        printf("B\n");
                        auto r = RectangleType(PositionType(positionedRect.max().x, (*it).min().y), (*it).max());
                        for (auto & rect : newRects)
                        {
                            if (r.overlaps(rect))
                            {
                                printf("ASKJALKSGJ\n");
                                r.min().y = rect.max().y;
                            }
                        }
                        newRects.append(r);
                    }

                    if ((*it).min().y < positionedRect.min().y)
                    {
                        printf("C\n");
                        auto r = RectangleType((*it).min(), PositionType((*it).max().x, positionedRect.min().y));
                        for (auto & rect : newRects)
                        {
                            if (r.overlaps(rect))
                            {
                                r.min().x = rect.max().x;
                            }
                        }
                        newRects.append(r);
                    }

                    if ((*it).max().y > positionedRect.max().y)
                    {
                        printf("D\n");
                        auto r = RectangleType(PositionType((*it).min().x, positionedRect.max().y), (*it).max());
                        for (auto & rect : newRects)
                        {
                            if (r.overlaps(rect))
                            {
                                printf("ASKJALKSGJ\n");
                                r.max().x = rect.min().x;
                            }
                        }
                        newRects.append(r);
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
                                printf("CONTAAAINS\n");
                                bIsContained = true;
                                break;
                            }
                        }
                    }

                    if (!bIsContained)
                    {
                        final.append(*sit);
                    }
                }

                //last pass to remove overlaps between new rectangles


                m_freeRects.insert(m_freeRects.end(), final.begin(), final.end());
                // for(auto rect : final)
                //     freeRectangle(rect);
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
                printf("MERGIN DA RECTS\n");
                m_freeRects.remove(it);
                return currentRect;
            }
        }
        printf("WADDDUUUP PIIIMPS\n");
        m_freeRects.append(_rect);
        printf("WADDDUUUP PIIIMPS 2\n");
        return stick::Maybe<RectangleType>();
    }

    template<class T>
    stick::Error RectanglePackerT<T>::freeRectangle(const RectangleType & _rect)
    {
        // for(auto & rect : m_freeRects)
        // {
        //     STICK_ASSERT(!_rect.contains(rect));
        // }
        auto mergedRect = freeRectangleHelper(_rect);
        while (mergedRect)
        {
            printf("WAJKHAJGSHJKAS\n");
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
