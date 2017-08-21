#ifndef CRUNCH_RECTANGLE_HPP
#define CRUNCH_RECTANGLE_HPP

#include <algorithm> //for swap

#include <Crunch/Vector2.hpp>

namespace crunch
{
    /**
     * @brief A axis aligned rectangle class.
     * @arg T The value type of the rectangle (i.e.stick::Float32)
     */
    template<class T>
    class Rectangle
    {
    public:

        /**
         * @brief Type that describes a point.
         */
        using Point = Vector2<T>;
        using VectorType = Point;

        /**
         * @brief Default Constructor.
         *
         * Initializes the internal min and max value to zero.
         */
        Rectangle();

        /**
         * @brief Constructs a rectangle from a minimum and maximum coordinate.
         * @param _min The minimum coordinate of the rectangle.
         * @param _max The maximum coordinate of the rectangle.
         */
        Rectangle(const Point & _min, const Point & _max);

        /**
         * @brief Constructs a rectangle from a minimum and maximum coordinate.
         * @param _minX The minimum x coordinate of the rectangle.
         * @param _minY The minimum y coordinate of the rectangle.
         * @param _maxX The maximum x coordinate of the rectangle.
         * @param _maxY The maximum y coordinate of the rectangle.
         */
        Rectangle(T _minX, T _minY, T _maxX, T _maxY);

        /**
         * @brief Constructs a rectangle from a minimum coordinate and a stick::Size.
         * @param _min The minimum coordinate of the rectangle.
         * @param _width The width of the rectangle.
         * @param _height The height of the rectangle.
         */
        Rectangle(const Point & _min, T _width, T _height);

        /**
         * @brief Copy constructs a rectangle.
         */
        Rectangle(const Rectangle & _other);

        /**
         * @brief Assigns another rectangle to this rectangle.
         */
        Rectangle & operator = (const Rectangle & _other);

        /**
         * @brief Returns true if both rectangles are identical.
         */
        bool operator == (const Rectangle & _other);

        /**
         * @brief Returns true if both rectangles are different.
         */
        bool operator != (const Rectangle & _other);

        /**
         * @brief Returns true if the provided rectangle is fully contained.
         * by this rectangle.
         */
        bool contains(const Rectangle & _other) const;

        /**
         * @brief Returns true if the provided point is contained.
         * by this rectangle.
         */
        bool contains(const Point & _p) const;

        /**
         * @brief Returns true if the provided point is contained.
         * by this rectangle.
         */
        bool contains(T _x, T _y) const;

        /**
         * @brief Returns true if the provided rectangle.
         * overlaps with this rectangle.
         */
        bool overlaps(const Rectangle & _other) const;

        /**
         * @brief Sets the stick::Size of the rectangle.
         */
        void setSize(const Point & _size);

        /**
         * @brief Sets the stick::Size of the rectangle.
         *
         * This will change the maximum value, while keeping the minimum value.
         */
        void setSize(T _width, T _height);

        /**
         * @brief Sets the position of the rectangle.
         * This will retain the stick::Size of the rectangle.
         */
        void setPosition(const Point & _position);

        /**
         * @brief Sets the position of the rectangle.
         * This will retain the stick::Size of the rectangle.
         */
        void setPosition(T _x, T _y);

        /**
         * @brief Moves the rectangle by a certain offset.
         */
        void moveBy(const Point & _offset);

        /**
         * @brief Moves the rectangle by a certain offset.
         */
        void moveBy(T _x, T _y);

        /**
         * @brief Sets the width of the rectangle.
         */
        void setWidth(T _width);

        /**
         * @brief Sets the height of the rectangle.
         */
        void setHeight(T _height);

        /**
         * @brief Sets the minimum value of the rectangle.
         */
        void setMin(const Point & _min);

        /**
         * @brief Sets the minimum value of the rectangle.
         */
        void setMin(T _x, T _y);

        /**
         * @brief Sets the maximum value of the rectangle.
         */
        void setMax(const Point & _max);

        /**
         * @brief Sets the maximum value of the rectangle.
         */
        void setMax(T _x, T _y);

        /**
         * @brief Returns the area of the rectangle.
         */
        T area() const;

        /**
         * @brief Returns the minimum of the rectangle.
         */
        const Point & min() const;

