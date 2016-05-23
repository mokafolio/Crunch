#ifndef CRUNCH_VECTOR2_HPP
#define CRUNCH_VECTOR2_HPP

#include <Stick/Platform.hpp>

namespace crunch
{
    template<class T>
    class Vector3;

    template<class T>
    class Vector4;

    /**
     * @brief A 2D vector class.
     * @arg T The internal value type (i.e. stick::Float32)
     */
    template<class T>
    class Vector2
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief The individual values of the vector.
         */
        ValueType x, y;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Vector2();

        /**
         * @brief Constructs a vector setting its elements to the provided number.
         */
        explicit inline Vector2(T _val);

        /**
         * @brief Constructs a vector setting its elements to the provided numbers.
         */
        inline Vector2(T _x, T _y);

        /**
         * @brief Constructs a vector from another vector.
         */
        template<class OT>
        inline Vector2(const Vector2<OT> & _vec);

        /**
         * @brief Constructs a 2D vector from a 3D vector, ignoring the z axis.
         */
        template<class OT>
        inline Vector2(const Vector3<OT> & _vec);

        /**
         * @brief Constructs a 2D vector from a 4D vector, ignoring the z & w axis.
         */
        template<class OT>
        inline Vector2(const Vector4<OT> & _vec);

        /**
         * @brief Assigns another vector to this.
         */
        inline Vector2<T> & operator = (const Vector2<T> & _other);

        /**
         * @brief Access an element of the vector by index.
         *
         * WARNING: This does not bounds check.
         *
         * @param _index The index.
         * @return A reference to the element.
         */
        inline T & operator [](stick::UInt32 _index);

        /**
         * @brief Access an element of the vector by index.
         *
         * WARNING: This does not bounds check.
         *
         * @param _index The index.
         * @return A const reference to the element.
         */
        inline const T & operator [](stick::UInt32 _index) const;

        /**
         * @brief Returns true if this vector and the provided vector are identical.
         */
        inline bool operator == (const Vector2<T> & _vec) const;

        /**
         * @brief Returns true if this vector and the provided vector are not identical.
         */
        inline bool operator != (const Vector2<T> & _vec) const;

        /**
         * @brief Adds two vectors.
         */
        inline Vector2<T> operator + (const Vector2<T> & _vec) const;

        /**
         * @brief Subtracts two vectors.
         */
        inline Vector2<T> operator - (const Vector2<T> & _vec) const;

        /**
         * @brief Multiplies two vectors.
         */
        inline Vector2<T> operator * (const Vector2<T> & _vec) const;

        /**
         * @brief Devides one vector by another.
         */
        inline Vector2<T> operator / (const Vector2<T> & _vec) const;

        //remove this?
        inline const Vector2<T> & operator + () const;

        /**
         * @brief Negates this vector.
         */
        inline Vector2<T> operator - () const;

        /**
         * @brief Subtracts another vector from this vector.
         */
        inline Vector2<T> & operator -= (const Vector2<T> & _vec);

        /**
         * @brief Adds another vector to this vector.
         */
        inline Vector2<T> & operator += (const Vector2<T> & _vec);

        /**
         * @brief Multiplies this vector by another vector.
         */
        inline Vector2<T> & operator *= (const Vector2<T> & _vec);

        /**
         * @brief Devides this vector by another vector.
         */
        inline Vector2<T> & operator /= (const Vector2<T> & _vec);

        /**
         * @brief Devides a vector by a number.
         */
        inline Vector2<T> operator / (T _val) const;

        /**
         * @brief Multiplies a vector by a number.
         */
        inline Vector2<T> operator * (T _val) const;

        /**
         * @brief Adds a number to a vector.
         */
        inline Vector2<T> operator + (T _val) const;

        /**
         * @brief Subtracts a number from a vector.
         */
        inline Vector2<T> operator - (T _val) const;

        /**
         * @brief Devides this vector by a number.
         */
        inline Vector2<T> & operator /= (T _val);

        /**
         * @brief Multiplies this vector by a number.
         */
        inline Vector2<T> & operator *= (T _val);

        /**
         * @brief Adds a number to this vector.
         */
        inline Vector2<T> & operator += (T _val);

        /**
         * @brief Subtracts a number from this vector.
         */
        inline Vector2<T> & operator -= (T _val);

        /**
         * @brief Returns a pointer to the memory block of this vector.
         */
        inline T * ptr();

        /**
         * @brief Returns a pointer to the memory block of this vector.
         */
        inline const T * ptr() const;

        //These swizzle operators are automatically generated by swizzleGenerator.py

