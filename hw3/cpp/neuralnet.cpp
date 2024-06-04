#include "neuralnet.h"

NeuralNet::NeuralNet(Dataset _dataset, size_t hln,
    const char* f1, const char* f2,
    double _lr, size_t _max_iters, double _min_loss)
    : dataset { _dataset }
    , hidden_layer_neurons { hln }
    , af1 { f1 }
    , af2 { f2 }
    , lr { _lr }
    , max_iters { _max_iters }
    , min_loss { _min_loss }
{
    std::cout << "Neural Net constructor: " << std::endl;
    std::cout << "af2 is----" << af2 << std::endl;
}

Matrix NeuralNet::forwardPropagate(Matrix& input)
{
    std::cout << "Neural Net Forward Propagate:" << std::endl;
    size_t num_neron_l1 = input.getSize()[1];
    size_t num_neron_wl1 = 2;

    // -------- Layer 1 -------//
    // Matrix W1
    // for (size_t i {}; i < num_neron_l1; i++) {
    //     for (size_t j {}; j < num_neron_wl1; j++) {
    //         w1[i][j] = 1;
    //     }
    // }
    // std::cout << "----w1----" << std::endl;
    // w1.show();

    // // Matrix b1
    // for (size_t i {}; i < num_neron_wl1; i++) {
    //     b1[i][0] = 1;
    // }

    // std::cout << "----b1----" << std::endl;
    // b1.show();

    //n1
    n1 = w1 * input + b1;
    // std::cout << "----n1----" << std::endl;
    // n1.show();

    //a1
    size_t n1_size = n1.getSize()[0];
    // std::cout << n1_size << std::endl;
    std::vector<double> f1_tmp;
    std::vector<std::vector<double>> f1_vec;
    if (strcmp(af1, "Sigmoid") == 0) {
        std::cout << "af1 is Sigmoid" << std::endl;
        for (size_t i {}; i < n1_size; i++) {
            double f1 = 1.0 / (1.0 + exp(-n1[i][0]));
            f1_tmp.push_back(f1);
        }
        f1_vec.push_back(f1_tmp);
    } else if (strcmp(af1, "Linear") == 0) {
        std::cout << "af1 is Linear" << std::endl;
        for (size_t i {}; i < n1_size; i++) {
            double f1 = n1[i][0];
            f1_tmp.push_back(f1);
        }
        f1_vec.push_back(f1_tmp);
    }
    Matrix a1_tmp { f1_vec };
    a1 = a1_tmp.T();
    // std::cout << "a1 matrix of layer1: " << std::endl;
    // a1.show();

    // -------- Layer 2 -------//

    // Matrix W2
    // size_t num_neron_l2 = a1.getSize()[0]; // rows
    // size_t num_neron_wl2 = 1;
    // Matrix _w2 { 2, 1 };
    // for (size_t i {}; i < num_neron_l2; i++) {
    //     for (size_t j {}; j < num_neron_wl2; j++) {
    //         _w2[i][j] = 1;
    //     }
    // }
    // std::cout << "----w2----" << std::endl;
    // w2.show();

    // std::cout << "check:" << num_neron_l2 << std::endl;
    // std::cout << "w2 show" << std::endl;
    // w2 = _w2.T();
    // w2.show();

    // Matrix b2
    // for (size_t i {}; i < num_neron_wl2; i++) {
    //     b2[i][0] = 1;
    // }
    // std::cout << "----b2----" << std::endl;
    // b2.show();

    //n2
    n2 = w2 * a1 + b2;
    // std::cout << "----n2----" << std::endl;
    // n2.show();

    //a2
    size_t n2_size = n2.getSize()[0];
    // std::cout << n2_size << std::endl;
    std::vector<double> f2_tmp;
    std::vector<std::vector<double>> f2_vec;
    if (strcmp(af2, "Sigmoid") == 0) {
        std::cout << "af2 is Sigmoid" << std::endl;
        for (size_t i {}; i < n2_size; i++) {
            double f2 = 1.0 / (1.0 + exp(-n2[i][0]));
            f2_tmp.push_back(f2);
        }
        f2_vec.push_back(f2_tmp);
    } else if (strcmp(af2, "Linear") == 0) {
        std::cout << "af2 is Linear" << std::endl;
        for (size_t i {}; i < n2_size; i++) {
            double f2 = n2[i][0];
            f2_tmp.push_back(f2);
        }
        f2_vec.push_back(f2_tmp);
    }
    Matrix a2 { f2_vec };
    // std::cout << "a2 matrix of layer2: " << std::endl;
    // a2.show();
    return a2;
}

