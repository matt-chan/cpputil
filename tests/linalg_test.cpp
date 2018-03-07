#define BOOST_TEST_MODULE "linalg"


#include "linalg.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>  // include this to get main(), otherwise the compiler will complain



BOOST_AUTO_TEST_CASE ( are_equal ) {

    // Check for a throw if the dimensions aren't compatible
    Eigen::Tensor<double, 4> M (2, 2, 2, 2);
    Eigen::Tensor<double, 4> T (2, 2, 3, 2);

    BOOST_REQUIRE_THROW(cpputil::linalg::areEqual(M, T, 1.0e-6));



}