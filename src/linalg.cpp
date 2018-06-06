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


/**
 *  Given a square matrix @param M, @return the strictly lower triangular matrix (i.e. without the diagonal elements) as a
 *  vector in column-major form.
 *
 *          1       -> (1, 2, 3)
 *          2   3
 */
Eigen::VectorXd strictLowerTriangle(const Eigen::MatrixXd& M) {

    if (M.cols() != M.rows()) {
        throw std::invalid_argument("The given matrix is not square.");
    }

    auto K = static_cast<size_t>(M.cols());  // the dimension of the matrix
    Eigen::VectorXd m = Eigen::VectorXd::Zero((K*(K-1)/2));  // strictly lower triangle has K(K-1)/2 parameters

    size_t vector_index = 0;
    for (size_t q = 0; q < K; q++) {
        for (size_t p = q+1; p < K; p++) {
            m(vector_index) = M(p,q);
            vector_index++;
        }
    }

    return m;
}


/**
 *  Reduce a rank-4 tensor @param T to and @return a 2-dimensional matrix
 *
 *  The elements of the tensor @param T are found the matrix such that
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
    for (size_t i = 0; i < dims[0]; i++) {
        for (size_t j = 0; j < dims[1]; j++) {
            for (size_t k = 0; k < dims[2]; k++) {
                for (size_t l = 0; l < dims[3]; l++) {
                    size_t m = i + dims[0] * j;
                    size_t n = k + dims[2] * l;

                    M(m,n) = T(i,j,k,l);
                }
            }
        }
    }

    return M;
}


}  // namespace linalg
}  // namespace cpputil
