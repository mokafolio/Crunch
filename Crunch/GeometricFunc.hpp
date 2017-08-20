#ifndef CRUNCH_GEOMETRICFUNC_HPP
#define CRUNCH_GEOMETRICFUNC_HPP

#include <cmath>
#include <Crunch/Constants.hpp>
#include <Crunch/CommonFunc.hpp>

namespace crunch
{
    /**
     * @brief Returns the length/magnitude of the provided vector.
     */
    template<class T>
    inline T length(const Vector2<T> & _vec)
    {
        return sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
    }

    /**
     * @brief Returns the length/magnitude of the provided vector.
     */
    template<class T>
    inline T length(const Vector3<T> & _vec)
    {
        return sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z);
    }

    /**
     * @brief Returns the length/magnitude of the provided vector.
     */
    template<class T>
    inline T length(const Vector4<T> & _vec)
    {
        return sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z + _vec.w * _vec.w);
    }

    /**
     * @brief Returns the squared length/magnitude of the provided vector.
     */
    template<class T>
    inline T lengthSquared(const Vector2<T> & _vec)
    {
        return _vec.x * _vec.x + _vec.y * _vec.y;
    }

    /**
     * @brief Returns the squared length/magnitude of the provided vector.
     */
    template<class T>
    inline T lengthSquared(const Vector3<T> & _vec)
    {
        return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
    }

    /**
     * @brief Returns the squared length/magnitude of the provided vector.
     */
    template<class T>
    inline T lengthSquared(const Vector4<T> & _vec)
    {
        return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z + _vec.w * _vec.w;
    }

    /**
     * @brief Returns the distance between the two provided vectors.
     */
    template<class T>
    inline T distance(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        return length(_a - _b);
    }

    /**
     * @brief Returns the distance between the two provided vectors.
     */
    template<class T>
    inline T distance(const Vector3<T> & _a, const Vector3<T> & _b)
    {
        return length(_a - _b);
    }

    /**
     * @brief Returns the distance between the two provided vectors.
     */
    template<class T>
    inline T distance(const Vector4<T> & _a, const Vector4<T> & _b)
    {
        return length(_a - _b);
    }

    /**
     * @brief Returns the squared distance between the two provided vectors.
     */
    template<class T>
    inline T distanceSquared(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        return lengthSquared(_a - _b);
    }

    /**
     * @brief Returns the squared distance between the two provided vectors.
     */
    template<class T>
    inline T distanceSquared(const Vector3<T> & _a, const Vector3<T> & _b)
    {
        return lengthSquared(_a - _b);
    }

    /**
     * @brief Returns the squared distance between the two provided vectors.
     */
    template<class T>
    inline T distanceSquared(const Vector4<T> & _a, const Vector4<T> & _b)
    {
        return lengthSquared(_a - _b);
    }

    /**
     * @brief Returns the dot/scalar product between the two provided vectors.
     * @return A number that holds the result.
     */
    template<class T>
    inline T dot(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        return _a.x * _b.x + _a.y * _b.y;
    }

    /**
     * @brief Returns the dot/scalar product between the two provided vectors.
     * @return A number that holds the result.
     */
    template<class T>
    inline T dot(const Vector3<T> & _a, const Vector3<T> & _b)
    {
        return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
    }

    /**
     * @brief Returns the dot/scalar product between the two provided vectors.
     * @return A number that holds the result.
     */
    template<class T>
    inline T dot(const Vector4<T> & _a, const Vector4<T> & _b)
    {
        return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z + _a.w * _b.w;
    }

    /**
     * @brief Returns the cross product between the two provided vectors.
     * @return A vector that holds the result.
     */
    template<class T>
    inline Vector3<T> cross(const Vector3<T> & _a, const Vector3<T> & _b)
    {
        Vector3<T> ret;

        ret.x = _a.y * _b.z - _a.z * _b.y;
        ret.y = _a.z * _b.x - _a.x * _b.z;
        ret.z = _a.x * _b.y - _a.y * _b.x;

        return ret;
    }

    /**
     * @brief Returns the cross product between the two provided vectors.
     * @return A vector that holds the result.
     */
    template<class T>
    inline T cross(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        return _a.x * _b.y - _a.y * _b.x;
    }

    /**
     * @brief Normalizes the provided vector.
     *
     * This will return a new vector which is the input vector in unit length (a length of one).
     *
     * @return A vector that is the normalized input vector.
     */
    template<class T>
    inline Vector2<T> normalize(const Vector2<T> & _vec)
    {
        T invLen = 1.0 / length(_vec);
        return _vec * invLen;
    }

    /**
     * @brief Normalizes the provided vector.
     *
     * This will return a new vector which is the input vector in unit length (a length of one).
     *
     * @return A vector that is the normalized input vector.
     */
    template<class T>
    inline Vector3<T> normalize(const Vector3<T> & _vec)
    {
        T invLen = 1.0 / length(_vec);
        return _vec * invLen;
    }

    /**
     * @brief Normalizes the provided vector.
     *
     * This will return a new vector which is the input vector in unit length (a length of one).
     *
     * @return A vector that is the normalized input vector.
     */
    template<class T>
    inline Vector4<T> normalize(const Vector4<T> & _vec)
    {
        T invLen = 1.0 / length(_vec);
        return _vec * invLen;
    }


    /**
     * @brief Reflects an incident vector along a normal.
     * @param _vec The incident vector.
     * @param _normal The normal vector. This should be normalized.
     * @return A vector that is the reflected incident vector.
     */
    template<class T>
    inline Vector2<T> reflect(const Vector2<T> & _vec, const Vector2<T> & _normal)
    {
        return _vec - _normal * dot(_normal, _vec) * T(2);
    }

    /**
     * @brief Reflects an incident vector along a normal.
     * @param _vec The incident vector.
     * @param _normal The normal vector. This should be normalized.
     * @return A vector that is the reflected incident vector.
     */
    template<class T>
    inline Vector3<T> reflect(const Vector3<T> & _vec, const Vector3<T> & _normal)
    {
        return _vec - _normal * dot(_normal, _vec) * T(2);
    }

    /**
     * @brief Reflects an incident vector along a normal.
     * @param _vec The incident vector.
     * @param _normal The normal vector. This should be normalized.
     * @return A vector that is the reflected incident vector.
     */
    template<class T>
    inline Vector4<T> reflect(const Vector4<T> & _vec, const Vector4<T> & _normal)
    {
        return _vec - _normal * dot(_normal, _vec) * T(2);
    }

    /**
     * @brief Calculates the refraction direction for an incident vector.
     * @param _vec The incident vector. This should be normalized.
     * @param _normal The normal vector. This should be normalized.
     * @param _eta The ratio of indices of refraction.
     * @return A vector that is the refracted incident vector.
     */
    template<class T>
    inline Vector2<T> refract(const Vector2<T> & _vec, const Vector2<T> & _normal, T _eta)
    {
        T k = T(1.0) - _eta * _eta * (T(1.0) - dot(_normal, _vec) * dot(_normal, _vec));

        if (k < T(0.0))
            return Vector2<T>(0.0);
        else
            return _eta * _vec - (_eta * dot(_normal, _vec) + sqrt(k)) * _normal;
    }

    /**
     * @brief Calculates the refraction direction for an incident vector.
     * @param _vec The incident vector. This should be normalized.
     * @param _normal The normal vector. This should be normalized.
     * @param _eta The ratio of indices of refraction.
     * @return A vector that is the refracted incident vector.
     */
    template<class T>
    inline Vector3<T> refract(const Vector3<T> & _vec, const Vector3<T> & _normal, T _eta)
    {
        T k = T(1.0) - _eta * _eta * (T(1.0) - dot(_normal, _vec) * dot(_normal, _vec));

        if (k < T(0.0))
            return Vector2<T>(0.0);
        else
            return _eta * _vec - (_eta * dot(_normal, _vec) + sqrt(k)) * _normal;
    }

    /**
     * @brief Calculates the refraction direction for an incident vector.
     * @param _vec The incident vector. This should be normalized.
     * @param _normal The normal vector. This should be normalized.
     * @param _eta The ratio of indices of refraction.
     * @return A vector that is the refracted incident vector.
     */
    template<class T>
    inline Vector4<T> refract(const Vector4<T> & _vec, const Vector4<T> & _normal, T _eta)
    {
        T k = T(1.0) - _eta * _eta * (T(1.0) - dot(_normal, _vec) * dot(_normal, _vec));

        if (k < T(0.0))
            return Vector2<T>(0.0);
        else
            return _eta * _vec - (_eta * dot(_normal, _vec) + sqrt(k)) * _normal;
    }

    /**
     * @brief Returns the directed angle in radians between two 2D vectors.
     */
    template<class T>
    inline T directedAngle(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        return std::atan2(cross(_a, _b), dot(_a, _b));
    }

    /**
     * @brief Rotates a 2D vector by an angle in radians.
     */
    template<class T>
    inline Vector2<T> rotate(const Vector2<T> & _a, T _radians)
    {
        T c = std::cos(_radians);
        T s = std::sin(_radians);
        return Vector2<T>(_a.x * c - _a.y * s, _a.x * s + _a.y * c);
    }

    /**
     * @brief Rotates a 2D vector by an angle in radians around a point.
     */
    template<class T>
    inline Vector2<T> rotate(const Vector2<T> & _a, const Vector2<T> & _point, T _radians)
    {
        T c = std::cos(_radians);
        T s = std::sin(_radians);
        T dx = _a.x - _point.x;
        T dy = _point.y - _a.y;
        return Vector2<T>(dx * c - dy * s + _point.x, dx * s + dy * c + _point.y);
    }

    /**
     * @brief Returns true if the directions of the two provided vectors are colinear (on the same line).
     * @param _a The first vector.
     * @param _b The second vector.
     * @param _epsilon An epsilon value for floating point comparison.
     */
    template<class T>
    inline bool isCollinear(const Vector2<T> & _a, const Vector2<T> & _b, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        return isClose(cross(_a, _b), static_cast<T>(0), _epsilon);
    }

    /**
     * @brief Returns true if the directions of the two provided vectors are orthogonal (perpendicular).
     * @param _a The first vector.
     * @param _b The second vector.
     * @param _epsilon An epsilon value for floating point comparison.
     */
    template<class T>
    inline bool isOrthogonal(const Vector2<T> & _a, const Vector2<T> & _b, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        return isClose(static_cast<T>(dot(_a, _b)), static_cast<T>(0), _epsilon);
    }

    /**
     * @brief Returns true if the directions of the two provided vectors are orthogonal (perpendicular).
     * @param _a The first vector.
     * @param _b The second vector.
     * @param _epsilon An epsilon value for floating point comparison.
     */
    template<class T>
    inline bool isOrthogonal(const Vector3<T> & _a, const Vector3<T> & _b, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        return isClose(dot(_a, _b), static_cast<T>(0), _epsilon);
    }
}

#endif //CRUNCH_GEOMETRIC_FUNC_HPP