#pragma once

#include <array>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>

namespace mathlib {
    template<int dim>
        class Vector;

    template<int dim, typename = void>
        class MaybeHasX {};

    template<int dim>
        class MaybeHasX<dim, std::enable_if_t<(dim > 0)>> {
            public:
                double& x() { return (reinterpret_cast<Vector<dim>*>(this))->operator[](0); }
                double x() const { return (reinterpret_cast<const Vector<dim>*>(this))->operator[](0); }
        };

    template<int dim, typename = void>
        class MaybeHasY {};

    template<int dim>
        class MaybeHasY<dim, std::enable_if_t<(dim > 1)>> {
            public:
                double& y() { return (reinterpret_cast<Vector<dim>*>(this))->operator[](1); }
                double y() const { return (reinterpret_cast<const Vector<dim>*>(this))->operator[](1); }
        };

    template<int dim, typename = void>
        class MaybeHasZ {};

    template<int dim>
        class MaybeHasZ<dim, std::enable_if_t<(dim > 2)>> {
            public:
                double& z() { return (reinterpret_cast<Vector<dim>*>(this))->operator[](2); }
                double z() const { return (reinterpret_cast<const Vector<dim>*>(this))->operator[](2); }

                // todo maybe learn some math and implement this for n-dimensional vector spaces
                Vector<dim> cross(const Vector<dim>& other) const
                {
                    const Vector<dim>* pThis = reinterpret_cast<const Vector<dim>*>(this);
                    return Vector<dim> {
                        pThis->y() * other.z() - pThis->z() * other.y(),
                            pThis->z() * other.x() - pThis->x() * other.z(),
                            pThis->x() * other.y() - pThis->y() * other.x(),
                    };
                }
        };

    template<int dim, typename = void>
        class MaybeHasW {};

    template<int dim>
        class MaybeHasW<dim, std::enable_if_t<(dim > 3)>> {
            public:
                double& w() { return (reinterpret_cast<Vector<dim>>(this))->operator[](3); }
        };

    template<int dim>
        class Vector : public MaybeHasX<dim>, public MaybeHasY<dim>, public MaybeHasZ<dim>, public MaybeHasW<dim> {
            private:
                std::array<double, dim> _val = {0};

            public:
                Vector() = default;
                Vector(const Vector& other) = default;
                template<typename... T>
                    Vector(T... v)
                    : _val {v...} {}

                // element-wise operations
                Vector<dim> operator+(const Vector<dim>& other) const
                {
                    Vector<dim> result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] + other._val[n];
                    }
                    return result;
                }

                Vector<dim> operator-(const Vector<dim>& other) const
                {
                    Vector<dim> result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] - other._val[n];
                    }
                    return result;
                }

                Vector<dim> operator*(const Vector<dim>& other) const
                {
                    Vector<dim> result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] * other._val[n];
                    }
                    return result;
                }

                Vector<dim> operator/(const Vector<dim>& other) const
                {
                    Vector<dim> result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] / other._val[n];
                    }
                    return result;
                }

                // scalar operations
                Vector<dim> operator*(double scale) const
                {
                    Vector<dim> result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] * scale;
                    }
                    return result;
                }

                Vector<dim> operator/(double scale) const
                {
                    Vector<dim> result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] / scale;
                    }
                    return result;
                }


                bool operator==(const Vector& other) const
                {
                    for (int n = 0; n < dim; n++) {
                        if (_val[n] != other._val[n])
                            return false;
                    }
                    return true;
                }

                bool operator!=(const Vector& other){
                    return !((*this) == other);
                }

                const double operator[](int row) const
                {
                    return _val[row];
                }

                double& operator[](int row)
                {
                    return _val[row];
                }

                // calculate the length of the vector
                double getLength() const
                {
                    return std::sqrt(getLengthSquared());
                }

                // calculate the length squared of the vector (self-dot)
                double getLengthSquared() const
                {
                    return dot(*this);
                }

                // return the normalized vector as a new one
                Vector getNormalized() const
                {
                    return (*this) / this->getLength();
                }

                // normalizes the vector
                void normalize()
                {
                    (*this) = getNormalized();
                }

                double dot(const Vector<dim>& other) const
                {
                    double sum = 0;
                    for (int n = 0; n < dim; n++)
                        sum += _val[n] * other._val[n];
                    return sum;
                }

                // print the vector in a formatted way
                void print() const
                {
                    std::stringstream ss;
                    ss << "[ ";
                    for (int n = 0; n < dim; n++)
                        ss << _val[n] << " ";
                    ss << "]\n";
                    std::string res = ss.str();
                    std::cout << res;
                    for (int i = 0; i < res.size() - 1; i++)
                        std::cout << "-";
                    std::cout << std::endl;
                }
        };

    typedef Vector<1> Vector1;
    typedef Vector<2> Vector2;
    typedef Vector<3> Vector3;
    typedef Vector<4> Vector4;
}
