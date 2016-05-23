#ifndef CRUNCH_COLOR3_HPP
#define CRUNCH_COLOR3_HPP

namespace crunch
{
    /**
     * @brief Implements a three channel color.
     */
    template<class C>
    class Color3 : public C
    {
    public:

        /**
         * @brief The channels type of the color.
         */
        using ChannelsType = C;

        /**
         * @brief The value type (i.e. Float32) of the color.
         */
        using ValueType = typename C::ValueType;


        /**
         * @brief Default Constructor.
         *
         * Does nothing for speed.
         */
        Color3();

        /**
         * @brief Constructs a color and sets all channels to the provided value.
         */
        explicit Color3(ValueType _val);

        /**
         * @brief Constructs a color and sets its three channels to the provided values.
         */
        Color3(ValueType _one, ValueType _two, ValueType _three);

        /**
         * @brief Returns true if both colors are the same.
         */
        bool operator==(const Color3 & _col) const;

        /**
         * @brief Returns true if both colors are not the same.
         */
        bool operator!=(const Color3 & _col) const;

        /**
         * @brief allows you to get channel values by index.
         */
        inline ValueType & operator [](stick::UInt32 _index);

        /**
         * @brief allows you to get channel values by index.
         */
        inline const ValueType & operator [](stick::UInt32 _index) const;

        /**
         * @brief Add two colors together.
         * @return Returns the resulting color.
         */
        Color3 operator+(const Color3 & _col) const;

        /**
         * @brief Subtract the provided color from this color.
         * @return Returns the resulting color.
         */
        Color3 operator-(const Color3 & _col) const;

        /**
         * @brief Multiply the provided color with this color.
         * @return Returns the resulting color.
         */
        Color3 operator*(const Color3 & _col) const;

        /**
         * @brief Devide this color by the provided color.
         * @return Returns the resulting color.
         */
        Color3 operator/(const Color3 & _col) const;

        /**
         * @brief Subtract the provided color from this.
         * @return A reference to this.
         */
        Color3 & operator-=(const Color3 & _col);

        /**
         * @brief Add the provided color to this.
         * @return A reference to this.
         */
        Color3 & operator+=(const Color3 & _col);

        /**
         * @brief Multiply the provided color with this.
         * @return A reference to this.
         */
        Color3 & operator*=(const Color3 & _col);

        /**
         * @brief Devide this color by the provided color.
         * @return A reference to this.
         */
        Color3 & operator/=(const Color3 & _col);

        /**
         * @brief Devide this color by the provided number.
         * @return The resulting color.
         */
        Color3 operator/(ValueType _val) const;

        /**
         * @brief Multiplies this color by the provided number.
         * @return The resulting color.
         */
        Color3 operator*(ValueType _val) const;

        /**
         * @brief Adds the provided number to all channels of this color.
         * @return The resulting color.
         */
        Color3 operator+(ValueType _val) const;

        /**
         * @brief Subtracts the provided number from all channels of this color.
         * @return The resulting color.
         */
        Color3 operator-(ValueType _val) const;

        /**
         * @brief Devide this color by the provided number.
         * @return A reference to this.
         */
        Color3 & operator/=(ValueType _val);

        /**
         * @brief Multiply this color by the provided number.
         * @return A reference to this.
         */
        Color3 & operator*=(ValueType _val);

        /**
         * @brief Add the provided number to this color.
         * @return A reference to this.
         */
        Color3 & operator+=(ValueType _val);

        /**
         * @brief Subtract the provided number from this color.
         * @return A reference to this.
         */
        Color3 & operator-=(ValueType _val);

        /**
         * @brief Access the pointer to the underlying color data (the first channel value).
         */
        ValueType * ptr();

        /**
         * @brief Access the const pointer to the underlying color data (the first channel value).
         */
        const ValueType * ptr() const;
    };


    // Constructors
    //____________________________________

    // this does not init to zero for speed reasons!
    template<class C>
    inline Color3<C>::Color3()
    {
    }

    template<class C>
    inline Color3<C>::Color3(ValueType _val) :
        ChannelsType(_val, _val, _val)
    {
    }

    template<class C>
    inline Color3<C>::Color3(ValueType _one, ValueType _two, ValueType _three) :
        ChannelsType(_one, _two, _three)
    {

    }


    // Boolean
    //____________________________________

    template<class C>
    inline bool Color3<C>::operator == (const Color3 & _col) const
    {
        if ((*this)[0] == _col[0] && (*this)[1] == _col[1] && (*this)[2] == _col[2])
            return true;
        else
            return false;
    }

