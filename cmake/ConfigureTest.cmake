# In this CMake file, we will include header files and link to libraries for a given test source

# Include this project
target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_INCLUDE_FOLDER})
target_link_libraries(${TEST_NAME} PRIVATE ${LIBRARY_NAME})

# Include Boost
target_include_directories(${TEST_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${TEST_NAME} PRIVATE ${Boost_LIBRARIES})

# Include Eigen3
target_link_libraries(${TEST_NAME} PUBLIC Eigen3::Eigen)

