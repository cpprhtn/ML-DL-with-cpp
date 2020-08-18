#pragma once

#include <assert.h>
#include <iostream>

#define SAFE_DELETE(pointer) if(pointer != nullptr){delete pointer; pointer=nullptr;} //Clears allocated memory


template<class TT>
class VectorT
{
public:
	int num_dimension;
	TT *values_;

public:
	VectorT(void)
		: num_dimension(0), values_(0)
	{};

	VectorT(const int& num)
	{
		values_ = 0;

		initialize(num);
	}

	VectorT(const VectorT<TT>& vector_)
	{
		values_ = 0;

		initialize(vector_.num_dimension, false);

		for(int i=0; i < num_dimension; i ++)	values_[i] = vector_[i];
	}

	~VectorT(void)
	{
		if(values_ != 0) delete [] values_;
		num_dimension = 0;
	}

public:
	void initialize(const int& num_, const bool initialize = false)
	{
		num_dimension = num_;

		SAFE_DELETE(values_);

		if(num_dimension>0)
		{
			values_ = new TT [num_dimension];
			if(initialize==true) for(int i=0; i<num_dimension; i++) values_[i] = TT();
		}
	}

public:
	void operator = (const VectorT<TT>& from)
	{
        if (from.num_dimension != num_dimension)
        {
            num_dimension = from.num_dimension;

            SAFE_DELETE(values_);

            values_ = new TT[num_dimension];
        }

		for(int i = 0; i < num_dimension; i++) values_[i] = from[i];
	}

	TT& operator[](const int& i) const
	{
        assert(i >= 0);
        assert(i < num_dimension);

		return values_[i];
	}

    TT& operator()(const int& i) const
    {
        assert(i >= 0);
        assert(i < num_dimension);

        return values_[i];
    }

	VectorT<TT> operator+(const VectorT & vector) const
	{
		assert(num_dimension == vector.num_dimension);

		VectorT<TT> result(num_dimension);

		for(int i=0;i<num_dimension;i++) result[i] = values_[i] + vector.values_[i];

		return result;
	}

	VectorT<TT> operator-(const VectorT & vector)const
	{
		assert(num_dimension == vector.num_dimension);

		VectorT<TT> result(num_dimension);

		for(int i=0;i<num_dimension;i++) result[i] = values_[i] - vector.values_[i];

		return result;
	}

    void operator += (const TT& s)
	{
		for(int i = 0; i < num_dimension; i++) values_[i] += s;
	}

	void operator -= (const TT& s)
	{
		for(int i = 0; i < num_dimension; i++) values_[i] -= s;
	}

	void operator *= (const int& s)
	{
		for(int i = 0; i < num_dimension; i++) values_[i] *= s;
	}

	void operator *= (const TT& s)
	{
		for(int i = 0; i < num_dimension; i++) values_[i] *= s;
	}

	void operator /= (const TT& s)
	{
		for(int i = 0; i < num_dimension; i++) values_[i] /= s;
	}

	void operator += (const VectorT<TT>& s)
	{
		assert(num_dimension == s.num_dimension);

		for(int i = 0; i < num_dimension; i++) values_[i] += s.values_[i];
	}

	void operator -= (const VectorT<TT>& s)
	{
		assert(num_dimension == s.num_dimension);
		
		for(int i = 0; i < num_dimension; i++) values_[i] -= s.values_[i];
	}

	void operator *= (const VectorT<TT>& s)
	{
		assert(num_dimension == s.num_dimension);

		for(int i = 0; i < num_dimension; i++) values_[i] *= s.values_[i];
	}

	void operator /= (const VectorT<TT>& s)
	{
		assert(num_dimension == s.num_dimension);

		for(int i = 0; i < num_dimension; i++) values_[i] /= s.values_[i];
	}

	VectorT <TT> operator*(const TT& s) const
	{
		VectorT <TT> V(num_dimension);

		for(int i=0; i < num_dimension; i++) V.values_[i]=values_[i]*s;

		return V;
	}

    void copyPartial(const VectorT<TT>& source, const int& start_ix_this, const int& start_ix_source, const int& num)
    {
        assert(start_ix_this >= 0);
        assert(start_ix_this + num <= num_dimension);

        assert(start_ix_source >= 0);
        assert(start_ix_source + num <= source.num_dimension);

        for (int i = 0; i < num; i++)
        {
            values_[start_ix_this + i] = source.values_[start_ix_source + i];
        }
    }
};

template<class TT> 
std::ostream& operator<<(std::ostream& output, const VectorT<TT>& v)
{
	for(int i=0; i<v.num_dimension; i++) output<<v.values_[i]<<" ";
    output << std::flush;
	return output;
}