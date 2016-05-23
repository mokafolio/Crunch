#ifndef CRUNCH_COLORS_HPP
#define CRUNCH_COLORS_HPP

#include <Crunch/Color1.hpp>
#include <Crunch/Color3.hpp>
#include <Crunch/Color4.hpp>
#include <Crunch/Constants.hpp>
#include <Crunch/CommonFunc.hpp>

#include <cmath>

namespace crunch
{
    namespace detail
    {
        template<class T>
        struct Gray
        {
            typedef T ValueType;

            Gray()
            {

            }

            Gray(T _g) :
                g(_g)
            {

            }

            T g;
        };

        template<class T>
        struct RGB
        {
            typedef T ValueType;

            RGB()
            {

            }

            RGB(T _g) :
                r(_g),
                g(_g),
                b(_g)
            {
            }

            RGB(T _r, T _g, T _b) :
                r(_r),
                g(_g),
                b(_b)
            {
            }

            T r, g, b;
        };

        template<class T>
        struct RGBA
        {
            typedef T ValueType;

            RGBA()
            {

            }

            RGBA(T _g) :
                r(_g),
                g(_g),
                b(_g),
                a(1.0)
            {
            }

            RGBA(T _r, T _g, T _b, T _a) :
                r(_r),
                g(_g),
                b(_b),
                a(_a)
            {
            }

            T r, g, b, a;
        };

        template<class T>
        struct HSB
        {
            typedef T ValueType;

            HSB()
            {

            }

            HSB(T _g) :
                h(_g),
                s(_g),
                b(_g)
            {
            }

            HSB(T _h, T _s, T _b) :
                h(_h),
                s(_s),
                b(_b)
            {
            }

            T h, s, b;
        };

        template<class T>
        struct HSBA
        {
            typedef T ValueType;

            HSBA()
            {

            }

            HSBA(T _g) :
                h(_g),
                s(_g),
                b(_g),
                a(1.0)
            {
            }

            HSBA(T _h, T _s, T _b, T _a) :
                h(_h),
                s(_s),
                b(_b),
                a(_a)
            {
            }

            T h, s, b, a;
        };

        template<class T>
        inline void convertHSBToRGB(T _fh, T _fs, T _fb, T & _tr, T & _tg, T & _tb)
        {
            static stick::UInt32 s_hsbIndices[6][3] =
            {
                {0, 3, 1}, // 0
                {2, 0, 1}, // 1
                {1, 0, 3}, // 2
                {1, 2, 0}, // 3
                {3, 1, 0}, // 4
                {0, 1, 2}  // 5
            };

            T h = std::fmod(std::fmod(_fh * 6.0, 6.0) + 6, 6.0);
            stick::UInt32 i = floor(h);
            T fract = h - i;

            stick::UInt32 * indices = s_hsbIndices[i];
            T values[4] = { _fb , _fb * (1 - _fs), _fb * (1 - _fs * fract), _fb * (1 - _fs * (1 - fract)) };

            _tr = values[indices[0]];
            _tg = values[indices[1]];
            _tb = values[indices[2]];
        }

        template<class T>
        inline void convertRGBToHSB(T _fr, T _fg, T _fb, T & _th, T & _ts, T & _tb)
        {
            //based on the implementation here: http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
            T K = 0.0;

            if (_fg < _fb)
            {
                std::swap(_fg, _fb);
                K = -1.0;
            }

            if (_fr < _fg)
            {
                std::swap(_fr, _fg);
                K = -2.0 / 6.0 - K;
            }

            T chroma = _fr - min(_fg, _fb);
            _th = abs(K + (_fg - _fb) / (6.0 * chroma + 1e-20));
            _ts = chroma / (_fr + 1e-20);
            _tb = _fr;
        }

        template<class T>
        inline T hueInRadians(T _hue);

        template<class T>
        inline T hueInDegrees(T _hue);

        template<>
        inline stick::Float64 hueInRadians(stick::Float64 _hue)
        {
            return _hue * Constants<stick::Float64>::twoPi();
        }

        template<>
        inline stick::Float32 hueInRadians(stick::Float32 _hue)
        {
            return _hue * Constants<stick::Float32>::twoPi();
        }

        template<>
        inline stick::Float64 hueInDegrees(stick::Float64 _hue)
        {
            return _hue * 360.0;
        }

        template<>
        inline stick::Float32 hueInDegrees(stick::Float32 _hue)
        {
            return _hue * 360.0;
        }
    }

    template<class T>
    using ColorGrayT = Color1<detail::Gray<T>>;
    using ColorGray = ColorGrayT<stick::Float32>;

    template<class T>
    using ColorRGBT = Color3<detail::RGB<T>>;
    using ColorRGB = ColorRGBT<stick::Float32>;

    template<class T>
    using ColorRGBAT = Color4<detail::RGBA<T>>;
    using ColorRGBA = ColorRGBAT<stick::Float32>;

    template<class T>
    using ColorHSBT = Color3<detail::HSB<T>>;
    using ColorHSB = ColorHSBT<stick::Float32>;

