#ifndef APHW3_H
#define APHW3_H

#include "NeuralNet.h"
#include "dataset.h"

Dataset loadFuncDataset(const char* filename);

// std::vector<Result> testNeuralNets(Dataset& dataset, std::vector<size_t>& hidden_neurons, double lr = 0.01, size_t max_iters = 10000, const char* af1 = "Sigmoid", const char* af2 = "Linear");

#endif