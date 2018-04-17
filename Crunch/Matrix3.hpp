#ifndef CRUNCH_MATRIX3_HPP
#define CRUNCH_MATRIX3_HPP

#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>
#include <Crunch/Quaternion.hpp>
#include <Crunch/QuaternionFunc.hpp>
#include <Crunch/TrigonometryFunc.hpp>
#include <cstring> //for memcpy


namespace crunch
{
    template <class T>
    class Matrix4;

    /**
     * @brief A 3x3 matrix class.
     *
     * The matrix has a column major memory layout.
     * The matrix uses column major notation (meaning vectors are treated like columns when multiplied, like OpenGL),
     * meaning that matrix multiplication works exactly like it does in OpenGL/GLSL.
     *
     * @arg T The value type of the matrix (i.e. stick::Float32)
     */
    template <class T>
    class Matrix3
    {
        template<class TF>
        friend class Matrix4;

    public:

        /**
         * @brief The internal value type.
         */
        typedef T ValueType;

        /**
         * @brief Default Constructor. Does nothing for speed.
         */
        inline Matrix3();

        /**
         * @brief Constructs a Matrix from the provided column vectors.
         */
        template<class OT>
        inline Matrix3(const Vector3<OT> & _col0,   //column0
                       const Vector3<OT> & _col1,   //column1
                       const Vector3<OT> & _col2);  //column2

        /**
         * @brief Constructs a Matrix from the provided numbers.
         */
        inline Matrix3(T _col00, T _col10, T _col20,
                       T _col01, T _col11, T _col21,
                       T _col02, T _col12, T _col22);

        /**
         * @brief Copy constructs a matrix from another one.
         */
        template<class OT>
        inline Matrix3(const Matrix3<OT> & _mat);

        /**
         * @brief Extracts a 3x3 Matrix from the provided 4x4 one.
         */
        template<class OT>
        inline Matrix3(const Matrix4<OT> & _mat);

        /**
         * @brief Creates a rotation matrix from a unit length quaternion.
         */
        template<class OT>
        inline Matrix3(const Quaternion<OT> & _quat);

        /**
         * @brief Constructs a matrix with all elements initialized to the provided number.
         */
        explicit inline Matrix3(const T _val);

        /**
         * @brief Constructs a matrix from the provided c array.
         *
         * Note: Remember, column major memory layout.
         */
        explicit inline Matrix3(const T * _floatArray);

        /**
         * @brief Assign another matrix to this.
         */
        inline Matrix3 & operator = (const Matrix3<T> & _other);

        /**
         * @brief Access a column vector of the matrix.
         * @param _col The column index.
         * @return A reference to the column vector.
         */
        inline Vector3<T> & operator [](stick::UInt32 _col);

        /**
         * @brief Access a column vector of the matrix.
         * @param _col The column index.
         * @return A const reference to the column vector.
         */
        inline const Vector3<T> & operator [](stick::UInt32 _col) const;

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
        inline bool operator == (const Matrix3<T> & _mat) const;

        /**
         * @brief Returns true if this matrix and the provided matrix are not identical.
         */
        inline bool operator != (const Matrix3<T> & _mat) const;

        /**
         * @brief Adds two matrices.
         */
        inline Matrix3 operator + (const Matrix3<T> & _mat) const;

        /**
         * @brief Subtracts two matrices.
         */
        inline Matrix3 operator - (const Matrix3<T> & _mat) const;

        /**
         * @brief Adds another matrix to this matrix.
         */
        inline Matrix3 & operator += (const Matrix3<T> & _mat);

        /**
         * @brief Subtracts another matrix from this matrix.
         */
        inline Matrix3 & operator -= (const Matrix3<T> & _mat);

        /**
         * @brief Negates this matrix.
         */
        inline Matrix3 operator - () const;

        /**
         * @brief Multiplies two matrices.
         */
        inline Matrix3 operator * (const Matrix3<T> & _mat) const;

        /**
         * @brief Multiplies all elements in a matrix with the provided number.
         */
        inline Matrix3 operator * (T _v) const;

        /**
         * @brief Multiplies a matrix with a column 2D vector.
         *
         * This will set the z element of the provided 2D vector to 1.0 for the multiplication.
         */
        inline Vector2<T> operator * (const Vector2<T> & _vec) const;

        /**
         * @brief Multiplies a matrix with a column vector.
         */
        inline Vector3<T> operator * (const Vector3<T> & _vec) const;

        /**
         * @brief Multiplies this matrix with another matrix.
         */
        inline Matrix3 & operator *= (const Matrix3<T> & _mat);

