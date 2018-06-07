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
#ifndef CPPUTIL_LINALG_HPP
#define CPPUTIL_LINALG_HPP



#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace linalg {


/**
 *  @return if two rank-4 tensors @param: M and @param: T are approximately equal with respect to a @param: tolerance.
 *
 *  This function is implemented because Eigen::Tensor does not have an isApprox yet.
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, double tolerance);

/**
 *  @return if two sets of eigenvalues @param: eigenvalues1 and @param: eigenvalues2 are equal within a given tolerance.
 */
bool areEqualEigenvalues(const Eigen::VectorXd& eigenvalues1, const Eigen::VectorXd& eigenvalues2, double tolerance);

/**
 *  @return if two eigenvectors @param: eigenvectors1 and @param: eigenvectors2 are equal within a given
 *  @param: tolerance.
 */
bool areEqualEigenvectors(const Eigen::VectorXd& eigenvectors1, const Eigen::VectorXd& eigenvectors2, double tolerance);

/**
 *  @return if two sets of eigenvectors (columns in @param: eigenvectors1 and @param: eigenvectors2) are equal within a
 *  given @param: tolerance.
 */
bool areEqualSetsOfEigenvectors(const Eigen::MatrixXd& eigenvectors1, const Eigen::MatrixXd& eigenvectors2,
                                double tolerance);


/**
 *  Given a matrix @param M, @return the strictly lower triangular matrix (i.e. without the diagonal elements) as a
 *  vector in column-major form.
 *
 *          1       -> (1, 2, 3)
 *          2   3
 */
Eigen::VectorXd strictLowerTriangle(const Eigen::MatrixXd& M);


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
Eigen::MatrixXd toMatrix(const Eigen::Tensor<double, 4>& T);


/**
 *  Given a rank-4 with dimensions (K,K,K,K) tensor @param T, @return the strict "lower triangle" as a matrix in column major form
 *  The matrix indices (m,n) come from the tensor indices (i,j,k,l) and are such that:
 *      - m is compounded in a column major way from i and j, with the restriction i>j
 *      - n is compounded in a column major way from k and l, with the restriction k>l
 */
Eigen::MatrixXd strictLowerTriangle(const Eigen::Tensor<double, 4>& T);


}  // namespace linalg
}  // namespace cpputil



#endif  // CPPUTIL_LINALG_HPP
