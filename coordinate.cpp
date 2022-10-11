#include "coordinate.h"
#define VNAME(value) (#value)
#include <QDebug>
 
// vertices of lines
GLfloat lineXVertices[6] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};
 
GLfloat lineYVertices[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};
 
GLfloat lineZVertices[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};
 
// vertices of pyramids
GLfloat pyramidXVertices[] =
{
    1.0f, 0.01f, 0.01f,     // x1
    1.0f, 0.01f, -0.01f,    // x2
    1.0f, -0.01f, -0.01f,   // x3
 
    1.0f, 0.01f, 0.01f,     // x1
    1.0f, -0.01f, -0.01f,   // x3
    1.0f, -0.01f, 0.01f,    // x4
 
    1.1f, 0.0f, 0.0f,       // 0
    1.0f, 0.01f, 0.01f,     // x1
    1.0f, -0.01f, 0.01f,    // x4
 
    1.1f, 0.0f, 0.0f,       // 0
    1.0f, 0.01f, 0.01f,     // x1
    1.0f, 0.01f, -0.01f,    // x2
 
    1.1f, 0.0f, 0.0f,       // 0
    1.0f, 0.01f, -0.01f,    // x2
    1.0f, -0.01f, -0.01f,   // x3
 
    1.1f, 0.0f, 0.0f,       // 0
    1.0f, -0.01f, -0.01f,   // x3
    1.0f, -0.01f, 0.01f     // x4
};
 
GLfloat pyramidYVertices[] =
{
    0.01f, 1.0f, -0.01f,    // x1
    -0.01f, 1.0f, -0.01f,   // x2
    -0.01f, 1.0f, 0.01f,    // x3
 
    0.01f, 1.0f, -0.01f,    // x1
    -0.01f, 1.0f, 0.01f,    // x3
    0.01f, 1.0f, 0.01f,     // x4
 
    0.0f, 1.1f, 0.0f,       // 0
    0.01f, 1.0f, -0.01f,    // x1
    0.01f, 1.0f, 0.01f,     // x4
 
    0.0f, 1.1f, 0.0f,       // 0
    0.01f, 1.0f, -0.01f,    // x1
    -0.01f, 1.0f, -0.01f,   // x2
 
    0.0f, 1.1f, 0.0f,       // 0
    -0.01f, 1.0f, -0.01f,   // x2
    -0.01f, 1.0f, 0.01f,    // x3
 
    0.0f, 1.1f, 0.0f,       // 0
    -0.01f, 1.0f, 0.01f,    // x3
    0.01f, 1.0f, 0.01f      // x4
};
 
GLfloat pyramidZVertices[] =
{
    0.01f, 0.01f, 1.0f,     // x1
    -0.01f, 0.01f, 1.0f,    // x2
    -0.01f, -0.01f, 1.0f,   // x3
 
    0.01f, 0.01f, 1.0f,     // x1
    -0.01f, -0.01f, 1.0f,   // x3
    0.01f, -0.01f, 1.0f,    // x4
 
    0.0f, 0.0f, 1.1f,       // 0
    0.01f, 0.01f, 1.0f,     // x1
    0.01f, -0.01f, 1.0f,    // x4
 
    0.0f, 0.0f, 1.1f,       // 0
    0.01f, 0.01f, 1.0f,     // x1
    -0.01f, 0.01f, 1.0f,    // x2
 
    0.0f, 0.0f, 1.1f,       // 0
    -0.01f, 0.01f, 1.0f,    // x2
    -0.01f, -0.01f, 1.0f,   // x3
 
    0.0f, 0.0f, 1.1f,       // 0
    -0.01f, -0.01f, 1.0f,   // x3
    0.01f, -0.01f, 1.0f     // x4
};
 
 
Coordinate::Coordinate()
{
    this->initializeOpenGLFunctions();
}
 
Coordinate::~Coordinate()
{
    glDeleteBuffers(3, linesVBO);
    glDeleteBuffers(3, pyramidsVBO);
}
 
void Coordinate::init()
{
    // generate VBO
    glGenBuffers(3, linesVBO);
    glGenBuffers(3, pyramidsVBO);
}
 
void Coordinate::drawCoordAxis(GLuint lineVBO, GLfloat *lineVertices, GLuint pyramidVBO, GLfloat *pyramidVertices)
{


    // line
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    // 24为sizeof(lineVertices)的大小，因数组作为参数传递，sizeof（）后值为1
    glBufferData(GL_ARRAY_BUFFER, 24, lineVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, 2);
 
    // pyramid
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, 216, pyramidVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 18);


}
 
void Coordinate::drawX()
{
    drawCoordAxis(linesVBO[0], lineXVertices, pyramidsVBO[0], pyramidXVertices);
}

void Coordinate::drawY()
{
    drawCoordAxis(linesVBO[1], lineYVertices, pyramidsVBO[1], pyramidYVertices);
}

void Coordinate::drawZ()
{
    drawCoordAxis(linesVBO[2], lineZVertices, pyramidsVBO[2], pyramidZVertices);
}
