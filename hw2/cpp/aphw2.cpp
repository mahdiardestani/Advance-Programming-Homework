#include "aphw2.h"

std::optional<double> det(Matrix& m)
{
    std::optional<double> det;
    std::array<size_t, 2> size;
    size = m.getSize();
    if (size[0] == size[1]) {
        det = m.det();
        return det.value();
    } else {
        std::cout << "The Matrix is not squere" << std::endl;
        return std::nullopt;
    }
}

std::optional<Matrix> transpose(Matrix& m)
{
    std::optional<Matrix> m1;
    m1 = m.T();
    return m1.value();
}

std::vector<std::vector<double>> getData(const char* file_name, bool add_bias)
{
    std::ifstream ifs;
    ifs.open(file_name);
    std::string line;
    std::vector<std::vector<double>> vec2_num;
    if (ifs.is_open()) {
        while (std::getline(ifs, line, '\n')) {
            std::stringstream s(line);
            std::string word;
            std::vector<double> vec_num;
            while (std::getline(s, word, ',')) {
                vec_num.push_back(std::stod(word));
            }
            if (add_bias) {
                vec_num.insert(vec_num.begin(), 1);
            }
            vec2_num.push_back(vec_num);
        }
    }
    ifs.close();
    return vec2_num;
}

Matrix findWeights(const char* file_name)
{
    std::cout << "Find Weights" << std::endl;
    std::vector<std::vector<double>> mydata;
    mydata = getData(file_name);
    // for (size_t j {}; j < mydata.size(); j++) {
    //     std::cout << mydata[j][7] << std::endl;
    //     // mydata[3][j] = (mydata[3][j] / 100.0);
    //     // mydata[4][j] = (mydata[4][j] / 100.0);
    //     // std::cout << mydata[3][j] << " " << mydata[4][j] << std::endl;
    // }

    Matrix X(mydata);
    Matrix Y;
    // Matrix W;
    // std::array<size_t, 2> size;
    Y = X.col_mat(7);
    // for (size_t i {}; i < mydata.size(); i++) {
    //     std::cout << Y[i][0] << std::endl;
    // }
    // X.delCol(7);
    Matrix Xdel = X.delCol(7);
    // for (size_t i {}; i < mydata.size(); i++) {
    //     for (size_t j {}; j < mydata[0].size() - 1; j++) {
    //         std::cout << Xdel[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    Matrix c { (Xdel.T() * Xdel).inv() };
    std::array<size_t, 2> size;
    size = c.getSize();
    for (size_t i {}; i < size[0]; i++) {
        for (size_t j {}; j < size[1]; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Matrix d { X.T() };
    Matrix W { c * d * Y };
    // W = (X.T() * X).inv();

    // W = (((X.T() * X).inv()) * X.T()) * Y;
    // std::array<size_t, 2> size;
    // size = Y.getSize();
    // std::cout << size[0] << " " << size[1] << std::endl;
    // W = (((Xdel.T() * Xdel).inv()) * Xdel.T()) * Y;

    return W;
}

Matrix predict(const char* file_name, Matrix& w, bool disp)
{
    std::vector<std::vector<double>> pdata;
    pdata = getData(file_name);

    Matrix X(pdata);
    Matrix Y;
    Matrix Xdel = X.delCol(7);
    Y = X.col_mat(7);

    Matrix y_hat { Xdel * w };

    if (disp) {
        const size_t num { 20 };
        // const size_t line { num * 3 };
        std::cout << std::left << std::setw(num) << "NO"
                  << std::left << std::setw(num) << "Real Grade"
                  << std::left << std::setw(num) << "Estimated Grade"
                  << std::right << std::endl;
        for (size_t i {}; i < pdata.size(); i++) {
            std::cout << std::left << std::setw(num) << i + 1
                      << std::left << std::setw(num) << Y[i][0]
                      << std::left << std::setw(num) << y_hat[i][0] << std::endl;
        }
    }

    return y_hat;
}
