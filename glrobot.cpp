#include "glrobot.h"



glrobot::glrobot() :
    d1(140),d4(160),d6(60),a1(60),a2(100),a3(55),//d6=0.6暂时设为0
    th1(0),th2(0),th3(0),th4(0),th5(0),th6(0)
   {
    baseModel=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                        ,"D:/QQT/OpenGL/GL13 MyRobot/model/1.stl");
    arm1Model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                          ,"D:/QQT/OpenGL/GL13 MyRobot/model/2.stl");
    arm2Model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                         ,"D:/QQT/OpenGL/GL13 MyRobot/model/3.stl");
    arm3Model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                        ,"D:/QQT/OpenGL/GL13 MyRobot/model/4.stl");

   arm4Model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                   ,"D:/QQT/OpenGL/GL13 MyRobot/model/5.stl");
   arm5Model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                   ,"D:/QQT/OpenGL/GL13 MyRobot/model/6.stl");
   arm6Model=new Model(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>()
                   ,"D:/QQT/OpenGL/GL13 MyRobot/model/7.stl");
}
//根据当前theta计算路径点push进path，然后显示
void glrobot::displayPath()
{

    double xpos =a1*cos(th1*M_PI/180) + d4*cos((th2 + th3)*M_PI/180)*cos(th1*M_PI/180) + a2*cos(th1*M_PI/180)*sin(th2*M_PI/180) + d6*cos((th2 + th3)*M_PI/180)*cos(th1*M_PI/180)*cos(th5*M_PI/180)
            + a3*cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + a3*cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180) - d6*sin(th1*M_PI/180)*sin(th4*M_PI/180)*sin(th5*M_PI/180)
            - d6*cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th4*M_PI/180)*sin(th3*M_PI/180)*sin(th5*M_PI/180) - d6*cos(th1*M_PI/180)*cos(th3*M_PI/180)*cos(th4*M_PI/180)*sin(th2*M_PI/180)*sin(th5*M_PI/180);
    double ypos = a1*sin(th1*M_PI/180) + d4*cos((th2 + th3)*M_PI/180)*sin(th1*M_PI/180) + a2*sin(th1*M_PI/180)*sin(th2*M_PI/180) + d6*cos((th2 + th3)*M_PI/180)*cos(th5*M_PI/180)*sin(th1*M_PI/180)
            + a3*cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + a3*cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180) + d6*cos(th1*M_PI/180)*sin(th4*M_PI/180)*sin(th5*M_PI/180)
            - d6*cos(th2*M_PI/180)*cos(th4*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180)*sin(th5*M_PI/180) - d6*cos(th3*M_PI/180)*cos(th4*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th5*M_PI/180);
    double  zpos = d1 + a3*cos((th2 + th3)*M_PI/180) - d4*sin((th2 + th3)*M_PI/180) + a2*cos(th2*M_PI/180) - (d6*cos((th2 + th3)*M_PI/180)*sin((th4 + th5)*M_PI/180))/2
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



    glBegin(GL_POINTS);//点、线
    //glLineWidth(2.0f);
    //glBegin(GL_LINE_STRIP);
    for(auto i:path){
        //!!注意修改轨迹-----缩放显示
        glVertex3d(i.x*0.01, i.y*0.01, i.z*0.01);

    }
    // qDebug()<<"x:"<<path.back().x<<"  y:"<<path.back().y<<"  z:"<<path.back().z<<"\n";
    glEnd();
    glLineWidth(1.0f);


}



void glrobot::display(QOpenGLShaderProgram &shader)
{   QMatrix4x4 model;
    model.scale(0.01,0.01,0.01);
    shader.setUniformValue("model",model);
    baseModel->Draw(shader);

    model.translate(0.0, 0, 60);
    model.rotate(th1+90,0,0,1.0); //90是调整坐标系，与实际计算无关，只和OpenGL显示有关
    shader.setUniformValue("model",model);
    arm1Model->Draw(shader);

    model.translate(0.0, -60, 80);  //d1=60+80=140 ,a1=60
    model.rotate(th2, 1, 0, 0);
    shader.setUniformValue("model",model);
    arm2Model->Draw(shader);

    model.translate(0.0, 0, 100);   //a2=100
    model.rotate(th3, 1, 0, 0);
    shader.setUniformValue("model",model);
    arm3Model->Draw(shader);

    model.translate(0.0, 0, 55);  //a3=55
    model.rotate(th4, 0, -1, 0);//绕-1，能改变旋转方向
    shader.setUniformValue("model",model);
    arm4Model->Draw(shader);

    model.translate(0.0, -160, 0);      //d4=160
    model.rotate(th5+90, 1, 0, 0);
    shader.setUniformValue("model",model);
    arm5Model->Draw(shader);

    model.translate(0.0, 0, 0);        //d6=60
    model.rotate(th6, 0, 0, 1);
    shader.setUniformValue("model",model);
    arm6Model->Draw(shader);

//    model.setToIdentity();
}

//刷新逆逆运动位姿，一帧
void glrobot::inverseGo()
{   //队列，保持有序
    if(!StPath.empty()){
        Stance st=StPath.front();
        StPath.pop();
        th1=st.th1;
        th2=st.th2;
        th3=st.th3;
        th4=st.th4;
        th5=st.th5;
        th6=st.th6;
    }
}
