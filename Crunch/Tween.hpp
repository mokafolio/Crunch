#ifndef CRUNCH_TWEEN_HPP
#define CRUNCH_TWEEN_HPP

#include <Crunch/Constants.hpp>
#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>

namespace crunch
{
namespace detail
{
/* EASING EQUATIONS PORTED FROM PENNERS EASING EQUATIONS */
/*
 TERMS OF USE - EASING EQUATIONS

 Open source under the BSD License.

 Copyright © 2001 Robert Penner
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted
 provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this list of conditions and
 the following disclaimer. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation and/or other materials
 provided with the distribution. Neither the name of the author nor the names of contributors may be
 used to endorse or promote products derived from this software without specific prior written
 permission. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 DAMAGE.
 */

// TODO: implement a lot more of these

using namespace stick;

template <class T>
inline T linearEaseOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    return _delta * (_elapsed / _duration) + _origin;
}

template <class T>
inline T cubicEaseIn(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    Float64 t = _elapsed / _duration;
    return _delta * t * t * t + _origin;
}

template <class T>
inline T cubicEaseOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    Float64 t = _elapsed / _duration - 1;
    return _delta * (t * t * t + 1) + _origin;
}

template <class T>
inline T cubicEaseInOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    Float64 t = _elapsed / (_duration / 2);

    if (t < 1)
        return _delta / 2 * t * t * t + _origin;

    t -= 2;
    return _delta / 2 * (t * t * t + 2) + _origin;
}

template <class T>
inline T elasticEaseIn(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    if (_elapsed == 0)
        return _origin;
    if ((_elapsed /= _duration) == 1)
        return _origin + _delta;

    Float64 p = _duration * 0.3;
    Float64 s = p / 4.0;
    _elapsed -= 1;
    T postFix = _delta * std::pow(2, 10 * _elapsed);
    return -(postFix * std::sin((_elapsed * _duration - s) * Constants<Float64>::twoPi() / p)) +
           _origin;
}

template <class T>
inline T elasticEaseOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    if (_elapsed == 0)
        return _origin;

    Float64 t = _elapsed / _duration;
    if (t == 1)
        return _origin + _delta;

    Float64 p = _duration * 0.3;
    T a = _delta;
    Float64 s = p / 4.0;
    return (a * std::pow(2, -10 * t) *
                std::sin((t * _duration - s) * Constants<Float64>::twoPi() / p) +
            _delta + _origin);
}

template <class T>
inline T elasticEaseInOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    if (_elapsed == 0)
        return _origin;

    Float64 t = _elapsed / (_duration / 2);
    if (t == 2)
        return _origin + _delta;

    Float64 p = _duration * (0.3 * 1.5);
    // T a = _delta;
    Float64 s = p / 4.0;

    t -= 1;
    if (t < 1)
    {
        // auto postFix = a * std::pow(2, 10 * t); // postIncrement is evil
        return (_delta * std::pow(2, 10 * t) * -0.5 *
                std::sin((t * _duration - s) * Constants<Float64>::twoPi() / p)) +
               _origin;
    }
    // auto postFix = a * std::pow(2, -10 * t); // postIncrement is evil
    return _delta * std::pow(2, -10 * t) *
               std::sin((t * _duration - s) * Constants<Float64>::twoPi() / p) * 0.5 +
           _delta + _origin;
}

template <class T>
inline T backEaseIn(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    static const Float64 s = 1.70158;
    Float64 t = _elapsed / _duration;
    return _delta * t * t * ((s + 1) * t - s) + _origin;
}

template <class T>
inline T backEaseOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    static const Float64 s = 1.70158;
    Float64 t = _elapsed / _duration - 1;
    return _delta * (t * t * ((s + 1) * t + s) + 1) + _origin;
}

template <class T>
inline T backEaseInOut(const T & _origin, const T & _delta, Float64 _duration, Float64 _elapsed)
{
    static const Float64 s = 1.70158 * 1.525;
    Float64 t = _elapsed / (_duration / 2);
    if (t < 1)
        return _delta / 2 * (t * t * ((s + 1) * t - s)) + _origin;
    t -= 2;
    return _delta / 2 * (t * t * ((s + 1) * t + s) + 2) + _origin;
}
} // namespace detail

/**
 * @brief A tween class.
 * @arg ValueType The internal value type (i.e. Float32)
 * @arg Func The tweening function.
 */
template <class VT, VT (*Func)(const VT &, const VT &, stick::Float64, stick::Float64)>
class Tween
{
  public:
    using ValueType = VT;

    /**
     * @brief Default Constructor.
     */
    Tween() :
        m_start(0),
        m_end(0),
        m_current(0),
        m_duration(0.0),
        m_timeElapsed(0.0),
        m_bIsFinished(true)
    {
    }

    /**
     * @brief Constructs a tween that animates from a start to a target value
     * in the provided amount of time.
     * @param _origin The start value.
     * @param _destination The target value.
     * @param _duration The duration in seconds.
     */
    Tween(const ValueType & _origin, const ValueType & _destination, stick::Float64 _duration) :
        m_start(_origin),
        m_end(_destination),
        m_current(_origin),
        m_delta(m_end - m_start),
        m_duration(_duration),
        m_timeElapsed(0.0),
        m_bIsFinished(false)
    {
    }

    /**
     * @brief Updates the animation state of the tween.
     * @param _dt The time elapsed since the laste call to update in seconds.
     * @return The current value of the tween.
     */
    const ValueType & update(stick::Float64 _dt)
    {
        if (m_bIsFinished)
            return m_current;

        m_timeElapsed += _dt;
        m_current = Func(m_start, m_delta, m_duration, m_timeElapsed);

        if (m_timeElapsed >= m_duration)
            m_bIsFinished = true;

        return m_current;
    }

