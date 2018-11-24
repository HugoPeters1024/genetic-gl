cmake_minimum_required(VERSION 3.10)
project(plox)

set(CMAKE_CXX_STANDARD 14)

add_executable(plox main.cpp VertexBuffer.cpp VertexBuffer.h Program.cpp Program.h Individual.h Utils.cpp Utils.h Individual.cpp Individual.h)
target_link_libraries(plox glfw OpenGL)