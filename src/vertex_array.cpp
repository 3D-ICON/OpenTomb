#include "vertex_array.h"

#include <cassert>
#include <cstring>

VertexArray::VertexArray(GLuint element_vbo, size_t numAttributes, const VertexArrayAttribute *attributes)
{
    glGenVertexArraysAPPLE(1, &m_vertexArrayObject);
    
    assert(m_vertexArrayObject && "Incorrect OpenGL function setup");
    glBindVertexArrayAPPLE(m_vertexArrayObject);
    
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, element_vbo);
    
    for (size_t i = 0; i < numAttributes; i++)
    {
        assert(attributes[i].m_vbo != 0);
        assert(attributes[i].m_stride != 0);
        
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, attributes[i].m_vbo);
        glEnableVertexAttribArrayARB(attributes[i].m_index);
        glVertexAttribPointerARB(attributes[i].m_index, attributes[i].m_size,
                                 attributes[i].m_type, attributes[i].m_normalized,
                                 attributes[i].m_stride,
                                 (const GLvoid *) attributes[i].m_offset);
    }
    
    glBindVertexArrayAPPLE(0);
}

void VertexArray::bind()
{
    glBindVertexArrayAPPLE(m_vertexArrayObject);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArraysAPPLE(1, &m_vertexArrayObject);
}