    template<class C>
    inline bool Color3<C>::operator!=(const Color3 & _col) const
    {
        return !(*this == _col);
    }

    template<class C>
    inline typename Color3<C>::ValueType & Color3<C>::operator [](stick::UInt32 _index)
    {
        return *(reinterpret_cast<ValueType *>(this) + _index);
    }

    template<class C>
    inline const typename Color3<C>::ValueType & Color3<C>::operator [](stick::UInt32 _index) const
    {
        return *(reinterpret_cast<const ValueType *>(this) + _index);
    }


    // Arithmetic operations
    //____________________________________

    template<class C>
    inline Color3<C> Color3<C>::operator+(const Color3 & _col) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] + _col[0];
        ret[1] = (*this)[1] + _col[1];
        ret[2] = (*this)[2] + _col[2];
        return ret;
    }

    template<class C>
    inline Color3<C> Color3<C>::operator-(const Color3 & _col) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] - _col[0];
        ret[1] = (*this)[1] - _col[1];
        ret[2] = (*this)[2] - _col[2];
        return ret;
    }

    template<class C>
    inline Color3<C> Color3<C>::operator*(const Color3 & _col) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] * _col[0];
        ret[1] = (*this)[1] * _col[1];
        ret[2] = (*this)[2] * _col[2];
        return ret;
    }

    template<class C>
    inline Color3<C> Color3<C>::operator/(const Color3 & _col) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] / _col[0];
        ret[1] = (*this)[1] / _col[1];
        ret[2] = (*this)[2] / _col[2];
        return ret;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator-=(const Color3 & _col)
    {
        (*this)[0] -= _col[0];
        (*this)[1] -= _col[1];
        (*this)[2] -= _col[2];
        return *this;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator+=(const Color3 & _col)
    {
        (*this)[0] += _col[0];
        (*this)[1] += _col[1];
        (*this)[2] += _col[2];
        return *this;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator*=(const Color3 & _col)
    {
        (*this)[0] *= _col[0];
        (*this)[1] *= _col[1];
        (*this)[2] *= _col[2];
        return *this;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator/=(const Color3 & _col)
    {
        (*this)[0] /= _col[0];
        (*this)[1] /= _col[1];
        (*this)[2] /= _col[2];
        return *this;
    }


    // Real Arithmetic
    //____________________________________

    template<class C>
    inline Color3<C> Color3<C>::operator/(ValueType _val) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] / _val;
        ret[1] = (*this)[1] / _val;
        ret[2] = (*this)[2] / _val;
        return ret;
    }

    template<class C>
    inline Color3<C> Color3<C>::operator*(ValueType _val) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] * _val;
        ret[1] = (*this)[1] * _val;
        ret[2] = (*this)[2] * _val;
        return ret;
    }

    template<class C>
    inline Color3<C> Color3<C>::operator+(ValueType _val) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] + _val;
        ret[1] = (*this)[1] + _val;
        ret[2] = (*this)[2] + _val;
        return ret;
    }

    template<class C>
    inline Color3<C> Color3<C>::operator-(ValueType _val) const
    {
        Color3<C> ret;
        ret[0] = (*this)[0] - _val;
        ret[1] = (*this)[1] - _val;
        ret[2] = (*this)[2] - _val;
        return ret;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator/=(ValueType _val)
    {
        (*this)[0] /= _val;
        (*this)[1] /= _val;
        (*this)[2] /= _val;
        return *this;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator*=(ValueType _val)
    {
        (*this)[0] *= _val;
        (*this)[1] *= _val;
        (*this)[2] *= _val;
        return *this;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator+=(ValueType _val)
    {
        (*this)[0] += _val;
        (*this)[1] += _val;
        (*this)[2] += _val;
        return *this;
    }

    template<class C>
    inline Color3<C> & Color3<C>::operator-=(ValueType _val)
    {
        (*this)[0] -= _val;
        (*this)[1] -= _val;
        (*this)[2] -= _val;
        return *this;
    }

    //Pointer accessors
    //____________________________________

    template<class C>
    inline typename Color3<C>::ValueType * Color3<C>::ptr()
    {
        return &(*this)[0];
    }

    template<class C>
    inline const typename Color3<C>::ValueType * Color3<C>::ptr() const
    {
        return &(*this)[0];
    }
}

#endif //CRUNCH_COLOR3_HPP
