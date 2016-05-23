#ifndef CRUNCH_TRIGONOMETRYFUNC_HPP
#define CRUNCH_TRIGONOMETRYFUNC_HPP

namespace crunch
{
    /**
     * @brief Convert an angle in degrees to radians.
     */
    template<class T>
    inline T toRadians(const T & _degrees)
    {
        return _degrees * 0.017453293;
    }

    /**
     * @brief Convert an angle in radians to degrees.
     */
    template<class T>
    inline T toDegrees(const T & _radians)
    {
        return _radians * 57.29577951;
    }
}


#endif //CRUNCH_TRIGONOMETRYFUNC_HPP
