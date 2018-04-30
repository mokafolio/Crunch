#ifndef CRUNCH_MATRIX4_HPP
#define CRUNCH_MATRIX4_HPP

#include <Crunch/Matrix3.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>
#include <Crunch/TrigonometryFunc.hpp>
#include <Stick/DynamicArray.hpp>

namespace crunch
{
    /**
     * @brief A 4x4 matrix class.
     *
     * The matrix has a column major memory layout.
     * The matrix uses column major notation (meaning vectors are treated like columns when multiplied, like OpenGL),
     * meaning that matrix multiplication works exactly like it does in OpenGL/GLSL.
     *
     * @arg T The value type of the matrix (i.e. stick::Float32)
     */
    template<class T>
    class Matrix4
    {
    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Matrix4();

        /**
         * @brief Constructs a Matrix from the provided column vectors.
         */
        template<class OT>
        inline Matrix4(const Vector4<OT> & _col0,
                       const Vector4<OT> & _col1,
                       const Vector4<OT> & _col2,
                       const Vector4<OT> & _col3);

        /**
         * @brief Constructs a Matrix from the provided numbers.
         */
        inline Matrix4(T m00, T m10, T m20, T m30,
                       T m01, T m11, T m21, T m31,
                       T m02, T m12, T m22, T m32,
                       T m03, T m13, T m23, T m33);

        /**
         * @brief Constructs a 4x4 matrix from a 3x3 matrix.
         *
         * This will use the 3x3 matrix for the transformation part of the matrix
         * and initialize the translation part of the 4x4 matrix to zero.
         */
        template<class OT>
        inline Matrix4(const Matrix3<OT> & _mat);

        /**
         * @brief Copy constructs a matrix from another one.
         */
        template<class OT>
        inline Matrix4(const Matrix4<OT> & _mat);

        /**
         * @brief Constructs a 4x4 matrix from a 3x3 matrix and a translation vector.
         *
         * This will use the 3x3 matrix for the transformation part of the matrix
         * and initialize the translation part to the provided translation vector.
         */
        template<class OT>
        inline Matrix4(const Matrix3<OT> & _mat, const Vector3<OT> & _translation);

        /**
         * @brief Constructs a matrix from a quaternion.
         *
         * This will build a 3x3 transformation matrix from the quaternion
         * and initialize the translation part to zero.
         */
        template<class OT>
        inline Matrix4(const Quaternion<OT> & _quat);

        /**
         * @brief Constructs a matrix from a quaternion and a translation vector.
         *
         * This will build a 3x3 transformation matrix from the quaternion
         * and initialize the translation part to the provided translation.
         */
        template<class OT>
        inline Matrix4(const Quaternion<OT> & _quat, const Vector3<OT> & _translation);

        /**
         * @brief Constructs a matrix with all elements initialized to the provided number.
         */
        explicit inline Matrix4(const T _val);

        /**
         * @brief Constructs a matrix from the provided c array.
         *
         * Note: Remember, column major memory layout.
         */
        explicit inline Matrix4(const T * _floatArray);

        /**
         * @brief Assign another matrix to this.
         */
        inline Matrix4 & operator = (const Matrix4 & _other);

        /**
         * @brief Access a column vector of the matrix.
         * @param _col The column index.
         * @return A reference to the column vector.
         */
        inline Vector4<T> & operator [](stick::UInt32 _col);

        /**
         * @brief Access a column vector of the matrix.
         * @param _col The column index.
         * @return A const reference to the column vector.
         */
        inline const Vector4<T> & operator [](stick::UInt32 _col) const;

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
        inline bool operator == (const Matrix4 & _mat) const;

        /**
         * @brief Returns true if this matrix and the provided matrix are not identical.
         */
        inline bool operator != (const Matrix4 & _mat) const;

        /**
         * @brief Adds two matrices.
         */
        inline Matrix4 operator + (const Matrix4 & _mat) const;

