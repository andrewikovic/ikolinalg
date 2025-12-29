cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

# 1. Create a library from our source files
add_library(MyLibrary src/my_lib.cpp)

# 2. Tell the library where its headers are
# PUBLIC means anything linking to this library also gets this include path
target_include_directories(MyLibrary PUBLIC include)

# 3. Create the executable
add_executable(MyApp src/main.cpp)

# 4. Link the library to the executable
target_link_libraries(MyApp PRIVATE MyLibrary)

message(STATUS "Using compiler: ${CMAKE_CXX_COMPILER_ID}")