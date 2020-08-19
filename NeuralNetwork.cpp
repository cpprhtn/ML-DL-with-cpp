#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork()
{}

NeuralNetwork::NeuralNetwork(const int& _num_input, const int& _num_output, const int& _num_hidden_layers)
{
	initialize(_num_input, _num_output, _num_hidden_layers);
}

void NeuralNetwork::initialize(const int& _num_input, const int& _num_output, const int& _num_hidden_layers)
{
	num_layer_acts_.initialize(_num_hidden_layers + 2);

	num_layer_acts_[0] = _num_input + 1;                       
	for (int l = 1; l < _num_hidden_layers + 1; ++l)
	{
		num_layer_acts_[l] = _num_input + 1;                    
	}

	num_layer_acts_[_num_hidden_layers + 1] = _num_output + 1;   

	initialize(num_layer_acts_, _num_hidden_layers);
}

void NeuralNetwork::initialize(const VectorT<unsigned>& num_layer_acts_, const int& _num_hidden_layers)
{
	num_input_ = num_layer_acts_[0] - 1;                       
	num_output_ = num_layer_acts_[_num_hidden_layers + 1] - 1;
	num_all_layers_ = _num_hidden_layers + 2;

	bias_ = 1;
	alpha_ = 0.15;

	//layer_type_act_.initialize(num_all_layers_, true);    // activation type: sigmoid, ReLU

	layer_neuron_act_.initialize(num_all_layers_);
	for (int l = 0; l < num_all_layers_; ++l)
	{
		layer_neuron_act_[l].initialize(num_layer_acts_[l], true);
		layer_neuron_act_[l][num_layer_acts_[l] - 1] = bias_;
	}

	layer_neuron_grad_.initialize(num_all_layers_);
	for (int l = 0; l < num_all_layers_; ++l)
		layer_neuron_grad_[l].initialize(num_layer_acts_[l], true);

	weights_.initialize(num_all_layers_ - 1);  
	for (int l = 0; l < weights_.num_elements_; l++)
	{
		weights_[l].initialize(layer_neuron_act_[l + 1].num_dimension - 1, layer_neuron_act_[l].num_dimension);   //y = W [x b]^T

		for (int ix = 0; ix < weights_[l].num_rows_ * weights_[l].num_cols_; ix++)
			weights_[l].values_[ix] = (D)rand() / RAND_MAX * 0.1;
	}
}

D NeuralNetwork::getSigmoid(const D& x)
{
	return 1.0 / (1.0 + exp(-x));
}

D NeuralNetwork::getSigmoidGrad(const D& y)   //y = getSigmoid(x)
{
	return (1.0 - y) * y;
}

D NeuralNetwork::getRELU(const D& x)
{
	return MAX2(0.0, x);
}

D NeuralNetwork::getRELUGrad(const D& x) //RELU Grad from X == RELU Grad from Y
{
	if (x > 0.0) return 1.0;
	else return 0.0;
}

D NeuralNetwork::getLRELU(const D& x)
{
	return x > 0.0 ? x : 0.01*x;
}

D NeuralNetwork::getLRELUGrad(const D& x) //RELU Grad from X == RELU Grad from Y
{
	if (x > 0.0) return 1.0;
	else return 0.01;
}

void NeuralNetwork::SigmoidToVector(VectorT<D>& vector)
{
	for (int d = 0; d < vector.num_dimension - 1; d++) 
		vector[d] = getSigmoid(vector[d]);
}

void NeuralNetwork::RELUToVector(VectorT<D>& vector)
{
	for (int d = 0; d < vector.num_dimension - 1; d++)
		vector[d] = getRELU(vector[d]);
}

void NeuralNetwork::LRELUToVector(VectorT<D>& vector)
{
	for (int d = 0; d < vector.num_dimension - 1; d++)
		vector[d] = getLRELU(vector[d]);
}

void NeuralNetwork::propForward()
{
	for (int l = 0; l < weights_.num_elements_; l++)
	{
		weights_[l].multiply(layer_neuron_act_[l], layer_neuron_act_[l + 1]);

		//activate 
		RELUToVector(layer_neuron_act_[l + 1]);
	}
}

//backward propagation
void NeuralNetwork::propBackward(const VectorT<D>& target)
{
	//calculate gradients of output layer
	{const int l = layer_neuron_grad_.num_elements_ - 1;

	for (int d = 0; d < layer_neuron_grad_[l].num_dimension - 1; d++)  
	{
		const D &output_value(layer_neuron_act_[l][d]);
		layer_neuron_grad_[l][d] = (target[d] - output_value) * getRELUGrad(output_value);
	}}

	//calculate gradients of hidden layers
	for (int l = weights_.num_elements_ - 1; l >= 0; l--)
	{
		weights_[l].multiplyTransposed(layer_neuron_grad_[l + 1], layer_neuron_grad_[l]);

		for (int d = 0; d < layer_neuron_act_[l].num_dimension - 1; d++)   
		{
			layer_neuron_grad_[l][d] *= getRELUGrad(layer_neuron_act_[l][d]);
		}
	}

	for (int l = weights_.num_elements_ - 1; l >= 0; l--)
	{
		updateWeight(weights_[l], layer_neuron_grad_[l + 1], layer_neuron_act_[l]);
	}
}

void NeuralNetwork::updateWeight(MatrixT<D>& weight_matrix, VectorT<D>& next_layer_grad, VectorT<D>& prev_layer_act)
{
	for (int row = 0; row < weight_matrix.num_rows_; row++)
	{
		for (int col = 0; col < weight_matrix.num_cols_; col++)
		{
			const D delta_w = alpha_ * next_layer_grad[row] * prev_layer_act[col];

			weight_matrix.getValue(row, col) += delta_w;

		}
	}
}

void NeuralNetwork::setInputVector(const VectorT<D>& input)
{
	//use num_input_ in case input vector doesn't include bias

	if (input.num_dimension < num_input_)
		std::cout << "Input dimension is wrong" << std::endl;

	for (int d = 0; d < num_input_; d++)
		layer_neuron_act_[0][d] = input[d];
}

void NeuralNetwork::copyOutputVector(VectorT<D>& copy, bool copy_bias)
{
	const VectorT<D>& output_layer_act(layer_neuron_act_[layer_neuron_act_.num_elements_ - 1]);

	if (copy_bias == false)
	{
		copy.initialize(num_output_, false);

		for (int d = 0; d < num_output_; d++)
			copy[d] = output_layer_act[d];
	}
	else
	{
		copy.initialize(num_output_ + 1, false);

		for (int d = 0; d < num_output_ + 1; d++)
			copy[d] = output_layer_act[d];
	}
}