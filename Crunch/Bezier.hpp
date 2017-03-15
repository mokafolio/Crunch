#ifndef CRUNCH_BEZIER_HPP
#define CRUNCH_BEZIER_HPP

#include <Stick/DynamicArray.hpp>
#include <Crunch/GeometricFunc.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/UtilityFunc.hpp>
#include <Crunch/Rectangle.hpp>
#include <Crunch/NumericalFunc.hpp>

namespace crunch
{
    /**
     * @brief A cubic bezier curve consisting of two points and two handles.
     *
     * http://en.wikipedia.org/wiki/B%C3%A9zier_curve
     * This is losely based on paper.js implementation (www.paperjs.org)
     * see Curve.js https://github.com/paperjs/paper.js/blob/master/src/path/Curve.js
     *
     * @arg T The vector type that is used internally.
     */
    template<class T>
    class BezierCubic
    {
    public:

        /**
         * @brief The internal vector type of the curve.
         */
        typedef T VectorType;

        /**
         * @brief The floating point value type.
         */
        typedef typename VectorType::ValueType ValueType;

        /**
         * @brief The rectangle type.
         */
        typedef Rectangle<ValueType> RectangleType;

        /**
         * @brief A pair of two beziers.
         * @see subdivide
         */
        struct Pair
        {
            BezierCubic first;
            BezierCubic second;
        };

        /**
         * @brief Default Constructor.
         */
        BezierCubic();

        /**
         * @brief Constructs a Bezier from four points.
         * @param _pointOne The absolute starting point of the curve.
         * @param _handleOne The absolute position of the first control point/handle.
         * @param _handleTwo The absolute position of the second control point/handle.
         * @param _pointTwo The end point of the curve.
         */
        BezierCubic(const VectorType & _pointOne, const VectorType & _handleOne, const VectorType & _handleTwo, const VectorType & _pointTwo);

        /**
         * @brief Returns the position of the bezier curve at the provided parameter.
         * @param _t The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         */
        VectorType positionAt(ValueType _t) const;

        /**
         * @brief Returns the normalized normal (the direction perpendicular to the curve) at the provided parameter.
         * @param _t The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         */
        VectorType normalAt(ValueType _t) const;

        /**
         * @brief Returns the normalized tangent (the direction of the curve) at the provided parameter.
         * @param _t The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         */
        VectorType tangentAt(ValueType _t) const;

        /**
         * @brief Returns the curvature at the provided parameter.
         * @param _t The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         */
        ValueType curvatureAt(ValueType _t) const;

        /**
         * @brief Returns the angle in radians of the curve at the provided parameter.
         * @param _t The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         */
        ValueType angleAt(ValueType _t) const;

        /**
         * @brief Splits the curve at the provided paramter.
         * @param _t The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         * @return Returns a pair of two bezier curves, where the first element is the curve from 0 to _t and the second element
         * is the curve from _t to 1.
         */
        Pair subdivide(ValueType _t) const;

        /**
         * @brief Calculates a sub curve slice of this bezier curve.
         * @param _fromT The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         * @param _toT The parameter value in the range 0 (the beginning of the curve) to 1 (the end of the curve).
         * The to paramater should be bigger than the from parameter.
         * Note: The sampling is not linear, meaning i.e. that a _t of 0.5 most likely won't give you the middle of the curve.
         * @return The resulting curve of the slicing operation.
         */
        BezierCubic slice(ValueType _fromT, ValueType _toT) const;


        /**
         * @brief Calculates the closest curve parameter to a provided point and target distance.
         * @param _point The position that you want to find the closest parameter to.
         * @param _distance Outputs the distance from the provided position to the closest point on the curve.
         * @param _startT Limits the curve to a starting parameter.
         * @param _endT Limits the curve to an ending parameter.
         * @param _targetDistance Allows you to specify a target distance that the found position/parameter should keep compared to the
         * input position.
         * @return The resulting curve parameter.
         */
        ValueType closestParameter(const VectorType & _point, ValueType & _distance, ValueType _startT, ValueType _endT, ValueType _targetDistance) const;

        /**
         * @brief Calculates the closest curve parameter to a provided point and target distance.
         * @param _point The position that you want to find the closest parameter to.
         * @param _startT Limits the curve to a starting parameter.
         * @param _endT Limits the curve to an ending parameter.
         * @param _targetDistance Allows you to specify a target distance that the found position/parameter should keep compared to the
         * input position.
         * @return The resulting curve parameter.
         */
        ValueType closestParameter(const VectorType & _point, ValueType _startT = 0.0, ValueType _endT = 1.0, ValueType _targetDistance = 0.0) const;

