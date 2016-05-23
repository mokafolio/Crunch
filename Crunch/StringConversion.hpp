#ifndef CRUNCH_STRINGCONVERSION_HPP
#define CRUNCH_STRINGCONVERSION_HPP

#include <Stick/String.hpp>
#include <Stick/StringConversion.hpp>

namespace crunch
{
    template<class T>
    stick::String toString(const Vector2<T> & _vec, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "Vector2(",
                stick::toString(_vec.x, _alloc), ", ",
                stick::toString(_vec.y, _alloc), ")");
    }

    template<class T>
    stick::String toString(const Vector3<T> & _vec, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "Vector3(",
                stick::toString(_vec.x, _alloc), ", ",
                stick::toString(_vec.y, _alloc), ", ",
                stick::toString(_vec.z, _alloc), ")");
    }

    template<class T>
    stick::String toString(const Vector4<T> & _vec, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "Vector4(",
                stick::toString(_vec.x, _alloc), ", ",
                stick::toString(_vec.y, _alloc), ", ",
                stick::toString(_vec.z, _alloc), ", ",
                stick::toString(_vec.w, _alloc), ")");
    }

    template<class T>
    stick::String toString(const ColorGrayT<T> & _col, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "ColorGray(",
                stick::toString(_col.g, _alloc), ")");
    }

    template<class T>
    stick::String toString(const ColorRGBT<T> & _col, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "ColorRGB(",
                stick::toString(_col.r, _alloc), ", ",
                stick::toString(_col.g, _alloc), ", ",
                stick::toString(_col.b, _alloc), ")");
    }

    template<class T>
    stick::String toString(const ColorRGBAT<T> & _col, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "ColorRGBA(",
                stick::toString(_col.r, _alloc), ", ",
                stick::toString(_col.g, _alloc), ", ",
                stick::toString(_col.b, _alloc), ", ",
                stick::toString(_col.a, _alloc), ")");
    }

    template<class T>
    stick::String toString(const ColorHSBT<T> & _col, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "ColorHSB(",
                stick::toString(_col.h, _alloc), ", ",
                stick::toString(_col.s, _alloc), ", ",
                stick::toString(_col.b, _alloc), ")");
    }

    template<class T>
    stick::String toString(const ColorHSBAT<T> & _col, stick::Allocator & _alloc = stick::defaultAllocator())
    {
        return stick::String::concatWithAllocator(_alloc, "ColorHSBA(",
                stick::toString(_col.h, _alloc), ", ",
                stick::toString(_col.s, _alloc), ", ",
                stick::toString(_col.b, _alloc), ", ",
                stick::toString(_col.a, _alloc), ")");
    }
}

#endif //CRUNCH_STRINGCONVERSION_HPP
