//
// Created by hugo on 1-12-18.
//

#include "GridIndividual.h"
#include "Utils.h"

GridIndividual::GridIndividual() {
    colors = std::vector<float>(TRIANGLES_HORZ * TRIANGLES_VERT);
    Randomize();
}

void GridIndividual::Randomize() {
    for (float &color : colors) {
        color = Utils::randomf();
    }
}

GridIndividual::GridIndividual(GridIndividual *mother, GridIndividual *father) {
    GridIndividual* src;
    for(int i=0; i<colors.size(); i++)
    {
        Utils::randomf() < CROSS_OVER_RATE ? src = mother : src = father;
        colors[i] = src->colors[i];
    }

}

void GridIndividual::init() {
    vertices = std::vector<float>(TRIANGLES_HORZ * TRIANGLES_VERT);
    for(int y=0; y<TRIANGLES_VERT; y++)
    {
        for(int x=0; x<TRIANGLES_HORZ; x++)
        {
        }
    }
}

std::vector<float> GridIndividual::vertices;
