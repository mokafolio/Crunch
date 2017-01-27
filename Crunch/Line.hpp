#ifndef CRUNCH_LINE_HPP
#define CRUNCH_LINE_HPP

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
    class Line
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
        Line();

        /**
         * @brief Constructs a line from that goes through the provided position with with provided direction.
         */
        Line(const VectorType & _position, const VectorType & _direction);

        /**
         * @brief Copy constructs a line from an existing line.
         */
        Line(const Line & _other);

        /**
         * @brief Assigns and copies an existing line to this.
         */
        Line & operator = (const Line & _other);

        /**
         * @brief Returns the first internal position on the line.
         */
        const VectorType & position() const;

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


        static Line fromPoints(const VectorType & _a, const VectorType & _b);


    private:

        VectorType m_position;
        VectorType m_direction;
    };

    template<class T>
    Line<T>::Line() :
        m_position(0),
        m_direction(0)
    {

    }

    template<class T>
    Line<T>::Line(const VectorType & _position, const VectorType & _direction) :
        m_position(_position),
        m_direction(_direction)
    {

    }

    template<class T>
    Line<T>::Line(const Line & _other) :
        m_position(_other.m_position),
        m_direction(_other.m_direction)
    {

    }

    template<class T>
    Line<T> & Line<T>::operator = (const Line & _other)
    {
        m_position = _other.m_position;
        m_direction = _other.m_direction;
        return *this;
    }

    template<class T>
    const typename Line<T>::VectorType & Line<T>::position() const
    {
        return m_position;
    }

    template<class T>
    typename Line<T>::VectorType Line<T>::direction() const
    {
        return m_direction;
    }

    template<class T>
    typename Line<T>::VectorType Line<T>::directionNormalized() const
    {
        return normalize(direction());
    }

    template<class T>
    stick::Int32 Line<T>::side(const VectorType & _point) const
    {
        VectorType dirA = direction();
        VectorType dirB = _point - m_position;

        ValueType cross = dirB.x * dirA.y - dirB.y * dirA.x;

        return cross < 0 ? -1 : cross > 0 ? 1 : 0;
    }

    template<class T>
    Line<T> Line<T>::fromPoints(const VectorType & _a, const VectorType & _b)
    {
        return Line<T>(_a, _b - _a);
    }

    template<class VT>
    IntersectionResult<VT> intersect(const Line<VT> & _a, const Line<VT> & _b);

    template<class T>
    IntersectionResult<Vector2<T> > intersect(const Line<Vector2<T> > & _a, const Line<Vector2<T> > & _b)
    {
        typedef typename IntersectionResult<Vector2<T> >::ResultArray ResultArray;

        Vector2<T> dirA = _a.direction();
        Vector2<T> dirB = _b.direction();

        //compute the intersection
        T cross = dirA.x * dirB.y - dirA.y * dirB.x;

        //parallel case
        if (abs(cross) < std::numeric_limits<T>::epsilon())
            return IntersectionResult<Vector2<T> >();

        ResultArray results;

        Vector2<T> dir = _a.position() - _b.position();
        T d = (dir.y * dirB.x - dir.x * dirB.y) / cross;
        //T t = (dir.y * dirA.x - dir.x * dirA.y) / cross;
        /*if(t >= 0 && t <= 1 && d >= 0 && d <= 1)*/
        
        results.append(_a.position() + dirA * d);

        return IntersectionResult<Vector2<T> >(results);
    }

    using Line2f = Line<Vector2<stick::Float32>>;
}

#endif //CRUNCH_LINE_HPP
