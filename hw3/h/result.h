#ifndef RESULT_H
#define RESULT_H

#include <compare>
#include <iomanip>
#include <iostream>

class Result {
public:
    Result(double train_loss, double test_loss, size_t no_of_hidden_neurons,
        double lr = 0.01, size_t iters = 10, const char* af1 = "Sigmoid", const char* af2 = "Sigmoid");
    explicit Result(double test_loss);
    double getTestLoss();
    void show();

    std::partial_ordering operator<=>(const Result& r);

    friend std::ostream& operator<<(std::ostream& os, const Result& r)
    {
        std::cout << "Result class ostream<<: " << std::endl;
        size_t align { 10 };
        os << "Result: " << std::endl
           << std::right
           << std::setw(align + 5) << "Train Loss: " << r.train_loss << std::endl
           << std::setw(align + 4) << "Test Loss: " << r.test_loss << std::endl
           << std::setw(align + 15) << "No of hidden neurons: " << r.no_of_hidden_neurons << std::endl
           << std::setw(align + 22) << "Layer 1 activation function: " << r.af1 << std::endl
           << std::setw(align + 22) << "Layer 2 activation function: " << r.af2 << std::endl;
    }

private:
    double train_loss;
    double test_loss;
    size_t no_of_hidden_neurons;
    double lr {};
    size_t iters {};
    const char* af1;
    const char* af2 {};
};

#endif