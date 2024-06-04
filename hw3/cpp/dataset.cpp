#include "dataset.h"

Dataset::Dataset(Matrix _inputs, Matrix _targets, double _percentage)
    : inputs { _inputs }
    , targets { _targets }
    , percentage { _percentage }
{
    // inputs = _inputs;
    // targets = _targets;
    // std::cout << "constructor dataset" << std::endl;
    size_t size { inputs.getSize()[1] };
    no_of_samples = size;
    input_dim = inputs.getSize()[0];
    target_dim = targets.getSize()[0];
    // std::cout << "number of sample: " << no_of_samples << std::endl;
    size_t numTrains = (no_of_samples * percentage) / 100.0;
    // std::cout << "number of trains: " << numTrains << std::endl;

    // Train Input
    // std::cout << "------make train input Matrix------" << std::endl;
    std::vector<double> train_tmp;
    for (size_t i {}; i < numTrains; i++) {
        // std::cout << i << ": " << inputs[0][i] << std::endl;
        train_tmp.push_back(inputs[0][i]);
    }
    std::vector<std::vector<double>> train_vec;
    train_vec.push_back(train_tmp);
    // Matrix a { train_vec };
    train_inputs = Matrix { train_vec };

    // Train Target
    // std::cout << "------make train target Matrix------" << std::endl;
    std::vector<double> trainTargets_tmp;
    for (size_t i {}; i < numTrains; i++) {
        trainTargets_tmp.push_back(targets[0][i]);
    }
    std::vector<std::vector<double>> trainTargets_vec;
    trainTargets_vec.push_back(trainTargets_tmp);
    // Matrix b { trainTargets_vec };
    train_targets = Matrix { trainTargets_vec };
    // train_targets.show();

    // Test Input
    // std::cout << "------make test input Matrix------" << std::endl;
    // size_t numTests { no_of_samples - numTrains };
    std::vector<double> test_tmp;
    for (size_t i { numTrains }; i < no_of_samples; i++) {
        // std::cout << i << ": " << inputs[0][i] << std::endl;
        test_tmp.push_back(inputs[0][i]);
    }
    std::vector<std::vector<double>> test_vec;
    test_vec.push_back(test_tmp);
    // Matrix c { test_vec };
    test_inputs = Matrix { test_vec };
    // test_inputs.show();

    // Test Targets
    // std::cout << "------make test target Matrix------" << std::endl;
    std::vector<double> testTargets_tmp;
    for (size_t i { numTrains }; i < no_of_samples; i++) {
        testTargets_tmp.push_back(targets[0][i]);
    }
    std::vector<std::vector<double>> testTargets_vec;
    testTargets_vec.push_back(testTargets_tmp);
    // Matrix d { testTargets_vec };
    test_targets = Matrix { testTargets_vec };
    // test_targets.show();

    // std::cout << "End of constructor Dataset" << std::endl;
}

Dataset::Dataset()
{
    std::cout << "Default Constructor dataset";
}

size_t Dataset::getNoOfSamples() const
{
    // std::cout << "Get Number of Samples: ";
    return no_of_samples;
}

size_t Dataset::getNoOfTrainSamples() const
{
    size_t size { 0 };
    size = (no_of_samples * percentage) / 100.0;
    // std::cout << "Get Number of Train Samples: ";
    return size;
}

size_t Dataset::getNoOfTestSamples() const
{
    size_t size { (no_of_samples - getNoOfTrainSamples()) };
    // std::cout << "Get Number of Test Samples: ";
    return size;
}

size_t Dataset::getInputDim() const
{
    // std::cout << "Get Input Dim: ";
    return input_dim;
}

size_t Dataset::getTargetDim() const
{
    // std::cout << "Get target dim: ";
    return target_dim;
}

Matrix Dataset::getInputs() const
{
    // std::cout << "Get Inputs: " << std::endl;
    return inputs;
}

Matrix Dataset::getTargets() const
{
    // std::cout << "Get Targets: " << std::endl;
    return targets;
}

Matrix Dataset::getTrainInputs() const
{

    // std::cout << "Get Train Inputs: " << std::endl;
    return train_inputs;
}

Matrix Dataset::getTrainTargets() const
{
    // std::cout << "Get Train Targets: " << std::endl;
    return train_targets;
}

Matrix Dataset::getTestInputs() const
{
    // std::cout << "Get Test Inputs: " << std::endl;
    return test_inputs;
}

Matrix Dataset::getTestTargets() const
{
    // std::cout << "Get Test Targets: " << std::endl;
    return test_targets;
}

