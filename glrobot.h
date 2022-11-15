#ifndef GLROBOT_H
#define GLROBOT_H
//机器人界面类，只负责机器人显示，不参与运算
#include "model.h"
#include <QObject>
#include <cmath>
#include <vector>
#include <queue>
#include"global.h"
class glrobot
{
public:
    glrobot();
    void displayPath();
    void display(QOpenGLShaderProgram &shader);
    //inline
    void setTh1(double th1c){ th1=th1c;}
    void setTh2(double th2c){ th1=th2c;}
    void setTh3(double th3c){ th1=th3c;}
    void setTh4(double th4c){ th1=th4c;}
    void setTh5(double th5c){ th1=th5c;}
    void setTh6(double th6c){ th1=th6c;}

    void setStancePath(const std::queue<Stance> &stpath){
        StPath=stpath;
    }
    void setPath(const std::vector<Point> &pathc){
        path=pathc;
    }

    void inverseGo();


public:
    const double d1,d4,d6,  a1,a2,a3;
private:
    double th1, th2, th3,th4,th5,th6;
    Model *baseModel, *arm1Model, *arm2Model, *arm3Model,*arm4Model,*arm5Model,*arm6Model;


    //轨迹点
    std::vector<Point> path;
    //逆运动的一串姿态
    std::queue<Stance> StPath;  //定义队列，使用的时候弹出元素
};

#endif // GLROBOT_H
