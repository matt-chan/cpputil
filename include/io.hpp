#ifndef CPPUTIL_IO_HPP
#define CPPUTIL_IO_HPP


#include <string>

#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>



namespace cpputil {
namespace io {


/** Read an array from a given filename line by line, and add the elements to a given matrix (rank-2 tensor)
*/
void readArrayFromFile(const std::string& filename, Eigen::MatrixXd& M);

/** Read an array from a given filename line by line, and add the elements to a given tensor (rank-4 tensor)
*/
void readArrayFromFile(const std::string& filename, Eigen::Tensor<double, 4>& M);

/** Print the contents of a rank-four tensor in a fashionable way
 */
void print(const Eigen::Tensor<double, 4>& T);


}  // namespace io
}  // namespace cpputil



#endif // CPPUTIL_IO_HPP