void NeuralNet::backPropagate(Matrix& input, Matrix& target)
{
    std::cout << "NeuralNet backpropagate" << std::endl;

    // output to the hidden -> s2
    double _target = target[0][0];
    double guess = a2[0][0];
    double e_out = (_target - guess);
    double fdot { 0 };
    if (strcmp(af2, "Sigmoid") == 0) {
        std::cout << "af2 is " << af2 << std::endl;
        double fx = 1.0 / (1.0 + exp(-guess));
        fdot = fx * (1.0 - fx);
    } else if (strcmp(af2, "Linear") == 0) {
        std::cout << "af2 is " << af2 << std::endl;
        fdot = 1.0;
    }
    Matrix _s2 { 1, 1 };
    _s2[0][0] = -2.0 * fdot * e_out;
    s2 = _s2;
    // std::cout << "Matrix s2: " << std::endl;
    // s2.show();
    // s1
    if (strcmp(af1, "Sigmoid") == 0) {
        std::cout << "af1 is " << af1 << std::endl;
        double fdot_n1 = a1[0][0] * (1.0 - a1[0][0]);
        double fdot_n2 = a1[1][0] * (1.0 - a1[1][0]);
        Matrix fdot_n1_mat { 2, 2 };
        fdot_n1_mat[0][0] = fdot_n1;
        fdot_n1_mat[0][1] = 0.0;
        fdot_n1_mat[1][0] = 0.0;
        fdot_n1_mat[1][1] = fdot_n2;
        // std::cout << "fdot: " << std::endl;
        // fdot_n1_mat.show();
        s1 = fdot_n1_mat * w2.T() * s2;
        // std::cout << "Matrix s1: " << std::endl;
        // s1.show();
    } else if (strcmp(af1, "Linear") == 0) {
        std::cout << "af1 is " << af1 << std::endl;
        double fdot_n1 = 1.0;
        double fdot_n2 = 1.0;
        Matrix fdot_n1_mat { 2, 2 };
        fdot_n1_mat[0][0] = fdot_n1;
        fdot_n1_mat[0][1] = 0.0;
        fdot_n1_mat[1][0] = 0.0;
        fdot_n1_mat[1][1] = fdot_n2;
        // std::cout << "fdot: " << std::endl;
        // fdot_n1_mat.show();
        s1 = fdot_n1_mat * w2.T() * s2;
        // std::cout << "Matrix s1: " << std::endl;
        // s1.show();
    }

    // Update weigth and biases
    //w2
    w2[0][0] = w2[0][0] - lr * s2[0][0] * a1[0][0];
    w2[0][1] = w2[0][1] - lr * s2[0][0] * a1[1][0];
    // std::cout << "w2 updated:" << std::endl;
    // w2.show();
    //b2
    b2[0][0] = b2[0][0] - lr * s2[0][0];
    // std::cout << "b2 updated:" << std::endl;
    // b2.show();

    //w1
    w1[0][0] = w1[0][0] - lr * s1[0][0] * input[0][0];
    w1[1][0] = w1[1][0] - lr * s1[1][0] * input[0][0];
    // std::cout << "w1 updated:" << std::endl;
    // w1.show();

    //b1
    b1[0][0] = b1[0][0] - lr * s1[0][0];
    b1[1][0] = b1[1][0] - lr * s1[1][0];
    // std::cout << "b1 updated:" << std::endl;
    // b1.show();
}

