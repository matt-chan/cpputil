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
#include "io.hpp"

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>



namespace cpputil {
namespace io {


/**
 *  Read a vector from a given @param filename line by line and add the elements to the given vector @param v.
 */
void readVectorFromFile(const std::string& filename, Eigen::VectorXd& v) {

    v.setZero();

    std::ifstream file (filename);
    size_t index = 0;
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> splitted_line;  // create a container for the line to be split in

            // Split the line on any whitespace or tabs.
            boost::split(splitted_line, line, boost::is_any_of(" \t"), boost::token_compress_on);

            if (splitted_line.size() != 1) {
                throw std::runtime_error("Found a line that doesn't contain exactly 1 field delimited by whitespace.");
            }

            auto value = std::stod(splitted_line[0]);
            v(index) = value;

            ++index;
        }

        file.close();
    } else {
        throw std::runtime_error("Cannot open the given file. Maybe you specified a wrong path?");
    }
}


/**
 *  Read an array from a given @param: filename line by line, and add the elements to the given matrix @param: M.
 */
void readArrayFromFile(const std::string& filename, Eigen::MatrixXd& M) {

    M.setZero();  // make sure that the given matrix is initialized to zero values before reading in

    std::ifstream file (filename);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> splitted_line;  // create a container for the line to be split in

            // Split the line on any whitespace or tabs.
            boost::split(splitted_line, line, boost::is_any_of(" \t"), boost::token_compress_on);

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
 *  Read an array from a given @param: filename line by line, and add the elements to the given rank-4 tensor @param: T.
 */
void readArrayFromFile(const std::string& filename, Eigen::Tensor<double, 4>& T) {

    T.setZero();  // make sure that the given tensor is initialized to zero values before reading in

    std::ifstream file (filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> splitted_line;  // create a container for the line to be split in

            // Split the line on any whitespace or tabs.
            boost::split(splitted_line, line, boost::is_any_of(" \t"), boost::token_compress_on);

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
 *  Print the contents of a matrix @param M in a fashionable way
 */
void print(const Eigen::MatrixXd& M) {

    for (size_t i = 0; i < M.rows(); i++) {
        for (size_t j = 0; j < M.cols(); j++) {
            std::cout << i << ' ' << j << "  " << M(i,j) << std::endl;
        }
    }
}


/**
 *  Print the contents of a matrix @param M to the @param output_filestream
 */
void print(const Eigen::MatrixXd& M, std::ofstream& output_filestream) {

    for (size_t i = 0; i < M.rows(); i++) {
        for (size_t j = 0; j < M.cols(); j++) {
            output_filestream << i << ' ' << j << "  " << M(i,j) << std::endl;
        }
    }
}


/**
 *  Print the contents of a rank-four tensor @param: T in a fashionable way.
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


/**
 *  Print the contents of a rank-four tensor @param: T to the @param output_filestream
 */
void print(const Eigen::Tensor<double, 4>& T, std::ofstream& output_filestream) {

    auto dim1 = static_cast<size_t>(T.dimension(0));
    auto dim2 = static_cast<size_t>(T.dimension(1));
    auto dim3 = static_cast<size_t>(T.dimension(2));
    auto dim4 = static_cast<size_t>(T.dimension(3));

    for (size_t i = 0; i < dim1; i++) {
        for (size_t j = 0; j < dim2; j++) {
            for (size_t k = 0; k < dim3; k++) {
                for (size_t l = 0; l < dim4; l++) {
                    output_filestream << i << ' ' << j << ' ' << k << ' ' << l << "  " << T(i,j,k,l) << std::endl;
                }
            }
        }
    }
}



}  // namespace io
}  // namespace cpputil
