#ifndef POSTURE_H
#define POSTURE_H


#include<cmath>
#include<QQuaternion>
#include<QMatrix4x4>
#include<vector>



//从四元数到旋转矩阵
extern QMatrix4x4 QuatertoRotMatix(const QQuaternion &q);

//旋转矩阵到四元数变换
extern QQuaternion RotMatixtoQuater( const QMatrix4x4 &rot);

//四元数插值
extern std::vector<QMatrix4x4> QInterpolation(const QMatrix4x4 &rot1,const QMatrix4x4 &rot2,double Tf,double inteT);



#endif // POSTURE_H
