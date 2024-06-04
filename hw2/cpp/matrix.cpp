#include "matrix.h"

/*Constructors , destructor */
Matrix::Matrix(std::vector<std::vector<double>> data)
    : row { data.size() }
    , col { data[0].size() }

{
    // std::cout << "constructor1" << std::endl;
    // std::cout << "row:" << data.size() << " col:" << data[0].size() << std::endl;
    for (size_t i {}; i < row; i++) {

        if (col != data[i].size()) {
            throw std::out_of_range("Illegal Matrix!");
        }
    }
    // std::cout << "data1 " << &data << std::endl;
    // std::cout << "mat1 " << &(mat) << std::endl;

    allocspace();
    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            // std::cout << "data " << i << j << ": " << data[i][j] << std::endl;
            mat[i][j] = data[i][j];
            // std::cout << "new Add " << i << " : " << &mat[i] << std::endl;
        }
        // std::cout << "new Add: " << &mat << std::endl;
    }
    // std::cout << "after -----" << std::endl;

    // std::cout << "data1 " << &data << std::endl;
    // std::cout << "mat1 " << &mat << std::endl;
}

Matrix::Matrix(const Matrix& m)
    : row { m.row }
    , col { m.col }
{
    // std::cout << "copy constructor" << std::endl;
    // std::cout << "mat 2 " << &m.mat << std::endl;
    // std::cout << "m" << &mat << std::endl;
    allocspace();
    // std::cout << "after-------" << std::endl;
    // std::cout << "mat 2 " << &m.mat << std::endl;
    // std::cout << "m" << &mat << std::endl;

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            // std::cout << m.mat[i][j] << " ";
            mat[i][j] = m.mat[i][j];
            // std::cout << mat[i][j] << " ";
        }
    }
    std::cout << std::endl;
}

Matrix::Matrix(size_t _row, size_t _col, bool flag)
    : row { _row }
    , col { _col }
{
    std::cout << "specific constructor " << std::endl;
    allocspace();
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
    // std::cout << "default constructor" << std::endl;
    allocspace();
    mat[0][0] = 0;
}

// Matrix::Matrix(std::unique_ptr<std::unique_ptr<double[]>[]> data, size_t m, size_t n)
// {
// }

