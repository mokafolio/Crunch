#ifndef CRUNCH_COMMONFUNC_HPP
#define CRUNCH_COMMONFUNC_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>

namespace crunch
{
    /**
     * @brief Returns the absolute value of the provided number.
     */
    template<class T>
    inline T abs(const T & _a)
    {
        return _a < 0 ? -_a : _a;
    }

    /**
     * @brief Returns the absolute vector of the provided vector.
     *
     * This will effectively compute the absolute value for each component of the vector.
     */
    template<class T>
    inline Vector2<T> abs(const Vector2<T> & _vec)
    {
        Vector2<T> ret;
        ret.x = abs(_vec.x);
        ret.y = abs(_vec.y);

        return ret;
    }

    /**
     * @brief Returns the absolute vector of the provided vector.
     *
     * This will effectively compute the absolute value for each component of the vector.
     */
    template<class T>
    inline Vector3<T> abs(const Vector3<T> & _vec)
    {
        Vector3<T> ret;
        ret.x = abs(_vec.x);
        ret.y = abs(_vec.y);
        ret.z = abs(_vec.z);

        return ret;
    }

    /**
     * @brief Returns the absolute vector of the provided vector.
     *
     * This will effectively compute the absolute value for each component of the vector.
     */
    template<class T>
    inline Vector4<T> abs(const Vector4<T> & _vec)
    {
        Vector4<T> ret;
        ret.x = abs(_vec.x);
        ret.y = abs(_vec.y);
        ret.z = abs(_vec.z);
        ret.w = abs(_vec.w);

        return ret;
    }

    /**
     * @brief Computes the largest integer not greater than the provided value.
     */
    template<class T>
    inline T floor(const T & _val)
    {
        return std::floor(_val);
    }

    /**
     * @brief Computes the largest integer for each vector component not greater
     * than the corresponding vector component of the input vector.
     */
    template<class T>
    inline Vector2<T> floor(const Vector2<T> & _vec)
    {
        Vector2<T> ret;
        ret.x = std::floor(_vec.x);
        ret.y = std::floor(_vec.y);
        return ret;
    }

    /**
     * @brief Computes the largest integer for each vector component not greater
     * than the corresponding vector component of the input vector.
     */
    template<class T>
    inline Vector3<T> floor(const Vector3<T> & _vec)
    {
        Vector3<T> ret;
        ret.x = std::floor(_vec.x);
        ret.y = std::floor(_vec.y);
        ret.z = std::floor(_vec.z);
        return ret;
    }

    /**
     * @brief Computes the largest integer for each vector component not greater
     * than the corresponding vector component of the input vector.
     */
    template<class T>
    inline Vector4<T> floor(const Vector4<T> & _vec)
    {
        Vector4<T> ret;
        ret.x = std::floor(_vec.x);
        ret.y = std::floor(_vec.y);
        ret.z = std::floor(_vec.z);
        ret.w = std::floor(_vec.w);
        return ret;
    }


    /**
     * @brief Computes the smallest integer value not less than the provided value.
     */
    template<class T>
    inline T ceil(const T & _val)
    {
        return std::ceil(_val);
    }

    /**
     * @brief Computes the smallest integer for each vector component not less
     * than the corresponding vector component of the input vector.
     */
    template<class T>
    inline Vector2<T> ceil(const Vector2<T> & _vec)
    {
        Vector2<T> ret;
        ret.x = std::ceil(_vec.x);
        ret.y = std::ceil(_vec.y);
        return ret;
    }

    /**
     * @brief Computes the smallest integer for each vector component not less
     * than the corresponding vector component of the input vector.
     */
    template<class T>
    inline Vector3<T> ceil(const Vector3<T> & _vec)
    {
        Vector3<T> ret;
        ret.x = std::ceil(_vec.x);
        ret.y = std::ceil(_vec.y);
        ret.z = std::ceil(_vec.z);
        return ret;
    }

