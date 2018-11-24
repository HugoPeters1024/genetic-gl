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
    float* posBegin;
    unsigned int vao;
    size_t posSize;
    GLenum mode;

public:
    VertexBuffer() = default;
    VertexBuffer(float* posBegin, float* posEnd, GLenum mode);
    virtual void Draw(bool rebind);
};

class VertexBufferUv : public VertexBuffer {
private:
    unsigned int vboUv;
    size_t uvSize;

public:
    VertexBufferUv() = default;
    VertexBufferUv(float* posBegin, float* posEnd, float* uvBegin, float* uvEnd, GLenum mode);
};

class VertexBufferColor : public VertexBuffer {
private:
    float* colBegin;
    size_t colSize;
    unsigned int vboCol;

public:
    VertexBufferColor() = default;
    VertexBufferColor(float* posBegin, float* posEnd, float* colBegin, float* colEnd, GLenum mode);
    void Draw(bool rebind) override;
};

#endif //PLOX_VERTEXBUFFER_H
