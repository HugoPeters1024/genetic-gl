//
// Created by hugo on 24-11-18.
//
#include <iostream>
#include <cstdlib>


#include "Individual.h"
#include "Utils.h"

Individual::Individual() {
    this->vertices = std::vector<float>(GENOME_SIZE * 3);
    this->colors = std::vector<float>(GENOME_SIZE * 4);

    this->Randomize();
    this->vb = VertexBufferColor(
            vertices.data(), vertices.data() + vertices.capacity(),
            colors.data(), colors.data() + vertices.capacity(),
            GL_TRIANGLES);
}

Individual::Individual(const Individual *father, const Individual *mother) {
    this->vertices = std::vector<float>(GENOME_SIZE * 3);
    this->colors = std::vector<float>(GENOME_SIZE * 4);
    bool unary = false;
    for(int i=0; i<GENOME_SIZE * 3; i+=3)
    {
        if (Utils::randomf() < GENOME_SIZE) unary = !unary;
        if (unary)
        {
            this->vertices[i+0] = father->vertices[i+0];
            this->vertices[i+1] = father->vertices[i+1];
            this->vertices[i+2] = father->vertices[i+2];
        } else {
            this->vertices[i+0] = mother->vertices[i+0];
            this->vertices[i+1] = mother->vertices[i+1];
            this->vertices[i+2] = mother->vertices[i+2];
        }
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
        this->colors[i+3] = Utils::randomf() * 0.02f;
    }
}

void Individual::Mutate() {
    for(int i=0; i<GENOME_SIZE * 3; i+=3) {
        if (Utils::randomf() > MUTATION_RATE) continue;
        vertices[i+0] = Utils::randomf() * 2 -1;
        if (Utils::randomf() > MUTATION_RATE) continue;
        vertices[i+1] = Utils::randomf() * 2 -1;
        if (Utils::randomf() > MUTATION_RATE) continue;
        vertices[i+2] = 0.0f;
    }
    for (int i=0; i<GENOME_SIZE * 4; i+=4) {
        if (Utils::randomf() > MUTATION_RATE) continue;
        colors[i+0] = Utils::randomf();
        if (Utils::randomf() > MUTATION_RATE) continue;
        colors[i+1] = Utils::randomf();
        if (Utils::randomf() > MUTATION_RATE) continue;
        colors[i+2] = Utils::randomf();
        if (Utils::randomf() > MUTATION_RATE) continue;
        colors[i+3] = Utils::randomf() * 0.02f;
    }
}

void Individual::Draw() {
    vb.Draw(true);
}
