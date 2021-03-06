#include "VertexArray.h"

#include <cmath>

#include "Context.h"

m4w::VertexArray::VertexArray (VertexLayout& vbl)
    : m_VBL(vbl)
{
    glGenVertexArrays(1, &m_ID);

    this->Bind();
}

m4w::VertexArray::~VertexArray () {
    glDeleteVertexArrays(1, &m_ID);
}

void m4w::VertexArray::SetIndexBuffer (m4w::Pointer<IndexBuffer> ib) {
    this->Bind();
    m_IB = ib;
    m_IB->Bind();
}

void m4w::VertexArray::SetVertexBuffer (m4w::Pointer<VertexBuffer> vb) {
    this->Bind();
    m_VB = vb;
    m_VB->Bind();

    m_VBL.Use(*this);
}

void m4w::VertexArray::Bind () {
    glBindVertexArray(m_ID);
    g_Context.m_VAO = this;
}

void m4w::VertexArray::Unbind () {
    glBindVertexArray(0);
    g_Context.m_VAO = nullptr;
}

m4w::Pointer<m4w::VertexArray> m4w::VertexArray::Sphere (unsigned int sub_divisions, float radius, float color[4], bool smooth){
    return Sphere(sub_divisions, radius, color[0], color[1], color[2], color[3], smooth);
}


m4w::Pointer<m4w::VertexArray> m4w::VertexArray::Sphere (unsigned int sub_divisions, float radius, float r, float g, float b, float a, bool smooth) {

    uint32_t final_square_count = 6 * (sub_divisions + 1) * (sub_divisions + 1);
    const float square_length = 1.f / ( sub_divisions + 1 );

    uint32_t vertex_count = final_square_count * 4;

    VertexLayout::DefaultVertex* vertices = new VertexLayout::DefaultVertex[vertex_count];

    uint32_t cur = 0;

    for ( uint32_t i = 0 ; i < sub_divisions + 1 ; i++ ) {
        // Left-Right
        float lr = square_length * i - .5f; 
        float next_lr = lr + square_length;

        for ( uint32_t j = 0 ; j < sub_divisions + 1 ; j++ ) {
            // Up-Down
            float ud = square_length * j - .5f;
            float next_ud = ud + square_length;

            // +X
            vertices[ cur++ ] = {  .5f,      ud,      lr,    1.f, ud+next_ud, lr+next_lr,   r, g, b, a,   next_lr,      ud };
            vertices[ cur++ ] = {  .5f, next_ud,      lr,    1.f, ud+next_ud, lr+next_lr,   r, g, b, a,   next_lr, next_ud };
            vertices[ cur++ ] = {  .5f, next_ud, next_lr,    1.f, ud+next_ud, lr+next_lr,   r, g, b, a,        lr, next_ud };
            vertices[ cur++ ] = {  .5f,      ud, next_lr,    1.f, ud+next_ud, lr+next_lr,   r, g, b, a,        lr,      ud };
            // -X
            vertices[ cur++ ] = { -.5f, next_ud, next_lr,   -1.f, ud+next_ud, lr+next_lr,   r, g, b, a,   next_lr, next_ud };
            vertices[ cur++ ] = { -.5f, next_ud,      lr,   -1.f, ud+next_ud, lr+next_lr,   r, g, b, a,        lr, next_ud };
            vertices[ cur++ ] = { -.5f,      ud,      lr,   -1.f, ud+next_ud, lr+next_lr,   r, g, b, a,        lr,      ud };
            vertices[ cur++ ] = { -.5f,      ud, next_lr,   -1.f, ud+next_ud, lr+next_lr,   r, g, b, a,   next_lr,      ud };
            // +Y
            vertices[ cur++ ] = {      lr,  .5f,      ud,   lr+next_lr,  1.f, ud+next_ud,   r, g, b, a,        lr,      ud };
            vertices[ cur++ ] = {      lr,  .5f, next_ud,   lr+next_lr,  1.f, ud+next_ud,   r, g, b, a,   next_lr,      ud };
            vertices[ cur++ ] = { next_lr,  .5f, next_ud,   lr+next_lr,  1.f, ud+next_ud,   r, g, b, a,   next_lr, next_ud };
            vertices[ cur++ ] = { next_lr,  .5f,      ud,   lr+next_lr,  1.f, ud+next_ud,   r, g, b, a,        lr, next_ud };
            // -Y
            vertices[ cur++ ] = { next_lr, -.5f, next_ud,   lr+next_lr, -1.f, ud+next_ud,   r, g, b, a,   next_lr,      ud };
            vertices[ cur++ ] = {      lr, -.5f, next_ud,   lr+next_lr, -1.f, ud+next_ud,   r, g, b, a,   next_lr, next_ud };
            vertices[ cur++ ] = {      lr, -.5f,      ud,   lr+next_lr, -1.f, ud+next_ud,   r, g, b, a,        lr, next_ud };
            vertices[ cur++ ] = { next_lr, -.5f,      ud,   lr+next_lr, -1.f, ud+next_ud,   r, g, b, a,        lr,      ud };
            // +Z
            vertices[ cur++ ] = {      ud,      lr,  .5f,   ud+next_ud, lr+next_lr,  1.f,   r, g, b, a,        lr,      ud };
            vertices[ cur++ ] = { next_ud,      lr,  .5f,   ud+next_ud, lr+next_lr,  1.f,   r, g, b, a,   next_lr,      ud };
            vertices[ cur++ ] = { next_ud, next_lr,  .5f,   ud+next_ud, lr+next_lr,  1.f,   r, g, b, a,   next_lr, next_ud };
            vertices[ cur++ ] = {      ud, next_lr,  .5f,   ud+next_ud, lr+next_lr,  1.f,   r, g, b, a,        lr, next_ud };
            // -Z
            vertices[ cur++ ] = { next_ud, next_lr, -.5f,   ud+next_ud, lr+next_lr, -1.f,   r, g, b, a,         lr, next_ud };
            vertices[ cur++ ] = { next_ud,      lr, -.5f,   ud+next_ud, lr+next_lr, -1.f,   r, g, b, a,         lr,      ud };
            vertices[ cur++ ] = {      ud,      lr, -.5f,   ud+next_ud, lr+next_lr, -1.f,   r, g, b, a,    next_lr,      ud };
            vertices[ cur++ ] = {      ud, next_lr, -.5f,   ud+next_ud, lr+next_lr, -1.f,   r, g, b, a,    next_lr, next_ud };

        }
    }


    for ( cur = 0 ; cur < vertex_count ; cur++ ) {
        VertexLayout::DefaultVertex& vertex = vertices[cur];
        float len = std::sqrt(vertex.Pos[0]*vertex.Pos[0] + vertex.Pos[1]*vertex.Pos[1] + vertex.Pos[2]*vertex.Pos[2]);

        if ( smooth ) {
            vertex.Normal[0] = vertex.Pos[0] / len;
            vertex.Normal[1] = vertex.Pos[1] / len;
            vertex.Normal[2] = vertex.Pos[2] / len;
        }

        vertex.Pos[0] = vertex.Pos[0] / len * radius;
        vertex.Pos[1] = vertex.Pos[1] / len * radius;
        vertex.Pos[2] = vertex.Pos[2] / len * radius;
    }

    VertexArray* vao = new VertexArray();

    vao->SetIndexBuffer( IndexBuffer::Squares(final_square_count) );
    vao->SetVertexBuffer( new VertexBuffer(sizeof(VertexLayout::DefaultVertex) * vertex_count, vertices) );

    delete[] vertices;
    return vao;
}


