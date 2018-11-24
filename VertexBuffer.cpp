//
// Created by hugo on 24-11-18.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() = default;

VertexBuffer::VertexBuffer(float *posBegin, float *posEnd, float* uvBegin, float* uvEnd, GLenum mode) {
    this->mode = mode;
    this->posSize = posEnd - posBegin;
    this->uvSize = uvEnd - uvBegin;

    glGenBuffers(1, &vboPos);
    glGenBuffers(1, &vboUv);
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, posSize * sizeof(float), posBegin, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboUv);
    glBufferData(GL_ARRAY_BUFFER, uvSize * sizeof(float), uvBegin, GL_STATIC_DRAW);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glVertexAttribPointer(
            0, // Attribute index
            3, // Elements per vertex
            GL_FLOAT,
            GL_FALSE, // Normalized
            0, // Stride: tightly packed
            nullptr
    );

    glBindBuffer(GL_ARRAY_BUFFER, vboUv);
    glVertexAttribPointer(
            1, // Attribute index
            2, // Elements per vertex
            GL_FLOAT,
            GL_FALSE, // Normalized
            0,
            nullptr
    );
}

void VertexBuffer::draw() const
{
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, posSize / 3);
}