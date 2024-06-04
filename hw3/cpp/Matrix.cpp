#include "Matrix.h"

/*Constructors , destructor */
Matrix::Matrix(std::vector<std::vector<double>> data)
    : row { data.size() }
    , col { data[0].size() }

{
    // std::cout << "constructor mat-> "
    //   << "row: " << row << " col: " << col << std::endl;

    for (size_t i {}; i < row; i++) {

        if (col != data[i].size()) {
            throw std::out_of_range("Illegal Matrix!");
        }
    }

    allocspace();
    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] = data[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& m)
    : row { m.row }
    , col { m.col }
{
    allocspace();
    // std::cout << "copy constructor mat" << std::endl;
    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] = m.mat[i][j];
        }
    }
}

Matrix::Matrix(size_t _row, size_t _col, bool flag)
    : row { _row }
    , col { _col }
{
    allocspace();
    // std::cout << "specific constructor mat:" << row << "," << col << std::endl;
    if (flag == 1) {
        for (size_t i {}; i < row; i++) {
            for (size_t j {}; j < col; j++) {
                mat[i][j] = 1;
            }
        }
    } else {
        for (size_t i {}; i < row; i++) {
            for (size_t j {}; j < col; j++) {
                mat[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix()
    : row { 1 }
    , col { 1 }
{
    // std::cout << "default constructor mat" << std::endl;
    allocspace();
    mat[0][0] = 0;
}

Matrix::Matrix(Matrix&& matrix)
    : row { matrix.row }
    , col { matrix.col }
    , mat { matrix.mat }
{
    // std::cout << "move constructor of mat" << std::endl;
    matrix.mat = nullptr;
}

Matrix::~Matrix()
{
    // std::cout << "destructor mat" << std::endl;
    for (size_t i {}; i < row; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

/*Member Funtions*/
std::array<size_t, 2> Matrix::getSize()
{
    std::array<size_t, 2> arr_size { row, col };
    return arr_size;
}

/*Matrix Functions*/
double Matrix::det()
{
    double det { 0 };
    size_t rfix { 1 };
    if (row != col) {
        std::cout << "row != col " << std::endl;
        throw std::out_of_range("The matrix is not square");
        det = 0;
        return det;
    } else if (row == 1 && col == 1) {
        det = mat[0][0];
        return det;
    } else if (row == 2 && col == 2) {
        det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        return det;
    }
    for (size_t j { 0 }; j < col; j++) {
        det = det + mat[rfix - 1][j] * pow(-1, rfix + j + 1) * getMinor(rfix, j).det();
    }
    return det;
}

Matrix Matrix::T()
{
    size_t row_n { col };
    size_t col_n { row };
    std::vector<std::vector<double>> t_vec;
    for (size_t i {}; i < row_n; i++) {
        std::vector<double> t_tmp;
        for (size_t j {}; j < col_n; j++) {
            size_t i_new { j };
            size_t j_new { i };
            t_tmp.push_back(mat[i_new][j_new]);
        }
        t_vec.push_back(t_tmp);
    }
    Matrix t_mat(t_vec);
    return t_mat;
}

Matrix Matrix::inv()
{
    if (row != col) {
        throw std::out_of_range("Inversion-> Matrix not square");
        for (size_t i {}; i < row; i++) {
            for (size_t j {}; j < col; j++) {
                mat[i][j] = 0.0;
            }
        }
    }
    std::vector<std::vector<double>> mat_copy;
    for (size_t i {}; i < row; i++) {
        // std::cout << "row " << i << " ";
        std::vector<double> mat_tmp;
        for (size_t j {}; j < col; j++) {

            mat_tmp.push_back(mat[i][j]);
        }
        mat_copy.push_back(mat_tmp);
    }
    Matrix m2(mat_copy);
    double det_inv { m2.det() };
    std::vector<std::vector<double>> inv_mat;
    for (size_t i {}; i < row; i++) {
        double tmp1 { static_cast<double>(i) };
        std::vector<double> inv_tmp;
        for (size_t j {}; j < col; j++) {
            double tmp2 { static_cast<double>(j) };
            Matrix test { getMinor_inv(i, j) };

            double det_tmp { getMinor_inv(i, j).det() };
            double re { static_cast<double>((1.0 / det_inv)) * static_cast<double>((pow(-1.0, tmp1 + tmp2 + 2.0) * det_tmp)) };
            inv_tmp.push_back(re);
        }
        inv_mat.push_back(inv_tmp);
    }
    Matrix binvMat(inv_mat);
    return binvMat.T();
}

void Matrix::show() const
{
    std::cout << "Matrix show" << std::endl;
    std::cout << "row: " << row << std::endl;
    std::cout << "col: " << col << std::endl;

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            std::cout << std::setprecision(30) << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::delCol(size_t index)
{
    std::vector<std::vector<double>> del_mat;
    for (size_t i {}; i < row; i++) {
        std::vector<double> del_tmp;
        for (size_t j {}; j < col; j++) {
            if (j == index) {
                continue;
            }
            del_tmp.push_back(mat[i][j]);
        }
        del_mat.push_back(del_tmp);
    }
    Matrix delMat(del_mat);
    return Matrix(del_mat);
}

Matrix Matrix::col_mat(size_t index)
{
    std::vector<std::vector<double>> col_vec;
    std::vector<double> col_tmp;
    for (size_t i {}; i < row; i++) {
        col_tmp.push_back(mat[i][index]);
    }
    col_vec.push_back(col_tmp);
    Matrix mat_col(col_vec);
    Matrix colMat = mat_col.T();
    return colMat;
}

void Matrix::save(const char* file_name)
{
    std::ofstream ofs;
    ofs.open(file_name);
    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            ofs << mat[i][j];
            if (j != col - 1)
                ofs << ",";
        }
        ofs << std::endl;
    }
    ofs.close();
}

Matrix Matrix::load(const char* file_name)
{
    // std::cout << "load" << std::endl;
    std::ifstream ifs(file_name);
    std::string line;
    std::string tmp;
    std::string word;
    std::vector<std::vector<double>> m_vec;
    while (getline(ifs, line)) {
        std::vector<double> m_tmp;
        std::stringstream s(line);
        while (getline(s, word, ',')) {
            std::cout << std::stod(word) << " ";
            m_tmp.push_back(std::stod(word));
        }
        m_vec.push_back(m_tmp);
    }
    ifs.close();
    return Matrix(m_vec);
}

/*Operator overloading*/
Matrix Matrix::operator+(const Matrix& b) const
{
    if (row != b.row) {
        throw std::out_of_range("Matrix shoud be the same size!");
    }
    std::vector<std::vector<double>> sum_vec;
    for (size_t i {}; i < row; i++) {
        std::vector<double> sum_tmp;
        for (size_t j {}; j < col; j++) {
            sum_tmp.push_back(mat[i][j] + b.mat[i][j]);
        }
        sum_vec.push_back(sum_tmp);
    }
    return Matrix(sum_vec);
}

Matrix Matrix::operator-(const Matrix& b) const
{
    std::vector<std::vector<double>> min_vec;
    if (row != b.row) {
        throw std::out_of_range("Matrix shoud be the same size!");
    }
    for (size_t i {}; i < row; i++) {
        std::vector<double> tmp_vec;
        for (size_t j {}; j < col; j++) {
            tmp_vec.push_back(mat[i][j] - b.mat[i][j]);
        }
        min_vec.push_back(tmp_vec);
    }

    return Matrix(min_vec);
}

double* Matrix::operator[](size_t index)
{
    if (index < row or index < col) {
        return mat[index];

    } else {
        throw std::out_of_range("large index!");
    }
}

const double* Matrix::operator[](size_t index) const
{
    if (index < row or index < col) {
        return mat[index];

    } else {
        throw std::out_of_range("large index!");
    }
}
Matrix& Matrix::operator=(const Matrix& m)
{
    // std::cout << "mat operator = " << std::endl;
    if (this == &m) {
        return *this;
    }

    if (row != m.row || col != m.col) {
        for (size_t i {}; i < row; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }

    row = m.row;
    col = m.col;
    allocspace();

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] = m.mat[i][j];
        }
    }
    // std::cout << "finished mat operator = " << std::endl;

    return *this;
}
Matrix& Matrix::operator=(Matrix&& m)
{
    // std::cout << "mat operator = move " << std::endl;
    for (size_t i {}; i < row; i++) {
        delete[] mat[i];
    }
    delete[] mat;
    // std::cout << m.row << " " << row << std::endl;
    // std::cout << m.col << " " << col << std::endl;

    row = m.row;
    col = m.col;
    mat = m.mat;

    m.row = 0;
    m.col = 0;
    m.mat = nullptr;
    // std::cout << m.row << " " << row << std::endl;
    // std::cout << m.col << " " << col << std::endl;

    // std::cout << "finished mat operator = move" << std::endl;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    // std::cout << "mat operator +=" << std::endl;
    if (row != m.row || col != m.col) {
        std::out_of_range("can not sum 2matrix!");
    }

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] += m.mat[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    // std::cout << "mat operator -=" << std::endl;
    if (row != m.row || col != m.col) {
        std::out_of_range("can not minus 2matrix!");
    }

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] -= m.mat[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator*(const Matrix& b) const
{
    // std::cout << "my operator* mat" << std::endl;
    std::vector<std::vector<double>> mul_vec;
    for (size_t i {}; i < row; i++) {
        std::vector<double> tmp_vec;
        for (size_t j {}; j < b.col; j++) {
            size_t m { 0 };
            double tmp { 0 };
            while (m < col) {
                tmp = tmp + mat[i][m] * b.mat[m][j];
                m++;
            }
            tmp_vec.push_back(tmp);
        }
        mul_vec.push_back(tmp_vec);
    }

    return Matrix(mul_vec);
}

Matrix& Matrix::operator*=(const Matrix& m)
{
    // std::cout << "operator* mat" << std::endl;
    Matrix tmp(row, m.col);

    for (size_t i {}; i < tmp.row; i++) {
        for (size_t j {}; j < tmp.col; j++) {
            for (size_t k {}; k < col; k++) {
                tmp.mat[i][j] += (mat[i][k] * m.mat[k][j]);
            }
        }
    }

    return (*this = tmp);
}

Matrix& Matrix::operator*=(double num)
{
    std::cout << "operator* mat in num" << std::endl;

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] *= num;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(double num)
{
    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            mat[i][j] /= num;
        }
    }
    return *this;
}
/*Private functions*/

double Matrix::det_inv()
{
    double det {};
    if (row != col) {
        std::cout << "row != col " << std::endl;
        throw std::out_of_range("The matrix is not square");
        det = 0.0;
        return det;
    } else if (row == 2 && col == 2) {
        det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        return det;
    } else if (row == 1 && col == 1) {
        det = mat[0][0];
        return det;
    }

    return 0;
}
void Matrix::allocspace()
{
    mat = new double*[row];
    for (size_t i {}; i < row; i++) {
        mat[i] = new double[col];
    }
}

Matrix Matrix::getMinor(size_t row_minor, size_t col_minor)
{
    std::vector<std::vector<double>> mat_tmp;
    for (size_t i { row_minor }; i < row; i++) {
        std::vector<double> vec_tmp;
        for (size_t j { 0 }; j < col; j++) {
            if (j == col_minor) {
                continue;
            }
            vec_tmp.push_back(mat[i][j]);
        }
        mat_tmp.push_back(vec_tmp);
    }

    Matrix mat_new(mat_tmp);
    return mat_new;
}

Matrix Matrix::getMinor_inv(size_t row_inv, size_t col_inv)
{
    std::vector<std::vector<double>> inv_mat;
    for (size_t i {}; i < row; i++) {
        std::vector<double> inv_tmp;
        if (row_inv == i) {
            continue;
        }
        for (size_t j {}; j < col; j++) {
            if (j == col_inv) {
                continue;
            }
            inv_tmp.push_back(mat[i][j]);
        }
        inv_mat.push_back(inv_tmp);
    }
    if (inv_mat.size() == 0) {
        Matrix m;
        return m;
    } else {
        Matrix inv_minor(inv_mat);
        return inv_mat;
    }
}