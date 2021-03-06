#define BOOST_TEST_MODULE "io_test"


#include "io.hpp"

#include "linalg.hpp"


#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>  // include this to get main(), otherwise the compiler will complain



BOOST_AUTO_TEST_CASE ( readVectorFromFile_throw ) {

    Eigen::VectorXd v = Eigen::VectorXd::Zero(7);


    // Check that there's an error when a wrong path is supplied.
    BOOST_CHECK_THROW(cpputil::io::readVectorFromFile("../tests/ref_data/small_vector.dat", v),
                      std::runtime_error);  // should be 'datA'


    // Check that there's no error when a correct path is supplied.
    BOOST_CHECK_NO_THROW(cpputil::io::readVectorFromFile("../tests/ref_data/small_vector.data", v));


    // Check that there's an error when the matrix is incompatible with the given file.
    BOOST_CHECK_THROW(cpputil::io::readVectorFromFile("../tests/ref_data/h2o_sto-3g_two_electron.data", v),
                      std::runtime_error);  // can't read in two-electron data in a vector
}


BOOST_AUTO_TEST_CASE ( readArrayFromFile_matrix_throw ) {

    Eigen::MatrixXd M = Eigen::MatrixXd::Zero(7, 7);


    // Check that there's an error when a wrong path is supplied.
    BOOST_CHECK_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_kinetic.dat", M),
                      std::runtime_error);  // should be 'datA'


    // Check that there's no error when a correct path is supplied.
    BOOST_CHECK_NO_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_kinetic.data", M));


    // Check that there's an error when the matrix is incompatible with the given file.
    BOOST_CHECK_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_two_electron.data", M),
                      std::runtime_error);  // can't read in two-electron data in a matrix
}



BOOST_AUTO_TEST_CASE ( readArrayFromFile_tensor_throw ) {

    Eigen::Tensor<double, 4> T (7, 7, 7, 7);
    T.setZero();


    // Check that there's an error when a wrong path is supplied.
    BOOST_CHECK_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_two_electron.dat", T),
                      std::runtime_error);


    // Check that there's no error when a correct path is supplied.
    BOOST_CHECK_NO_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_two_electron.data", T));


    // Check that there's an error when the tensor is incompatible with the given file.
    BOOST_CHECK_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_kinetic.data", T),
                      std::runtime_error);  // can't read in one-electron data in a tensor
}


BOOST_AUTO_TEST_CASE ( readVectorFromFile_example ) {

    // Test the read function on a small example
    Eigen::VectorXd v (4);
    Eigen::VectorXd v_ref (4);
    v_ref << 1.5, -0.2, 0.002, 8.3314;

    cpputil::io::readVectorFromFile("../tests/ref_data/small_vector.data", v);
    std::cout << v << std::endl;


    BOOST_CHECK(v.isApprox(v_ref, 1.0e-8));
}


BOOST_AUTO_TEST_CASE ( readArrayFromFile_matrix_example ) {

    // Test the read function on a small example mimicking the one-electron integrals.
    Eigen::MatrixXd M (2, 2);
    Eigen::MatrixXd M_ref (2, 2);
    M_ref << 2.1,  1.1,
             1.1, -3.4;

    cpputil::io::readArrayFromFile("../tests/ref_data/small_one_ints.data", M);


    BOOST_CHECK(M.isApprox(M_ref, 1.0e-8));
}


BOOST_AUTO_TEST_CASE ( readArrayFromFile_tensor_example ) {

    // Test the read function on a small example mimicking the two-electron integrals.
    Eigen::Tensor<double, 4> T (6, 6, 6, 6);
    T.setZero();
    Eigen::Tensor<double, 4> T_ref (6, 6, 6, 6);
    T_ref.setZero();

    T_ref(0,0,0,0) = 4.78506540471;
    T_ref(0,0,0,1) = 0.741380351973;
    T_ref(0,0,0,2) = 0.0;
    T_ref(0,0,0,3) = 3.94054708595e-17;
    T_ref(0,0,0,4) = 0.0;
    T_ref(0,0,0,5) = 0.121785318177;
    T_ref(0,0,0,6) = 0.121785318177;

    cpputil::io::readArrayFromFile("../tests/ref_data/small_two_ints.data", T);


    BOOST_CHECK(cpputil::linalg::areEqual(T, T_ref, 1.0e-8));
}
