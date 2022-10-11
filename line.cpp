#include "line.h"
#include<QDebug>
#include<fstream>
#include<iostream>



 //两点直线规划的参数初始化
void initLine(Point p1,Point p2,double &L,Point &e){
    //向量传出
    e.setPiont(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
    //pow(double x, double y);x的y次方
    //总长度L 传出
    L=sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2)+pow(p2.z-p1.z,2));
}



 //实现给定距离和约束的S加减速规划，返回一个vector保存点的相对位置,通过引用传递修改变量s,v,a,lim
 std::vector<double> splanning(double L,Limit &lim,double &Tf,std::vector<double>&s,std::vector<double>&v ,std::vector<double>&a){


     double T1 = lim.A_max / lim.J;
     double T2 = (lim.V_max - lim.V_st) / lim.A_max - T1;
     double T7, T5, T3;
     T7 = T5 = T3 = T1;
     double T6 = T2;
     //总时间 传出
     Tf= (lim.A_max * (lim.V_max - lim.V_st)) / (lim.V_max * lim.J) + L / lim.V_max + pow((lim.V_max - lim.V_st), 2) / (lim.A_max * lim.V_max);
     double T4 = Tf - 2 * lim.A_max / lim.J - 2 * (lim.V_max - lim.V_st) / lim.A_max;



     //限制速度，确保T4符合要求，能够达到理论上的最高速度
     while(T4<=0||T2<=0){
         if(T4<=0){
             lim.V_max=0.9*lim.V_max;
             //重新计算
             T1 = lim.A_max / lim.J;
             T2 = (lim.V_max - lim.V_st) / lim.A_max - T1;
             T7 = T5 = T3 = T1;
             T6 = T2;
             Tf= (lim.A_max * (lim.V_max - lim.V_st)) / (lim.V_max * lim.J) + L / lim.V_max + pow((lim.V_max - lim.V_st), 2) / (lim.A_max * lim.V_max);
             T4 = Tf - 2 * lim.A_max / lim.J - 2 * (lim.V_max - lim.V_st) / lim.A_max;

         }
         //限制加速度，确保T1符合要求，能够达到理论上的最高加速度
         if(T2<=0){
             lim.A_max=0.9*lim.A_max;
             //重新计算
             T1 = lim.A_max / lim.J;
             T2 = (lim.V_max - lim.V_st) / lim.A_max - T1;
             T7 = T5 = T3 = T1;
             T6 = T2;
             Tf= (lim.A_max * (lim.V_max - lim.V_st)) / (lim.V_max * lim.J) + L / lim.V_max + pow((lim.V_max - lim.V_st), 2) / (lim.A_max * lim.V_max);
             T4 = Tf - 2 * lim.A_max / lim.J - 2 * (lim.V_max - lim.V_st) / lim.A_max;

         }
     }
     //验证L是否等于S；
     //double Sref = lim.V_max * Tf - lim.A_max*(lim.V_max - lim.V_st) / lim.J - pow(lim.V_max - lim.V_st, 2) / lim.A_max;

     double time_t = 0;


     //初始化--计算出固定值t1-7
     double s_temp[8];
     double v_temp[8];
     double t[8];
     t[0] = 0;
     t[1] = T1;
     t[2] = T1+T2;
     t[3] = T1 + T2 + T3 ;
     t[4] = T1 + T2 + T3 + T4 ;
     t[5] = T1 + T2 + T3 + T4 + T5;
     t[6] = T1 + T2 + T3 + T4 + T5 + T6;
     t[7] = T1 + T2 + T3 + T4 + T5 + T6 + T7;

     //初始化--计算出固定值V1-7
     v_temp[1] = lim.V_st + 0.5 * lim.J * T1*T1;
     v_temp[2] = v_temp[1] + lim.J*T1*T2;
     v_temp[3] = v_temp[2] + lim.J * T1 * T3 - 0.5 * lim.J * T3*T3;
     v_temp[4] = v_temp[3];
     v_temp[5] = v_temp[4] - 0.5 * lim.J * T5 * T5;
     v_temp[6] = v_temp[5] - lim.J * T5 * T6;
     v_temp[7] = v_temp[6] - lim.J * T5 * T7 + 0.5 * lim.J * T7 * T7;

     //初始化--计算出固定值S1-7
     s_temp[1]=lim.V_st * T1 + lim.J * pow(T1, 3) / 6;//S1
     s_temp[2] = s_temp[1] + v_temp[1] * T2 + lim.J * T1 * T2 * T2 / 2; // S2
     s_temp[3] = s_temp[2] + v_temp[2] * T3 + lim.J * T1 * T3 * T3 / 2 - lim.J * pow(T3, 3) / 6;
     s_temp[4] = s_temp[3] + v_temp[3] * T4;
     s_temp[5] = s_temp[4] + v_temp[4] * T5 - lim.J * pow(T5, 3) / 6;
     s_temp[6] = s_temp[5] + v_temp[5] * T6 - lim.J * T5 * T6 * T6 / 2;//S6
     s_temp[7] = s_temp[6] + v_temp[6] * T7 - lim.J * T5 * T7 * T7 / 2 + lim.J * pow(T7, 3) / 6;


     //注意clear
     s.clear();
     v.clear();
     a.clear();

     //根据时间插补
     while (time_t<=Tf)
     {
         if(time_t<=t[1]){
             s.push_back(lim.V_st * (time_t - t[0]) + lim.J * pow(time_t - t[0], 3)/6);
             a.push_back(lim.J * time_t);
             v.push_back(lim.V_st + 0.5 * lim.J * pow(time_t, 2));
             if(bugflag==1)s.push_back(1*10);

         }else if(time_t<=t[2]){
             s.push_back(s_temp[1] + v_temp[1] * (time_t - t[1]) + 0.5 * lim.J * T1 * pow(time_t - t[1], 2));
             a.push_back(lim.A_max);
             v.push_back(v_temp[1] + lim.J * T1 * (time_t - t[1]));
             if (bugflag == 1)s.push_back(2*10);

         }else if(time_t<=t[3]){
             s.push_back(s_temp[2] + v_temp[2] * (time_t - t[2]) + 0.5 * lim.J * T1 * pow(time_t - t[2], 2)-lim.J*pow(time_t -t[2], 3)/6);
             a.push_back(lim.A_max-lim.J*(time_t-t[2]));
             v.push_back(v_temp[2] + lim.J * T1 * (time_t - t[2]) - 0.5 * lim.J * pow(time_t - t[2], 2));

             if (bugflag == 1)s.push_back(3*10);
         }else if(time_t<=t[4]){
             s.push_back(s_temp[3] + v_temp[3] * (time_t - t[3]));
             a.push_back(0);
             v.push_back(v_temp[3]);
             if (bugflag == 1)s.push_back(4*10);

         }else if(time_t<=t[5]){
             s.push_back(s_temp[4] + v_temp[4] * (time_t - t[4]) - lim.J * pow(time_t - t[4], 3) / 6);
             a.push_back(-lim.J*(time_t-t[4]));
             v.push_back(v_temp[4] - 0.5 * lim.J * pow(time_t - t[4], 2));

             if(bugflag==1)s.push_back(5*10);
         }else if(time_t<=t[6]){
             s.push_back(s_temp[5] + v_temp[5] * (time_t - t[5]) -0.5*lim.J*T5*pow(time_t - t[5], 2));
             a.push_back(-lim.A_max);
             v.push_back(v_temp[5] -lim.J * T5 * (time_t - t[5]) );

             if(bugflag==1)s.push_back(6*10);
         }else if(time_t<=t[7]){
             s.push_back(s_temp[6] + v_temp[6] * (time_t -t[6])-0.5*lim.J*T5*pow(time_t - t[6], 2)+lim.J*pow(time_t - t[6], 3)/6);
             a.push_back(-lim.A_max+lim.J*(time_t-t[6]));
             v.push_back(v_temp[6] - lim.J * T5 * (time_t - t[6]) + 0.5 * lim.J * pow(time_t - t[6], 2));

             if(bugflag==1)s.push_back(7*10);

             if (time_t + lim.interval/1000 >= Tf){
                 time_t = Tf;
             }
         }
         time_t += lim.interval/1000;//lim.interval>1是ms,
     }
     return s;

 }
