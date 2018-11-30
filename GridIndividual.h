//
// Created by hugo on 1-12-18.
//

#include <vector>

#ifndef PLOX_GRIDINDIVIDUAL_H
#define PLOX_GRIDINDIVIDUAL_H

#define TRIANGLE_SIZE 10
#define TRIANGLES_HORZ (SCREEN_WIDTH / TRIANGLE_SIZE)
#define TRIANGLES_VERT (SCREEN_HEIGHT / TRIANGLE_SIZE)
#define CROSS_OVER_RATE 0.3f
#define MUTATION_RATE 0.005f


class GridIndividual {
private:
    void Randomize();

public:
    std::vector<float> colors;
    static std::vector<float> vertices;
    static void init();
    GridIndividual();
    GridIndividual(GridIndividual* mother, GridIndividual* father);

};


#endif //PLOX_GRIDINDIVIDUAL_H
