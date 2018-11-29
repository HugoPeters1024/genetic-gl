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
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT* 4; i += 4) {
        float diffR = frameBuffer[i + 0] - fbSource[i + 0];
        float diffG = frameBuffer[i + 1] - fbSource[i + 1];
        float diffB = frameBuffer[i + 2] - fbSource[i + 2];
        float diffA = frameBuffer[i + 3] - fbSource[i + 3];
        float preSum = sqrt(diffR * diffR + diffG * diffG + diffB * diffB + diffA * diffA);
        sum += preSum;
    }
    return sum;
}

GLFWwindow* Utils::window = nullptr;

unsigned char* Utils::ReadBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
    }

    return data;
}
