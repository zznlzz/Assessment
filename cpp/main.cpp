/**
 * 完善 Matrix 类，使得下面的代码可以正常运行:
 * class Matrix {
 * public:
 * TODO: Someting
 * private:
 *     int rows;
 *     int cols;
 *     int **matrix;
 * };
 *
 * 评分标准：
 * 1. 代码能够正常的运行就有 100 分，若代码不能正常运行，则按以下标准进行评分：
 * Matrix::Matrix(int rows, int cols):                              20 points
 * Matrix::~Matrix():                                               20 points
 * std::istream& operator>>(std::istream& in, Matrix& matrix)       20 points
 * std::ostream& operator<<(std::ostream& os, const Matrix& matrix) 20 points
 * Matrix Matrix::operator*(Matrix &other)                          20 points
 * 2. 在正常运行的基础上，若还有其他的功能，则按以下标准进行评分：
 * Matrix::Matrix(int rows, int cols, int** matrix)                 10 points
 * template <...> Matrix::Matrix(int (&matrix)[rows][cols])         10 points
 * Matrix::Matrix(const Matrix& other)                              10 points
 * Matrix::Matrix(Matrix&& other)                                   10 points
 * Matrix& Matrix::operator=(const Matrix& other)                   10 points
 * Matrix& Matrix::operator=(Matrix &&other)                        10 points
 * Matrix Matrix::operator+(const Matrix& other)                    10 points
 * Matrix Matrix::operator-(const Matrix& other)                    10 points
 * Matrix Matrix::operator/(const Matrix& other)                    10 points
 * bool Matrix::operator==(const Matrix& other)                     10 points
 */

#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

std::istream &operator>>(std::istream &in, Matrix &matrix)
{
    for (int i = 0; i < matrix.rows; ++i)
    {
        for (int j = 0; j < matrix.cols; ++j)
        {
            in >> matrix.matrix[i][j];
        }
    }
    return in;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            os << matrix.matrix[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix Matrix::operator*(Matrix &other)
{
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            result.matrix[i][j] = 0;
            for (int k = 0; k < cols; k++)
            {
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                // cout << matrix[i][k] << "*" << other.matrix[k][j] << " ";
            }
            // cout << endl;
        }
    }
    return result;
}

Matrix::Matrix(int rows, int cols, int **matrix)
{
    this->rows = rows;
    this->cols = cols;
    this->matrix = matrix;
}

// 拷贝构造
Matrix::Matrix(const Matrix& other)
{
    rows = other.rows;
    cols = other.cols;
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

// 移动构造
Matrix::Matrix(Matrix&& other)
{
    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.matrix = nullptr;
}

// 拷贝构造
Matrix& Matrix::operator=(const Matrix& other)
{
    rows = other.rows;
    cols = other.cols;
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    return *this;
}

// 移动构造
Matrix& Matrix::operator=(Matrix &&other)
{
    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.matrix = nullptr;
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) 
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) 
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator/(const Matrix& other)
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.matrix[i][j] = matrix[i][j] / other.matrix[i][j];
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other)
{
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            if (matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int Matrix::get_rows()
{
    return rows;
}

int Matrix::get_cols()
{
    return cols;
}

int main()
{
    int rows, cols;

    std::cin >> rows >> cols;
    Matrix A(rows, cols);
    std::cin >> A;

    std::cin >> rows >> cols;
    Matrix B(rows, cols);
    std::cin >> B;

    std::cout << "矩阵乘法: A * B =" << endl;
    std::cout << A * B;

    std::cout << "矩阵除法: A / B =" << endl;
    std::cout << A / B;    

    if(A.get_rows() == B.get_rows() && A.get_cols() == B.get_cols()){
        std::cout << "矩阵加法: A + B =" << endl;
        std::cout << A + B;

        std::cout << "矩阵减法: A - B =" << endl;
        std::cout << A - B;

        if(A == B){
            std::cout << "矩阵相等" << endl; 
        }
    }

    return 0;
}
