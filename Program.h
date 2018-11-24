//
// Created by hugo on 24-11-18.
//

#ifndef PLOX_PROGRAM_H
#define PLOX_PROGRAM_H

#include <iostream>
#include <vector>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <GL/gl.h>


class Program {
private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;

public:
    Program() = default;
    Program(const char *vertexShaderSource, const char *fragmentShaderSource);

    void setupDraw() const;
};


#endif //PLOX_PROGRAM_H
