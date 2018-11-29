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
        RenderFactory::RenderIndividual(buffer[i]);
        scores[i] = Utils::GetScore(fbSource);
        glfwSwapBuffers(Utils::window);
        glfwPollEvents();
    }

    double maxv = (*std::max_element(scores, scores + POP_SIZE));
    // Invert the scoring
   // double maxv = SCREEN_HEIGHT * SCREEN_WIDTH * 4;
    std::transform(scores, scores + POP_SIZE, scores, [maxv](double &v){ return maxv - v; });

    double maxScore = 0.0;
    int maxIndex = 0;
    for(int i=0; i<POP_SIZE; i++)
    {
        if (i % 10 == 0)
        printf("%lf\n", scores[i]);
        if (scores[i] > maxScore)
        {
            maxIndex = i;
            maxScore = scores[i];
        }
    }
    printf("max: %lf / %lf\%\n\n", maxScore, maxScore / (SCREEN_WIDTH * SCREEN_HEIGHT * 4.0) * 100.0);
    double scoreSum = std::accumulate(scores, scores + POP_SIZE, 0.0);

    Individual* best = new Individual(buffer[maxIndex]);
    std::swap(swapBuffer[0], *best);
    delete best;
    for(int i=1; i<POP_SIZE; i++)
    {
        Individual* temp = new Individual(PickWinner(scoreSum), PickWinner(scoreSum));
        temp->Mutate();
        std::swap(swapBuffer[i], *temp);
        delete temp;
    }

    buffer.swap(swapBuffer);
}

Individual* Population::PickWinner(double scoreSum) {
    double rf = Utils::randomlf();
    double winner = rf * scoreSum + 1;
    int winnerIndex = -1;
    double winnerSum = 0;
    while(winnerSum < winner)
    {
        winnerSum += scores[winnerIndex+1];
        winnerIndex += 1;
        if (winnerIndex == POP_SIZE-1)
            break;
    }
    return &buffer[winnerIndex];
}
