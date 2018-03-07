#include "io.hpp"

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>


namespace cpputil {
namespace io {


/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given matrix @param: M.
 */
void readArrayFromFile(std::string filename, Eigen::MatrixXd& M) {

    M.setZero();  // make sure that the given matrix is initialized to zero values before reading in

    std::ifstream file (filename);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> splitted_line;  // create a container for the line to be split in
            boost::split(splitted_line, line, boost::is_any_of(" \t"), boost::token_compress_on);  // split the line on any whitespace or tabs

            if (splitted_line.size() != 3) {
                throw std::runtime_error("Found a line that doesn't contain exactly 3 fields delimited by whitespace.");
            }

            auto i = std::stoi(splitted_line[0]);
            auto j = std::stoi(splitted_line[1]);
            auto value = std::stod(splitted_line[2]);

            M(i,j) = value;
        }

        file.close();
    } else {
        throw std::runtime_error("Cannot open the given file. Maybe you specified a wrong path?");
    }
}


/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given rank-4 tensor  @param: T
 */
void readArrayFromFile(std::string filename, Eigen::Tensor<double, 4>& T) {

    T.setZero();  // make sure that the given tensor is initialized to zero values before reading in

    std::ifstream file (filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> splitted_line;  // create a container for the line to be split in
            boost::split(splitted_line, line, boost::is_any_of(" \t"), boost::token_compress_on);  // split the line on any whitespace or tabs

            if (splitted_line.size() != 5) {
                throw std::runtime_error("Found a line that doesn't contain exactly 5 fields delimited by whitespace.");
            }

            auto i = std::stoi(splitted_line[0]);
            auto j = std::stoi(splitted_line[1]);
            auto k = std::stoi(splitted_line[2]);
            auto l = std::stoi(splitted_line[3]);
            auto value = std::stod(splitted_line[4]);

            T(i,j,k,l) = value;
        }

        file.close();
    } else {
        throw std::runtime_error("Cannot open the given file. Maybe you specified a wrong path?");
    }
}


/**
 *  Print the contents of a rank-four tensor @param: T in a fashionable way
 */
void print(const Eigen::Tensor<double, 4>& T) {
    auto dim1 = static_cast<size_t>(T.dimension(0));
    auto dim2 = static_cast<size_t>(T.dimension(1));
    auto dim3 = static_cast<size_t>(T.dimension(2));
    auto dim4 = static_cast<size_t>(T.dimension(3));

    for (size_t i = 0; i < dim1; i++) {
        for (size_t j = 0; j < dim2; j++) {
            for (size_t k = 0; k < dim3; k++) {
                for (size_t l = 0; l < dim4; l++) {
                    std::cout << i << ' ' << j << ' ' << k << ' ' << l << "  " << T(i,j,k,l) << std::endl;
                }
            }
        }
    }
}



}  // namespace io
}  // namespace cpputil
