//
// Created by hugo on 24-11-18.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float *posBegin, float *posEnd, GLenum mode) {
    this->mode = mode;
    this->posSize = posEnd - posBegin;
    this->posBegin = posBegin;

    glGenBuffers(1, &vboPos);
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, posSize * sizeof(float), posBegin, GL_STATIC_DRAW);


    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glVertexAttribPointer(
            0, // Attribute index
            3, // Elements per vertex
            GL_FLOAT,
            GL_FALSE, // Normalized
            0, // Stride: tightly packed
            nullptr
    );
}

void VertexBuffer::Draw(bool rebind)
{
    glBindVertexArray(vao);
    if (rebind) {
        glBindBuffer(GL_ARRAY_BUFFER, vboPos);
        glBufferData(GL_ARRAY_BUFFER, posSize * sizeof(float), posBegin, GL_STATIC_DRAW);
    }
    glDrawArrays(mode, 0, posSize / 3);
}

VertexBufferUv::VertexBufferUv(float *posBegin, float *posEnd, float *uvBegin, float *uvEnd, GLenum mode)
    : VertexBuffer(posBegin, posEnd, mode)
{
    this->uvSize = uvEnd - uvBegin;
    glGenBuffers(1, &vboUv);

    glBindBuffer(GL_ARRAY_BUFFER, vboUv);
    glBufferData(GL_ARRAY_BUFFER, uvSize * sizeof(float), uvBegin, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);

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

VertexBufferColor::VertexBufferColor(float* posBegin, float* posEnd, float* colBegin, float * colEnd, GLenum mode)
    : VertexBuffer(posBegin, posEnd, mode)
{
    this->colBegin = colBegin;
    this->colSize = colEnd - colBegin;
    glGenBuffers(1, &vboCol);

    glBindBuffer(GL_ARRAY_BUFFER, vboCol);
    glBufferData(GL_ARRAY_BUFFER, colSize * sizeof(float), colBegin, GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vboCol);
    glVertexAttribPointer(
            2, // Attribute index,
            4, // Elements per color
            GL_FLOAT,
            GL_FALSE, // Normalized
            0,
            nullptr);
}

void VertexBufferColor::Draw(bool rebind) {
    if (rebind)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vboCol);
        glBufferData(GL_ARRAY_BUFFER, colSize * sizeof(float), colBegin, GL_STATIC_DRAW);
    }
    VertexBuffer::Draw(rebind);
}