m4w::Pointer<m4w::VertexArray> m4w::VertexArray::Cube (float pos1[3], float pos2[3], float color[4]) {
    return Cube(pos1[0], pos1[1], pos1[2],  pos2[0], pos2[1], pos2[2],  color[0], color[1], color[2], color[3]);
}

m4w::Pointer<m4w::VertexArray> m4w::VertexArray::Cube (float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b, float a) {
    float pX = std::max(x1, x2);
    float nX = std::min(x1, x2);

    float pY = std::max(y1, y2);
    float nY = std::min(y1, y2);

    float pZ = std::max(z1, z2);
    float nZ = std::min(z1, z2);

    float verts[] = {
        // +X
        pX, nY, nZ,    1.f, 0.f, 0.f,   r, g, b, a,   1.f, 0.f,
        pX, pY, nZ,    1.f, 0.f, 0.f,   r, g, b, a,   1.f, 1.f,
        pX, pY, pZ,    1.f, 0.f, 0.f,   r, g, b, a,   0.f, 1.f,
        pX, nY, pZ,    1.f, 0.f, 0.f,   r, g, b, a,   0.f, 0.f,
        // -X
        nX, pY, pZ,   -1.f, 0.f, 0.f,   r, g, b, a,   1.f, 1.f,
        nX, pY, nZ,   -1.f, 0.f, 0.f,   r, g, b, a,   0.f, 1.f,
        nX, nY, nZ,   -1.f, 0.f, 0.f,   r, g, b, a,   0.f, 0.f,
        nX, nY, pZ,   -1.f, 0.f, 0.f,   r, g, b, a,   1.f, 0.f,
        // +Y
        nX, pY, nZ,   0.f,  1.f, 0.f,   r, g, b, a,   0.f, 0.f,
        nX, pY, pZ,   0.f,  1.f, 0.f,   r, g, b, a,   1.f, 0.f,
        pX, pY, pZ,   0.f,  1.f, 0.f,   r, g, b, a,   1.f, 1.f,
        pX, pY, nZ,   0.f,  1.f, 0.f,   r, g, b, a,   0.f, 1.f,
        // -Y
        pX, nY, pZ,   0.f, -1.f, 0.f,   r, g, b, a,   1.f, 0.f,
        nX, nY, pZ,   0.f, -1.f, 0.f,   r, g, b, a,   1.f, 1.f,
        nX, nY, nZ,   0.f, -1.f, 0.f,   r, g, b, a,   0.f, 1.f,
        pX, nY, nZ,   0.f, -1.f, 0.f,   r, g, b, a,   0.f, 0.f,
        // +Z
        nX, nY, pZ,   0.f, 0.f,  1.f,   r, g, b, a,   0.f, 0.f,
        pX, nY, pZ,   0.f, 0.f,  1.f,   r, g, b, a,   1.f, 0.f,
        pX, pY, pZ,   0.f, 0.f,  1.f,   r, g, b, a,   1.f, 1.f,
        nX, pY, pZ,   0.f, 0.f,  1.f,   r, g, b, a,   0.f, 1.f,
        // -Z
        pX, pY, nZ,   0.f, 0.f, -1.f,   r, g, b, a,   0.f, 1.f,
        pX, nY, nZ,   0.f, 0.f, -1.f,   r, g, b, a,   0.f, 0.f,
        nX, nY, nZ,   0.f, 0.f, -1.f,   r, g, b, a,   1.f, 0.f,
        nX, pY, nZ,   0.f, 0.f, -1.f,   r, g, b, a,   1.f, 1.f,
    };
    VertexArray* vao = new VertexArray();

    vao->SetIndexBuffer(IndexBuffer::Squares(6));
    vao->SetVertexBuffer(new VertexBuffer(sizeof(verts), verts));

    return vao;
}
