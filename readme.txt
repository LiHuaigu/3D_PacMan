
The program will run with multi-threading, please compile all the .cpp files

Operating System:
Mac OS Mojave 10.14.6


Development Environment:
Clion 2019.3.5
CMake 3.15.3
g++ -10
Bundled GDB 8.0.1


Third-party library:
CMakeLists.txt:
cmake_minimum_required(VERSION 3.15)
project(Final_Project)

set(CMAKE_CXX_STANDARD 14)
set(GLEW_H /usr/local/Cellar/glew/2.2.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include/GLFW)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H})

set(GLEW_LINK /usr/local/Cellar/glew/2.2.0/lib/libGLEW.2.2.0.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})
set(SOURCE_FILES "main.cpp" ECE_Pacman.cpp ECE_Pacman.h ECE_Ghost.cpp ECE_Ghost.h ECE_Maze.h ECE_Maze.cpp)
add_executable(Final_Project ${SOURCE_FILES})


if (APPLE)
    target_link_libraries(Final_Project "-framework OpenGL")
    target_link_libraries(Final_Project "-framework GLUT")
endif()