        /**
         * @brief Calculates the closest point on the curve to a provided point and target distance.
         * @param _point The position that you want to find the closest position to.
         * @param _startT Limits the curve to a starting parameter.
         * @param _endT Limits the curve to an ending parameter.
         * @param _targetDistance Allows you to specify a target distance that the found position/parameter should keep compared to the
         * input position.
         * @return The closest point on the curve.
         */
        VectorType closestPoint(const VectorType & _point, ValueType _startT = 0.0, ValueType _endT = 1.0, ValueType _targetDistance = 0.0) const;

        /**
         * @brief Calculates the closest point on the curve to a provided point and target distance.
         * @param _point The position that you want to find the closest position to.
         * @param _distance Outputs the distance from the provided position to the closest point on the curve.
         * @param _startT Limits the curve to a starting parameter.
         * @param _endT Limits the curve to an ending parameter.
         * @param _targetDistance Allows you to specify a target distance that the found position/parameter should keep compared to the
         * input position.
         * @return The closest point on the curve.
         */
        VectorType closestPoint(const VectorType & _point, ValueType & _distance, ValueType _startT = 0.0, ValueType _endT = 1.0, ValueType _targetDistance = 0.0) const;

        /**
         * @brief Calculates the length of the curve.
         */
        ValueType length() const;

        /**
         * @brief Calculates the area of the curve.
         */
        ValueType area() const;

        /**
         * @brief Calculates the bounding rectangle of the curve.
         *
         * This only makes sense in 2D.
         *
         * @param _padding Can be used if you want to pad the bounds (i.e. for a path with a stroke)
         */
        RectangleType bounds(ValueType _padding = 0) const;

        /**
         * From paper.js src:
         * Returns the t values for the "peaks" of the curve. The peaks are
         * calculated by finding the roots of the dot product of the first and
         * second derivative.
         *
         * Peaks are locations sharing some qualities of curvature extrema but
         * are cheaper to compute. They fulfill their purpose here quite well.
         * See:
         * http://math.stackexchange.com/questions/1954845/bezier-curvature-extrema
         */
        void peaks(stick::DynamicArray<ValueType> & _peaks) const;

        /**
         * @brief Calculates the length of the curve between two parameters.
         * @param _t0 Parameter between 0 and 1.
         * @param _t1 Parameter between 0 and 1.
         */
        ValueType lengthBetween(ValueType _t0, ValueType _t1) const;

        /**
         * @brief Calculates the parameter of the curve at a specific offset.
         * @param _offset A value between 0 (the beginning of the curve) and length() (the end of the curve).
         */
        ValueType parameterAtOffset(ValueType _offset) const;

        /**
         * @brief Calculates the first derivate of the curve at the provided parameter.
         * @param _t Parameter between 0 and 1.
         */
        VectorType firstDerivateAt(ValueType _t) const;

        /**
         * @brief Calculates the second derivate of the curve at the provided parameter.
         * @param _t Parameter between 0 and 1.
         */
        VectorType secondDerivateAt(ValueType _t) const;

        /**
         * @brief Set the absolute position of the starting point of the curve.
         */
        void setPositionOne(const VectorType & _p);

        /**
         * @brief Set the absolute position of the first control point/handle.
         */
        void setHandleOne(const VectorType & _p);

        /**
         * @brief Set the absolute position of the second control point/handle.
         */
        void setHandleTwo(const VectorType & _p);

        /**
         * @brief Set the absolute position of the end point of the curve.
         */
        void setPositionTwo(const VectorType & _p);

        /**
         * @brief Returns the absolute starting point of the curve.
         */
        const VectorType & positionOne() const;

        /**
         * @brief Returns the absolute first control point/handle of the curve.
         */
        const VectorType & handleOne() const;

        /**
         * @brief Returns the absolute second control point/handle of the curve.
         */
        const VectorType & handleTwo() const;

        /**
         * @brief Returns the absolute end point of the curve.
         */
        const VectorType & positionTwo() const;

        /**
         * @brief Returns true if the curve is linear.
         *
         * A linear curve is a curve where the first handle and first point are identical
         * and the second handle and second point are identical.
         *
         * @param _epsilon An epsilon value that changes the tolerance of the internal calculation.
         */
        bool isLinear(ValueType _epsilon = std::numeric_limits<ValueType>::epsilon()) const;

        bool isStraight() const;