        /**
         * @brief Subtracts two matrices.
         */
        inline Matrix4 operator - (const Matrix4 & _mat) const;

        /**
         * @brief Adds another matrix to this matrix.
         */
        inline Matrix4 & operator += (const Matrix4 & _mat);

        /**
         * @brief Subtracts another matrix from this matrix.
         */
        inline Matrix4  & operator -= (const Matrix4 & _mat);

        /**
         * @brief Negates this matrix.
         */
        inline Matrix4 operator - () const;

        /**
         * @brief Multiplies two matrices.
         */
        inline Matrix4 operator * (const Matrix4 & _mat) const;

        /**
         * @brief Multiplies all elements in a matrix with the provided number.
         */
        inline Matrix4 operator * (T _v) const;

        /**
         * @brief Multiplies a matrix with a column 3D vector.
         *
         * This will set the w element of the provided 3D vector to 1.0 for the multiplication.
         */
        inline Vector3<T> operator * (const Vector3<T> & _vec) const;

        /**
         * @brief Multiplies a matrix with a column vector.
         */
        inline Vector4<T> operator * (const Vector4<T> & _vec) const;

        /**
         * @brief Multiplies this matrix with another matrix.
         */
        inline Matrix4 & operator *= (const Matrix4<T> & _mat);

        /**
         * @brief Multiplies all elements in this matrix with the provided number.
         */
        inline Matrix4 & operator *= (T _v);

        /**
         * @brief Translate this matrix.
         * @param _x Translation along the x axis.
         * @param _y Translation along the y axis.
         * @param _z Translation along the z axis.
         */
        inline Matrix4 & translate(T _x, T _y, T _z);

        /**
         * @brief Translate this matrix.
         * @param _vec Translation vector.
         */
        inline Matrix4 & translate(const Vector3<T> & _vec);

        /**
         * @brief Scale this matrix.
         * @param _s Uniform scaling factor.
         */
        inline Matrix4 & scale(T _s);

        /**
         * @brief Scale this matrix in 3D.
         * @param _x The scaling factor along the x axis.
         * @param _y The scaling factor along the y axis.
         * @param _z The scaling factor along the z axis.
         */
        inline Matrix4 & scale(T _x, T _y, T _z);

        /**
         * @brief Scale this matrix in 3D.
         * @param _vec The scaling factors along the three axis.
         */
        inline Matrix4 & scale(const Vector3<T> & _vec);

        /**
         * @brief Rotate this matrix by an angle in radians around the provided axis.
         */
        inline Matrix4 & rotate(T _radians, const Vector3<T> & _axis);

        /**
         * @brief Rotate this matrix by the orientation of a quaternion.
         * @param _quat The quaternion expressing the orientation.
         */
        inline Matrix4 & rotate(const Quaternion<T> & _quat);

        /**
         * @brief Rotate this matrix by the provided euler angles in radians.
         * @param _yaw Angle in radians.
         * @param _pitch Angle in radians.
         * @param _roll Angle in radians.
         */
        inline Matrix4 & rotate(T _yaw, T _pitch, T _roll);

        /**
         * @brief Rotate this matrix by the provided euler angles in radians.
         * @param _euler Vector holding the euler angles in radians.
         */
        inline Matrix4 & rotate(const Vector3<T> & _euler);

        /**
         * @brief Returns a pointer to the memory block of this matrix.
         */
        inline T * ptr();

        /**
         * @brief Returns a pointer to the memory block of this matrix.
         */
        inline const T * ptr() const;

        /**
         * @brief Returns the translation vector of this matrix.
         */
        inline Vector3<T> translation() const;

        /**
         * @brief Returns an identity matrix.
         */
        inline static Matrix4 identity();

        /**
         * @brief Returns a matrix with all elements initialized to zero.
         */
        inline static Matrix4 zero();

        /**
         * @brief Returns a 3D translation matrix.
         */
        inline static Matrix4 translation(const Vector3<T> & _vec);

