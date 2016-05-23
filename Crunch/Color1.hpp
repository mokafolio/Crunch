#ifndef CRUNCH_COLOR1_HPP
#define CRUNCH_COLOR1_HPP

namespace crunch
{
    /**
     * @brief A one channel color.
     * @arg C The channel storage.
     */
    template<class T>
    class Color1 : public T
    {
    public:

        using ChannelsType = T;

        using ValueType = typename T::ValueType;

        /**
         * @brief Default Constructor.
         *
         * Does nothing for speed.
         */
        Color1();

        /**
         * @brief Constructs a color and sets its one channel to the provided value.
         */
        explicit Color1(ValueType _val);

        /**
         * @brief Returns true if both colors are the same.
         */
        bool operator==(const Color1 & _col) const;

        /**
         * @brief Returns true if both colors are not the same.
         */
        bool operator!=(const Color1 & _col) const;

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
        Color1 operator+(const Color1 & _col) const;

        /**
         * @brief Subtract the provided color from this color.
         * @return Returns the resulting color.
         */
        Color1 operator-(const Color1 & _col) const;

        /**
         * @brief Multiply the provided color with this color.
         * @return Returns the resulting color.
         */
        Color1 operator*(const Color1 & _col) const;

        /**
         * @brief Devide this color by the provided color.
         * @return Returns the resulting color.
         */
        Color1 operator/(const Color1 & _col) const;

        /**
         * @brief Subtract the provided color from this.
         * @return A reference to this.
         */
        Color1 & operator-=(const Color1 & _col);

        /**
         * @brief Add the provided color to this.
         * @return A reference to this.
         */
        Color1 & operator+=(const Color1 & _col);

        /**
         * @brief Multiply the provided color with this.
         * @return A reference to this.
         */
        Color1 & operator*=(const Color1 & _col);

        /**
         * @brief Devide this color by the provided color.
         * @return A reference to this.
         */
        Color1 & operator/=(const Color1 & _col);

        /**
         * @brief Devide this color by the provided number.
         * @return The resulting color.
         */
        Color1 operator/(ValueType _val) const;

        /**
         * @brief Multiplies this color by the provided number.
         * @return The resulting color.
         */
        Color1 operator*(ValueType _val) const;

        /**
         * @brief Adds the provided number to all channels of this color.
         * @return The resulting color.
         */
        Color1 operator+(ValueType _val) const;

        /**
         * @brief Subtracts the provided number from all channels of this color.
         * @return The resulting color.
         */
        Color1 operator-(ValueType _val) const;

        /**
         * @brief Devide this color by the provided number.
         * @return A reference to this.
         */
        Color1 & operator/=(ValueType _val);

        /**
         * @brief Multiply this color by the provided number.
         * @return A reference to this.
         */
        Color1 & operator*=(ValueType _val);

        /**
         * @brief Add the provided number to this color.
         * @return A reference to this.
         */
        Color1 & operator+=(ValueType _val);

        /**
         * @brief Subtract the provided number from this color.
         * @return A reference to this.
         */
        Color1 & operator-=(ValueType _val);

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
    inline Color1<C>::Color1()
    {
    }

    template<class C>
    inline Color1<C>::Color1(ValueType _val) :
        ChannelsType(_val)
    {
    }


    // Boolean
    //____________________________________

    template<class C>
    inline bool Color1<C>::operator == (const Color1 & _col) const
    {
        if ((*this)[0] == _col[0])
            return true;
        else
            return false;
    }

    template<class C>
    inline bool Color1<C>::operator!=(const Color1 & _col) const
    {
        return !(*this == _col);
    }

    template<class C>
    inline typename Color1<C>::ValueType & Color1<C>::operator [](stick::UInt32 _index)
    {
        return *(reinterpret_cast<ValueType *>(this) + _index);
    }

    template<class C>
    inline const typename Color1<C>::ValueType & Color1<C>::operator [](stick::UInt32 _index) const
    {
        return *(reinterpret_cast<const ValueType *>(this) + _index);
    }


    // Arithmetic operations
    //____________________________________

    template<class C>
    inline Color1<C> Color1<C>::operator+(const Color1 & _col) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] + _col[0];
        return ret;
    }

    template<class C>
    inline Color1<C> Color1<C>::operator-(const Color1 & _col) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] - _col[0];
        return ret;
    }

    template<class C>
    inline Color1<C> Color1<C>::operator*(const Color1 & _col) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] * _col[0];
        return ret;
    }

    template<class C>
    inline Color1<C> Color1<C>::operator/(const Color1 & _col) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] / _col[0];
        return ret;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator-=(const Color1 & _col)
    {
        (*this)[0] -= _col[0];
        return *this;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator+=(const Color1 & _col)
    {
        (*this)[0] += _col[0];
        return *this;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator*=(const Color1 & _col)
    {
        (*this)[0] *= _col[0];
        return *this;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator/=(const Color1 & _col)
    {
        (*this)[0] /= _col[0];
        return *this;
    }


    // Real Arithmetic
    //____________________________________

    template<class C>
    inline Color1<C> Color1<C>::operator/(ValueType _val) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] / _val;
        return ret;
    }

    template<class C>
    inline Color1<C> Color1<C>::operator*(ValueType _val) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] * _val;
        return ret;
    }

    template<class C>
    inline Color1<C> Color1<C>::operator+(ValueType _val) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] + _val;
        return ret;
    }

    template<class C>
    inline Color1<C> Color1<C>::operator-(ValueType _val) const
    {
        Color1<C> ret;
        ret[0] = (*this)[0] - _val;
        return ret;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator/=(ValueType _val)
    {
        (*this)[0] /= _val;
        return *this;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator*=(ValueType _val)
    {
        (*this)[0] *= _val;
        return *this;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator+=(ValueType _val)
    {
        (*this)[0] += _val;
        return *this;
    }

    template<class C>
    inline Color1<C> & Color1<C>::operator-=(ValueType _val)
    {
        (*this)[0] -= _val;
        return *this;
    }

    //Pointer accessors
    //____________________________________

    template<class C>
    inline typename Color1<C>::ValueType * Color1<C>::ptr()
    {
        return &((*this)[0]);
    }

    template<class C>
    inline const typename Color1<C>::ValueType * Color1<C>::ptr() const
    {
        return &((*this)[0]);
    }
}

#endif //CRUNCH_COLOR1_HPP
