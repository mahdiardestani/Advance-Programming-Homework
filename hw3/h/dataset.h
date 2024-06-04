#ifndef DATASET_H
#define DATASET_H

#include "Matrix.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>

class Dataset {
public:
    Dataset(Matrix inputs, Matrix targets, double percentage = 70);
    Dataset();

    size_t getNoOfSamples() const;
    size_t getNoOfTrainSamples() const;
    size_t getNoOfTestSamples() const;
    size_t getInputDim() const;
    size_t getTargetDim() const;

    Matrix getInputs() const;
    Matrix getTargets() const;
    Matrix getTrainInputs() const;
    Matrix getTrainTargets() const;
    Matrix getTestInputs() const;
    Matrix getTestTargets() const;

    void shuffle();
    void show();

    // Matrix operator[](size_t index);
    Dataset operator+(const Dataset& dataset);

    friend std::ostream& operator<<(std::ostream& os, const Dataset& dataset)
    {
        os << "Data set:" << std::endl;
        os << dataset.getNoOfSamples() << "\n";
        os << dataset.getNoOfTrainSamples() << "\n";
        os << dataset.getNoOfTestSamples() << std::endl;
        os << dataset.getInputDim() << std::endl;
        os << dataset.getTargetDim() << std::endl;
        return os;
    }

private:
    Matrix inputs;
    Matrix targets;
    Matrix train_inputs;
    Matrix train_targets;
    Matrix test_inputs;
    Matrix test_targets;
    double percentage { 70 };
    size_t no_of_samples;
    size_t input_dim;
    size_t target_dim;
};

#endif