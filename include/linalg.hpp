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

/**
 *  Check if two sets of eigenvalues @param: eigenvalues1 and @param: eigenvalues2 are equal within a given tolerance
 */
bool areEqualEigenvalues(const Eigen::VectorXd& eigenvalues1, const Eigen::VectorXd& eigenvalues2, double tolerance);

/**
 *  Check if two eigenvectors @param: eigenvectors1 and @param: eigenvectors2 are equal within a given @param: tolerance
 */
bool areEqualEigenvectors(const Eigen::VectorXd& eigenvectors1, const Eigen::VectorXd& eigenvectors2, double tolerance);

/**
 *  Check if two sets of eigenvectors (columns in @param: eigenvectors1 and @param: eigenvectors2) are equal within a given @param: tolerance
 */
bool areEqualSetsOfEigenvectors(const Eigen::MatrixXd& eigenvectors1, const Eigen::MatrixXd& eigenvectors2, double tolerance);



}  // namespace linalg
}  // namespace cpputil



#endif // CPPUTIL_LINEAR_ALGEBRA_HPP
