cmake_minimum_required(VERSION 3.22.1)

project("voicelab_native")

# Configure C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization flags for high-performance DSP
# Note: -ffast-math trades IEEE compliance for performance in audio DSP
# This is intentional for low-latency real-time audio processing
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -funroll-loops")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Add native library
add_library(
    voicelab_native
    SHARED
    native-lib.cpp
    audio_processor.cpp
)

# Find and link required libraries
find_library(log-lib log)
find_library(android-lib android)

# Link libraries
target_link_libraries(
    voicelab_native
    ${log-lib}
    ${android-lib}
)

# Include directories
target_include_directories(
    voicelab_native
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
