#ifndef CIRCLE_H
#define CIRCLE_H

#include<Eigen/LU>
#include<Eigen/Core>
#include<Eigen/Dense>
#include"global.h"
//给定三点，实现全局变量的初始化
void initCircle(Point p1,Point p2,Point p3,double &Len);//Len传出参数，圆弧长度

//把uvw距离点转为实际xyz坐标点
std::vector<Point> transformCircle(std::vector<double>lt, std::vector<Point>&vec_pt);


extern double r_circle;
extern double l_circle;
extern Eigen::Matrix<double,4,4> Tr;

























#endif // CIRCLE_H
