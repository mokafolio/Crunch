#ifndef CRUNCH_EXPONENTIALFUNC_HPP
#define CRUNCH_EXPONENTIALFUNC_HPP

#include <cmath>
#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>

namespace crunch
{
    /**
     * @brief Computes the square root of the provided value.
     */
    template<class T>
    inline T sqrt(const T & _a)
    {
        return std::sqrt(_a);
    }

    /**
     * @brief Computes the square root on all components of the provided vector.
     */
    template<class T>
    inline Vector2<T> sqrt(const Vector2<T> & _vec)
    {
        Vector2<T> ret;
        ret.x = std::sqrt(_vec.x);
        ret.y = std::sqrt(_vec.y);

        return ret;
    }

    /**
     * @brief Computes the square root on all components of the provided vector.
     */
    template<class T>
    inline Vector3<T> sqrt(const Vector3<T> & _vec)
    {
        Vector3<T> ret;
        ret.x = std::sqrt(_vec.x);
        ret.y = std::sqrt(_vec.y);
        ret.z = std::sqrt(_vec.z);

        return ret;
    }

    /**
     * @brief Computes the square root on all components of the provided vector.
     */
    template<class T>
    inline Vector4<T> sqrt(const Vector4<T> & _vec)
    {
        Vector4<T> ret;
        ret.x = std::sqrt(_vec.x);
        ret.y = std::sqrt(_vec.y);
        ret.z = std::sqrt(_vec.z);
        ret.w = std::sqrt(_vec.w);

        return ret;
    }
}

#endif //CRUNCH_EXPONENTIALFUNC_HPP
