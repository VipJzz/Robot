#include "robot.h"


Robot::Robot() :
    d1(140),d4(160),d6(60),a1(60),a2(100),a3(55),//d6=0.6暂时设为0

    th1(0),th2(0),th3(0),th4(0),th5(0),th6(0),
    xpos(0), ypos(0), zpos(0),
    minth1(-170),maxth1(170), minth2(-90),maxth2(155),
    minth3(-88),maxth3(180),minth4(-90),maxth4(90),
    minth5(-135),maxth5(135),minth6(-180),maxth6(180){

}
//正向运动，存储路径点，不是界面
void Robot::forwardGo()
{
    xpos =a1*cos(th1*M_PI/180) + d4*cos((th2 + th3)*M_PI/180)*cos(th1*M_PI/180) + a2*cos(th1*M_PI/180)*sin(th2*M_PI/180) + d6*cos((th2 + th3)*M_PI/180)*cos(th1*M_PI/180)*cos(th5*M_PI/180)
            + a3*cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + a3*cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180) - d6*sin(th1*M_PI/180)*sin(th4*M_PI/180)*sin(th5*M_PI/180)
            - d6*cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th4*M_PI/180)*sin(th3*M_PI/180)*sin(th5*M_PI/180) - d6*cos(th1*M_PI/180)*cos(th3*M_PI/180)*cos(th4*M_PI/180)*sin(th2*M_PI/180)*sin(th5*M_PI/180);
    ypos = a1*sin(th1*M_PI/180) + d4*cos((th2 + th3)*M_PI/180)*sin(th1*M_PI/180) + a2*sin(th1*M_PI/180)*sin(th2*M_PI/180) + d6*cos((th2 + th3)*M_PI/180)*cos(th5*M_PI/180)*sin(th1*M_PI/180)
            + a3*cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + a3*cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180) + d6*cos(th1*M_PI/180)*sin(th4*M_PI/180)*sin(th5*M_PI/180)
            - d6*cos(th2*M_PI/180)*cos(th4*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180)*sin(th5*M_PI/180) - d6*cos(th3*M_PI/180)*cos(th4*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th5*M_PI/180);
    zpos = d1 + a3*cos((th2 + th3)*M_PI/180) - d4*sin((th2 + th3)*M_PI/180) + a2*cos(th2*M_PI/180) - (d6*cos((th2 + th3)*M_PI/180)*sin((th4 + th5)*M_PI/180))/2
            - d6*sin((th2 + th3)*M_PI/180)*cos(th5*M_PI/180) + (d6*sin((th4 - th5)*M_PI/180)*cos((th2 + th3)*M_PI/180))/2;
    //    nx= sin(th6*M_PI/180)*(cos(th4*M_PI/180)*sin(th1*M_PI/180) - sin(th4*M_PI/180)*(cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180))) + cos(th6*M_PI/180)*(cos(th5*M_PI/180)*(sin(th1*M_PI/180)*sin(th4*M_PI/180) + cos(th4*M_PI/180)*(cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180))) - sin(th5*M_PI/180)*(cos(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th3*M_PI/180)));
    //    ny= - sin(th6*M_PI/180)*(cos(th1*M_PI/180)*cos(th4*M_PI/180) + sin(th4*M_PI/180)*(cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180))) - cos(th6*M_PI/180)*(cos(th5*M_PI/180)*(cos(th1*M_PI/180)*sin(th4*M_PI/180) - cos(th4*M_PI/180)*(cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180))) + sin(th5*M_PI/180)*(sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - cos(th2*M_PI/180)*cos(th3*M_PI/180)*sin(th1*M_PI/180)));
    //    nz= - cos(th6*M_PI/180)*(sin(th5*M_PI/180)*(cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th2*M_PI/180)) - cos(th4*M_PI/180)*cos(th5*M_PI/180)*(cos(th2*M_PI/180)*cos(th3*M_PI/180) - sin(th2*M_PI/180)*sin(th3*M_PI/180))) - sin(th4*M_PI/180)*sin(th6*M_PI/180)*(cos(th2*M_PI/180)*cos(th3*M_PI/180) - sin(th2*M_PI/180)*sin(th3*M_PI/180));
    //    ox= cos(th6*M_PI/180)*(cos(th4*M_PI/180)*sin(th1*M_PI/180) - sin(th4*M_PI/180)*(cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180))) - sin(th6*M_PI/180)*(cos(th5*M_PI/180)*(sin(th1*M_PI/180)*sin(th4*M_PI/180) + cos(th4*M_PI/180)*(cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180))) - sin(th5*M_PI/180)*(cos(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th3*M_PI/180)));
    //    oy=sin(th6*M_PI/180)*(cos(th5*M_PI/180)*(cos(th1*M_PI/180)*sin(th4*M_PI/180) - cos(th4*M_PI/180)*(cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180))) + sin(th5*M_PI/180)*(sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - cos(th2*M_PI/180)*cos(th3*M_PI/180)*sin(th1*M_PI/180))) - cos(th6*M_PI/180)*(cos(th1*M_PI/180)*cos(th4*M_PI/180) + sin(th4*M_PI/180)*(cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180)));
    //    oz=sin(th6*M_PI/180)*(sin(th5*M_PI/180)*(cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th2*M_PI/180)) - cos(th4*M_PI/180)*cos(th5*M_PI/180)*(cos(th2*M_PI/180)*cos(th3*M_PI/180) - sin(th2*M_PI/180)*sin(th3*M_PI/180))) - cos(th6*M_PI/180)*sin(th4*M_PI/180)*(cos(th2*M_PI/180)*cos(th3*M_PI/180) - sin(th2*M_PI/180)*sin(th3*M_PI/180));
    //    ax= - sin(th5*M_PI/180)*(sin(th1*M_PI/180)*sin(th4*M_PI/180) + cos(th4*M_PI/180)*(cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180))) - cos(th5*M_PI/180)*(cos(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th3*M_PI/180));
    //    ay=sin(th5*M_PI/180)*(cos(th1*M_PI/180)*sin(th4*M_PI/180) - cos(th4*M_PI/180)*(cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180))) - cos(th5*M_PI/180)*(sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - cos(th2*M_PI/180)*cos(th3*M_PI/180)*sin(th1*M_PI/180));
    //    az= - cos(th5*M_PI/180)*(cos(th2*M_PI/180)*sin(th3*M_PI/180) + cos(th3*M_PI/180)*sin(th2*M_PI/180)) - cos(th4*M_PI/180)*sin(th5*M_PI/180)*(cos(th2*M_PI/180)*cos(th3*M_PI/180) - sin(th2*M_PI/180)*sin(th3*M_PI/180));


    path.push_back(Point(xpos, ypos, zpos));
    if(path.size() > 1000) path.erase(path.begin());
}


//逆解，得到一串位姿
void Robot::inverseInit(trajMode mode)
{
    switch(mode){
    case line:
        traj=new LinePlanning(d1,d4,d6,a1,a2,a3);
        break;

    case circle:
        traj=new CirclePlanning(d1,d4,d6,a1,a2,a3);
        break;

    }

    traj->initialStance=getCurStance();
    while(!StPath.empty()) StPath.pop();
    StPath=traj->planning();
}





