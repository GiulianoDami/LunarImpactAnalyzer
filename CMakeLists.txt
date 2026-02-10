cmake_minimum_required(VERSION 3.10)
project(LunarImpactAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add executable
add_executable(lunar_impact_analyzer
    src/main.cpp
    src/Analyzer.cpp
    src/SampleData.cpp
    src/ImpactDetector.cpp
)

# Include directories
target_include_directories(lunar_impact_analyzer PRIVATE include)

# Compiler-specific options
if(MSVC)
    target_compile_options(lunar_impact_analyzer PRIVATE /W4)
else()
    target_compile_options(lunar_impact_analyzer PRIVATE -Wall -Wextra -O3)
endif()