//
// Created by hugo on 25-11-18.
//

#ifndef PLOX_POPULATION_H
#define PLOX_POPULATION_H

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>

#include "Utils.h"
#include "Population.h"
#include "RenderFactory.h"

#define POP_SIZE 10

class Population {
private:
    std::vector<Individual> buffer;
    unsigned char* fbSource;
public:
    explicit Population(unsigned char* fbSource);
    void NextGeneration();

};


#endif //PLOX_POPULATION_H
