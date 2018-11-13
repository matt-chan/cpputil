# In this CMake file, we will include the headers and link to the necessary libraries


# Include this project's headers
target_include_directories(${LIBRARY_NAME} PRIVATE ${PROJECT_INCLUDE_FOLDER})

# Include Eigen3
target_include_directories(${LIBRARY_NAME} PRIVATE ${EIGEN3_INCLUDE_DIR})

# Include Boost
target_include_directories(${LIBRARY_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
