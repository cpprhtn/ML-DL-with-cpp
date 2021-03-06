#pragma once

#include <iostream>
#include "Arr1D.h"
#include "MatrixTest.h"

#define MAX2(a, b)	((a) > (b) ? (a) : (b)) //for ReLU

typedef double D;

class NeuralNetwork
{
public:
    int num_input_;
    int num_output_;
    int num_all_layers_; //num_hidden_layers_ + 2

    D   bias_;	  //constant bias
    D   alpha_;   //learning rate

    Arr1D<VectorT<D> > layer_neuron_act_;   //input layer, output_layer, activation value
    Arr1D<VectorT<D> > layer_neuron_grad_;
    Arr1D<MatrixTest<D> > weights_;

    VectorT<unsigned>    num_layer_acts_;

	NeuralNetwork();
	NeuralNetwork(const int& _num_input, const int& _num_output, const int& _num_hidden_layers);

	void initialize(const int& _num_input, const int& _num_output, const int& _num_hidden_layers);
	void initialize(const VectorT<unsigned>& num_layer_acts_, const int& _num_hidden_layers);

	D getSigmoid(const D& x);
	D getRELU(const D& x);
	D getLRELU(const D& x);

	D getSigmoidGradFromY(const D& y);   //y = getSigmoid(x).
	D getRELUGradFromY(const D& x);
	D getLRELUGradFromY(const D& x);

	void applySigmoidToVector(VectorT<D>& vector);
	void applyRELUToVector(VectorT<D>& vector);
	void applyLRELUToVector(VectorT<D>& vector);

	void propForward();
	void propBackward(const VectorT<D>& target);
	void updateWeight(MatrixTest<D>& weight_matrix, VectorT<D>& next_layer_grad, VectorT<D>& prev_layer_act);

	void setInputVector(const VectorT<D>& input);
	void copyOutputVector(VectorT<D>& copy, bool copy_bias = false);
};
