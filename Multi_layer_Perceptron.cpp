#include <iostream>
#include <cmath>
#include <random>
#include <vector>

double Sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}

class Neuron
{
public:
    Neuron(std::size_t input size)
    {
        W_.resize(input_size);
        Reset();
    }

    double Compute(const std::vector<double>& x) const //입력시 출력형태로
    {
        if (x.size() != W_.size()) // 예외처리
            throw "x.size() != W_.size()";


        double Wx = 0.0;
        for (std::size_t i = 0; i < W_.size(); i++)
        {
             Wx += W_[i] * x[i];
        }

        return Sigmoid(Wx + b_); //h(x) 구현
    }
    //a (W, b 다 적용한.)
    void Train(double a, const::vector<std::pair<std::vector<double>, double>>& t_data)
    {
         std::size_t input_size = t_data[o].first.size();

        if(input_size != W_.size())
            throw "input_size.size() != W_.size()";

        for(std::size_t i = 0; i < t_data.size(); ++i)
        {
            double o = Compute(t_data[i].first);
            double t = t_data[i].second;


            for(std::size_t j = 0; j < input_size; ++j)
            {
                W_[j] += a * (t - o) * t_data[i].first[j];
            }

        b_ += a * (t - o)
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

//Network 구현

class Network
{
public:
    Network(const std::vector<std::size_t>& layers)
    {
        for (std::size_t i = 1; i < layers.size(); ++i)
        {
            std::vector<Neuron> layer;
            for (std::size_t j = 0; j <layers[i]; j++)
            {
                layer.push_back(Neuron(layers[i - 1]));
            }
            Layers_.push_back(layer);
        }
    }

public:
    std::vector<double> Compute(const std::vector<double>& x)
    {
        if (x.size() != Layers_[0][0].Inputsize())
            throw "x.size() != Layers_[0][0].Inputsize()"

        std::vector<double> result;
        std::vector<double> x_next_layer = x;

    
    }

private:
    std::vector<std::vector<Neuron>> Layers_;
};

//Network net({a,b,c,d});