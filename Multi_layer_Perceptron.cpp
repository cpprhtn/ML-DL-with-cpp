#include <iostream>
#include <cmath>
#include <random>
#include <vector>

double Sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}
double D_Sigmoid(double x)
{
    double y = Sigmoid(x);
    return y * (1 - y);
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

        LastV_ = Wx + b_;
        LastX_ = x;
        return Sigmoid(LastV_);
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
                W_[j] += a * D_Sigmoid
            (LastV_) * (t - o) * t_data[i].first[j];
            }
            b_ += a * D_Sigmoid
        (LastV_) * (t - o);

            LastD_ = D_Sigmoid
        (LastV_) * (t - o);
        }
    }
    void Train(double a, double e, const std::vector<double>& t_data)
    {
        std::size_t input_size = t_data.size();
        if (input_size != W_.size())
            throw "input_size != W_.size()";

        for (std::size_t j = 0; j < input_size; ++j)
        {
            W_[j] += a * D_Sigmoid
        (LastV_) * e * t_data[j];
        }
        b_ += a * D_Sigmoid
    (LastV_) * e;

        LastD_ = D_Sigmoid
    (LastV_) * e;
    }
    std::size_t InputSize() const
    {
        return W_.size();
    }
    double LastV() const
    {
        return LastV_;
    }
    double LastD() const
    {
        return LastD_;
    }
    std::vector<double>& Weights()
    {
        return W_;
    }
    double& Bias()
    {
        return b_;
    }
    const std::vector<double>& LastX() const
    {
        return LastX_;
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
    mutable double LastV_;
    double LastD_;
    mutable std::vector<double> LastX_;
};

class Network
{
public:
    Network(const std::vector<std::size_t>& layers)
    {
        for (std::size_t i = 1; i < layers.size(); ++i)
        {
            std::vector<Neuron> layer;
            for (std::size_t j = 0; j < layers[i]; ++j)
            {
                layer.push_back(Neuron(layers[i - 1]));
            }
            Layers_.push_back(layer);
        }
    }

public:
    std::vector<double> Calc(const std::vector<double>& x)
    {
        if (x.size() != Layers_[0][0].InputSize())
            throw "x.size() != Layers_[0][0].InputSize()";

        std::vector<double> result;
        std::vector<double> x_next_layer = x;

        for (std::size_t i = 0; i < Layers_.size(); ++i)
        {
            result.clear();
            for (std::size_t j = 0; j < Layers_[i].size(); ++j)
            {
                result.push_back(Layers_[i][j].Calc(x_next_layer));
            }
            x_next_layer = result;
        }

        return result;
    }
    void Train(double a, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& t_data)
    {
        for (std::size_t i = 0; i < t_data.size(); ++i)
        {
            // 출력 레이어 학습
            std::vector<double> o = Calc(t_data[i].first);
            std::vector<double> e;

            if (o.size() != t_data[i].second.size())
                throw "o.size() != t_data[i].second.size()";

            for (std::size_t j = 0; j < o.size(); ++j)
            {
                e.push_back(t_data[i].second[j] - o[j]);
            }

            std::vector<double> d;
            for (std::size_t j = 0; j < Layers_[Layers_.size() - 1].size(); ++j)
            {
                Layers_[Layers_.size() - 1][j].Train(a, e[j], Layers_[Layers_.size() - 1][j].LastX());
                d.push_back(Layers_[Layers_.size() - 1][j].LastD());
            }

            if (Layers_.size() == 1)
                continue;

            //Train hidden layers
            for (std::size_t j = Layers_.size() - 2; j >= 0; --j)
            {
                std::vector<double> new_d;

                for (std::size_t k = 0; k < Layers_[j].size(); ++k)
                {
                    std::vector<double> linked_w;
                    for (std::size_t n = 0; n < Layers_[j + 1].size(); ++n)
                    {
                        linked_w.push_back(Layers_[j + 1][n].Weights()[k]);
                    }

                    if (linked_w.size() != d.size())
                        throw "linked_w.size() != d.size()";

                    double e_hidden = 0.0;
                    for (std::size_t n = 0; n < linked_w.size(); ++n)
                    {
                        e_hidden += linked_w[n] * d[n];
                    }

                    Layers_[j][k].Train(a, e_hidden, Layers_[j][k].LastX());
                    new_d.push_back(Layers_[j][k].LastD());
                }

                if (j == 0)
                {
                    break;
                }

                d = new_d;
            }
        }
    }

private:
    std::vector<std::vector<Neuron>> Layers_;
};

int main()
{
	Network net({ 2, 4, 1 });

	for (int i = 0; i < 100000; ++i)
	{
		net.Train(0.2,
		{
			{ { 0, 0 }, { 0 } },
			{ { 1, 0 }, { 1 } },
			{ { 0, 1 }, { 1 } },
			{ { 1, 1 }, { 0 } },
		});
	}

    std::cout << "XOR Operator" << std::endl;
	std::cout << "0 xor 0 = " << net.Calc({ 0, 0 })[0] << '\n';
	std::cout << "1 xor 0 = " << net.Calc({ 1, 0 })[0] << '\n';
	std::cout << "0 xor 1 = " << net.Calc({ 0, 1 })[0] << '\n';
	std::cout << "1 xor 1 = " << net.Calc({ 1, 1 })[0] << '\n';

	return 0;
}