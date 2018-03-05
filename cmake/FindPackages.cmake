# In this CMake file, we will find all required packages


# Find the boost package - needed for unittests
find_package(Boost REQUIRED)

# Find the Eigen3 package
# Options to find this package from (http://eigen.tuxfamily.org/dox/TopicCMakeGuide.html)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