        /**
         * @brief Multiplies all elements in this matrix with the provided number.
         */
        inline Matrix3 & operator *= (T _v);

        /**
         * @brief Translate this matrix in 2D.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & translate2D(T _x, T _y);

        /**
         * @brief Translate this matrix in 2D.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & translate2D(const Vector2<T> & _vec);

        /**
         * @brief Scales this matrix in 2D.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & scale2D(T _s);

        /**
         * @brief Scales this matrix in 2D.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & scale2D(T _x, T _y);

        /**
         * @brief Scales this matrix in 2D.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & scale2D(const Vector2<T> & _scale);

        /**
         * @brief Rotate this matrix in 2D by an angle in radians.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & rotate2D(T _radians);

        /**
         * @brief Skew this matrix in 2D.
         *
         * Note: This operation only yiels meaningful results if this is a 2D matrix
         * (i.e. the upper left 2x2 is the 2D transformation and the third column translation)
         */
        inline Matrix3 & skew2D(T _radiansX, T _radiansY);

        /**
         * @brief Scale this matrix in 3D.
         * @param _s Uniform scaling factor.
         */
        inline Matrix3 & scale(T _s);

        /**
         * @brief Scale this matrix in 3D.
         * @param _x The scaling factor along the x axis.
         * @param _y The scaling factor along the y axis.
         * @param _z The scaling factor along the z axis.
         */
        inline Matrix3 & scale(T _x, T _y, T _z);

        /**
         * @brief Scale this matrix in 3D.
         * @param _vec The scaling factors along the three axis.
         */
        inline Matrix3 & scale(const Vector3<T> & _vec);

        /**
         * @brief Rotate this matrix by an angle in radians around the provided axis.
         */
        inline Matrix3 & rotate(T _radians, const Vector3<T> & _axis);

        /**
         * @brief Rotate this matrix by the orientation of a quaternion.
         * @param _quat The quaternion expressing the orientation.
         */
        inline Matrix3 & rotate(const Quaternion<T> & _quat);

        /**
         * @brief Rotate this matrix by the provided euler angles in radians.
         * @param _yaw Angle in radians.
         * @param _pitch Angle in radians.
         * @param _roll Angle in radians.
         */
        inline Matrix3 & rotate(T _yaw, T _pitch, T _roll);

        /**
         * @brief Rotate this matrix by the provided euler angles in radians.
         * @param _euler Vector holding the euler angles in radians.
         */
        inline Matrix3 & rotate(const Vector3<T> & _euler);

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
        static inline Matrix3 identity();

        /**
         * @brief Returns a matrix with all elements initialized to zero.
         */
        static inline Matrix3 zero();

        /**
         * @brief Returns a 2D translation matrix.
         */
        inline static Matrix3 translation2D(const Vector2<T> & _vec);

        /**
         * @brief Returns a 2D translation matrix.
         */
        inline static Matrix3 translation2D(T _x, T _y);

        /**
         * @brief Returns a 3D rotation matrix.
         * @param _radians Angle in radians.
         * @param _axis Rotation axis.
         */
        static inline Matrix3 rotation(T _radians, const Vector3<T> & _axis = Vector3<T>(0, 0, 1));

        /**
         * @brief Returns a 3D rotation matrix from euler angles.
         * @param _yaw Angle in radians.
         * @param _pitch Angle in radians.
         * @param _roll Angle in radians.
         */
        static inline Matrix3 rotation(T _yaw, T _pitch, T _roll);

        /**
         * @brief Returns a 3D rotation matrix from euler angles.
         * @param _euler Vector holding the euler angles in radians.
         */
        static inline Matrix3 rotation(const Vector3<T> & _angles);

        /**
         * @brief Returns a 3D rotation matrix from a quaternion.
         * @param _quat The quaternion expressing the orientation.
         */
        static inline Matrix3 rotation(const Quaternion<T> & _quat);

        /**
         * @brief Returns a 2D rotation matrix.
         * @param _angle The angle in radians.
         */
        static inline Matrix3 rotation2D(T _angle);

        /**
         * @brief Returns a 2D skew matrix.
         */
        static inline Matrix3 skewMatrix2D(T _radiansX, T _radiansY);

        /**
        * @brief Returns a 2D skew matrix.
        */
        static inline Matrix3 skewMatrix2D(const Vector2<T> & _rads);

        /**
         * @brief Returns a uniform scaling matrix.
         * @param _scale The scaling factor.
         */
        static inline Matrix3 scaling(T _scale);

        /**
         * @brief Returns a scaling matrix.
         * @param _scale The scaling factor along the three axis.
         */
        static inline Matrix3 scaling(const Vector3<T> & _scale);

