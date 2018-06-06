#define BOOST_TEST_MODULE "linalg_test"


#include "linalg.hpp"


#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>  // include this to get main(), otherwise the compiler will complain



BOOST_AUTO_TEST_CASE ( areEqual_throws ) {

    // Check for a throw if the dimensions aren't compatible.
    Eigen::Tensor<double, 4> M (2, 2, 2, 2);  // don't need to set them to zeros to check dimensions
    Eigen::Tensor<double, 4> T1 (2, 2, 3, 2);  // don't need to set them to zeros to check dimensions

    BOOST_CHECK_THROW(cpputil::linalg::areEqual(M, T1, 1.0e-6), std::invalid_argument);


    // Check for no throw if correct tensors are given.
    Eigen::Tensor<double, 4> T2 (2, 2, 2, 2);

    BOOST_CHECK_NO_THROW(cpputil::linalg::areEqual(M, T2, 1.0e-6));
}


BOOST_AUTO_TEST_CASE ( areEqual_example ) {

    Eigen::Tensor<double, 4> M (2, 2, 2, 2);
    Eigen::Tensor<double, 4> T (2, 2, 2, 2);


    // Fill the two compatible tensors with random data and check if they're not equal.
    M.setRandom();
    T.setRandom();

    BOOST_CHECK(!cpputil::linalg::areEqual(M, T, 1.0e-6));  // probability of random tensors being equal approaches zero


    // Fill the two compatible tensors with the same data and check if they're equal.
    M.setZero();
    T.setZero();
    M(0,1,0,0) = 0.5;
    T(0,1,0,0) = 0.5;

    BOOST_CHECK(cpputil::linalg::areEqual(M, T, 1.0e-6));
}


BOOST_AUTO_TEST_CASE ( areEqualEigenvectors ) {

    // Test areEqualEigenvectors with an example.
    Eigen::VectorXd a (3);
    Eigen::VectorXd b (3);
    Eigen::VectorXd c (3);
    Eigen::VectorXd d (3);

    a << 2, 3, 1;
    b << 2, 3, 1;
    c << -2, -3, -1;
    d << 2, 3, 0;


    BOOST_CHECK(cpputil::linalg::areEqualEigenvectors(a, b, 1.0e-6));
    BOOST_CHECK(cpputil::linalg::areEqualEigenvectors(a, c, 1.0e-6));
    BOOST_CHECK(cpputil::linalg::areEqualEigenvectors(b, c, 1.0e-6));

    BOOST_CHECK(!cpputil::linalg::areEqualEigenvectors(a, d, 1.0e-6));
    BOOST_CHECK(!cpputil::linalg::areEqualEigenvectors(c, d, 1.0e-6));
}


BOOST_AUTO_TEST_CASE ( areEqualSetsOfEigenvectors_throws ) {

    // Check for throws if the dimensions aren't compatible.
    Eigen::MatrixXd C1 (3, 3);
    Eigen::MatrixXd C2 (3, 2);

    BOOST_CHECK_THROW(cpputil::linalg::areEqualSetsOfEigenvectors(C1, C2, 1.0e-6), std::invalid_argument);


    // Check for no throw if the dimensions are compatible
    Eigen::MatrixXd C3 (3, 3);

    BOOST_CHECK_NO_THROW(cpputil::linalg::areEqualSetsOfEigenvectors(C1, C3, 1.0e-6));
}


BOOST_AUTO_TEST_CASE ( areEqualSetsOfEigenvectors_example ) {

    // Test areEqualSetsOfEigenvectors with an example
    Eigen::MatrixXd eigenvectors1 (2, 2);
    Eigen::MatrixXd eigenvectors2 (2, 2);
    Eigen::MatrixXd eigenvectors3 (2, 2);
    Eigen::MatrixXd eigenvectors4 (2, 2);

    eigenvectors1 << 0,  2,
                     1, -1;

    eigenvectors2 << 0,  2,
                     1, -1;

    eigenvectors3 << 0, -2,
                     1,  1;

    eigenvectors4 << 1,  2,
                     1, -1;


    BOOST_CHECK(cpputil::linalg::areEqualSetsOfEigenvectors(eigenvectors1, eigenvectors2, 1.0e-6));
    BOOST_CHECK(cpputil::linalg::areEqualSetsOfEigenvectors(eigenvectors1, eigenvectors3, 1.0e-6));

    BOOST_CHECK(!cpputil::linalg::areEqualSetsOfEigenvectors(eigenvectors1, eigenvectors4, 1.0e-6));
}


BOOST_AUTO_TEST_CASE ( strictLowerTriangle ) {

    Eigen::MatrixXd A (3, 3);
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    Eigen::VectorXd ref_strict_lower_triangle_A (3);
    ref_strict_lower_triangle_A << 4, 7, 8;

    BOOST_CHECK(ref_strict_lower_triangle_A.isApprox(cpputil::linalg::strictLowerTriangle(A)));


    Eigen::MatrixXd B (4, 4);
    B <<  1,  2,  3,  4,
          5,  6,  7,  8,
          9, 10, 11, 12,
         13, 14, 15, 16;

    Eigen::VectorXd ref_strict_lower_triangle_B (6);
    ref_strict_lower_triangle_B << 5, 9, 13, 10, 14, 15;

    BOOST_CHECK(ref_strict_lower_triangle_B.isApprox(cpputil::linalg::strictLowerTriangle(B)));


    Eigen::MatrixXd A_invalid (3, 4);
    BOOST_CHECK_THROW(cpputil::linalg::strictLowerTriangle(A_invalid), std::invalid_argument);
}


BOOST_AUTO_TEST_CASE ( toMatrix ) {

    // Create an example tensor
    Eigen::Tensor<double, 4> T (2, 2, 2, 2);

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            for (size_t k = 0; k < 2; k++) {
                for (size_t l = 0; l < 2; l++) {
                    T(i,j,k,l) = l + 2*k + 4*j + 8*i;
                }
            }
        }
    }


    Eigen::MatrixXd M_ref (4, 4);
    M_ref <<  0,  2,  1,  3,
              8, 10,  9, 11,
              4,  6,  5,  7,
             12, 14, 13, 15;


    BOOST_CHECK(M_ref.isApprox(cpputil::linalg::toMatrix(T), 1.0e-12));
}
