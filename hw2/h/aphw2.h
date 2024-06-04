#ifndef APHW2_H
#define APH2_H

#include "matrix.h"
#include <iomanip>
#include <optional>

std::optional<double> det(Matrix&);
std::optional<Matrix> transpose(Matrix&);
std::vector<std::vector<double>> getData(const char*, bool = true);
Matrix findWeights(const char*);
Matrix predict(const char*, Matrix&, bool = true);

// ? size_t findMinNoOfMultiplications(std::vector<Matrix>& v);

#endif