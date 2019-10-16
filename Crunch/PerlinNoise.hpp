#ifndef CRUNCH_PERLINNOISE_HPP
#define CRUNCH_PERLINNOISE_HPP

#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>
#include <Crunch/Randomizer.hpp>
#include <Crunch/CommonFunc.hpp>

namespace crunch
{
    namespace detail
    {
        struct RandomValueArray
        {
            Randomizer m_generator;
            stick::UInt8 m_rValues[512];

            RandomValueArray()
            {
                randomize();
            }

            void randomize()
            {
                m_generator.randomizeSeed();

                for (stick::Int32 i = 0; i < 255; ++i)
                {
                    m_rValues[i] = (stick::UInt8)m_generator.randomui(0, 255);
                }

                for (stick::Int32 i = 256; i < 512; ++i)
                {
                    m_rValues[i] = m_rValues[i - 256];
                }
            }

            void setSeed(stick::Int32 _seed)
            {
                m_generator.setSeed(_seed);

                for (stick::Int32 i = 0; i < 255; ++i)
                {
                    m_rValues[i] = (stick::UInt8)m_generator.randomui(0, 255);
                }

                for (stick::Int32 i = 256; i < 512; ++i)
                {
                    m_rValues[i] = m_rValues[i - 256];
                }
            }

            inline stick::UInt8 operator[](stick::Int32 _i) const
            {
                return m_rValues[_i];
            }
        };

        /*
         * Helper functions to compute gradients-dot-residualvectors (1D to 4D)
         * Note that these generate gradients of more than unit length. To make
         * a close match with the value range of classic PerlinNoise noise, the final
         * noise values need to be rescaled. To match the RenderMan noise in a
         * statistical sense, the approximate scaling values (empirically
         * determined from test renderings) are:
         * 1D noise needs rescaling with 0.188
         * 2D noise needs rescaling with 0.507
         * 3D noise needs rescaling with 0.936
         * 4D noise needs rescaling with 0.87

         * thes grad function implementation are a port of Noise1234
         * class by Stefan Gustavson ( stegu@itn.liu.se )
         * http://staffwww.itn.liu.se/~stegu/aqsis/aqsis-newnoise/noise1234.cpp
         */

        inline stick::Float32 grad(stick::Int32 _hash, stick::Float32 _x)
        {
            stick::Int32 h = _hash & 15;
            stick::Float32 grad = (stick::Float32)1.0 + (h & 7);  // Gradient value 1.0, 2.0, ..., 8.0
            if (h & 8) grad = -grad;      // and a random sign for the gradient
            return ( grad * _x );       // Multiply the gradient with the distance
        }

        inline stick::Float32 grad(stick::Int32 _hash, stick::Float32 _x, stick::Float32 _y)
        {
            stick::Int32 h = _hash & 7;    // Convert low 3 bits of hash code
            stick::Float32 u = h < 4 ? _x : _y;  // into 8 simple gradient directions,
            stick::Float32 v = h < 4 ? _y : _x;  // and compute the dot product with (x,y).
            return ((h & 1) ? -u : u) + ((h & 2) ? -(stick::Float32)2.0 * v : (stick::Float32)2.0 * v);
        }

        inline stick::Float32 grad(stick::Int32 _hash, stick::Float32 _x, stick::Float32 _y, stick::Float32 _z)
        {
            stick::Int32 h = _hash & 15;                             // Convert low 4 bits of hash code into 12 simple
            stick::Float32 u = h < 8 ? _x : _y;                            // gradient directions, and compute dot product.
            stick::Float32 v = h < 4 ? _y : h == 12 || h == 14 ? _x : _z;  // Fix repeats at h = 12 to 15
            return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
        }

