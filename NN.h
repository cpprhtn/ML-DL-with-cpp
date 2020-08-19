#pragma once

#include <iostream>
#include "Arr1D.h"
#include "MatrixT.h"
#include <cmath> //for exp


#define MAX2(a, b)		((a) > (b) ? (a) : (b))	//for ReLU

//typedef double D;
typedef float D;

class NN
{
public:
    int num_input_;
    int num_output_;
    int num_all_layers_; //num_hidden_layers_ + 2

    D   bias_;	  //constant bias
    D   alpha_;   //learning rate

    Arr1D<VectorT<D> > layer_neuron_act_;       //input layer, output_layer, activation value
    Arr1D<VectorT<D> > layer_neuron_grad_;    
    Arr1D<MatrixT<D> > weights_;               

    VectorT<unsigned>    num_layer_acts_;        

	NN();
	NN(const int& _num_input, const int& _num_output, const int& _num_hidden_layers);

	void initialize(const int& _num_input, const int& _num_output, const int& _num_hidden_layers);
	void initialize(const VectorT<unsigned>& num_layer_acts_, const int& _num_hidden_layers);

	D getSigmoid(const D& x);
	D getRELU(const D& x);
	D getLRELU(const D& x);

	D getSigmoidGrad(const D& y);   // not from x. y = getSigmoid(x).
	D getRELUGrad(const D& x); // RELU Grad from X == RELU Grad from Y
	D getLRELUGrad(const D& x); // RELU Grad from X == RELU Grad from Y

	void SigmoidToVector(VectorT<D>& vector);
	void RELUToVector(VectorT<D>& vector);
	void LRELUToVector(VectorT<D>& vector);

	void propForward();
	void propBackward(const VectorT<D>& target);
	void updateWeight(MatrixT<D>& weight_matrix, VectorT<D>& next_layer_grad, VectorT<D>& prev_layer_act);

	void setInputVector(const VectorT<D>& input);
	void copyOutputVector(VectorT<D>& copy, bool copy_bias = false);
};