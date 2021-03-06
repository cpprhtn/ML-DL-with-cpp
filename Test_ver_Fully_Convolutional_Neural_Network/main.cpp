#include <iostream>
#include "NN.h"

void main()
{
	VectorT<D> x(2);
	x[0] = 0.0; x[1] = 0.0;

	VectorT<D> y_target(2);
	y_target[0] = 0.3f;

	VectorT<D> y_temp(2);

	NeuralNetwork nn_;
	nn_.initialize(2, 1, 1); // (input, output, layer)
	nn_.alpha_ = 0.1;

	for (int i = 0; i < 100; i++)
	{
		nn_.setInputVector(x);
		nn_.propForward();

		nn_.copyOutputVector(y_temp);
		std::cout << y_temp << std::endl;

		nn_.propBackward(y_target);

		//Initialize to random number at first.
	}
	
}