Matrix::~Matrix()
{
    // std::cout << "destructor" << std::endl;
    for (size_t i {}; i < row; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

/*Member Funtions*/
std::array<size_t, 2> Matrix::getSize()
{
    std::array<size_t, 2> arr_size { row, col };
    // std::cout << "row " << arr_size[0] << std::endl;
    // std::cout << "col " << arr_size[1] << std::endl;

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
        // std::cout << "row == col = 1 " << std::endl;

        det = mat[0][0];
        // std::cout << " one element: " << det << std::endl;
        return det;
    } else if (row == 2 && col == 2) {
        // std::cout << "[0][0]" << mat[0][0] << std::endl;
        // std::cout << "[1][1]" << mat[0][1] << std::endl;
        // std::cout << "[0][1]" << mat[1][0] << std::endl;
        // std::cout << "[1][0]" << mat[1][1] << std::endl;
        det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        // std::cout << " two element: " << det << std::endl;
        return det;
    }
    for (size_t j { 0 }; j < col; j++) {
        det = det + mat[rfix - 1][j] * pow(-1, rfix + j + 1) * getMinor(rfix, j).det();
        // std::cout << "det: " << det;
        // std::cout << std::endl;
    }
    return det;
}

Matrix Matrix::T()
{
    // std::cout << "-----Transpose of the matrix-----" << std::endl;
    // std::cout << "row:" << row << "col: " << col << std::endl;
    size_t row_n { col };
    size_t col_n { row };
    // std::cout << "Trow: " << row_n << " Tcol: " << col_n << std::endl;
    std::vector<std::vector<double>> t_vec;
    for (size_t i {}; i < row_n; i++) {
        std::vector<double> t_tmp;
        for (size_t j {}; j < col_n; j++) {
            size_t i_new { j };
            size_t j_new { i };
            // std::cout << mat[i_new][j_new] << std::endl;
            t_tmp.push_back(mat[i_new][j_new]);
        }
        t_vec.push_back(t_tmp);
    }
    Matrix t_mat(t_vec);
    return t_mat;
}

Matrix Matrix::inv()
{
    // std::cout << "------- Inverse Function ------" << std::endl;
    // std::cout << "row " << row << std::endl;
    // std::cout << "col " << col << std::endl;
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
            // std::cout << " col " << j << std::endl;

            // std::cout << "mat" << i << j << ": " << mat[i][j] << std::endl;
            mat_tmp.push_back(mat[i][j]);
            // std::cout << "matcopy" << i << j << ": " << mat_copy[i][j] << std::endl;
        }
        mat_copy.push_back(mat_tmp);
    }
    Matrix m2(mat_copy);
    double det_inv { m2.det() };
    // std::cout << "det inv: " << det_inv << std::endl;
    std::vector<std::vector<double>> inv_mat;
    for (size_t i {}; i < row; i++) {
        double tmp1 { static_cast<double>(i) };
        std::vector<double> inv_tmp;
        for (size_t j {}; j < col; j++) {
            double tmp2 { static_cast<double>(j) };
            Matrix test { getMinor_inv(i, j) };
            // std::array<size_t, 2> size = test.getSize();
            // std::cout << "r: " << size[0] << "c: " << size[1] << std::endl;
            double det_tmp { getMinor_inv(i, j).det() };
            // std::cout << " getMinor_inv(i, j) " << det_tmp << std::endl;
            // std::cout << "test " << static_cast<double>((1.0 / det_inv)) << std::endl;
            // std::cout << "test2 " << static_cast<double>((pow(-1.0, tmp1 + tmp2 + 2.0) * det_tmp)) << std::endl;
            double re { static_cast<double>((1.0 / det_inv)) * static_cast<double>((pow(-1.0, tmp1 + tmp2 + 2.0) * det_tmp)) };
            // std::cout << re << std::endl;
            inv_tmp.push_back(re);
        }
        inv_mat.push_back(inv_tmp);
    }
    Matrix binvMat(inv_mat);

    // std::cout << "------ Inverse Matrix ------" << std::endl;
    // binvMat.T();
    return binvMat.T();
}

