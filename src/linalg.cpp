// This file is part of GQCG-cpputil.
// 
// Copyright (C) 2017-2018  the GQCG developers
// 
// GQCG-cpputil is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// GQCG-cpputil is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with GQCG-cpputil.  If not, see <http://www.gnu.org/licenses/>.
#include "linalg.hpp"
#include <iostream>



namespace cpputil {
namespace linalg {


/**
 *  @param M            the first tensor
 *  @param T            the other tensor
 *  @param tolerance    the tolerance for element-wise comparison
 *
 *  @return if two rank-4 tensors are approximately equal with respect to a tolerance
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
 *  @param eigenvalues1     the first set of eigenvalues
 *  @param eigenvalues2     the second set of eigenvalues
 *  @param tolerance        the tolerance for comparison
 *
 *  @return if two sets of eigenvalues are equal within a given tolerance
 */
bool areEqualEigenvalues(const Eigen::VectorXd& eigenvalues1, const Eigen::VectorXd& eigenvalues2, double tolerance) {
    return eigenvalues1.isApprox(eigenvalues2, tolerance);
}


/**
 *  @param eigenvector1     the first eigenvector
 *  @param eigenvector2     the second eigenvector
 *  @param tolerance        the tolerance for comparison
 *
 *  @return if two eigenvectors are equal within a given tolerance
 */
bool areEqualEigenvectors(const Eigen::VectorXd& eigenvector1, const Eigen::VectorXd& eigenvector2,
                          double tolerance) {

    //  Eigenvectors are equal if they are equal up to their sign.
    return (eigenvector1.isApprox(eigenvector2, tolerance) || eigenvector1.isApprox(-eigenvector2, tolerance));
}


/**
 *  @param eigenvectors1        the first set of eigenvectors
 *  @param eigenvectors2        the second set of eigenvectors
 *  @param tolerance            the tolerance for comparison
 *
 *  @return if two sets of eigenvectors are equal within a given tolerance
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


/**
 *  @param M        the matrix
 *
 *  @return the strictly lower triangular matrix (i.e. without the diagonal elements) as a vector in column-major form
 *
 *          5
 *          1   5       -> (1, 2, 3)
 *          2   3   5
 */
Eigen::VectorXd strictLowerTriangle(const Eigen::MatrixXd& M) {

    if (M.cols() != M.rows()) {
        throw std::invalid_argument("The given matrix is not square.");
    }

    auto K = static_cast<size_t>(M.cols());  // the dimension of the matrix
    Eigen::VectorXd m = Eigen::VectorXd::Zero((K*(K-1)/2));  // strictly lower triangle has K(K-1)/2 parameters

    size_t vector_index = 0;
    for (size_t q = 0; q < K; q++) {  // "column major" ordering for, so we do p first, then q
        for (size_t p = q+1; p < K; p++) {  // strict lower triangle means p > q
            m(vector_index) = M(p,q);
            vector_index++;
        }
    }

    return m;
}


/**
 *  @param a        the lower triangle of the matrix in column major form
 *
 *  @return a matrix in which the lower triangle is filled with the given vector, and the other elements are set to zero
 */
Eigen::MatrixXd fillStrictLowerTriangle(const Eigen::VectorXd& a) {

    // Check for valid input
    auto N = static_cast<size_t>(a.size());  // dimension of the vector
    double K_ = 0.5 + 0.5 * std::sqrt(1 + 8*N);  // dimension of the matrix
    if (std::abs(K_ - std::floor(K_)) > 1.0e-12) {  // if K is not an integer, within the given precision, i.e. N is not a triangular number
        throw std::invalid_argument("The given vector cannot be stored in the strict lower triangle of a matrix.");
    }

    // After the input checking, we are safe to cast K into size_t
    auto K = static_cast<size_t>(K_);
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(K, K);


    size_t column_index = 0;
    size_t row_index = column_index + 1;  // fill the lower triangle
    for (size_t vector_index = 0; vector_index < N; vector_index++) {
        A(row_index,column_index) = a(vector_index);

        if (row_index == K-1) {  // -1 because of computers
            column_index++;
            row_index = column_index + 1;
        } else {
            row_index++;
        }
    }
    return A;
}



/**
 *  @param T        the rank-4 tensor
 *
 *  @return the reduced form of a rank-4 tensor. The elements of the tensor are put into the matrix such that
 *      M(m,n) = T(i,j,k,l)
 *
 *  in which
 *      m is calculated from i and j in a column-major way
 *      n is calculated from k and l in a column-major way
 */
Eigen::MatrixXd toMatrix(const Eigen::Tensor<double, 4>& T) {

    // Initialize the resulting matrix
    const auto& dims = T.dimensions();
    Eigen::MatrixXd M (dims[0]*dims[1], dims[2]*dims[3]);


    // Calculate the compound indices and bring the elements from the tensor over into the matrix
    size_t row_index = 0;
    for (size_t j = 0; j < dims[1]; j++) {  // "column major" ordering for row_index<-i,j so we do j first, then i
        for (size_t i = 0; i < dims[0]; i++) {  // in column major indices, columns are contiguous, so the first of two indices changes more rapidly

            size_t column_index = 0;
            for (size_t l = 0; l < dims[3]; l++) {  // "column major" ordering for column_index<-k,l so we do l first, then k
                for (size_t k = 0; k < dims[2]; k++) {  // in column major indices, columns are contiguous, so the first of two indices changes more rapidly

                    M(row_index,column_index) = T(i,j,k,l);

                    column_index++;
                }
            }

            row_index++;
        }
    }

    return M;
}


/**
 *  @param T        a rank-4 tensor with equal dimensions
 *
 *  @return the strict "lower triangle" as a matrix in column major form
 *
 *  The matrix indices (m,n) come from the tensor indices (i,j,k,l) and are such that:
 *      - m is compounded in a column major way from i and j, with the restriction i>j
 *      - n is compounded in a column major way from k and l, with the restriction k>l
 */
Eigen::MatrixXd strictLowerTriangle(const Eigen::Tensor<double, 4>& T) {

    // Check for invalid input
    const auto& dims = T.dimensions();

    auto K = static_cast<size_t> (dims[0]);
    for (size_t i = 1; i < 4; i++) {
        if (K != dims[i]) {
            throw std::invalid_argument("The given tensor does not have equal dimensions in each rank.");
        }
    }


    // Initialize the resulting matrix
    Eigen::MatrixXd M (K*(K-1)/2, K*(K-1)/2);


    // Calculate the compound indices and bring the elements from the tensor over into the matrix
    size_t row_index = 0;
    for (size_t j = 0; j < K; j++) {  // "column major" ordering for row_index<-i,j so we do j first, then i
        for (size_t i = j+1; i < K; i++) {  // in column major indices, columns are contiguous, so the first of two indices changes more rapidly
                                                  // require i > j for "lower triangle"

            size_t column_index = 0;
            for (size_t l = 0; l < K; l++) {  // "column major" ordering for column_index<-k,l so we do l first, then k
                for (size_t k = l+1; k < K; k++) {  // in column major indices, columns are contiguous, so the first of two indices changes more rapidly
                                                          // require l > k for "lower triangle"

                    M(row_index,column_index) = T(i,j,k,l);

                    column_index++;
                }
            }

            row_index++;
        }
    }

    return M;
}


}  // namespace linalg
}  // namespace cpputil
