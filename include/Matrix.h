#pragma once

#include "Vector.h"

namespace mathlib {
    template<int rows, int cols, typename = void>
        struct MaybeIsQuadratic {};

    template<int rows, int cols>
        class Matrix;

    template<int rows, int cols>
        class MaybeIsQuadratic<rows, cols, std::enable_if_t<(rows == cols)>> {
            public:
                Matrix<rows,rows> getInverse() {

                }

                static Matrix<rows,rows> makeIdentity() {
                    Matrix<rows, rows> result;
                    for (int i = 0; i < rows; i++) {
                        result[i][i] = 1;
                    }
                    return result;
                }
        };

    // primary template
    template<int rows, int cols>
        class Matrix : public MaybeIsQuadratic<rows, cols> {
            private:
                std::array<std::array<double, cols>, rows> _val = {0};

            public:
                Matrix() = default;
                template<typename... T>
                Matrix(T... v)
                    : _val {v...} {}

                Matrix<rows, cols> operator+(const Matrix<rows, cols>& other) const
                {
                    Matrix<rows, cols> result;
                    for (int row = 0; row < rows; row++) {
                        for (int col = 0; col < cols; col++) {
                            result.at(row,col) = _val[row][col] + other.at(row,col);
                        }
                    }
                }

                Matrix<rows, cols> operator-(const Matrix<rows, cols>& other) const
                {
                    Matrix<rows, cols> result;
                    for (int row = 0; row < rows; row++) {
                        for (int col = 0; col < cols; col++) {
                            result.at(row,col) = _val[row][col] - other.at(row,col);
                        }
                    }
                }

                template<int ocols>
                    Matrix<rows, ocols> operator*(const Matrix<cols, ocols>& other) const
                    {
                        Matrix<rows, ocols> result;
                        for (int row = 0; row < rows; row++) {
                            for (int col = 0; col < ocols; col++) {
                                for (int n = 0; n <  cols; n++) {
                                    result.at(row,col) += _val[row][n] * other.at(n, col);
                                }
                            }
                        }
                    }

                // vector rows must be equal to matrix columns
                Vector<rows> operator*(const Vector<cols>& v) const
                {
                    Vector<rows> result;
                    for (int row = 0; row < rows; row++) {
                        double sum = 0;
                        for (int col = 0; col < cols; col++) {
                            sum += _val[row][col] * v[col];
                        }
                        result[row] = sum;
                    }
                    return result;
                }


                bool operator==(const Matrix<rows, cols>& other) const
                {
                    for (int row = 0; row < rows; row++) {
                        for (int col = 0; col < cols; col++) {
                            if (_val[row][col] != other[row][col])
                                return false;
                        }
                    }
                    return true;
                }

                bool operator!=(const Matrix<rows, cols>& other) const
                {
                    return !(this->operator==(other));
                }

                const std::array<double, cols>& operator[](int row) const
                {
                    return _val[row];
                }

                std::array<double, cols>& operator[](int row)
                {
                    return _val[row];
                }

                // print the matrix in a formatted way
                void print() const
                {
                    // get longest row
                    int longest = 0;
                    std::string rowStrings[rows];
                    std::stringstream r;
                    for (int row = 0; row < rows; row++) {
                        r.str(std::string());
                        r << "[ ";
                        for (int col = 0; col < cols; col++) {
                            r << _val[row][col] << " ";
                        }
                        rowStrings[row] = r.str();
                        if (rowStrings[row].size() > longest)
                            longest = rowStrings[row].size();
                    }

                    // fill with spaces and print
                    for (int row = 0; row < rows; row++) {
                        rowStrings[row].resize(longest, ' ');
                        std::cout << rowStrings[row] << "]\n";
                    }

                    for (int i = 0; i < longest + 1; i++)
                        std::cout << "-";
                    std::cout << std::endl;
                }
        };

    typedef Matrix<1,1> Matrix1;
    typedef Matrix<2,2> Matrix2;
    typedef Matrix<3,3> Matrix3;
    typedef Matrix<4,4> Matrix4;
}
