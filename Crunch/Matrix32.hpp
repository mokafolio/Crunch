#ifndef CRUNCH_MATRIX32_HPP
#define CRUNCH_MATRIX32_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/TrigonometryFunc.hpp>
#include <cstring> //for memcpy
#include <cmath> //for sin cos

namespace crunch
{
    /**
    * @brief A 3x2 Matrix class.
    *
    * The matrix has a column major memory layout.
    *
    * @arg T The value type of the matrix (i.e. stick::Float32)
    */
    template<class T>
    class Matrix32
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Matrix32();

        /**
         * @brief Constructs a Matrix from the provided column vectors.
         */
        template<class OT>
        inline Matrix32(const Vector2<OT> & _col0,
                        const Vector2<OT> & _col1,
                        const Vector2<OT> & _col2);

        /**
         * @brief Constructs a Matrix from the provided numbers.
         */
        inline Matrix32(T _col00, T _col10, T _col20,
                        T _col01, T _col11, T _col21);

        /**
         * @brief Copy constructs a matrix from another one.
         */
        template<class OT>
        inline Matrix32(const Matrix32<OT> & _mat);

        /**
         * @brief Constructs a matrix with all elements initialized to the provided number.
         */
        explicit inline Matrix32(const T _val);

        /**
         * @brief Constructs a matrix from the provided c array.
         *
         * Note: Remember, column major memory layout.
         */
        explicit inline Matrix32(T * _floatArray);

        /**
         * @brief Assign another matrix to this.
         */
        inline Matrix32 & operator = (const Matrix32<T> & _other);

        /**
         * @brief Access a column vector of the matrix.
         * @param _col The column index.
         * @return A reference to the column vector.
         */
        inline Vector2<T> & operator [](stick::UInt32 _col);

        /**
         * @brief Access a column vector of the matrix.
         * @param _col The column index.
         * @return A const reference to the column vector.
         */
        inline const Vector2<T> & operator [](stick::UInt32 _col) const;

        /**
         * @brief Access a value in the matrix.
         * @param _col The column index.
         * @param _row The row index.
         * @return A reference to the matrix element.
         */
        inline T & element(stick::UInt32 _col, stick::UInt32 _row);

        /**
         * @brief Access a value in the matrix.
         * @param _col The column index.
         * @param _row The row index.
         * @return A const reference to the matrix element.
         */
        inline const T & element(stick::UInt32 _col, stick::UInt32 _row) const;

        /**
         * @brief Returns true if this matrix and the provided matrix are identical.
         */
        inline bool operator == (const Matrix32 & _mat) const;

        /**
         * @brief Returns true if this matrix and the provided matrix are not identical.
         */
        inline bool operator != (const Matrix32 & _mat) const;

        /**
         * @brief Adds two matrices.
         */
        inline Matrix32 operator + (const Matrix32 & _mat) const;

        /**
         * @brief Subtracts two matrices.
         */
        inline Matrix32 operator - (const Matrix32 & _mat) const;

        /**
         * @brief Adds another matrix to this matrix.
         */
        inline Matrix32 & operator += (const Matrix32 & _mat);

        /**
         * @brief Subtracts another matrix from this matrix.
         */
        inline Matrix32 & operator -= (const Matrix32 & _mat);

        /**
         * @brief Negates this matrix.
         */
        inline Matrix32 operator - () const;

        /**
         * @brief Multiplies two matrices.
         */
        inline Matrix32 operator * (const Matrix32 & _mat) const;

        /**
         * @brief Multiplies all elements in a matrix with the provided number.
         */
        inline Matrix32 operator * (T _v) const;

        /**
         * @brief Multiplies a matrix with a column vector.
         */
        inline Vector2<T> operator * (const Vector2<T> & _vec) const;

        /**
         * @brief Multiplies this matrix with another matrix.
         */
        inline Matrix32 & operator *= (const Matrix32 & _mat);

        /**
         * @brief Multiplies all elements in this matrix with the provided number.
         */
        inline Matrix32 & operator *= (T _v);

        /**
         * @brief Scales this matrix.
         *
         * This will effectively create a scaling matrix and multiply it with
         * this matrix: *this = scaling(_s) * *this;
         */
        inline Matrix32 & scale(T _s);

        /**
         * @brief Scales this matrix.
         *
         * This will effectively create a scaling matrix and multiply it with
         * this matrix: *this = scaling(_x, _y) * *this;
         */
        inline Matrix32 & scale(T _x, T _y);

        /**
         * @brief Scales this matrix.
         *
         * This will effectively create a scaling matrix and multiply it with
         * this matrix: *this = scaling(_vec) * *this;
         */
        inline Matrix32 & scale(const Vector2<T> & _vec);

        /**
         * @brief Rotates this matrix by an angle in radians.
         *
         * This will effectively create a rotation matrix and multiply it with
         * this matrix: *this = rotation(_radians) * *this;
         */
        inline Matrix32 & rotate(T _radians);


        /**
         * @brief Skew this matrix.
         */
        inline Matrix32 & skew(T _radiansX, T _radiansY);
        inline Matrix32 & skew(const Vector2<T> & _skew);

