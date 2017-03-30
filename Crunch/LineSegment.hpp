#ifndef CRUNCH_LINESEGMENT_HPP
#define CRUNCH_LINESEGMENT_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/IntersectionResult.hpp>
#include <limits>

namespace crunch
{
    /**
     * @brief Describes an infinite line.
     * @arg VT The internal vector type.
     */
    template<class VT>
    class LineSegment
    {
    public:

        /**
         * @brief The internal vector type.
         */
        typedef VT VectorType;

        /**
         * @brief The internal floating point value type.
         */
        typedef typename VectorType::ValueType ValueType;

        /**
         * @brief The default constructor. Initializes both internal positions to 0.
         */
        LineSegment();

        /**
         * @brief Constructs a segment with the provided end points.
         */
        LineSegment(const VectorType & _a, const VectorType & _b);

        /**
         * @brief Copy constructs a line from an existing line.
         */
        LineSegment(const LineSegment & _other);

        /**
         * @brief Assigns and copies an existing line to this.
         */
        LineSegment & operator = (const LineSegment & _other);

        /**
         * @brief Returns the first internal position on the line.
         */
        const VectorType & positionOne() const;

        /**
         * @brief Returns the second internal position on the line.
         */
        const VectorType & positionTwo() const;

        /**
         * @brief Returns the direction of the line (not normalized).
         */
        VectorType direction() const;

        /**
         * @brief Returns the normalized direction of the line.
         */
        VectorType directionNormalized() const;

        /**
         * @brief Returns which side of the line the provided point is on.
         * @return -1 for left, 0 if the _point is on the line and 1 for right.
         */
        stick::Int32 side(const VectorType & _point) const;

        // //@TODO: Make this a free function and put it into Geometric Func?
        // ValueType signedDistance(const VectorType & _point) const;
        // ValueType distance(const VectorType & _point) const;

    private:

        VectorType m_positionOne;
        VectorType m_positionTwo;
    };

    template<class T>
    LineSegment<T>::LineSegment() :
        m_positionOne(0),
        m_positionTwo(0)
    {

    }

    template<class T>
    LineSegment<T>::LineSegment(const VectorType & _a, const VectorType & _b) :
        m_positionOne(_a),
        m_positionTwo(_b)
    {

    }

    template<class T>
    LineSegment<T>::LineSegment(const LineSegment & _other) :
        m_positionOne(_other.m_positionOne),
        m_positionTwo(_other.m_positionTwo)
    {

    }

    template<class T>
    LineSegment<T> & LineSegment<T>::operator = (const LineSegment & _other)
    {
        m_positionOne = _other.m_positionOne;
        m_positionTwo = _other.m_positionTwo;
        return *this;
    }

    template<class T>
    const typename LineSegment<T>::VectorType & LineSegment<T>::positionOne() const
    {
        return m_positionOne;
    }

    template<class T>
    const typename LineSegment<T>::VectorType & LineSegment<T>::positionTwo() const
    {
        return m_positionTwo;
    }

    template<class T>
    typename LineSegment<T>::VectorType LineSegment<T>::direction() const
    {
        return m_positionTwo - m_positionOne;
    }

    template<class T>
    typename LineSegment<T>::VectorType LineSegment<T>::directionNormalized() const
    {
        return normalize(direction());
    }

    template<class T>
    stick::Int32 LineSegment<T>::side(const VectorType & _point) const
    {
        VectorType dirA = direction();
        VectorType dirB = _point - m_positionOne;

        ValueType cross = dirB.x * dirA.y - dirB.y * dirA.x;
        if (cross == 0)
        {
            cross = dot(dirA, dirB) / dot(dirA, dirA);
            if (cross >= 0 && cross <= 1)
                cross = 0;
        }

        return cross < 0 ? -1 : cross > 0 ? 1 : 0;
    }

    // template<class T>
    // typename LineSegment<T>::ValueType LineSegment<T>::signedDistance(const VectorType & _point) const
    // {
    //     if (m_direction.x == 0)
    //     {
    //         if (m_direction.y > 0)
    //         {
    //             return _point.x - m_position.x;
    //         }
    //         else
    //         {
    //             return m_position.x - _point.x;
    //         }
    //     }
    //     else if (m_direction.y == 0)
    //     {
    //         if (m_direction.x < 0)
    //         {
    //             return _point.y - m_position.y;
    //         }
    //         else
    //         {
    //             return m_position.y - _point.y;
    //         }
    //     }

    //     return ((_point.x - m_position.x) * m_direction.y - (_point.y - m_position.y) * m_direction.x) /
    //            std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
    // }

    // template<class T>
    // typename LineSegment<T>::ValueType LineSegment<T>::distance(const VectorType & _point) const
    // {
    //     return abs(signedDistance(_point));
    // }

    template<class VT>
    IntersectionResult<VT> intersect(const LineSegment<VT> & _a, const LineSegment<VT> & _b);

    template<class T>
    IntersectionResult<Vector2<T> > intersect(const LineSegment<Vector2<T> > & _a, const LineSegment<Vector2<T> > & _b)
    {
        typedef typename IntersectionResult<Vector2<T> >::ResultArray ResultArray;

        Vector2<T> dirA = _a.direction();
        Vector2<T> dirB = _b.direction();

        //compute the intersection
        T cross = dirA.x * dirB.y - dirA.y * dirB.x;

        //parallel case (TODO: use epsilon)
        if (abs(cross) < std::numeric_limits<T>::epsilon())
            return IntersectionResult<Vector2<T> >();

        ResultArray results;

        Vector2<T> dir = _a.positionOne() - _b.positionOne();
        T d = (dir.y * dirB.x - dir.x * dirB.y) / cross;
        T t = (dir.y * dirA.x - dir.x * dirA.y) / cross;

        if (t >= 0 && t <= 1 && d >= 0 && d <= 1)
            results.append(_a.positionOne() + dirA * d);

        return IntersectionResult<Vector2<T> >(results);
    }

    using LineSegment2f = LineSegment<Vector2<stick::Float32>>;
}

#endif //CRUNCH_LINESEGMENT_HPP