void Dataset::shuffle()
{
    size_t numSamples { inputs.getSize()[1] };
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis1(0, numSamples - 1);
    // Inputs
    std::vector<double> shuffle_tmp;
    for (size_t i {}; i < numSamples; i++) {
        size_t index = (1 + dis1(gen)) % numSamples;
        // std::cout << index << " " << inputs[0][index] << std::endl;
        shuffle_tmp.push_back(inputs[0][index]);
    }
    std::vector<std::vector<double>> input_vec;
    input_vec.push_back(shuffle_tmp);
    // Matrix a(input_vec);
    inputs = Matrix(input_vec);

    // Targets
    std::vector<double> targets_tmp;
    for (size_t i {}; i < numSamples; i++) {
        size_t index = (1 + dis1(gen)) % numSamples;
        // std::cout << index << " ";
        targets_tmp.push_back(targets[0][index]);
        // std::cout << i << ":" << train_inputs[0][i] << std::endl;
    }
    std::vector<std::vector<double>> targets_vec;
    targets_vec.push_back(targets_tmp);
    targets = Matrix(targets_vec);

    // Train inputs
    size_t numTrains = (numSamples * percentage) / 100.0;
    std::uniform_int_distribution<int> dis2(0, numTrains - 1);
    std::vector<double> trainInputs_tmp;
    for (size_t i {}; i < numTrains; i++) {
        size_t index = (1 + dis2(gen)) % numTrains;
        // std::cout << index << " ";
        trainInputs_tmp.push_back(train_inputs[0][index]);
        // std::cout << i << ":" << train_inputs[0][i] << std::endl;
    }
    std::vector<std::vector<double>> trainInputs_vec;
    trainInputs_vec.push_back(trainInputs_tmp);
    train_inputs = Matrix(trainInputs_vec);

    // Train Targets
    std::vector<double> trainTargets_tmp;
    for (size_t i {}; i < numTrains; i++) {
        size_t index = (1 + dis2(gen)) % numTrains;
        // std::cout << index << " ";
        trainTargets_tmp.push_back(train_targets[0][index]);
        // std::cout << i << ":" << train_inputs[0][i] << std::endl;
    }
    std::vector<std::vector<double>> trainTargets_vec;
    trainTargets_vec.push_back(trainTargets_tmp);
    train_targets = Matrix(trainTargets_vec);

    // Test Inputs
    std::vector<double> testInputs_tmp;
    size_t numTests { no_of_samples - numTrains };
    std::uniform_int_distribution<int> dis3(0, numTests - 1);
    for (size_t i { numTrains }; i < no_of_samples; i++) {
        size_t index = (1 + dis3(gen)) % numTests;
        testInputs_tmp.push_back(test_inputs[0][index]);
        // std::cout << i << ":" << train_inputs[0][i] << std::endl;
    }
    std::vector<std::vector<double>> testInputs_vec;
    testInputs_vec.push_back(testInputs_tmp);
    test_inputs = Matrix(testInputs_vec);

    // Test Targets
    std::vector<double> testTargets_tmp;
    for (size_t i { numTrains }; i < no_of_samples; i++) {
        size_t index = (1 + dis3(gen)) % numTests;
        testTargets_tmp.push_back(test_targets[0][index]);
        // std::cout << i << ":" << train_inputs[0][i] << std::endl;
    }
    std::vector<std::vector<double>> testTargets_vec;
    testTargets_vec.push_back(testTargets_tmp);
    test_targets = Matrix(testTargets_vec);
    // std::cout << "End of the shuffle function" << std::endl;
}

void Dataset::show()
{
    size_t align { 23 };
    std::cout << "DataSet Show Function " << std::endl;
    std::cout << "Dataset: " << std::endl
              << std::right
              << std::setw(align) << "No of samples: " << no_of_samples << std::endl
              << std::setw(align) << "Train samples: " << getNoOfTrainSamples() << " Samples" << std::endl
              << std::setw(align - 1) << "Test samples: " << getNoOfTestSamples() << " Samples" << std::endl
              << std::setw(align + 3) << "Input dimensions: " << getInputDim() << std::endl
              << std::setw(align + 4) << "Target dimensions: " << getTargetDim() << std::endl;
}

// Matrix Dataset::operator[](size_t index)
// {
// ?????????????????????
//     return Matrix::col_mat(index);
// }

Dataset Dataset::operator+(const Dataset& dataset)
{
    std::cout << "dataset operator +" << std::endl;
    // size_t dim = getInputDim();
    // std::cout << dim << "\n";
    // std::cout << no_of_samples << "\n";
    std::vector<double> tmp_inputs;
    std::vector<double> tmp_targets;

    for (size_t i {}; i < no_of_samples; i++) {
        tmp_inputs.push_back(inputs[0][i]);
        tmp_targets.push_back(targets[0][i]);
    }
    std::vector<std::vector<double>> inputNew_vec;
    inputNew_vec.push_back(tmp_inputs);
    std::vector<std::vector<double>> targetNew_vec;
    targetNew_vec.push_back(tmp_targets);

    size_t numd2 = dataset.getNoOfSamples();
    // size_t dimd2 = dataset.getInputDim();
    // std::cout << dimd2 << "\n";
    // std::cout << numd2 << "\n";
    std::vector<double> tmp2_inputs;
    std::vector<double> tmp2_targets;

    for (size_t i {}; i < numd2; i++) {
        tmp2_inputs.push_back(dataset.inputs[0][i]);
        tmp2_targets.push_back(dataset.targets[0][i]);
    }
    inputNew_vec.push_back(tmp2_inputs);
    targetNew_vec.push_back(tmp2_targets);

    Matrix a(inputNew_vec);
    inputs = a;
    Matrix b(targetNew_vec);
    targets = b;
    no_of_samples = no_of_samples + numd2;
    // std::cout << no_of_samples << "endd";
    return *this;
}