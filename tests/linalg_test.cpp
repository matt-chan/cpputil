#define BOOST_TEST_MODULE "linalg"


#include "linalg.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>  // include this to get main(), otherwise the compiler will complain



BOOST_AUTO_TEST_CASE ( are_equal ) {

    // Check for a throw if the dimensions aren't compatible
    Eigen::Tensor<double, 4> M (2, 2, 2, 2);
    Eigen::Tensor<double, 4> T1 (2, 2, 3, 2);

    BOOST_CHECK_THROW(cpputil::linalg::areEqual(M, T1, 1.0e-6), std::invalid_argument);


    // Check for no throw if correct tensors are given
    Eigen::Tensor<double, 4> T2 (2, 2, 2, 2);

    BOOST_CHECK_NO_THROW(cpputil::linalg::areEqual(M, T2, 1.0e-6));


    // Fill the two compatible tensors with random data and check if they're not equal
    M.setRandom();
    T2.setRandom();

    BOOST_CHECK(!cpputil::linalg::areEqual(M, T2, 1.0e-6));


    // Fill the two compatible tensors with the same data and check if they're equal
    M.setZero();
    T2.setZero();
    M(0,1,0,0) = 0.5;
    T2(0,1,0,0) = 0.5;

    BOOST_CHECK(cpputil::linalg::areEqual(M, T2, 1.0e-6));
}


BOOST_AUTO_TEST_CASE ( are_equal_eigenvectors ) {

    // Test areEqualEigenvectors with an example
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


BOOST_AUTO_TEST_CASE ( are_equal_sets_of_eigenvectors ) {

    // Check for throws if the dimensions aren't compatible
    Eigen::MatrixXd C1 (3, 3);
    Eigen::MatrixXd C2 (3, 2);

    BOOST_CHECK_THROW(cpputil::linalg::areEqualSetsOfEigenvectors(C1, C2, 1.0e-6), std::invalid_argument);


    // Check for no throw if the dimensions are compatible
    Eigen::MatrixXd C3 (3, 3);

    BOOST_CHECK_NO_THROW(cpputil::linalg::areEqualSetsOfEigenvectors(C1, C3, 1.0e-6));


    // Check an example
    Eigen::MatrixXd eigenvectors1 (2, 2);
    Eigen::MatrixXd eigenvectors2 (2, 2);
    Eigen::MatrixXd eigenvectors3 (2, 2);
    Eigen::MatrixXd eigenvectors4 (2, 2);


    eigenvectors1 << 0, 2,
                     1, -1;

    eigenvectors2 << 0, 2,
                     1, -1;

    eigenvectors3 << 0, -2,
                     1, 1;

    eigenvectors4 << 1, 2,
                     1, -1;


    BOOST_CHECK(cpputil::linalg::areEqualSetsOfEigenvectors(eigenvectors1, eigenvectors2, 1.0e-6));
    BOOST_CHECK(cpputil::linalg::areEqualSetsOfEigenvectors(eigenvectors1, eigenvectors3, 1.0e-6));

    BOOST_CHECK(!cpputil::linalg::areEqualSetsOfEigenvectors(eigenvectors1, eigenvectors4, 1.0e-6));
}