    template<class T>
    using ColorHSBAT = Color4<detail::HSBA<T>>;
    using ColorHSBA = ColorHSBAT<stick::Float32>;

    template<class T>
    ColorGrayT<T> toGray(const ColorRGBT<T> & _col)
    {
        return ColorGrayT<T>(_col.r * 0.2989 + _col.g * 0.587 + _col.b * 0.114);
    }

    template<class T>
    ColorGrayT<T> toGray(const ColorRGBAT<T> & _col)
    {
        return ColorGrayT<T>(_col.r * 0.2989 + _col.g * 0.587 + _col.b * 0.114);
    }

    template<class T>
    ColorGrayT<T> toGray(const ColorHSBT<T> & _col)
    {
        return ColorGrayT<T>(_col.b); //is this correct?
    }

    template<class T>
    ColorGrayT<T> toGray(const ColorHSBAT<T> & _col)
    {
        return ColorGrayT<T>(_col.b); //is this correct?
    }

    template<class T>
    ColorRGBT<T> toRGB(const ColorGrayT<T> & _col)
    {
        return ColorRGBT<T>(_col.g);
    }

    template<class T>
    ColorRGBT<T> toRGB(const ColorRGBAT<T> & _col)
    {
        return ColorRGBT<T>(_col.r, _col.g, _col.b);
    }

    template<class T>
    ColorRGBT<T> toRGB(const ColorHSBT<T> & _col)
    {
        ColorRGBT<T> ret;
        detail::convertHSBToRGB(_col.h, _col.s, _col.b, ret.r, ret.g, ret.b);
        return ret;
    }

    template<class T>
    ColorRGBT<T> toRGB(const ColorHSBAT<T> & _col)
    {
        ColorRGBT<T> ret;
        detail::convertHSBToRGB(_col.h, _col.s, _col.b, ret.r, ret.g, ret.b);
        return ret;
    }

    template<class T>
    ColorRGBAT<T> toRGBA(const ColorGrayT<T> & _col)
    {
        return ColorRGBAT<T>(_col.g, _col.g, _col.g, 1.0);
    }

    template<class T>
    ColorRGBAT<T> toRGBA(const ColorRGBT<T> & _col)
    {
        return ColorRGBAT<T>(_col.r, _col.g, _col.b, 1.0);
    }

    template<class T>
    ColorRGBAT<T> toRGBA(const ColorHSBT<T> & _col)
    {
        ColorRGBAT<T> ret;
        detail::convertHSBToRGB(_col.h, _col.s, _col.b, ret.r, ret.g, ret.b);
        ret.a = 1.0;
        return ret;
    }

    template<class T>
    ColorRGBAT<T> toRGBA(const ColorHSBAT<T> & _col)
    {
        ColorRGBAT<T> ret;
        detail::convertHSBToRGB(_col.h, _col.s, _col.b, ret.r, ret.g, ret.b);
        ret.a = _col.a;
        return ret;
    }

    template<class T>
    ColorHSBT<T> toHSB(const ColorGrayT<T> & _col)
    {
        return ColorHSBT<T>(0.0, 0.0, _col.g);
    }

    template<class T>
    ColorHSBT<T> toHSB(const ColorRGBT<T> & _col)
    {
        ColorHSBT<T> ret;
        detail::convertRGBToHSB(_col.r, _col.g, _col.b, ret.h, ret.s, ret.b);
        return ret;
    }

    template<class T>
    ColorHSBT<T> toHSB(const ColorRGBAT<T> & _col)
    {
        ColorHSBT<T> ret;
        detail::convertRGBToHSB(_col.r, _col.g, _col.b, ret.h, ret.s, ret.b);
        return ret;
    }

    template<class T>
    ColorHSBT<T> toHSB(const ColorHSBAT<T> & _col)
    {
        return ColorHSBT<T>(_col.h, _col.s, _col.b);
    }

    template<class T>
    ColorHSBAT<T> toHSBA(const ColorGrayT<T> & _col)
    {
        return ColorHSBAT<T>(0.0, 0.0, _col.g, 1.0);
    }

    template<class T>
    ColorHSBAT<T> toHSBA(const ColorRGBT<T> & _col)
    {
        ColorHSBAT<T> ret;
        detail::convertRGBToHSB(_col.r, _col.g, _col.b, ret.h, ret.s, ret.b);
        ret.a = 1.0;
        return ret;
    }

    template<class T>
    ColorHSBAT<T> toHSBA(const ColorRGBAT<T> & _col)
    {
        ColorHSBAT<T> ret;
        detail::convertRGBToHSB(_col.r, _col.g, _col.b, ret.h, ret.s, ret.b);
        ret.a = _col.a;
        return ret;
    }

    template<class T>
    ColorHSBAT<T> toHSBA(const ColorHSBT<T> & _col)
    {
        return ColorHSBAT<T>(_col.h, _col.s, _col.b, 1.0);
    }
}

#endif // CRUNCH_COLORS_HPP
