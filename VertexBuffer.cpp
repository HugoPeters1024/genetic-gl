//
// Created by hugo on 24-11-18.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLenum mode) {
    this->mode = mode;
    glGenBuffers(1, &vboPos);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
}

void VertexBuffer::SetData(const float *posBegin, const float *posEnd) {
    this->posSize = posEnd - posBegin;

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, posSize * sizeof(float), posBegin, GL_STATIC_DRAW);

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

void VertexBuffer::Draw()
{
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, static_cast<GLsizei>(posSize / 3));
}

VertexBufferUv::VertexBufferUv(GLenum mode)
    : VertexBuffer(mode)
{
    glGenBuffers(1, &vboUv);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(1);

}

void VertexBufferUv::SetData(const float *posBegin, const float *posEnd, const float *uvBegin, const float *uvEnd) {
    VertexBuffer::SetData(posBegin, posEnd);
    this->uvSize = uvEnd - uvBegin;

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vboUv);
    glBufferData(GL_ARRAY_BUFFER, uvSize * sizeof(float), uvBegin, GL_STATIC_DRAW);
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

VertexBufferColor::VertexBufferColor(GLenum mode)
    : VertexBuffer(mode)
{
    glGenBuffers(1, &vboCol);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(2);
}

void VertexBufferColor::SetData(const float *posBegin, const float *posEnd, const float *colBegin, const float *colEnd) {
    VertexBuffer::SetData(posBegin, posEnd);
    this->colSize = colEnd - colBegin;

    glBindBuffer(GL_ARRAY_BUFFER, vboCol);
    glBufferData(GL_ARRAY_BUFFER, colSize * sizeof(float), colBegin, GL_STATIC_DRAW);

    glVertexAttribPointer(
            2, // Attribute index,
            4, // Elements per color
            GL_FLOAT,
            GL_FALSE, // Normalized
            0,
            nullptr);
}
