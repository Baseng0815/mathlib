#include "base.h"

#include "../include/Vector.h"
#include "../include/Matrix.h"
#include "../include/Convert.h"
#include "../include/MatrixTransform.h"

using namespace mathlib;

void testVec() {
    std::cout << "testing vector..." << std::endl;
    Vector3 vec {0, 2, 1};
    ASSERT_EQUAL(vec, (Vector3 {0, 2, 1}));
    vec.print();
}

void testMatrix() {
    std::cout << "testing matrix..." << std::endl;
    auto mat = Matrix3::makeIdentity();
    ASSERT_EQUAL(mat, (Matrix3 {1, 0, 0, 0, 1, 0, 0, 0, 1}));
    mat.print();
}

void testOperations() {
    std::cout << "testing operations..." << std::endl;
    Vector3 vec {2, 1, 0};
    Matrix<2,3> mat {1, -1, 2, 0, -3, 1};

    Vector2 result = mat * vec;
    ASSERT_EQUAL(result, (Vector<2> {1, -3}));
    result.print();

    double lengthSquared = vec.getLengthSquared();
    std::cout << lengthSquared << std::endl;
    ASSERT_EQUAL(lengthSquared, 5);

    Vector3 vec2 {-2, 3, 1};
    Vector3 cross = vec.cross(vec2);
    cross.print();

    Vector4 xhat {1, 0, 0};
    Vector4 yhat {0, 1, 0};
    Vector4 zhat {0, 0, 1};

    std::cout << "X rotation 1\n";
    Matrix4 rot1 = createRotationX(toRadians(90.0));
    rot1.print();
    Vector4 xrot1 = rot1 * xhat;
    Vector4 yrot1 = rot1 * yhat;
    Vector4 zrot1 = rot1 * zhat;

    xrot1.print();
    yrot1.print();
    zrot1.print();

    std::cout << "X rotation 2\n";
    rot1 = createRotationX(toRadians(45.0));
    rot1.print();
    xrot1 = rot1 * xhat;
    yrot1 = rot1 * yhat;
    zrot1 = rot1 * zhat;

    xrot1.print();
    yrot1.print();
    zrot1.print();

    std::cout << "Y rotation\n";
    Matrix4 rot2 = createRotationY(toRadians(90.0));
    rot1.print();
    Vector4 xrot2 = rot2 * xhat;
    Vector4 yrot2 = rot2 * yhat;
    Vector4 zrot2 = rot2 * zhat;

    xrot2.print();
    yrot2.print();
    zrot2.print();

    std::cout << "Z rotation\n";
    Matrix4 rot3 = createRotationZ(toRadians(90.0));
    rot2.print();
    Vector4 xrot3 = rot3 * xhat;
    Vector4 yrot3 = rot3 * yhat;
    Vector4 zrot3 = rot3 * zhat;

    xrot3.print();
    yrot3.print();
    zrot3.print();
}

int main(int, char**) {
    testVec();
    testMatrix();
    testOperations();

    return 0;
}
