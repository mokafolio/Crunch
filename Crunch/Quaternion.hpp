#ifndef CRUNCH_QUATERNION_HPP
#define CRUNCH_QUATERNION_HPP

#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>
#include <Crunch/ExponentialFunc.hpp>
#include <Crunch/GeometricFunc.hpp>
#include <cmath>

namespace crunch
{
    template<class T>
    class Matrix3;

    /**
     * @brief A Quaternion class.
     *
     * http://en.wikipedia.org/wiki/Quaternion
     *
     * Quaternions are useful to compactly express 3D orientations.
     * Furthermore Quaternions allow you to seamlessly interpolate between
     * each other.
     *
     * @arg T The value type of the Quaternion (i.e. stick::Float32)
     */
    template<class T>
    class Quaternion
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief The individual values of the quaternion.
         */
        ValueType x, y, z, w;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Quaternion();

        /**
         * @brief Constructs a quaternion from the provided values.
         */
        inline Quaternion(T _x, T _y, T _z, T _w);

        /**
         * @brief Constructs a quaternion from an existing one.
         */
        inline Quaternion(const Quaternion & _other);

        /**
         * @brief Constructs a quaternion from a 4D vector.
         */
        inline Quaternion(const Vector4<T> & _vec);

        /**
         * @brief Constructs a quaternion from a 3D vector and a w component.
         */
        inline Quaternion(const Vector3<T> & _vec, T _w);

        /**
         * @brief Constructs a quaternion from a 3D rotation matrix.
         */
        inline Quaternion(const Matrix3<T> & _mat);

        /**
         * @brief Assign another quaternion to this.
         */
        inline Quaternion<T> & operator = (const Quaternion<T> & _other);

        /**
         * @brief Returns true if this quaternion and the provided quaternion are identical.
         */
        inline bool operator == (const Quaternion<T> & _quat) const;

        /**
         * @brief Returns false if this quaternion and the provided quaternion are identical.
         */
        inline bool operator != (const Quaternion<T> & _quat) const;

        /**
         * @brief Access an element of the quaternion by index.
         *
         * WARNING: This does not bounds check.
         *
         * @param _index The index.
         * @return A reference to the element.
         */
        inline T & operator [](stick::UInt32 _index);

        /**
         * @brief Access an element of the quaternion by index.
         *
         * WARNING: This does not bounds check.
         *
         * @param _index The index.
         * @return A const reference to the element.
         */
        inline const T & operator [](stick::UInt32 _index) const;

        /**
         * @brief Adds two quaternions.
         */
        inline Quaternion<T> operator + (const Quaternion<T> & _quat) const;

        /**
         * @brief Subtracts two quaternions.
         */
        inline Quaternion<T> operator - (const Quaternion<T> & _quat) const;

        /**
         * @brief Multiplies a quaternion with this quaternion.
         *
         * Quaternion multiplication is noncommutative.
         *
         * @return The resulting quaternion.
         */
        inline Quaternion<T> operator * (const Quaternion<T> & _quat) const;

        /**
         * @brief Multiplies a 3D vector with this quaternion.
         * @return The resulting vector.
         */
        inline Vector3<T> operator * (const Vector3<T> & _vec) const;

        //remove this?
        inline const Quaternion<T> & operator + () const;

        /**
         * @brief Returns the negated version of this quaternion.
         */
        inline Quaternion<T> operator - () const;

        /**
         * @brief Subtracts a quaternion from this quaternion.
         */
        inline Quaternion<T> & operator -= (const Quaternion<T> & _quat);

        /**
         * @brief Adds a quaternion to this quaternion.
         */
        inline Quaternion<T> & operator += (const Quaternion<T> & _quat);

        /**
         * @brief Multiplies a quaternion with this quaternion.
         */
        inline Quaternion<T> & operator *= (const Quaternion<T> & _quat);

        /**
         * @brief Devides all elements of the quaternion by the provided number.
         * @return The resulting quaternion.
         */
        inline Quaternion<T> operator / (T _val) const;

        /**
         * @brief Multiplies all elements of the quaternion by the provided number.
         * @return The resulting quaternion.
         */
        inline Quaternion<T> operator * (T _val) const;

        /**
         * @brief Adds a number to all elements of the quaternion.
         * @return The resulting quaternion.
         */
        inline Quaternion<T> operator + (T _val) const;

        /**
         * @brief Subtracts a number from all elements of the quaternion.
         * @return The resulting quaternion.
         */
        inline Quaternion<T> operator - (T _val) const;

        /**
         * @brief Devides all elements of this quaterntion by a number.
         */
        inline Quaternion<T> & operator /= (T _val);

