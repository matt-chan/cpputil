#include "linalg.hpp"



namespace cpputil {
namespace linalg {


/**
 *  @return if two rank-4 tensors @param: M and @param: T are approximately equal with respect to a @param: tolerance.
 *
 *  This function is implemented because Eigen::Tensor does not have an isApprox yet.
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, double tolerance) {

    // Check if the dimensions of the tensors are equal
    const auto& dim_M = M.dimensions();
    const auto& dim_T = T.dimensions();

    for (size_t i = 0; i < 4; i++) {
        if (dim_M[i] != dim_T[i]) {
            throw std::invalid_argument("Cannot compare the two tensors as they have different dimensions.");
        }
    }


    // Check every pair of values
    for (size_t i = 0; i < dim_M[0] ; i++) {
        for (size_t j = 0; j < dim_M[1]; j++) {
            for (size_t k = 0; k < dim_M[2]; k++) {
                for (size_t l = 0; l < dim_M[3]; l++) {
                    if (std::abs(M(i,j,k,l) - T(i,j,k,l)) > tolerance) {
                        return false;
                    }
                }
            }
        }
    }  // rank-4 tensor traversing

    return true;
}


/**
 *  @return if two sets of eigenvalues @param: eigenvalues1 and @param: eigenvalues2 are equal within a given tolerance.
 */
bool areEqualEigenvalues(const Eigen::VectorXd& eigenvalues1, const Eigen::VectorXd& eigenvalues2, double tolerance) {
    return eigenvalues1.isApprox(eigenvalues2, tolerance);
}


/**
 *  @return if two eigenvectors @param: eigenvectors1 and @param: eigenvectors2 are equal within a given
 *  @param: tolerance.
 */
bool areEqualEigenvectors(const Eigen::VectorXd& eigenvectors1, const Eigen::VectorXd& eigenvectors2,
                          double tolerance) {

    //  Eigenvectors are equal if they are equal up to their sign.
    return (eigenvectors1.isApprox(eigenvectors2, tolerance) || eigenvectors1.isApprox(-eigenvectors2, tolerance));
}


/**
 *  @return if two sets of eigenvectors (columns in @param: eigenvectors1 and @param: eigenvectors2) are equal within a
 *  given @param: tolerance.
 */
bool areEqualSetsOfEigenvectors(const Eigen::MatrixXd& eigenvectors1, const Eigen::MatrixXd& eigenvectors2,
                                double tolerance) {

    // Check if the dimensions of the eigenvectors are equal.
    if (eigenvectors1.cols() != eigenvectors2.cols()) {
        throw std::invalid_argument("Cannot compare the two sets of eigenvectors as they have different dimensions.");
    }

    if (eigenvectors1.rows() != eigenvectors2.rows()) {
        throw std::invalid_argument("Cannot compare the two sets of eigenvectors as they have different dimensions.");
    }


    for (size_t i = 0; i < eigenvectors1.cols(); i++) {
        const Eigen::VectorXd eigenvector1 = eigenvectors1.col(i);
        const Eigen::VectorXd eigenvector2 = eigenvectors2.col(i);

        if (!areEqualEigenvectors(eigenvector1, eigenvector2, tolerance)) {
            return false;
        }
    }

    return true;
}


}  // namespace linalg
}  // namespace cpputil
