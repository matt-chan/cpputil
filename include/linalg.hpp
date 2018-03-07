#ifndef CPPUTIL_LINEAR_ALGEBRA_HPP
#define CPPUTIL_LINEAR_ALGEBRA_HPP


#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace linalg {


/**
 *  Return if two rank-4 tensors @param: M and @param: T are approximately equal with respect to a @param: tolerance
 *
 *  This function is implemented because Eigen::Tensor does not have an isApprox yet.
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, const double tolerance);

/** Check if two sets of eigenvalues are equal
 */
bool areEqualEigenvalues(Eigen::VectorXd eigenvalues1, Eigen::VectorXd eigenvalues2, double tolerance);

/** Check if two eigenvectors are equal. This is the case if they are equal up to their sign.
 */
bool areEqualEigenvectors(Eigen::VectorXd eigenvectors1, Eigen::VectorXd eigenvectors2, double tolerance);

/** Check if two sets of eigenvectors are equal.
 */
bool areEqualSetsOfEigenvectors(Eigen::MatrixXd evecs1, Eigen::MatrixXd evecs2, double tolerance);



}  // namespace linalg
}  // namespace cpputil



#endif // CPPUTIL_LINEAR_ALGEBRA_HPP