        //Getters

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> xx() const { return Vector2<T>(x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> xy() const { return Vector2<T>(x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> yx() const { return Vector2<T>(y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> yy() const { return Vector2<T>(y, y); }

        //Setters

        /**
         * @brief Swizzle setter function.
         */
        inline void xy(const Vector2<T> & _vec) { x = _vec.x; y = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yx(const Vector2<T> & _vec) { y = _vec.x; x = _vec.y; }
    };
}

#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>

namespace crunch
{

    // Constructors
    //____________________________________

    // this does not init to zero for speed reasons!
    template<class T>
    inline Vector2<T>::Vector2()
    {
    }

    template<class T>
    inline Vector2<T>::Vector2(T _val) :
        x(_val),
        y(_val)
    {

    }

    template<class T>
    inline Vector2<T>::Vector2(T _x, T _y) :
        x(_x),
        y(_y)
    {
    }

    template<class T>
    template<class OT>
    inline Vector2<T>::Vector2(const Vector2<OT> & _vec):
        x(_vec.x),
        y(_vec.y)
    {

    }

    template<class T>
    template<class OT>
    inline Vector2<T>::Vector2(const Vector3<OT> & _vec) :
        x(_vec.x),
        y(_vec.y)
    {
    }

    template<class T>
    template<class OT>
    inline Vector2<T>::Vector2(const Vector4<OT> & _vec) :
        x(_vec.x),
        y(_vec.y)
    {
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator = (const Vector2<T> & _other)
    {
        x = _other.x;
        y = _other.y;
        return *this;
    }

    template<class T>
    inline T & Vector2<T>::operator [](stick::UInt32 _index)
    {
        return *(&x + _index);
    }

    template<class T>
    inline const T & Vector2<T>::operator [](stick::UInt32 _index) const
    {
        return *(&x + _index);
    }


    // Boolean
    //____________________________________

    template<class T>
    inline bool Vector2<T>::operator == (const Vector2<T> & _vec) const
    {
        if (x == _vec.x && y == _vec.y)
            return true;
        else
            return false;
    }

    template<class T>
    inline bool Vector2<T>::operator != (const Vector2<T> & _vec) const
    {
        if (x == _vec.x && y == _vec.y)
            return false;
        else
            return true;
    }


    // Arithmetic operations
    //____________________________________

    template<class T>
    inline Vector2<T> Vector2<T>::operator + (const Vector2<T> & _vec) const
    {
        Vector2<T> ret;
        ret.x = x + _vec.x;
        ret.y = y + _vec.y;
        return ret;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator - (const Vector2<T> & _vec) const
    {
        Vector2<T> ret;
        ret.x = x - _vec.x;
        ret.y = y - _vec.y;
        return ret;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator * (const Vector2<T> & _vec) const
    {
        Vector2<T> ret;
        ret.x = x * _vec.x;
        ret.y = y * _vec.y;
        return ret;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator / (const Vector2<T> & _vec) const
    {
        Vector2<T> ret;
        ret.x = x / _vec.x;
        ret.y = y / _vec.y;
        return ret;
    }

    template<class T>
    inline const Vector2<T> & Vector2<T>::operator + () const
    {
        return *this;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator - () const
    {
        return Vector2<T>(-x, -y);
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator -= (const Vector2<T> & _vec)
    {
        x -= _vec.x;
        y -= _vec.y;
        return *this;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator += (const Vector2<T> & _vec)
    {
        x += _vec.x;
        y += _vec.y;
        return *this;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator *= (const Vector2<T> & _vec)
    {
        x *= _vec.x;
        y *= _vec.y;
        return *this;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator /= (const Vector2<T> & _vec)
    {
        x /= _vec.x;
        y /= _vec.y;
        return *this;
    }


    // Real Arithmetic
    //____________________________________

    template<class T>
    inline Vector2<T> Vector2<T>::operator / (T _val) const
    {
        Vector2<T> ret;
        ret.x = x / _val;
        ret.y = y / _val;
        return ret;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator * (T _val) const
    {
        Vector2<T> ret;
        ret.x = x * _val;
        ret.y = y * _val;
        return ret;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator + (T _val) const
    {
        Vector2<T> ret;
        ret.x = x + _val;
        ret.y = y + _val;
        return ret;
    }

    template<class T>
    inline Vector2<T> Vector2<T>::operator - (T _val) const
    {
        Vector2<T> ret;
        ret.x = x - _val;
        ret.y = y - _val;
        return ret;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator /= (T _val)
    {
        x /= _val;
        y /= _val;
        return *this;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator *= (T _val)
    {
        x *= _val;
        y *= _val;
        return *this;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator += (T _val)
    {
        x += _val;
        y += _val;
        return *this;
    }

    template<class T>
    inline Vector2<T> & Vector2<T>::operator -= (T _val)
    {
        x -= _val;
        y -= _val;
        return *this;
    }

    //Pointer accessors
    //____________________________________

    template<class T>
    inline T * Vector2<T>::ptr()
    {
        return &x;
    }

    template<class T>
    inline const T * Vector2<T>::ptr() const
    {
        return &x;
    }

    using Vec2f = Vector2<stick::Float32>;
}

#endif //CRUNCH_VECTOR2_HPP
