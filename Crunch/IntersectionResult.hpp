#ifndef CRUNCH_INTERSECTIONRESULT_HPP
#define CRUNCH_INTERSECTIONRESULT_HPP

#include <Stick/DynamicArray.hpp>

namespace crunch
{
    //@Check: Make intersections accessible in non const so we can avoid the extra copy in the constructor?
    // Or add a version that moves the array?
    template<class VT>
    class IntersectionResult
    {
    public:

        using VectorType = VT;
        using ResultArray = stick::DynamicArray<VT>;

        IntersectionResult()
        {

        }

        IntersectionResult(const ResultArray & _intersections) :
            m_intersections(_intersections)
        {

        }

        //this is enough for safe bool idiom in c++11
        explicit operator bool() const
        {
            return m_intersections.count();
        }

        const ResultArray & intersections() const
        {
            return m_intersections;
        }

    private:

        ResultArray m_intersections;
    };
}

#endif //CRUNCH_INTERSECTIONRESULT_HPP
