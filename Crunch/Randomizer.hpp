#ifndef CRUNCH_RANDOMIZER_HPP
#define CRUNCH_RANDOMIZER_HPP

#include <Stick/Platform.hpp>
#include <random>
#include <type_traits>

namespace crunch
{
    /**
     * @brief A class to generate random numbers.
     * @arg Engine The random number generator engine.
     */
    template<class Engine = std::mt19937>
    class RandomizerT
    {
    public:

        /**
         * @brief Constructs a random number generator, randomizing its seed.
         */
        RandomizerT()
        {
            randomizeSeed();
        }

        /**
         * @brief Constructs a random number generator with the provided seed.
         */
        RandomizerT(stick::UInt32 _seed)
        {
            setSeed(_seed);
        }

        /**
         * @brief Randomizes the seed.
         */
        void randomizeSeed()
        {
            std::random_device rd;
            m_engine = Engine(rd());
        }

        /**
         * @brief Sets the seed of the random number generator.
         *
         * This is useful, if you want to get reproducible random numbers.
         * The random numbers produced by the generator will be identical
         * every time for the same seed.
         */
        void setSeed(stick::UInt32 _seed)
        {
            m_engine = Engine(_seed);
        }

        /**
         * @brief Returns a random 32-bit floating point number in the requested range.
         */
        stick::Float32 randomf(stick::Float32 _min = 0.0f, stick::Float32 _max = 1.0f)
        {
            m_floatDistribution = std::uniform_real_distribution<stick::Float32>(_min, _max);
            return m_floatDistribution(m_engine);
        }

        /**
         * @brief Returns a random 64-bit floating point number in the requested range.
         */
        stick::Float64 randomd(stick::Float64 _min = 0.0, stick::Float64 _max = 1.0)
        {
            m_doubleDistribution = std::uniform_real_distribution<stick::Float64>(_min, _max);
            return m_doubleDistribution(m_engine);
        }

        /**
         * @brief Returns a random 32-bit integer in the requested range.
         */
        stick::Int32 randomi(stick::Int32 _min = 0, stick::Int32 _max = std::numeric_limits<stick::Int32>::max())
        {
            m_intDistribution = std::uniform_int_distribution<stick::Int32>(_min, _max);
            return m_intDistribution(m_engine);
        }

        /**
         * @brief Returns a random 32-bit unsigned integer in the requested range.
         */
        stick::UInt32 randomui(stick::UInt32 _min = 0, stick::UInt32 _max = std::numeric_limits<stick::UInt32>::max())
        {
            m_uintDistribution = std::uniform_int_distribution<stick::UInt32>(_min, _max);
            return m_uintDistribution(m_engine);
        }


    private:

        Engine m_engine;

        std::uniform_int_distribution<stick::UInt32> m_uintDistribution;
        std::uniform_int_distribution<stick::Int32> m_intDistribution;
        std::uniform_real_distribution<stick::Float32> m_floatDistribution;
        std::uniform_real_distribution<stick::Float64> m_doubleDistribution;
    };

    using Randomizer = RandomizerT<>;
}

#endif //CRUNCH_RANDOMIZER_HPP
