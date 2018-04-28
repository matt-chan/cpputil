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
#ifndef CPPUTIL_IO_HPP
#define CPPUTIL_IO_HPP


#include <string>

#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace io {


/**
 *  Read a vector from a given @param filename line by line and add the elements to the given vector @param v.
 */
void readVectorFromFile(const std::string& filename, Eigen::VectorXd& v);

/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given matrix @param: M.
 */
void readArrayFromFile(const std::string& filename, Eigen::MatrixXd& M);

/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given rank-4 tensor @param: T.
 */
void readArrayFromFile(const std::string& filename, Eigen::Tensor<double, 4>& T);

/**
 *  Print the contents of a rank-four tensor @param: T in a fashionable way.
 */
void print(const Eigen::Tensor<double, 4>& T);


}  // namespace io
}  // namespace cpputil



#endif  // CPPUTIL_IO_HPP