    /**
     * @brief Computes the smallest integer for each vector component not less
     * than the corresponding vector component of the input vector.
     */
    template<class T>
    inline Vector4<T> ceil(const Vector4<T> & _vec)
    {
        Vector4<T> ret;
        ret.x = std::ceil(_vec.x);
        ret.y = std::ceil(_vec.y);
        ret.z = std::ceil(_vec.z);
        ret.w = std::ceil(_vec.w);
        return ret;
    }

    /**
     * @brief Computes the fractional part of the provided value.
     *
     * If the input type is a vector, it will return a vector with the fractional
     * part of each component of the input vector.
     */
    template<class T>
    inline T fract(const T & _val)
    {
        return _val - floor(_val);
    }

    /**
     * @brief Returns the smaller value of the two provided arguments.
     */
    template<class T>
    inline T min(const T & _a, const T & _b)
    {
        return _a < _b ? _a : _b;
    }

    /**
     * @brief Returns the bigger value of the two provided arguments.
     */
    template<class T>
    inline T max(const T & _a, const T & _b)
    {
        return _a > _b ? _a : _b;
    }

    /**
     * @brief Returns the vector with the smallest components of both provided vectors.
     */
    template<class T>
    inline Vector2<T> min(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        Vector2<T> ret;
        _a.x < _b.x ? ret.x = _a.x : ret.x = _b.x;
        _a.y < _b.y ? ret.y = _a.y : ret.y = _b.y;
        return ret;
    }

    /**
     * @brief Returns the vector with the biggest components of both provided vectors.
     */
    template<class T>
    inline Vector2<T> max(const Vector2<T> & _a, const Vector2<T> & _b)
    {
        Vector2<T> ret;
        _a.x > _b.x ? ret.x = _a.x : ret.x = _b.x;
        _a.y > _b.y ? ret.y = _a.y : ret.y = _b.y;
        return ret;
    }

    /**
     * @brief Returns the vector with the smallest components of both provided vectors.
     */
    template<class T>
    inline Vector3<T> min(const Vector3<T> & _a, const Vector3<T> & _b)
    {
        Vector3<T> ret;
        _a.x < _b.x ? ret.x = _a.x : ret.x = _b.x;
        _a.y < _b.y ? ret.y = _a.y : ret.y = _b.y;
        _a.z < _b.z ? ret.z = _a.z : ret.z = _b.z;
        return ret;
    }

    /**
     * @brief Returns the vector with the biggest components of both provided vectors.
     */
    template<class T>
    inline Vector3<T> max(const Vector3<T> & _a, const Vector3<T> & _b)
    {
        Vector3<T> ret;
        _a.x > _b.x ? ret.x = _a.x : ret.x = _b.x;
        _a.y > _b.y ? ret.y = _a.y : ret.y = _b.y;
        _a.z > _b.z ? ret.z = _a.z : ret.z = _b.z;
        return ret;
    }

    /**
     * @brief Returns the vector with the smallest components of both provided vectors.
     */
    template<class T>
    inline Vector4<T> min(const Vector4<T> & _a, const Vector4<T> & _b)
    {
        Vector4<T> ret;
        _a.x < _b.x ? ret.x = _a.x : ret.x = _b.x;
        _a.y < _b.y ? ret.y = _a.y : ret.y = _b.y;
        _a.z < _b.z ? ret.z = _a.z : ret.z = _b.z;
        _a.w < _b.w ? ret.w = _a.w : ret.w = _b.w;
        return ret;
    }

    /**
     * @brief Returns the vector with the biggest components of both provided vectors.
     */
    template<class T>
    inline Vector4<T> max(const Vector4<T> & _a, const Vector4<T> & _b)
    {
        Vector4<T> ret;
        _a.x > _b.x ? ret.x = _a.x : ret.x = _b.x;
        _a.y > _b.y ? ret.y = _a.y : ret.y = _b.y;
        _a.z > _b.z ? ret.z = _a.z : ret.z = _b.z;
        _a.w > _b.w ? ret.w = _a.w : ret.w = _b.w;
        return ret;
    }

    /**
     * @brief Clamps the provided value so that it is bigger or equal then the minimum
     * value provided and smaller or equal than the maximum value.
     *
     * For vectors, this process is performed for each component.
     */
    template<class T>
    inline T clamp(const T & _val, const T & _min, const T & _max)
    {
        return min(max(_val, _min), _max);
    }


