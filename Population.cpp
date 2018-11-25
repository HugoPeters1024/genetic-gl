//
// Created by hugo on 25-11-18.
//
#include "Population.h"

Population::Population(unsigned char* fbSource) {
    this->buffer = std::vector<Individual>(POP_SIZE);
    this->fbSource = fbSource;

}

void Population::NextGeneration() {
    double scores[POP_SIZE];
    for(int i=0; i<POP_SIZE; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        RenderFactory::RenderIndividual(buffer[i]);
        scores[i] = Utils::GetScore(fbSource);
        glfwSwapBuffers(Utils::window);
    }
}
