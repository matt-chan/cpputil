#ifndef CPPUTIL_LINEAR_ALGEBRA_HPP
#define CPPUTIL_LINEAR_ALGEBRA_HPP


#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace linalg {


/** Return if two rank-4 tensors are approximately equal
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, const double tolerance);

/** Check if two sets of eigenvalues are equal
 */
bool areEqualEigenvalues(Eigen::VectorXd evals1, Eigen::VectorXd evals2, double tol);

/** Check if two eigenvectors are equal. This is the case if they are equal up to their sign.
 */
bool areEqualEigenvectors(Eigen::VectorXd evec1, Eigen::VectorXd evec2, double tol);

/** Check if two sets of eigenvectors are equal.
 */
bool areEqualSetsOfEigenvectors(Eigen::MatrixXd evecs1, Eigen::MatrixXd evecs2, double tol);


}  // namespace linalg
}  // namespace cpputil



#endif // CPPUTIL_LINEAR_ALGEBRA_HPP
