#ifndef CRUNCH_VECTOR4_HPP
#define CRUNCH_VECTOR4_HPP

#include <Crunch/Vector3.hpp>

namespace crunch
{
    /**
     * @brief A 4D vector class.
     * @arg T The internal value type (i.e. stick::Float32)
     */
    template<class T>
    class Vector4
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief The individual values of the vector.
         */
        ValueType x, y, z, w;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Vector4();

        /**
         * @brief Constructs a vector setting its elements to the provided number.
         */
        explicit inline Vector4(T _val);

        /**
         * @brief Constructs a vector setting its elements to the provided numbers.
         */
        inline Vector4(T _x, T _y, T _z, T _w);

        /**
         * @brief Constructs a vector from another vector.
         */
        template<class OT>
        inline Vector4(const Vector4<OT> & _vec);

        /**
         * @brief Constructs a 4D vector from a 3D vector.
         * This will set the w element to 1.0.
         */
        template<class OT>
        inline Vector4(const Vector3<OT> & _vec);

        /**
         * @brief Constructs a 4D vector from a 2D vector.
         * This will set the z element to 0 and the w element to 1.0.
         */
        template<class OT>
        inline Vector4(const Vector2<OT> & _vec);

        /**
         * @brief Assigns another vector to this.
         */
        inline Vector4<T> & operator = (const Vector4<T> & _other);

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
        inline bool operator == (const Vector4<T> & _vec) const;

        /**
         * @brief Returns true if this vector and the provided vector are not identical.
         */
        inline bool operator != (const Vector4<T> & _vec) const;

        /**
         * @brief Adds two vectors.
         */
        inline Vector4<T> operator + (const Vector4<T> & _vec) const;

        /**
         * @brief Subtracts two vectors.
         */
        inline Vector4<T> operator - (const Vector4<T> & _vec) const;

        /**
         * @brief Multiplies two vectors.
         */
        inline Vector4<T> operator * (const Vector4<T> & _vec) const;

        /**
         * @brief Devides one vector by another.
         */
        inline Vector4<T> operator / (const Vector4<T> & _vec) const;

        //remove this?
        inline const Vector4<T> & operator + () const;

        /**
         * @brief Negates this vector.
         */
        inline Vector4<T> operator - () const;

        /**
         * @brief Subtracts another vector from this vector.
         */
        inline Vector4<T> & operator -= (const Vector4<T> & _vec);

        /**
         * @brief Adds another vector to this vector.
         */
        inline Vector4<T> & operator += (const Vector4<T> & _vec);

        /**
         * @brief Multiplies this vector by another vector.
         */
        inline Vector4<T> & operator *= (const Vector4<T> & _vec);

        /**
         * @brief Devides this vector by another vector.
         */
        inline Vector4<T> & operator /= (const Vector4<T> & _vec);

        /**
         * @brief Devides a vector by a number.
         */
        inline Vector4<T> operator / (T _val) const;

        /**
         * @brief Multiplies a vector by a number.
         */
        inline Vector4<T> operator * (T _val) const;

        /**
         * @brief Adds a number to a vector.
         */
        inline Vector4<T> operator + (T _val) const;

        /**
         * @brief Subtracts a number from a vector.
         */
        inline Vector4<T> operator - (T _val) const;

        /**
         * @brief Devides this vector by a number.
         */
        inline Vector4<T> & operator /= (T _val);

        /**
         * @brief Multiplies this vector by a number.
         */
        inline Vector4<T> & operator *= (T _val);

        /**
         * @brief Adds a number to this vector.
         */
        inline Vector4<T> & operator += (T _val);

