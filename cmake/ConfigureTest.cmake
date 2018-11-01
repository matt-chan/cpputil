# In this CMake file, we will include header files and link to libraries for a given test source


# Include Boost
target_include_directories(${TEST_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

# Include this project
target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_INCLUDE_FOLDER})
target_link_libraries(${TEST_NAME} PRIVATE ${LIBRARY_NAME} rt)
