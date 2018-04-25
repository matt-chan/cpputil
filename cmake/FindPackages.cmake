# In this CMake file, we will find all required packages


# Find Boost
find_package(Boost REQUIRED)

# Find Eigen3 (through the supplied FindEigen3.cmake file
find_package(Eigen3 3.3.4 REQUIRED)
