#ifndef CRUNCH_VECTOR3_HPP
#define CRUNCH_VECTOR3_HPP

#include <Crunch/Vector2.hpp>

namespace crunch
{
    template<class T>
    class Vector4;

    /**
     * @brief A 3D vector class.
     * @arg T The internal value type (i.e. stick::Float32)
     */
    template<class T>
    class Vector3
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief The individual values of the vector.
         */
        ValueType x, y, z;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Vector3();

        /**
         * @brief Constructs a vector setting its elements to the provided number.
         */
        explicit inline Vector3(T _val);

        /**
         * @brief Constructs a vector setting its x & y values to the provided numbers
         * and the z element to 1.0.
         */
        inline Vector3(T _x, T _y);

        /**
         * @brief Constructs a vector setting its elements to the provided numbers.
         */
        inline Vector3(T _x, T _y, T _z);

        /**
         * @brief Constructs a vector from another vector.
         */
        template<class OT>
        inline Vector3(const Vector3<OT> & _vec);

        /**
         * @brief Constructs a 3D vector from a 2D vector.
         * This will set the z element to 1.0.
         */
        template<class OT>
        inline Vector3(const Vector2<OT> & _vec);

        /**
         * @brief Constructs a 3D vector from a 4D vector, ignoring the w axis.
         */
        template<class OT>
        inline Vector3(const Vector4<OT> & _vec);

        /**
         * @brief Assigns another vector to this.
         */
        inline Vector3<T> & operator = (const Vector3<T> & _other);

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
        inline bool operator == (const Vector3<T> & _vec) const;

        /**
         * @brief Returns true if this vector and the provided vector are not identical.
         */
        inline bool operator != (const Vector3<T> & _vec) const;

        /**
         * @brief Adds two vectors.
         */
        inline Vector3<T> operator + (const Vector3<T>  & _vec) const;

        /**
         * @brief Subtracts two vectors.
         */
        inline Vector3<T> operator - (const Vector3<T> & _vec) const;

        /**
         * @brief Multiplies two vectors.
         */
        inline Vector3<T> operator * (const Vector3<T> & _vec) const;

        /**
         * @brief Devides one vector by another.
         */
        inline Vector3<T> operator / (const Vector3<T> & _vec) const;

        //remove this?
        inline const Vector3<T> & operator + () const;

        /**
         * @brief Negates this vector.
         */
        inline Vector3<T> operator - () const;

        /**
         * @brief Subtracts another vector from this vector.
         */
        inline Vector3<T> & operator -= (const Vector3<T> & _vec);

        /**
         * @brief Adds another vector to this vector.
         */
        inline Vector3<T> & operator += (const Vector3<T> & _vec);

        /**
         * @brief Multiplies this vector by another vector.
         */
        inline Vector3<T> & operator *= (const Vector3<T> & _vec);

        /**
         * @brief Devides this vector by another vector.
         */
        inline Vector3<T> & operator /= (const Vector3<T> & _vec);

        /**
         * @brief Devides a vector by a number.
         */
        inline Vector3<T> operator / (T _val) const;

        /**
         * @brief Multiplies a vector by a number.
         */
        inline Vector3<T> operator * (T _val) const;

        /**
         * @brief Adds a number to a vector.
         */
        inline Vector3<T> operator + (T _val) const;

        /**
         * @brief Subtracts a number from a vector.
         */
        inline Vector3<T> operator - (T _val) const;

        /**
         * @brief Devides this vector by a number.
         */
        inline Vector3<T> & operator /= (T _val);

        /**
         * @brief Multiplies this vector by a number.
         */
        inline Vector3<T> & operator *= (T _val);

        /**
         * @brief Adds a number to this vector.
         */
        inline Vector3<T> & operator += (T _val);

