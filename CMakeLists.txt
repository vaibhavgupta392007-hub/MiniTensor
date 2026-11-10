
cmake_minimum_required(VERSION 3.16)

project(MiniTensor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Build the Tensor library
add_library(tensor
    src/tensor.cpp
)

# Header locations
target_include_directories(tensor PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Demo executable
add_executable(tensor_demo
    examples/demo.cpp
)

target_link_libraries(tensor_demo PRIVATE tensor)

# Test executable
add_executable(tensor_tests
    tests/test_tensor.cpp
)

target_link_libraries(tensor_tests PRIVATE tensor)

enable_testing()
add_test(NAME TensorTests COMMAND tensor_tests)

# Install the library
install(TARGETS tensor
    EXPORT MiniTensorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install public headers
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export the library target
install(EXPORT MiniTensorTargets
    FILE MiniTensorTargets.cmake
    NAMESPACE MiniTensor::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MiniTensor
)



# Generate MiniTensor package configuration
configure_package_config_file(
    cmake/MiniTensorConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MiniTensorConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MiniTensor
)

# Generate package version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MiniTensorConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install package configuration files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MiniTensorConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MiniTensorConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MiniTensor
)
