#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include "Matrix.h"
#include "dataset.h"
#include "result.h"
#include <cmath>
#include <string.h>

class NeuralNet {
public:
    NeuralNet(Dataset dataset, size_t hidden_layer_neurons, const char* f1 = "Sigmoid", const char* f2 = "Linear", double lr = 0.01, size_t max_iters = 10000, double min_loss = 0.01);
    Matrix forwardPropagate(Matrix& input);
    void backPropagate(Matrix& input, Matrix& target);
    double trainLoss();
    double testLoss();
    void setW1(Matrix& w);
    void setW2(Matrix& w);
    void setB1(Matrix& b);
    void setB2(Matrix& b);
    Matrix getW1();
    Matrix getW2();
    Matrix getB1();
    Matrix getB2();
    Result fit();
    void show();

    friend std::ostream& operator<<(std::ostream& os, const NeuralNet& nn)
    {
        size_t align { 23 };
        os << "Neural Network ostream<<: " << std::endl;
        os << std::setw(align + 5) << "No of hidden neurons: " << nn.hidden_layer_neurons << std::endl;
        os << std::setw(align + 1) << "Output dimension: " << nn.dataset.getInputDim() << std::endl;
        os << std::setw(align + 1) << "Output dimension: " << nn.dataset.getInputDim() << std::endl;
        os << std::setw(align + 12) << "Layer 1 activation function: " << nn.af1 << std::endl;
        os << std::setw(align + 12) << "Layer 2 activation function: " << nn.af2 << std::endl;
        return os;
    }

private:
    Dataset dataset;
    size_t hidden_layer_neurons { 3 };
    const char* af1 { "Sigmoid" };
    const char* af2 { "Linear" };
    double lr { 0.01 };
    size_t max_iters { 10000 };
    double min_loss { 0.01 };
    Matrix w1; // weights of layer 1
    Matrix w2; // weights of layer 2
    Matrix b1; // Biases of layer 1
    Matrix b2; // Biases of layer 2
    Matrix a1; // Output of layer 1
    Matrix a2; // Output of layer 2
    Matrix n1; // n vector for layer 1
    Matrix n2; // n vector for layer 2
    Matrix s1; // s vector for layer 1
    Matrix s2; // s vector for layer 2
};

#endif