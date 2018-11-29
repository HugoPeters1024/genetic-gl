#include <iostream>
#include <math.h>
#include <fstream>
#include <limits>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#define POP_SIZE 10

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>


#include "VertexBuffer.h"
#include "Program.h"
#include "Utils.h"
#include "Individual.h"
#include "RenderFactory.h"
#include "Population.h"

static VertexBufferUv vbQuad;
static VertexBufferColor vbTriangles;
static Program shader;
static float* fbSource;
float iTime = 0.0f;
double prevScore = std::numeric_limits<double>::max();
Individual* boi;
Population* population;


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


void setup(int width, int height)
{
    std::cout << "Setting things up" << std::endl;
    RenderFactory::Startup();
    fbSource = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float) * 4);

    char* file = const_cast<char *>("monalisa.bmp");
    auto image = Utils::ReadBMP(file);
    for(int i=0, j=0; i<SCREEN_WIDTH * SCREEN_HEIGHT * 3; i+=3, j+=4)
    {
        fbSource[j + 0] = (float)image[i + 0] / 255.0f;
        fbSource[j + 1] = (float)image[i + 1] / 255.0f;
        fbSource[j + 2] = (float)image[i + 2] / 255.0f;
        fbSource[j + 3] = 1.0f;
   //  fbSource[j + 0] = (float)j / (SCREEN_HEIGHT * SCREEN_WIDTH * 4);
    // fbSource[j + 1] = (float)j / (SCREEN_HEIGHT * SCREEN_WIDTH * 4) * -1 + 1;
     // fbSource[j + 2] = 0;
       printf("%f\n", fbSource[j + 0]);
    }

    shader = Program(vertexShaderSource, fragmentShaderSource);
    boi = new Individual();
    population = new Population(fbSource);
}

void render(int width, int height)
{
    for(int i=0; i<POP_SIZE; i++) {
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        shader.setupDraw();
        glUniform1f(0, iTime);

        population->NextGeneration();
    }
}


void reportError(GLenum, GLenum, GLuint, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "%s\n", message);

    if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) abort();
}

int main(int argc, char** argv) {
    if(!glfwInit()) return 2;

    if (!glfwInit()) return -2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Utils::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Genetic GL", nullptr, nullptr);

    if (!Utils::window) return -1;
    glfwMakeContextCurrent(Utils::window);

    glDebugMessageCallback(reportError, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    int width, height;
    glfwGetFramebufferSize(Utils::window, &width, &height);

    // Enable vsync
    glfwSwapInterval(0);

    setup(width, height);

    while(!glfwWindowShouldClose(Utils::window))
    {
        render(width, height);
        glfwSwapBuffers(Utils::window);
        glfwPollEvents();
        iTime += 0.01f;
    }
    return 0;
}