        inline stick::Float32 grad(stick::Int32 _hash, stick::Float32 _x, stick::Float32 _y, stick::Float32 _z, stick::Float32 _t)
        {
            stick::Int32 h = _hash & 31;      // Convert low 5 bits of hash code into 32 simple
            stick::Float32 u = h < 24 ? _x : _y;    // gradient directions, and compute dot product.
            stick::Float32 v = h < 16 ? _y : _z;
            stick::Float32 w = h < 8  ? _z : _t;
            return ((h & 1) ? -u : u) + ((h & 2) ? -v : v) + ((h & 4) ? -w : w);
        }

        inline stick::Float32 fade(stick::Float32 _val)
        {
            return ( _val * _val * _val * ( _val * ( _val * (stick::Float32)6.0 - (stick::Float32)15.0 ) + (stick::Float32 )10.0 ) );
        }
    }

    /**
     * @brief A perlin noise implementation.
     *
     * (improved PerlinNoise noise, Ken PerlinNoise 2002)
     * http://en.wikipedia.org/wiki/Perlin_noise
     */
    class PerlinNoise
    {
    public:

        /**
         * @brief Default Constructor. Picks a random seed.
         */
        PerlinNoise()
        {
            randomize();
        }

        /**
         * @brief Constructs PerlinNoise with the provided seed.
         */
        PerlinNoise(stick::Int32 _seed)
        {
            setSeed(_seed);
        }

        /**
         * @brief Randomizes the seed.
         */
        void randomize()
        {
            m_rand.randomize();
        }

        /**
         * @brief Sets the seed.
         */
        void setSeed(stick::Int32 _seed)
        {
            m_rand.setSeed(_seed);
        }

        /**
         * @brief Computes the 1D perlin noise value at the specified coordinate in noise space.
         * @param _x The x coordinate in noise space.
         */
        stick::Float32 noise(stick::Float32 _x)
        {
            stick::Int32 intPart = (stick::Int32)crunch::floor( _x );
            stick::Float32 floatPart = _x - intPart;

            stick::Float32 faded = detail::fade(floatPart);

            stick::UInt32 index0 = intPart & 255;
            stick::UInt32 index1 = index0 + 1;

            stick::Float32 grad0 = detail::grad(m_rand[index0], floatPart);
            stick::Float32 grad1 = detail::grad(m_rand[index1], floatPart - 1.0f);

            return (stick::Float32)0.188 * ( crunch::mix(grad0, grad1, faded) );
        }

