#include <iostream>
#include <cmath>
#include <map>
#include <random>
#include <vector>

double Sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}

class Neuron
{
public:
    Neuron(std::size_t input_size)
    {
        W_.resize(input_size);
        Reset();
    }

public:
    double Calc(const std::vector<double>& x) const
    {
        if (x.size() != W_.size())
            throw "x.size() != W_.size()";

        double Wx = 0.0;
        for (std::size_t i = 0; i < W_.size(); ++i)
        {
            Wx += W_[i] * x[i];
        }

        return Sigmoid(Wx + b_);
    }
    void Train(double a, const std::vector<std::pair<std::vector<double>, double>>& t_data)
    {
        std::size_t input_size = t_data[0].first.size();
        if (input_size != W_.size())
            throw "input_size != W_.size()";

        for (std::size_t i = 0; i < t_data.size(); ++i)
        {
            double o = Calc(t_data[i].first);
            double t = t_data[i].second;

            for (std::size_t j = 0; j < input_size; ++j)
            {
                W_[j] += a * (t - o) * t_data[i].first[j];
            }
            b_ += a * (t - o);
        }
    }

private:
    void Reset()
    {
        b_ = -1;

        std::mt19937 random((std::random_device()()));
        std::uniform_real_distribution<double> dist(-1, 1);

        for (std::size_t i = 0; i < W_.size(); ++i)
        {
            W_[i] = dist(random);
        }
    }

private:
    std::vector<double> W_;
    double b_;
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

    std::cout << "And Operator" << std::endl;
	std::cout << "0 and 0 = " << and_neuron.Calc({ 0, 0 }) << std::endl;
	std::cout << "1 and 0 = " << and_neuron.Calc({ 1, 0 }) << std::endl;
	std::cout << "0 and 1 = " << and_neuron.Calc({ 0, 1 }) << std::endl;
	std::cout << "1 and 1 = " << and_neuron.Calc({ 1, 1 }) << std::endl;
    std::cout << std::endl;



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

    std::cout << "Or Operator" << std::endl;
	std::cout << "0 or 0 = " << or_neuron.Calc({ 0, 0 }) << std::endl;
	std::cout << "1 or 0 = " << or_neuron.Calc({ 1, 0 }) << std::endl;
	std::cout << "0 or 1 = " << or_neuron.Calc({ 0, 1 }) << std::endl;
	std::cout << "1 or 1 = " << or_neuron.Calc({ 1, 1 }) << std::endl;

	return 0;
}