    /**
     * @brief Returns the starting value of the tween.
     */
    const ValueType & origin() const
    {
        return m_start;
    }

    /**
     * @brief Returns the target value of the tween.
     */
    const ValueType & destination() const
    {
        return m_end;
    }

    /**
     * @brief Returns the last computed value of the tween.
     */
    const ValueType & current() const
    {
        return m_current;
    }

    /**
     * @brief Returns the time elapsed in seconds since the start of the tween.
     */
    stick::Float64 timeElapsed() const
    {
        return m_timeElapsed;
    }

    /**
     * @brief Returns the duration of the tween in seconds.
     */
    stick::Float64 duration() const
    {
        return m_duration;
    }

    /**
     * @brief Returns true if the tween is finished.
     */
    bool isFinished() const
    {
        return m_bIsFinished;
    }

  private:
    ValueType m_start;
    ValueType m_end;
    ValueType m_current;
    ValueType m_delta;
    stick::Float64 m_duration;
    stick::Float64 m_timeElapsed;
    bool m_bIsFinished;
};

//@TODO properly order this
typedef Tween<stick::Float32, detail::linearEaseOut> TweenLinearEaseOutf;
typedef Tween<Vector2<stick::Float32>, detail::linearEaseOut> TweenLinearEaseOut2f;
typedef Tween<Vector3<stick::Float32>, detail::linearEaseOut> TweenLinearEaseOut3f;
typedef Tween<stick::Float32, detail::cubicEaseOut> TweenCubicEaseOutf;
typedef Tween<Vector2<stick::Float32>, detail::cubicEaseOut> TweenCubicEaseOut2f;
typedef Tween<Vector3<stick::Float32>, detail::cubicEaseOut> TweenCubicEaseOut3f;
typedef Tween<stick::Float32, detail::cubicEaseInOut> TweenCubicEaseInOutf;
typedef Tween<Vector2<stick::Float32>, detail::cubicEaseInOut> TweenCubicEaseInOut2f;
typedef Tween<Vector3<stick::Float32>, detail::cubicEaseInOut> TweenCubicEaseInOut3f;
typedef Tween<stick::Float32, detail::cubicEaseIn> TweenCubicEaseInf;
typedef Tween<Vector2<stick::Float32>, detail::cubicEaseIn> TweenCubicEaseIn2f;
typedef Tween<Vector3<stick::Float32>, detail::cubicEaseIn> TweenCubicEaseIn3f;

// typedef Tween<stick::Float32, detail::elasticEaseOut> TweenElasticEaseOutf;
// typedef Tween<Vector2<stick::Float32>, detail::elasticEaseOut> TweenElasticEaseOut2f;
// typedef Tween<stick::Float32, detail::elasticEaseIn> TweenElasticEaseInf;
// typedef Tween<Vector2<stick::Float32>, detail::elasticEaseIn> TweenElasticEaseIn2f;

typedef Tween<stick::Float64, detail::linearEaseOut> TweenLinearEaseOutd;
typedef Tween<Vector2<stick::Float64>, detail::linearEaseOut> TweenLinearEaseOut2d;
typedef Tween<Vector3<stick::Float64>, detail::linearEaseOut> TweenLinearEaseOut3d;
typedef Tween<stick::Float64, detail::cubicEaseOut> TweenCubicEaseOutd;
typedef Tween<Vector2<stick::Float64>, detail::cubicEaseOut> TweenCubicEaseOut2d;
typedef Tween<Vector3<stick::Float64>, detail::cubicEaseOut> TweenCubicEaseOut3d;

typedef Tween<stick::Float32, detail::backEaseIn> TweenBackEaseInf;
typedef Tween<stick::Float32, detail::backEaseOut> TweenBackEaseOutf;
typedef Tween<stick::Float32, detail::backEaseInOut> TweenBackEaseInOutf;
typedef Tween<stick::Float64, detail::backEaseIn> TweenBackEaseInd;
typedef Tween<stick::Float64, detail::backEaseOut> TweenBackEaseOutd;
typedef Tween<stick::Float64, detail::backEaseInOut> TweenBackEaseInOutd;
typedef Tween<Vector2<stick::Float32>, detail::backEaseIn> TweenBackEaseIn2f;
typedef Tween<Vector2<stick::Float32>, detail::backEaseOut> TweenBackEaseOut2f;
typedef Tween<Vector2<stick::Float32>, detail::backEaseInOut> TweenBackEaseInOut2f;

typedef Tween<stick::Float32, detail::elasticEaseIn> TweenElasticEaseInf;
typedef Tween<stick::Float32, detail::elasticEaseOut> TweenElasticEaseOutf;
typedef Tween<stick::Float32, detail::elasticEaseInOut> TweenElasticEaseInOutf;
typedef Tween<stick::Float64, detail::elasticEaseIn> TweenElasticEaseInd;
typedef Tween<stick::Float64, detail::elasticEaseOut> TweenElasticEaseOutd;
typedef Tween<stick::Float64, detail::elasticEaseInOut> TweenElasticEaseInOutd;
typedef Tween<Vector2<stick::Float32>, detail::elasticEaseIn> TweenElasticEaseIn2f;
typedef Tween<Vector2<stick::Float32>, detail::elasticEaseOut> TweenElasticEaseOut2f;
typedef Tween<Vector2<stick::Float32>, detail::elasticEaseInOut> TweenElasticEaseInOut2f;

} // namespace crunch

#endif // CRUNCH_TWEEN_HPP
