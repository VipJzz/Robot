#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include<vector>
#include<queue>
#include"posture.h"
#include"line.h"
#include"circle.h"

using namespace std;
struct Stance{          //记录逆运动学中的姿态，6个theta为一个姿态
    double th1;
    double th2;
    double th3;
    double th4;
    double th5;
    double th6;
};
//轨迹规划器
class Trajectory
{
public:
    Trajectory();
    Trajectory(double d1,double d4,double d6,double a1,double a2,double a3):
        d1(d1),d4(d4),d6(d6),a1(a1),a2(a2),a3(a3){}

    virtual queue<Stance> planning()=0;
   // virtual ~Trajectory();

private:

    const double d1,d4,d6,  a1,a2,a3;   //
public:
   Stance initialStance;
   std::queue<Stance> StPath;
   Stance inverseTh(Point i,QMatrix4x4 m,Stance oldst);
};


class LinePlanning :public Trajectory
{
public:
    LinePlanning(double d1,double d4,double d6,double a1,double a2,double a3):
        Trajectory(d1,d4,d6,  a1,a2,a3){}

    virtual queue<Stance>  planning() override;

};

class CirclePlanning :public Trajectory
{
public:
    CirclePlanning(double d1,double d4,double d6,double a1,double a2,double a3):
        Trajectory(d1,d4,d6,  a1,a2,a3){}
    virtual queue<Stance> planning() override;

};












#endif // TRAJECTORY_H
