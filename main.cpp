#include <iostream>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "Program.h"

static VertexBuffer vbQuad;
static Program shader;
float iTime = 0.0f;


static float vsQuad[] = {
   1.0f, -1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
  -1.0f, -1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
};
static float vsUnitUvs[] = {
        1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f, -1.0f,
        -1.0f,  1.0f,
};

static const char* vertexShaderSource = R"(
#version 420
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

void main()
{
    gl_Position = vec4(aPos.xyz, 1.0);
}
)";

static const char* fragmentShaderSource = R"(
#version 420
#extension GL_ARB_explicit_uniform_location : enable
layout(location = 0) out vec4 frag_color;
layout(location = 0) uniform float iTime;
void main()
{
    frag_color = vec4(0,0,0.2f,0);
}
)";


void setup(int width, int height)
{
    std::cout << "Setting things up" << std::endl;
    shader = Program(vertexShaderSource, fragmentShaderSource);
    vbQuad = VertexBuffer(
            std::begin(vsQuad), std::end(vsQuad),
            std::begin(vsUnitUvs), std::end(vsUnitUvs),
            GL_TRIANGLE_STRIP);
}

void render(int width, int height)
{
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.setupDraw();
    glUniform1f(0, iTime);
    vbQuad.draw();
}

void reportError(GLenum, GLenum, GLuint, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "%s\n", message);

    if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) abort();
}

int main(int argc, char** argv) {
    GLFWwindow* window;

    if(!glfwInit()) return 2;

    if (!glfwInit()) return -2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Demo", nullptr, nullptr);


    if (!window) return -1;
    glfwMakeContextCurrent(window);

    glDebugMessageCallback(reportError, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // Enable vsync
    glfwSwapInterval(1);

    setup(width, height);

    while(!glfwWindowShouldClose(window))
    {
        render(width, height);
        glfwSwapBuffers(window);
        glfwPollEvents();
        iTime += 0.01f;
    }
    return 0;
}