Result NeuralNet::fit()
{
    std::cout << "Fit function" << std::endl;
    double _train_loss { 0 };
    double _test_loss { 0 };
    double _no_of_hidden_neurons { 2 };
    double _max_iters { 10000 };
    const char* _af1 = "Sigmoid";
    const char* _af2 = "Sigmoid";
    af1 = _af1;
    af2 = _af2;
    // Train
    Matrix inputs_train = dataset.getTrainInputs();
    Matrix target_train = dataset.getTrainTargets();
    for (size_t iter {}; iter < _max_iters; iter++) {
        std::cout << "------------ Train iteraion " << iter + 1 << "------------------" << std::endl;
        for (size_t i {}; i < dataset.getNoOfTrainSamples(); i++) {
            Matrix input_tmp { 1, 1 };
            Matrix target_tmp { 1, 1 };
            input_tmp[0][0] = inputs_train[0][i];
            target_tmp[0][0] = target_train[0][i];
            forwardPropagate(input_tmp);
            _train_loss = target_tmp[0][0] - a2[0][0];
            backPropagate(a2, target_tmp);
            std::cout << "train loss:" << _train_loss << std::endl;
        }
    }

    //Test
    Matrix inputs_test = dataset.getTestInputs();
    Matrix target_test = dataset.getTestTargets();
    for (size_t i {}; i < dataset.getNoOfTestSamples(); i++) {
        std::cout << "------------IN Test iteraion " << i + 1 << "------------------" << std::endl;
        Matrix input_tmp { 1, 1 };
        Matrix target_tmp { 1, 1 };
        input_tmp[0][0] = inputs_test[0][i];
        target_tmp[0][0] = target_test[0][i];
        Matrix test_a { 1, 1 };
        test_a = forwardPropagate(input_tmp);
        // backPropagate(a2, target_tmp);
        _test_loss = target_tmp[0][0] - test_a[0][0];
        if (_test_loss < min_loss) {
            std::cout << "Reach the minimum loss in test:" << std::endl;
            std::cout << " This is the minimum loss: " << _test_loss << std::endl;
            break;
        }
        std::cout << "test loss:" << _test_loss << std::endl;
    }

    Result r { _train_loss, _test_loss, _no_of_hidden_neurons, lr, _max_iters, _af1, _af2 };
    std::cout << "End of fit function" << std::endl;
    // std::cout << "w1" << std::endl;
    // w1.show();

    // std::cout << "w2" << std::endl;
    // w2.show();

    // std::cout << "b1" << std::endl;
    // b1.show();

    // std::cout << "b2" << std::endl;
    // b2.show();
    return r;
}

double NeuralNet::trainLoss()
{
    std::cout << "NeuralNet class trainLoss_ fault" << std::endl;
    double totalErr { 0 };
    size_t noNerons2 { n2.getSize()[0] };

    // for (size_t i {}; i < noNerons2; i++) {
    //     totalErr += a2[0][i] - dataset.getTargets()[0][i];
    // }
    return totalErr;
}

double NeuralNet::testLoss()
{
    std::cout << "NeuralNet class testLoss_fault" << std::endl;
    double totalErr { 0 };
    size_t noNerons2 { n2.getSize()[0] };
    // for (size_t i {}; i < noNerons2; i++) {
    //     totalErr += a2[0][i] - dataset.getTargets()[0][i];
    // }
    return totalErr;
}

void NeuralNet::setW1(Matrix& w)
{
    std::cout << "Neural Net set W1" << std::endl;
    w1 = w;
}

void NeuralNet::setW2(Matrix& w)
{
    std::cout << "Neural Net set W2" << std::endl;
    w2 = w;
}

void NeuralNet::setB1(Matrix& b)
{
    std::cout << "Neural Net set B1" << std::endl;
    b1 = b;
}

void NeuralNet::setB2(Matrix& b)
{
    std::cout << "Neural Net set B2" << std::endl;
    b2 = b;
}

Matrix NeuralNet::getW1()
{
    std::cout << "Neural Net get W1" << std::endl;
    return w1;
}

Matrix NeuralNet::getW2()
{
    std::cout << "Neural Net get W2" << std::endl;
    return w2;
}

Matrix NeuralNet::getB1()
{
    std::cout << "Neural Net get b1" << std::endl;
    return b1;
}

Matrix NeuralNet::getB2()
{
    std::cout << "Neural Net get b2" << std::endl;
    return b2;
}

void NeuralNet::show()
{
    std::cout << "Neural Net show Function" << std::endl;
    size_t align { 23 };
    std::cout << "Neural Network: " << std::endl
              << std::right
              << std::setw(align + 5) << "No of hidden neurons: " << hidden_layer_neurons << std::endl
              << std::setw(align) << "Input dimension: " << dataset.getInputDim() << std::endl
              << std::setw(align + 1) << "Output dimension: " << dataset.getInputDim() << std::endl
              << std::setw(align + 12) << "Layer 1 activation function: " << af1 << std::endl
              << std::setw(align + 12) << "Layer 2 activation function: " << af2 << std::endl;
}