        /**
         * @brief Returns the maximum of the rectangle.
         */
        const Point & max() const;

        /**
         * @brief Returns the minimum of the rectangle.
         */
        Point & min();

        /**
         * @brief Returns the maximum of the rectangle.
         */
        Point & max();

        /**
         * @brief Returns the top left of the rectangle.
         */
        Point topLeft() const;

        /**
         * @brief Returns the top right of the rectangle.
         */
        Point topRight() const;

        /**
         * @brief Returns the top left of the rectangle.
         */
        Point bottomRight() const;

        /**
         * @brief Returns the top right of the rectangle.
         */
        Point bottomLeft() const;

        /**
         * @brief Returns the center of the rectangle.
         */
        Point center() const;

        /**
         * @brief Returns the width of the rectangle.
         */
        T width() const;

        /**
         * @brief Returns the height of the rectangle.
         */
        T height() const;

        /**
         * @brief Returns the size of the rectangle.
         */
        Point size() const;


    private:

        Point m_min;

        Point m_max;

        void validate();
    };

    using Rectf = Rectangle<stick::Float32>;

    //free functions
    template<class T>
    Rectangle<T> merge(const Rectangle<T> & _a, const Rectangle<T> & _b);

    template<class T>
    Rectangle<T> merge(const Rectangle<T> & _a, const typename Rectangle<T>::Point & _b);


    template<class T>
    Rectangle<T>::Rectangle() :
        m_min(0),
        m_max(0)
    {

    }

    template<class T>
    Rectangle<T>::Rectangle(const Point & _min, const Point & _max) :
        m_min(_min),
        m_max(_max)
    {
        validate();
    }

    template<class T>
    Rectangle<T>::Rectangle(T _minX, T _minY, T _maxX, T _maxY) :
        m_min(_minX, _minY),
        m_max(_maxX, _maxY)
    {
        validate();
    }

    template<class T>
    Rectangle<T>::Rectangle(const Point & _min, T _width, T _height) :
        m_min(_min),
        m_max(_min + Point(_width, _height))
    {

    }

    template<class T>
    void Rectangle<T>::validate()
    {
        //this float checks the true min/max
        if (m_max.x < m_min.x)
            std::swap(m_max.x, m_min.x);

        if (m_max.y < m_min.y)
            std::swap(m_max.y, m_min.y);
    }

    template<class T>
    Rectangle<T>::Rectangle(const Rectangle & _other) :
        m_min(_other.m_min),
        m_max(_other.m_max)
    {

    }

    template<class T>
    Rectangle<T> & Rectangle<T>::operator = (const Rectangle & _other)
    {
        m_min = _other.m_min;
        m_max = _other.m_max;
        return *this;
    }

    template<class T>
    bool Rectangle<T>::operator == (const Rectangle & _other)
    {
        return (m_min == _other.m_min && m_max == _other.m_max);
    }

    template<class T>
    bool Rectangle<T>::operator != (const Rectangle & _other)
    {
        return !(*this == _other);
    }

    template<class T>
    bool Rectangle<T>::contains(const Rectangle & _other) const
    {
        return contains(_other.min()) && contains(_other.max());
    }

    template<class T>
    bool Rectangle<T>::contains(const Point & _p) const
    {
        return (_p.x >= m_min.x && _p.x <= m_max.x &&
                _p.y >= m_min.y && _p.y <= m_max.y);
    }

    template<class T>
    bool Rectangle<T>::contains(T _x, T _y) const
    {
        return contains(Point(_x, _y));
    }

    template<class T>
    bool Rectangle<T>::overlaps(const Rectangle & _other) const
    {
        if (m_min.x < _other.m_max.x && m_max.x > _other.m_min.x &&
                m_min.y < _other.m_max.y && m_max.y > _other.m_min.y)
            return true;

        return false;
    }

    template<class T>
    T Rectangle<T>::area() const
    {
        T a = m_max.x - m_min.x;
        T b = m_max.y - m_min.y;
        return a * b;
    }

    template<class T>
    void Rectangle<T>::setSize(const Point & _size)
    {
        m_max = m_min + _size;
    }

