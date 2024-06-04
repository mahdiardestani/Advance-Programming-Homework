#include "aphw1.h"

std::vector<std::vector<double>> getData(const char* file_path)
{
    std::ifstream ifs;
    ifs.open(file_path);
    std::string line;
    std::vector<std::vector<double>> vec2_num;
    if (ifs.is_open()) {
        while (std::getline(ifs, line, '\n')) {
            std::stringstream data(line);
            std::string word;
            std::vector<double> vec_num;
            while (std::getline(data, word, ',')) {
                vec_num.push_back(std::stod(word));
            }
            vec_num[2] = vec_num[2] / 100.0;
            vec_num[3] = vec_num[3] / 100.0;
            vec_num.insert(vec_num.begin(), 1.0);
            vec2_num.push_back(vec_num);
        }
    }

    return vec2_num;
}

void displayDataset(std::vector<std::vector<double>> vec)
{
    const int num { 15 };
    const int line { 8 * num };
    std::cout << std::left << std::setw(num) << "Bias"
              << std::left << std::setw(num) << "class"
              << std::left << std::setw(num) << "TA"
              << std::left << std::setw(num) << "Coding"
              << std::left << std::setw(num) << "Studing"
              << std::left << std::setw(num) << "Background"
              << std::left << std::setw(num) << "Mind"
              << std::left << std::setw(num) << "Grade" << std::endl;
    std::cout << std::string(line, '*') << std::endl;

    for (size_t i {}; i < vec.size(); i++) {
        std::cout << std::right << std::setw(num);
        for (size_t j {}; j < vec[i].size(); j++) {
            std::cout << std::left << vec[i][j] << std::setw(num);
        }
        std::cout << std::right << std::endl;
    }
}

double grade(std::vector<double> w, std::vector<double> x)
{
    if (x.size() == 8) {
        x.pop_back();
    }
    double inner { 0.0 };
    inner = std::inner_product(x.begin(), x.end(), w.begin(), 0.0);
    return inner;
}

double J(std::vector<double> w, std::vector<std::vector<double>> data_vec)
{
    double sum { 0.0 };
    double J { 0.0 };
    for (size_t i {}; i < data_vec.size(); i++) {
        double tmp { 0.0 };
        tmp = grade(w, data_vec[i]);
        sum = sum + pow((tmp - data_vec[i][7]), 2);
    }
    J = (1.0 / (2.0 * data_vec.size())) * sum;
    return J;
}

std::vector<double> train(std::vector<std::vector<double>> data_vec, std::vector<double> w_vec, double lr,
    size_t max_iter, double min_cost, bool verbose)
{
    for (size_t m {}; m < max_iter; m++) {
        for (size_t i {}; i < data_vec[0].size() - 1; i++) {
            double gradian { 0.0 };
            double sum { 0.0 };
            for (size_t j {}; j < data_vec.size(); j++) {
                double tmp { 0.0 };
                tmp = grade(w_vec, data_vec[j]);
                sum = sum + ((tmp - data_vec[j][7]) * data_vec[j][i]);
            }
            gradian = (1.0 / data_vec.size()) * sum;
            w_vec[i] = w_vec[i] - (lr * gradian);
        }
        double cost { 0.0 };
        cost = J(w_vec, data_vec);
        std::cout << "iteration " << m + 1 << ":" << cost << std::endl;
        if (cost <= min_cost) {
            std::cout << "Reach the min_cost!" << std::endl;
            break;
        }
        if (verbose) {
            std::cout << "Cost in" << m + 1 << "itearion: " << cost << std::endl;
        }
    }
    return w_vec;
}

void displayOutput(std::vector<std::vector<double>> data_vec, std::vector<double> w_vec)
{
    std::vector<double> est_grade;
    for (size_t i {}; i < data_vec.size(); i++) {
        est_grade.push_back(grade(w_vec, data_vec[i]));
    }
    const size_t num { 20 };
    const size_t line { num * 3 };
    std::cout << std::left << std::setw(num) << "NO"
              << std::left << std::setw(num) << "Real Grade"
              << std::left << std::setw(num) << "Estimated Grade"
              << std::right << std::endl;
    std::cout << std::string(line, '*') << std::endl;
    for (size_t i {}; i < data_vec.size(); i++) {
        std::cout << std::left << std::setw(num) << i + 1
                  << std::left << std::setw(num) << data_vec[i][7]
                  << std::left << std::setw(num) << est_grade[i]
                  << std::endl;
    }
}

void save(std::vector<double> w_vec, const char* file_name)
{
    std::ofstream ofs(file_name);
    for (size_t i {}; i < w_vec.size(); i++) {
        ofs << w_vec[i] << std::endl;
    }
    ofs.close();
}

std::vector<double> load(const char* file_name)
{
    std::vector<double> wf_vec;
    std::ifstream ifs(file_name);
    std::string line;
    while (std::getline(ifs, line, '\n')) {
        wf_vec.push_back(std::stod(line));
    }

    ifs.close();

    return wf_vec;
}

void predict(std::vector<double> fea_vec)
{
    std::vector<double> fea_tmp(fea_vec.begin(), fea_vec.begin() + 6);
    std::vector<double> w_tmp(fea_vec.begin() + 7, fea_vec.end());

    std::cout << grade(w_tmp, fea_tmp) << std::endl;
}
