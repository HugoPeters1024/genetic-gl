#include <iostream>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    GLFWwindow* window;
    std::cout << "Hello, World!" << argv[1] << std::endl;
    if(!glfwInit()) return 2;

    if (!glfwInit()) return -2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Demo", nullptr, nullptr);

    if (!window) return -1;
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // Enable vsync
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}