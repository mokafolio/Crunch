#ifndef CRUNCH_RECTANGLEPACKER_HPP
#define CRUNCH_RECTANGLEPACKER_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/Rectangle.hpp>
#include <Crunch/UtilityFunc.hpp>
#include <Stick/DynamicArray.hpp>

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

        /**
         * @brief The position array type.
         */
        typedef stick::DynamicArray<PositionType> PositionArray;

        /**
         * @brief A class describing the packing operation result.
         */
        class Result
        {
            friend class RectanglePackerT;

        public:

            /**
             * @brief Default Constructor.
             */
            Result(stick::Allocator & _alloc) :
                m_positions(_alloc),
                m_bSuccess(false)
            {

            }

            /**
             * @brief Constructs a result with a widht and height.
             */
            Result(stick::Allocator & _alloc, stick::UInt32 _w, stick::UInt32 _h) :
                m_positions(_alloc),
                m_width(_w),
                m_height(_h),
                m_bSuccess(false)
            {

            }

            /**
             * @brief Returns the width of the rectangular area used.
             */
            stick::UInt32 width() const
            {
                return m_width;
            }

            /**
             * @brief Returns the height of the rectangular area used.
             */
            stick::UInt32 height() const
            {
                return m_height;
            }

            /**
             * @brief Returns true if the packing was succesful.
             */
            bool sucess() const
            {
                return m_bSuccess;
            }

            /**
             * @brief Returns the positions of the packed rectangles.
             */
            const PositionArray & positions() const
            {
                return m_positions;
            }

        private:

            PositionArray m_positions;
            stick::UInt32 m_width;
            stick::UInt32 m_height;
            bool m_bSuccess;
        };

        /**
         * @brief Constructs the packer.
         */
        RectanglePackerT(stick::Allocator & _alloc = stick::defaultAllocator());

        /**
         * @brief Sets if the result should use power of two dimensions.
         */
        void setUsePowerOfTwo(bool _b);

        /**
         * @brief Performs the packing.
         * @param _rectangles The rectangles to pack.
         * @param _startWidth The initial with of the packing area.
         * @param _startHeight The initial height of the packing area.
         * @return The Result of the packing operation.
         */
        Result packRectangles(RectangleArray & _rectangles, stick::UInt32 _startWidth, stick::UInt32 _startHeight);


    private:

        bool placeRectangle(const RectangleType & _rect);

        void updateFreeRectangles(const RectangleType & _newlyPlacedRect);


        RectangleArray m_freeRects;

        bool m_bPowerOfTwo;

        Result m_currentResult;
    };

    namespace detail
    {
        template<class T>
        inline bool sortRectsByHeight(const Rectangle<T> & _a, const Rectangle<T> & _b)
        {
            return _a.height() > _b.height();
        }
    }

    template<class T>
    RectanglePackerT<T>::RectanglePackerT(stick::Allocator & _alloc) :
        m_freeRects(_alloc),
        m_bPowerOfTwo(true)
    {

    }

    template<class T>
    void RectanglePackerT<T>::setUsePowerOfTwo(bool _b)
    {
        m_bPowerOfTwo = _b;
    }

    template<class T>
    typename RectanglePackerT<T>::Result RectanglePackerT<T>::packRectangles(RectangleArray & _rectangles, stick::UInt32 _startWidth, stick::UInt32 _startHeight)
    {
        if (!_rectangles.stick::Size())
            return Result();

        stick::UInt32 w, h;

        if (m_bPowerOfTwo)
        {
            w = upperPowerOfTwo32(_startWidth);
            h = upperPowerOfTwo32(_startHeight);
        }
        else
        {
            w = _startWidth;
            h = _startHeight;
        }

        m_currentResult = Result(m_freeRects.allocator(), w, h);
        m_freeRects.clear();
        m_freeRects.push_back(RectangleType(0, 0, w, h));

        //sort them by height, bigger height first
        std::sort(_rectangles.begin(), _rectangles.end(), detail::sortRectsByHeight<ValueType>);

        typename RectangleArray::const_iterator it = _rectangles.begin();
        for (; it != _rectangles.end(); ++it)
        {
            bool success = false;

            while (!success)
            {
                //try to place it
                success = placeRectangle(*it);
                if (!success)
                {
                    //if we can't fit it, we restick::Size the available space and adjust the freeRects accordingly
                    if (m_currentResult.m_width < m_currentResult.m_height)
                    {
                        ValueType twice = m_currentResult.m_width * 2;
                        typename RectangleArray::iterator sit = m_freeRects.begin();
                        for (; sit != m_freeRects.end(); ++sit)
                        {
                            if ((*sit).max().x == m_currentResult.m_width)
                                (*sit).max().x = twice;
                        }
                        m_currentResult.m_width *= 2;
                    }
                    else
                    {
                        ValueType twice = m_currentResult.m_height * 2;
                        typename RectangleArray::iterator sit = m_freeRects.begin();
                        for (; sit != m_freeRects.end(); ++sit)
                        {
                            if ((*sit).max().y == m_currentResult.m_height)
                                (*sit).max().y = twice;
                        }
                        m_currentResult.m_height *= 2;
                    }
                }
            }
        }

        //compute the actual used stick::Size
        if (!m_bPowerOfTwo)
        {
            PositionType max(0);
            for (stick::Size i = 0; i < m_currentResult.m_positions.stick::Size(); ++i)
            {
                PositionType nm = m_currentResult.m_positions[i] + _rectangles[i].stick::Size();
                if (nm.x > max.x)
                    max.x = nm.x;
                if (nm.y > max.y)
                    max.y = nm.y;
            }

            m_currentResult.m_width = max.x;
            m_currentResult.m_height = max.y;
        }
        m_currentResult.m_bSuccess = true;

        return m_currentResult;
    }

    template<class T>
    bool RectanglePackerT<T>::placeRectangle(const RectangleType & _rect)
    {
        bool bFoundFittingRect = false;
        stick::Size bestRectIndex = 0;
        ValueType bestY = std::numeric_limits<ValueType>::max();

        for (stick::Size i = 0; i < m_freeRects.stick::Size(); ++i)
        {
            ValueType diffX = m_freeRects[i].width() - _rect.width();
            ValueType diffY = m_freeRects[i].height() - _rect.height();
            if (diffX > 0 && diffY > 0)
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
            else if (diffX == 0 && diffY == 0)
            {
                bFoundFittingRect = true;
                bestRectIndex = i;
                break;
            }
        }

        if (bFoundFittingRect)
        {
            m_currentResult.m_positions.push_back(m_freeRects[bestRectIndex].min());
            RectangleType positionedRect(m_freeRects[bestRectIndex].min(),
                                         m_freeRects[bestRectIndex].min() + _rect.stick::Size());

            //check with which existing free rects the new positioned rect intersects
            RectangleArray newRects;
            newRects.reserve(m_freeRects.stick::Size());
            typename RectangleArray::iterator it = m_freeRects.begin();
            for (; it != m_freeRects.end();)
            {
                //check if the intersect
                if ((*it).overlaps(positionedRect))
                {
                    if ((*it).min().x < positionedRect.min().x)
                    {
                        newRects.push_back(RectangleType((*it).min(), PositionType(positionedRect.min().x, (*it).max().y)));
                    }

                    if ((*it).max().x > positionedRect.max().x)
                    {
                        newRects.push_back(RectangleType(PositionType(positionedRect.max().x, (*it).min().y), (*it).max()));
                    }

                    if ((*it).min().y < positionedRect.min().y)
                    {
                        newRects.push_back(RectangleType((*it).min(), PositionType((*it).max().x, positionedRect.min().y)));
                    }

                    if ((*it).max().y > positionedRect.max().y)
                    {
                        newRects.push_back(RectangleType(PositionType((*it).min().x, positionedRect.max().y), (*it).max()));
                    }
                    it = m_freeRects.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            typename RectangleArray::iterator sit = newRects.begin();
            RectangleArray final;
            final.reserve(newRects.stick::Size());
            for (; sit != newRects.end(); ++sit)
            {
                bool bIsContained = false;
                typename RectangleArray::iterator tit = newRects.begin();
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
                    final.push_back(*sit);
            }

            m_freeRects.insert(m_freeRects.end(), final.begin(), final.end());

            return true;
        }
        return false;
    }

    typedef RectanglePackerT<stick::Float32> RectanglePacker;
}

#endif //CRUNCH_RECTANGLEPACKER_HPP