        /**
         * @brief Computes the 2D perlin noise value at the specified coordinate in noise space.
         * @param _x The x coordinate in noise space.
         * @param _y The y coordinate in noise space.
         */
        stick::Float32 noise(stick::Float32 _x, stick::Float32 _y)
        {
            stick::Int32 intPartX = (stick::Int32)crunch::floor( _x );
            stick::Int32 intPartY = (stick::Int32)crunch::floor( _y );

            stick::Float32 floatPartX0 = _x - intPartX;
            stick::Float32 floatPartY0 = _y - intPartY;

            stick::Float32 floatPartX1 = floatPartX0 - 1.0f;
            stick::Float32 floatPartY1 = floatPartY0 - 1.0f;

            stick::Float32 fadedX = detail::fade(floatPartX0);
            stick::Float32 fadedY = detail::fade(floatPartY0);

            stick::UInt32 indexX0 = intPartX & 255;
            stick::UInt32 indexY0 = intPartY & 255;
            stick::UInt32 indexX1 = indexX0 + 1;
            stick::UInt32 indexY1 = indexY0 + 1;


            stick::Float32 grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0]], floatPartX0, floatPartY0);
            stick::Float32 grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1]], floatPartX0, floatPartY1);

            stick::Float32 lerp0 = crunch::mix(grad0, grad1, fadedY);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0]], floatPartX1, floatPartY0 );
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1]], floatPartX1, floatPartY1);

            stick::Float32 lerp1 = crunch::mix(grad0, grad1, fadedY);

            return (stick::Float32)0.507 * ( crunch::mix(lerp0, lerp1, fadedX) );
        }

        /**
         * @brief Computes the 3D perlin noise value at the specified coordinate in noise space.
         * @param _x The x coordinate in noise space.
         * @param _y The y coordinate in noise space.
         * @param _z The z coordinate in noise space.
         */
        stick::Float32 noise(stick::Float32 _x, stick::Float32 _y, stick::Float32 _z)
        {
            stick::Int32 intPartX = (stick::Int32)crunch::floor( _x );
            stick::Int32 intPartY = (stick::Int32)crunch::floor( _y );
            stick::Int32 intPartZ = (stick::Int32)crunch::floor( _z );

            stick::Float32 floatPartX0 = _x - intPartX;
            stick::Float32 floatPartY0 = _y - intPartY;
            stick::Float32 floatPartZ0 = _z - intPartZ;

            stick::Float32 floatPartX1 = floatPartX0 - 1.0f;
            stick::Float32 floatPartY1 = floatPartY0 - 1.0f;
            stick::Float32 floatPartZ1 = floatPartZ0 - 1.0f;

            stick::Float32 fadedX = detail::fade(floatPartX0);
            stick::Float32 fadedY = detail::fade(floatPartY0);
            stick::Float32 fadedZ = detail::fade(floatPartZ0);

            stick::UInt32 indexX0 = intPartX & 255;
            stick::UInt32 indexY0 = intPartY & 255;
            stick::UInt32 indexZ0 = intPartZ & 255;
            stick::UInt32 indexX1 = indexX0 + 1;
            stick::UInt32 indexY1 = indexY0 + 1;
            stick::UInt32 indexZ1 = indexZ0 + 1;

            stick::Float32 grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ0]]], floatPartX0, floatPartY0, floatPartZ0);
            stick::Float32 grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ1]]], floatPartX0, floatPartY0, floatPartZ1);

            stick::Float32 lerp0 = crunch::mix(grad0, grad1, fadedZ);

            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ0]]], floatPartX0, floatPartY1, floatPartZ0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ1]]], floatPartX0, floatPartY1, floatPartZ1);

            stick::Float32 lerp1 = crunch::mix(grad0, grad1, fadedZ);

            stick::Float32 finLerp0 = crunch::mix(lerp0, lerp1, fadedY);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ0]]], floatPartX1, floatPartY0, floatPartZ0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ1]]], floatPartX1, floatPartY0, floatPartZ1);

            lerp0 = crunch::mix(grad0, grad1, fadedZ);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ0]]], floatPartX1, floatPartY1, floatPartZ0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ1]]], floatPartX1, floatPartY1, floatPartZ1);

            lerp1 = crunch::mix(grad0, grad1, fadedZ);

            stick::Float32 finLerp1 = crunch::mix(lerp0, lerp1, fadedY);

            return 0.936f * ( crunch::mix(finLerp0, finLerp1, fadedX));
        }

        /**
         * @brief Computes the 4D perlin noise value at the specified coordinate in noise space.
         * @param _x The x coordinate in noise space.
         * @param _y The y coordinate in noise space.
         * @param _z The z coordinate in noise space.
         * @param _t The t coordinate in noise space.
         */
        stick::Float32 noise(stick::Float32 _x, stick::Float32 _y, stick::Float32 _z, stick::Float32 _t)
        {
            stick::Int32 intPartX = (stick::Int32)crunch::floor( _x );
            stick::Int32 intPartY = (stick::Int32)crunch::floor( _y );
            stick::Int32 intPartZ = (stick::Int32)crunch::floor( _z );
            stick::Int32 intPartT = (stick::Int32)crunch::floor( _t );

            stick::Float32 floatPartX0 = _x - intPartX;
            stick::Float32 floatPartY0 = _y - intPartY;
            stick::Float32 floatPartZ0 = _z - intPartZ;
            stick::Float32 floatPartT0 = _t - intPartT;

            stick::Float32 floatPartX1 = floatPartX0 - 1.0f;
            stick::Float32 floatPartY1 = floatPartY0 - 1.0f;
            stick::Float32 floatPartZ1 = floatPartZ0 - 1.0f;
            stick::Float32 floatPartT1 = floatPartT0 - 1.0f;

            stick::Float32 fadedX = detail::fade(floatPartX0);
            stick::Float32 fadedY = detail::fade(floatPartY0);
            stick::Float32 fadedZ = detail::fade(floatPartZ0);
            stick::Float32 fadedT = detail::fade(floatPartT0);

            stick::UInt32 indexX0 = intPartX & 255;
            stick::UInt32 indexY0 = intPartY & 255;
            stick::UInt32 indexZ0 = intPartZ & 255;
            stick::UInt32 indexT0 = intPartT & 255;
            stick::UInt32 indexX1 = indexX0 + 1;
            stick::UInt32 indexY1 = indexY0 + 1;
            stick::UInt32 indexZ1 = indexZ0 + 1;
            stick::UInt32 indexT1 = indexT0 + 1;

            stick::Float32 grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX0, floatPartY0, floatPartZ0, floatPartT0);
            stick::Float32 grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX0, floatPartY0, floatPartZ0, floatPartT1);
            stick::Float32 lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX0, floatPartY0, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX0, floatPartY0, floatPartZ1, floatPartT1);
            stick::Float32 lerp1 = crunch::mix(grad0, grad1, fadedT);
            stick::Float32 tempLerp0 = crunch::mix(lerp0, lerp1, fadedZ);

            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX0, floatPartY1, floatPartZ0, floatPartT0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX0, floatPartY1, floatPartZ0, floatPartT1);
            lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX0, floatPartY1, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX0, floatPartY1, floatPartZ1, floatPartT1);
            lerp1 = crunch::mix(grad0, grad1, fadedT);
            stick::Float32 tempLerp1 = crunch::mix(lerp0, lerp1, fadedZ);

            stick::Float32 finLerp0 = crunch::mix(tempLerp0, tempLerp1, fadedY);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX1, floatPartY0, floatPartZ0, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX1, floatPartY0, floatPartZ0, floatPartT1);
            lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX1, floatPartY0, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX1, floatPartY0, floatPartZ1, floatPartT1);
            lerp1 = crunch::mix(grad0, grad1, fadedT);
            tempLerp0 = crunch::mix(lerp0, lerp1, fadedZ);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX1, floatPartY1, floatPartZ0, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX1, floatPartY1, floatPartZ0, floatPartT1);
            lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX1, floatPartY1, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX1, floatPartY1, floatPartZ1, floatPartT1);
            lerp1 = crunch::mix(grad0, grad1, fadedT);
            tempLerp1 = crunch::mix(lerp0, lerp1, fadedZ);

            stick::Float32 finLerp1 = crunch::mix(tempLerp0, tempLerp1, fadedY);

            return 0.87f * ( crunch::mix(finLerp0, finLerp1, fadedX) );
        }

        /**
         * @brief Computes the 2D perlin noise value at the specified coordinate in noise space.
         * @param _vec The coordinate in noise space.
         */
        template<class T>
        stick::Float32 noise(const Vector2<T> & _vec)
        {
            return noise(_vec.x, _vec.y);
        }

        /**
         * @brief Computes the 3D perlin noise value at the specified coordinate in noise space.
         * @param _vec The coordinate in noise space.
         */
        template<class T>
        stick::Float32 noise(const Vector3<T> & _vec)
        {
            return noise(_vec.x, _vec.y, _vec.z);
        }

        /**
         * @brief Computes the 4D perlin noise value at the specified coordinate in noise space.
         * @param _vec The coordinate in noise space.
         */
        template<class T>
        stick::Float32 noise(const Vector4<T> & _vec)
        {
            return noise(_vec.x, _vec.y, _vec.z, _vec.w);
        }

        /**
         * @brief Computes the 1D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _x The x coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         */
        stick::Float32 periodicNoise(stick::Float32 _x, stick::Int32 _px)
        {
            stick::Int32 intPart = (stick::Int32)crunch::floor( _x );
            stick::Float32 floatPart = _x - intPart;

            stick::Float32 faded = detail::fade(floatPart);

            stick::UInt32 index0 = (intPart % _px) & 255;
            stick::UInt32 index1 = (index0 + 1) % _px;

            stick::Float32 grad0 = detail::grad(m_rand[index0], floatPart);
            stick::Float32 grad1 = detail::grad(m_rand[index1], floatPart - 1.0f);

            return 0.188f * ( crunch::mix(grad0, grad1, faded) );
        }

        /**
         * @brief Computes the 2D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _x The x coordinate in noise space.
         * @param _y The y coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         * @param _py The period along the y axis in noise space.
         */
        stick::Float32 periodicNoise(stick::Float32 _x, stick::Float32 _y, stick::Int32 _px, stick::Int32 _py)
        {
            stick::Int32 intPartX = (stick::Int32)crunch::floor( _x );
            stick::Int32 intPartY = (stick::Int32)crunch::floor( _y );

            stick::Float32 floatPartX0 = _x - intPartX;
            stick::Float32 floatPartY0 = _y - intPartY;

            stick::Float32 floatPartX1 = floatPartX0 - 1.0f;
            stick::Float32 floatPartY1 = floatPartY0 - 1.0f;

            stick::Float32 fadedX = detail::fade(floatPartX0);
            stick::Float32 fadedY = detail::fade(floatPartY0);

            stick::UInt32 indexX0 = (intPartX % _px) & 255;
            stick::UInt32 indexY0 = (intPartY % _py) & 255;
            stick::UInt32 indexX1 = (indexX0 + 1) % _px;
            stick::UInt32 indexY1 = (indexY0 + 1) % _py;

            stick::Float32 grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0]], floatPartX0, floatPartY0);
            stick::Float32 grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1]], floatPartX0, floatPartY1);

            stick::Float32 lerp0 = crunch::mix(grad0, grad1, fadedY);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0]], floatPartX1, floatPartY0 );
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1]], floatPartX1, floatPartY1);

            stick::Float32 lerp1 = crunch::mix(grad0, grad1, fadedY);

            return 0.507f * ( crunch::mix(lerp0, lerp1, fadedX) );
        }

        /**
         * @brief Computes the 3D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _x The x coordinate in noise space.
         * @param _y The y coordinate in noise space.
         * @param _z The z coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         * @param _py The period along the y axis in noise space.
         * @param _pz The period along the z axis in noise space.
         */
        stick::Float32 periodicNoise(stick::Float32 _x, stick::Float32 _y, stick::Float32 _z, stick::Int32 _px, stick::Int32 _py, stick::Int32 _pz)
        {
            stick::Int32 intPartX = (stick::Int32)crunch::floor( _x );
            stick::Int32 intPartY = (stick::Int32)crunch::floor( _y );
            stick::Int32 intPartZ = (stick::Int32)crunch::floor( _z );

            stick::Float32 floatPartX0 = _x - intPartX;
            stick::Float32 floatPartY0 = _y - intPartY;
            stick::Float32 floatPartZ0 = _z - intPartZ;

            stick::Float32 floatPartX1 = floatPartX0 - 1.0f;
            stick::Float32 floatPartY1 = floatPartY0 - 1.0f;
            stick::Float32 floatPartZ1 = floatPartZ0 - 1.0f;

            stick::Float32 fadedX = detail::fade(floatPartX0);
            stick::Float32 fadedY = detail::fade(floatPartY0);
            stick::Float32 fadedZ = detail::fade(floatPartZ0);

            stick::UInt32 indexX0 = (intPartX % _px) & 255;
            stick::UInt32 indexY0 = (intPartY % _py) & 255;
            stick::UInt32 indexZ0 = (intPartZ % _pz) & 255;
            stick::UInt32 indexX1 = ((indexX0 + 1) % _px);
            stick::UInt32 indexY1 = ((indexY0 + 1) % _py);
            stick::UInt32 indexZ1 = ((indexZ0 + 1) % _pz);

            stick::Float32 grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ0]]], floatPartX0, floatPartY0, floatPartZ0);
            stick::Float32 grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ1]]], floatPartX0, floatPartY0, floatPartZ1);

            stick::Float32 lerp0 = crunch::mix(grad0, grad1, fadedZ);

            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ0]]], floatPartX0, floatPartY1, floatPartZ0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ1]]], floatPartX0, floatPartY1, floatPartZ1);

            stick::Float32 lerp1 = crunch::mix(grad0, grad1, fadedZ);

            stick::Float32 finLerp0 = crunch::mix(lerp0, lerp1, fadedY);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ0]]], floatPartX1, floatPartY0, floatPartZ0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ1]]], floatPartX1, floatPartY0, floatPartZ1);

            lerp0 = crunch::mix(grad0, grad1, fadedZ);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ0]]], floatPartX1, floatPartY1, floatPartZ0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ1]]], floatPartX1, floatPartY1, floatPartZ1);

            lerp1 = crunch::mix(grad0, grad1, fadedZ);

            stick::Float32 finLerp1 = crunch::mix(lerp0, lerp1, fadedY);

            return 0.936f * ( crunch::mix(finLerp0, finLerp1, fadedX));
        }

        /**
         * @brief Computes the 4D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _x The x coordinate in noise space.
         * @param _y The y coordinate in noise space.
         * @param _z The z coordinate in noise space.
         * @param _t The t coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         * @param _py The period along the y axis in noise space.
         * @param _pz The period along the z axis in noise space.
         * @param _pt The period along the t axis in noise space.
         */
        stick::Float32 periodicNoise(stick::Float32 _x, stick::Float32 _y, stick::Float32 _z, stick::Float32 _t, stick::Int32 _px, stick::Int32 _py, stick::Int32 _pz, stick::Int32 _pt)
        {
            stick::Int32 intPartX = (stick::Int32)crunch::floor( _x );
            stick::Int32 intPartY = (stick::Int32)crunch::floor( _y );
            stick::Int32 intPartZ = (stick::Int32)crunch::floor( _z );
            stick::Int32 intPartT = (stick::Int32)crunch::floor( _t );

            stick::Float32 floatPartX0 = _x - intPartX;
            stick::Float32 floatPartY0 = _y - intPartY;
            stick::Float32 floatPartZ0 = _z - intPartZ;
            stick::Float32 floatPartT0 = _t - intPartT;

            stick::Float32 floatPartX1 = floatPartX0 - 1.0f;
            stick::Float32 floatPartY1 = floatPartY0 - 1.0f;
            stick::Float32 floatPartZ1 = floatPartZ0 - 1.0f;
            stick::Float32 floatPartT1 = floatPartT0 - 1.0f;

            stick::Float32 fadedX = detail::fade(floatPartX0);
            stick::Float32 fadedY = detail::fade(floatPartY0);
            stick::Float32 fadedZ = detail::fade(floatPartZ0);
            stick::Float32 fadedT = detail::fade(floatPartT0);

            stick::UInt32 indexX0 = (intPartX % _px) & 255;
            stick::UInt32 indexY0 = (intPartY % _py) & 255;
            stick::UInt32 indexZ0 = (intPartZ % _pz) & 255;
            stick::UInt32 indexT0 = (intPartT % _pt) & 255;
            stick::UInt32 indexX1 = (indexX0 + 1) % _px;
            stick::UInt32 indexY1 = (indexY0 + 1) % _py;
            stick::UInt32 indexZ1 = (indexZ0 + 1) % _pz;
            stick::UInt32 indexT1 = (indexT0 + 1) % _pt;

            stick::Float32 grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX0, floatPartY0, floatPartZ0, floatPartT0);
            stick::Float32 grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX0, floatPartY0, floatPartZ0, floatPartT1);
            stick::Float32 lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX0, floatPartY0, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX0, floatPartY0, floatPartZ1, floatPartT1);
            stick::Float32 lerp1 = crunch::mix(grad0, grad1, fadedT);
            stick::Float32 tempLerp0 = crunch::mix(lerp0, lerp1, fadedZ);

            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX0, floatPartY1, floatPartZ0, floatPartT0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX0, floatPartY1, floatPartZ0, floatPartT1);
            lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX0, floatPartY1, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX0 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX0, floatPartY1, floatPartZ1, floatPartT1);
            lerp1 = crunch::mix(grad0, grad1, fadedT);
            stick::Float32 tempLerp1 = crunch::mix(lerp0, lerp1, fadedZ);

            stick::Float32 finLerp0 = crunch::mix(tempLerp0, tempLerp1, fadedY);


            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX1, floatPartY0, floatPartZ0, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX1, floatPartY0, floatPartZ0, floatPartT1);
            lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX1, floatPartY0, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY0 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX1, floatPartY0, floatPartZ1, floatPartT1);
            lerp1 = crunch::mix(grad0, grad1, fadedT);
            tempLerp0 = crunch::mix(lerp0, lerp1, fadedZ);

            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT0]]]], floatPartX1, floatPartY1, floatPartZ0, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ0 + m_rand[indexT1]]]], floatPartX1, floatPartY1, floatPartZ0, floatPartT1);
            lerp0 = crunch::mix(grad0, grad1, fadedT);
            grad0 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT0]]]], floatPartX1, floatPartY1, floatPartZ1, floatPartT0);
            grad1 = detail::grad(m_rand[indexX1 + m_rand[indexY1 + m_rand[indexZ1 + m_rand[indexT1]]]], floatPartX1, floatPartY1, floatPartZ1, floatPartT1);
            lerp1 = crunch::mix(grad0, grad1, fadedT);
            tempLerp1 = crunch::mix(lerp0, lerp1, fadedZ);

            stick::Float32 finLerp1 = crunch::mix(tempLerp0, tempLerp1, fadedY);

            return 0.87f * ( crunch::mix(finLerp0, finLerp1, fadedX) );
        }

        /**
         * @brief Computes the 2D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _vec The coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         * @param _py The period along the y axis in noise space.
         */
        template<class T>
        stick::Float32 periodicNoise(const Vector2<T> & _vec, stick::Int32 _px, stick::Int32 _py)
        {
            return periodicNoise(_vec.x, _vec.y, _px, _py);
        }

        /**
         * @brief Computes the 3D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _vec The coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         * @param _py The period along the y axis in noise space.
         * @param _pz The period along the z axis in noise space.
         */
        template<class T>
        stick::Float32 periodicNoise(const Vector3<T> & _vec, stick::Int32 _px, stick::Int32 _py, stick::Int32 _pz)
        {
            return periodicNoise(_vec.x, _vec.y, _vec.z, _px, _py, _pz);
        }

        /**
         * @brief Computes the 4D periodic perlin noise value at the specified coordinate in noise space.
         *
         * Periodic noise functions allow you to generate tileable, seamlessly wrapping noise values.
         *
         * @param _vec The coordinate in noise space.
         * @param _px The period along the x axis in noise space.
         * @param _py The period along the y axis in noise space.
         * @param _pz The period along the z axis in noise space.
         * @param _pt The period along the t axis in noise space.
         */
        template<class T>
        stick::Float32 periodicNoise(const Vector4<T> & _vec, stick::Int32 _px, stick::Int32 _py, stick::Int32 _pz, stick::Int32 _pt)
        {
            return periodicNoise(_vec.x, _vec.y, _vec.w, _px, _py, _pz, _pt);
        }

    private:

        detail::RandomValueArray m_rand;
    };
}

#endif //CRUNCH_PERLINNOISE_HPP
