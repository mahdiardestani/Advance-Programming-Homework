#include <result.h>

Result::Result(double _train_loss, double _test_loss, size_t _no_of_hidden_neurons,
    double _lr, size_t _iters, const char* _af1, const char* _af2)
    : train_loss { _train_loss }
    , test_loss { _test_loss }
    , no_of_hidden_neurons { _no_of_hidden_neurons }
    , lr { _lr }
    , iters { _iters }
    , af1 { _af1 }
    , af2 { _af2 }
{
    std::cout << "class Result constructor" << std::endl;
}

Result::Result(double _test_loss)
    : Result(-1, _test_loss, 0, lr, iters, af1, af2)
{
    std::cout << "class Result specefic constructor" << std::endl;
    train_loss = -1;
    no_of_hidden_neurons = 0;
}

double Result::getTestLoss()
{
    std::cout << "Result class Get Test Loss: " << test_loss << std::endl;
    return test_loss;
}

std::partial_ordering Result::operator<=>(const Result& r)
{
    std::cout << "Result comparision operator" << std::endl;
    return test_loss <=> r.test_loss;
}

void Result::show()
{
    std::cout << "Result class show" << std::endl;
    size_t align { 10 };
    std::cout << "Result: " << std::endl
              << std::right
              << std::setw(align + 5) << "Train Loss: " << train_loss << std::endl
              << std::setw(align + 4) << "Test Loss: " << test_loss << std::endl
              << std::setw(align + 15) << "No of hidden neurons: " << no_of_hidden_neurons << std::endl
              << std::setw(align + 22) << "Layer 1 activation function: " << af1 << std::endl
              << std::setw(align + 22) << "Layer 2 activation function: " << af2 << std::endl;
}