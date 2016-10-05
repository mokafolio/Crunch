#ifndef CRUNCH_TILEDFRUSTUM_HPP
#define CRUNCH_TILEDFRUSTUM_HPP

#include <Crunch/Matrix4.hpp>
#include <Stick/DynamicArray.hpp>

namespace crunch
{
    template<class T = stick::Float32>
    struct STICK_API FrustumT
    {
    public:

        FrustumT()
        {
        }

        FrustumT(T _left, T _right, T _bottom,
                 T _top, T _near, T _far) :
            left(_left),
            right(_right),
            bottom(_bottom),
            top(_top),
            near(_near),
            far(_far),
            bOrtho(false)
        {

        }

        //TODO: Add support to extract the planes from an existing ortho / perspective matrix
        // i.e. so we can have overloads for fromPerspective / fromOrtho that take a Matrix4.

        static FrustumT fromPerspective(T _fovy, T _aspect, T _near, T _far)
        {
            auto planes = frustumPlanesFromPerspective(_fovy, _aspect, _near, _far);
            return FrustumT(planes[0], planes[1], planes[2], planes[3], planes[4], planes[5]);
        }

        static FrustumT fromOrtho(T _left, T _right, T _bottom,
                                  T _top, T _near, T _far)
        {
            FrustumT ret;
            ret.left = _left;
            ret.right = _right;
            ret.bottom = _bottom;
            ret.top = _top;
            ret.near = _near;
            ret.far = _far;
            ret.bOrtho = true;
            return ret;
        }

        T left, right, bottom, top, near, far;
        bool bOrtho;
    };

    using Frustum = FrustumT<>;

    template<class T = stick::Float32>
    struct FrustumTileT
    {
        stick::Size x, y;
        stick::Size pixelOffsetX, pixelOffsetY;
        Matrix4<T> frustum;
    };

    using FrustumTile = FrustumTileT<>;

    template<class T = stick::Float32>
    struct SubFrustumResultT
    {
        stick::DynamicArray<FrustumTileT<T>> tiles;
        stick::Size pixelWidth, pixelHeight;
        stick::Size tilePixelWidth, tilePixelHeight;
        stick::Size pixelBorderX, pixelBorderY;
    };

    using SubFrustumResult = SubFrustumResultT<>;

    template<class T>
    STICK_API inline SubFrustumResultT<T> subFrustum(const FrustumT<T> & _frustum, stick::Size _pixelWidth, stick::Size _pixelHeight,
            stick::Size _subdivisions, stick::Size _pixelBorder = 0)
    {
        stick::DynamicArray<FrustumTileT<T>> ret(_subdivisions * _subdivisions);
        T aspect = _pixelWidth / _pixelHeight;
        stick::Size vertPixelBorder = _pixelBorder / aspect;
        stick::Size width = (_pixelWidth - _pixelBorder * 2) * _subdivisions;
        stick::Size height = (_pixelHeight - vertPixelBorder * 2) * _subdivisions;
        stick::Size tmpWidth = _pixelWidth - _pixelBorder * 2;
        stick::Size tmpHeight = _pixelHeight - vertPixelBorder * 2;

        for (stick::Size x = 0; x < _subdivisions; ++x)
        {
            for (stick::Size y = 0; y < _subdivisions; ++y)
            {
                T left = _frustum.left + ((_frustum.right - _frustum.left) * ((T)x * tmpWidth - (T)_pixelBorder)) / width;
                T right = left + ((_frustum.right - _frustum.left) * _pixelWidth) / width;
                T bottom = _frustum.bottom + (_frustum.top - _frustum.bottom) * ((T)y * tmpHeight - (T)vertPixelBorder) / height;
                T top = bottom + ((_frustum.top - _frustum.bottom) * _pixelHeight) / height;
                if (!_frustum.bOrtho)
                    ret[x * _subdivisions + y] = {x, y, x * (stick::Size)tmpWidth, y * (stick::Size)tmpHeight, Matrix4<T>::frustum(left, right, bottom, top, _frustum.near, _frustum.far)};
                else
                    ret[x * _subdivisions + y] = {x, y, x * (stick::Size)tmpWidth, y * (stick::Size)tmpHeight, Matrix4<T>::ortho(left, right, bottom, top, _frustum.near, _frustum.far)};
            }
        }

        return {ret, static_cast<stick::Size>(width), static_cast<stick::Size>(height),
                static_cast<stick::Size>(tmpWidth), static_cast<stick::Size>(tmpHeight),
                static_cast<stick::Size>(_pixelBorder), static_cast<stick::Size>(vertPixelBorder)};
    }
}

#endif //CRUNCH_TILEDFRUSTUM_HPP
