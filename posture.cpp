#include"posture.h"

//从四元数到旋转矩阵
QMatrix4x4 QuatertoRotMatix(const QQuaternion &q)
{
    QMatrix4x4 mat ;
    mat.setToIdentity();
    float x = q.x();
    float y = q.y();
    float z = q.z();
    float w = q.scalar();

    float x2 = x * x;
    float xy = x * y;
    float xz = x * z;
    float y2 = y * y;
    float yz = y * z;
    float z2 = z * z;
    mat(0, 0) = 1 - 2 * (y2 + z2);
    mat(0, 1) = 2 * (xy - w * z);
    mat(0, 2) = 2 * (xz + w * y);
    mat(0, 3) = 0;
    mat(1, 0) = 2 * (xy + w * z);
    mat(1, 1) = 1 - 2 * (x2 + z2);
    mat(1, 2) = 2 * (yz - w * x);
    mat(1, 3) = 0;
    mat(2, 0) = 2 * (xz - w * y);
    mat(2, 1) = 2 * (yz + w * x);
    mat(2, 2) = 1 - 2 * (x2 + y2);
    mat(2, 3) = 0;
    return mat;
}



//旋转矩阵到四元数变换
QQuaternion RotMatixtoQuater( const QMatrix4x4 &rot){
    //先判断R是否为旋转矩阵，R*(RT)=I


    float m11=rot(0,0),m12=rot(0,1),m13=rot(0,2);
    float m21=rot(1,0),m22=rot(1,1),m23=rot(1,2);
    float m31=rot(2,0),m32=rot(2,1),m33=rot(2,2);
    float w,x,y,z;

    //探测四元数中最大的项
    float fourW = m11+m22+m33;
    float fourX = m11-m22-m33;
    float fourY = m22-m11-m33;
    float fourZ = m33-m11-m22;

    //找到四个数中最大的一个，并标记
    int biggestIndex = 0;
    float fourBiggest = fourW;
    if(fourX>fourBiggest){
        fourBiggest= fourX;
        biggestIndex =1;
    }
    if(fourY>fourBiggest){
        fourBiggest = fourY;
        biggestIndex =2;
    }
    if(fourZ>fourBiggest){
        fourBiggest = fourZ;
        biggestIndex =3;
    }
    //计算平方根和除法
    float biggestVal = sqrt(fourBiggest+1.0f)*0.5f;
    float mult = 0.25f/biggestVal;

    /************   计算四元数的值  ****************/
    //https://blog.csdn.net/reasonyuanrobot/article/details/116275578
    //************，右手系，单位四元数转化为旋转矩阵是左手系的转置

    switch(biggestIndex){
        case 0:
            w=biggestVal;
            x=-1*(m23-m32)*mult;
            y=-1*(m31-m13)*mult;
            z=-1*(m12-m21)*mult;
            break;
        case 1:
            x = biggestVal;
            w =-1*(m23-m32)*mult;
            y =(m12+m21)*mult;
            z =(m31+m13)*mult;
            break;
        case 2:
            y =biggestVal;
            w =-1*(m31-m13)*mult;
            x =(m12+m21)*mult;
            z =(m23+m32)*mult;
            break;
        case 3:
            z =biggestVal;
            w =-1*(m12-m21)*mult;
            x =(m31+m13)*mult;
            y =(m23+m32)*mult;
            break;
    }

    return QQuaternion(w,x,y,z);
}

//四元数插值
std::vector<QMatrix4x4> QInterpolation(const QMatrix4x4 &rot1,const QMatrix4x4 &rot2,double Tf,double inteT){
    QQuaternion q1=RotMatixtoQuater(rot1);
    QQuaternion q2=RotMatixtoQuater(rot2);
    qDebug()<<"w="<<q1.scalar()<<" x="<<q1.x()<<" y="<<q1.y()<<" z="<<q1.z();
    qDebug()<<"w="<<q2.scalar()<<" x="<<q2.x()<<" y="<<q2.y()<<" z="<<q2.z();
    int frequency=Tf*0.8/(inteT/1000);//乘以0.5，姿态先于位置到达

    std::vector<QMatrix4x4>result;
    QQuaternion qt;
    QMatrix4x4 mt;
    for(int i=0;i<frequency;i++){
        double t=(double)i/frequency;//t取值范围0-1
        //qDebug()<<"t="<<t;
        qt= (1 - t)*q1 + t*q2;
        //qDebug()<<"w="<<qt.scalar()<<" x="<<qt.x()<<" y="<<qt.y()<<" z="<<qt.z();
        double qtabs=sqrt(qt.x()*qt.x()+qt.y()*qt.y()+qt.z()*qt.z()+qt.scalar()*qt.scalar());
        qt=qt/qtabs;//化单位四元数
        //qDebug()<<"w="<<qt.scalar()<<" x="<<qt.x()<<" y="<<qt.y()<<" z="<<qt.z();
        mt=QuatertoRotMatix(qt);
        result.push_back(mt);
    }
    return result;
}
