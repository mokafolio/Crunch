#ifndef CRUNCH_MATRIXFUNC_HPP
#define CRUNCH_MATRIXFUNC_HPP

#include <Crunch/GeometricFunc.hpp>
#include <Crunch/Matrix2.hpp>
#include <Crunch/Matrix32.hpp>
#include <Crunch/Matrix4.hpp>

#ifdef minor
#undef minor
#endif

namespace crunch
{
/**
 * @brief Calculates the transpose of a matrix.
 *
 * http://en.wikipedia.org/wiki/Transpose
 */
template <class T>
inline Matrix2<T> transpose(const Matrix2<T> & _mat)
{
    return Matrix2<T>(Vector2<T>(_mat[0].x, _mat[1].x), Vector2<T>(_mat[0].y, _mat[1].y));
}

/**
 * @brief Calculates the transpose of a matrix.
 *
 * http://en.wikipedia.org/wiki/Transpose
 */
template <class T>
inline Matrix3<T> transpose(const Matrix3<T> & _mat)
{
    return Matrix3<T>(Vector3<T>(_mat[0].x, _mat[1].x, _mat[2].x),
                      Vector3<T>(_mat[0].y, _mat[1].y, _mat[2].y),
                      Vector3<T>(_mat[0].z, _mat[1].z, _mat[2].z));
}

/**
 * @brief Calculates the transpose of a matrix.
 *
 * http://en.wikipedia.org/wiki/Transpose
 */
template <class T>
inline Matrix4<T> transpose(const Matrix4<T> & _mat)
{
    return Matrix4<T>(Vector4<T>(_mat[0].x, _mat[1].x, _mat[2].x, _mat[3].x),
                      Vector4<T>(_mat[0].y, _mat[1].y, _mat[2].y, _mat[3].y),
                      Vector4<T>(_mat[0].z, _mat[1].z, _mat[2].z, _mat[3].z),
                      Vector4<T>(_mat[0].w, _mat[1].w, _mat[2].w, _mat[3].w));
}

/**
 * @brief Calculates the minor of the requested elements of the input matrix.
 *
 * A minor is the determinant of a smaller matrix within a matrix.
 * http://en.wikipedia.org/wiki/Minor_(linear_algebra)
 */
template <class T>
inline T minor(const Matrix3<T> & _mat,
               stick::UInt32 _col0,
               stick::UInt32 _col1,
               stick::UInt32 _row0,
               stick::UInt32 _row1)
{
    return _mat.element(_col0, _row0) * _mat.element(_col1, _row1) -
           _mat.element(_col1, _row0) * _mat.element(_col0, _row1);
}

/**
 * @brief Calculates the minor of the requested elements of the input matrix.
 *
 * A minor is the determinant of a smaller matrix within a matrix.
 * http://en.wikipedia.org/wiki/Minor_(linear_algebra)
 */
template <class T>
inline T minor(const Matrix4<T> & _mat,
               stick::UInt32 _col0,
               stick::UInt32 _col1,
               stick::UInt32 _col2,
               stick::UInt32 _row0,
               stick::UInt32 _row1,
               stick::UInt32 _row2)
{

    return _mat.element(_col0, _row0) * (_mat.element(_col1, _row1) * _mat.element(_col2, _row2) -
                                         _mat.element(_col1, _row2) * _mat.element(_col2, _row1)) -
           _mat.element(_col1, _row0) * (_mat.element(_col0, _row1) * _mat.element(_col2, _row2) -
                                         _mat.element(_col0, _row2) * _mat.element(_col2, _row1)) +
           _mat.element(_col2, _row0) * (_mat.element(_col0, _row1) * _mat.element(_col1, _row2) -
                                         _mat.element(_col0, _row2) * _mat.element(_col1, _row1));
}

/**
 * @brief Calculates the determinant of a matrix.
 *
 * http://en.wikipedia.org/wiki/Determinant
 */
template <class T>
inline T determinant(const Matrix2<T> & _mat)
{
    return _mat[0].x * _mat[1].y - _mat[1].x * _mat[0].y;
}

/**
 * @brief Calculates the determinant of a matrix.
 *
 * http://en.wikipedia.org/wiki/Determinant
 */
template <class T>
inline T determinant(const Matrix3<T> & _mat)
{
    return _mat.element(0, 0) * minor(_mat, 1, 2, 1, 2) -
           _mat.element(1, 0) * minor(_mat, 0, 2, 1, 2) +
           _mat.element(2, 0) * minor(_mat, 0, 1, 1, 2);
}

/**
 * @brief Calculates the determinant of a matrix.
 *
 * http://en.wikipedia.org/wiki/Determinant
 */
template <class T>
inline T determinant(const Matrix4<T> & _mat)
{
    return _mat.element(0, 0) * minor(_mat, 1, 2, 3, 1, 2, 3) -
           _mat.element(1, 0) * minor(_mat, 0, 2, 3, 1, 2, 3) +
           _mat.element(2, 0) * minor(_mat, 0, 1, 3, 1, 2, 3) -
           _mat.element(3, 0) * minor(_mat, 0, 1, 2, 1, 2, 3);
}

/**
 * @brief Calculates the adjoint matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Adjugate_matrix
 */
template <class T>
inline Matrix2<T> adjoint(const Matrix2<T> & _mat)
{
    return Matrix2<T>(_mat[1].y, -_mat[1].x, -_mat[0].y, _mat[0].x);
}

/**
 * @brief Calculates the adjoint matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Adjugate_matrix
 */
template <class T>
inline Matrix3<T> adjoint(const Matrix3<T> & _mat)
{
    return Matrix3<T>(minor(_mat, 1, 2, 1, 2),
                      -minor(_mat, 1, 2, 0, 2),
                      minor(_mat, 1, 2, 0, 1),

                      -minor(_mat, 0, 2, 1, 2),
                      minor(_mat, 0, 2, 0, 2),
                      -minor(_mat, 0, 2, 0, 1),

                      minor(_mat, 0, 1, 1, 2),
                      -minor(_mat, 0, 1, 0, 2),
                      minor(_mat, 0, 1, 0, 1));
}

/**
 * @brief Calculates the adjoint matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Adjugate_matrix
 */
template <class T>
inline Matrix4<T> adjoint(const Matrix4<T> & _mat)
{
    return Matrix4<T>(minor(_mat, 1, 2, 3, 1, 2, 3),
                      -minor(_mat, 1, 2, 3, 0, 2, 3),
                      minor(_mat, 1, 2, 3, 0, 1, 3),
                      -minor(_mat, 1, 2, 3, 0, 1, 2),

                      -minor(_mat, 0, 2, 3, 1, 2, 3),
                      minor(_mat, 0, 2, 3, 0, 2, 3),
                      -minor(_mat, 0, 2, 3, 0, 1, 3),
                      minor(_mat, 0, 2, 3, 0, 1, 2),

                      minor(_mat, 0, 1, 3, 1, 2, 3),
                      -minor(_mat, 0, 1, 3, 0, 2, 3),
                      minor(_mat, 0, 1, 3, 0, 1, 3),
                      -minor(_mat, 0, 1, 3, 0, 1, 2),

                      -minor(_mat, 0, 1, 2, 1, 2, 3),
                      minor(_mat, 0, 1, 2, 0, 2, 3),
                      -minor(_mat, 0, 1, 2, 0, 1, 3),
                      minor(_mat, 0, 1, 2, 0, 1, 2));
}

/**
 * @brief Calculates the inverse matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Invertible_matrix
 */
template <class T>
inline Matrix2<T> inverse(const Matrix2<T> & _mat)
{
    return adjoint(_mat) * (T(1.0) / determinant(_mat));
}

/**
 * @brief Calculates the inverse matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Invertible_matrix
 */
template <class T>
inline Matrix32<T> inverse(const Matrix32<T> & _mat)
{
    Matrix2<T> tmp = inverse(Matrix2<T>(_mat[0], _mat[1]));
    return Matrix32<T>(tmp[0], tmp[1], tmp * -_mat[2]);
}

/**
 * @brief Calculates the inverse matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Invertible_matrix
 */
template <class T>
inline Matrix3<T> inverse(const Matrix3<T> & _mat)
{
    return adjoint(_mat) * (T(1.0) / determinant(_mat));
}

/**
 * @brief Calculates the inverse matrix of the input matrix.
 *
 * http://en.wikipedia.org/wiki/Invertible_matrix
 */
template <class T>
inline Matrix4<T> inverse(const Matrix4<T> & _mat)
{
    return adjoint(_mat) * (T(1.0) / determinant(_mat));
}

/**
 * @brief Decomposes the 2D input matrix
 *
 *
 * @param _mat The matrix to decompose.
 * @param _outTranslation Will hold the translation of the input matrix.
 * @param _outRotation Will hold the rotation of the input matrix.
 * @param _outScale Will hold the scale of the input matrix.
 */
template <class T>
inline void decompose(const Matrix3<T> & _mat,
                      Vector2<T> & _outTranslation,
                      T & _outRotation,
                      Vector2<T> & _outScale)
{
    //@TODO: this should be a more involved implementation (see the Mat32 implementation below)
    _outTranslation = _mat[2];

    T a = _mat.element(0, 0);
    T b = _mat.element(1, 0);
    T c = _mat.element(0, 1);
    T d = _mat.element(1, 1);

    _outScale = Vector2<T>(crunch::sqrt(a * a + b * b), crunch::sqrt(c * c + d * d));

    _outRotation = -atan2(b, a);
}

/**
 * @brief Decomposes the 2D input matrix
 *
 *
 * @param _mat The matrix to decompose.
 * @param _outTranslation Will hold the translation of the input matrix.
 * @param _outRotation Will hold the rotation of the input matrix.
 * @param _outSkew Will hold the skew of the input matrix.
 * @param _outScale Will hold the scale of the input matrix.
 */
template <class T>
inline void decompose(const Matrix32<T> & _mat,
                      Vector2<T> & _outTranslation,
                      T & _outRotation,
                      Vector2<T> & _outSkew,
                      Vector2<T> & _outScale)
{
    _outTranslation = _mat[2];

    T a = _mat.element(0, 0);
    T b = _mat.element(1, 0);
    T c = _mat.element(0, 1);
    T d = _mat.element(1, 1);

    T det = a * d - b * c;

    if (a != 0 || b != 0)
    {
        T r = std::sqrt(a * a + b * b);
        _outRotation = std::acos(a / r) * (b > 0 ? 1 : -1);
        _outScale.x = r;
        _outScale.y = det / r;
        _outSkew.x = std::atan2(a * c + b * d, r * r);
        _outSkew.y = 0;
    }
    else if (c != 0 || d != 0)
    {
        T s = std::sqrt(c * c + d * d);
        _outRotation = std::asin(c / s) * (d > 0 ? 1 : -1);
        _outScale.x = det / s;
        _outScale.y = s;
        _outSkew.x = 0;
        _outSkew.y = std::atan2(a * c + b * d, s * s);
    }
    else /* a = b = c = d = 0 */
    {
        _outRotation = 0;
        _outScale.x = 0;
        _outScale.y = 0;
        _outSkew.x = 0;
        _outSkew.y = 0;
    }

    _outRotation = -atan2(b, a);
}

/**
 * @brief Builds a 3D 4x4 Matrix from a 2D 3x3 Matrix.
 *
 * This is useful if you have your transformations for 2D code stored in 3x3/3x2 matrices,
 * but need 4x4 matrices for rendering (i.e. when using openGL).
 *
 * NOTE: I think these should move to Matrix4 class as one of the static helper functions.
 */
template <class T>
inline Matrix4<T> to3DTransform(const Matrix32<T> & _mat)
{
    return Matrix4<T>(Vector4<T>(_mat[0].x, _mat[0].y, 0, 0),
                      Vector4<T>(_mat[1].x, _mat[1].y, 0, 0),
                      Vector4<T>(0, 0, 1, 0),
                      Vector4<T>(_mat[2].x, _mat[2].y, 0, 1));
}

template <class T>
inline Matrix4<T> to3DTransform(const Matrix3<T> & _mat)
{
    Matrix4<T> ret(_mat);
    ret[2] = Vector4<T>(0, 0, 1, 0);
    ret[3] = Vector4<T>(_mat[2].x, _mat[2].y, 0.0, 1.0);
    return ret;
}
} // namespace crunch

#endif // CRUNCH_MATRIXFUNC_HPP