        /**
         * @brief Returns a 3D translation matrix.
         */
        inline static Matrix4 translation(T _x, T _y, T _z);

        /**
         * @brief Returns a scaling matrix.
         * @param _scale The scaling factor along the three axis.
         */
        inline static Matrix4 scaling(const Vector3<T> & _vec);

        /**
         * @brief Returns a uniform scaling matrix.
         * @param _scale The scaling factor.
         */
        inline static Matrix4 scaling(T _s);

        /**
         * @brief Returns a scaling matrix.
         * @param _x The scaling factor along the x axis.
         * @param _y The scaling factor along the y axis.
         * @param _z The scaling factor along the z axis.
         */
        inline static Matrix4 scaling(T _x, T _y, T _z);

        /**
         * @brief Returns a 3D rotation matrix.
         * @param _radians Angle in radians.
         * @param _axis Rotation axis.
         */
        inline static Matrix4 rotation(T _radians, const Vector3<T> & _axis);

        /**
         * @brief Returns a 3D rotation matrix from a quaternion.
         * @param _quat The quaternion expressing the orientation.
         */
        inline static Matrix4 rotation(const Quaternion<T> & _quat);

        /**
         * @brief Returns a 3D rotation matrix from euler angles.
         * @param _yaw Angle in radians.
         * @param _pitch Angle in radians.
         * @param _roll Angle in radians.
         */
        inline static Matrix4 rotation(T _yaw, T _pitch, T _roll);

        /**
         * @brief Returns a 3D rotation matrix from euler angles.
         * @param _euler Vector holding the euler angles in radians.
         */
        inline static Matrix4 rotation(const Vector3<T> & _euler);

        /**
         * @brief Returns an orthographic projection matrix.
         * @param _left The value for the left clipping plane.
         * @param _right The value for the right clipping plane.
         * @param _bottom The value for the bottom clipping plane.
         * @param _top The value for the top clipping plane.
         * @param _near The value for the near clipping plane.
         * @param _far The value for the far clipping plane.
         */
        inline static Matrix4 ortho(T _left, T _right, T _bottom, T _top, T _near, T _far);

        /**
         * @brief Returns a perspective frustum projection matrix.
         * @param _left The value for the left clipping plane.
         * @param _right The value for the right clipping plane.
         * @param _bottom The value for the bottom clipping plane.
         * @param _top The value for the top clipping plane.
         * @param _near The value for the near clipping plane. Must be positive.
         * @param _far The value for the far clipping plane. Must be positive.
         */
        inline static Matrix4 frustum(T _left, T _right, T _bottom, T _top, T _near, T _far);

        /**
         * @brief Returns a perspective projection matrix.
         * @param _fovy Field of view angle in degrees in the y direction.
         * @param _aspect Specifies the aspect ratio that determines the field of view in the x direction.
         * The aspect ratio is the ratio of x (width) to y (height).
         * @param _near The value for the near clipping plane. Must be positive.
         * @param _far The value for the far clipping plane. Must be positive.
         */
        inline static Matrix4 perspective(T _fovy, T _aspect, T _near, T _far);

        /**
         * @brief Returns a look at viewing transformation matrix.
         * @param _eye Specifies the position of the eye point.
         * @param _center Specifies the position of the reference point.
         * This is the point that the camera is looking at.
         * @param _up Specifies the direction of the up vector.
         */
        inline static Matrix4 lookAt(const Vector3<T> & _eye, const Vector3<T> & _center, const Vector3<T> & _up);

    private:

        Vector4<T> m_col0;
        Vector4<T> m_col1;
        Vector4<T> m_col2;
        Vector4<T> m_col3;
    };

    using Mat4f = Matrix4<stick::Float32>;

    // Constructors
    //____________________________________

    template<class T>
    inline Matrix4<T>::Matrix4()
    {
    }