    /**
     * @brief Linear interpolation between two values.
     * @param _a The first value
     * @param _b The second value
     * @param _fact Mix factor between 0 and 1.
     */
    template<class T>
    inline T mix(const T & _a, const T & _b, const T & _fact)
    {
        return (T)(_a + (_b - _a) * _fact);
    }

    /*template<template<class> class C, class T>
    inline C<T> mix(const C<T> & _a, const C<T> & _b, const T & _fact)
    {
        return _a + (_b - _a) * _fact;
    }*/


    /**
     * @brief Absolute tolerance compare. Good for small numbers.
     *
     * http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison
     */
    template<class T>
    bool absoluteToleranceCompare(T _x, T _y, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        return std::fabs(_x - _y) <= _epsilon;
    }

    /**
     * @brief Relative tolerance compare. Good for big numbers.
     *
     * http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison
     */
    template<class T>
    bool relativeToleranceCompare(T _x, T _y, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        T maxXY = std::max(std::fabs(_x) , std::fabs(_y)) ;
        return std::fabs(_x - _y) <= _epsilon * maxXY ;
    }

    /**
     * @brief Combined tolerance compare. Good for all kinds of numbers.
     *
     * http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison
     */
    template<class T>
    bool combinedToleranceCompare(T _x, T _y, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        T maxXYOne = std::max((T)1.0, (T)std::max(std::fabs(_x), std::fabs(_y))) ;
        return std::fabs(_x - _y) <= _epsilon * maxXYOne ;
    }

    /**
     * @brief More verbose naming, basically boils down to a combinedToleranceCompare.
     * @see combinedToleranceCompare
     */
    template<class T>
    bool isClose(T _a, T _b, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        return combinedToleranceCompare(_a, _b, _epsilon);
    }

    /**
     * @brief Checks if two vectors are close.
     * @param _a First vector.
     * @param _b Second vector.
     * @param _epsilon Epsilon value to use for the floating point comparison.
     * @see combinedToleranceCompare
     */
    template<class T>
    bool isClose(const Vector2<T> & _a, const Vector2<T> & _b, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        if (combinedToleranceCompare(_a.x, _b.x, _epsilon) &&
                combinedToleranceCompare(_a.y, _b.y, _epsilon))
            return true;

        return false;
    }

    /**
     * @brief Checks if two vectors are close.
     * @param _a First vector.
     * @param _b Second vector.
     * @param _epsilon Epsilon value to use for the floating point comparison.
     * @see combinedToleranceCompare
     */
    template<class T>
    bool isClose(const Vector3<T> & _a, const Vector3<T> & _b, T _epsilon = std::numeric_limits<T>::epsilon())
    {
        if (combinedToleranceCompare(_a.x, _b.x, _epsilon) &&
                combinedToleranceCompare(_a.y, _b.y, _epsilon) &&
                combinedToleranceCompare(_a.z, _b.z, _epsilon))
            return true;

        return false;
    }

    /**
     * @brief Greatest common divisor.
     *
     * http://en.wikipedia.org/wiki/Greatest_common_divisor
     */
    template<class T>
    inline T greatestCommonDivisor(T _a, T _b)
    {
        if (_b == 0)
            return _a;

        return greatestCommonDivisor(_b, std::fmod(_a, _b));
    }

    /**
     * @brief Greatest common divisor.
     *
     * http://en.wikipedia.org/wiki/Greatest_common_divisor
     */
    template<>
    inline int greatestCommonDivisor(int _a, int _b)
    {
        if (_b == 0)
            return _a;

        return greatestCommonDivisor(_b, _a % _b);
    }

    /**
     * @brief Greatest common divisor.
     *
     * http://en.wikipedia.org/wiki/Greatest_common_divisor
     */
    template<>
    inline stick::Int64 greatestCommonDivisor(stick::Int64 _a, stick::Int64 _b)
    {
        if (_b == 0)
            return _a;

        return greatestCommonDivisor(_b, _a % _b);
    }
}

#endif //CRUNCH_COMMONFUNC_HPP