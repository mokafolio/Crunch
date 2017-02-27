#ifndef CRUNCH_COLORS_HPP
#define CRUNCH_COLORS_HPP

#include <Crunch/Color1.hpp>
#include <Crunch/Color3.hpp>
#include <Crunch/Color4.hpp>
#include <Crunch/Constants.hpp>
#include <Crunch/CommonFunc.hpp>

#include <Stick/HashMap.hpp>

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

    template<class T>
    T svgColor(const stick::String & _name)
    {
        static stick::HashMap<stick::String, T> svgColors =
        {
            {"aliceblue", T(240, 248, 255)},
            {"antiquewhite", T(250, 235, 215)},
            {"aqua", T(0, 255, 255)},
            {"aquamarine", T(127, 255, 212)},
            {"azure", T(240, 255, 255)},
            {"beige", T(245, 245, 220)},
            {"bisque", T(255, 228, 196)},
            {"black", T(0, 0, 0)},
            {"blanchedalmond", T(255, 235, 205)},
            {"blue", T(0, 0, 255)},
            {"blueviolet", T(138, 43, 226)},
            {"brown", T(165, 42, 42)},
            {"burlywood", T(222, 184, 135)},
            {"cadetblue", T(95, 158, 160)},
            {"chartreuse", T(127, 255, 0)},
            {"chocolate", T(210, 105, 30)},
            {"coral", T(255, 127, 80)},
            {"cornflowerblue", T(100, 149, 237)},
            {"cornsilk", T(255, 248, 220)},
            {"crimson", T(220, 20, 60)},
            {"cyan", T(0, 255, 255)},
            {"darkblue", T(0, 0, 139)},
            {"darkcyan", T(0, 139, 139)},
            {"darkgoldenrod", T(184, 134, 11)},
            {"darkgray", T(169, 169, 169)},
            {"darkgreen", T(0, 100, 0)},
            {"darkgrey", T(169, 169, 169)},
            {"darkkhaki", T(189, 183, 107)},
            {"darkmagenta", T(139, 0, 139)},
            {"darkolivegreen", T(85, 107, 47)},
            {"darkorange", T(255, 140, 0)},
            {"darkorchid", T(153, 50, 204)},
            {"darkred", T(139, 0, 0)},
            {"darksalmon", T(233, 150, 122)},
            {"darkseagreen", T(143, 188, 143)},
            {"darkslateblue", T(72, 61, 139)},
            {"darkslategray", T(47, 79, 79)},
            {"darkslategrey", T(47, 79, 79)},
            {"darkturquoise", T(0, 206, 209)},
            {"darkviolet", T(148, 0, 211)},
            {"deeppink", T(255, 20, 147)},
            {"deepskyblue", T(0, 191, 255)},
            {"dimgray", T(105, 105, 105)},
            {"dimgrey", T(105, 105, 105)},
            {"dodgerblue", T(30, 144, 255)},
            {"firebrick", T(178, 34, 34)},
            {"floralwhite", T(255, 250, 240)},
            {"forestgreen", T(34, 139, 34)},
            {"fuchsia", T(255, 0, 255)},
            {"gainsboro", T(220, 220, 220)},
            {"ghostwhite", T(248, 248, 255)},
            {"gold", T(255, 215, 0)},
            {"goldenrod", T(218, 165, 32)},
            {"gray", T(128, 128, 128)},
            {"grey", T(128, 128, 128)},
            {"green", T(0, 128, 0)},
            {"greenyellow", T(173, 255, 47)},
            {"honeydew", T(240, 255, 240)},
            {"hotpink", T(255, 105, 180)},
            {"indianred", T(205, 92, 92)},
            {"indigo", T(75, 0, 130)},
            {"ivory", T(255, 255, 240)},
            {"khaki", T(240, 230, 140)},
            {"lavender", T(230, 230, 250)},
            {"lavenderblush", T(255, 240, 245)},
            {"lawngreen", T(124, 252, 0)},
            {"lemonchiffon", T(255, 250, 205)},
            {"lightblue", T(173, 216, 230)},
            {"lightcoral", T(240, 128, 128)},
            {"lightcyan", T(224, 255, 255)},
            {"lightgoldenrodyellow", T(250, 250, 210)},
            {"lightgray", T(211, 211, 211)},
            {"lightgreen", T(144, 238, 144)},
            {"lightgrey", T(211, 211, 211)},
            {"lightpink", T(255, 182, 193)},
            {"lightsalmon", T(255, 160, 122)},
            {"lightseagreen", T(32, 178, 170)},
            {"lightskyblue", T(135, 206, 250)},
            {"lightslategray", T(119, 136, 153)},
            {"lightslategrey", T(119, 136, 153)},
            {"lightsteelblue", T(176, 196, 222)},
            {"lightyellow", T(255, 255, 224)},
            {"lime", T(0, 255, 0)},
            {"limegreen", T(50, 205, 50)},
            {"linen", T(250, 240, 230)},
            {"magenta", T(255, 0, 255)},
            {"maroon", T(128, 0, 0)},
            {"mediumaquamarine", T(102, 205, 170)},
            {"mediumblue", T(0, 0, 205)},
            {"mediumorchid", T(186, 85, 211)},
            {"mediumpurple", T(147, 112, 219)},
            {"mediumseagreen", T(60, 179, 113)},
            {"mediumslateblue", T(123, 104, 238)},
            {"mediumspringgreen", T(0, 250, 154)},
            {"mediumturquoise", T(72, 209, 204)},
            {"mediumvioletred", T(199, 21, 133)},
            {"midnightblue", T(25, 25, 112)},
            {"mintcream", T(245, 255, 250)},
            {"mistyrose", T(255, 228, 225)},
            {"moccasin", T(255, 228, 181)},
            {"navajowhite", T(255, 222, 173)},
            {"navy", T(0, 0, 128)},
            {"oldlace", T(253, 245, 230)},
            {"olive", T(128, 128, 0)},
            {"olivedrab", T(107, 142, 35)},
            {"orange", T(255, 165, 0)},
            {"orangered", T(255, 69, 0)},
            {"orchid", T(218, 112, 214)},
            {"palegoldenrod", T(238, 232, 170)},
            {"palegreen", T(152, 251, 152)},
            {"paleturquoise", T(175, 238, 238)},
            {"palevioletred", T(219, 112, 147)},
            {"papayawhip", T(255, 239, 213)},
            {"peachpuff", T(255, 218, 185)},
            {"peru", T(205, 133, 63)},
            {"pink", T(255, 192, 203)},
            {"plum", T(221, 160, 221)},
            {"powderblue", T(176, 224, 230)},
            {"purple", T(128, 0, 128)},
            {"red", T(255, 0, 0)},
            {"rosybrown", T(188, 143, 143)},
            {"royalblue", T(65, 105, 225)},
            {"saddlebrown", T(139, 69, 19)},
            {"salmon", T(250, 128, 114)},
            {"sandybrown", T(244, 164, 96)},
            {"seagreen", T(46, 139, 87)},
            {"seashell", T(255, 245, 238)},
            {"sienna", T(160, 82, 45)},
            {"silver", T(192, 192, 192)},
            {"skyblue", T(135, 206, 235)},
            {"slateblue", T(106, 90, 205)},
            {"slategray", T(112, 128, 144)},
            {"slategrey", T(112, 128, 144)},
            {"snow", T(255, 250, 250)},
            {"springgreen", T(0, 255, 127)},
            {"steelblue", T(70, 130, 180)},
            {"tan", T(210, 180, 140)},
            {"teal", T(0, 128, 128)},
            {"thistle", T(216, 191, 216)},
            {"tomato", T(255, 99, 71)},
            {"turquoise", T(64, 224, 208)},
            {"violet", T(238, 130, 238)},
            {"wheat", T(245, 222, 179)},
            {"white", T(255, 255, 255)},
            {"whitesmoke", T(245, 245, 245)},
            {"yellow", T(255, 255, 0)},
            {"yellowgreen", T(154, 205, 50)}
        };

        auto it = svgColors.find(_name);
        if (it != svgColors.end())
            return it->value;

        return T(0.0, 0.0, 0.0);
    }
}

#endif // CRUNCH_COLORS_HPP
