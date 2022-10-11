#ifndef ROBOT_H
#define ROBOT_H
#include "model.h"

#include <QObject>
#include <cmath>
#include <vector>
#include <queue>
#include"global.h"
#include "trajectory.h" //轨迹规划器


class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);


public :

    void forwardGo();
    void displayPath();
    void display(QOpenGLShaderProgram &shader);
    Stance getCurStance(){
        Stance currentStance;
        currentStance.th1=th1;
        currentStance.th2=th2;
        currentStance.th3=th3;
        currentStance.th4=th4;
        currentStance.th5=th5;
        currentStance.th6=th6;
        return currentStance;
    }



    Stance inverseTh(Point p,QMatrix4x4 m,Stance oldst);//逆运动求解th,接受一轨迹点,一末端姿态，返回对应的theta
    void inverseInit(trajMode);//逆运动
    void inverseGo();//逆运动
    void setTh1(double th1c);
    void setTh2(double th2c);
    void setTh3(double th3c);
    void setTh4(double th4c);
    void setTh5(double th5c);
    void setTh6(double th6c);


public:
    const double d1,d4,d6,  a1,a2,a3;

private:


    double th1, th2, th3,th4,th5,th6;//变量θ1，θ2，z，3自由度
    double xpos, ypos, zpos;//末端当前位置
    double nx,ox, ax , ny, oy ,ay,  nz, oz ,az;//T矩阵参数
    double minth1,maxth1,minth2,maxth2,minth3,maxth3,minth4,maxth4,minth5,maxth5,minth6,maxth6;

    Model *baseModel, *arm1Model, *arm2Model, *arm3Model,*arm4Model,*arm5Model,*arm6Model;



    std::vector<Point> path;
    //逆运动的一串姿态
    std::queue<Stance> StPath;  //定义队列，使用的时候弹出元素

    Trajectory * traj;
};




#endif // ROBOT_H




