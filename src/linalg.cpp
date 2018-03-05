#include "linalg.hpp"


namespace cpputil {
namespace linalg {


/** Return if two rank-4 tensors are approximately equal
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, const double tolerance){
    auto dim = M.dimension(0);

    // Since Eigen::Tensor doesn't have an isApprox yet, we will check every pair of values manually
    for (int i = 0; i < dim ; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                for (int l = 0; l < dim; l++) {
                    if (std::abs(M(i,j,k,l) - T(i,j,k,l)) > tolerance) {
                        return false;
                    }
                }
            }
        }
    } // rank-4 tensor traversing
    return true;
}


/** Check if two sets of eigenvalues are equal
 */
bool areEqualEigenvalues(Eigen::VectorXd evals1, Eigen::VectorXd evals2, double tol) {
    return evals1.isApprox(evals2, tol);
}


/** Check if two eigenvectors are equal. This is the case if they are equal up to their sign.
 */
bool areEqualEigenvectors(Eigen::VectorXd evec1, Eigen::VectorXd evec2, double tol) {
    return (evec1.isApprox(evec2, tol) || evec1.isApprox(-evec2, tol));
}


/** Check if two sets of eigenvectors are equal.
 */
bool areEqualSetsOfEigenvectors(Eigen::MatrixXd evecs1, Eigen::MatrixXd evecs2, double tol) {
    auto dim = evecs1.cols();
    for (size_t i = 0; i < dim; i++) {
        if (!areEqualEigenvectors(evecs1.col(i), evecs2.col(i), tol)) {
            return false;
        }
    }
    return true;
}


}  // namespace linalg
}  // namespace cpputil

