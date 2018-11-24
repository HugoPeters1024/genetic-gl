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