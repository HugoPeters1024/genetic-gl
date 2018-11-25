//
// Created by hugo on 24-11-18.
//

#include <vector>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>
#include "VertexBuffer.h"

#ifndef PLOX_INDIVIDUAL_H
#define PLOX_INDIVIDUAL_H


#define GENOME_SIZE 40
#define MUTATION_RATE 0.01f
#define CROSS_OVER_RATE 0.30f


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
    Individual Mutate();
};


#endif //PLOX_INDIVIDUAL_H