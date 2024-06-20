cmake_minimum_required(VERSION 3.5)
project(p3)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Set the C++ Standard (don't modify)
set(CMAKE_CXX_STANDARD 17)

# Set the compiling flags (don't modify)
set(CMAKE_CXX_FLAGS "-Werror -pedantic -Wall -Wextra -Wvla")

include_directories(include)
add_subdirectory(pms)
add_subdirectory(ipa)
