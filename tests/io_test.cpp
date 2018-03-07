#define BOOST_TEST_MODULE "io"


#include "io.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>  // include this to get main(), otherwise the compiler will complain



BOOST_AUTO_TEST_CASE ( read_array_from_file ) {

    Eigen::MatrixXd M (7, 7);
    Eigen::Tensor<double, 4> T (7, 7, 7, 7);

    // Make sure that there's an error when a wrong path is supplied
    BOOST_REQUIRE_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_kinetic.dat", M), std::runtime_error);
    BOOST_REQUIRE_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_two_electron.dat", T), std::runtime_error);

    // Make sure that there's no error when a correct path is supplied
    BOOST_REQUIRE_NO_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_kinetic.data", M));
    BOOST_REQUIRE_NO_THROW(cpputil::io::readArrayFromFile("../tests/ref_data/h2o_sto-3g_two_electron.data", T));
}
