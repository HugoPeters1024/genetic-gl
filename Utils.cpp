//
// Created by hugo on 24-11-18.
//


#include <cstdio>
#include <limits>
#include "Utils.h"

static auto frameBuffer = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float) * 4);

float Utils::randomf() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

double Utils::randomlf() {
    return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}


float Utils::randomNonUniformf() {
    float r = randomf() * 2 - 1;
    if (r < 0)
        return -std::sqrt(-r);
    else
        return std::sqrt(r);
}

double Utils::GetScore(float* fbSource) {
    glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_FLOAT, frameBuffer);
    double sum = 0;
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH * 4; x += 4) {
            float diffR = frameBuffer[x + y * SCREEN_WIDTH * 4 + 0] - fbSource[x + y * SCREEN_WIDTH * 4 + 0];
            float diffG = frameBuffer[x + y * SCREEN_WIDTH * 4 + 1] - fbSource[x + y * SCREEN_WIDTH * 4 + 1];
            float diffB = frameBuffer[x + y * SCREEN_WIDTH * 4 + 2] - fbSource[x + y * SCREEN_WIDTH * 4 + 2];
            float diffA = frameBuffer[x + y * SCREEN_WIDTH * 4 + 3] - fbSource[x + y * SCREEN_WIDTH * 4 + 3];
            sum += sqrt(diffR * diffR + diffG * diffG + diffB * diffB + diffA * diffA) / sqrt(4.0);
        }
    }
    return sum;
}

GLFWwindow* Utils::window = nullptr;
