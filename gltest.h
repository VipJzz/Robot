#ifndef GLTEST_H
#define GLTEST_H

#include<GL/gl.h>
#include<GL/glu.h>
#include<QtOpenGL/qgl.h>
#include<QOpenGLWidget>
#include<QOpenGLFunctions_3_3_Core>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include<QTime>
#include<QTimer>
#include<QImage>
#include<QVector>

#include<QVector3D>

#include<QMouseEvent>
#include<QKeyEvent>
#include<iostream>
#include<stdio.h>


#include<stdlib.h>
#include"camera.h"
#include<coordinate.h>
#include"glrobot.h"

class GLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();
    enum Shape{None,Rect,Circle,Triangle};//枚举量
    void drawShape(Shape shape);
    void setWireFraem(bool wire);
   // void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent*event) ;
    void mousePressEvent(QMouseEvent *event);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();


signals:

public slots:
    void on_timeout();

private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLShaderProgram lightingShader;
    QOpenGLShaderProgram axisShader;
    QOpenGLShaderProgram color1;
    QOpenGLShaderProgram color2;

    Shape m_shape;

    QTimer timer;
    QTime m_time;
    QOpenGLTexture *textureWall;//纹理类
    QOpenGLTexture *textureSmile;

    Camera m_camera;
    QPoint lastPos;//默认(0,0)
    Coordinate *axis;
public:

    //Model m_model;
    glrobot *m_robot; //以便mainwindow访问，调用改变运动参数
    //
    bool invflag=0;//接口，mainwindow访问，标志是否逆，true=逆


};

#endif // GLTEST_H
