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


}  // namespace linalg
}  // namespace cpputil



#endif  // CPPUTIL_LINALG_HPP
