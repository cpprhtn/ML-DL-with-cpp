#include <assert.h>
#include "MatrixT.h"

template<class T>
void MatrixT<T>::multiply(const VectorT<T>& vector, VectorT<T>& result) const
{
    assert(num_rows_ <= result.num_dimension);
    assert(num_cols_ <= vector.num_dimension);

    for (int row = 0; row < num_rows_; row++)
    {
        result.values_[row] = (T)0;

        int ix = row*num_cols_;
        T temp;

        for (int col = 0; col < num_cols_; col++, ix++)
        {
            temp = values_[ix];
            temp *= vector.values_[col];

            result.values_[row] += temp;
        }
    }
}

template<class T>
void MatrixT<T>::multiplyTransposed(const VectorT<T>& vector, VectorT<T>& result) const 
{
    assert(num_rows_ <= vector.num_dimension);
    assert(num_cols_ <= result.num_dimension);

    for (int col = 0; col < num_cols_; col++)
    {
        result.values_[col] = (T)0;

        for (int row = 0, ix = col; row < num_rows_; row++, ix += num_cols_)
        {
            result.values_[col] += values_[ix] * vector.values_[row];
        }
    }
}

template<class T>
void MatrixT<T>::cout()
{
	for (int row = 0; row < num_rows_; row++)
	{
		for (int col = 0; col < num_cols_; col++)
		{
			std::cout << getValue(row, col) << " ";
		}

		std::cout << std::endl;
	}
}

template<class T>
int MatrixT<T>::get1DIndex(const int& row, const int& column) const
{
	assert(row >= 0);
	assert(column >= 0);
	assert(row < num_rows_);
	assert(column < num_cols_);

	//column = i, row = j
	return column + row * num_cols_;    //data structure is for faster dot product of a row vector and VectorT input.
}