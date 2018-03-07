#include "io.hpp"

#include <fstream>
#include <iostream>



namespace cpputil {
namespace io {


/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given matrix @param: M.
 */
void readArrayFromFile(std::string filename, Eigen::MatrixXd& M) {

    std::ifstream file (filename);

    if (file.is_open()) {
        std::string line;

        size_t line_counter = 1;
        while (std::getline(file, line)) {
            std::istringstream is (line);

            int i;
            int j;
            double value;

            is >> i >> j >> value;
            M(i, j) = value;

            line_counter ++;
        }

        file.close();
    } else {
        throw std::runtime_error("Cannot open the given file. Maybe you specified a wrong path?");
    }
}


/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given rank-4 tensor  @param: T
 */
void readArrayFromFile(std::string filename, Eigen::Tensor<double, 4>& M) {
    std::ifstream file (filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream is(line);

            int i;
            int j;
            int k;
            int l;
            float value;

            is >> i >> j >> k >> l >> value;
            M(i, j, k, l) = value;
        }

        file.close();
    } else {
        throw std::runtime_error("Cannot open the given file. Maybe you specified a wrong path?");
    }
}


/** Print the contents of a rank-four tensor in a fashionable way
 */
void print(const Eigen::Tensor<double, 4>& T) {
    auto dim = T.dimension(0);

    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            for (size_t k = 0; k < dim; k++) {
                for (size_t l = 0; l < dim; l++) {
                    std::cout << i << ' ' << j << ' ' << k << ' ' << l << "  " << T(i, j, k, l) << std::endl;
                }
            }
        }
    }
}


}  // namespace io
}  // namespace cpputil
