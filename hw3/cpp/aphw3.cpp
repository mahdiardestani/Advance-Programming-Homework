#include "aphw3.h"
#include "Matrix.h"
#include "dataset.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

Dataset loadFuncDataset(const char* filename)
{
    // std::cout << "Scope hw3 start" << std::endl;
    std::ifstream ifs(filename);
    if (ifs.is_open()) {

        std::out_of_range("Error: the file is open");
    }

    std::string line;
    std::vector<std::vector<double>> data_vec;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        // std::cout << line << std::endl;
        std::string word;
        std::vector<double> data;
        while (std::getline(ss, word, ',')) {
            // std::cout << word << std::endl;
            double tmp { std::stod(word) };
            data.push_back(tmp);
        }
        data_vec.push_back(data);
    }
    std::vector<std::vector<double>> target_vec;
    target_vec.push_back(data_vec.back());
    data_vec.pop_back();
    Matrix input_mat(data_vec);
    Matrix target_mat(target_vec);
    // std::cout << "-----Input Data-----" << std::endl;
    // input_mat.show();
    // std::cout << "-----Target Data-----" << std::endl;
    // target_mat.show();
    std::cout << "now call Construct Dataset" << std::endl;
    Dataset dataset(input_mat, target_mat);
    ifs.close();
    // std::cout << "Scope hw3 end" << std::endl;

    return dataset;
}

// std::vector<Result> testNeuralNets(Dataset& dataset, std::vector<size_t>& hidden_neurons,
//     double lr = 0.01, size_t max_iters = 10000,
//     const char* af1 = "Sigmoid", const char* af2 = "Linear")
// {
//     size_t numNN = hidden_neurons.size();
//     Dataset ds = dataset;
//     std::vector<NeuralNet> nnVec;
//     for (size_t i {}; i < numNN; i++) {
//         std::cout << hidden_neurons[i] << std::endl;
//         // NeuralNet nn(ds, hidden_neurons[i], lr, max_iters, af1, af2);
//         // nnVec.push_back(nn)
//     }
// }
