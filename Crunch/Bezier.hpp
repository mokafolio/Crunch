#ifndef CRUNCH_BEZIER_HPP
#define CRUNCH_BEZIER_HPP

#include <Stick/DynamicArray.hpp>
#include <Stick/Variant.hpp>
#include <Crunch/LineSegment.hpp>
#include <Crunch/Line.hpp>
#include <Crunch/GeometricFunc.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/UtilityFunc.hpp>
#include <Crunch/Rectangle.hpp>
#include <Crunch/NumericalFunc.hpp>
#include <Crunch/TrigonometryFunc.hpp>

namespace crunch
{
    /**
     * @brief For classifying curves.
     */
    enum class CurveType
    {
        Line,
        Quadratic,
        Serpentine,
        Cusp,
        Loop,
        Arch
    };

    template<class T>
    struct ClassificationResult
    {
        CurveType type;
        SolveResult<T> roots;
    };

    namespace detail
    {
        template<class T>
        struct BezierTraits;

        template<>
        struct BezierTraits<stick::Float32>
        {
            //@TODO: These are just good guesses right now
            constexpr static stick::Float32 epsilon = 1e-5f;
            constexpr static stick::Float32 machineEpsilon = std::numeric_limits<stick::Float32>::epsilon();
            constexpr static stick::Float32 curveTimeEpsilon = 1e-3f;
            constexpr static stick::Float32 fatLineEpsilon = 1e-5f;
            constexpr static stick::Float32 geometricEpsilon = 1e-3f;
            constexpr static stick::Float32 trigonometricEpsilon = 1e-4f;
        };

        template<>
        struct BezierTraits<stick::Float64>
        {
            //based on the values used in paper.js
            constexpr static stick::Float64 epsilon = 1e-12;
            constexpr static stick::Float64 machineEpsilon = std::numeric_limits<stick::Float64>::epsilon();
            constexpr static stick::Float64 curveTimeEpsilon = 1e-8;
            constexpr static stick::Float64 fatLineEpsilon = 1e-9f;
            constexpr static stick::Float64 geometricEpsilon = 1e-7;
            constexpr static stick::Float64 trigonometricEpsilon = 1e-8;
        };
    }

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

        constexpr static ValueType epsilon = detail::BezierTraits<ValueType>::epsilon;
        constexpr static ValueType machineEpsilon = detail::BezierTraits<ValueType>::machineEpsilon;
        constexpr static ValueType curveTimeEpsilon = detail::BezierTraits<ValueType>::curveTimeEpsilon;
        constexpr static ValueType geometricEpsilon = detail::BezierTraits<ValueType>::geometricEpsilon;
        constexpr static ValueType trigonometricEpsilon = detail::BezierTraits<ValueType>::trigonometricEpsilon;
        constexpr static ValueType fatLineEpsilon = detail::BezierTraits<ValueType>::fatLineEpsilon;

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

        ValueType parameterOf(const VectorType & _point) const;

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

        RectangleType handleBounds() const;

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

        struct PeaksResult
        {
            ValueType values[3];
            stick::Int32 count;
        };

        PeaksResult peaks() const;


        struct ExtremaResult
        {
            ValueType values[4];
            stick::Int32 count;
        };

        ExtremaResult extrema2D() const;

        static void extrema(ValueType _a, ValueType _b, ValueType _c, ExtremaResult & _outResult);

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
        bool isLinear(ValueType _epsilon = geometricEpsilon) const;

        bool isStraight() const;

        SolveResult<ValueType> solveCubic(ValueType _val, bool _bHorizontal, ValueType _min = 0, ValueType _max = 1) const;

        ClassificationResult<ValueType> classify() const;

        struct IntersectionResult
        {
            struct Intersection
            {
                ValueType parameterOne;
                ValueType parameterTwo;
                VectorType position;
            };

            inline void append(ValueType _parameterOne, ValueType _parameterTwo, const VectorType & _pos)
            {
                STICK_ASSERT(count < 9);
                values[count++] = {_parameterOne, _parameterTwo, _pos};
            }

            //Even though technically there can only be 9 intersections between two curves
            //due to floating point inacuracies and the iterative approach with overlapping
            //curves there might be more (false) ones. Hence we should make this a dynamic array for
            //now until we have a proper way of dealing with overlaps??. @TODOOOO!!!1111
            Intersection values[9];
            stick::Int32 count = 0;
        };

        IntersectionResult overlaps(const BezierCubic & _other) const;

        IntersectionResult intersections(const BezierCubic & _other) const;

        void derivativeCoefficients(VectorType & _a, VectorType & _b, VectorType & _c) const;


        struct Arc
        {
            bool isClockwise() const
            {
                return sweepAngle > 0;
            }

            VectorType center;
            VectorType start;
            VectorType end;
            ValueType radius;
            ValueType startAngle;
            ValueType sweepAngle;
        };

        struct Biarc
        {
            Arc first;
            Arc second;
        };

        struct PointPair
        {
            VectorType first;
            VectorType second;
        };

        using BiarcResult = stick::Variant<Biarc, PointPair>;
        using BiarcResultArray = stick::DynamicArray<BiarcResult>;

        SolveResult<ValueType> inflections(ValueType _minParameter = curveTimeEpsilon, ValueType _maxParameter = 1 - curveTimeEpsilon) const;

        void biarcs(BiarcResultArray & _outArcs, ValueType _tolerance) const;

        static ValueType arcLength(ValueType _t, const VectorType & _a, const VectorType & _b, const VectorType & _c);

    private:

        bool refine(const VectorType & _point, ValueType & _minDist, ValueType & _minT, ValueType _t, ValueType _startT, ValueType _endT, ValueType _targetDistance) const;

        static stick::UInt32 iterationCount(ValueType _t0, ValueType _t1);

        //Gauss-Legendre Numerical Integration, max 16 iterations at this point.
        // ValueType integrateLength(ValueType _t0, ValueType _t1, const VectorType & _a, const VectorType & _b, const VectorType & _c) const;


