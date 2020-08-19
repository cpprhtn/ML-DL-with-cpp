#pragma once

#include "VectorT.h"

template<class T>
class MatrixT
{
public:
    int num_rows_;  //m_
    int num_cols_;  //n_
    T   *values_;

    MatrixT()
        : values_(nullptr), num_rows_(0), num_cols_(0)
    {}

	void initialize(const int& _m, const int& _n, const bool init = true);

	void multiply(const VectorT<T>& vector, VectorT<T>& result) const;
    void multiplyTransposed(const VectorT<T>& vector, VectorT<T>& result) const;

	int get1DIndex(const int& row, const int& column) const;
	T&  getValue(const int& row, const int& column) const;

	void cout();
};  //Makes 1D arrays into 2D arrays when indexing