        stick::Int32 solveCubic(ValueType _val, stick::DynamicArray<ValueType> & _outRoots, bool _bHorizontal, ValueType _min = 0, ValueType _max = 1) const;


    private:

        static const ValueType s_tolerance;


        bool refine(const VectorType & _point, ValueType & _minDist, ValueType & _minT, ValueType _t, ValueType _startT, ValueType _endT, ValueType _targetDistance) const;

        void derivativeCoefficients(VectorType & _a, VectorType & _b, VectorType & _c) const;

        //arc length of bezier:
        //_t point on curve in range 0-1
        //_a, _b, _c bezier derivate coefficients
        static ValueType arcLength(ValueType _t, const VectorType & _a, const VectorType & _b, const VectorType & _c);

        static stick::UInt32 iterationCount(ValueType _t0, ValueType _t1);

        //Gauss-Legendre Numerical Integration, max 16 iterations at this point.
        ValueType integrateLength(ValueType _t0, ValueType _t1, const VectorType & _a, const VectorType & _b, const VectorType & _c) const;


        VectorType m_pointOne;
        VectorType m_pointTwo;
        VectorType m_handleOne;
        VectorType m_handleTwo;
    };

    template<class T>
    const typename BezierCubic<T>::ValueType BezierCubic<T>::s_tolerance = 10e-6;

    template<class T>
    BezierCubic<T>::BezierCubic() :
        m_pointOne(0),
        m_handleOne(0),
        m_handleTwo(0),
        m_pointTwo(0)
    {

    }

