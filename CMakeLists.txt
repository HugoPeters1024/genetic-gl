cmake_minimum_required(VERSION 3.10)
project(plox)

set(CMAKE_CXX_STANDARD 14)
# ENABLE INTEL AVX SUPPORT
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 - ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -mavx -Ofast -march=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -O3")

add_executable(plox main.cpp VertexBuffer.cpp VertexBuffer.h Program.cpp Program.h Individual.h Utils.cpp Utils.h Individual.cpp Individual.h RenderFactory.cpp RenderFactory.h Population.cpp Population.h)
target_link_libraries(plox glfw OpenGL)