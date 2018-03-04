#ifndef CPPUTIL_LINEAR_ALGEBRA_HPP
#define CPPUTIL_LINEAR_ALGEBRA_HPP


#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace linalg {


/** Return if two rank-4 tensors are approximately equal
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, const double tolerance);


}  // namespace linalg
}  // namespace cpputil



#endif // CPPUTIL_LINEAR_ALGEBRA_HPP
