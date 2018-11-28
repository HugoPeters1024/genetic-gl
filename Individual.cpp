//
// Created by hugo on 24-11-18.
//
#include <iostream>
#include <cstdlib>
#include <cstring>


#include "Individual.h"
#include "Utils.h"

Individual::Individual() {
    this->vertices = std::vector<float>(GENOME_SIZE * 3);
    this->colors = std::vector<float>(GENOME_SIZE * 4);
    this->Randomize();
}

Individual::Individual(const Individual &father, const Individual &mother) {
    this->vertices = std::vector<float>(GENOME_SIZE * 3);
    this->colors = std::vector<float>(GENOME_SIZE * 4);
    bool unary = true;
    for(int i=0; i<GENOME_SIZE*3; i+=3 )
    {
        if (Utils::randomf() < CROSS_OVER_RATE) unary = !unary;
        const Individual* src = unary ? &father : &mother;
        this->vertices[i+0] = src->vertices[i+0];
        this->vertices[i+1] = src->vertices[i+1];
        this->vertices[i+2] = src->vertices[i+2];

    }

    for(int j=0; j<GENOME_SIZE*4; j+=4)
    {
        if (Utils::randomf() < CROSS_OVER_RATE) unary = !unary;
        const Individual* src = unary ? &father : &mother;
        this->colors[j+0] = src->colors[j+0];
        this->colors[j+1] = src->colors[j+1];
        this->colors[j+2] = src->colors[j+2];
        this->colors[j+3] = src->colors[j+3];
    }
}

void Individual::Randomize() {
    for(int i=0; i<GENOME_SIZE * 3; i+=3) {
        vertices[i+0] = Utils::randomf() * 2 - 1;
        vertices[i+1] = Utils::randomf() * 2 - 1;
        vertices[i+2] = 1.0f;
    }
    for (int i=0; i<GENOME_SIZE * 4; i+=4) {
        this->colors[i+0] = Utils::randomf();
        this->colors[i+1] = Utils::randomf();
        this->colors[i+2] = Utils::randomf();
        this->colors[i+3] = Utils::randomf() * 0.01f;
    }
}

void Individual::Mutate() {
    for(int i=0; i<GENOME_SIZE * 3; i+=3) {
        if (Utils::randomf() < MUTATION_RATE) this->vertices[i+0] = Utils::randomf() * 2 - 1;
        if (Utils::randomf() < MUTATION_RATE) this->vertices[i+1] = Utils::randomf() * 2 - 1;
    }
    for (int i=0; i<GENOME_SIZE * 4; i+=4) {
        if (Utils::randomf() < MUTATION_RATE) this->colors[i + 0] = Utils::randomf();
        if (Utils::randomf() < MUTATION_RATE) this->colors[i + 1] = Utils::randomf();
        if (Utils::randomf() < MUTATION_RATE) this->colors[i + 2] = Utils::randomf();
        if (Utils::randomf() < MUTATION_RATE) this->colors[i + 3] = Utils::randomf() * 0.5f;
    }
}

Individual::Individual(const Individual* source) {
    this->vertices = std::vector<float>(source->vertices);
    this->colors = std::vector<float>(source->colors);
}

Individual::~Individual() = default;
