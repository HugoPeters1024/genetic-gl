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
private:
    unsigned int vboPos;
    unsigned int vboUv;
    unsigned int vao;
    size_t posSize;
    size_t uvSize;
    GLenum mode;

public:
    VertexBuffer(void);

    VertexBuffer(float* posBegin, float* posEnd, float* uvBegin, float* uvEnd, GLenum mode);

    void draw() const;
};


#endif //PLOX_VERTEXBUFFER_H
