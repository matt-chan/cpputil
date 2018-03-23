#include "miscellaneous.hpp"



#include <chrono>
#include <iostream>



namespace cpputil {


/**
 *  Print the time a function @param function takes to be executed.
 *
 *  Takes a @param method_name that is printed as well.
 */
void printExecutionTime(const std::string& method_name, const std::function<void()>& function) {

    // High resolution clock example from (https://stackoverflow.com/a/12231232/7930415).
    auto start = std::chrono::high_resolution_clock::now();

    function();

    auto stop = std::chrono::high_resolution_clock::now();


    // Print the timings.
    std::cout << method_name << " took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
              << " milliseconds to complete." << std::endl;
}


}  // namespace cpputil
