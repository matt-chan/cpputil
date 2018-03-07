#ifndef CPPUTIL_IO_HPP
#define CPPUTIL_IO_HPP


#include <string>

#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace io {


/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given matrix @param: M
 */
void readArrayFromFile(std::string filename, Eigen::MatrixXd& M);

/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given rank-4 tensor  @param: T
 */
void readArrayFromFile(std::string filename, Eigen::Tensor<double, 4>& M);

/**
 *  Print the contents of a rank-four tensor @param: T in a fashionable way
 */
void print(const Eigen::Tensor<double, 4>& T);



}  // namespace io
}  // namespace cpputil



#endif // CPPUTIL_IO_HPP
