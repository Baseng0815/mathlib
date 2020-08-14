#pragma once

#include <array>
#include <cmath>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include <type_traits>

namespace mathlib {
    template<int dim, typename vtype>
        class Vector;

    template<int dim, typename vtype, typename = void>
        class MaybeHasX {};

    template<int dim, typename vtype>
        class MaybeHasX<dim, vtype, std::enable_if_t<(dim > 0)>> {
            public:
                vtype &x() { return (static_cast<Vector<dim, vtype>*>(this))->operator[](0); }
                vtype x() const { return (static_cast<const Vector<dim, vtype>*>(this))->operator[](0); }
        };

    template<int dim, typename vtype, typename = void>
        class MaybeHasY {};

    template<int dim, typename vtype>
        class MaybeHasY<dim, vtype, std::enable_if_t<(dim > 1)>> {
            public:
                vtype &y() { return (static_cast<Vector<dim, vtype>*>(this))->operator[](1); }
                vtype y() const { return (static_cast<const Vector<dim, vtype>*>(this))->operator[](1); }
        };

    template<int dim, typename vtype, typename = void>
        class MaybeHasZ {};

    template<int dim, typename vtype>
        class MaybeHasZ<dim, vtype, std::enable_if_t<(dim > 2)>> {
            public:
                vtype &z() { return (static_cast<Vector<dim, vtype>*>(this))->operator[](2); }
                vtype z() const { return (static_cast<const Vector<dim, vtype>*>(this))->operator[](2); }

                // todo maybe learn some math and implement this for n-dimensional vector spaces
                Vector<dim, vtype> cross(const Vector<dim, vtype> &other) const
                {
                    const Vector<dim, vtype>* pThis = static_cast<const Vector<dim, vtype>*>(this);
                    return Vector<dim, vtype> {
                        pThis->y() * other.z() - pThis->z() * other.y(),
                            pThis->z() * other.x() - pThis->x() * other.z(),
                            pThis->x() * other.y() - pThis->y() * other.x(),
                    };
                }
        };

    template<int dim, typename vtype, typename = void>
        class MaybeHasW {};

    template<int dim, typename vtype>
        class MaybeHasW<dim, vtype, std::enable_if_t<(dim > 3)>> {
            public:
                vtype &w() { return (static_cast<Vector<dim, vtype>*>(this))->operator[](3); }
                vtype w() const { return (static_cast<const Vector<dim, vtype>*>(this))->operator[](3); }
        };

    template<int dim, typename vtype = float>
        class Vector : public MaybeHasX<dim, vtype>, public MaybeHasY<dim, vtype>, public MaybeHasZ<dim, vtype>, public MaybeHasW<dim, vtype> {
            private:
                std::array<vtype, dim> _val = {0};

                using ThisType = Vector<dim, vtype>;

            public:
                // default constructor that zero-initializes the vector
                Vector() = default;

                // constructor that takes elements from which to construct the vector
                template<typename... T>
                    Vector(T... v)
                    : _val {v...}
                {}

                // copy constructor that also allows conversion and size difference
                template<int odim, typename T>
                    Vector(const Vector<odim, T> &other)
                    {
                        for (int i = 0; i < std::min(dim, odim); i++)
                            _val[i] = static_cast<vtype>(other[i]);
                    }

                // default copy constructor
                Vector(const ThisType &other) = default;

                // default copy assignment
                Vector &operator=(const ThisType &other) = default;

                // copy assignment that also allows conversion
                template<int odim, typename T>
                    Vector &operator=(const Vector<odim, T> &other)
                    {
                        for (int i = 0; i < std::min(dim, odim); i++)
                            _val[i] = static_cast<vtype>(other[i]);

                        return *this;
                    }

                // default move constructor
                Vector(ThisType &&other) noexcept = default;

                // default move assignment operator
                ThisType &operator=(ThisType &&other) noexcept = default;

                // element-wise operations
                ThisType operator+(const ThisType& other) const
                {
                    ThisType result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] + other._val[n];
                    }
                    return result;
                }

                ThisType operator-(const ThisType& other) const
                {
                    ThisType result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] - other._val[n];
                    }
                    return result;
                }

                ThisType operator*(const ThisType& other) const
                {
                    ThisType result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] * other._val[n];
                    }
                    return result;
                }

                ThisType operator/(const ThisType& other) const
                {
                    ThisType result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = _val[n] / other._val[n];
                    }
                    return result;
                }

                ThisType &operator+=(const ThisType& other)
                {
                    for (int n = 0; n < dim; n++) {
                        _val[n] += other._val[n];
                    }
                    return *this;
                }

                ThisType &operator-=(const ThisType& other)
                {
                    for (int n = 0; n < dim; n++) {
                        _val[n] -= other._val[n];
                    }
                    return *this;
                }

                ThisType &operator*=(const ThisType& other)
                {
                    for (int n = 0; n < dim; n++) {
                        _val[n] *= other._val[n];
                    }
                    return *this;
                }
                ThisType &operator/=(const ThisType& other)
                {
                    for (int n = 0; n < dim; n++) {
                        _val[n] /= other._val[n];
                    }
                    return *this;
                }

                // scalar operations
                template<typename T>
                    ThisType operator*(T scale) const
                    {
                        ThisType result;
                        for (int n = 0; n < dim; n++) {
                            result[n] = _val[n] * scale;
                        }
                        return result;
                    }

                template<typename T>
                    ThisType operator/(T scale) const
                    {
                        ThisType result;
                        for (int n = 0; n < dim; n++) {
                            result[n] = _val[n] / scale;
                        }
                        return result;
                    }

                ThisType operator-() const
                {
                    ThisType result;
                    for (int n = 0; n < dim; n++) {
                        result[n] = -_val[n];
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

                const vtype operator[](int row) const
                {
                    return _val[row];
                }

                vtype& operator[](int row)
                {
                    return _val[row];
                }

                // calculate the length of the vector
                vtype getLength() const
                {
                    return std::sqrt(getLengthSquared());
                }

                // calculate the length squared of the vector (self-dot)
                vtype getLengthSquared() const
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

                vtype dot(const ThisType& other) const
                {
                    vtype sum = 0;
                    for (int n = 0; n < dim; n++)
                        sum += _val[n] * other._val[n];
                    return sum;
                }

                // print the vector in a formatted way
                void print(bool useBetterPrecision = false) const
                {
                    std::stringstream ss;
                    if (useBetterPrecision)
                        ss.precision(std::numeric_limits<vtype>::max_digits10);
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

    template<int dim, typename vtype>
        Vector<dim, vtype> operator*(const vtype &scale, const Vector<dim, vtype> &vec)
        {
            return vec * scale;
        }
    template<int dim, typename vtype>
        Vector<dim, vtype> operator/(const vtype &scale, const Vector<dim, vtype> &vec)
        {
            return vec * scale;
        }


    typedef Vector<1> Vector1;
    typedef Vector<2> Vector2;
    typedef Vector<3> Vector3;
    typedef Vector<4> Vector4;

    typedef Vector<1, double> Vector1d;
    typedef Vector<2, double> Vector2d;
    typedef Vector<3, double> Vector3d;
    typedef Vector<4, double> Vector4d;

    typedef Vector<1, float> Vector1f;
    typedef Vector<2, float> Vector2f;
    typedef Vector<3, float> Vector3f;
    typedef Vector<4, float> Vector4f;

    typedef Vector<1, int> Vector1i;
    typedef Vector<2, int> Vector2i;
    typedef Vector<3, int> Vector3i;
    typedef Vector<4, int> Vector4i;
}
