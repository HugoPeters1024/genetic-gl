#include <iostream>
#include <math.h>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <GLFW/glfw3.h>


#include "VertexBuffer.h"
#include "Program.h"

static VertexBufferUv vbQuad;
static VertexBufferColor vbTriangles;
static Program shader;
float iTime = 0.0f;


static float vsQuad[] = {
   1.0f, -1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
  -1.0f, -1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
};

static std::vector<float> vsTriangles;
static std::vector<float> vsTrianglesCol;

static float vsUnitUvs[] = {
        1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f, -1.0f,
        -1.0f,  1.0f,
};

static const char* vertexShaderSource = R"(
#version 420
#extension GL_ARB_explicit_uniform_location : enable
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec4 aCol;
layout (location = 0) uniform float iTime;

layout (location = 0) out vec3 pos;
layout (location = 1) out vec4 col;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    pos = aPos;
    col = aCol;
}
)";

static const char* fragmentShaderSource = R"(
#version 420
#extension GL_ARB_explicit_uniform_location : enable
layout(location = 0) out vec4 frag_color;
layout(location = 0) uniform float iTime;
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aCol;

void main()
{
    frag_color = aCol;
}
)";


float randomf()
{
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


void setup(int width, int height)
{
    std::cout << "Setting things up" << std::endl;
    shader = Program(vertexShaderSource, fragmentShaderSource);
    vbQuad = VertexBufferUv(
            std::begin(vsQuad), std::end(vsQuad),
            std::begin(vsUnitUvs), std::end(vsUnitUvs),
            GL_TRIANGLE_STRIP);

    for(int i=0; i<200; i++) {
        vsTriangles.push_back(randomf() * 2 - 1);
        vsTriangles.push_back(randomf() * 2 - 1);
        vsTriangles.push_back(1.0f);
        vsTrianglesCol.push_back(randomf());
        vsTrianglesCol.push_back(randomf());
        vsTrianglesCol.push_back(randomf());
        vsTrianglesCol.push_back(randomf());
    }
    vbTriangles = VertexBufferColor(
            vsTriangles.data(), vsTriangles.data() + vsTriangles.capacity(),
            vsTrianglesCol.data(), vsTrianglesCol.data() + vsTrianglesCol.capacity(),
            GL_TRIANGLES);
}

void render(int width, int height)
{
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    using namespace std;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    shader.setupDraw();
    glUniform1f(0, iTime);
   // vbQuad.draw();
    vbTriangles.draw();
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

    window = glfwCreateWindow(720, 720, "Demo", nullptr, nullptr);


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