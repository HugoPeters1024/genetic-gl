//
// Created by hugo on 25-11-18.
//
#include <cstdio>
#include <limits>
#include <algorithm>
#include <numeric>
#include "Population.h"

static double maxScore = 0;

Population::Population(float* fbSource) {
    this->buffer = std::vector<Individual>(POP_SIZE);
    this->swapBuffer = std::vector<Individual>(POP_SIZE);
    this->fbSource = fbSource;
    this->scores = (double*)malloc(POP_SIZE * sizeof(double));
}

void Population::NextGeneration() {
    for(int i=0; i<POP_SIZE; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        buffer[i].Mutate();
        RenderFactory::RenderIndividual(buffer[i]);
        scores[i] = Utils::GetScore(fbSource);
        glfwSwapBuffers(Utils::window);
        glfwPollEvents();
    }

    // Sort the population on descending scores
    std::sort(scores, scores + POP_SIZE);
    float maxv = (*std::max_element(scores, scores + POP_SIZE));
   // double maxv = SCREEN_WIDTH * SCREEN_HEIGHT;
    std::transform(scores, scores + POP_SIZE, scores, [maxv](double &v){ return maxv - v; });

    for(int i=0; i<POP_SIZE; i++)
    {
        if (i % 10 == 0)
        printf("%lf\n", scores[i]);
    }
    printf("\n");
    double scoreSum = std::accumulate(scores, scores + POP_SIZE, 0.0);
    //scoreSum = 0;

    for(int i=0; i<POP_SIZE; i++)
    {
        Individual* temp = new Individual(PickWinner(scoreSum), PickWinner(scoreSum));
        std::swap(swapBuffer[0], *temp);
        delete temp;

        if (scores[i] > maxScore)
        {
            maxScore = scores[i];
        }
    }

    buffer.swap(swapBuffer);
}

Individual* Population::PickWinner(double scoreSum) {
    double rf = Utils::randomlf();
    double winner = rf * scoreSum;
    int winnerIndex = -1;
    double winnerSum = 0;
    while(winnerSum < winner)
    {
        winnerSum += scores[winnerIndex+1];
        winnerIndex += 1;
    }
    return &buffer[winnerIndex];
}
