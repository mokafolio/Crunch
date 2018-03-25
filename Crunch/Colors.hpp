#ifndef CRUNCH_COLORS_HPP
#define CRUNCH_COLORS_HPP

#include <Crunch/Color1.hpp>
#include <Crunch/Color3.hpp>
#include <Crunch/Color4.hpp>
#include <Crunch/Constants.hpp>
#include <Crunch/CommonFunc.hpp>

#include <Stick/String.hpp>
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

    namespace detail
    {
        template<class T>
        T rgb(stick::UInt8 _r, stick::UInt8 _g, stick::UInt8 _b)
        {
            return T(_r / 255.0, _g / 255.0, _b / 255.0);
        }
    }

    template<class T>
    T svgColor(const stick::String & _name)
    {
        static stick::HashMap<stick::String, T> svgColors =
        {
            {"aliceblue", detail::rgb<T>(240, 248, 255)},
            {"antiquewhite", detail::rgb<T>(250, 235, 215)},
            {"aqua", detail::rgb<T>(0, 255, 255)},
            {"aquamarine", detail::rgb<T>(127, 255, 212)},
            {"azure", detail::rgb<T>(240, 255, 255)},
            {"beige", detail::rgb<T>(245, 245, 220)},
            {"bisque", detail::rgb<T>(255, 228, 196)},
            {"black", detail::rgb<T>(0, 0, 0)},
            {"blanchedalmond", detail::rgb<T>(255, 235, 205)},
            {"blue", detail::rgb<T>(0, 0, 255)},
            {"blueviolet", detail::rgb<T>(138, 43, 226)},
            {"brown", detail::rgb<T>(165, 42, 42)},
            {"burlywood", detail::rgb<T>(222, 184, 135)},
            {"cadetblue", detail::rgb<T>(95, 158, 160)},
            {"chartreuse", detail::rgb<T>(127, 255, 0)},
            {"chocolate", detail::rgb<T>(210, 105, 30)},
            {"coral", detail::rgb<T>(255, 127, 80)},
            {"cornflowerblue", detail::rgb<T>(100, 149, 237)},
            {"cornsilk", detail::rgb<T>(255, 248, 220)},
            {"crimson", detail::rgb<T>(220, 20, 60)},
            {"cyan", detail::rgb<T>(0, 255, 255)},
            {"darkblue", detail::rgb<T>(0, 0, 139)},
            {"darkcyan", detail::rgb<T>(0, 139, 139)},
            {"darkgoldenrod", detail::rgb<T>(184, 134, 11)},
            {"darkgray", detail::rgb<T>(169, 169, 169)},
            {"darkgreen", detail::rgb<T>(0, 100, 0)},
            {"darkgrey", detail::rgb<T>(169, 169, 169)},
            {"darkkhaki", detail::rgb<T>(189, 183, 107)},
            {"darkmagenta", detail::rgb<T>(139, 0, 139)},
            {"darkolivegreen", detail::rgb<T>(85, 107, 47)},
            {"darkorange", detail::rgb<T>(255, 140, 0)},
            {"darkorchid", detail::rgb<T>(153, 50, 204)},
            {"darkred", detail::rgb<T>(139, 0, 0)},
            {"darksalmon", detail::rgb<T>(233, 150, 122)},
            {"darkseagreen", detail::rgb<T>(143, 188, 143)},
            {"darkslateblue", detail::rgb<T>(72, 61, 139)},
            {"darkslategray", detail::rgb<T>(47, 79, 79)},
            {"darkslategrey", detail::rgb<T>(47, 79, 79)},
            {"darkturquoise", detail::rgb<T>(0, 206, 209)},
            {"darkviolet", detail::rgb<T>(148, 0, 211)},
            {"deeppink", detail::rgb<T>(255, 20, 147)},
            {"deepskyblue", detail::rgb<T>(0, 191, 255)},
            {"dimgray", detail::rgb<T>(105, 105, 105)},
            {"dimgrey", detail::rgb<T>(105, 105, 105)},
            {"dodgerblue", detail::rgb<T>(30, 144, 255)},
            {"firebrick", detail::rgb<T>(178, 34, 34)},
            {"floralwhite", detail::rgb<T>(255, 250, 240)},
            {"forestgreen", detail::rgb<T>(34, 139, 34)},
            {"fuchsia", detail::rgb<T>(255, 0, 255)},
            {"gainsboro", detail::rgb<T>(220, 220, 220)},
            {"ghostwhite", detail::rgb<T>(248, 248, 255)},
            {"gold", detail::rgb<T>(255, 215, 0)},
            {"goldenrod", detail::rgb<T>(218, 165, 32)},
            {"gray", detail::rgb<T>(128, 128, 128)},
            {"grey", detail::rgb<T>(128, 128, 128)},
            {"green", detail::rgb<T>(0, 128, 0)},
            {"greenyellow", detail::rgb<T>(173, 255, 47)},
            {"honeydew", detail::rgb<T>(240, 255, 240)},
            {"hotpink", detail::rgb<T>(255, 105, 180)},
            {"indianred", detail::rgb<T>(205, 92, 92)},
            {"indigo", detail::rgb<T>(75, 0, 130)},
            {"ivory", detail::rgb<T>(255, 255, 240)},
            {"khaki", detail::rgb<T>(240, 230, 140)},
            {"lavender", detail::rgb<T>(230, 230, 250)},
            {"lavenderblush", detail::rgb<T>(255, 240, 245)},
            {"lawngreen", detail::rgb<T>(124, 252, 0)},
            {"lemonchiffon", detail::rgb<T>(255, 250, 205)},
            {"lightblue", detail::rgb<T>(173, 216, 230)},
            {"lightcoral", detail::rgb<T>(240, 128, 128)},
            {"lightcyan", detail::rgb<T>(224, 255, 255)},
            {"lightgoldenrodyellow", detail::rgb<T>(250, 250, 210)},
            {"lightgray", detail::rgb<T>(211, 211, 211)},
            {"lightgreen", detail::rgb<T>(144, 238, 144)},
            {"lightgrey", detail::rgb<T>(211, 211, 211)},
            {"lightpink", detail::rgb<T>(255, 182, 193)},
            {"lightsalmon", detail::rgb<T>(255, 160, 122)},
            {"lightseagreen", detail::rgb<T>(32, 178, 170)},
            {"lightskyblue", detail::rgb<T>(135, 206, 250)},
            {"lightslategray", detail::rgb<T>(119, 136, 153)},
            {"lightslategrey", detail::rgb<T>(119, 136, 153)},
            {"lightsteelblue", detail::rgb<T>(176, 196, 222)},
            {"lightyellow", detail::rgb<T>(255, 255, 224)},
            {"lime", detail::rgb<T>(0, 255, 0)},
            {"limegreen", detail::rgb<T>(50, 205, 50)},
            {"linen", detail::rgb<T>(250, 240, 230)},
            {"magenta", detail::rgb<T>(255, 0, 255)},
            {"maroon", detail::rgb<T>(128, 0, 0)},
            {"mediumaquamarine", detail::rgb<T>(102, 205, 170)},
            {"mediumblue", detail::rgb<T>(0, 0, 205)},
            {"mediumorchid", detail::rgb<T>(186, 85, 211)},
            {"mediumpurple", detail::rgb<T>(147, 112, 219)},
            {"mediumseagreen", detail::rgb<T>(60, 179, 113)},
            {"mediumslateblue", detail::rgb<T>(123, 104, 238)},
            {"mediumspringgreen", detail::rgb<T>(0, 250, 154)},
            {"mediumturquoise", detail::rgb<T>(72, 209, 204)},
            {"mediumvioletred", detail::rgb<T>(199, 21, 133)},
            {"midnightblue", detail::rgb<T>(25, 25, 112)},
            {"mintcream", detail::rgb<T>(245, 255, 250)},
            {"mistyrose", detail::rgb<T>(255, 228, 225)},
            {"moccasin", detail::rgb<T>(255, 228, 181)},
            {"navajowhite", detail::rgb<T>(255, 222, 173)},
            {"navy", detail::rgb<T>(0, 0, 128)},
            {"oldlace", detail::rgb<T>(253, 245, 230)},
            {"olive", detail::rgb<T>(128, 128, 0)},
            {"olivedrab", detail::rgb<T>(107, 142, 35)},
            {"orange", detail::rgb<T>(255, 165, 0)},
            {"orangered", detail::rgb<T>(255, 69, 0)},
            {"orchid", detail::rgb<T>(218, 112, 214)},
            {"palegoldenrod", detail::rgb<T>(238, 232, 170)},
            {"palegreen", detail::rgb<T>(152, 251, 152)},
            {"paleturquoise", detail::rgb<T>(175, 238, 238)},
            {"palevioletred", detail::rgb<T>(219, 112, 147)},
            {"papayawhip", detail::rgb<T>(255, 239, 213)},
            {"peachpuff", detail::rgb<T>(255, 218, 185)},
            {"peru", detail::rgb<T>(205, 133, 63)},
            {"pink", detail::rgb<T>(255, 192, 203)},
            {"plum", detail::rgb<T>(221, 160, 221)},
            {"powderblue", detail::rgb<T>(176, 224, 230)},
            {"purple", detail::rgb<T>(128, 0, 128)},
            {"red", detail::rgb<T>(255, 0, 0)},
            {"rosybrown", detail::rgb<T>(188, 143, 143)},
            {"royalblue", detail::rgb<T>(65, 105, 225)},
            {"saddlebrown", detail::rgb<T>(139, 69, 19)},
            {"salmon", detail::rgb<T>(250, 128, 114)},
            {"sandybrown", detail::rgb<T>(244, 164, 96)},
            {"seagreen", detail::rgb<T>(46, 139, 87)},
            {"seashell", detail::rgb<T>(255, 245, 238)},
            {"sienna", detail::rgb<T>(160, 82, 45)},
            {"silver", detail::rgb<T>(192, 192, 192)},
            {"skyblue", detail::rgb<T>(135, 206, 235)},
            {"slateblue", detail::rgb<T>(106, 90, 205)},
            {"slategray", detail::rgb<T>(112, 128, 144)},
            {"slategrey", detail::rgb<T>(112, 128, 144)},
            {"snow", detail::rgb<T>(255, 250, 250)},
            {"springgreen", detail::rgb<T>(0, 255, 127)},
            {"steelblue", detail::rgb<T>(70, 130, 180)},
            {"tan", detail::rgb<T>(210, 180, 140)},
            {"teal", detail::rgb<T>(0, 128, 128)},
            {"thistle", detail::rgb<T>(216, 191, 216)},
            {"tomato", detail::rgb<T>(255, 99, 71)},
            {"turquoise", detail::rgb<T>(64, 224, 208)},
            {"violet", detail::rgb<T>(238, 130, 238)},
            {"wheat", detail::rgb<T>(245, 222, 179)},
            {"white", detail::rgb<T>(255, 255, 255)},
            {"whitesmoke", detail::rgb<T>(245, 245, 245)},
            {"yellow", detail::rgb<T>(255, 255, 0)},
            {"yellowgreen", detail::rgb<T>(154, 205, 50)}
        };

        auto it = svgColors.find(_name);
        if (it != svgColors.end())
            return it->value;

        return detail::rgb<T>(0.0, 0.0, 0.0);
    }
}

#endif // CRUNCH_COLORS_HPP
