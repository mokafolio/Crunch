#ifndef CRUNCH_QUATERNION_FUNC_HPP
#define CRUNCH_QUATERNION_FUNC_HPP

#include <cmath>
#include <limits>
#include <Crunch/Quaternion.hpp>

namespace crunch
{

    /**
     * @brief Returns the length of a quaternion.
     */
    template<class T>
    inline T length(const Quaternion<T> & _quat)
    {
        return sqrt(_quat.x * _quat.x + _quat.y * _quat.y + _quat.z * _quat.z + _quat.w * _quat.w);
    }

    //Add length squared?

    /**
     * @brief Returns the dot product between two quaternions.
     */
    template<class T>
    inline T dot(const Quaternion<T> & _a, const Quaternion<T> & _b)
    {
        return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z + _a.w * _b.w;
    }

    /**
     * @brief Returns the normalized version of the input quaternion.
     */
    template<class T>
    inline Quaternion<T> normalize(const Quaternion<T> & _quat)
    {
        T invLen = (T)1.0 / length(_quat);
        return _quat * invLen;
    }

    /**
     * @brief Returns the conjugate quaternion of the input quaternion.
     */
    template<class T>
    inline Quaternion<T> conjugate(const Quaternion<T> & _quat)
    {
        return Quaternion<T>(-_quat.w, -_quat.x, -_quat.y, -_quat.z);
    }

    /**
     * @brief Linear interpolation between two quaternions.
     * @brief _a The first quaternion.
     * @brief _b The second quaternion.
     * @brief _fact The interpolation factor between 0 and 1.
     * @return The interpolation result quaternion.
     */
    template<class T>
    inline Quaternion<T> lerp(const Quaternion<T> & _a, const Quaternion<T> & _b, T _fact)
    {
        return _a + (_b - _a) * _fact;
    }

    /**
     * @brief Normalized linear interpolation between two quaternions, ensuring to chose
     * of the shortes possible path.
     * @brief _a The first quaternion.
     * @brief _b The second quaternion.
     * @brief _fact The interpolation factor between 0 and 1.
     * @return The interpolation result quaternion.
     */
    template<class T>
    inline Quaternion<T> nlerp(const Quaternion<T> & _a, const Quaternion<T> & _b, T _fact)
    {
        Quaternion<T> ret;

        T dp = dot(_a, _b);
        if (dp < (T)0.0)
        {
            ret = _a + ((-_b) - _a) * _fact;
        }
        else
        {
            ret = _a + (_b - _a) * _fact;
        }

        return normalize(ret);
    }

    /**
     * @brief Spherical linear interpolation between two quaternions.
     * @brief _a The first quaternion.
     * @brief _b The second quaternion.
     * @brief _fact The interpolation factor between 0 and 1.
     * @brief _epsilon Epsilon value used for internal floating point comparisons.
     * @return The interpolation result quaternion.
     */
    template<class T>
    inline Quaternion<T> slerp(const Quaternion<T> & _a, const Quaternion<T> & _b, T _fact,
                               T _epsilon = std::ldexp(std::numeric_limits<T>::epsilon(),
                                            std::numeric_limits<T>::digits / (T)8))
    {
        if (_fact <= (T)0.0)
            return _a;
        else if (_fact >= (T)1.0)
            return _b;

        Quaternion<T> c = _b;
        T dp = dot(_a, c);

        if (dp < (T)0.0)
        {
            c = -c;
            dp = -dp;
        }

        if (dp > (T)1.0 - _epsilon)
            return normalize(lerp(_a, _b, _fact));

        T acosa = std::acos(dp);
        return (_a * sin(((T)1.0 - _fact) * acosa) + c * sin(_fact * acosa)) / sin(acosa);
    }

    /**
     * @brief More GLSL like naming convention for linear interpolation.
     * @see lerp
     */
    template<class T>
    inline Quaternion<T> mix(const Quaternion<T> & _a, const Quaternion<T> & _b, T _fact)
    {
        return lerp(_a, _b, _fact);
    }

    /**
     * @brief More GLSL like naming convention for normalized linear interpolation.
     * @see nlerp
     */
    template<class T>
    inline Quaternion<T> nmix(const Quaternion<T> & _a, const Quaternion<T> & _b, T _fact)
    {
        return nlerp(_a, _b, _fact);
    }

    /**
     * @brief More GLSL like naming convention for spherical linear interpolation.
     * @see slerp
     */
    template<class T>
    inline Quaternion<T> smix(const Quaternion<T> & _a, const Quaternion<T> & _b, T _fact,
                              T _epsilon = std::ldexp(std::numeric_limits<T>::epsilon(),
                                           std::numeric_limits<T>::digits / (T)8))
    {
        return slerp(_a, _b, _fact, _epsilon);
    }
}

#endif //CRUNCH_QUATERNION_FUNC_HPP
