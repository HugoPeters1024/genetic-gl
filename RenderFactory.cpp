//
// Created by hugo on 25-11-18.
//

#include "RenderFactory.h"

void RenderFactory::RenderIndividual(const Individual &individual) {
    Individual_buffer.SetData(
            individual.vertices.data(), individual.vertices.data() + individual.vertices.capacity(),
            individual.colors.data(), individual.colors.data() + individual.colors.capacity());
    Individual_buffer.Draw();
}

void RenderFactory::RenderIndividual(const GridIndividual &individual) {
    GridIndividual_buffer.SetData(
            GridIndividual::vertices.data(), GridIndividual::vertices.data() + GridIndividual::vertices.capacity(),
            individual.colors.data(), individual.colors.data() + individual.colors.capacity());
    GridIndividual_buffer.Draw();
}


void RenderFactory::Startup() {
    Individual_buffer = VertexBufferColor(GL_TRIANGLE_STRIP);
    GridIndividual_buffer = VertexBufferColor(GL_TRIANGLES);
}


VertexBufferColor RenderFactory::Individual_buffer;
VertexBufferColor RenderFactory::GridIndividual_buffer;
