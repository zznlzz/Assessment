// #include <Eigen/Core>
// #include <Eigen/Dense>
#include <iostream>

using namespace std;
// using namespace Eigen;

class Matrix {
public:
    Matrix(int rows, int cols);
    ~Matrix();
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    Matrix operator*(Matrix &other);
    Matrix(int rows, int cols, int** matrix);
    // template <int rows, int cols> Matrix(int (&matrix)[rows][cols]);
    Matrix(const Matrix& other); // 拷贝构造
    Matrix(Matrix&& other); // 移动构造
    Matrix& operator=(const Matrix& other); // 拷贝构造
    Matrix& operator=(Matrix &&other); // 移动构造
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator/(const Matrix& other);
    bool operator==(const Matrix& other);

    int get_rows();
    int get_cols();
private:
    int rows;
    int cols;
    int **matrix;
};
std::istream& operator>>(std::istream& in, Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);