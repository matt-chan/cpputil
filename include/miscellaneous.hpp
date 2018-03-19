#ifndef CPPUTIL_MISCELLANEOUS_HPP
#define CPPUTIL_MISCELLANEOUS_HPP



#include <string>
#include <functional>



namespace cpputil {


/**
 *  Print the time a function @param function takes to be executed.
 *
 *  Takes a @param method_name that is printed as well.
 */
void printExecutionTime(const std::string& method_name, const std::function<void()>& function);


}  // namespace cpputil



#endif  // CPPUTIL_MISCELLANEOUS_HPP
