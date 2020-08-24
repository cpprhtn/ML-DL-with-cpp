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

