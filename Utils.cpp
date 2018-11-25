//
// Created by hugo on 24-11-18.
//


#include "Utils.h"

float Utils::randomf() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float Utils::randomNonUniformf() {
    float r = randomf() * 2 - 1;
    if (r < 0)
        return -std::sqrt(-r);
    else
        return std::sqrt(r);
}

double Utils::GetScore(unsigned char* fbSource)
{
    size_t size = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(char) * 3;
    auto data = (unsigned char*)malloc(size);
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

GLFWwindow* Utils::window = nullptr;