        /**
         * @brief Returns a scaling matrix.
         * @param _x The scaling factor along the x axis.
         * @param _y The scaling factor along the y axis.
         * @param _z The scaling factor along the z axis.
         */
        static inline Matrix3 scaling(T _x, T _y, T _z);


        /**
         * @brief Returns a 2D scaling matrix.
         * @param _s The scaling factor along the xy axis.
         */
        static inline Matrix3 scaling2D(const Vector2<T> & _s);

        /**
         * @brief Returns a 2D scaling matrix.
         * @param _x The scaling factor along the x axis.
         * @param _y The scaling factor along the y axis.
         */
        static inline Matrix3 scaling2D(T _x, T _y);


        /**
         * @brief Returns a 2D scaling matrix.
         * @param _s The scaling factor along the xy axis.
         */
        static inline Matrix3 scaling2D(T _s);


    private:

        Vector3<T> m_col0;
        Vector3<T> m_col1;
        Vector3<T> m_col2;
    };

    using Mat3f = Matrix3<stick::Float32>;

    // Constructors
    //____________________________________

    template<class T>
    inline Matrix3<T>::Matrix3()
    {
    }

    template<class T>
    template<class OT>
    inline Matrix3<T>::Matrix3(const Vector3<OT> & _col0,
                               const Vector3<OT> & _col1,
                               const Vector3<OT> & _col2) :
        m_col0(_col0),
        m_col1(_col1),
        m_col2(_col2)
    {

    }

    template<class T>
    inline Matrix3<T>::Matrix3(T _col00, T _col10, T _col20,
                               T _col01, T _col11, T _col21,
                               T _col02, T _col12, T _col22) :
        m_col0(_col00, _col01, _col02),
        m_col1(_col10, _col11, _col12),
        m_col2(_col20, _col21, _col22)
    {

    }


    template<class T>
    template<class OT>
    inline Matrix3<T>::Matrix3(const Matrix3<OT> & _mat)
    {
        m_col0 = _mat.m_col0;
        m_col1 = _mat.m_col1;
        m_col2 = _mat.m_col2;
    }

    template<class T>
    template<class OT>
    inline Matrix3<T>::Matrix3(const Matrix4<OT> & _mat)
    {
        m_col0 = _mat[0];
        m_col1 = _mat[1];
        m_col2 = _mat[2];
    }

    template<class T>
    template<class OT>
    inline Matrix3<T>::Matrix3(const Quaternion<OT> & _quat)
    {
        *this = rotation(_quat);
    }

    template<class T>
    inline Matrix3<T>::Matrix3(const T _val)
    {
        m_col0 = Vector3<T>(_val);
        m_col1 = Vector3<T>(_val);
        m_col2 = Vector3<T>(_val);
    }