        VectorType m_pointOne;
        VectorType m_handleOne;
        VectorType m_handleTwo;
        VectorType m_pointTwo;
    };

    namespace detail
    {
        template<class BezierType>
        struct LengthIntegrand
        {
            using VectorType = typename BezierType::VectorType;
            using ValueType = typename BezierType::ValueType;

            LengthIntegrand(const BezierType & _curve)
            {
                _curve.derivativeCoefficients(a, b, c);
            }

            ValueType operator () (ValueType _t) const
            {
                return BezierType::arcLength(_t, a, b, c);
            }

            VectorType a, b, c;
        };
    }

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
        return VectorType(tan.y, -tan.x);
    }

    template<class T>
    typename BezierCubic<T>::VectorType BezierCubic<T>::tangentAt(ValueType _t) const
    {
        // Prevent tangents and normals of length 0:
        // http://stackoverflow.com/questions/10506868/
        if ((_t < curveTimeEpsilon && m_handleOne == m_pointOne)
                || (_t > 1 - curveTimeEpsilon && m_handleTwo == m_pointTwo))
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

        //@TODO: I imagine these are not needed anymore? :D
        
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
        bool bFlip = _fromT > _toT;
        BezierCubic ret = *this;

        if (_fromT > 0)
            ret = subdivide(_fromT).second;

        // from paper.js source, function is called getPart in Curve.js
        // Interpolate the  parameter at 'to' in the new curve and
        // cut there.
        if (_toT < 1)
            ret = ret.subdivide((_toT - _fromT) / (1.0 - _fromT)).first;

        if (!bFlip)
            return ret;
        else
            return BezierCubic(ret.m_pointTwo, ret.m_handleTwo, ret.m_handleOne, ret.m_pointOne);
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
        void setMinMaxForRoots(const SolveResult<T> & _roots, T _tMin, T _tMax, T _padding, T & _inOutMin, T & _inOutMax, const BT & _bezier, bool _bX)
        {
            for (stick::Int32 i = 0; i < _roots.count; ++i)
            {
                // Test for good roots and only add to bounds if good.
                if (_tMin < _roots.values[i] && _roots.values[i] < _tMax)
                {
                    setMinMax(_bX ? _bezier.positionAt(_roots.values[i]).x : _bezier.positionAt(_roots.values[i]).y, _padding, _inOutMin, _inOutMax);
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

        //@TODO: Move derivate coefficient generation in seperate functions
        //@TODO: Does that still make sense? Moka, 03/15/17
        VectorType a = (m_handleOne - m_handleTwo) * 3.0 - m_pointOne + m_pointTwo;
        VectorType b = (m_pointOne + m_handleTwo) * 2.0 - m_handleOne * 4.0;
        VectorType c = m_handleOne - m_pointOne;

        //find quadratic roots for both axis (2d extrema)
        auto xRoots = solveQuadratic(a.x, b.x, c.x);
        auto yRoots = solveQuadratic(a.y, b.y, c.y);

        //ignore the padding for points not in 0 < t < 1
        ValueType tMin = curveTimeEpsilon;
        ValueType tMax = 1.0 - curveTimeEpsilon;
        min = m_pointOne;
        max = m_pointOne;

        detail::setMinMax(m_pointTwo.x, (ValueType)0, min.x, max.x);
        detail::setMinMax(m_pointTwo.y, (ValueType)0, min.y, max.y);

        detail::setMinMaxForRoots(xRoots, tMin, tMax, _padding, min.x, max.x, *this, true);
        detail::setMinMaxForRoots(yRoots, tMin, tMax, _padding, min.y, max.y, *this, false);

        return RectangleType(min, max);
    }

    template<class T>
    typename BezierCubic<T>::RectangleType BezierCubic<T>::handleBounds() const
    {
        return RectangleType(min(m_pointOne, min(m_pointTwo, min(m_handleOne, m_handleTwo))),
                             max(m_pointOne, max(m_pointTwo, max(m_handleOne, m_handleTwo))));
    }

    template<class T>
    typename BezierCubic<T>::PeaksResult BezierCubic<T>::peaks() const
    {
        ValueType ax = -m_pointOne.x + 3 * m_handleOne.x - 3 * m_handleTwo.x + m_pointTwo.x;
        ValueType bx = 3 * m_pointOne.x - 6 * m_handleOne.x + 3 * m_handleTwo.x;
        ValueType cx = -3 * m_pointOne.x + 3 * m_handleOne.x;
        ValueType ay = -m_pointOne.y + 3 * m_handleOne.y - 3 * m_handleTwo.y + m_pointTwo.y;
        ValueType by = 3 * m_pointOne.y - 6 * m_handleOne.y + 3 * m_handleTwo.y;
        ValueType cy = -3 * m_pointOne.y + 3 * m_handleOne.y;

        //@TODO: Double check if these epsilon values make sense (most likely need adjustment)
        ValueType tMin = curveTimeEpsilon;
        ValueType tMax = 1.0 - curveTimeEpsilon;
        auto res = crunch::solveCubic(9 * (ax * ax + ay * ay),
                                      9 * (ax * bx + by * ay),
                                      2 * (bx * bx + by * by) + 3 * (cx * ax + cy * ay),
                                      (cx * bx + by * cy),
                                      // Exclude 0 and 1 as we don't count them as peaks.
                                      tMin, tMax);

        //@TODO: Should we sort here at all? I think either both, extrema2D and this should
        //be sorted or not.
        std::sort(&res.values[0], &res.values[0] + res.count);

        PeaksResult ret;
        ret.count = res.count;
        for (stick::Int32 i = 0; i < res.count; ++i)
            ret.values[i] = res.values[i];
        return ret;
    }

    template<class T>
    typename BezierCubic<T>::ExtremaResult BezierCubic<T>::extrema2D() const
    {
        // From paper.js Curve.js:
        // Calculate derivative of our bezier polynomial, divided by 3.
        // Doing so allows for simpler calculations of a, b, c and leads to the
        // same quadratic roots.

        //@TODO: Move derivate coefficient generation in seperate functions
        //@TODO: Does that still make sense? Moka, 03/15/17
        VectorType a = (m_handleOne - m_handleTwo) * 3.0 - m_pointOne + m_pointTwo;
        VectorType b = (m_pointOne + m_handleTwo) * 2.0 - m_handleOne * 4.0;
        VectorType c = m_handleOne - m_pointOne;

        //find quadratic roots for both axis
        ExtremaResult res;
        res.count = 0;
        extrema(a.x, b.x, c.x, res);
        extrema(a.y, b.y, c.y, res);

        return res;
    }

    template<class T>
    void BezierCubic<T>::extrema(ValueType _a, ValueType _b, ValueType _c, ExtremaResult & _outResult)
    {
        auto res = solveQuadratic(_a, _b, _c);
        for (stick::Int32 i = 0; i < res.count; ++i)
            _outResult.values[_outResult.count++] = res.values[i];
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
        //@TODO: Update this to the current implementation in paper.js (Moka @ 03/23/2017)
        ValueType tolerance = curveTimeEpsilon;
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
    typename BezierCubic<T>::ValueType BezierCubic<T>::parameterOf(const VectorType & _point) const
    {
        // Before solving cubics, compare the beginning and end of the curve
        // with zero epsilon:
        if (!isClose(m_pointOne, _point) && !isClose(m_pointTwo, _point))
        {
            // printf("SOLVE CUBIC\n");
            // Solve the cubic for both x- and y-coordinates and consider all
            // solutions, testing with the larger / looser geometric epsilon.
            auto resultHor = solveCubic(_point.x, true, (ValueType)0, (ValueType)1);
            for (stick::Int32 i = 0; i < resultHor.count; i++)
            {
                if (isClose(_point, positionAt(resultHor.values[i]), geometricEpsilon))
                    return resultHor.values[i];
            }

            auto resultVert = solveCubic(_point.y, false, (ValueType)0, (ValueType)1);
            for (stick::Int32 i = 0; i < resultVert.count; i++)
            {
                if (isClose(_point, positionAt(resultVert.values[i]), geometricEpsilon))
                    return resultVert.values[i];
            }
        }
        else if (isClose(m_pointOne, _point, geometricEpsilon))
        {
            // printf("START\n");
            return 0;
        }
        else if (isClose(m_pointTwo, _point, geometricEpsilon))
        {
            // printf("END\n");
            return 1;
        }

        return -1;
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::length() const
    {
        auto ret = lengthBetween(0, 1);
        //@TODO: Does this still happen?
        //I don't think this check should be here 03/26/2017, Moka
        return std::isnan(ret) ? 0 : ret;
        //return ret;
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::lengthBetween(ValueType _t0, ValueType _t1) const
    {
        // Comment from PaperJS source in Curve.js:
        // Guess required precision based on stick::Size of range...
        // TODO: There should be much better educated guesses for
        // this. Also, what does this depend on? Required precision?
        stick::UInt32 iterationCount = max(2, min(16, static_cast<stick::Int32>((ceil(abs(_t1 - _t0) * 32)))));

        return integrate(detail::LengthIntegrand<BezierCubic>(*this), _t0, _t1, iterationCount);
    }

    template<class T>
    typename BezierCubic<T>::ValueType BezierCubic<T>::parameterAtOffset(ValueType _offset) const
    {
        //@TODO: Update this to the current implementation in paper.js (Moka @ 03/23/2017)

        //early out for zero case
        if (std::abs(_offset) <= epsilon)
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
        while (abs(error) > epsilon)
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
            if (abs(error) < epsilon) //early out
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

    // template<class T>
    // typename BezierCubic<T>::ValueType BezierCubic<T>::integrateLength(ValueType _t0, ValueType _t1, const VectorType & _a, const VectorType & _b, const VectorType & _c) const
    // {
    //     static const ValueType s_abscissas[16][8] =
    //     {
    //         {0.5773502691896257645091488},
    //         {0, 0.7745966692414833770358531},
    //         {0.3399810435848562648026658, 0.8611363115940525752239465},
    //         {0, 0.5384693101056830910363144, 0.9061798459386639927976269},
    //         {0.2386191860831969086305017, 0.6612093864662645136613996, 0.9324695142031520278123016},
    //         {0, 0.4058451513773971669066064, 0.7415311855993944398638648, 0.9491079123427585245261897},
    //         {0.1834346424956498049394761, 0.5255324099163289858177390, 0.7966664774136267395915539, 0.9602898564975362316835609},
    //         {0, 0.3242534234038089290385380, 0.6133714327005903973087020, 0.8360311073266357942994298, 0.9681602395076260898355762},
    //         {0.1488743389816312108848260, 0.4333953941292471907992659, 0.6794095682990244062343274, 0.8650633666889845107320967, 0.9739065285171717200779640},
    //         {0, 0.2695431559523449723315320, 0.5190961292068118159257257, 0.7301520055740493240934163, 0.8870625997680952990751578, 0.9782286581460569928039380},
    //         {0.1252334085114689154724414, 0.3678314989981801937526915, 0.5873179542866174472967024, 0.7699026741943046870368938, 0.9041172563704748566784659, 0.9815606342467192506905491},
    //         {0, 0.2304583159551347940655281, 0.4484927510364468528779129, 0.6423493394403402206439846, 0.8015780907333099127942065, 0.9175983992229779652065478, 0.9841830547185881494728294},
    //         {0.1080549487073436620662447, 0.3191123689278897604356718, 0.5152486363581540919652907, 0.6872929048116854701480198, 0.8272013150697649931897947, 0.9284348836635735173363911, 0.9862838086968123388415973},
    //         {0, 0.2011940939974345223006283, 0.3941513470775633698972074, 0.5709721726085388475372267, 0.7244177313601700474161861, 0.8482065834104272162006483, 0.9372733924007059043077589, 0.9879925180204854284895657},
    //         {0.0950125098376374401853193, 0.2816035507792589132304605, 0.4580167776572273863424194, 0.6178762444026437484466718, 0.7554044083550030338951012, 0.8656312023878317438804679, 0.9445750230732325760779884, 0.9894009349916499325961542}
    //     };

    //     static const ValueType s_weights[16][8] =
    //     {
    //         {1},
    //         {0.8888888888888888888888889, 0.5555555555555555555555556},
    //         {0.6521451548625461426269361, 0.3478548451374538573730639},
    //         {0.5688888888888888888888889, 0.4786286704993664680412915, 0.2369268850561890875142640},
    //         {0.4679139345726910473898703, 0.3607615730481386075698335, 0.1713244923791703450402961},
    //         {0.4179591836734693877551020, 0.3818300505051189449503698, 0.2797053914892766679014678, 0.1294849661688696932706114},
    //         {0.3626837833783619829651504, 0.3137066458778872873379622, 0.2223810344533744705443560, 0.1012285362903762591525314},
    //         {0.3302393550012597631645251, 0.3123470770400028400686304, 0.2606106964029354623187429, 0.1806481606948574040584720, 0.0812743883615744119718922},
    //         {0.2955242247147528701738930, 0.2692667193099963550912269, 0.2190863625159820439955349, 0.1494513491505805931457763, 0.0666713443086881375935688},
    //         {0.2729250867779006307144835, 0.2628045445102466621806889, 0.2331937645919904799185237, 0.1862902109277342514260976, 0.1255803694649046246346943, 0.0556685671161736664827537},
    //         {0.2491470458134027850005624, 0.2334925365383548087608499, 0.2031674267230659217490645, 0.1600783285433462263346525, 0.1069393259953184309602547, 0.0471753363865118271946160},
    //         {0.2325515532308739101945895, 0.2262831802628972384120902, 0.2078160475368885023125232, 0.1781459807619457382800467, 0.1388735102197872384636018, 0.0921214998377284479144218, 0.0404840047653158795200216},
    //         {0.2152638534631577901958764, 0.2051984637212956039659241, 0.1855383974779378137417166, 0.1572031671581935345696019, 0.1215185706879031846894148, 0.0801580871597602098056333, 0.0351194603317518630318329},
    //         {0.2025782419255612728806202, 0.1984314853271115764561183, 0.1861610000155622110268006, 0.1662692058169939335532009, 0.1395706779261543144478048, 0.1071592204671719350118695, 0.0703660474881081247092674, 0.0307532419961172683546284},
    //         {0.1894506104550684962853967, 0.1826034150449235888667637, 0.1691565193950025381893121, 0.1495959888165767320815017, 0.1246289712555338720524763, 0.0951585116824927848099251, 0.0622535239386478928628438, 0.0271524594117540948517806}
    //     };

    //     ValueType ret;

    //     // Comment from PaperJS source, line 998 of Curve.js:
    //     // Guess required precision based on stick::Size of range...
    //     // TODO: There should be much better educated guesses for
    //     // this. Also, what does this depend on? Required precision?
    //     stick::UInt32 iterationCount = max(2, min(16, static_cast<stick::Int32>((ceil(abs(_t1 - _t0) * 32)))));

    //     const ValueType * abscissas = s_abscissas[iterationCount - 2];
    //     const ValueType * weights = s_weights[iterationCount - 2];

    //     ValueType a = 0.5 * (_t1 - _t0);
    //     ValueType b = a + _t0;

    //     stick::UInt32 i = 0;
    //     stick::UInt32 lookUpCount = (iterationCount + 1) >> 1;
    //     ret = isOdd(iterationCount) ? weights[i++] * arcLength(b, _a, _b, _c) : 0;

    //     while (i < lookUpCount)
    //     {
    //         ValueType aa = a * abscissas[i];
    //         ret += weights[i++] * (arcLength(b + aa, _a, _b, _c) + arcLength(b - aa, _a, _b, _c));
    //     }

    //     return a * ret;
    // }

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
        //@TODO: Update this to the current implementation in paper.js (Moka @ 03/23/2017)
        VectorType a = abs(m_pointOne - m_handleOne);
        VectorType b = abs(m_pointTwo - m_handleTwo);

        return isClose(a, VectorType(0), _epsilon) && isClose(b, VectorType(0), _epsilon);
    }

    template<class T>
    bool BezierCubic<T>::isStraight() const
    {
        //@TODO: Update this to the current implementation in paper.js (Moka @ 03/23/2017)
        if (isLinear())
            return true;

        VectorType line = positionTwo() - positionOne();

        // Zero-length line, with some handles defined.
        if (isClose(line, VectorType(0)))
            return false;

        if (isCollinear(handleOne(), line, geometricEpsilon) && isCollinear(handleTwo(), line, geometricEpsilon))
        {
            // Collinear handles. Project them onto line to see if they are
            // within the line's range:

            Line<VectorType> l = Line<VectorType>::fromPoints(m_pointOne, m_pointTwo);
            if (l.distance(m_handleOne) < geometricEpsilon &&
                    l.distance(m_handleTwo) < geometricEpsilon)
            {
                ValueType d = dot(line, line);
                ValueType p1 = dot(line, handleOne()) / d;
                ValueType p2 = dot(line, handleTwo()) / d;

                return p1 >= 0 && p1 <= 1 && p2 <= 0 && p2 >= -1;
            }
        }

        return false;
    }

    template<class T>
    SolveResult<typename BezierCubic<T>::ValueType> BezierCubic<T>::solveCubic(ValueType _val, bool _bHorizontal, ValueType _min, ValueType _max) const
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

        return crunch::solveCubic(a, b, c, p1 - _val, _min, _max);
    }

    namespace detail
    {
        template<class T>
        inline ClassificationResult<T> classificationHelperImpl(CurveType _type, T * _rootA, T * _rootB)
        {
            bool bHasRoots = _rootA != nullptr;
            bool t1Ok = _rootA && *_rootA > 0 && *_rootA < 1;
            bool t2Ok = _rootB && *_rootB > 0 && *_rootB < 1;

            // Degrade to arch for serpentine, cusp or loop if no solutions
            // within 0..1 are found. loop requires 2 solutions to be valid.
            if (bHasRoots && (!(t1Ok || t2Ok) || (_type == CurveType::Loop && !(t1Ok && t2Ok))))
            {
                _type = CurveType::Arch;
                t1Ok = t2Ok = false;
            }
            SolveResult<T> roots;
            if (t1Ok)
                roots.append(*_rootA);
            if (t2Ok)
                roots.append(*_rootB);
            std::sort(&roots.values[0], &roots.values[0] + roots.count);
            return {_type, roots};
        }

        template<class T>
        inline ClassificationResult<T> classificationHelper(CurveType _type, T _rootA, T _rootB)
        {
            return classificationHelperImpl<T>(_type, &_rootA, &_rootB);
        }

        template<class T>
        inline ClassificationResult<T> classificationHelper(CurveType _type, T _rootA)
        {
            return classificationHelperImpl<T>(_type, &_rootA, nullptr);
        }

        template<class T>
        inline ClassificationResult<T> classificationHelper(CurveType _type)
        {
            return classificationHelperImpl<T>(_type, nullptr, nullptr);
        }
    }

    template<class T>
    ClassificationResult<typename BezierCubic<T>::ValueType> BezierCubic<T>::classify() const
    {
        // See: Loop and Blinn, 2005, Resolution Independent Curve Rendering
        // using Programmable Graphics Hardware, GPU Gems 3 chapter 25
        //
        // Possible types:
        //   'line'       (d1 == d2 == d3 == 0)
        //   'quadratic'  (d1 == d2 == 0)
        //   'serpentine' (d > 0)
        //   'cusp'       (d == 0)
        //   'loop'       (d < 0)
        //   'arch'       (serpentine, cusp or loop with roots outside 0..1)
        //
        // NOTE: Roots for serpentine, cusp and loop curves are only
        // considered if they are within 0..1. If the roots are outside,
        // then we degrade the type of curve down to an 'arch'.

        // Calculate coefficients of I(s, t), of which the roots are
        // inflection points.
        ValueType a1 = m_pointOne.x * (m_pointTwo.y - m_handleTwo.y) + m_pointOne.y * (m_handleTwo.x - m_pointTwo.x) + m_pointTwo.x * m_handleTwo.y - m_pointTwo.y * m_handleTwo.x;
        ValueType a2 = m_handleOne.x * (m_pointOne.y - m_pointTwo.y) + m_handleOne.y * (m_pointTwo.x - m_pointOne.x) + m_pointOne.x * m_pointTwo.y - m_pointOne.y * m_pointTwo.x;
        ValueType a3 = m_handleTwo.x * (m_handleOne.y - m_pointOne.y) + m_handleTwo.y * (m_pointOne.x - m_handleOne.x) + m_handleOne.x * m_pointOne.y - m_handleOne.y * m_pointOne.x;
        ValueType d3 = 3 * a3;
        ValueType d2 = d3 - a2;
        ValueType d1 = d2 - a2 + a1;

        // Normalize the vector (d1, d2, d3) to keep error consistent.
        ValueType l = std::sqrt(d1 * d1 + d2 * d2 + d3 * d3);
        ValueType s = l != 0 ? 1 / l : 0;

        d1 *= s;
        d2 *= s;
        d3 *= s;

        if (isClose(d1, (ValueType)0.0))
        {
            if (isClose(d2, (ValueType)0.0))
            {
                if (isClose(d3, (ValueType)0.0))
                {
                    return detail::classificationHelper<ValueType>(CurveType::Line); // 5.
                }
                else
                {
                    return detail::classificationHelper<ValueType>(CurveType::Quadratic); // 4.
                }
            }
            else
            {
                return detail::classificationHelper<ValueType>(CurveType::Serpentine, d3 / (3 * d2)); // 3b.
            }
        }

        ValueType d = 3 * d2 * d2 - 4 * d1 * d3;
        if (isClose(d, (ValueType)0.0))
        {
            return detail::classificationHelper<ValueType>(CurveType::Cusp, d2 / (2 * d1)); // 3a.
        }

        ValueType f1 = d > 0 ? std::sqrt(d / 3) : std::sqrt(-d);
        ValueType f2 = 2 * d1;
        if (d > 0)
        {
            return detail::classificationHelper<ValueType>(CurveType::Serpentine, (d2 + f1) / f2, (d2 - f1) / f2); // 1.
        }
        else
        {
            return detail::classificationHelper<ValueType>(CurveType::Loop, (d2 + f1) / f2, (d2 - f1) / f2); // 2.
        }
    }

    namespace detail
    {
        template<class T>
        inline void findOverlap(const BezierCubic<T> & _a, const BezierCubic<T> & _b,
                                typename BezierCubic<T>::ValueType _aParameter, bool _bFlip,
                                typename BezierCubic<T>::IntersectionResult & _outResult)
        {
            using ValueType = typename BezierCubic<T>::ValueType;
            using VectorType = typename BezierCubic<T>::VectorType;

            ValueType t0 = _aParameter;
            ValueType t1 = _a.parameterOf(_aParameter ? _b.positionTwo() : _b.positionOne());

            // if the point is on the curve
            if (t1 != -1)
            {
                VectorType pair = _bFlip ? VectorType(t0, t1) : VectorType(t1, t0);
                if (!_outResult.count || (abs(pair[0] - _outResult.values[0].parameterOne) > BezierCubic<T>::curveTimeEpsilon &&
                                          abs(pair[1] - _outResult.values[0].parameterTwo) > BezierCubic<T>::curveTimeEpsilon))
                {
                    _outResult.append(pair.x, pair.y, _aParameter ? _b.positionTwo() : _b.positionOne());
                }
            }
        }
    }

    template<class T>
    typename BezierCubic<T>::IntersectionResult BezierCubic<T>::overlaps(const BezierCubic & _other) const
    {
        // Linear curves can only overlap if they are collinear. Instead of
        // using the #isCollinear() check, we pick the longer of the two curves
        // treated as lines, and see how far the starting and end points of the
        // other line are from this line (assumed as an infinite line). But even
        // if the curves are not straight, they might just have tiny handles
        // within geometric epsilon distance, so we have to check for that too.

        bool bStraight1 = isStraight();
        bool bStraight2 = _other.isStraight();
        bool bStraightBoth = bStraight1 && bStraight2;
        bool bFlip = lengthSquared(m_pointTwo - m_pointOne) < lengthSquared(_other.m_pointTwo - _other.m_pointOne);

        const BezierCubic & l1 =  bFlip ? _other : *this;
        const BezierCubic & l2 =  bFlip ? *this : _other;

        // Get l1 start and end point values for faster referencing.
        ValueType px = l1.m_pointOne.x;
        ValueType py = l1.m_pointOne.y;
        ValueType vx = l1.m_pointTwo.x - px;
        ValueType vy = l1.m_pointTwo.y - py;
        Line<VectorType> line(VectorType(px, py), VectorType(vx, vy));

        // See if the starting and end point of curve two are very close to the
        // picked line. Note that the curve for the picked line might not
        // actually be a line, so we have to perform more checks after.
        if (line.distance(l2.m_pointOne) < geometricEpsilon &&
                line.distance(l2.m_pointTwo) < geometricEpsilon)
        {
            // If not both curves are straight, check against both of their
            // handles, and treat them as straight if they are very close.
            if (!bStraightBoth &&
                    line.distance(l1.m_handleOne) < geometricEpsilon &&
                    line.distance(l1.m_handleTwo) < geometricEpsilon &&
                    line.distance(l2.m_handleOne) < geometricEpsilon &&
                    line.distance(l2.m_handleTwo) < geometricEpsilon)
            {
                bStraight1 = bStraight2 = bStraightBoth = true;
            }
        }
        else if (bStraightBoth)
        {
            // If both curves are straight and not very close to each other,
            // there can't be a solution.
            return IntersectionResult();
        }

        if (bStraight1 ^ bStraight2)
        {
            // If one curve is straight, the other curve must be straight too,
            // otherwise they cannot overlap.
            return IntersectionResult();
        }

        IntersectionResult ret;
        detail::findOverlap(*this, _other, 0, false, ret);
        detail::findOverlap(_other, *this, 0, true, ret);
        if (ret.count < 2)
        {
            detail::findOverlap(*this, _other, 1, false, ret);
            //if we are still missing one
            if (ret.count == 1)
                detail::findOverlap(_other, *this, 1, true, ret);
        }

        if (ret.count != 2)
        {
            return IntersectionResult();
        }
        else if (bStraightBoth)
        {
            // Straight pairs don't need further checks. If we found 2 pairs,
            // the end points on v1 & v2 should be the same.
            BezierCubic o1 = slice(ret.values[0].parameterOne, ret.values[1].parameterOne);
            BezierCubic o2 = _other.slice(ret.values[0].parameterTwo, ret.values[1].parameterTwo);
            // Check if handles of the overlapping curves are the same too.
            if (abs(o2.m_handleOne.x - o1.m_handleOne.x) > geometricEpsilon ||
                    abs(o2.m_handleOne.y - o1.m_handleOne.y) > geometricEpsilon ||
                    abs(o2.m_handleTwo.x - o1.m_handleTwo.x) > geometricEpsilon ||
                    abs(o2.m_handleTwo.y - o1.m_handleTwo.y) > geometricEpsilon)
                return IntersectionResult();
        }

        return ret;
    }

    namespace detail
    {
        /**
        * Calculate the convex hull for the non-parametric bezier curve D(ti, di(t))
        * The ti is equally spaced across [0..1] — [0, 1/3, 2/3, 1] for
        * di(t), [dq0, dq1, dq2, dq3] respectively. In other words our CVs for the
        * curve are already sorted in the X axis in the increasing order.
        * Calculating convex-hull is much easier than a set of arbitrary points.
        *
        * The convex-hull is returned as two parts [TOP, BOTTOM]:
        * (both are in a coordinate space where y increases upwards with origin at
        * bottom-left)
        * TOP: The part that lies above the 'median' (line connecting end points of
        * the curve)
        * BOTTOM: The part that lies below the median.
        */

        template<class T>
        struct ConvexHull
        {
            struct HullPart
            {
                HullPart() :
                    count(0)
                {
                }

                HullPart(std::initializer_list<Vector2<T>> _list) :
                    count(0)
                {
                    for (const auto & vec : _list)
                    {
                        append(vec);
                    }
                }

                void append(const Vector2<T> & _val)
                {
                    STICK_ASSERT(count < 4);
                    values[count++] = _val;
                }

                Vector2<T> values[4];
                stick::Int32 count;
            };

            HullPart top;
            HullPart bottom;
        };

        template<class T>
        inline ConvexHull<T> convexHull(T _dq0, T _dq1, T _dq2, T _dq3)
        {
            ConvexHull<T> ret;

            Vector2<T> p0(0, _dq0);
            Vector2<T> p1(1.0 / 3.0, _dq1);
            Vector2<T> p2(2.0 / 3.0, _dq2);
            Vector2<T> p3(1, _dq3);

            // Find vertical signed distance of p1 and p2 from line [p0, p3]
            T dist1 = _dq1 - (2 * _dq0 + _dq3) / 3.0;
            T dist2 = _dq2 - (_dq0 + 2 * _dq3) / 3.0;

            // Check if p1 and p2 are on the opposite side of the line [p0, p3]
            if (dist1 * dist2 < 0)
            {
                // p1 and p2 lie on different sides of [p0, p3]. The hull is a
                // quadrilateral and line [p0, p3] is NOT part of the hull so we are
                // pretty much done here. The top part includes p1, we will reverse
                // it later if that is not the case.
                ret = {{p0, p1, p3}, {p0, p2, p3}};
            }
            else
            {
                // p1 and p2 lie on the same sides of [p0, p3]. The hull can be a
                // triangle or a quadrilateral and line [p0, p3] is part of the
                // hull. Check if the hull is a triangle or a quadrilateral. We have
                // a triangle if the vertical distance of one of the middle points
                // (p1, p2) is equal or less than half the vertical distance of the
                // other middle point.
                T distRatio = dist1 / dist2;

                typename ConvexHull<T>::HullPart top;
                if (distRatio >= 2)
                {
                    // p2 is inside, the hull is a triangle.
                    top = {p0, p1, p3};
                }
                else if (distRatio <= 0.5)
                {
                    // p1 is inside, the hull is a triangle.
                    top = {p0, p2, p3};
                }
                else
                {
                    // Hull is a quadrilateral, we need all lines in correct order.
                    top = {p0, p1, p2, p3};
                }

                ret =
                {
                    top,
                    // Line [p0, p3] is part of the hull.
                    {p0, p3}
                };
            }

            // Flip hull if dist1 is negative or if it is zero and dist2 is negative
            if (dist1 < 0 || (dist1 == 0 && dist2 < 0))
            {
                std::swap(ret.top, ret.bottom);
            }

            return ret;
        }

        template<class T>
        inline stick::Maybe<T> clipConvexHullPart(const typename ConvexHull<T>::HullPart & _part, bool _bTop, T _threshold)
        {
            T px = _part.values[0].x;
            T py = _part.values[0].y;

            for (stick::Int32 i = 1; i < _part.count; ++i)
            {
                T qx = _part.values[i].x;
                T qy = _part.values[i].y;

                if ((_bTop && qy >= _threshold) || (!_bTop && qy <= _threshold))
                {
                    return qy == _threshold ? qx : px + (_threshold - py) * (qx - px) / (qy - py);
                }

                px = qx;
                py = qy;
            }

            return stick::Maybe<T>();
        }

        /**
         * Clips the convex-hull and returns [tMin, tMax] for the curve contained.
         */

        template<class T>
        inline stick::Maybe<T> clipConvexHull(const ConvexHull<T> & _hull, T _dMin, T _dMax)
        {
            if (_hull.top.values[0].y < _dMin)
            {
                // Left of hull is below dMin, walk through the hull until it
                // enters the region between dMin and dMax
                return clipConvexHullPart(_hull.top, true, _dMin);
            }
            else if (_hull.bottom.values[0].y > _dMax)
            {
                // Left of hull is above dMax, walk through the hull until it
                // enters the region between dMin and dMax
                return clipConvexHullPart(_hull.bottom, false, _dMax);
            }
            else
            {
                // Left of hull is between dMin and dMax, no clipping possible
                return _hull.top.values[0].x;
            }
        }

        // fat line clipping implementation
        template<class T>
        inline stick::Int32 curveIntersections(const BezierCubic<T> & _a, const BezierCubic<T> & _b,
                                               typename BezierCubic<T>::IntersectionResult & _outResult, bool _bFlip,
                                               stick::Int32 _calls, stick::Int32 _recursion,
                                               typename BezierCubic<T>::ValueType _tMin, typename BezierCubic<T>::ValueType _tMax,
                                               typename BezierCubic<T>::ValueType _uMin, typename BezierCubic<T>::ValueType _uMax)
        {
            using BezierType = BezierCubic<T>;
            using ValueType = typename BezierType::ValueType;
            using VectorType = typename BezierType::VectorType;

            // Avoid deeper recursion, by counting the total amount of recursions,
            // as well as the total amount of calls, to avoid massive call-trees as
            if (++_calls >= 4096 || ++_recursion >= 40)
                return _calls;

            // printf("START CUVE INTRE\n");

            static ValueType fatLineEpsilon = BezierType::fatLineEpsilon;

            Line<VectorType> line = Line<VectorType>::fromPoints(_b.positionOne(), _b.positionTwo());
            ValueType d1 = line.signedDistance(_b.handleOne());
            ValueType d2 = line.signedDistance(_b.handleTwo());
            ValueType factor = d1 * d2 > 0 ? 3.0 / 4.0 : 4.0 / 9.0;
            ValueType dMin = factor * min((ValueType)0.0, min(d1, d2));
            ValueType dMax = factor * max((ValueType)0.0, max(d1, d2));

            // Calculate non-parametric bezier curve D(ti, di(t)):
            // - di(t) is the distance of P from baseline l of the fat-line
            // - ti is equally spaced in [0, 1]
            ValueType dp0 = line.signedDistance(_a.positionOne());
            ValueType dp1 = line.signedDistance(_a.handleOne());
            ValueType dp2 = line.signedDistance(_a.handleTwo());
            ValueType dp3 = line.signedDistance(_a.positionTwo());

            auto hull = convexHull(dp0, dp1, dp2, dp3);
            auto reverseHull = hull;
            std::reverse(&reverseHull.top.values[0], &reverseHull.top.values[0] + reverseHull.top.count);
            std::reverse(&reverseHull.bottom.values[0], &reverseHull.bottom.values[0] + reverseHull.bottom.count);
            stick::Maybe<ValueType> tMinClip, tMaxClip;
            // printf("%f %f %f %f\n", dp0, dp1, dp2, dp3);
            // printf("DMIN %f DMAX %f\n", dMin, dMax);

            // Stop iteration if all points and control points are collinear.
            if ((d1 == 0 && d2 == 0
                    && dp0 == 0 && dp1 == 0 && dp2 == 0 && dp3 == 0)
                    // Clip convex-hull with dMin and dMax, taking into account that
                    // there will be no intersections if one of the results is null.
                    || !(tMinClip = clipConvexHull(hull, dMin, dMax))
                    || !(tMaxClip = clipConvexHull(reverseHull, dMin, dMax)))
            {
                return _calls;
            }

            // just a sanity check...this should never be reached but the above if clause
            // is somewhat messy oO
            STICK_ASSERT(tMinClip && tMaxClip);

            // tMin and tMax are within the range (0, 1). Project it back to the
            // original parameter range for v2.
            ValueType tMinNew = _tMin + (_tMax - _tMin) * *tMinClip;
            ValueType tMaxNew = _tMin + (_tMax - _tMin) * *tMaxClip;

            if (max(_uMax - _uMin, tMaxNew - tMinNew) < fatLineEpsilon)
            {
                // We have isolated the intersection with sufficient precision
                ValueType t = (tMinNew + tMaxNew) / 2.0;
                ValueType u = (_uMin + _uMax) / 2.0;
                //_outResult.values[_outResult.count++] = _bFlip ? VectorType(u, t) : VectorType(t, u);
                if (_bFlip)
                    _outResult.append(u, t, _b.positionAt(u));
                else
                    _outResult.append(t, u, _a.positionAt(t));
            }
            else
            {
                // printf("TRYING\n");
                // Apply the result of the clipping to curve 1:
                auto sliced = _a.slice(*tMinClip, *tMaxClip);
                if (*tMaxClip - *tMinClip > 0.8)
                {
                    // Subdivide the curve which has converged the least.
                    if (tMaxNew - tMinNew > _uMax - _uMin)
                    {
                        // printf("A\n");
                        auto pair = sliced.subdivide(0.5);
                        auto t = (tMinNew + tMaxNew) / 2.0;
                        _calls = curveIntersections(
                                     _b, pair.first, _outResult, !_bFlip,
                                     _calls, _recursion, _uMin, _uMax, tMinNew, t);
                        _calls = curveIntersections(
                                     _b, pair.second, _outResult, !_bFlip,
                                     _calls, _recursion, _uMin, _uMax, t, tMaxNew);
                    }
                    else
                    {
                        // printf("B\n");
                        auto pair = _b.subdivide(0.5);
                        auto u = (_uMin + _uMax) / 2.0;
                        _calls = curveIntersections(
                                     pair.first, sliced, _outResult, !_bFlip,
                                     _calls, _recursion, _uMin, u, tMinNew, tMaxNew);
                        _calls = curveIntersections(
                                     pair.second, sliced, _outResult, !_bFlip,
                                     _calls, _recursion, u, _uMax, tMinNew, tMaxNew);
                    }
                }
                else
                {
                    // Iterate
                    if (_uMax - _uMin >= fatLineEpsilon)
                    {
                        // printf("ITER A\n");
                        _calls = curveIntersections(_b, sliced, _outResult, !_bFlip,
                                                    _recursion, _calls, _uMin, _uMax, tMinNew, tMaxNew);
                    }
                    else
                    {
                        // printf("ITER B\n");
                        // The interval on the other curve is already tight enough,
                        // therefore we keep iterating on the same curve.
                        _calls = curveIntersections(sliced, _b, _outResult, _bFlip,
                                                    _recursion, _calls, tMinNew, tMaxNew, _uMin, _uMax);
                    }
                }
            }

            return _calls;
        }

        template<class T>
        inline Vector2<T> alignWithLineHelper(const Vector2<T> & _point, const Vector2<T> & _lineStart, T _sinVal, T _cosVal)
        {
            T x = _point.x - _lineStart.x;
            T y = _point.y - _lineStart.y;
            return {x * _cosVal - y * _sinVal, x * _sinVal + y * _cosVal};
        }
    }

    template<class T>
    typename BezierCubic<T>::IntersectionResult BezierCubic<T>::intersections(const BezierCubic & _other) const
    {
        IntersectionResult ret;

        // Avoid checking curves if completely out of control bounds.
        RectangleType myHandleBounds = handleBounds();
        RectangleType otherHandleBounds = _other.handleBounds();
        // printf("HANDE BOUNDS %s %s\n", toString(myHandleBounds.min()).cString(), toString(myHandleBounds.max()).cString());
        // printf("OTHER HANDE BOUNDS %s %s\n", toString(otherHandleBounds.min()).cString(), toString(otherHandleBounds.max()).cString());
        if (myHandleBounds.overlaps(otherHandleBounds))
        {
            // if we overlap, we are done.
            // @TODO: Technically there can be other intersections than the two overlap start and
            // endpoints, so we should most likely do that eventually!
            auto ol = overlaps(_other);
            if (ol.count)
            {
                for (stick::Int32 i = 0; i < 2; ++i)
                {
                    ret.append(ol.values[i].parameterOne, ol.values[i].parameterTwo,
                               ol.values[i].position);
                }
            }
            else
            {
                //otherwise we find the intersections
                bool bStraight1 = isStraight();
                bool bStraight2 = _other.isStraight();
                bool bStraightBoth = bStraight1 && bStraight2;
                bool bFlip = bStraight1 && !bStraight2;

                if (bStraightBoth)
                {
                    // printf("BOTH STRAIGHT\n");
                    //find the intersection between the two line segments
                    LineSegment<VectorType> lineA(positionOne(), positionTwo());
                    LineSegment<VectorType> lineB(_other.positionOne(), _other.positionTwo());
                    if (auto result = intersect(lineA, lineB))
                    {
                        ret.append(parameterOf(*result), _other.parameterOf(*result), *result);
                    }
                }
                else if (bStraight1 || bStraight2)
                {
                    /**
                     * Intersections between curve and line becomes rather simple here.
                     * We can rotate the curve and line so that the
                     * line is on the X axis, and solve the implicit equations for the X axis
                     * and the curve.
                     */

                    // printf("ONE STRAIGHT\n");
                    //make sure a is always the curven and b the straight one
                    const BezierCubic * a = this;
                    const BezierCubic * b = &_other;
                    if (bFlip) std::swap(a, b);

                    LineSegment<VectorType> line(b->m_pointOne, b->m_pointTwo);
                    if (isClose(line.direction(), VectorType(0), epsilon))
                    {
                        // printf("POINT CHECK\n");
                        // Handle special case of a line with no direction as a point,
                        // and check if it is on the curve.
                        auto t = a->parameterOf(b->m_pointOne);
                        if (t != -1)
                        {
                            // printf("GOT DA POINT!!!!!\n");
                            if (bFlip)
                                ret.append(0, t, b->m_pointOne);
                            else
                                ret.append(t, 0, b->m_pointOne);
                        }
                    }
                    else
                    {
                        // printf("ALIGN WITH LINE CHECK\n");
                        // Calculate angle to the x-axis (1, 0).
                        auto dir = line.direction();
                        ValueType angle = std::atan2(-dir.y, dir.x);
                        ValueType s = std::sin(angle);
                        ValueType c = std::cos(angle);

                        // printf("LINE ANGLE %f %f %f\n", toDegrees(angle), s, c);

                        VectorType rotatedP1 = detail::alignWithLineHelper(a->m_pointOne, line.positionOne(), s, c);
                        VectorType rotatedH1 = detail::alignWithLineHelper(a->m_handleOne, line.positionOne(), s, c);
                        VectorType rotatedH2 = detail::alignWithLineHelper(a->m_handleTwo, line.positionOne(), s, c);
                        VectorType rotatedP2 = detail::alignWithLineHelper(a->m_pointTwo, line.positionOne(), s, c);
                        BezierCubic bez(rotatedP1, rotatedH1, rotatedH2, rotatedP2);

                        // printf("%s %s %s %s\n", toString(rotatedP1).cString(), toString(rotatedH1).cString(), toString(rotatedH2).cString(), toString(rotatedP2).cString());
                        auto roots = bez.solveCubic(0, false, 0, 1);

                        for (stick::Int32 i = 0; i < roots.count; ++i)
                        {
                            auto pos = a->positionAt(roots.values[i]);
                            auto t2 = b->parameterOf(pos);
                            // printf("ROOT %f %f\n", roots.values[i], t2);
                            if (t2 != -1)
                            {
                                if (bFlip)
                                    ret.append(t2, roots.values[i], pos);
                                else
                                    ret.append(roots.values[i], t2, pos);
                            }
                        }
                    }
                }
                else
                {
                    // printf("BOTH CURVES BRAAA\n");
                    // fat line clipping for curve curve intersecting
                    if (bFlip)
                        detail::curveIntersections(_other, *this, ret, bFlip, 0, 0, 0, 1, 0, 1);
                    else
                        detail::curveIntersections(*this, _other, ret, bFlip, 0, 0, 0, 1, 0, 1);
                }

                //@TODO: Add code to handle special case (see paper.js src)
            }
        }
        // else
        // {
        //     printf("HANDLE BOUNDS DONT OVERELAP\n");
        // }

        // sort the intersections
        std::sort(&ret.values[0], &ret.values[0] + ret.count, [](const typename IntersectionResult::Intersection & _a,
                  const typename IntersectionResult::Intersection & _b)
        {
            return _a.parameterOne < _b.parameterOne;
        });

        return ret;
    }

    namespace detail
    {
        template<class T>
        inline void biarcsImpl(const BezierCubic<T> & _bezier,
                               typename BezierCubic<T>::BiarcResultArray & _outArcs,
                               typename BezierCubic<T>::ValueType _tolerance)
        {
            using ValueType = typename BezierCubic<T>::ValueType;
            using VectorType = typename BezierCubic<T>::VectorType;
            using ArcType = typename BezierCubic<T>::Arc;
            using BiarcType = typename BezierCubic<T>::Biarc;
            using LineType = Line<VectorType>;

            // printf("BIARCS IMPL %f\n", _bezier.length());

            VectorType aNorm = _bezier.normalAt(0);
            VectorType bNorm = _bezier.normalAt(1.0);
            VectorType mid = _bezier.positionAt(0.5);
            // VectorType midNorm = _bezier.normalAt(0.5);

            LineType aLine(_bezier.positionOne(), aNorm);
            LineType bLine(_bezier.positionTwo(), bNorm);

            VectorType ah = mid - _bezier.positionOne();
            VectorType amidStart = _bezier.positionOne() + ah * 0.5;
            VectorType amidDir(-ah.y, ah.x);
            LineType aMidLine(amidStart, amidDir);

            // printf("AMID START %s\n", toString(amidStart).cString());

            VectorType bh = mid - _bezier.positionTwo();
            VectorType bmidStart = _bezier.positionTwo() + bh * 0.5;
            VectorType bmidDir(bh.y, -bh.x);
            LineType bMidLine(bmidStart, bmidDir);

            // printf("BMID START %s\n", toString(bmidStart).cString());

            auto ira = intersect(aLine, aMidLine);
            auto irb = intersect(bLine, bMidLine);

            STICK_ASSERT(ira && irb);
            if (ira && irb)
            {
                ValueType radA = distance(*ira, _bezier.positionOne());
                ValueType radB = distance(*irb, _bezier.positionTwo());

                // printf("RADII %f %f\n", radA, radB);

                /*VectorType ta = ira.intersections()[0] - normalize(amidDir) * radA;
                VectorType tb = irb.intersections()[0] - normalize(bmidDir) * radB;

                printf("ta %s\n", toString(ta).cString());
                printf("tb %s\n", toString(tb).cString());

                ValueType distA = 0;
                auto para = _bezier.closestParameter(ta, distA, 0.0, 1.0, 0.0);
                ValueType distB = 0;
                auto parb = _bezier.closestParameter(tb, distB, 0.0, 1.0, 0.0);
                printf("pars %f %f\n", para, parb);
                //ValueType distB = abs(radB - distance(tb, irb.intersections()[0]));

                ValueType divergence = (distA + distB) * 0.5;

                printf("TOLERANCE %f\n", _tolerance);
                printf("GOT INTERSECTIONS %f %f %f\n", distA, distB, divergence);*/

                float divergence = 0.0f;
                for (int i = 0; i < 10; i++)
                {
                    ValueType t = i * 0.1;
                    auto p = _bezier.positionAt(t);
                    if (t < 0.5)
                    {
                        auto d = distance(p, *ira);
                        divergence += abs(d - radA);
                    }
                    else
                    {
                        auto d = distance(p, *irb);
                        divergence += abs(d - radB);
                    }
                }

                divergence *= 0.1;

                if (divergence <= _tolerance)
                {
                    // printf("GOT IIIIIIT\n");

                    bool cw = _bezier.area() >= 0;
                    auto va = _bezier.positionOne() - *ira;
                    auto va2 = mid - *ira;

                    auto astart = std::atan2(va.y, va.x);
                    auto asweep = std::atan2(va2.y, va2.x) - astart;

                    auto vb = mid - *irb;
                    auto vb2 = _bezier.positionTwo() - *irb;
                    auto bstart = std::atan2(vb.y, vb.x);
                    auto bsweep = std::atan2(vb2.y, vb2.x) - astart;

                    // Adjust angles according to the orientation of the curve
                    if (cw && asweep < 0) asweep = Constants<ValueType>::twoPi() + asweep;
                    if (!cw && asweep > 0) asweep = asweep - Constants<ValueType>::twoPi();
                    if (cw && bsweep < 0) bsweep = Constants<ValueType>::twoPi() + bsweep;
                    if (!cw && bsweep > 0) bsweep = bsweep - Constants<ValueType>::twoPi();

                    // printf("CW: %d\n", cw);
                    // printf("START ANGLE %f SWEEP %f\n", toDegrees(astart), toDegrees(asweep));
                    // printf("START ANGLE2 %f SWEEP2 %f\n", toDegrees(bstart), toDegrees(bsweep));

                    ArcType a = {*ira, _bezier.positionOne(), mid, radA, astart, asweep};
                    ArcType b = {*irb, mid, _bezier.positionTwo(), radB, bstart, bsweep};

                    _outArcs.append((BiarcType) {a, b});
                }
                else
                {
                    // printf("SUBDIVIDEIT BRAA\n");
                    auto pair = _bezier.subdivide(0.5);
                    // printf("START %s END %s\n", toString(pair.first.positionTwo()).cString(), toString(pair.second.positionOne()).cString());

                    biarcsImpl(pair.first, _outArcs, _tolerance);
                    biarcsImpl(pair.second, _outArcs, _tolerance);
                }
            }
        }
    }

    template<class T>
    SolveResult<typename BezierCubic<T>::ValueType> BezierCubic<T>::inflections(ValueType _minParameter, ValueType _maxParameter) const
    {
        // http://www.caffeineowl.com/graphics/2d/vectorial/cubic-inflexion.html
        VectorType av = m_handleOne - m_pointOne;
        VectorType bv = m_handleTwo - m_handleOne - av;
        VectorType cv = m_pointTwo - m_handleTwo - av - bv * 2;

        ValueType a = av.x * bv.y - av.y * bv.x;
        ValueType b = av.x * cv.y - av.y * cv.x;
        ValueType c = bv.x * cv.y - bv.y * cv.x;
        return solveQuadratic(c, b, a, _minParameter, _maxParameter);
    }

    template<class T>
    void BezierCubic<T>::biarcs(BiarcResultArray & _outArcs,
                                ValueType _tolerance) const
    {
        //for straight beziers, we simply return the two endpoints
        if (isStraight())
        {
            _outArcs.append((PointPair) {m_pointOne, m_pointTwo});
            return;
        }

        auto res = inflections();

        // printf("INFLECTIONS: %i\n", res.count);

        if (res.count)
        {
            if (res.count == 1)
            {
                auto pair = subdivide(res.values[0]);
                // printf("FIRST\n");
                detail::biarcsImpl(pair.first, _outArcs, _tolerance);
                // printf("SECOND\n");
                detail::biarcsImpl(pair.second, _outArcs, _tolerance);
            }
            else
            {
                detail::biarcsImpl(slice(0, res.values[0]), _outArcs, _tolerance);
                detail::biarcsImpl(slice(res.values[0], res.values[1]), _outArcs, _tolerance);
                detail::biarcsImpl(slice(res.values[1], 1), _outArcs, _tolerance);
            }
        }
        else
        {
            // printf("NO INFLECTIONS\n");
            detail::biarcsImpl(*this, _outArcs, _tolerance);
        }
    }

    typedef BezierCubic<Vector2<stick::Float32> > BezierCubic2f;
    typedef BezierCubic<Vector2<stick::Float64> > BezierCubic2d;
    typedef BezierCubic<Vector3<stick::Float32> > BezierCubic3f;
    typedef BezierCubic<Vector3<stick::Float64> > BezierCubic3d;
}

#endif //CRUNCH_BEZIER_HPP
