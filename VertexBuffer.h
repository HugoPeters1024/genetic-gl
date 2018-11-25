//
// Created by hugo on 24-11-18.
//

#ifndef PLOX_VERTEXBUFFER_H
#define PLOX_VERTEXBUFFER_H

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include <glob.h>
#include <GL/gl.h>

class VertexBuffer {
protected:
    unsigned int vboPos;
    unsigned int vao;
    size_t posSize;
    GLenum mode;

public:
    VertexBuffer() = default;

    explicit VertexBuffer(GLenum mode);
    void SetData(const float* posBegin, const float* posEnd);
    void Draw();
};

class VertexBufferUv : public VertexBuffer {
private:
    unsigned int vboUv;
    size_t uvSize;

public:
    VertexBufferUv() = default;
    explicit VertexBufferUv(GLenum mode);
    void SetData(const float* posBegin, const float* posEnd, const float* uvBegin, const float* uvEnd);
};

class VertexBufferColor : public VertexBuffer {
private:
    float* colBegin;
    size_t colSize;
    unsigned int vboCol;

public:
    VertexBufferColor() = default;
    explicit VertexBufferColor(GLenum mode);
    void SetData(const float* posBegin, const float* posEnd, const float* colBegin, const float* colEnd);
};

#endif //PLOX_VERTEXBUFFER_H
