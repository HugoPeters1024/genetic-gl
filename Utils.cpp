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

    __m256 result = _mm256_set1_ps(0);
    for(int i=0; i<SCREEN_WIDTH * SCREEN_HEIGHT * 4; i+=8)
    {
        __m256 frameBufferAVX = _mm256_loadu_ps(frameBuffer + i);
        __m256 fbSourceAVX = _mm256_loadu_ps(fbSource + i);

        // Substracted diff
        __m256 diff = _mm256_sub_ps(frameBufferAVX, fbSourceAVX);

        // Square the values
        __m256 sqr = _mm256_mul_ps(diff, diff);

        // Sum up the result;
        result = _mm256_add_ps(sqr, result);
    }

    // Extract both halves
    __m128 left = _mm256_extractf128_ps(result, 0);
    left[3] = 0;
    __m128 right = _mm256_extractf128_ps(result, 1);
    right[3] = 0;
    __m128 summed = _mm_add_ps(left, right);
    // Calculate prefix sum
    summed = _mm_hadd_ps(summed, summed);
    summed = _mm_hadd_ps(summed, summed);

    // Sum is now in the first register.
    return summed[0];
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