    template<class T>
    inline Matrix4<T>::Matrix4(T m00, T m10, T m20, T m30,
                               T m01, T m11, T m21, T m31,
                               T m02, T m12, T m22, T m32,
                               T m03, T m13, T m23, T m33 ) :
        m_col0(m00, m01, m02, m03),
        m_col1(m10, m11, m12, m13),
        m_col2(m20, m21, m22, m23),
        m_col3(m30, m31, m32, m33)
    {

    }

    template<class T>
    template<class OT>
    inline Matrix4<T>::Matrix4(const Vector4<OT> & _col0,
                               const Vector4<OT> & _col1,
                               const Vector4<OT> & _col2,
                               const Vector4<OT> & _col3) :
        m_col0(_col0),
        m_col1(_col1),
        m_col2(_col2),
        m_col3(_col3)
    {

    }

    template<class T>
    template<class OT>
    inline Matrix4<T>::Matrix4(const Matrix4<OT> & _mat) :
        m_col0(_mat.m_col0),
        m_col1(_mat.m_col1),
        m_col2(_mat.m_col2),
        m_col3(_mat.m_col3)
    {

    }

    template<class T>
    template<class OT>
    inline Matrix4<T>::Matrix4(const Matrix3<OT> & _mat) :
        m_col0(_mat.m_col0.x, _mat.m_col0.y, _mat.m_col0.z, 0.0),
        m_col1(_mat.m_col1.x, _mat.m_col1.y, _mat.m_col1.z, 0.0),
        m_col2(_mat.m_col2.x, _mat.m_col2.y, _mat.m_col2.z, 0.0),
        m_col3(0.0, 0.0, 0.0, 1.0)
    {

    }

    template<class T>
    template<class OT>
    inline Matrix4<T>::Matrix4(const Matrix3<OT> & _mat, const Vector3<OT> & _translation)
    {
        m_col0 = Vector4<T>(_mat.m_col0.x, _mat.m_col0.y, _mat.m_col0.z, 0.0);
        m_col1 = Vector4<T>(_mat.m_col1.x, _mat.m_col1.y, _mat.m_col1.z, 0.0);
        m_col2 = Vector4<T>(_mat.m_col2.x, _mat.m_col2.y, _mat.m_col2.z, 0.0);
        m_col3 = Vector4<T>(_translation, 1.0);
    }

    template<class T>
    template<class OT>
    inline Matrix4<T>::Matrix4(const Quaternion<OT> & _quat)
    {
        Matrix3<T> mat(_quat);
        m_col0 = Vector4<T>(mat.m_col0.x, mat.m_col0.y, mat.m_col0.z, 0.0);
        m_col1 = Vector4<T>(mat.m_col1.x, mat.m_col1.y, mat.m_col1.z, 0.0);
        m_col2 = Vector4<T>(mat.m_col2.x, mat.m_col2.y, mat.m_col2.z, 0.0);
        m_col3 = Vector4<T>(0.0, 0.0, 0.0, 1.0);
    }

    template<class T>
    template<class OT>
    inline Matrix4<T>::Matrix4(const Quaternion<OT> & _quat, const Vector3<OT> & _translation)
    {
        Matrix3<T> mat(_quat);
        m_col0 = Vector4<T>(mat.m_col0, 0.0);
        m_col1 = Vector4<T>(mat.m_col1, 0.0);
        m_col2 = Vector4<T>(mat.m_col2, 0.0);
        m_col3 = Vector4<T>(_translation, 1.0);
    }

    template<class T>
    inline Matrix4<T>::Matrix4(const T _val)
    {
        m_col0 = Vector4<T>(_val);
        m_col1 = Vector4<T>(_val);
        m_col2 = Vector4<T>(_val);
        m_col3 = Vector4<T>(_val);
    }

