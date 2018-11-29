//
// Created by hugo on 24-11-18.
//

#ifndef PLOX_UTILS_H
#define PLOX_UTILS_H

#include <cstdlib>
#include <math.h>
#include <vector>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 184
#define SCREEN_HEIGHT 275

class Utils {
public:
    static GLFWwindow* window;

    static float randomf();
    static double randomlf();
    static float randomNonUniformf();
    static double GetScore(float* fbSource);
    static unsigned char* ReadBMP(char* filename);
};


#endif //PLOX_UTILS_H
