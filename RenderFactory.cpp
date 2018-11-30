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


void RenderFactory::Startup() {
    Individual_buffer = VertexBufferColor(GL_TRIANGLE_STRIP);
}


VertexBufferColor RenderFactory::Individual_buffer;
const float* RenderFactory::Individual_vertices;
const float* RenderFactory::Individual_colors;