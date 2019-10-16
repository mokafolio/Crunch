#ifndef CRUNCH_UTILITIES_HPP
#define CRUNCH_UTILITIES_HPP

namespace crunch
{
    /**
     * @brief Holds math constants.
     * @arg T The value/floating point type to use.
     */
    template<class T>
    class Constants
    {
    public:

        /**
         * @brief Returns Pi.
         */
        static inline T pi()
        {
            return (T)3.14159265358979323846;
        }

        /**
         * @brief Returns half Pi.
         */
        static inline T halfPi()
        {
            return (T)pi() * (T)0.5;
        }

        /**
         * @brief Returns Pi times two.
         */
        static inline T twoPi()
        {
            return (T)pi() * (T)2.0;
        }
    };
}

#endif //CRUNCH_UTILITIES_HPP
