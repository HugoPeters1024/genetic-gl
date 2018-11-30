//
// Created by hugo on 25-11-18.
//

#ifndef PLOX_RENDERFACTORY_H
#define PLOX_RENDERFACTORY_H


#include <cstdlib>
#include "VertexBuffer.h"
#include "Individual.h"
#include "GridIndividual.h"

class RenderFactory {
public:
    static VertexBufferColor Individual_buffer;
    static const float* GridIndividual_vertices;
    static VertexBufferColor GridIndividual_buffer;

public:
    static void RenderIndividual(const Individual &individual);
    static void RenderIndividual(const GridIndividual &individual);
    static void Startup();

};
#endif //PLOX_RENDERFACTORY_H
