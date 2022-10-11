#ifndef COORDINATE_H
#define COORDINATE_H
#include <QOpenGLExtraFunctions>
 
class Coordinate : protected QOpenGLExtraFunctions
{
public:
    Coordinate();
    ~Coordinate();
 
    void init();
 
    void drawCoordAxis(GLuint lineVBO, GLfloat *lineVertices, GLuint pyramidVBO, GLfloat *pyramidVertices);
    void drawX();
    void drawY();
    void drawZ();
 
private:
    GLuint linesVBO[3];    // VBO of lines
    GLuint pyramidsVBO[3];   // VBO of pyramids
};
 
#endif // COORDINATE_H