//直线插补 抽象的S传入，返回具体的3维坐标类型,参数通过引用传递
std::vector<Point>transformLine(std::vector<double>s,std::vector<Point>&p,double l,Point e){
    //注意clear
    p.clear();//暂存坐标点，用过一次数据就旧了
    Point p_tmp;
    for(auto i:s){
        //得到各个分量坐标
        p_tmp.setPiont(e.x*i/l+p1.x,e.y*i/l+p1.y,e.z*i/l+p1.z);
        p.push_back(p_tmp);
    }
    return p;
}


//实现把有用数据存入文件
bool saveDate(char const* filename,std::vector<Point>p,Limit lim,double Tf){
    std::ifstream f(filename);
    std::fstream file;
    if(f.good()){//文件存在
        file.open(filename,std::ios::out);
    }else{//文件不存在，创建文件
        std::fstream file(filename);
        file.open(filename,std::ios::out);
    }
    //打开文件失败则返回false
    if (!file.is_open()) {
           return false;
    }
    for (std::vector<Point>::size_type i = 0; i < p.size();i++){
        file << p[i].x<<"\t"<<p[i].y<<"\t"<<p[i].z<<std::endl;
    }
    file <<"V_max="<<lim.V_max<<std::endl;
    file <<"A_max="<<lim.A_max<<std::endl;
    file <<"J="<<lim.J<<std::endl;
    file <<"V_st="<<lim.V_st<<std::endl;
    file <<"interval="<<lim.interval<<std::endl;
    file <<"Tf="<<Tf<<std::endl;
    file.close();
    return true;
}

//实现定时发送，把坐标值依时间间隔发送。，结合其他通讯方式
/*
 * bool sendDate(std::vector<Point>p,Limit lim,double Tf){
    QString array;
    char buffer[50];
    for(auto i:p){
     sprintf(buffer, "x:%.2f\ty:%.2f\tz:%.2f\n", i.m_x,i.m_y,i.m_z);
      qDebug()<<buffer;
      array+=QString(QLatin1String(buffer));
    }
    return true;
}
*/
