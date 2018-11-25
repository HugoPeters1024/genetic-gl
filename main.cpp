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

static VertexBufferUv vbQuad;
static VertexBufferColor vbTriangles;
static Program shader;
static std::vector<unsigned char> fbSource;
float iTime = 0.0f;
double prevScore = std::numeric_limits<double>::max();
Individual* boi;


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
    fbSource = std::vector<unsigned char>(static_cast<unsigned long>(width * height * 4L));
    for(int i=0; i<fbSource.capacity(); i+=4)
    {
        fbSource[i+0] = (char)255;
        fbSource[i+1] = (char)255;
        fbSource[i+2] = (char)255;
        fbSource[i+3] = (char)255;
    }
    shader = Program(vertexShaderSource, fragmentShaderSource);
    boi = new Individual();
}

double GetScore()
{
    size_t size = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(char) * 3;
    unsigned char* data = (unsigned char*)malloc(size);
    glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_BYTE, data);
    unsigned long sum = 0;
    for(int y=0; y<SCREEN_HEIGHT; y++)
    {
        for(int x=0; x<SCREEN_WIDTH*3; x+=3)
        {
            long diff;
            diff = data[x + y * SCREEN_WIDTH + 0] - fbSource[x + y * SCREEN_WIDTH + 0];
            sum += diff * diff;
            diff = data[x + y * SCREEN_WIDTH + 1] - fbSource[x + y * SCREEN_WIDTH + 1];
            sum += diff * diff;
            diff = data[x + y * SCREEN_WIDTH + 2] - fbSource[x + y * SCREEN_WIDTH + 2];
            sum += diff * diff;
        }
    }
    free(data);
    return sqrt(sum);
}

void render(int width, int height)
{
    glFinish();
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    shader.setupDraw();
    glUniform1f(0, iTime);

    Individual* mutant = new Individual(boi->Mutate());
    RenderFactory::RenderIndividual(mutant);
    double score = GetScore();
    if (score < prevScore) {
        printf("%f\n", score);
        prevScore = score;
        std::swap(boi, mutant);
    }
    delete(mutant);
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

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Genetic GL", nullptr, nullptr);

    if (!window) return -1;
    glfwMakeContextCurrent(window);

    glDebugMessageCallback(reportError, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // Enable vsync
    glfwSwapInterval(0);

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