#include <iostream>
#include "NN.h"

clss Test
{
	VectorT<D> x_, y_;
}

void main()
{
	Test xor[4];

	for (int i = 0;  i < 4; i++)
	{
		xor[i].x_.initalize(2);
		xor[i].y_.initalize(1);
	}

	xor[0].x_[0] = 0.0f;
	xor[0].x_[1] = 0.0f;
	xor[0].y_[0] = 0.0f;

	xor[1].x_[0] = 0.0f;
	xor[1].x_[1] = 1.0f;
	xor[1].y_[0] = 1.0f;

	xor[2].x_[0] = 1.0f;
	xor[2].x_[1] = 0.0f;
	xor[2].y_[0] = 1.0f;

	xor[3].x_[0] = 1.0f;
	xor[3].x_[1] = 1.0f;
	xor[3].y_[0] = 0.0f;

	VectorT<D> y_temp(2);

	NeuralNetwork nn_;
	nn_.initialize(2, 1, 1);
	nn_.alpha_ = 0.1;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			nn_.setInputVector(xor[j].x_);
			nn_.propForward();

			nn_.copyOutputVector(y_temp);
			std::cout << xor[j].y_ << " " << y_temp << std::endl;

			nn_.propBackward(xor[j].y_);
		}

		std::cout << std::endl;
	}
}