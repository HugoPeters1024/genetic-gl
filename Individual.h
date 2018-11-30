//
// Created by hugo on 24-11-18.
//

#include <vector>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include <assert.h>
#include "VertexBuffer.h"

#ifndef PLOX_INDIVIDUAL_H
#define PLOX_INDIVIDUAL_H


// Must be a multiple of three
#define GENOME_SIZE 180
#define MUTATION_RATE 0.005f
#define CROSS_OVER_RATE 0.3f


class Individual {
public:
    std::vector<float> vertices;
    std::vector<float> colors;

    void Randomize();


public:
    Individual();
    Individual(const Individual* source);
    Individual(const Individual &father, const Individual &mother);
    ~Individual();
    void Mutate();
};


#endif //PLOX_INDIVIDUAL_H