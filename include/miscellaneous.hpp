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
#ifndef CPPUTIL_MISCELLANEOUS_HPP
#define CPPUTIL_MISCELLANEOUS_HPP



#include <string>
#include <functional>



namespace cpputil {


/**
 *  Print the time a function takes to be executed
 *
 *  @param function         the function call to be made
 *  @param method_name      the name of function that is to be executed
 */
void printExecutionTime(const std::string& method_name, const std::function<void()>& function);


}  // namespace cpputil



#endif  // CPPUTIL_MISCELLANEOUS_HPP
