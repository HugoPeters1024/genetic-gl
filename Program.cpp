//
// Created by hugo on 24-11-18.
//

#include "Program.h"

Program::Program(const char *vertexShaderSource, const char *fragmentShaderSource) {
    // Compile vertex shader
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Print status report
    /*
    GLint logSize = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
    std::vector<GLchar> vertexLog(logSize);
    glGetShaderInfoLog(vertexShader, logSize, &logSize, &vertexLog[0]);
    std::cout << "Vertex shader log:" << std::endl << &vertexLog[0] << std::endl; */

    // Compile fragment shader
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Print status report
    GLint logSize;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
    std::vector<GLchar> framentLog(logSize);
    glGetShaderInfoLog(vertexShader, logSize, &logSize, &framentLog[0]);
    std::cout << "Fragment shader log:" << std::endl << &framentLog[0] << std::endl;

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

void Program::setupDraw() const {
    glUseProgram(shaderProgram);
}

