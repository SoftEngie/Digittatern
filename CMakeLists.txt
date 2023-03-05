cmake_minimum_required(VERSION 3.10)
project(Digitattern VERSION 1.0)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Enable testing
enable_testing()

# Download and configure Google Test framework
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Add main executable
file(GLOB SOURCES "src/*.cpp")
add_executable(digitattern ${SOURCES})
target_include_directories(digitattern PRIVATE "include")
target_link_libraries(digitattern ${OpenCV_LIBS})

add_custom_command(
  TARGET digitattern POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:digitattern>/resources
)
# Add test
file(GLOB TEST_SOURCES "test/*.cpp")
file(GLOB SOURCES_EXCEPT_MAIN "src/*.cpp")
list(FILTER SOURCES_EXCEPT_MAIN EXCLUDE REGEX "src/main.cpp")
add_executable(run_tests ${TEST_SOURCES} ${SOURCES_EXCEPT_MAIN} )
target_include_directories(run_tests PRIVATE "include")
target_link_libraries(run_tests ${OpenCV_LIBS} gtest_main)
add_test(NAME run_tests COMMAND run_tests)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Set project properties
set_property(TARGET digitattern PROPERTY CXX_STANDARD 17)
set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)
set_property(TARGET digitattern PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET digitattern PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET run_tests PROPERTY CXX_STANDARD_REQUIRED ON)

# Set install directories
install(TARGETS digitattern DESTINATION bin)
install(FILES "README.md" DESTINATION share/digitattern)
