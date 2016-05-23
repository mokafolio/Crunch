#ifndef CRUNCH_UTILITYFUNC_HPP
#define CRUNCH_UTILITYFUNC_HPP

#include <Stick/Platform.hpp>
#include <complex>
#include <iostream>

namespace crunch
{
    /**
     * @brief Returns true if a number is power of two.
     */
    template<class T>
    bool isPowerOfTwo(const T & _a)
    {
        return ((_a > 0) && ((_a & (_a - 1)) == 0));
    }

    /**
     * @brief Returns true if a number is even.
     */
    template<class T>
    bool isEven(const T & _a)
    {
        return (_a % 2 == 0) ? true : false;
    }

    /**
     * @brief Returns true if a number is odd.
     */
    template<class T>
    bool isOdd(const T & _a)
    {
        return (_a % 2 == 0) ? false : true;
    }

    //based on the functions from the book: Hacker's Delight!

    /**
     * @brief Returns the next integer that is power of two
     * that is bigger than the input value.
     */
    inline stick::UInt32 upperPowerOfTwo32(stick::UInt32 _val)
    {
        _val--;
        _val |= _val >> 1;
        _val |= _val >> 2;
        _val |= _val >> 4;
        _val |= _val >> 8;
        _val |= _val >> 16;
        _val++;

        return _val;
    }

    /**
     * @brief Returns the next integer that is power of two
     * that is bigger than the input value.
     */
    inline stick::UInt64 upperPowerOfTwo64(stick::UInt64 _val)
    {
        _val--;
        _val |= _val >> 1;
        _val |= _val >> 2;
        _val |= _val >> 4;
        _val |= _val >> 8;
        _val |= _val >> 16;
        _val |= _val >> 32;
        _val++;

        return _val;
    }

    /**
     * @brief Returns the previous integer that is power of two
     * that is smaller than the input value.
     */
    inline stick::UInt32 lowerPowerOfTwo32(stick::UInt32 _val)
    {
        _val = _val | (_val >> 1);
        _val = _val | (_val >> 2);
        _val = _val | (_val >> 4);
        _val = _val | (_val >> 8);
        _val = _val | (_val >> 16);
        return _val - (_val >> 1);
    }

    /**
     * @brief Returns the previous integer that is power of two
     * that is smaller than the input value.
     */
    inline stick::UInt64 lowerPowerOfTwo64(stick::UInt64 _val)
    {
        _val = _val | (_val >> 1);
        _val = _val | (_val >> 2);
        _val = _val | (_val >> 4);
        _val = _val | (_val >> 8);
        _val = _val | (_val >> 16);
        _val = _val | (_val >> 32);
        return _val - (_val >> 1);
    }

    /**
     * @brief Default adder type for averaging.
     * @see average
     */
    template<class T>
    class DefaultAdder
    {
    public:

        typedef T ValueType;

        void addTo(T & _result, const T & _adder) const
        {
            _result += _adder;
        }
    };

    /**
     * @brief Adder adding only the real part of a complex number.
     * @see average
     */
    template<class T>
    class ComplexRealAdder
    {
    public:

        typedef T ValueType;

        void addTo(T & _result, const std::complex<T> & _adder) const
        {
            _result += _adder.real();
        }
    };

    /**
     * @brief Adder adding only the imaginary part of a complex number.
     * @see average
     */
    template<class T>
    class ComplexImaginaryAdder
    {
    public:

        typedef T ValueType;

        void addTo(T & _result, const std::complex<T> & _adder) const
        {
            _result += _adder.imag();
        }
    };

    /**
     * @brief Returns the average of a range.
     * @arg Iterator The iterator type of the range.
     * @arg Adder A type responsible implementing addition behavior.
     * @param _begin The beginning of the range.
     * @param _end The end of the range.
     * @param _adder The adder to to the addition.
     */
    template<class Iterator, class Adder = DefaultAdder<stick::Float32> >
    inline typename Adder::ValueType average(Iterator _begin, Iterator _end, const Adder & _adder = Adder())
    {
        typename Adder::ValueType ret(0);
        Iterator it = _begin;
        for (; it != _end; ++it)
        {
            _adder.addTo(ret, *it);
        }

        ret /= std::distance(_begin, _end);

        return ret;
    }
}

#endif //CRUNCH_UTILITYFUNC_HPP
