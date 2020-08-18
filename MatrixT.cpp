#include <assert.h>
#include "MatrixT.h"

template<class T>
void MatrixT<T>::multiply(const VectorT<T>& vector, VectorT<T>& result) const
{
    assert(num_rows_ <= result.num_dimension_);
    assert(num_cols_ <= vector.num_dimension_);

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