    template<class T>
    inline Matrix4<T>::Matrix4(const T * _floatArray)
    {
        std::memcpy(m_col0.ptr(), _floatArray, 16 * sizeof(T));
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::operator = (const Matrix4<T> & _other)
    {
        m_col0 = _other.m_col0;
        m_col1 = _other.m_col1;
        m_col2 = _other.m_col2;
        m_col3 = _other.m_col3;

        return *this;
    }


    // Access
    //____________________________________

    template<class T>
    inline Vector4<T> & Matrix4<T>::operator [](stick::UInt32 _col)
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline const Vector4<T> & Matrix4<T>::operator [](stick::UInt32 _col) const
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline T & Matrix4<T>::element(stick::UInt32 _col, stick::UInt32 _row)
    {
        return this->operator[](_col)[_row];
    }

    template<class T>
    inline const T & Matrix4<T>::element(stick::UInt32 _col, stick::UInt32 _row) const
    {
        return this->operator[](_col)[_row];
    }


    // Boolean
    //____________________________________

    template<class T>
    inline bool Matrix4<T>::operator==(const Matrix4<T> & _mat) const
    {
        if (m_col0 != _mat.m_col0 ||
                m_col1 != _mat.m_col1 ||
                m_col2 != _mat.m_col2 ||
                m_col3 != _mat.m_col3
           )
        {
            return false;
        }

        return true;
    }

    template<class T>
    inline bool Matrix4<T>::operator!=(const Matrix4<T> & _mat) const
    {
        if (m_col0 != _mat.m_col0 ||
                m_col1 != _mat.m_col1 ||
                m_col2 != _mat.m_col2 ||
                m_col3 != _mat.m_col3
           )
        {
            return true;
        }

        return false;
    }


    // Addition / Substraction
    //____________________________________

    template<class T>
    inline Matrix4<T> Matrix4<T>::operator + (const Matrix4<T> & _mat) const
    {
        return Matrix4<T>(
                   m_col0 + _mat.m_col0,
                   m_col1 + _mat.m_col1,
                   m_col2 + _mat.m_col2,
                   m_col3 + _mat.m_col3
               );
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::operator - (const Matrix4<T> & _mat) const
    {
        return Matrix4<T>(
                   m_col0 - _mat.m_col0,
                   m_col1 - _mat.m_col1,
                   m_col2 - _mat.m_col2,
                   m_col3 - _mat.m_col3
               );
    }

    template<class T>
    inline Matrix4<T>  & Matrix4<T>::operator += (const Matrix4<T> & _mat)
    {
        *this = *this + _mat;
        return *this;
    }

    template<class T>
    inline Matrix4<T>  & Matrix4<T>::operator -= (const Matrix4<T> & _mat)
    {
        *this = *this - _mat;
        return *this;
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::operator - () const
    {
        return Matrix4<T>(
                   -m_col0,
                   -m_col1,
                   -m_col2,
                   -m_col3
               );
    }


    // Multiplication
    //____________________________________

    //TODO: Add overloaded operators for matrix multiplication

    template<class T>
    inline Vector3<T> Matrix4<T>::operator*(const Vector3<T> & _vec) const
    {
        return Vector3<T>(_vec.x * m_col0.x + _vec.y * m_col1.x + m_col2.x * _vec.z + m_col3.x,
                          _vec.x * m_col0.y + _vec.y * m_col1.y + m_col2.y * _vec.z + m_col3.y,
                          _vec.x * m_col0.z + _vec.y * m_col1.z + m_col2.z * _vec.z + m_col3.z
                         );
    }


    template<class T>
    inline Vector4<T> Matrix4<T>::operator*(const Vector4<T> & _vec) const
    {
        return Vector4<T>(_vec.x * m_col0.x + _vec.y * m_col1.x + m_col2.x * _vec.z + m_col3.x * _vec.w,
                          _vec.x * m_col0.y + _vec.y * m_col1.y + m_col2.y * _vec.z + m_col3.y * _vec.w,
                          _vec.x * m_col0.z + _vec.y * m_col1.z + m_col2.z * _vec.z + m_col3.z * _vec.w,
                          _vec.x * m_col0.w + _vec.y * m_col1.w + m_col2.w * _vec.z + m_col3.w * _vec.w
                         );
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::operator*(const Matrix4<T> & _mat) const
    {
        return Matrix4<T>(
                   *this * _mat.m_col0,
                   *this * _mat.m_col1,
                   *this * _mat.m_col2,
                   *this * _mat.m_col3
               );
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::operator *= (const Matrix4<T> & _mat)
    {
        *this = *this * _mat;
        return *this;
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::operator*(T _v) const
    {
        return Matrix4<T>(
                   m_col0 * _v,
                   m_col1 * _v,
                   m_col2 * _v,
                   m_col3 * _v
               );
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::operator *= (T _v)
    {
        *this = *this * _v;
        return *this;
    }


    // Non static members to translate / scale / rotate an existing matrix
    //____________________________________

    //@TODO: THESE TRANSLATE IMPLEMENTATIONS ARE WRONG
    // WE NEED TO DO A MATRIX MULTIPLICATION HERE, AT LEAST FOR THE TRANSLATION COLUMN
    template<class T>
    inline Matrix4<T> & Matrix4<T>::translate(T _x, T _y, T _z)
    {
        m_col3.x += _x;
        m_col3.y += _y;
        m_col3.z += _z;
        return *this;
    }

    //@TODO: THESE TRANSLATE IMPLEMENTATIONS ARE WRONG
    // WE NEED TO DO A MATRIX MULTIPLICATION HERE, AT LEAST FOR THE TRANSLATION COLUMN
    template<class T>
    inline Matrix4<T> & Matrix4<T>::translate(const Vector3<T> & _vec)
    {
        m_col3.x += _vec.x;
        m_col3.y += _vec.y;
        m_col3.z += _vec.z;
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::scale(T _s)
    {
        *this *= scaling(_s);
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::scale(T _x, T _y, T _z)
    {
        *this *= scaling(_x, _y, _z);
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::scale(const Vector3<T> & _vec)
    {
        *this *= scaling(_vec);
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::rotate(T _radians, const Vector3<T> & _axis)
    {
        *this *= rotation(_radians, _axis);
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::rotate(const Quaternion<T> & _quat)
    {
        *this *= rotation(_quat);
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::rotate(T _yaw, T _pitch, T _roll)
    {
        *this *= rotation(_yaw, _pitch, _roll);
        return *this;
    }

    template<class T>
    inline Matrix4<T> & Matrix4<T>::rotate(const Vector3<T> & _euler)
    {
        *this *= rotation(_euler);
        return *this;
    }


    //Pointer accessors
    //____________________________________

    template<class T>
    inline T * Matrix4<T>::ptr()
    {
        return &m_col0.x;
    }

    template<class T>
    inline const T * Matrix4<T>::ptr() const
    {
        return &m_col0.x;
    }


    //Getters
    //____________________________________

    template<class T>
    inline Vector3<T> Matrix4<T>::translation() const
    {
        return m_col3;
    }


    //Static helper functions
    //____________________________________

    template<class T>
    inline Matrix4<T> Matrix4<T>::identity()
    {
        return Matrix4<T>(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::zero()
    {
        return Matrix4<T>(0, 0, 0, 0,
                          0, 0, 0, 0,
                          0, 0, 0, 0,
                          0, 0, 0, 0);
    }


    template<class T>
    inline Matrix4<T> Matrix4<T>::translation(const Vector3<T> & _vec)
    {
        return Matrix4<T>(
                   Vector4<T>(1.0, 0.0, 0.0, 0.0),
                   Vector4<T>(0.0, 1.0, 0.0, 0.0),
                   Vector4<T>(0.0, 0.0, 1.0, 0.0),
                   Vector4<T>(_vec.x, _vec.y, _vec.z, 1.0)
               );
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::translation(T _x, T _y, T _z)
    {
        return translation(Vector3<T>(_x, _y, _z));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::scaling(const Vector3<T> & _vec)
    {
        return Matrix4<T>(
                   Vector4<T>(_vec.x, 0.0, 0.0, 0.0),
                   Vector4<T>(0.0, _vec.y, 0.0, 0.0),
                   Vector4<T>(0.0, 0.0, _vec.z, 0.0),
                   Vector4<T>(0.0, 0.0, 0.0, 1.0)
               );
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::scaling(T _s)
    {
        return scaling(Vector3<T>(_s));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::scaling(T _x, T _y, T _z)
    {
        return scaling(Vector3<T>(_x, _y, _z));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::rotation(T _radians, const Vector3<T> & _axis)
    {
        return Matrix4<T>(Matrix3<T>::rotation(_radians, _axis));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::rotation(const Quaternion<T> & _quat)
    {
        return Matrix4<T>(Matrix4<T>::rotation(_quat));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::rotation(T _yaw, T _pitch, T _roll)
    {
        return Matrix4<T>(Matrix4<T>::rotation(_yaw, _pitch, _roll));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::rotation(const Vector3<T> & _euler)
    {
        return Matrix4<T>(Matrix4<T>::rotation(_euler));
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::ortho(T _left, T _right, T _bottom, T _top, T _near, T _far)
    {
        Matrix4<T> ret;

        T a = (T)2.0 / (_right - _left);
        T b = (T)2.0 / (_top - _bottom);
        T c = (T) - 2.0 / (_far - _near);
        T tx = -(_right + _left) / (_right - _left);
        T ty = -(_top + _bottom) / (_top - _bottom);
        T tz = -(_far + _near) / (_far - _near);

        ret = Matrix4<T>(a, 0.0, 0.0, tx,
                         0.0, b, 0.0, ty,
                         0.0, 0.0, c, tz,
                         0.0, 0.0, 0, 1.0
                        );

        return ret;
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::frustum(T _left, T _right, T _bottom, T _top, T _near, T _far)
    {
        Matrix4<T> ret;

        T a = (T)(2.0 * _near) / (_right - _left);
        T b = (T)(2.0 * _near) / (_top - _bottom);
        T c = (_right + _left) / (_right - _left);
        T d = (_top + _bottom) / (_top - _bottom);
        T e = -(_far + _near) / (_far - _near);
        T f = (T)(-2.0 * _far * _near) / (_far - _near);

        ret = Matrix4<T>(a, 0.0, c, 0.0,
                         0.0, b, d, 0.0,
                         0.0, 0.0, e, f,
                         0.0, 0.0, -1.0, 0.0
                        );

        return ret;
    }

    //@TODO Get rid of dynamic array here in favor of a fixed size array
    template<class T>
    stick::DynamicArray<T> frustumPlanesFromPerspective(T _fovy, T _aspect, T _near, T _far)
    {
        T tanFovy = tan(toRadians(_fovy * (T)0.5));
        T height = tanFovy * _near;
        T width = height * _aspect;

        return { -width, width, -height, height, _near, _far};
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::perspective(T _fovy, T _aspect, T _near, T _far)
    {
        Matrix4<T> ret;
        auto fr = frustumPlanesFromPerspective(_fovy, _aspect, _near, _far);
        ret = frustum(fr[0], fr[1], fr[2], fr[3], fr[4], fr[5]);

        return ret;
    }

    template<class T>
    inline Matrix4<T> Matrix4<T>::lookAt(const Vector3<T> & _eye, const Vector3<T> & _center, const Vector3<T> & _up)
    {
        Matrix4<T> ret;

        Vector3<T> f = normalize(_center - _eye);
        Vector3<T> s = normalize(cross(f, _up));
        Vector3<T> u = cross(s, f);

        ret = Matrix4<T>(s.x, s.y, s.z, -dot(s, _eye),
                         u.x, u.y, u.z, -dot(u, _eye),
                         -f.x, -f.y, -f.z, dot(f, _eye),
                         0, 0, 0, 1.0);

        return ret;
    }
}

#endif //CRUNCH_MATRIX4_HPP
