//
// Created by hugo on 25-11-18.
//

#ifndef PLOX_RENDERFACTORY_H
#define PLOX_RENDERFACTORY_H


#include <cstdlib>
#include "VertexBuffer.h"
#include "Individual.h"

class RenderFactory {
public:
    static const float* Individual_vertices;
    static const float* Individual_colors;
    static VertexBufferColor Individual_buffer;

public:
    static void RenderIndividual(const Individual &individual);
    static void Startup();

};
#endif //PLOX_RENDERFACTORY_H
