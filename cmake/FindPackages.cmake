# In this CMake file, we will find all required packages


# Find Boost.
find_package(Boost REQUIRED)

# Find Eigen3 (see http://eigen.tuxfamily.org/dox/TopicCMakeGuide.html).
find_package(Eigen3 3.3.4 REQUIRED)
