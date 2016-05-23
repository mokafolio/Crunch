#ifndef CRUNCH_CIRCLE_HPP
#define CRUNCH_CIRCLE_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/Line.hpp>

namespace crunch
{
    /**
     * @brief A simple circle class.
     * @arg T The floating point type that is used internally.
     */
    template<class T>
    class Circle
    {
    public:

        /**
         * @brief The 2D vector type.
         */
        typedef Vector2<T> VectorType;

        /**
         * @brief Errors that can occur during circle construction.
         */
        enum Error
        {
            NoError = 0,
            ErrorIntersection,
            ErrorColinear
        };

        /**
         * @brief Default Constructor.
         *
         * Does nothing for speed reasons.
         */
        Circle();

        /**
         * @brief Constructs a circle from a position and radius.
         */
        Circle(const VectorType & _p, T _radius);

        /**
         * @brief Constructs a circle from three points on its circumference.
         * @param _a The first position.
         * @param _b The second position.
         * @param _c The third position.
         * @param _errorCode Holds the error, if an error occurs during construction.
         */
        Circle(const VectorType & _a, const VectorType & _b, const VectorType & _c, Error & _errorCode);

        /**
         * @brief Constructs a circle from three points on its circumference.
         * @param _a The first position.
         * @param _b The second position.
         * @param _c The third position.
         */
        Circle(const VectorType & _a, const VectorType & _b, const VectorType & _c);

        /**
         * @brief Copy constructs a circle from another circle.
         */
        Circle(const Circle & _other);

        /**
         * @brief Assigns and copies another circle to this.
         */
        Circle & operator = (const Circle & _other);

        /**
         * @brief Returns true if this equals the provided circle.
         */
        bool operator == (const Circle & _other);

        /**
         * @brief Returns true if this is not equal to the provided circle.
         */
        bool operator != (const Circle & _other);

        /**
         * @brief Returns true if the provided circle is fully contained by this.
         */
        bool contains(const Circle & _other) const;

        /**
         * @brief Returns true if the provided position is fully contained by this.
         */
        bool contains(const VectorType & _p) const;

        /**
         * @brief Returns true if the provided position is fully contained by this.
         */
        bool contains(T _x, T _y) const;

        /**
         * @brief Set the position of this circle.
         */
        void setPosition(const VectorType & _position);

        /**
         * @brief Set the radius of this circle.
         */
        void setRadius(T _radius);

        /**
         * @brief Returns the const position of this circle.
         */
        const VectorType & position() const;

        /**
         * @brief Returns a reference to the position of this circle.
         */
        VectorType & position();

        /**
         * @brief Returns the radius of this circle.
         */
        T radius() const;

    private:

        VectorType m_position;

        T m_radius;
    };


    template<class T>
    Circle<T>::Circle()
    {

    }

    template<class T>
    Circle<T>::Circle(const VectorType & _p, T _radius) :
        m_position(_p),
        m_radius(_radius)
    {

    }

    template<class T>
    Circle<T>::Circle(const VectorType & _a, const VectorType & _b, const VectorType & _c)
    {
        Error err;
        *this = Circle(_a, _b, _c, err);

        /*if (err != NoError)
        {
            if (err == ErrorColinear)
                throw std::invalid_argument("Circle: The three VectorTypes provided are colinear");
            else if (err == ErrorIntersection)
                throw std::invalid_argument("Circle: Could not intersect bisector lines");
        }*/
    }

    template<class T>
    Circle<T>::Circle(const VectorType & _a, const VectorType & _b, const VectorType & _c, Error & _errorCode)
    {
        _errorCode = NoError;

        //bisect the triangle to find circle position and radius
        VectorType lineOneStart = (_a + _b) * 0.5;
        VectorType lineOneEnd = (_b - _a);
        lineOneEnd = lineOneStart + VectorType(-lineOneEnd.y, lineOneEnd.x);
        Line<VectorType> lineOne(lineOneStart, lineOneEnd);

        VectorType lineTwoStart = (_b + _c) * 0.5;
        VectorType lineTwoEnd = (_c - _b);
        lineTwoEnd = lineTwoStart + VectorType(-lineTwoEnd.y, lineTwoEnd.x);
        Line<VectorType> lineTwo(lineTwoStart, lineTwoEnd);

        IntersectionResult<VectorType> result = crunch::intersect(lineOne, lineTwo);
        Line<VectorType> line(_a, _c);

        stick::Int32 throughSide = line.side(_b);
        if (!result)
        {
            m_position = VectorType(0);
            m_radius = -1;

            if (throughSide == 0)
                _errorCode = ErrorColinear;
            else
                _errorCode = ErrorIntersection;
            return;
        }

        m_position = result.intersections()[0];
        m_radius = distance(m_position, _a);
    }

    template<class T>
    Circle<T>::Circle(const Circle & _other) :
        m_position(_other.m_position),
        m_radius(_other.m_radius)
    {

    }

    template<class T>
    Circle<T> & Circle<T>::operator = (const Circle & _other)
    {
        m_position = _other.m_position;
        m_radius = _other.m_radius;
        return *this;
    }

    template<class T>
    bool Circle<T>::operator == (const Circle & _other)
    {
        return m_position == _other.m_position && m_radius == _other.m_radius;
    }

    template<class T>
    bool Circle<T>::operator != (const Circle & _other)
    {
        return m_position != _other.m_position || m_radius != _other.m_radius;
    }

    template<class T>
    bool Circle<T>::contains(const Circle & _other) const
    {
        if (_other.m_radius > m_radius)
            return false;
        if (distance(m_position, _other.m_position) < m_radius - _other.m_radius)
            return true;

        return false;
    }

    template<class T>
    bool Circle<T>::contains(const VectorType & _p) const
    {
        if (distance(m_position, _p) < m_radius)
            return true;

        return false;
    }

    template<class T>
    bool Circle<T>::contains(T _x, T _y) const
    {
        return contains(VectorType(_x, _y));
    }

    template<class T>
    void Circle<T>::setRadius(T _radius)
    {
        m_radius = _radius;
    }

    template<class T>
    void Circle<T>::setPosition(const VectorType & _position)
    {
        m_position = _position;
    }

    template<class T>
    const typename Circle<T>::VectorType & Circle<T>::position() const
    {
        return m_position;
    }

    template<class T>
    typename Circle<T>::VectorType & Circle<T>::position()
    {
        return m_position;
    }

    template<class T>
    T Circle<T>::radius() const
    {
        return m_radius;
    }
}

#endif //CRUNCH_CIRCLE_HPP