    template<class T>
    inline Matrix3<T>::Matrix3(const T * _floatArray)
    {
        std::memcpy(m_col0.ptr(), _floatArray, 9 * sizeof(T));
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::operator = (const Matrix3<T> & _other)
    {
        m_col0 = _other.m_col0;
        m_col1 = _other.m_col1;
        m_col2 = _other.m_col2;

        return *this;
    }



    // Access
    //____________________________________

    template<class T>
    inline Vector3<T> & Matrix3<T>::operator [](stick::UInt32 _col)
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline const Vector3<T> & Matrix3<T>::operator [](stick::UInt32 _col) const
    {
        return *(&m_col0 + _col);
    }

    template<class T>
    inline T & Matrix3<T>::element(stick::UInt32 _col, stick::UInt32 _row)
    {
        return this->operator[](_col)[_row];
    }

    template<class T>
    inline const T & Matrix3<T>::element(stick::UInt32 _col, stick::UInt32 _row) const
    {
        return this->operator[](_col)[_row];
    }


    // Boolean
    //____________________________________

    template<class T>
    inline bool Matrix3<T>::operator == (const Matrix3<T> & _mat) const
    {
        if (m_col0 != _mat.m_col0 ||
                m_col1 != _mat.m_col1 ||
                m_col2 != _mat.m_col2  )
        {
            return false;
        }

        return true;
    }

    template<class T>
    inline bool Matrix3<T>::operator != (const Matrix3<T> & _mat) const
    {
        if (m_col0 != _mat.m_col0 ||
                m_col1 != _mat.m_col1 ||
                m_col2 != _mat.m_col2  )
        {
            return true;
        }

        return false;
    }


    // Addition / Substraction
    //____________________________________

    template<class T>
    inline Matrix3<T> Matrix3<T>::operator + (const Matrix3<T> & _mat) const
    {
        return Matrix3<T>(
                   m_col0 + _mat.m_col0,
                   m_col1 + _mat.m_col1,
                   m_col2 + _mat.m_col2
               );
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::operator - (const Matrix3<T> & _mat) const
    {
        return Matrix3<T>(
                   m_col0 - _mat.m_col0,
                   m_col1 - _mat.m_col1,
                   m_col2 - _mat.m_col2
               );
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::operator += (const Matrix3<T> & _mat)
    {
        *this = *this + _mat;
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::operator -= (const Matrix3<T> & _mat)
    {
        *this = *this - _mat;
        return *this;
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::operator - () const
    {
        return Matrix3<T>(
                   -m_col0,
                   -m_col1,
                   -m_col2
               );
    }


    // Multiplication
    //____________________________________

    template<class T>
    inline Vector2<T> Matrix3<T>::operator * (const Vector2<T> & _vec) const
    {
        return *this * Vector3<T>(_vec.x, _vec.y, 1.0);
    }

    template<class T>
    inline Vector3<T> Matrix3<T>::operator * (const Vector3<T> & _vec) const
    {
        Vector3<T> ret;

        ret.x = _vec.x * m_col0.x + _vec.y * m_col1.x + _vec.z * m_col2.x;
        ret.y = _vec.x * m_col0.y + _vec.y * m_col1.y + _vec.z * m_col2.y;
        ret.z = _vec.x * m_col0.z + _vec.y * m_col1.z + _vec.z * m_col2.z;

        return ret;
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::operator * (const Matrix3<T> & _mat) const
    {
        return Matrix3<T>(
                   *this * _mat.m_col0,
                   *this * _mat.m_col1,
                   *this * _mat.m_col2
               );
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::operator *= (const Matrix3<T> & _mat)
    {
        *this = *this * _mat;
        return *this;
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::operator * (T _v) const
    {
        return Matrix3<T>(
                   m_col0 * _v,
                   m_col1 * _v,
                   m_col2 * _v
               );
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::operator *= (T _v)
    {
        *this = *this * _v;
        return *this;
    }


    // Non static members to scale / rotate an existing matrix
    //____________________________________

    template<class T>
    inline Matrix3<T> & Matrix3<T>::translate2D(T _x, T _y)
    {
        return translate2D(Vector2<T>(_x, _y));
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::translate2D(const Vector2<T> & _vec)
    {
        m_col2 = m_col0 * _vec.x + m_col1 * _vec.y + m_col2;
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::scale2D(T _s)
    {
        return scale(Vector3<T>(_s, _s, 1.0));
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::scale2D(T _x, T _y)
    {
        return scale(Vector3<T>(_x, _y, 1.0));
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::scale2D(const Vector2<T> & _scale)
    {
        return scale(Vector3<T>(_scale.x, _scale.y, 1.0));
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::rotate2D(T _radians)
    {
        *this *= rotation2D(_radians);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::skew2D(T _radiansX, T _radiansY)
    {
        *this *= skewMatrix2D(_radiansX, _radiansY);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::scale(T _s)
    {
        *this *= scaling(_s);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::scale(T _x, T _y, T _z)
    {
        *this *= scaling(Vector3<T>(_x, _y, _z));
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::scale(const Vector3<T> & _vec)
    {
        *this *= scaling(_vec);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::rotate(T _radians, const Vector3<T> & _axis)
    {
        *this *= rotation(_radians, _axis);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::rotate(const Quaternion<T> & _quat)
    {
        *this *= rotation(_quat);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::rotate(T _yaw, T _pitch, T _roll)
    {
        *this *= rotation(_yaw, _pitch, _roll);
        return *this;
    }

    template<class T>
    inline Matrix3<T> & Matrix3<T>::rotate(const Vector3<T> & _euler)
    {
        *this *= rotation(_euler);
        return *this;
    }


    //Pointer accessors
    //____________________________________

    template<class T>
    inline T * Matrix3<T>::ptr()
    {
        return &m_col0.x;
    }

    template<class T>
    inline const T * Matrix3<T>::ptr() const
    {
        return &m_col0.x;
    }


    //Static helper functions
    //____________________________________

    template<class T>
    inline Matrix3<T> Matrix3<T>::identity()
    {
        return Matrix3<T>(1, 0, 0,
                          0, 1, 0,
                          0, 0, 1);
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::zero()
    {
        return Matrix3<T>(0, 0, 0,
                          0, 0, 0,
                          0, 0, 0);
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::translation2D(const Vector2<T> & _vec)
    {
        return Matrix3<T>(
                   Vector3<T>(1.0, 0.0, 0.0),
                   Vector3<T>(0.0, 1.0, 0.0),
                   Vector3<T>(_vec.x, _vec.y, 1.0)
               );
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::translation2D(T _x, T _y)
    {
        return Matrix3<T>(
                   Vector3<T>(1.0, 0.0, 0.0),
                   Vector3<T>(0.0, 1.0, 0.0),
                   Vector3<T>(_x, _y, 1.0)
               );
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::rotation(T _radians, const Vector3<T> & _axis)
    {
        T c = std::cos(_radians);
        T s = std::sin(_radians);
        T C = T(1.0) - c;
        T xs = _axis.x * s;
        T ys = _axis.y * s;
        T zs = _axis.z * s;
        T xC = _axis.x * C;
        T yC = _axis.y * C;
        T zC = _axis.z * C;
        T xyC = _axis.x * yC;
        T yzC = _axis.y * zC;
        T zxC = _axis.z * xC;

        return Matrix3<T>(
                   Vector3<T>(_axis.x * xC + c, xyC + zs, zxC - ys),
                   Vector3<T>(xyC - zs, _axis.y * yC + c, yzC + xs),
                   Vector3<T>(zxC + ys, yzC - xs, _axis.z * zC + c)
               );
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::rotation(T _yaw, T _pitch, T _roll)
    {
        T ch = std::cos(_yaw);   //heading
        T sh = std::sin(_yaw);   //heading
        T ca = std::cos(_pitch); //attitude
        T sa = std::sin(_pitch); //attitude
        T cb = std::cos(_roll);  //bank
        T sb = std::sin(_roll);  //bank

        return Matrix3<T>(
                   Vector3<T>(ch * ca, sa, - sh * ca),
                   Vector3<T>(sh * sb - ch * sa * cb, ca * cb, sh * sa * cb + ch * sb),
                   Vector3<T>(ch * sa * sb + sh * cb, - ca * sb, - sh * sa * sb + ch * cb)
               );
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::rotation(const Vector3<T> & _angles)
    {
        return rotation(_angles.x, _angles.y, _angles.z);
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::rotation(const Quaternion<T> & _quat)
    {
        T qx2 = (_quat.x + _quat.x);
        T qy2 = (_quat.y + _quat.y);
        T qz2 = (_quat.z + _quat.z);

        T vxx = _quat.x * qx2;
        T vxy = _quat.x * qy2;
        T vxz = _quat.x * qz2;
        T vxw = _quat.w * qx2;

        T vyy = _quat.y * qy2;
        T vyz = _quat.y * qz2;
        T vyw = _quat.w * qy2;

        T vzz = _quat.z * qz2;
        T vzw = _quat.w * qz2;

        return Matrix3<T>(
                   Vector3<T>(T(1.0) - vyy - vzz, vxy + vzw, vxz - vyw),
                   Vector3<T>(vxy - vzw, T(1.0) - vxx - vzz, vyz + vxw),
                   Vector3<T>(vxz + vyw, vyz - vxw, T(1.0) - vxx - vyy)
               );
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::rotation2D(T _angle)
    {
        T c = std::cos(_angle);
        T s = std::sin(_angle);
        return Matrix3<T>(Vector3<T>(c, s, 0),
                          Vector3<T>(-s, c, 0),
                          Vector3<T>(0, 0, 1));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::skewMatrix2D(T _radiansX, T _radiansY)
    {
        return Matrix3<T>(Vector3<T>(1, std::tan(_radiansY), 0),
                          Vector3<T>(std::tan(_radiansX), 1, 0),
                          Vector3<T>(0, 0, 1));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::skewMatrix2D(const Vector2<T> & _rads)
    {
        return skewMatrix2D(_rads.x, _rads.y);
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::scaling(const Vector3<T> & _scale)
    {
        return Matrix3<T>(Vector3<T>(_scale.x, T(0.0), T(0.0)),
                          Vector3<T>(T(0.0), _scale.y, T(0.0)),
                          Vector3<T>(T(0.0), T(0.0), _scale.z));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::scaling(T _scale)
    {
        return scaling(Vector3<T>(_scale));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::scaling(T _x, T _y, T _z)
    {
        return scaling(Vector3<T>(_x, _y, _z));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::scaling2D(const Vector2<T> & _s)
    {
        return scaling(Vector3<T>(_s.x, _s.y, 1.0));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::scaling2D(T _x, T _y)
    {
        return scaling2D(Vector2<T>(_x, _y));
    }

    template<class T>
    inline Matrix3<T> Matrix3<T>::scaling2D(T _s)
    {
        return scaling2D(Vector2<T>(_s));
    }
}

#endif //CRUNCH_MATRIX3_HPP