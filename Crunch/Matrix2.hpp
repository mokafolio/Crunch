#ifndef CRUNCH_MATRIX2_HPP
#define CRUNCH_MATRIX2_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/TrigonometryFunc.hpp>
#include <cstring> //for memcpy
#include <cmath> //for sin cos

namespace crunch
{
    template <class T>
    class Matrix4;

    /**
     * @brief A 2x2 matrix class.
     *
     * The matrix has a column major memory layout.
     * The matrix uses column major notation (meaning vectors are treated like columns when multiplied, like OpenGL),
     * meaning that matrix multiplication works exactly like it does in OpenGL/GLSL.
     *
     * @arg T The value type of the matrix (i.e. stick::Float32)
     */
    template <class T>
    class Matrix2
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Matrix2();

        /**
         * @brief Constructs a Matrix from the provided column vectors.
         */
        template<class OT>
        inline Matrix2(const Vector2<OT> & _col0,
                       const Vector2<OT> & _col1);

        /**
         * @brief Constructs a Matrix from the provided numbers.
         */
        inline Matrix2(T _col00, T _col10,
                       T _col01, T _col11);

        /**
         * @brief Copy constructs a matrix from another one.
         */
        template<class OT>
        inline Matrix2(const Matrix2<OT> & _mat);

        /**
         * @brief Constructs a matrix with all elements initialized to the provided number.
         */
        explicit inline Matrix2(const T _val);

        /**
         * @brief Constructs a matrix from the provided c array.
         *
         * Note: Remember, column major memory layout.
         */
        explicit inline Matrix2(T * _floatArray);

        /**
         * @brief Assign another matrix to this.
         */
        inline Matrix2 & operator = (const Matrix2<T> & _other);

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
        inline bool operator == (const Matrix2<T> & _mat) const;

        /**
         * @brief Returns true if this matrix and the provided matrix are not identical.
         */
        inline bool operator != (const Matrix2<T> & _mat) const;

        /**
         * @brief Adds two matrices.
         */
        inline Matrix2 operator + (const Matrix2<T> & _mat) const;

        /**
         * @brief Subtracts two matrices.
         */
        inline Matrix2 operator - (const Matrix2<T> & _mat) const;

        /**
         * @brief Adds another matrix to this matrix.
         */
        inline Matrix2 & operator += (const Matrix2<T> & _mat);

        /**
         * @brief Subtracts another matrix from this matrix.
         */
        inline Matrix2 & operator -= (const Matrix2<T> & _mat);

        /**
         * @brief Negates this matrix.
         */
        inline Matrix2 operator - () const;

        /**
         * @brief Multiplies two matrices.
         */
        inline Matrix2 operator * (const Matrix2<T> & _mat) const;

        /**
         * @brief Multiplies all elements in a matrix with the provided number.
         */
        inline Matrix2 operator * (T _v) const;

        /**
         * @brief Multiplies a matrix with a column vector.
         */
        inline Vector2<T> operator * (const Vector2<T> & _vec) const;

        /**
         * @brief Multiplies this matrix with another matrix.
         */
        inline Matrix2 & operator *= (const Matrix2<T> & _mat);

        /**
         * @brief Multiplies all elements in this matrix with the provided number.
         */
        inline Matrix2 & operator *= (T _v);

        /**
         * @brief Scales this matrix.
         *
         * This will effectively create a scaling matrix and multiply it with
         * this matrix: *this = scaling(_s) * *this;
         */
        inline Matrix2 & scale(T _s);

        /**
         * @brief Scales this matrix.
         *
         * This will effectively create a scaling matrix and multiply it with
         * this matrix: *this = scaling(_x, _y) * *this;
         */
        inline Matrix2 & scale(T _x, T _y);

        /**
         * @brief Scales this matrix.
         *
         * This will effectively create a scaling matrix and multiply it with
         * this matrix: *this = scaling(_vec) * *this;
         */
        inline Matrix2 & scale(const Vector2<T> & _vec);

        /**
         * @brief Rotates this matrix by an angle in radians.
         *
         * This will effectively create a rotation matrix and multiply it with
         * this matrix: *this = rotation(_radians) * *this;
         */
        inline Matrix2 & rotate(T _radians);

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
        static inline Matrix2 identity();

        /**
         * @brief Returns a matrix with all elements initialized to zero.
         */
        static inline Matrix2 zero();

        /**
         * @brief Returns a rotation matrix.
         * @param _radians An angle in radians.
         */
        static inline Matrix2 rotation(T _radians);

        /**
         * @brief Returns a scaling matrix.
         * @param _scale Uniform scale factor.
         */
        static inline Matrix2 scaling(T _scale);

        /**
         * @brief Returns a scaling matrix.
         * @param _scale Scale vector.
         */
        static inline Matrix2 scaling(const Vector2<T> & _scale);

        /**
         * @brief Returns a scaling matrix.
         * @param _x Scale along x axis.
         * @param _y Scale along y axis.
         */
        static inline Matrix2 scaling(T _x, T _y);


    private:

