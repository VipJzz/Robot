#ifndef GLOBAL_H
#define GLOBAL_H
#include<vector>
#include<iostream>
#include<QMatrix4x4>
/*
    包含全局变量，便于梳理关系
    全局变量声明


*/
class Point{
public:
    Point()=default;
    Point(const double &tx,const double &ty,const double &tz):x(tx),y(ty),z(tz){

    }
    Point setPiont(const double &tx,const double &ty,const double &tz){
        x = tx;
        y = ty;
        z = tz;
        return *this;
    }
public:
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Limit{
public:
    double V_max=200;
    double A_max=1000;
    double J=5000;
    double V_st=0;    //初始速度，默认为0
    double interval=10;//单位毫秒

};
//line.h
extern  Point p1,p2,e;
extern  Limit lim;//约束
extern  double Tf;
extern  double  L;
extern  std::vector<double>St_l;//记录每个时隔的S
extern  std::vector<Point>Pt_l;//S转化来的坐标  point_t_line
extern std::vector<double>Vt_l;//记录每个时隔的V
extern std::vector<double>At_l;//记录每个时隔的A

extern int bugflag;//debug选项，查看曲线阶段，为1就debug

//circle
extern  Point p1c,p2c,p3c;
extern  std::vector<double> St_c;//记录每个时隔的S
extern std::vector<double> Vt_c;//记录每个时隔的V
extern std::vector<double> At_c;//记录每个时隔的A
extern  std::vector<Point>Pt_c;//S转化来的坐标

//Q
extern QMatrix4x4 rotStart,rotEnd;//声明全局变量


enum trajMode{line,circle};


#endif // GLOBAL_H