    template<class T>
    void Rectangle<T>::setSize(T _width, T _height)
    {
        m_max = m_min + Point(_width, _height);
    }

    template<class T>
    void Rectangle<T>::setPosition(const Point & _targetPos)
    {
        Point s = size();

        m_min = _targetPos;
        m_max = m_min + s;
    }

    template<class T>
    void Rectangle<T>::setPosition(T _x, T _y)
    {
        setPosition(Point(_x, _y));
    }

    template<class T>
    void Rectangle<T>::moveBy(const Point & _offset)
    {
        Point s = size();

        m_min += _offset;
        m_max = m_min + s;
    }

    template<class T>
    void Rectangle<T>::moveBy(T _x, T _y)
    {
        moveBy(Point(_x, _y));
    }

    template<class T>
    void Rectangle<T>::setWidth(T _width)
    {
        setSize(_width, height());
    }

    template<class T>
    void Rectangle<T>::setHeight(T _height)
    {
        setSize(width(), _height);
    }

    template<class T>
    void Rectangle<T>::setMin(const Point & _min)
    {
        m_min = _min;
    }

    template<class T>
    void Rectangle<T>::setMin(T _x, T _y)
    {
        setMin(Point(_x, _y));
    }

    template<class T>
    void Rectangle<T>::setMax(const Point & _max)
    {
        m_max = _max;
    }

    template<class T>
    void Rectangle<T>::setMax(T _x, T _y)
    {
        setMax(Point(_x, _y));
    }

    template<class T>
    const typename Rectangle<T>::Point & Rectangle<T>::min() const
    {
        return m_min;
    }

    template<class T>
    const typename Rectangle<T>::Point & Rectangle<T>::max() const
    {
        return m_max;
    }

    template<class T>
    typename Rectangle<T>::Point & Rectangle<T>::min()
    {
        return m_min;
    }

    template<class T>
    typename Rectangle<T>::Point & Rectangle<T>::max()
    {
        return m_max;
    }

    template<class T>
    T Rectangle<T>::width() const
    {
        return m_max.x - m_min.x;
    }

    template<class T>
    T Rectangle<T>::height() const
    {
        return m_max.y - m_min.y;
    }

    template<class T>
    typename Rectangle<T>::Point Rectangle<T>::size() const
    {
        return Point(width(), height());
    }

    template<class T>
    typename Rectangle<T>::Point Rectangle<T>::center() const
    {
        return min() + size() * 0.5;
    }

    template<class T>
    typename Rectangle<T>::Point Rectangle<T>::topLeft() const
    {
        return min();
    }

    template<class T>
    typename Rectangle<T>::Point Rectangle<T>::topRight() const
    {
        return min() + VectorType(width(), 0);
    }

    template<class T>
    typename Rectangle<T>::Point Rectangle<T>::bottomRight() const
    {
        return max();
    }

    template<class T>
    typename Rectangle<T>::Point Rectangle<T>::bottomLeft() const
    {
        return min() + VectorType(0, height());
    }

    //free function implementations

    template<class T>
    Rectangle<T> merge(const Rectangle<T> & _a, const Rectangle<T> & _b)
    {
        typename Rectangle<T>::Point min;
        typename Rectangle<T>::Point max;

        min.x = _a.min().x < _b.min().x ? _a.min().x : _b.min().x;
        min.y = _a.min().y < _b.min().y ? _a.min().y : _b.min().y;

        max.x = _a.max().x > _b.max().x ? _a.max().x : _b.max().x;
        max.y = _a.max().y > _b.max().y ? _a.max().y : _b.max().y;

        return Rectangle<T>(min, max);
    }

    template<class T>
    Rectangle<T> merge(const Rectangle<T> & _a, const typename Rectangle<T>::Point & _b)
    {
        typename Rectangle<T>::Point min;
        typename Rectangle<T>::Point max;

        min.x = _a.min().x < _b.x ? _a.min().x : _b.x;
        min.y = _a.min().y < _b.y ? _a.min().y : _b.y;

        max.x = _a.max().x > _b.x ? _a.max().x : _b.x;
        max.y = _a.max().y > _b.y ? _a.max().y : _b.y;

        return Rectangle<T>(min, max);
    }
}

#endif //CRUNCH_RECTANGLE_HPP
