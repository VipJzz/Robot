#ifndef POINT_H
#define POINT_H

#include <QWidget>
#include<QString>
#include<cmath>
#include <string>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>

#include"global.h"


void initLine(Point p1,Point p2,double &L,Point &e);
std::vector<double> splanning(double L,Limit &lim,double &Tf,std::vector<double>&s,std::vector<double>&v ,std::vector<double>&a);
std::vector<Point>transformLine(std::vector<double>s,std::vector<Point>&p,double l,Point e);
bool saveDate(char const* filename,std::vector<Point>p,Limit lim,double Tf);
//bool sendDate(std::vector<Point>p,Limit lim,double Tf);


#endif // POINT_H