        Vector2<T> m_col0;
        Vector2<T> m_col1;
    };

    using Mat2f = Matrix2<stick::Float32>;

    // Constructors
    //____________________________________

    template<class T>
    inline Matrix2<T>::Matrix2()
    {
    }

    template<class T>
    template<class OT>
    inline Matrix2<T>::Matrix2(const Vector2<OT> & _col0,   //column0
                               const Vector2<OT> & _col1)   //column1
    {
        m_col0 = _col0;
        m_col1 = _col1;
    }

    template<class T>
    inline Matrix2<T>::Matrix2(T _col00, T _col10,
                               T _col01, T _col11)
    {
        m_col0 = Vector2<T>(_col00, _col01);
        m_col1 = Vector2<T>(_col10, _col11);
    }


    template<class T>
    template<class OT>
    inline Matrix2<T>::Matrix2(const Matrix2<OT> & _mat)
    {
        m_col0 = _mat.m_col0;
        m_col1 = _mat.m_col1;
    }

    template<class T>
    inline Matrix2<T>::Matrix2(const T _val)
    {
        m_col0 = Vector2<T>(_val);
        m_col1 = Vector2<T>(_val);
    }

    template<class T>
    inline Matrix2<T>::Matrix2(T * _floatArray)
    {
        std::memcpy(m_col0.ptr(), _floatArray, 4 * sizeof(T));
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::operator = (const Matrix2<T> & _other)
    {
        m_col0 = _other.m_col0;
        m_col1 = _other.m_col1;

        return *this;
    }



    // Access
    //____________________________________

    template<class T>
    inline Vector2<T> & Matrix2<T>::operator [](stick::UInt32 _col)
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline const Vector2<T> & Matrix2<T>::operator [](stick::UInt32 _col) const
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline T & Matrix2<T>::element(stick::UInt32 _col, stick::UInt32 _row)
    {
        return this->operator[](_col)[_row];
    }

    template<class T>
    inline const T & Matrix2<T>::element(stick::UInt32 _col, stick::UInt32 _row) const
    {
        return this->operator[](_col)[_row];
    }


    // Boolean
    //____________________________________

    template<class T>
    inline bool Matrix2<T>::operator == (const Matrix2<T> & _mat) const
    {
        if (m_col0 != _mat.m_col0 ||
                m_col1 != _mat.m_col1)
        {
            return false;
        }

        return true;
    }

    template<class T>
    inline bool Matrix2<T>::operator != (const Matrix2<T> & _mat) const
    {
        if (m_col0 != _mat.m_col0 ||
                m_col1 != _mat.m_col1)
        {
            return true;
        }

        return false;
    }


    // Addition / Substraction
    //____________________________________

    template<class T>
    inline Matrix2<T> Matrix2<T>::operator + (const Matrix2<T> & _mat) const
    {
        return Matrix2<T>(
                   m_col0 + _mat.m_col0,
                   m_col1 + _mat.m_col1
               );
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::operator - (const Matrix2<T> & _mat) const
    {
        return Matrix2<T>(
                   m_col0 - _mat.m_col0,
                   m_col1 - _mat.m_col1
               );
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::operator += (const Matrix2<T> & _mat)
    {
        *this = *this + _mat;
        return *this;
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::operator -= (const Matrix2<T> & _mat)
    {
        *this = *this - _mat;
        return *this;
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::operator - () const
    {
        return Matrix2<T>(
                   -m_col0,
                   -m_col1
               );
    }


    // Multiplication
    //____________________________________

    template<class T>
    inline Vector2<T> Matrix2<T>::operator * (const Vector2<T> & _vec) const
    {
        Vector2<T> ret;

        ret.x = _vec.x * m_col0.x + _vec.y * m_col1.x;
        ret.y = _vec.x * m_col0.y + _vec.y * m_col1.y;

        return ret;
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::operator * (const Matrix2<T> & _mat) const
    {
        return Matrix2<T>(
                   *this * _mat.m_col0,
                   *this * _mat.m_col1
               );
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::operator *= (const Matrix2<T> & _mat)
    {
        *this = *this * _mat;
        return *this;
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::operator * (T _v) const
    {
        return Matrix2<T>(
                   m_col0 * _v,
                   m_col1 * _v
               );
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::operator *= (T _v)
    {
        *this = *this * _v;
        return *this;
    }


    // Non static members to scale / rotate an existing matrix
    //____________________________________

    template<class T>
    inline Matrix2<T> & Matrix2<T>::scale(T _s)
    {
        *this *= scaling(_s);
        return *this;
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::scale(T _x, T _y)
    {
        *this *= scaling(Vector3<T>(_x, _y));
        return *this;
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::scale(const Vector2<T> & _vec)
    {
        *this *= scaling(_vec);
        return *this;
    }

    template<class T>
    inline Matrix2<T> & Matrix2<T>::rotate(T _radians)
    {
        *this *= rotation(_radians);
        return *this;
    }


    //Pointer accessors
    //____________________________________

    template<class T>
    inline T * Matrix2<T>::ptr()
    {
        return &m_col0.x;
    }

    template<class T>
    inline const T * Matrix2<T>::ptr() const
    {
        return &m_col0.x;
    }


    //Static helper functions
    //____________________________________

    template<class T>
    inline Matrix2<T> Matrix2<T>::identity()
    {
        return Matrix2<T>(1, 0,
                          0, 1);
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::zero()
    {
        return Matrix2<T>(0, 0,
                          0, 0);
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::rotation(T _radians)
    {
        T c = std::cos(_radians);
        T s = std::sin(_radians);

        return Matrix2<T>(
                   Vector2<T>(c, s),
                   Vector2<T>(-s, c)
               );
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::scaling(const Vector2<T> & _scale)
    {
        return Matrix2<T>(
                   Vector2<T>(_scale.x, T(0.0)),
                   Vector2<T>(T(0.0), _scale.y)
               );
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::scaling(T _scale)
    {
        return scaling(Vector2<T>(_scale));
    }

    template<class T>
    inline Matrix2<T> Matrix2<T>::scaling(T _x, T _y)
    {
        return scaling(Vector2<T>(_x, _y));
    }
}

#endif //CRUNCH_MATRIX2_HPP