        /**
         * @brief Subtracts a number from this vector.
         */
        inline Vector4<T> & operator -= (T _val);

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
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxxx() const { return Vector4<T>(x, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxxy() const { return Vector4<T>(x, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxxz() const { return Vector4<T>(x, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxxw() const { return Vector4<T>(x, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxyx() const { return Vector4<T>(x, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxyy() const { return Vector4<T>(x, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxyz() const { return Vector4<T>(x, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxyw() const { return Vector4<T>(x, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxzx() const { return Vector4<T>(x, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxzy() const { return Vector4<T>(x, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxzz() const { return Vector4<T>(x, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxzw() const { return Vector4<T>(x, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxwx() const { return Vector4<T>(x, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxwy() const { return Vector4<T>(x, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxwz() const { return Vector4<T>(x, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xxww() const { return Vector4<T>(x, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyxx() const { return Vector4<T>(x, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyxy() const { return Vector4<T>(x, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyxz() const { return Vector4<T>(x, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyxw() const { return Vector4<T>(x, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyyx() const { return Vector4<T>(x, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyyy() const { return Vector4<T>(x, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyyz() const { return Vector4<T>(x, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyyw() const { return Vector4<T>(x, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyzx() const { return Vector4<T>(x, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyzy() const { return Vector4<T>(x, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyzz() const { return Vector4<T>(x, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyzw() const { return Vector4<T>(x, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xywx() const { return Vector4<T>(x, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xywy() const { return Vector4<T>(x, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xywz() const { return Vector4<T>(x, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xyww() const { return Vector4<T>(x, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzxx() const { return Vector4<T>(x, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzxy() const { return Vector4<T>(x, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzxz() const { return Vector4<T>(x, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzxw() const { return Vector4<T>(x, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzyx() const { return Vector4<T>(x, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzyy() const { return Vector4<T>(x, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzyz() const { return Vector4<T>(x, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzyw() const { return Vector4<T>(x, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzzx() const { return Vector4<T>(x, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzzy() const { return Vector4<T>(x, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzzz() const { return Vector4<T>(x, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzzw() const { return Vector4<T>(x, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzwx() const { return Vector4<T>(x, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzwy() const { return Vector4<T>(x, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzwz() const { return Vector4<T>(x, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xzww() const { return Vector4<T>(x, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwxx() const { return Vector4<T>(x, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwxy() const { return Vector4<T>(x, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwxz() const { return Vector4<T>(x, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwxw() const { return Vector4<T>(x, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwyx() const { return Vector4<T>(x, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwyy() const { return Vector4<T>(x, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwyz() const { return Vector4<T>(x, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwyw() const { return Vector4<T>(x, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwzx() const { return Vector4<T>(x, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwzy() const { return Vector4<T>(x, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwzz() const { return Vector4<T>(x, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwzw() const { return Vector4<T>(x, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwwx() const { return Vector4<T>(x, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwwy() const { return Vector4<T>(x, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwwz() const { return Vector4<T>(x, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> xwww() const { return Vector4<T>(x, w, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxxx() const { return Vector4<T>(y, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxxy() const { return Vector4<T>(y, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxxz() const { return Vector4<T>(y, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxxw() const { return Vector4<T>(y, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxyx() const { return Vector4<T>(y, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxyy() const { return Vector4<T>(y, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxyz() const { return Vector4<T>(y, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxyw() const { return Vector4<T>(y, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxzx() const { return Vector4<T>(y, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxzy() const { return Vector4<T>(y, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxzz() const { return Vector4<T>(y, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxzw() const { return Vector4<T>(y, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxwx() const { return Vector4<T>(y, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxwy() const { return Vector4<T>(y, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxwz() const { return Vector4<T>(y, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yxww() const { return Vector4<T>(y, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyxx() const { return Vector4<T>(y, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyxy() const { return Vector4<T>(y, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyxz() const { return Vector4<T>(y, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyxw() const { return Vector4<T>(y, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyyx() const { return Vector4<T>(y, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyyy() const { return Vector4<T>(y, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyyz() const { return Vector4<T>(y, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyyw() const { return Vector4<T>(y, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyzx() const { return Vector4<T>(y, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyzy() const { return Vector4<T>(y, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyzz() const { return Vector4<T>(y, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyzw() const { return Vector4<T>(y, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yywx() const { return Vector4<T>(y, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yywy() const { return Vector4<T>(y, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yywz() const { return Vector4<T>(y, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yyww() const { return Vector4<T>(y, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzxx() const { return Vector4<T>(y, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzxy() const { return Vector4<T>(y, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzxz() const { return Vector4<T>(y, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzxw() const { return Vector4<T>(y, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzyx() const { return Vector4<T>(y, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzyy() const { return Vector4<T>(y, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzyz() const { return Vector4<T>(y, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzyw() const { return Vector4<T>(y, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzzx() const { return Vector4<T>(y, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzzy() const { return Vector4<T>(y, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzzz() const { return Vector4<T>(y, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzzw() const { return Vector4<T>(y, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzwx() const { return Vector4<T>(y, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzwy() const { return Vector4<T>(y, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzwz() const { return Vector4<T>(y, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> yzww() const { return Vector4<T>(y, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywxx() const { return Vector4<T>(y, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywxy() const { return Vector4<T>(y, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywxz() const { return Vector4<T>(y, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywxw() const { return Vector4<T>(y, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywyx() const { return Vector4<T>(y, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywyy() const { return Vector4<T>(y, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywyz() const { return Vector4<T>(y, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywyw() const { return Vector4<T>(y, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywzx() const { return Vector4<T>(y, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywzy() const { return Vector4<T>(y, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywzz() const { return Vector4<T>(y, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywzw() const { return Vector4<T>(y, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywwx() const { return Vector4<T>(y, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywwy() const { return Vector4<T>(y, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywwz() const { return Vector4<T>(y, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> ywww() const { return Vector4<T>(y, w, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxxx() const { return Vector4<T>(z, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxxy() const { return Vector4<T>(z, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxxz() const { return Vector4<T>(z, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxxw() const { return Vector4<T>(z, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxyx() const { return Vector4<T>(z, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxyy() const { return Vector4<T>(z, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxyz() const { return Vector4<T>(z, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxyw() const { return Vector4<T>(z, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxzx() const { return Vector4<T>(z, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxzy() const { return Vector4<T>(z, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxzz() const { return Vector4<T>(z, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxzw() const { return Vector4<T>(z, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxwx() const { return Vector4<T>(z, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxwy() const { return Vector4<T>(z, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxwz() const { return Vector4<T>(z, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zxww() const { return Vector4<T>(z, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyxx() const { return Vector4<T>(z, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyxy() const { return Vector4<T>(z, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyxz() const { return Vector4<T>(z, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyxw() const { return Vector4<T>(z, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyyx() const { return Vector4<T>(z, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyyy() const { return Vector4<T>(z, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyyz() const { return Vector4<T>(z, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyyw() const { return Vector4<T>(z, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyzx() const { return Vector4<T>(z, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyzy() const { return Vector4<T>(z, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyzz() const { return Vector4<T>(z, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyzw() const { return Vector4<T>(z, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zywx() const { return Vector4<T>(z, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zywy() const { return Vector4<T>(z, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zywz() const { return Vector4<T>(z, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zyww() const { return Vector4<T>(z, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzxx() const { return Vector4<T>(z, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzxy() const { return Vector4<T>(z, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzxz() const { return Vector4<T>(z, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzxw() const { return Vector4<T>(z, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzyx() const { return Vector4<T>(z, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzyy() const { return Vector4<T>(z, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzyz() const { return Vector4<T>(z, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzyw() const { return Vector4<T>(z, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzzx() const { return Vector4<T>(z, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzzy() const { return Vector4<T>(z, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzzz() const { return Vector4<T>(z, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzzw() const { return Vector4<T>(z, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzwx() const { return Vector4<T>(z, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzwy() const { return Vector4<T>(z, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzwz() const { return Vector4<T>(z, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zzww() const { return Vector4<T>(z, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwxx() const { return Vector4<T>(z, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwxy() const { return Vector4<T>(z, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwxz() const { return Vector4<T>(z, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwxw() const { return Vector4<T>(z, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwyx() const { return Vector4<T>(z, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwyy() const { return Vector4<T>(z, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwyz() const { return Vector4<T>(z, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwyw() const { return Vector4<T>(z, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwzx() const { return Vector4<T>(z, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwzy() const { return Vector4<T>(z, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwzz() const { return Vector4<T>(z, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwzw() const { return Vector4<T>(z, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwwx() const { return Vector4<T>(z, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwwy() const { return Vector4<T>(z, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwwz() const { return Vector4<T>(z, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> zwww() const { return Vector4<T>(z, w, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxxx() const { return Vector4<T>(w, x, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxxy() const { return Vector4<T>(w, x, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxxz() const { return Vector4<T>(w, x, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxxw() const { return Vector4<T>(w, x, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxyx() const { return Vector4<T>(w, x, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxyy() const { return Vector4<T>(w, x, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxyz() const { return Vector4<T>(w, x, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxyw() const { return Vector4<T>(w, x, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxzx() const { return Vector4<T>(w, x, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxzy() const { return Vector4<T>(w, x, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxzz() const { return Vector4<T>(w, x, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxzw() const { return Vector4<T>(w, x, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxwx() const { return Vector4<T>(w, x, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxwy() const { return Vector4<T>(w, x, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxwz() const { return Vector4<T>(w, x, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wxww() const { return Vector4<T>(w, x, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyxx() const { return Vector4<T>(w, y, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyxy() const { return Vector4<T>(w, y, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyxz() const { return Vector4<T>(w, y, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyxw() const { return Vector4<T>(w, y, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyyx() const { return Vector4<T>(w, y, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyyy() const { return Vector4<T>(w, y, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyyz() const { return Vector4<T>(w, y, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyyw() const { return Vector4<T>(w, y, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyzx() const { return Vector4<T>(w, y, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyzy() const { return Vector4<T>(w, y, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyzz() const { return Vector4<T>(w, y, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyzw() const { return Vector4<T>(w, y, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wywx() const { return Vector4<T>(w, y, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wywy() const { return Vector4<T>(w, y, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wywz() const { return Vector4<T>(w, y, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wyww() const { return Vector4<T>(w, y, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzxx() const { return Vector4<T>(w, z, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzxy() const { return Vector4<T>(w, z, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzxz() const { return Vector4<T>(w, z, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzxw() const { return Vector4<T>(w, z, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzyx() const { return Vector4<T>(w, z, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzyy() const { return Vector4<T>(w, z, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzyz() const { return Vector4<T>(w, z, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzyw() const { return Vector4<T>(w, z, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzzx() const { return Vector4<T>(w, z, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzzy() const { return Vector4<T>(w, z, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzzz() const { return Vector4<T>(w, z, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzzw() const { return Vector4<T>(w, z, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzwx() const { return Vector4<T>(w, z, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzwy() const { return Vector4<T>(w, z, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzwz() const { return Vector4<T>(w, z, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wzww() const { return Vector4<T>(w, z, w, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwxx() const { return Vector4<T>(w, w, x, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwxy() const { return Vector4<T>(w, w, x, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwxz() const { return Vector4<T>(w, w, x, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwxw() const { return Vector4<T>(w, w, x, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwyx() const { return Vector4<T>(w, w, y, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwyy() const { return Vector4<T>(w, w, y, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwyz() const { return Vector4<T>(w, w, y, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwyw() const { return Vector4<T>(w, w, y, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwzx() const { return Vector4<T>(w, w, z, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwzy() const { return Vector4<T>(w, w, z, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwzz() const { return Vector4<T>(w, w, z, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwzw() const { return Vector4<T>(w, w, z, w); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwwx() const { return Vector4<T>(w, w, w, x); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwwy() const { return Vector4<T>(w, w, w, y); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwwz() const { return Vector4<T>(w, w, w, z); }

        /**
         * @brief Swizzle getter function.
         * @return A new, rearranged Vector4.
         */
        inline Vector4<T> wwww() const { return Vector4<T>(w, w, w, w); }

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
        inline void xyzw(const Vector4<T> & _vec) { x = _vec.x; y = _vec.y; z = _vec.z; w = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xywz(const Vector4<T> & _vec) { x = _vec.x; y = _vec.y; w = _vec.z; z = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzyw(const Vector4<T> & _vec) { x = _vec.x; z = _vec.y; y = _vec.z; w = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xzwy(const Vector4<T> & _vec) { x = _vec.x; z = _vec.y; w = _vec.z; y = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xwyz(const Vector4<T> & _vec) { x = _vec.x; w = _vec.y; y = _vec.z; z = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void xwzy(const Vector4<T> & _vec) { x = _vec.x; w = _vec.y; z = _vec.z; y = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxzw(const Vector4<T> & _vec) { y = _vec.x; x = _vec.y; z = _vec.z; w = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yxwz(const Vector4<T> & _vec) { y = _vec.x; x = _vec.y; w = _vec.z; z = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzxw(const Vector4<T> & _vec) { y = _vec.x; z = _vec.y; x = _vec.z; w = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void yzwx(const Vector4<T> & _vec) { y = _vec.x; z = _vec.y; w = _vec.z; x = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void ywxz(const Vector4<T> & _vec) { y = _vec.x; w = _vec.y; x = _vec.z; z = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void ywzx(const Vector4<T> & _vec) { y = _vec.x; w = _vec.y; z = _vec.z; x = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxyw(const Vector4<T> & _vec) { z = _vec.x; x = _vec.y; y = _vec.z; w = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zxwy(const Vector4<T> & _vec) { z = _vec.x; x = _vec.y; w = _vec.z; y = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zyxw(const Vector4<T> & _vec) { z = _vec.x; y = _vec.y; x = _vec.z; w = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zywx(const Vector4<T> & _vec) { z = _vec.x; y = _vec.y; w = _vec.z; x = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zwxy(const Vector4<T> & _vec) { z = _vec.x; w = _vec.y; x = _vec.z; y = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void zwyx(const Vector4<T> & _vec) { z = _vec.x; w = _vec.y; y = _vec.z; x = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wxyz(const Vector4<T> & _vec) { w = _vec.x; x = _vec.y; y = _vec.z; z = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wxzy(const Vector4<T> & _vec) { w = _vec.x; x = _vec.y; z = _vec.z; y = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wyxz(const Vector4<T> & _vec) { w = _vec.x; y = _vec.y; x = _vec.z; z = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wyzx(const Vector4<T> & _vec) { w = _vec.x; y = _vec.y; z = _vec.z; x = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wzxy(const Vector4<T> & _vec) { w = _vec.x; z = _vec.y; x = _vec.z; y = _vec.w; }

        /**
         * @brief Swizzle setter function.
         */
        inline void wzyx(const Vector4<T> & _vec) { w = _vec.x; z = _vec.y; y = _vec.z; x = _vec.w; }

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


    // Constructors
    //____________________________________

    // this does not init to zero for speed reasons!
    template<class T>
    inline Vector4<T>::Vector4()
    {
    }

    template<class T>
    inline Vector4<T>::Vector4(T _val) :
        x(_val),
        y(_val),
        z(_val),
        w(_val)
    {
    }

    template<class T>
    inline Vector4<T>::Vector4(T _x, T _y, T _z, T _w) :
        x(_x),
        y(_y),
        z(_z),
        w(_w)
    {
    }

    template<class T>
    template<class OT>
    inline Vector4<T>::Vector4(const Vector4<OT> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(_vec.z),
        w(_vec.w)
    {
    }

    template<class T>
    template<class OT>
    inline Vector4<T>::Vector4(const Vector3<OT> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(_vec.z),
        w(1.0)
    {
    }

    template<class T>
    template<class OT>
    inline Vector4<T>::Vector4(const Vector2<OT> & _vec) :
        x(_vec.x),
        y(_vec.y),
        z(0.0),
        w(1.0)
    {
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator = (const Vector4<T> & _other)
    {
        x = _other.x;
        y = _other.y;
        z = _other.z;
        w = _other.w;
        return *this;
    }

    // Access
    //____________________________________

    template<class T>
    inline T & Vector4<T>::operator [](stick::UInt32 _index)
    {
        return *(&x + _index);
    }

    template<class T>
    inline const T & Vector4<T>::operator [](stick::UInt32 _index) const
    {
        return *(&x + _index);
    }

    // Boolean
    //____________________________________

    template<class T>
    inline bool Vector4<T>::operator == (const Vector4<T> & _vec) const
    {
        if (x == _vec.x && y == _vec.y && z == _vec.z && w == _vec.w)
            return true;
        else
            return false;
    }

    template<class T>
    inline bool Vector4<T>::operator != (const Vector4<T> & _vec) const
    {
        if (x == _vec.x && y == _vec.y && z == _vec.z && w == _vec.w)
            return false;
        else
            return true;
    }


    // Arithmetic operations
    //____________________________________

    template<class T>
    inline Vector4<T> Vector4<T>::operator + (const Vector4<T> & _vec) const
    {
        Vector4<T> ret;
        ret.x = x + _vec.x;
        ret.y = y + _vec.y;
        ret.z = z + _vec.z;
        ret.w = w + _vec.w;
        return ret;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator - (const Vector4<T> & _vec) const
    {
        Vector4<T> ret;
        ret.x = x - _vec.x;
        ret.y = y - _vec.y;
        ret.z = z - _vec.z;
        ret.w = w - _vec.w;
        return ret;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator * (const Vector4<T> & _vec) const
    {
        Vector4<T> ret;
        ret.x = x * _vec.x;
        ret.y = y * _vec.y;
        ret.z = z * _vec.z;
        ret.w = w * _vec.w;
        return ret;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator / (const Vector4<T> & _vec) const
    {
        Vector4<T> ret;
        ret.x = x / _vec.x;
        ret.y = y / _vec.y;
        ret.z = z / _vec.z;
        ret.w = w / _vec.w;
        return ret;
    }

    template<class T>
    inline const Vector4<T> & Vector4<T>::operator + () const
    {
        return *this;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator - () const
    {
        return Vector4<T>(-x, -y, -z, -w);
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator -= (const Vector4<T> & _vec)
    {
        x -= _vec.x;
        y -= _vec.y;
        z -= _vec.z;
        w -= _vec.w;
        return *this;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator += (const Vector4<T> & _vec)
    {
        x += _vec.x;
        y += _vec.y;
        z += _vec.z;
        w += _vec.w;
        return *this;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator *= (const Vector4<T> & _vec)
    {
        x *= _vec.x;
        y *= _vec.y;
        z *= _vec.z;
        w *= _vec.w;
        return *this;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator /= (const Vector4<T> & _vec)
    {
        x /= _vec.x;
        y /= _vec.y;
        z /= _vec.z;
        w /= _vec.w;
        return *this;
    }

    // Real Arithmetic
    //____________________________________

    template<class T>
    inline Vector4<T> Vector4<T>::operator / (T _val) const
    {
        Vector4<T> ret;
        ret.x = x / _val;
        ret.y = y / _val;
        ret.z = z / _val;
        ret.w = w / _val;
        return ret;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator * (T _val) const
    {
        Vector4<T> ret;
        ret.x = x * _val;
        ret.y = y * _val;
        ret.z = z * _val;
        ret.w = w * _val;
        return ret;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator + (T _val) const
    {
        Vector4<T> ret;
        ret.x = x + _val;
        ret.y = y + _val;
        ret.z = z + _val;
        ret.w = w + _val;
        return ret;
    }

    template<class T>
    inline Vector4<T> Vector4<T>::operator - (T _val) const
    {
        Vector4<T> ret;
        ret.x = x - _val;
        ret.y = y - _val;
        ret.z = z - _val;
        ret.w = w - _val;
        return ret;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator /= (T _val)
    {
        x /= _val;
        y /= _val;
        z /= _val;
        w /= _val;
        return *this;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator *= (T _val)
    {
        x *= _val;
        y *= _val;
        z *= _val;
        w *= _val;
        return *this;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator += (T _val)
    {
        x += _val;
        y += _val;
        z += _val;
        w += _val;
        return *this;
    }

    template<class T>
    inline Vector4<T> & Vector4<T>::operator -= (T _val)
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
    inline T * Vector4<T>::ptr()
    {
        return &x;
    }

    template<class T>
    inline const T * Vector4<T>::ptr() const
    {
        return &x;
    }

    using Vec4f = Vector4<stick::Float32>;
}

#endif //CRUNCH_VECTOR4_HPP