        /**
         * @brief Translate this matrix.
         */
        inline Matrix32 & translate(T _x, T _y);
        inline Matrix32 & translate(const Vector2<T> & _translation);


        /**
         * @brief Returns a pointer to the memory block of this matrix.
         */
        inline T * ptr();

        /**
         * @brief Returns a pointer to the memory block of this matrix.
         */
        inline const T * ptr() const;

        /**
         * @brief Returns an identity matrix.
         */
        static inline Matrix32 identity();

        /**
         * @brief Returns a matrix with all elements initialized to zero.
         */
        static inline Matrix32 zero();

        /**
         * @brief Returns a rotation matrix.
         * @param _radians An angle in radians.
         */
        static inline Matrix32 rotation(T _radians);

        /**
         * @brief Returns a scaling matrix.
         * @param _scale Uniform scale factor.
         */
        static inline Matrix32 scaling(T _scale);

        /**
         * @brief Returns a scaling matrix.
         * @param _scale Scale vector.
         */
        static inline Matrix32 scaling(const Vector2<T> & _scale);

        /**
         * @brief Returns a scaling matrix.
         * @param _x Scale along x axis.
         * @param _y Scale along y axis.
         */
        static inline Matrix32 scaling(T _x, T _y);

        /**
        * @brief Returns a 2D translation matrix.
        */
        inline static Matrix32 translation(const Vector2<T> & _vec);

        /**
         * @brief Returns a 2D translation matrix.
         */
        inline static Matrix32 translation(T _x, T _y);

        /**
         * @brief Returns a 2D skew matrix.
         */
        static inline Matrix32 skewMatrix(T _radiansX, T _radiansY);

        /**
         * @brief Returns a 2D skew matrix.
         */
        static inline Matrix32 skewMatrix(const Vector2<T> & _rads);


    private:

        Vector2<T> m_col0;
        Vector2<T> m_col1;
        Vector2<T> m_col2;
    };

    using Mat32f = Matrix32<stick::Float32>;

    // Constructors
    //____________________________________

    template<class T>
    inline Matrix32<T>::Matrix32()
    {
    }

    template<class T>
    template<class OT>
    inline Matrix32<T>::Matrix32(const Vector2<OT> & _col0,   //column0
                                 const Vector2<OT> & _col1,
                                 const Vector2<OT> & _col2) :
        m_col0(_col0),
        m_col1(_col1),
        m_col2(_col2)
    {

    }

    template<class T>
    inline Matrix32<T>::Matrix32(T _col00, T _col10, T _col20,
                                 T _col01, T _col11, T _col21)
    {
        m_col0 = Vector2<T>(_col00, _col01);
        m_col1 = Vector2<T>(_col10, _col11);
        m_col2 = Vector2<T>(_col20, _col21);
    }


    template<class T>
    template<class OT>
    inline Matrix32<T>::Matrix32(const Matrix32<OT> & _mat) :
        m_col0(_mat.m_col0),
        m_col1(_mat.m_col1),
        m_col2(_mat.m_col2)
    {

    }

    template<class T>
    inline Matrix32<T>::Matrix32(const T _val)
    {
        m_col0 = Vector2<T>(_val);
        m_col1 = Vector2<T>(_val);
        m_col2 = Vector2<T>(_val);
    }

    template<class T>
    inline Matrix32<T>::Matrix32(T * _floatArray)
    {
        std::memcpy(m_col0.ptr(), _floatArray, 6 * sizeof(T));
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::operator = (const Matrix32 & _other)
    {
        m_col0 = _other.m_col0;
        m_col1 = _other.m_col1;
        m_col2 = _other.m_col2;

        return *this;
    }



    // Access
    //____________________________________

    template<class T>
    inline Vector2<T> & Matrix32<T>::operator [](stick::UInt32 _col)
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline const Vector2<T> & Matrix32<T>::operator [](stick::UInt32 _col) const
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline T & Matrix32<T>::element(stick::UInt32 _col, stick::UInt32 _row)
    {
        return this->operator[](_col)[_row];
    }

    template<class T>
    inline const T & Matrix32<T>::element(stick::UInt32 _col, stick::UInt32 _row) const
    {
        return this->operator[](_col)[_row];
    }


    // Boolean
    //____________________________________

    template<class T>
    inline bool Matrix32<T>::operator == (const Matrix32 & _mat) const
    {
        if (m_col0 != _mat.m_col0 || m_col1 != _mat.m_col1 || m_col2 != _mat.m_col2)
        {
            return false;
        }

        return true;
    }

    template<class T>
    inline bool Matrix32<T>::operator != (const Matrix32 & _mat) const
    {
        return !(*this == _mat);
    }


    // Addition / Substraction
    //____________________________________

    template<class T>
    inline Matrix32<T> Matrix32<T>::operator + (const Matrix32 & _mat) const
    {
        return Matrix32<T>(
                   m_col0 + _mat.m_col0,
                   m_col1 + _mat.m_col1,
                   m_col2 + _mat.m_col2
               );
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::operator - (const Matrix32 & _mat) const
    {
        return Matrix32<T>(
                   m_col0 - _mat.m_col0,
                   m_col1 - _mat.m_col1,
                   m_col2 - _mat.m_col2
               );
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::operator += (const Matrix32 & _mat)
    {
        *this = *this + _mat;
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::operator -= (const Matrix32 & _mat)
    {
        *this = *this - _mat;
        return *this;
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::operator - () const
    {
        return Matrix32<T>(
                   -m_col0,
                   -m_col1,
                   -m_col2
               );
    }


    // Multiplication
    //____________________________________

    template<class T>
    inline Vector2<T> Matrix32<T>::operator * (const Vector2<T> & _vec) const
    {
        Vector2<T> ret;

        ret.x = _vec.x * m_col0.x + _vec.y * m_col1.x + m_col2.x;
        ret.y = _vec.x * m_col0.y + _vec.y * m_col1.y + m_col2.y;

        return ret;
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::operator * (const Matrix32 & _mat) const
    {
        Matrix32<T> ret;
        ret.m_col0.x = _mat.m_col0.x *  m_col0.x + _mat.m_col0.y * m_col1.x;
        ret.m_col0.y = _mat.m_col0.x *  m_col0.y + _mat.m_col0.y * m_col1.y;

        ret.m_col1.x = _mat.m_col1.x *  m_col0.x + _mat.m_col1.y * m_col1.x;
        ret.m_col1.y = _mat.m_col1.x *  m_col0.y + _mat.m_col1.y * m_col1.y;

        ret.m_col2.x = _mat.m_col2.x *  m_col0.x + _mat.m_col2.y * m_col1.x + m_col2.x;
        ret.m_col2.y = _mat.m_col2.x *  m_col0.y + _mat.m_col2.y * m_col1.y + m_col2.y;
        return ret;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::operator *= (const Matrix32 & _mat)
    {
        *this = _mat * *this;
        return *this;
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::operator * (T _v) const
    {
        return Matrix32<T>(
                   m_col0 * _v,
                   m_col1 * _v,
                   m_col2 * _v
               );
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::operator *= (T _v)
    {
        *this = *this * _v;
        return *this;
    }


    // Non static members to scale / rotate an existing matrix
    //____________________________________

    template<class T>
    inline Matrix32<T> & Matrix32<T>::scale(T _s)
    {
        *this *= scaling(_s);
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::scale(T _x, T _y)
    {
        *this *= scaling(Vector3<T>(_x, _y));
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::scale(const Vector2<T> & _vec)
    {
        *this *= scaling(_vec);
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::rotate(T _radians)
    {
        *this *= rotation(_radians);
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::skew(T _radiansX, T _radiansY)
    {
        *this *= skewMatrix(_radiansX, _radiansY);
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::skew(const Vector2<T> & _skew)
    {
        *this *= skewMatrix(_skew);
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::translate(T _x, T _y)
    {
        *this *= translation(_x, _y);
        return *this;
    }

    template<class T>
    inline Matrix32<T> & Matrix32<T>::translate(const Vector2<T> & _translation)
    {
        *this *= translation(_translation);
        return *this;
    }


    //Pointer accessors
    //____________________________________

    template<class T>
    inline T * Matrix32<T>::ptr()
    {
        return &m_col0.x;
    }

    template<class T>
    inline const T * Matrix32<T>::ptr() const
    {
        return &m_col0.x;
    }


    //Static helper functions
    //____________________________________

    template<class T>
    inline Matrix32<T> Matrix32<T>::identity()
    {
        return Matrix32<T>(1, 0, 0,
                           0, 1, 0);
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::zero()
    {
        return Matrix32<T>(0, 0, 0,
                           0, 0, 0);
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::rotation(T _radians)
    {
        T c = std::cos(_radians);
        T s = std::sin(_radians);

        return Matrix32<T>(
                   Vector2<T>(c, s),
                   Vector2<T>(-s, c),
                   Vector2<T>(0)
               );
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::scaling(const Vector2<T> & _scale)
    {
        return Matrix32<T>(
                   Vector2<T>(_scale.x, T(0.0)),
                   Vector2<T>(T(0.0), _scale.y),
                   Vector2<T>(0)
               );
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::scaling(T _scale)
    {
        return scaling(Vector2<T>(_scale));
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::scaling(T _x, T _y)
    {
        return scaling(Vector2<T>(_x, _y));
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::translation(const Vector2<T> & _vec)
    {
        return Matrix32(Vector2<T>(1, 0), Vector2<T>(0, 1), _vec);
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::translation(T _x, T _y)
    {
        return translation(Vector2<T>(_x, _y));
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::skewMatrix(T _radiansX, T _radiansY)
    {
        return skewMatrix(Vector2<T>(_radiansX, _radiansY));
    }

    template<class T>
    inline Matrix32<T> Matrix32<T>::skewMatrix(const Vector2<T> & _rads)
    {
        return Matrix32(Vector2<T>(1, std::tan(_rads.y)),
                        Vector2<T>(std::tan(_rads.x), 1),
                        Vector2<T>(0));
    }
}

#endif //CRUNCH_MATRIX32_HPP
