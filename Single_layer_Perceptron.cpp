#include <cmath>
#include <map>
#include <random>
#include <vector>
#include <iostream>
double Sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}

class Neuron
{
public:
    Neuron(std::size_t input_size)
    {
        Weights_.resize(input_size);
        Reset();
    }

public:
    double Compute(const std::vector<double>& x) const
    {
        if (x.size() != Weights_.size())
            throw "x.size() != Weights_.size()";

        double wx = 0.0;
        for (std::size_t i = 0; i < Weights_.size(); ++i)
        {
            wx += Weights_[i] * x[i];
        }

        return Sigmoid(wx + Bias_);
    }
    void Train(double a, const std::vector<std::pair<std::vector<double>, double>>& train_data)
    {
        std::size_t input_size = train_data[0].first.size();
        if (input_size != Weights_.size())
            throw "input_size != Weights_.size()";

        for (std::size_t i = 0; i < train_data.size(); ++i)
        {
            double o = Compute(train_data[i].first);
            double t = train_data[i].second;

            for (std::size_t j = 0; j < input_size; ++j)
            {
                Weights_[j] += a * (t - o) * train_data[i].first[j];
            }
            Bias_ += a * (t - o);
        }
    }

private:
    void Reset()
    {
        Bias_ = -1;

        std::mt19937 random((std::random_device()()));
        std::uniform_real_distribution<double> dist(-1, 1);

        for (std::size_t i = 0; i < Weights_.size(); ++i)
        {
            Weights_[i] = dist(random);
        }
    }

private:
    std::vector<double> Weights_;
    double Bias_;
};

int main()
{
	Neuron and_neuron(2);

	for (int i = 0; i < 100000; ++i)
	{
		and_neuron.Train(0.1,
		{
			{ { 0, 0 }, 0 },
			{ { 1, 0 }, 0 },
			{ { 0, 1 }, 0 },
			{ { 1, 1 }, 1 },
		});
	}

	std::cout << "0 and 0 = " << and_neuron.Compute({ 0, 0 }) << '\n';
	std::cout << "1 and 0 = " << and_neuron.Compute({ 1, 0 }) << '\n';
	std::cout << "0 and 1 = " << and_neuron.Compute({ 0, 1 }) << '\n';
	std::cout << "1 and 1 = " << and_neuron.Compute({ 1, 1 }) << '\n';

	Neuron or_neuron(2);

	for (int i = 0; i < 100000; ++i)
	{
		or_neuron.Train(0.1,
		{
			{ { 0, 0 }, 0 },
			{ { 1, 0 }, 1 },
			{ { 0, 1 }, 1 },
			{ { 1, 1 }, 1 },
		});
	}

	std::cout << "0 or 0 = " << or_neuron.Compute({ 0, 0 }) << '\n';
	std::cout << "1 or 0 = " << or_neuron.Compute({ 1, 0 }) << '\n';
	std::cout << "0 or 1 = " << or_neuron.Compute({ 0, 1 }) << '\n';
	std::cout << "1 or 1 = " << or_neuron.Compute({ 1, 1 }) << '\n';

	return 0;
}