        /**
         * @brief Multiplies all elements of this quaterntion by a number.
         */
        inline Quaternion<T> & operator *= (T _val);

        /**
         * @brief Adds a number to all elements of this quaterntion.
         */
        inline Quaternion<T> & operator += (T _val);

        /**
         * @brief Subtracts a number from all the elements of this quaterntion.
         */
        inline Quaternion<T> & operator -= (T _val);

        /**
         * @brief Returns a pointer to the memory block of this quaternion.
         */
        inline T * ptr();

        /**
         * @brief Returns a pointer to the memory block of this quaternion.
         */
        inline const T * ptr() const;

        /**
         * @brief Returns an identity quaternion.
         */
        inline static Quaternion<T> identity();

        /**
         * @brief Creates a quaternion from an angle in radians and a rotation axis.
         * @param _radians The rotation angle in radians.
         * @param _axis The rotation axis.
         */
        inline static Quaternion<T> rotation(T _radians, const Vector3<T> & _axis);

        /**
         * @brief Returns a quaternion from euler angles.
         * @param _yaw Angle in radians.
         * @param _pitch Angle in radians.
         * @param _roll Angle in radians.
         */
        inline static Quaternion<T> rotation(T _yaw, T _pitch, T _roll);

        /**
         * @brief Returns a quaternion from euler angles.
         * @param _euler Vector holding the euler angles in radians.
         */
        inline static Quaternion<T> rotation(const Vector3<T> & _angles);

        /**
         * @brief Returns a quaternion from a 3x3 rotation matrix.
         * @param _mat A rotation matrix.
         */
        inline static Quaternion<T> rotation(const Matrix3<T> & _mat);

        //These swizzle operators are automatically generated by swizzleGenerator.py