void Matrix::show() const
{
    // std::cout << "new row " << row << std::endl;
    // std::cout << "new col " << col << std::endl;

    for (size_t i {}; i < row; i++) {
        for (size_t j {}; j < col; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// void Matrix::show(const Matrix m) const
// {
//     std::cout << "new row " << m.row << std::endl;
//     std::cout << "new col " << m.col << std::endl;

//     for (size_t i {}; i < m.row; i++) {
//         for (size_t j {}; j < m.col; j++) {
//             std::cout << m.mat[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

Matrix Matrix::delCol(size_t index)
{
    // std::cout << "delCol" << std::endl;
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
    // std::cout << "delrow: " << delMat.row << " del_col: " << delMat.col << std::endl;

    return Matrix(del_mat);
}

Matrix Matrix::col_mat(size_t index)
{
    std::vector<std::vector<double>> col_vec;
    std::vector<double> col_tmp;
    for (size_t i {}; i < row; i++) {
        // col_vec[i][index] = mat[i][index];
        col_tmp.push_back(mat[i][index]);
    }
    col_vec.push_back(col_tmp);
    Matrix mat_col(col_vec);
    Matrix colMat = mat_col.T();
    // std::cout << "col_mat_row: " << colMat.row << "col_mat_col: " << colMat.col << std::endl;
    return colMat;
}

void Matrix::save(const char* file_name)
{
    std::ofstream ofs;
    ofs.open(file_name);
    for (size_t i {}; i < row; i++) {
        // ofs << "[";
        for (size_t j {}; j < col; j++) {
            ofs << mat[i][j];
            if (j != col - 1)
                ofs << ",";
        }
        // ofs << "]";
        ofs << std::endl;
    }
    ofs.close();
}

Matrix Matrix::load(const char* file_name)
{
    std::cout << "load" << std::endl;
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

Matrix Matrix::operator*(const Matrix& b) const
{
    // std::cout << "*col1: " << col << " and "
    //   << "*row2: " << b.row << std::endl;
    // if (col != b.row) {
    //     std::cout << "col1: " << col << " "
    //               << "row2: " << b.row << std::endl;
    //     throw std::out_of_range("Can not multiply!");
    // }
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

double* Matrix::operator[](size_t index)
{
    // std::cout << "operator []" << std::endl;
    if (index < row or index < col) {
        // std::cout << *mat[index] << std::endl;
        return mat[index];

    } else {
        throw std::out_of_range("large index!");
    }
}

const double* Matrix::operator[](size_t index) const
{
    // std::cout << "operator []" << std::endl;
    if (index < row or index < col) {
        // std::cout << *mat[index] << std::endl;
        return mat[index];

    } else {
        throw std::out_of_range("large index!");
    }
}

// Matrix Matrix::operator()(const Matrix& matp)
// {
//     std::vector<std::vector<double>> mat_vec;
//     for (size_t i {}; i < row; i++) {
//         std::vector<double> tmp_vec;
//         for (size_t j {}; j < col; j++) {
//             tmp_vec.push_back(matp.mat[i][j]);
//         }
//         mat_vec.push_back(tmp_vec);
//     }
//     return Matrix(mat_vec);
// }
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
        // std::cout << "row == col = 1 " << std::endl;
        det = mat[0][0];
        return det;
    }

    return 0;
}
void Matrix::allocspace()
{
    // std::cout << "New allocation memory for object " << std::endl;

    mat = new double*[row];
    for (size_t i {}; i < row; i++) {
        mat[i] = new double[col];
    }
    // std::cout << "pri" << &(mat[0]) << std::endl;
}

Matrix Matrix::getMinor(size_t row_minor, size_t col_minor)
{
    std::vector<std::vector<double>> mat_tmp;
    for (size_t i { row_minor }; i < row; i++) {
        std::vector<double> vec_tmp;
        for (size_t j { 0 }; j < col; j++) {
            if (j == col_minor) {
                // std::cout << "------continue---- " << j << ":" << std::endl;
                continue;
            }
            // std::cout << "Minor mat" << i << j << ":" << mat[i][j] << std::endl;
            vec_tmp.push_back(mat[i][j]);
        }
        mat_tmp.push_back(vec_tmp);
    }

    // std::cout << "1:" << mat_tmp[0][0] << std::endl;
    // std::cout << "2:" << mat_tmp[0][1] << std::endl;
    // std::cout << "3:" << mat_tmp[1][0] << std::endl;
    // std::cout << "4:" << mat_tmp[1][1] << std::endl;

    // for (size_t i {}; i < mat_tmp.size(); i++) {
    //     for (size_t j {}; j < mat_tmp[0].size(); j++) {
    //         std::cout << "mat_tmp " << i << j << ": " << mat_tmp[i][j] << std::endl;
    //     }
    // }
    Matrix mat_new(mat_tmp);
    return mat_new;
}

Matrix Matrix::getMinor_inv(size_t row_inv, size_t col_inv)
{
    std::vector<std::vector<double>> inv_mat;
    // std::cout << "row: " << row << std::endl;
    // std::cout << "col: " << col << std::endl;
    // std::cout << "row_inv: " << row_inv << std::endl;
    // std::cout << "col_inv: " << col_inv << std::endl;

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
    // std::cout << "size: " << inv_mat.size();
    // std::cout << "here" << std::endl;
    // std::cout << "here2" << std::endl;
    // return inv_minor;
}