        /**
         * @brief Subtracts a number from this vector.
         */
        inline Vector3<T> & operator -= (T _val);

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
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xxx() const { return Vector3<T>(x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xxy() const { return Vector3<T>(x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xxz() const { return Vector3<T>(x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xyx() const { return Vector3<T>(x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xyy() const { return Vector3<T>(x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xyz() const { return Vector3<T>(x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xzx() const { return Vector3<T>(x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xzy() const { return Vector3<T>(x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xzz() const { return Vector3<T>(x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yxx() const { return Vector3<T>(y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yxy() const { return Vector3<T>(y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yxz() const { return Vector3<T>(y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yyx() const { return Vector3<T>(y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yyy() const { return Vector3<T>(y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yyz() const { return Vector3<T>(y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yzx() const { return Vector3<T>(y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yzy() const { return Vector3<T>(y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yzz() const { return Vector3<T>(y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zxx() const { return Vector3<T>(z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zxy() const { return Vector3<T>(z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zxz() const { return Vector3<T>(z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zyx() const { return Vector3<T>(z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zyy() const { return Vector3<T>(z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zyz() const { return Vector3<T>(z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zzx() const { return Vector3<T>(z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zzy() const { return Vector3<T>(z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zzz() const { return Vector3<T>(z, z, z); }

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
        inline Vector2<T> xz() const { return Vector2<T>(x, z); }

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

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> yz() const { return Vector2<T>(y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> zx() const { return Vector2<T>(z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> zy() const { return Vector2<T>(z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> zz() const { return Vector2<T>(z, z); }

        //Setters

        /**
         * @brief Swizzle setter function.
         */
        inline void xyz(const Vector3<T> & _vec) { x = _vec.x; y = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzy(const Vector3<T> & _vec) { x = _vec.x; z = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxz(const Vector3<T> & _vec) { y = _vec.x; x = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzx(const Vector3<T> & _vec) { y = _vec.x; z = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxy(const Vector3<T> & _vec) { z = _vec.x; x = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zyx(const Vector3<T> & _vec) { z = _vec.x; y = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xy(const Vector2<T> & _vec) { x = _vec.x; y = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xz(const Vector2<T> & _vec) { x = _vec.x; z = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yx(const Vector2<T> & _vec) { y = _vec.x; x = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yz(const Vector2<T> & _vec) { y = _vec.x; z = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zx(const Vector2<T> & _vec) { z = _vec.x; x = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zy(const Vector2<T> & _vec) { z = _vec.x; y = _vec.y; }

        //swizzleGenerator.py end
    };
}

#include <Crunch/Vector4.hpp>

namespace crunch
{
    template<class T>
    inline Vector3<T>::Vector3()
    {
    }

    template<class T>
    inline Vector3<T>::Vector3(T _val) :
        x(_val),
        y(_val),
        z(_val)
    {
    }

    template<class T>
    inline Vector3<T>::Vector3(T _x, T _y) :
        x(_x),
        y(_y),
        z(1.0)
    {
    }

    template<class T>
    inline Vector3<T>::Vector3(T _x, T _y, T _z) :
        x(_x),
        y(_y),
        z(_z)
    {
    }

    template<class T>
    template<class OT>
    inline Vector3<T>::Vector3(const Vector3<OT> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(_vec.z)
    {
    }

    template<class T>
    template<class OT>
    inline Vector3<T>::Vector3(const Vector2<OT> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(1.0)
    {
    }

    template<class T>
    template<class OT>
    inline Vector3<T>::Vector3(const Vector4<OT> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(_vec.z)
    {
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator = (const Vector3<T> & _other)
    {
        x = _other.x;
        y = _other.y;
        z = _other.z;

        return *this;
    }


    // Access
    //____________________________________

    template<class T>
    inline T & Vector3<T>::operator [](stick::UInt32 _index)
    {
        return *(&x + _index);
    }

    template<class T>
    inline const T & Vector3<T>::operator [](stick::UInt32 _index) const
    {
        return *(&x + _index);
    }



    // Boolean
    //____________________________________

    template<class T>
    inline bool Vector3<T>::operator == (const Vector3<T> & _vec) const
    {
        if (x == _vec.x && y == _vec.y && z == _vec.z)
            return true;
        else
            return false;
    }

    template<class T>
    inline bool Vector3<T>::operator != (const Vector3<T> & _vec) const
    {
        if (x == _vec.x && y == _vec.y && z == _vec.z)
            return false;
        else
            return true;
    }


    // Arithmetic operations
    //____________________________________

    template<class T>
    inline Vector3<T> Vector3<T>::operator + (const Vector3<T> & _vec) const
    {
        Vector3<T> ret;
        ret.x = x + _vec.x;
        ret.y = y + _vec.y;
        ret.z = z + _vec.z;
        return ret;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator - (const Vector3<T> & _vec) const
    {
        Vector3<T> ret;
        ret.x = x - _vec.x;
        ret.y = y - _vec.y;
        ret.z = z - _vec.z;
        return ret;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator * (const Vector3<T> & _vec) const
    {
        Vector3<T> ret;
        ret.x = x * _vec.x;
        ret.y = y * _vec.y;
        ret.z = z * _vec.z;
        return ret;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator / (const Vector3<T> & _vec) const
    {
        Vector3<T> ret;
        ret.x = x / _vec.x;
        ret.y = y / _vec.y;
        ret.z = z / _vec.z;
        return ret;
    }

    template<class T>
    inline const Vector3<T> & Vector3<T>::operator + () const
    {
        return *this;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator - () const
    {
        return Vector3<T>(-x, -y, -z);
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator -= (const Vector3<T> & _vec)
    {
        x -= _vec.x;
        y -= _vec.y;
        z -= _vec.z;
        return *this;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator += (const Vector3<T> & _vec)
    {
        x += _vec.x;
        y += _vec.y;
        z += _vec.z;
        return *this;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator *= (const Vector3<T> & _vec)
    {
        x *= _vec.x;
        y *= _vec.y;
        z *= _vec.z;
        return *this;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator /= (const Vector3<T> & _vec)
    {
        x /= _vec.x;
        y /= _vec.y;
        z /= _vec.z;
        return *this;
    }

    // Real Arithmetic
    //____________________________________


    template<class T>
    inline Vector3<T> Vector3<T>::operator / (T _val) const
    {
        Vector3<T> ret;
        ret.x = x / _val;
        ret.y = y / _val;
        ret.z = z / _val;
        return ret;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator * (T _val) const
    {
        Vector3<T> ret;
        ret.x = x * _val;
        ret.y = y * _val;
        ret.z = z * _val;
        return ret;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator + (T _val) const
    {
        Vector3<T> ret;
        ret.x = x + _val;
        ret.y = y + _val;
        ret.z = z + _val;
        return ret;
    }

    template<class T>
    inline Vector3<T> Vector3<T>::operator - (T _val) const
    {
        Vector3<T> ret;
        ret.x = x - _val;
        ret.y = y - _val;
        ret.z = z - _val;
        return ret;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator /= (T _val)
    {
        x /= _val;
        y /= _val;
        z /= _val;
        return *this;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator *= (T _val)
    {
        x *= _val;
        y *= _val;
        z *= _val;
        return *this;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator += (T _val)
    {
        x += _val;
        y += _val;
        z += _val;
        return *this;
    }

    template<class T>
    inline Vector3<T> & Vector3<T>::operator -= (T _val)
    {
        x -= _val;
        y -= _val;
        z -= _val;
        return *this;
    }


    //Pointer accessors
    //____________________________________


    template<class T>
    inline T * Vector3<T>::ptr()
    {
        return &x;
    }

    template<class T>
    inline const T * Vector3<T>::ptr() const
    {
        return &x;
    }

    using Vec3f = Vector3<stick::Float32>;
}

#endif //CRUNCH_VECTOR3_HPP
