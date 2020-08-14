#include "base.h"

#include "../include/Vector.h"
#include "../include/Matrix.h"
#include "../include/Convert.h"
#include "../include/MatrixTransform.h"

#include <limits>

using namespace mathlib;

void testVec() {
    std::cout << "testing vector..." << std::endl;
    Vector3 vec {0, 2, 1};
    ASSERT_EQUAL(vec, (Vector3 {0, 2, 1}));
    (vec * 2.0f).print();
    (2.0f * vec).print();
    ASSERT_EQUAL(vec * 2.0f, 2.0f * vec);
    vec.print();
    Vector4 v4 {-1, 3.23, 2.1, 4};
    Vector<5, int> v5i = v4;
    v4.print();
    v5i.print();
    std::cout << v4.w() << " " << v5i.w() << std::endl;
}

void testMatrix() {
    std::cout << "testing matrix..." << std::endl;
    auto mat = Matrix3::makeIdentity();
    ASSERT_EQUAL(mat, (Matrix3 {1, 0, 0, 0, 1, 0, 0, 0, 1}));
    mat.print();

    Matrix<4, 2> m
    {
        1, 2,
        3, 4,
        5, 6,
        7, 8
    };
    m.print();
}

void testOperations() {
    {
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
    }

    Vector4 xhat {1, 0, 0};
    Vector4 yhat {0, 1, 0};
    Vector4 zhat {0, 0, 1};

    {
        std::cout << "X rotation 1" << std::endl;
        Matrix4 rot1 = createRotationX(toRadians(90.0));
        rot1.print();
        Vector4 xrot1 = rot1 * xhat;
        Vector4 yrot1 = rot1 * yhat;
        Vector4 zrot1 = rot1 * zhat;

        xrot1.print();
        yrot1.print();
        zrot1.print();
    }

    {
        std::cout << "X rotation 2" << std::endl;
        Matrix4 rot1 = createRotationX(toRadians(45.0));
        rot1.print();

        Vector4 xrot1 = rot1 * xhat;
        Vector4 yrot1 = rot1 * yhat;
        Vector4 zrot1 = rot1 * zhat;

        xrot1.print();
        yrot1.print();
        zrot1.print();
    }

    {
        std::cout << "Y rotation" << std::endl;
        Matrix4 rot2 = createRotationY(toRadians(90.0));
        rot2.print();

        Vector4 xrot2 = rot2 * xhat;
        Vector4 yrot2 = rot2 * yhat;
        Vector4 zrot2 = rot2 * zhat;

        xrot2.print();
        yrot2.print();
        zrot2.print();
    }

    {
        std::cout << "Z rotation" << std::endl;
        Matrix4 rot3 = createRotationZ(toRadians(90.0));
        rot3.print();

        Vector4 xrot3 = rot3 * xhat;
        Vector4 yrot3 = rot3 * yhat;
        Vector4 zrot3 = rot3 * zhat;

        xrot3.print();
        yrot3.print();
        zrot3.print();
    }

    {
        std::cout << "Testing matrix operations..." << std::endl;;
        Matrix4 ma = Matrix4::makeIdentity();
        Matrix4 mb = Matrix4::makeIdentity();
        Matrix4 mc = ma * mb;
        ma.print();
        mb.print();
        mc.print();
        ASSERT_EQUAL(ma, mb);
        ASSERT_EQUAL(ma, mc);
        ASSERT_EQUAL(mb, mc);

        Matrix<2,3,float> md {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
        Matrix<3,2,float> me {7.f, 8.f, 9.f, 10.f, 11.f, 12.f};
        auto mf = md * me;
        md.print();
        me.print();
        mf.print();
        ASSERT_EQUAL(mf, (Matrix<2,2,float> {58.f, 64.f, 139.f, 154.f}));
        auto mg = ma * mb * mc;
        mg.print();

        Matrix4 rotationMatrix = createRotationZ(90.0f)
            * createRotationY(90.0f)
            * createRotationX(90.0f);
        Matrix4 res = createTranslation(Vector3 {0.f, 1.f, 2.f}) * rotationMatrix;
        res.print();

        Matrix4 perspProj = createPerspectiveProjection(90.0f, 4/3.0f, 1.0f, 100.f);
        perspProj.print();

        Vector4 p {1, 1, 0, 1};
        Matrix4 scale = createScale(Vector3 {1, 1, 1});
        Matrix4 translate = createTranslation(Vector3 {0, 0, 0});

        Vector4 np = perspProj * scale * translate * p;
        p.print();
        np.print();
    }

    {
        std::cout << "Testing some conversions..." << std::endl;
        Vector3d vd {1.182938394828, -2.49281739292, 5.495030919283};
        Vector3f vf = vd;
        Vector3i vi = vf;
        vd.print(true);
        vf.print(true);
        vi.print(true);
    }

    {
        Vector2f v2f {2.1f, -3.53f};
        Vector3f v3f(v2f);
        Vector1f v1f(v2f);
        v1f.print();
        v2f.print();
        v3f.print();

        Matrix4 trans = createOrthographicProjection(0.f, 800.f, 0.f, 600.f);
        trans.print();
    }
}

int main(int, char**) {
    testVec();
    testMatrix();
    testOperations();

    return 0;
}
