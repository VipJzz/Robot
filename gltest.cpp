#include "gltest.h"
//创建VAO，VBO,赋予id
unsigned int VBO,VAO,EBO;
//EBO索引绘制
unsigned int indices[]={
    0,1,3,
    1,2,3};

unsigned int lightVAO;
QVector3D lightPos(5.0f, 3.0f,8.0f);


QMatrix4x4 matrix;

QMatrix4x4 RotMatrix;


QVector<QVector3D> cubePositionsQt= {
    QVector3D( 0.0f,  0.0f,  0.0f),
    QVector3D( 0.0f,  0.0f, 1.0f),
    QVector3D(0.0f, 0.0f, 2.5f),
    QVector3D( 1.0f,  3.0f,  0.6f),
    QVector3D( 1.0f,  -1.5f, 0.0f)

};

#define TIMEOUTMSEC 1000
float ratio=0.5;
QPoint deltaPos;
QPoint fristPos;
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    timer.start(10);//50ms
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    m_time.start();
    //setMouseTracking(true);
    m_camera.Position=QVector3D(0.0,0.0,3.0);



}

GLWidget::~GLWidget(){
   // if(!isValid())return;
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    doneCurrent();
}

void GLWidget::drawShape(GLWidget::Shape shape){

    m_shape=shape;
    update();

}

void GLWidget::setWireFraem(bool wire){

    makeCurrent();
    if(wire){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    update();
    doneCurrent();

}



void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();


    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shapes.frag");
    shaderProgram.link();

    lightingShader.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/light.vert");
    lightingShader.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/light.frag");
    lightingShader.link();

    axisShader.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/axis.vert");
    axisShader.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/axis.frag");
    axisShader.link();


    color1.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/color1.vert");
    color1.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/color1.frag");
    color1.link();
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    //设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glEnable(GL_DEPTH_TEST);
    axis=new Coordinate();
    axis->init();



    m_robot=new glrobot;
    glPointSize(3.0);//点的大小

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

;





void GLWidget::paintGL()
{
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QMatrix4x4 viewz={-1,0,0,0,
                      0,0,1,0,
                      0,1,0,0,
                      0,0,0,1};//交换view矩阵，修正坐标轴视角,观察方向为z向上
    float time=m_time.elapsed()/1000.0;
    //unsigned int time=QTime::currentTime().second()*1000+QTime::currentTime().msec();



    glClearColor(0.678f, 0.842f, 0.902f,0.98f);//窗口底色，RGBA，A是透明度
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_TEST);//清除缓冲区(颜色、深度、模板）




    projection.perspective(m_camera.Zoom,(float)width()/height(), 0.1f, 100.0f);
    view=m_camera.GetViewMatrix()*viewz;
    //    //使用light
    //    lightingShader.bind();
    //    glBindVertexArray(lightVAO);
    //    model.translate(lightPos);
    //    model.scale(0.5,0.5,0.5);
    //    lightingShader.setUniformValue("model",model);
    //    lightingShader.setUniformValue("projection",projection);
    //    lightingShader.setUniformValue("view",view);

    glBindVertexArray(0);
    //坐标轴
    axisShader.bind();
    axisShader.setUniformValue("projection",projection);
    axisShader.setUniformValue("view",view);
    model.setToIdentity();
    model.translate(0.0f,0.0f,0.0f);
    axisShader.setUniformValue("model",model);
    axisShader.setUniformValue("axisIndex", 1);
    axis->drawX();
    axisShader.setUniformValue("axisIndex", 2);
    axis->drawY();
    axisShader.setUniformValue("axisIndex", 3);
    axis->drawZ();
//测试未通过
//    color1.bind();
//    color1.setUniformValue("projection",projection);
//    color1.setUniformValue("view",view);
//    color1.setUniformValue("model",model);


    //网格
    for(int i = 0; i <= 20; ++i) {
        //抗锯齿
        glEnable (GL_POINT_SMOOTH);
        glHint (GL_LINE_SMOOTH, GL_NICEST);
        glBegin(GL_LINES);
            glVertex3f(-5+0.5*i, -5, 0.0); glVertex3f(-5+0.5*i, 5, 0.0);
            glVertex3f(-5, -5+0.5*i, 0.0); glVertex3f(5, -5+0.5*i, 0.0);
        glEnd();
    }
    //光照、材质
    shaderProgram.bind();//使用就要绑定
    shaderProgram.setUniformValue("lightPos",lightPos);
    shaderProgram.setUniformValue("viewPos",m_camera.Position);

    shaderProgram.setUniformValue("material.ambient",  1.0f, 0.5f, 0.31f);
    shaderProgram.setUniformValue("material.diffuse",  1.0f, 0.5f, 0.31f);
    shaderProgram.setUniformValue("material.specular", 0.5f, 0.5f, 0.5f);
    shaderProgram.setUniformValue("material.shininess", 32.0f);
    shaderProgram.setUniformValue("light.ambient",  0.4f, 0.4f, 0.4f);
    shaderProgram.setUniformValue("light.diffuse",  0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
    shaderProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
    shaderProgram.setUniformValue("light.direction", -0.2f, -1.0f, -0.3f);

    shaderProgram.setUniformValue("view",view);
    shaderProgram.setUniformValue("projection",projection);
    shaderProgram.setUniformValue("model",model);


    if(invflag==true){
        m_robot->inverseGo();
    }else{
       // m_robot->forwardGo();
    }
    shaderProgram.release();
    //画线，采用坐标轴的shader
    axisShader.bind();
    axisShader.setUniformValue("axisIndex", 1);
    glEnable (GL_POINT_SMOOTH);


    m_robot->displayPath();
    shaderProgram.bind();

    m_robot->display(shaderProgram);


}

void GLWidget::on_timeout()
{

    update();
}
//第三视角需要确定鼠标按下的初始位置
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    fristPos=event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint currentPos=event->pos();//鼠标按下后的第一个位置
    deltaPos=currentPos-fristPos;
    m_camera.ProcessMouseMovement(deltaPos.x(),deltaPos.y()/2);
    update();

}

void GLWidget::wheelEvent(QWheelEvent*event) {
    m_camera.ProcessMouseScroll(event->angleDelta().y()/120);
    update();
}