    template<class T>
    BezierCubic<T>::BezierCubic(const VectorType & _pointOne, const VectorType & _handleOne, const VectorType & _handleTwo, const VectorType & _pointTwo) :
        m_pointOne(_pointOne),
        m_handleOne(_handleOne),
        m_handleTwo(_handleTwo),
        m_pointTwo(_pointTwo)
    {

    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::positionAt(ValueType _t) const
    {
        if (_t == 0)
            return m_pointOne;
        if (_t == 1)
            return m_pointTwo;

        ValueType u = 1.0 - _t;
        ValueType tt = _t * _t;
        ValueType uu = u * u;
        ValueType uuu = uu * u;
        ValueType ttt = tt * _t;

        VectorType p = m_pointOne * uuu; //first term
        p += m_handleOne * 3 * uu * _t; //second term
        p += m_handleTwo * 3 * u * tt; //third term
        p += m_pointTwo * ttt; //fourth term

        return p;
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::normalAt(ValueType _t) const
    {
        VectorType tan = tangentAt(_t);
        return VectorType(-tan.y, tan.x);
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::tangentAt(ValueType _t) const
    {
        // Prevent tangents and normals of length 0:
        // http://stackoverflow.com/questions/10506868/
        if ((_t < s_tolerance && m_handleOne == m_pointOne)
                || (_t > 1 - s_tolerance && m_handleTwo == m_pointTwo))
        {
            return normalize(m_pointTwo - m_pointOne);
        }

        VectorType fd = firstDerivateAt(_t);

        return normalize(fd);
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::curvatureAt(ValueType _t) const
    {
        if (m_handleTwo == m_pointTwo && m_pointOne == m_handleOne)
            return 0;

        VectorType fd = firstDerivateAt(_t);
        VectorType sd = secondDerivateAt(_t);

        return (fd.x * sd.y - fd.y * sd.x) / std::pow(fd.x * fd.x + fd.y * fd.y, 3.0 / 2.0);
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::angleAt(ValueType _t) const
    {
        VectorType tangent = tangentAt(_t);
        return std::atan2(tangent.y, tangent.x);
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::firstDerivateAt(ValueType _t) const
    {
        ValueType u = 1.0 - _t;
        ValueType uu = u * u;
        ValueType tt = _t * _t;

        VectorType ret = m_pointOne * uu * -3;
        ret += m_handleOne * (3 * uu - 6 * u * _t);
        ret += m_handleTwo * (6 * u * _t - 3 * tt);
        ret += m_pointTwo * tt * 3;

        return ret;
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::secondDerivateAt(ValueType _t) const
    {
        ValueType t6 = 6 * _t;
        ValueType t18 = 3 * t6;

        VectorType ret = m_pointOne * (6 - t6);
        ret += m_handleOne * (-12 + t18);
        ret += m_handleTwo * (6 - t18);
        ret += m_pointTwo * t6;

        return ret;
    }

    template<class T>
    typename BezierCubic<T>::Pair BezierCubic<T>::subdivide(ValueType _t) const
    {
        VectorType v1, v2, v3, v4, v5, v6;

        ValueType u = 1 - _t;

        v1 = m_pointOne * u + m_handleOne * _t;
        v2 = m_handleOne * u + m_handleTwo * _t;
        v3 = m_handleTwo * u + m_pointTwo * _t;
        v4 = v1 * u + v2 * _t;
        v5 = v2 * u + v3 * _t;
        v6 = v4 * u + v5 * _t;

        STICK_ASSERT(!std::isnan(v1.x));
        STICK_ASSERT(!std::isnan(v1.y));

        STICK_ASSERT(!std::isnan(v2.x));
        STICK_ASSERT(!std::isnan(v2.y));

        STICK_ASSERT(!std::isnan(v3.x));
        STICK_ASSERT(!std::isnan(v3.y));

        STICK_ASSERT(!std::isnan(v4.x));
        STICK_ASSERT(!std::isnan(v4.y));

        STICK_ASSERT(!std::isnan(v5.x));
        STICK_ASSERT(!std::isnan(v5.y));

        STICK_ASSERT(!std::isnan(v6.x));
        STICK_ASSERT(!std::isnan(v6.y));

        return {BezierCubic(m_pointOne, v1, v4, v6), BezierCubic(v6, v5, v3, m_pointTwo)};
    }

    template<class T>
    BezierCubic<T> BezierCubic<T>::slice(ValueType _fromT, ValueType _toT) const
    {
        BezierCubic ret = *this;

        if (_fromT > 0)
            ret = subdivide(_fromT).second;

        // from paper.js source, function is called getPart in Curve.js
        // Interpolate the  parameter at 'to' in the new curve and
        // cut there.
        if (_toT < 1)
            ret = ret.subdivide((_toT - _fromT) / (1.0 - _fromT)).first;

        return ret;
    }

    namespace detail
    {
        template<class T>
        void setMinMax(T _value, T _padding, T & _inOutMin, T & _inOutMax)
        {
            T left = _value - _padding;
            T right = _value + _padding;

            if (left < _inOutMin)
                _inOutMin = left;

            if (right > _inOutMax)
                _inOutMax = right;
        }

        template<class T, class BT>
        void setMinMaxForRoots(const stick::DynamicArray<T> & _roots, T _tMin, T _tMax, T _padding, T & _inOutMin, T & _inOutMax, const BT & _bezier, bool _bX)
        {
            T t;
            auto it = _roots.begin();
            for (; it != _roots.end(); ++it)
            {
                t = *it;

                // Test for good roots and only add to bounds if good.
                if (_tMin < t && t < _tMax)
                {
                    setMinMax(_bX ? _bezier.positionAt(t).x : _bezier.positionAt(t).y, _padding, _inOutMin, _inOutMax);
                }
            }
        }
    }

    template<class T>
    typename BezierCubic<T>::RectangleType BezierCubic<T>::bounds(ValueType _padding) const
    {
        VectorType min;
        VectorType max;

        // From paper.js Curve.js:
        // Calculate derivative of our bezier polynomial, divided by 3.
        // Doing so allows for simpler calculations of a, b, c and leads to the
        // same quadratic roots.

        //TODO: Move derivate coefficient generation in seperate functions
        VectorType a = (m_handleOne - m_handleTwo) * 3.0 - m_pointOne + m_pointTwo;
        VectorType b = (m_pointOne + m_handleTwo) * 2.0 - m_handleOne * 4.0;
        VectorType c = m_handleOne - m_pointOne;

        //find quadratic roots for both axis
        stick::DynamicArray<ValueType> xRoots;
        solveQuadratic(a.x, b.x, c.x, xRoots);

        stick::DynamicArray<ValueType> yRoots;
        solveQuadratic(a.y, b.y, c.y, yRoots);

        //ignore the padding for points not in 0 < t < 1
        ValueType tMin = s_tolerance;
        ValueType tMax = 1.0 - s_tolerance;
        min = m_pointOne;
        max = m_pointOne;

        detail::setMinMax(m_pointTwo.x, (ValueType)0, min.x, max.x);
        detail::setMinMax(m_pointTwo.y, (ValueType)0, min.y, max.y);

        detail::setMinMaxForRoots(xRoots, tMin, tMax, _padding, min.x, max.x, *this, true);
        detail::setMinMaxForRoots(yRoots, tMin, tMax, _padding, min.y, max.y, *this, false);

        return RectangleType(min, max);
    }

    template<class T>
    void BezierCubic<T>::peaks(stick::DynamicArray<ValueType> & _peaks) const
    {
        ValueType ax = -m_pointOne.x + 3 * m_handleOne.x - 3 * m_handleTwo.x + m_pointTwo.x;
        ValueType bx = 3 * m_pointOne.x - 6 * m_handleOne.x + 3 * m_handleTwo.x;
        ValueType cx = -3 * m_pointOne.x + 3 * m_handleOne.x;
        ValueType ay = -m_pointOne.y + 3 * m_handleOne.y - 3 * m_handleTwo.y + m_pointTwo.y;
        ValueType by = 3 * m_pointOne.y - 6 * m_handleOne.y + 3 * m_handleTwo.y;
        ValueType cy = -3 * m_pointOne.y + 3 * m_handleOne.y;

        //@TODO: Double check if these epsilon values make sense (most likely need adjustment)
        ValueType tMin = std::numeric_limits<ValueType>::epsilon();
        ValueType tMax = 1.0 - tMin;
        crunch::solveCubic(9 * (ax * ax + ay * ay),
                           9 * (ax * bx + by * ay),
                           2 * (bx * bx + by * by) + 3 * (cx * ax + cy * ay),
                           (cx * bx + by * cy),
                           // Exclude 0 and 1 as we don't count them as peaks.
                           _peaks, tMin, tMax);
        
        std::sort(_peaks.begin(), _peaks.end());
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::area() const
    {
        // From paper.js Curve.js:
        // http://objectmix.com/graphics/133553-area-closed-bezier-curve.html
        return (  3.0 * m_handleOne.y * m_pointOne.x - 1.5 * m_handleOne.y * m_handleTwo.x
                  - 1.5 * m_handleOne.y * m_pointTwo.x - 3.0 * m_pointOne.y * m_handleOne.x
                  - 1.5 * m_pointOne.y * m_handleTwo.x - 0.5 * m_pointOne.y * m_pointTwo.x
                  + 1.5 * m_handleTwo.y * m_pointOne.x + 1.5 * m_handleTwo.y * m_handleOne.x
                  - 3.0 * m_handleTwo.y * m_pointTwo.x + 0.5 * m_pointTwo.y * m_pointOne.x
                  + 1.5 * m_pointTwo.y * m_handleOne.x + 3.0 * m_pointTwo.y * m_handleTwo.x) / 10.0;
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::closestParameter(const VectorType & _point, ValueType _startT, ValueType _endT, ValueType _targetDistance) const
    {
        ValueType dist;
        return closestParameter(_point, dist, _startT, _endT, _targetDistance);
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::closestParameter(const VectorType & _point, ValueType & _distance, ValueType _startT, ValueType _endT, ValueType _targetDistance) const
    {
        ValueType tolerance = s_tolerance;
        stick::UInt32 sampleCount = 100;
        ValueType minDist = std::numeric_limits<ValueType>::max();
        ValueType minT = _startT;

        ValueType sampleStepSize = (_endT - _startT) / (sampleCount - 1);

        //find the rough position
        for (stick::UInt32 i = 0; i < sampleCount; ++i)
        {
            refine(_point, minDist, minT, _startT + i * sampleStepSize, _startT, _endT, _targetDistance);
        }

        //refine the position
        sampleStepSize = 1.0 / (sampleCount * 2.0);
        while (sampleStepSize > tolerance)
        {
            if (!refine(_point, minDist, minT, minT - sampleStepSize, _startT, _endT, _targetDistance) &&
                    !refine(_point, minDist, minT, minT + sampleStepSize, _startT, _endT, _targetDistance))
            {
                sampleStepSize *= 0.5;
            }
        }

        _distance = minDist;
        return minT;
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::closestPoint(const VectorType & _point, ValueType _startT, ValueType _endT, ValueType _targetDistance) const
    {
        ValueType distance;
        return positionAt(closestParameter(_point, distance, _startT, _endT, _targetDistance));
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::closestPoint(const VectorType & _point, ValueType & _distance, ValueType _startT, ValueType _endT, ValueType _targetDistance) const
    {
        return positionAt(closestParameter(_point, _distance, _startT, _endT, _targetDistance));
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::length() const
    {
        auto ret = lengthBetween(0, 1);
        return std::isnan(ret) ? 0 : ret;
        //return ret;
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::lengthBetween(ValueType _t0, ValueType _t1) const
    {
        VectorType a, b, c;
        derivativeCoefficients(a, b, c);

        return integrateLength(_t0, _t1, a, b, c);
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::parameterAtOffset(ValueType _offset) const
    {
        //early out for zero case
        if (std::abs(_offset) <= std::numeric_limits<ValueType>::epsilon())
            return 0.0;

        bool bForward = _offset > 0;
        ValueType a = 0.0;
        ValueType b = 1.0;
        ValueType rangeLength = lengthBetween(a, b);

        ValueType offset = bForward ? _offset : rangeLength - abs(_offset);

        if (offset >= rangeLength)
            return bForward ? b : a;

        // Use offset / rangeLength for an initial guess for t, to
        // bring us closer:
        ValueType start = 0.0;
        ValueType guess = offset / rangeLength;
        guess = a + guess;

        ValueType length = 0.0;

        VectorType ca, cb, cc;
        derivativeCoefficients(ca, cb, cc);

        ValueType error = 1.0;

        stick::UInt32 numIters = 0;

        //refine the initial guess
        while (abs(error) > s_tolerance)
        {
            if (start == guess)
                break;

            if (start < guess)
                length += lengthBetween(start, guess);
            else
                length -= lengthBetween(guess, start);

            start = guess;

            //Root finding using Newton-Raphson Method combined with Bisection.

            //function result
            ValueType fGuess = length - offset;

            //derivative result
            error =  fGuess / arcLength(guess, ca, cb, cc);

            // See if we can trust the Newton-Raphson result. If not we use
            // bisection to find another candiate for Newton's method.
            if (abs(error) < s_tolerance) //early out
            {
                break;
            }

            // Generate a candidate for Newton's method.
            ValueType nextGuess = guess - error;

            // Update the root-bounding interval and test for containment of
            // the candidate. If candidate is outside the root-bounding
            // interval, use bisection instead.
            // There is no need to compare to lower / upper because the
            // tangent line has positive slope, guaranteeing that the x-axis
            // intercept is larger than lower / smaller than upper.
            if (fGuess > 0)
            {
                b = guess;
                guess = nextGuess <= a ? 0.5 * (a + b) : nextGuess;
            }
            else
            {
                a = guess;
                guess = nextGuess >= b ? 0.5 * (a + b) : nextGuess;
            }

            numIters++;
        }

        return guess;
    }

    template<class T>
    bool BezierCubic<T>::refine(const VectorType & _point, ValueType & _minDist, ValueType & _minT, ValueType _t, ValueType _startT, ValueType _endT, ValueType _targetDistance) const
    {
        if (_t >= _startT && _t <= _endT)
        {
            VectorType currentPoint = positionAt(_t);
            ValueType dist = abs(distance(_point, currentPoint) - _targetDistance);

            if (dist < _minDist)
            {
                _minDist = dist;
                _minT = _t;
                return true;
            }
        }
        return false;
    }

    template<class T>
    void BezierCubic<T>::derivativeCoefficients(VectorType & _a, VectorType & _b, VectorType & _c) const
    {
        _a = (m_handleOne - m_handleTwo) * 9 + (m_pointTwo - m_pointOne) * 3;
        _b = (m_pointOne + m_handleTwo) * 6 - m_handleOne * 12;
        _c = (m_handleOne - m_pointOne) * 3;
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::arcLength(ValueType _t, const VectorType & _a, const VectorType & _b, const VectorType & _c)
    {
        VectorType tmp = (_a * _t + _b) * _t + _c;
        return sqrt(tmp.x * tmp.x + tmp.y * tmp.y) + std::numeric_limits<ValueType>::min(); //to avoid returning 0 (and division by zero)
    }

    template<class T>
    stick::UInt32 BezierCubic<T>::iterationCount(ValueType _t0, ValueType _t1)
    {
        // Comment from PaperJS source, line 998 of Curve.js:
        // Guess required precision based on stick::Size of range...
        // TODO: There should be much better educated guesses for
        // this. Also, what does this depend on? Required precision?
        return crunch::max(2, crunch::min(16, static_cast<stick::Int32>((ceil(abs(_t1 - _t0) * 32)))));
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::integrateLength(ValueType _t0, ValueType _t1, const VectorType & _a, const VectorType & _b, const VectorType & _c) const
    {
        static const ValueType s_abscissas[16][8] =
        {
            {0.5773502691896257645091488},
            {0, 0.7745966692414833770358531},
            {0.3399810435848562648026658, 0.8611363115940525752239465},
            {0, 0.5384693101056830910363144, 0.9061798459386639927976269},
            {0.2386191860831969086305017, 0.6612093864662645136613996, 0.9324695142031520278123016},
            {0, 0.4058451513773971669066064, 0.7415311855993944398638648, 0.9491079123427585245261897},
            {0.1834346424956498049394761, 0.5255324099163289858177390, 0.7966664774136267395915539, 0.9602898564975362316835609},
            {0, 0.3242534234038089290385380, 0.6133714327005903973087020, 0.8360311073266357942994298, 0.9681602395076260898355762},
            {0.1488743389816312108848260, 0.4333953941292471907992659, 0.6794095682990244062343274, 0.8650633666889845107320967, 0.9739065285171717200779640},
            {0, 0.2695431559523449723315320, 0.5190961292068118159257257, 0.7301520055740493240934163, 0.8870625997680952990751578, 0.9782286581460569928039380},
            {0.1252334085114689154724414, 0.3678314989981801937526915, 0.5873179542866174472967024, 0.7699026741943046870368938, 0.9041172563704748566784659, 0.9815606342467192506905491},
            {0, 0.2304583159551347940655281, 0.4484927510364468528779129, 0.6423493394403402206439846, 0.8015780907333099127942065, 0.9175983992229779652065478, 0.9841830547185881494728294},
            {0.1080549487073436620662447, 0.3191123689278897604356718, 0.5152486363581540919652907, 0.6872929048116854701480198, 0.8272013150697649931897947, 0.9284348836635735173363911, 0.9862838086968123388415973},
            {0, 0.2011940939974345223006283, 0.3941513470775633698972074, 0.5709721726085388475372267, 0.7244177313601700474161861, 0.8482065834104272162006483, 0.9372733924007059043077589, 0.9879925180204854284895657},
            {0.0950125098376374401853193, 0.2816035507792589132304605, 0.4580167776572273863424194, 0.6178762444026437484466718, 0.7554044083550030338951012, 0.8656312023878317438804679, 0.9445750230732325760779884, 0.9894009349916499325961542}
        };

        static const ValueType s_weights[16][8] =
        {
            {1},
            {0.8888888888888888888888889, 0.5555555555555555555555556},
            {0.6521451548625461426269361, 0.3478548451374538573730639},
            {0.5688888888888888888888889, 0.4786286704993664680412915, 0.2369268850561890875142640},
            {0.4679139345726910473898703, 0.3607615730481386075698335, 0.1713244923791703450402961},
            {0.4179591836734693877551020, 0.3818300505051189449503698, 0.2797053914892766679014678, 0.1294849661688696932706114},
            {0.3626837833783619829651504, 0.3137066458778872873379622, 0.2223810344533744705443560, 0.1012285362903762591525314},
            {0.3302393550012597631645251, 0.3123470770400028400686304, 0.2606106964029354623187429, 0.1806481606948574040584720, 0.0812743883615744119718922},
            {0.2955242247147528701738930, 0.2692667193099963550912269, 0.2190863625159820439955349, 0.1494513491505805931457763, 0.0666713443086881375935688},
            {0.2729250867779006307144835, 0.2628045445102466621806889, 0.2331937645919904799185237, 0.1862902109277342514260976, 0.1255803694649046246346943, 0.0556685671161736664827537},
            {0.2491470458134027850005624, 0.2334925365383548087608499, 0.2031674267230659217490645, 0.1600783285433462263346525, 0.1069393259953184309602547, 0.0471753363865118271946160},
            {0.2325515532308739101945895, 0.2262831802628972384120902, 0.2078160475368885023125232, 0.1781459807619457382800467, 0.1388735102197872384636018, 0.0921214998377284479144218, 0.0404840047653158795200216},
            {0.2152638534631577901958764, 0.2051984637212956039659241, 0.1855383974779378137417166, 0.1572031671581935345696019, 0.1215185706879031846894148, 0.0801580871597602098056333, 0.0351194603317518630318329},
            {0.2025782419255612728806202, 0.1984314853271115764561183, 0.1861610000155622110268006, 0.1662692058169939335532009, 0.1395706779261543144478048, 0.1071592204671719350118695, 0.0703660474881081247092674, 0.0307532419961172683546284},
            {0.1894506104550684962853967, 0.1826034150449235888667637, 0.1691565193950025381893121, 0.1495959888165767320815017, 0.1246289712555338720524763, 0.0951585116824927848099251, 0.0622535239386478928628438, 0.0271524594117540948517806}
        };

        ValueType ret;

        // Comment from PaperJS source, line 998 of Curve.js:
        // Guess required precision based on stick::Size of range...
        // TODO: There should be much better educated guesses for
        // this. Also, what does this depend on? Required precision?
        stick::UInt32 iterationCount = max(2, min(16, static_cast<stick::Int32>((ceil(abs(_t1 - _t0) * 32)))));

        const ValueType * abscissas = s_abscissas[iterationCount - 2];
        const ValueType * weights = s_weights[iterationCount - 2];

        ValueType a = 0.5 * (_t1 - _t0);
        ValueType b = a + _t0;

        stick::UInt32 i = 0;
        stick::UInt32 lookUpCount = (iterationCount + 1) >> 1;
        ret = isOdd(iterationCount) ? weights[i++] * arcLength(b, _a, _b, _c) : 0;

        while (i < lookUpCount)
        {
            ValueType aa = a * abscissas[i];
            ret += weights[i++] * (arcLength(b + aa, _a, _b, _c) + arcLength(b - aa, _a, _b, _c));
        }

        return a * ret;
    }

    template<class T>
    void BezierCubic<T>::setPositionOne(const VectorType & _p)
    {
        m_pointOne = _p;
    }

    template<class T>
    void BezierCubic<T>::setHandleOne(const VectorType & _p)
    {
        m_handleOne = _p;
    }

    template<class T>
    void BezierCubic<T>::setHandleTwo(const VectorType & _p)
    {
        m_handleTwo = _p;
    }

    template<class T>
    void BezierCubic<T>::setPositionTwo(const VectorType & _p)
    {
        m_pointTwo = _p;
    }

    template<class T>
    const typename BezierCubic<T>::VectorType & BezierCubic<T>::positionOne() const
    {
        return m_pointOne;
    }

    template<class T>
    const typename BezierCubic<T>::VectorType & BezierCubic<T>::handleOne() const
    {
        return m_handleOne;
    }

    template<class T>
    const typename BezierCubic<T>::VectorType & BezierCubic<T>::handleTwo() const
    {
        return m_handleTwo;
    }

    template<class T>
    const typename BezierCubic<T>::VectorType & BezierCubic<T>::positionTwo() const
    {
        return m_pointTwo;
    }

    template<class T>
    bool BezierCubic<T>::isLinear(ValueType _epsilon) const
    {
        VectorType a = abs(m_pointOne - m_handleOne);
        VectorType b = abs(m_pointTwo - m_handleTwo);

        return isClose(a, VectorType(0), _epsilon) && isClose(b, VectorType(0), _epsilon);
    }

    template<class T>
    bool BezierCubic<T>::isStraight() const
    {
        if (isLinear())
            return true;

        VectorType line = positionTwo() - positionOne();

        // Zero-length line, with some handles defined.
        if (isClose(line, VectorType(0)))
            return false;

        if (isColinear(handleOne(), line) && isColinear(handleTwo(), line))
        {
            // Collinear handles. Project them onto line to see if they are
            // within the line's range:
            ValueType d = dot(line, line);
            ValueType p1 = dot(line, handleOne()) / d;
            ValueType p2 = dot(line, handleTwo()) / d;

            return p1 >= 0 && p1 <= 1 && p2 <= 0 && p2 >= -1;
        }

        return false;
    }

    template<class T>
    stick::Int32 BezierCubic<T>::solveCubic(ValueType _val, stick::DynamicArray<ValueType> & _outRoots, bool _bHorizontal, ValueType _min, ValueType _max) const
    {
        ValueType a, b, c, p1;
        if (_bHorizontal)
        {
            c = 3 * (m_handleOne.x - m_pointOne.x);
            b = 3 * (m_handleTwo.x - m_handleOne.x) - c;
            a = m_pointTwo.x - m_pointOne.x - c - b;
            p1 = m_pointOne.x;
        }
        else
        {
            c = 3 * (m_handleOne.y - m_pointOne.y);
            b = 3 * (m_handleTwo.y - m_handleOne.y) - c;
            a = m_pointTwo.y - m_pointOne.y - c - b;
            p1 = m_pointOne.y;
        }

        return crunch::solveCubic(a, b, c, p1 - _val, _outRoots, _min, _max);
    }

    typedef BezierCubic<Vector2<stick::Float32> > BezierCubic2f;
    typedef BezierCubic<Vector2<stick::Float64> > BezierCubic2d;
    typedef BezierCubic<Vector3<stick::Float32> > BezierCubic3f;
    typedef BezierCubic<Vector3<stick::Float64> > BezierCubic3d;
}

#endif //CRUNCH_BEZIER_HPP
