#pragma once

#include "Vector.h"

namespace mathlib {
    template<int rows, int cols, typename vtype, typename = void>
        struct MaybeIsQuadratic {};

    template<int rows, int cols, typename vtype>
        class Matrix;

    template<int rows, int cols, typename vtype>
        class MaybeIsQuadratic<rows, cols, vtype, std::enable_if_t<(rows == cols)>> {
            public:
                Matrix<rows, rows, vtype> getInverse() {

                }

                static Matrix<rows, rows, vtype> makeIdentity() {
                    Matrix<rows, rows, vtype> result;
                    for (int i = 0; i < rows; i++) {
                        result[i][i] = 1;
                    }
                    return result;
                }
        };

    // primary template
    // row-major order
    template<int rows, int cols, typename vtype = float>
        class Matrix : public MaybeIsQuadratic<rows, cols, vtype> {
            private:
                std::array<std::array<vtype, cols>, rows> _val = {0};

                using ThisType = Matrix<rows, cols, vtype>;

            public:
                // default constructor that zero-initializes the matrix
                Matrix() = default;

                // constructor that takes elements from which to construct the matrix
                template<typename... T>
                Matrix(T... v)
                    : _val {v...} {}

                // copy constructor that also allows conversion
                template<typename T>
                    Matrix(const Matrix<rows, cols, T> &other)
                    {
                        for (int row = 0; row < rows; row++)
                            for (int col = 0; col < cols; col++)
                                _val[row][col] = static_cast<vtype>(other[row][col]);
                    }

                // move constructor that also allows conversion
                template<typename T>
                    Matrix(Matrix<rows, cols, T> &&other)
                    {
                        for (int row = 0; row < rows; row++)
                            for (int col = 0; col < cols; col++)
                                _val[row][col] = static_cast<vtype>(other[row][col]);
                    }

                // default move constructor
                Matrix(ThisType &&other) = default;

                // move assignment operator that also allows conversion
                template<typename T>
                    ThisType &operator=(Matrix<rows, cols, T> &&other)
                    {
                        for (int row = 0; row < rows; row++)
                            for (int col = 0; col < cols; col++)
                                _val[row][col] = static_cast<vtype>(other[row][col]);

                        return *this;
                    }

                // default move assignment operator
                ThisType &operator=(ThisType &&other) = default;

                ThisType operator+(const ThisType& other) const
                {
                    ThisType result;
                    for (int row = 0; row < rows; row++) {
                        for (int col = 0; col < cols; col++) {
                            result.at(row,col) = _val[row][col] + other.at(row,col);
                        }
                    }
                }

                ThisType operator-(const ThisType& other) const
                {
                    ThisType result;
                    for (int row = 0; row < rows; row++) {
                        for (int col = 0; col < cols; col++) {
                            result.at[row][col] = _val[row][col] - other[row][col];
                        }
                    }
                }

                template<int ocols>
                    Matrix<rows, ocols, vtype> operator*(const Matrix<cols, ocols, vtype>& other) const
                    {
                        Matrix<rows, ocols, vtype> result;
                        for (int row = 0; row < rows; row++) {
                            for (int col = 0; col < ocols; col++) {
                                for (int n = 0; n <  cols; n++) {
                                    result[row][col] += _val[row][n] * other[n][col];
                                }
                            }
                        }
                    }

                // vector rows must be equal to matrix columns
                Vector<rows, vtype> operator*(const Vector<cols, vtype>& v) const
                {
                    Vector<rows, vtype> result;
                    for (int row = 0; row < rows; row++) {
                        vtype sum = 0;
                        for (int col = 0; col < cols; col++) {
                            sum += _val[row][col] * v[col];
                        }
                        result[row] = sum;
                    }
                    return result;
                }


                bool operator==(const ThisType& other) const
                {
                    for (int row = 0; row < rows; row++) {
                        for (int col = 0; col < cols; col++) {
                            if (_val[row][col] != other[row][col])
                                return false;
                        }
                    }
                    return true;
                }

                bool operator!=(const ThisType& other) const
                {
                    return !(this->operator==(other));
                }

                const std::array<vtype, cols>& operator[](int row) const
                {
                    return _val[row];
                }

                std::array<vtype, cols>& operator[](int row)
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

    typedef Matrix<1,1, double> Matrix1d;
    typedef Matrix<2,2, double> Matrix2d;
    typedef Matrix<3,3, double> Matrix3d;
    typedef Matrix<4,4, double> Matrix4d;

    typedef Matrix<1,1, float> Matrix1f;
    typedef Matrix<2,2, float> Matrix2f;
    typedef Matrix<3,3, float> Matrix3f;
    typedef Matrix<4,4, float> Matrix4f;

    typedef Matrix<1,1, int> Matrix1i;
    typedef Matrix<2,2, int> Matrix2i;
    typedef Matrix<3,3, int> Matrix3i;
    typedef Matrix<4,4, int> Matrix4i;
}