        //Getters

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxxx() const { return Quaternion<T>(x, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxxy() const { return Quaternion<T>(x, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxxz() const { return Quaternion<T>(x, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxxw() const { return Quaternion<T>(x, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxyx() const { return Quaternion<T>(x, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxyy() const { return Quaternion<T>(x, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxyz() const { return Quaternion<T>(x, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxyw() const { return Quaternion<T>(x, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxzx() const { return Quaternion<T>(x, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxzy() const { return Quaternion<T>(x, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxzz() const { return Quaternion<T>(x, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxzw() const { return Quaternion<T>(x, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxwx() const { return Quaternion<T>(x, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxwy() const { return Quaternion<T>(x, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxwz() const { return Quaternion<T>(x, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xxww() const { return Quaternion<T>(x, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyxx() const { return Quaternion<T>(x, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyxy() const { return Quaternion<T>(x, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyxz() const { return Quaternion<T>(x, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyxw() const { return Quaternion<T>(x, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyyx() const { return Quaternion<T>(x, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyyy() const { return Quaternion<T>(x, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyyz() const { return Quaternion<T>(x, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyyw() const { return Quaternion<T>(x, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyzx() const { return Quaternion<T>(x, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyzy() const { return Quaternion<T>(x, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyzz() const { return Quaternion<T>(x, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyzw() const { return Quaternion<T>(x, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xywx() const { return Quaternion<T>(x, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xywy() const { return Quaternion<T>(x, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xywz() const { return Quaternion<T>(x, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xyww() const { return Quaternion<T>(x, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzxx() const { return Quaternion<T>(x, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzxy() const { return Quaternion<T>(x, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzxz() const { return Quaternion<T>(x, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzxw() const { return Quaternion<T>(x, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzyx() const { return Quaternion<T>(x, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzyy() const { return Quaternion<T>(x, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzyz() const { return Quaternion<T>(x, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzyw() const { return Quaternion<T>(x, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzzx() const { return Quaternion<T>(x, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzzy() const { return Quaternion<T>(x, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzzz() const { return Quaternion<T>(x, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzzw() const { return Quaternion<T>(x, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzwx() const { return Quaternion<T>(x, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzwy() const { return Quaternion<T>(x, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzwz() const { return Quaternion<T>(x, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xzww() const { return Quaternion<T>(x, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwxx() const { return Quaternion<T>(x, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwxy() const { return Quaternion<T>(x, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwxz() const { return Quaternion<T>(x, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwxw() const { return Quaternion<T>(x, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwyx() const { return Quaternion<T>(x, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwyy() const { return Quaternion<T>(x, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwyz() const { return Quaternion<T>(x, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwyw() const { return Quaternion<T>(x, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwzx() const { return Quaternion<T>(x, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwzy() const { return Quaternion<T>(x, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwzz() const { return Quaternion<T>(x, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwzw() const { return Quaternion<T>(x, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwwx() const { return Quaternion<T>(x, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwwy() const { return Quaternion<T>(x, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwwz() const { return Quaternion<T>(x, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> xwww() const { return Quaternion<T>(x, w, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxxx() const { return Quaternion<T>(y, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxxy() const { return Quaternion<T>(y, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxxz() const { return Quaternion<T>(y, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxxw() const { return Quaternion<T>(y, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxyx() const { return Quaternion<T>(y, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxyy() const { return Quaternion<T>(y, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxyz() const { return Quaternion<T>(y, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxyw() const { return Quaternion<T>(y, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxzx() const { return Quaternion<T>(y, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxzy() const { return Quaternion<T>(y, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxzz() const { return Quaternion<T>(y, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxzw() const { return Quaternion<T>(y, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxwx() const { return Quaternion<T>(y, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxwy() const { return Quaternion<T>(y, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxwz() const { return Quaternion<T>(y, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yxww() const { return Quaternion<T>(y, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyxx() const { return Quaternion<T>(y, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyxy() const { return Quaternion<T>(y, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyxz() const { return Quaternion<T>(y, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyxw() const { return Quaternion<T>(y, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyyx() const { return Quaternion<T>(y, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyyy() const { return Quaternion<T>(y, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyyz() const { return Quaternion<T>(y, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyyw() const { return Quaternion<T>(y, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyzx() const { return Quaternion<T>(y, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyzy() const { return Quaternion<T>(y, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyzz() const { return Quaternion<T>(y, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyzw() const { return Quaternion<T>(y, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yywx() const { return Quaternion<T>(y, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yywy() const { return Quaternion<T>(y, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yywz() const { return Quaternion<T>(y, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yyww() const { return Quaternion<T>(y, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzxx() const { return Quaternion<T>(y, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzxy() const { return Quaternion<T>(y, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzxz() const { return Quaternion<T>(y, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzxw() const { return Quaternion<T>(y, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzyx() const { return Quaternion<T>(y, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzyy() const { return Quaternion<T>(y, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzyz() const { return Quaternion<T>(y, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzyw() const { return Quaternion<T>(y, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzzx() const { return Quaternion<T>(y, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzzy() const { return Quaternion<T>(y, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzzz() const { return Quaternion<T>(y, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzzw() const { return Quaternion<T>(y, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzwx() const { return Quaternion<T>(y, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzwy() const { return Quaternion<T>(y, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzwz() const { return Quaternion<T>(y, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> yzww() const { return Quaternion<T>(y, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywxx() const { return Quaternion<T>(y, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywxy() const { return Quaternion<T>(y, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywxz() const { return Quaternion<T>(y, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywxw() const { return Quaternion<T>(y, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywyx() const { return Quaternion<T>(y, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywyy() const { return Quaternion<T>(y, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywyz() const { return Quaternion<T>(y, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywyw() const { return Quaternion<T>(y, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywzx() const { return Quaternion<T>(y, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywzy() const { return Quaternion<T>(y, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywzz() const { return Quaternion<T>(y, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywzw() const { return Quaternion<T>(y, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywwx() const { return Quaternion<T>(y, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywwy() const { return Quaternion<T>(y, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywwz() const { return Quaternion<T>(y, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> ywww() const { return Quaternion<T>(y, w, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxxx() const { return Quaternion<T>(z, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxxy() const { return Quaternion<T>(z, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxxz() const { return Quaternion<T>(z, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxxw() const { return Quaternion<T>(z, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxyx() const { return Quaternion<T>(z, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxyy() const { return Quaternion<T>(z, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxyz() const { return Quaternion<T>(z, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxyw() const { return Quaternion<T>(z, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxzx() const { return Quaternion<T>(z, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxzy() const { return Quaternion<T>(z, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxzz() const { return Quaternion<T>(z, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxzw() const { return Quaternion<T>(z, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxwx() const { return Quaternion<T>(z, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxwy() const { return Quaternion<T>(z, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxwz() const { return Quaternion<T>(z, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zxww() const { return Quaternion<T>(z, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyxx() const { return Quaternion<T>(z, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyxy() const { return Quaternion<T>(z, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyxz() const { return Quaternion<T>(z, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyxw() const { return Quaternion<T>(z, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyyx() const { return Quaternion<T>(z, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyyy() const { return Quaternion<T>(z, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyyz() const { return Quaternion<T>(z, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyyw() const { return Quaternion<T>(z, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyzx() const { return Quaternion<T>(z, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyzy() const { return Quaternion<T>(z, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyzz() const { return Quaternion<T>(z, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyzw() const { return Quaternion<T>(z, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zywx() const { return Quaternion<T>(z, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zywy() const { return Quaternion<T>(z, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zywz() const { return Quaternion<T>(z, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zyww() const { return Quaternion<T>(z, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzxx() const { return Quaternion<T>(z, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzxy() const { return Quaternion<T>(z, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzxz() const { return Quaternion<T>(z, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzxw() const { return Quaternion<T>(z, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzyx() const { return Quaternion<T>(z, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzyy() const { return Quaternion<T>(z, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzyz() const { return Quaternion<T>(z, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzyw() const { return Quaternion<T>(z, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzzx() const { return Quaternion<T>(z, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzzy() const { return Quaternion<T>(z, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzzz() const { return Quaternion<T>(z, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzzw() const { return Quaternion<T>(z, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzwx() const { return Quaternion<T>(z, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzwy() const { return Quaternion<T>(z, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzwz() const { return Quaternion<T>(z, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zzww() const { return Quaternion<T>(z, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwxx() const { return Quaternion<T>(z, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwxy() const { return Quaternion<T>(z, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwxz() const { return Quaternion<T>(z, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwxw() const { return Quaternion<T>(z, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwyx() const { return Quaternion<T>(z, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwyy() const { return Quaternion<T>(z, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwyz() const { return Quaternion<T>(z, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwyw() const { return Quaternion<T>(z, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwzx() const { return Quaternion<T>(z, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwzy() const { return Quaternion<T>(z, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwzz() const { return Quaternion<T>(z, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwzw() const { return Quaternion<T>(z, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwwx() const { return Quaternion<T>(z, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwwy() const { return Quaternion<T>(z, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwwz() const { return Quaternion<T>(z, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> zwww() const { return Quaternion<T>(z, w, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxxx() const { return Quaternion<T>(w, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxxy() const { return Quaternion<T>(w, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxxz() const { return Quaternion<T>(w, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxxw() const { return Quaternion<T>(w, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxyx() const { return Quaternion<T>(w, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxyy() const { return Quaternion<T>(w, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxyz() const { return Quaternion<T>(w, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxyw() const { return Quaternion<T>(w, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxzx() const { return Quaternion<T>(w, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxzy() const { return Quaternion<T>(w, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxzz() const { return Quaternion<T>(w, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxzw() const { return Quaternion<T>(w, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxwx() const { return Quaternion<T>(w, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxwy() const { return Quaternion<T>(w, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxwz() const { return Quaternion<T>(w, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wxww() const { return Quaternion<T>(w, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyxx() const { return Quaternion<T>(w, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyxy() const { return Quaternion<T>(w, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyxz() const { return Quaternion<T>(w, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyxw() const { return Quaternion<T>(w, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyyx() const { return Quaternion<T>(w, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyyy() const { return Quaternion<T>(w, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyyz() const { return Quaternion<T>(w, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyyw() const { return Quaternion<T>(w, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyzx() const { return Quaternion<T>(w, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyzy() const { return Quaternion<T>(w, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyzz() const { return Quaternion<T>(w, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyzw() const { return Quaternion<T>(w, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wywx() const { return Quaternion<T>(w, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wywy() const { return Quaternion<T>(w, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wywz() const { return Quaternion<T>(w, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wyww() const { return Quaternion<T>(w, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzxx() const { return Quaternion<T>(w, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzxy() const { return Quaternion<T>(w, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzxz() const { return Quaternion<T>(w, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzxw() const { return Quaternion<T>(w, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzyx() const { return Quaternion<T>(w, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzyy() const { return Quaternion<T>(w, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzyz() const { return Quaternion<T>(w, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzyw() const { return Quaternion<T>(w, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzzx() const { return Quaternion<T>(w, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzzy() const { return Quaternion<T>(w, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzzz() const { return Quaternion<T>(w, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzzw() const { return Quaternion<T>(w, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzwx() const { return Quaternion<T>(w, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzwy() const { return Quaternion<T>(w, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzwz() const { return Quaternion<T>(w, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wzww() const { return Quaternion<T>(w, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwxx() const { return Quaternion<T>(w, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwxy() const { return Quaternion<T>(w, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwxz() const { return Quaternion<T>(w, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwxw() const { return Quaternion<T>(w, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwyx() const { return Quaternion<T>(w, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwyy() const { return Quaternion<T>(w, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwyz() const { return Quaternion<T>(w, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwyw() const { return Quaternion<T>(w, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwzx() const { return Quaternion<T>(w, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwzy() const { return Quaternion<T>(w, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwzz() const { return Quaternion<T>(w, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwzw() const { return Quaternion<T>(w, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwwx() const { return Quaternion<T>(w, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwwy() const { return Quaternion<T>(w, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwwz() const { return Quaternion<T>(w, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Quaternion.
         */
        inline Quaternion<T> wwww() const { return Quaternion<T>(w, w, w, w); }

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
        inline Vector3<T> xxw() const { return Vector3<T>(x, x, w); }

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
        inline Vector3<T> xyw() const { return Vector3<T>(x, y, w); }

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
        inline Vector3<T> xzw() const { return Vector3<T>(x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xwx() const { return Vector3<T>(x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xwy() const { return Vector3<T>(x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xwz() const { return Vector3<T>(x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> xww() const { return Vector3<T>(x, w, w); }

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
        inline Vector3<T> yxw() const { return Vector3<T>(y, x, w); }

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
        inline Vector3<T> yyw() const { return Vector3<T>(y, y, w); }

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
        inline Vector3<T> yzw() const { return Vector3<T>(y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> ywx() const { return Vector3<T>(y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> ywy() const { return Vector3<T>(y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> ywz() const { return Vector3<T>(y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> yww() const { return Vector3<T>(y, w, w); }

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
        inline Vector3<T> zxw() const { return Vector3<T>(z, x, w); }

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
        inline Vector3<T> zyw() const { return Vector3<T>(z, y, w); }

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
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zzw() const { return Vector3<T>(z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zwx() const { return Vector3<T>(z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zwy() const { return Vector3<T>(z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zwz() const { return Vector3<T>(z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> zww() const { return Vector3<T>(z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wxx() const { return Vector3<T>(w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wxy() const { return Vector3<T>(w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wxz() const { return Vector3<T>(w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wxw() const { return Vector3<T>(w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wyx() const { return Vector3<T>(w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wyy() const { return Vector3<T>(w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wyz() const { return Vector3<T>(w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wyw() const { return Vector3<T>(w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wzx() const { return Vector3<T>(w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wzy() const { return Vector3<T>(w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wzz() const { return Vector3<T>(w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wzw() const { return Vector3<T>(w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wwx() const { return Vector3<T>(w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wwy() const { return Vector3<T>(w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> wwz() const { return Vector3<T>(w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector3.
         */
        inline Vector3<T> www() const { return Vector3<T>(w, w, w); }

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
        inline Vector2<T> xw() const { return Vector2<T>(x, w); }

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
        inline Vector2<T> yw() const { return Vector2<T>(y, w); }

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

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> zw() const { return Vector2<T>(z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> wx() const { return Vector2<T>(w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> wy() const { return Vector2<T>(w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> wz() const { return Vector2<T>(w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector2.
         */
        inline Vector2<T> ww() const { return Vector2<T>(w, w); }

        //Setters

        /**
         * @brief Swizzle setter function.
         */
        inline void xyzw(const Quaternion<T> & _quat) { x = _quat.x; y = _quat.y; z = _quat.z; w = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xywz(const Quaternion<T> & _quat) { x = _quat.x; y = _quat.y; w = _quat.z; z = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzyw(const Quaternion<T> & _quat) { x = _quat.x; z = _quat.y; y = _quat.z; w = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzwy(const Quaternion<T> & _quat) { x = _quat.x; z = _quat.y; w = _quat.z; y = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xwyz(const Quaternion<T> & _quat) { x = _quat.x; w = _quat.y; y = _quat.z; z = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xwzy(const Quaternion<T> & _quat) { x = _quat.x; w = _quat.y; z = _quat.z; y = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxzw(const Quaternion<T> & _quat) { y = _quat.x; x = _quat.y; z = _quat.z; w = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxwz(const Quaternion<T> & _quat) { y = _quat.x; x = _quat.y; w = _quat.z; z = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzxw(const Quaternion<T> & _quat) { y = _quat.x; z = _quat.y; x = _quat.z; w = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzwx(const Quaternion<T> & _quat) { y = _quat.x; z = _quat.y; w = _quat.z; x = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void ywxz(const Quaternion<T> & _quat) { y = _quat.x; w = _quat.y; x = _quat.z; z = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void ywzx(const Quaternion<T> & _quat) { y = _quat.x; w = _quat.y; z = _quat.z; x = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxyw(const Quaternion<T> & _quat) { z = _quat.x; x = _quat.y; y = _quat.z; w = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxwy(const Quaternion<T> & _quat) { z = _quat.x; x = _quat.y; w = _quat.z; y = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zyxw(const Quaternion<T> & _quat) { z = _quat.x; y = _quat.y; x = _quat.z; w = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zywx(const Quaternion<T> & _quat) { z = _quat.x; y = _quat.y; w = _quat.z; x = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zwxy(const Quaternion<T> & _quat) { z = _quat.x; w = _quat.y; x = _quat.z; y = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zwyx(const Quaternion<T> & _quat) { z = _quat.x; w = _quat.y; y = _quat.z; x = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wxyz(const Quaternion<T> & _quat) { w = _quat.x; x = _quat.y; y = _quat.z; z = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wxzy(const Quaternion<T> & _quat) { w = _quat.x; x = _quat.y; z = _quat.z; y = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wyxz(const Quaternion<T> & _quat) { w = _quat.x; y = _quat.y; x = _quat.z; z = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wyzx(const Quaternion<T> & _quat) { w = _quat.x; y = _quat.y; z = _quat.z; x = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wzxy(const Quaternion<T> & _quat) { w = _quat.x; z = _quat.y; x = _quat.z; y = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wzyx(const Quaternion<T> & _quat) { w = _quat.x; z = _quat.y; y = _quat.z; x = _quat.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xyz(const Vector3<T> & _vec) { x = _vec.x; y = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xyw(const Vector3<T> & _vec) { x = _vec.x; y = _vec.y; w = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzy(const Vector3<T> & _vec) { x = _vec.x; z = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzw(const Vector3<T> & _vec) { x = _vec.x; z = _vec.y; w = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xwy(const Vector3<T> & _vec) { x = _vec.x; w = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xwz(const Vector3<T> & _vec) { x = _vec.x; w = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxz(const Vector3<T> & _vec) { y = _vec.x; x = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxw(const Vector3<T> & _vec) { y = _vec.x; x = _vec.y; w = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzx(const Vector3<T> & _vec) { y = _vec.x; z = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzw(const Vector3<T> & _vec) { y = _vec.x; z = _vec.y; w = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void ywx(const Vector3<T> & _vec) { y = _vec.x; w = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void ywz(const Vector3<T> & _vec) { y = _vec.x; w = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxy(const Vector3<T> & _vec) { z = _vec.x; x = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxw(const Vector3<T> & _vec) { z = _vec.x; x = _vec.y; w = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zyx(const Vector3<T> & _vec) { z = _vec.x; y = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zyw(const Vector3<T> & _vec) { z = _vec.x; y = _vec.y; w = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zwx(const Vector3<T> & _vec) { z = _vec.x; w = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zwy(const Vector3<T> & _vec) { z = _vec.x; w = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wxy(const Vector3<T> & _vec) { w = _vec.x; x = _vec.y; y = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wxz(const Vector3<T> & _vec) { w = _vec.x; x = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wyx(const Vector3<T> & _vec) { w = _vec.x; y = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wyz(const Vector3<T> & _vec) { w = _vec.x; y = _vec.y; z = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wzx(const Vector3<T> & _vec) { w = _vec.x; z = _vec.y; x = _vec.z; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wzy(const Vector3<T> & _vec) { w = _vec.x; z = _vec.y; y = _vec.z; }

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
        inline void xw(const Vector2<T> & _vec) { x = _vec.x; w = _vec.y; }

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
        inline void yw(const Vector2<T> & _vec) { y = _vec.x; w = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zx(const Vector2<T> & _vec) { z = _vec.x; x = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zy(const Vector2<T> & _vec) { z = _vec.x; y = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zw(const Vector2<T> & _vec) { z = _vec.x; w = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wx(const Vector2<T> & _vec) { w = _vec.x; x = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wy(const Vector2<T> & _vec) { w = _vec.x; y = _vec.y; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wz(const Vector2<T> & _vec) { w = _vec.x; z = _vec.y; }

        //swizzleGenerator.py end
    };
}

#include <Crunch/Matrix3.hpp>

namespace crunch
{
    template<class T>
    inline Quaternion<T>::Quaternion()
    {}

    template<class T>
    inline Quaternion<T>::Quaternion(T _w, T _x, T _y, T _z) :
        w(_w),
        x(_x),
        y(_y),
        z(_z)
    {
    }

    template<class T>
    inline Quaternion<T>::Quaternion(const Quaternion & _other) :
        x(_other.x),
        y(_other.y),
        z(_other.z),
        w(_other.w)
    {
    }

    template<class T>
    inline Quaternion<T>::Quaternion(const Vector4<T> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(_vec.z),
        w(_vec.w)
    {
    }

    template<class T>
    inline Quaternion<T>::Quaternion(const Vector3<T> & _vec, T _w) :
        x(_vec.x),
        y(_vec.y),
        z(_vec.z),
        w(_w)
    {
    }

    template<class T>
    inline Quaternion<T>::Quaternion(const Matrix3<T> & _mat)
    {
        *this = rotation(_mat);
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator = (const Quaternion<T> & _other)
    {
        x = _other.x;
        y = _other.y;
        z = _other.z;
        w = _other.w;
        return *this;
    }

    // Boolean
    //____________________________________

    template<class T>
    inline bool Quaternion<T>::operator == (const Quaternion<T> & _quat) const
    {
        if (x == _quat.x && y == _quat.y && z == _quat.z && w == _quat.w)
            return true;
        else
            return false;
    }

    template<class T>
    inline bool Quaternion<T>::operator != (const Quaternion<T> & _quat) const
    {
        if (x == _quat.x && y == _quat.y && z == _quat.z && w == _quat.w)
            return false;
        else
            return true;
    }

    // Access
    //____________________________________

    template<class T>
    inline T & Quaternion<T>::operator [](stick::UInt32 _index)
    {
        return *(&x + _index);
    }

    template<class T>
    inline const T & Quaternion<T>::operator [](stick::UInt32 _index) const
    {
        return *(&x + _index);
    }

    // Arithmetic operations
    //____________________________________

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator + (const Quaternion<T> & _quat) const
    {
        Quaternion<T> quat;
        quat.x = x + _quat.x;
        quat.y = y + _quat.y;
        quat.z = z + _quat.z;
        quat.w = w + _quat.w;
        return quat;
    }

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator - (const Quaternion<T> & _quat) const
    {
        Quaternion<T> quat;
        quat.x = x - _quat.x;
        quat.y = y - _quat.y;
        quat.z = z - _quat.z;
        quat.w = w - _quat.w;
        return quat;
    }

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator * (const Quaternion<T> & _quat) const
    {
        Quaternion<T> quat;

        quat.w = w * _quat.w - x * _quat.x - y * _quat.y - z * _quat.z;
        quat.x = w * _quat.x + x * _quat.w + y * _quat.z - z * _quat.y;
        quat.y = w * _quat.y + y * _quat.w + z * _quat.x - x * _quat.z;
        quat.z = w * _quat.z + z * _quat.w + x * _quat.y - y * _quat.x;

        return quat;
    }

    template<class T>
    inline Vector3<T> Quaternion<T>::operator * (const Vector3<T> & _vec) const
    {
        // nVidia SDK implementation
        Vector3<T> qvec(x, y, z);
        Vector3<T> uv, uuv;
        uv = cross(qvec, _vec);
        uuv = cross(qvec, uv);
        uv = uv * ((T)2.0 * w);
        uuv = uuv * (T)2.0;

        return _vec + uv + uuv;
    }

    template<class T>
    inline const Quaternion<T> & Quaternion<T>::operator + () const
    {
        return *this;
    }

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator - () const
    {
        return Quaternion<T>(-x, -y, -z, -w);
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator -= (const Quaternion<T> & _quat)
    {
        x -= _quat.x;
        y -= _quat.y;
        z -= _quat.z;
        w -= _quat.w;
        return *this;
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator += (const Quaternion<T> & _quat)
    {
        x += _quat.x;
        y += _quat.y;
        z += _quat.z;
        w += _quat.w;
        return *this;
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator *= (const Quaternion<T> & _quat)
    {
        w = w * _quat.w - x * _quat.x - y * _quat.y - z * _quat.z;
        x = w * _quat.x + x * _quat.w + y * _quat.z - z * _quat.y;
        y = w * _quat.y + y * _quat.w + z * _quat.x - x * _quat.z;
        z = w * _quat.z + z * _quat.w + x * _quat.y - y * _quat.x;
        return *this;
    }

    // Real Arithmetic
    //____________________________________

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator / (T _val) const
    {
        Quaternion<T> vec;
        vec.x = x / _val;
        vec.y = y / _val;
        vec.z = z / _val;
        vec.w = w / _val;
        return vec;
    }

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator * (T _val) const
    {
        Quaternion<T> vec;
        vec.x = x * _val;
        vec.y = y * _val;
        vec.z = z * _val;
        vec.w = w * _val;
        return vec;
    }

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator + (T _val) const
    {
        Vector4<T> vec;
        vec.x = x + _val;
        vec.y = y + _val;
        vec.z = z + _val;
        vec.w = w + _val;
        return vec;
    }

    template<class T>
    inline Quaternion<T> Quaternion<T>::operator - (T _val) const
    {
        Vector4<T> vec;
        vec.x = x - _val;
        vec.y = y - _val;
        vec.z = z - _val;
        vec.w = w - _val;
        return vec;
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator /= (T _val)
    {
        x /= _val;
        y /= _val;
        z /= _val;
        w /= _val;
        return *this;
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator *= (T _val)
    {
        x *= _val;
        y *= _val;
        z *= _val;
        w *= _val;
        return *this;
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator += (T _val)
    {
        x += _val;
        y += _val;
        z += _val;
        w += _val;
        return *this;
    }

    template<class T>
    inline Quaternion<T> & Quaternion<T>::operator -= (T _val)
    {
        x -= _val;
        y -= _val;
        z -= _val;
        w -= _val;
        return *this;
    }


    //Pointer accessors
    //____________________________________

    template<class T>
    inline T * Quaternion<T>::ptr()
    {
        return &x;
    }

    template<class T>
    inline const T * Quaternion<T>::ptr() const
    {
        return &x;
    }


    //Static helper functions
    //____________________________________

    template<class T>
    inline Quaternion<T> Quaternion<T>::identity()
    {
        return Quaternion<T>(0.0, 0.0, 0.0, 1.0);
    }

    template<class T>
    Quaternion<T> Quaternion<T>::rotation(T _radians, const Vector3<T> & _axis)
    {
        Quaternion<T> ret;

        Vector3<T> ax = _axis;

        T halfAngle = (T)0.5 * _radians;
        T sinAngle = std::sin(halfAngle);
        ret.w = std::cos(halfAngle);
        ret.x = sinAngle * ax.x;
        ret.y = sinAngle * ax.y;
        ret.z = sinAngle * ax.z;

        return ret;
    }

    // angles in radians
    template<class T>
    Quaternion<T> Quaternion<T>::rotation(T _yaw, T _pitch, T _roll)
    {
        Quaternion<T> ret;

        T c1 = std::cos(_yaw);
        T s1 = std::sin(_yaw);
        T c2 = std::cos(_pitch);
        T s2 = std::sin(_pitch);
        T c3 = std::cos(_roll);
        T s3 = std::sin(_roll);
        ret.w = sqrt((T)1.0 + c1 * c2 + c1 * c3 - s1 * s2 * s3 + c2 * c3) / (T)2.0;
        T w4 = (T)(4.0 * ret.w);
        ret.x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
        ret.y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
        ret.z = (-s1 * s3 + c1 * s2 * c3 + s2) / w4 ;

        return ret;
    }

    template<class T>
    Quaternion<T> Quaternion<T>::rotation(const Vector3<T> & _euler)
    {
        return rotation(_euler.x, _euler.y, _euler.z);
    }

    template<class T>
    Quaternion<T> Quaternion<T>::rotation(const Matrix3<T> & _mat)
    {
        Quaternion<T> ret;

        T tr = _mat.element(0, 0) + _mat.element(1, 1) + _mat.element(2, 2);

        if (tr > (T)0.0)
        {
            T root = (T)0.5 / sqrt((T)(tr + 1.0));
            ret.w = (T)0.25 / root;
            ret.x = (_mat.element(1, 2) - _mat.element(2, 1)) * root;
            ret.y = (_mat.element(2, 0) - _mat.element(0, 2)) * root;
            ret.z = (_mat.element(0, 1) - _mat.element(1, 0)) * root;
        }
        else
        {
            T tr1 = (T)1.0 + _mat.element(0, 0) - _mat.element(1, 1) - _mat.element(2, 2);
            T tr2 = (T)1.0 - _mat.element(0, 0) + _mat.element(1, 1) - _mat.element(2, 2);
            T tr3 = (T)1.0 - _mat.element(0, 0) - _mat.element(1, 1) + _mat.element(2, 2);

            if (_mat.element(0, 0) > _mat.element(1, 1) && _mat.element(1, 1) > _mat.element(1, 1))
            {
                T S = sqrt(tr1) * (T)2.0; // S=4*qx
                ret.w = (_mat.element(1, 2) - _mat.element(2, 1)) / S;
                ret.x = (T)0.25 * S;
                ret.y = (_mat.element(1, 0) + _mat.element(0, 1)) / S;
                ret.z = (_mat.element(2, 0) + _mat.element(0, 2)) / S;
            }
            else if (_mat.element(1, 1) > _mat.element(2, 2))
            {
                T S = sqrt(tr2) * (T)2.0; // S=4*qy
                ret.w = (_mat.element(2, 0) - _mat.element(0, 2)) / S;
                ret.x = (_mat.element(1, 0) + _mat.element(0, 1)) / S;
                ret.y = (T)0.25 * S;
                ret.z = (_mat.element(2, 1) + _mat.element(1, 2)) / S;
            }
            else
            {
                T S = sqrt(tr3) * (T)2.0; // S=4*qz
                ret.w = (_mat.element(0, 1) - _mat.element(1, 0)) / S;
                ret.x = (_mat.element(0, 2) + _mat.element(2, 0)) / S;
                ret.y = (_mat.element(2, 1) + _mat.element(1, 2)) / S;
                ret.z = (T)0.25 * S;
            }
        }

        return ret;
    }
}

#endif //CRUNCH_QUATERNION_HPP
