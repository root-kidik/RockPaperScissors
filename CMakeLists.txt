cmake_minimum_required(VERSION 3.25)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(RockPaperScissors)

include(${PROJECT_BINARY_DIR}/generators/conan_toolchain.cmake)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

if(${PROJECT_NAME}_ENABLE_TESTS)
    enable_testing()
    include(CTest)

    add_subdirectory(tests/unit)
    add_subdirectory(tests/integration)
endif()
