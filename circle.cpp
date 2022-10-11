#include"circle.h"



//0号默认不使用

//.h声明，这里定义

double r_circle=0;//圆弧半径
double l_circle;//圆弧长度
Eigen::Matrix<double,4,4> Tr;//齐次变换矩阵，包含坐标轴、圆心信息

//给定三点，实现全局变量的初始化
void initCircle(Point p1,Point p2,Point p3,double &Len){
    double A[4];
    double B[4];
    double C[4];
    double D[4];

    //2个约束条件：1、三点共面 2、 三点到圆心距离相等   ，得到方程组系数矩阵
    A[1] = p1.y*p2.z - p1.y*p3.z - p1.z*p2.y + p1.z*p3.y + p2.y*p3.z - p3.y*p2.z;
    B[1] = -p1.x*p2.z + p1.x*p3.z + p1.z*p2.x - p1.z*p3.x - p2.x*p3.z + p3.x*p2.z;
    C[1] = p1.x*p2.y - p1.x*p3.y - p1.y*p2.x + p1.y*p3.x + p2.x*p3.y - p3.x*p2.y;
    D[1] = -p1.x*p2.y*p3.z + p1.x*p3.y*p2.z +p2.x*p1.y*p3.z- p3.x*p1.y*p2.z - p2.x*p3.y*p1.z+ p3.x*p2.y*p1.z;

    A[2] = 2*(p2.x - p1.x);
    B[2] = 2*(p2.y - p1.y);
    C[2] = 2*(p2.z - p1.z);
    D[2] = p1.x*p1.x + p1.y*p1.y + p1.z*p1.x - p2.x*p2.x - p2.y*p2.y - p2.z*p2.z;

    A[3] = 2*(p3.x - p1.x);
    B[3] = 2*(p3.y - p1.y);
    C[3] = 2*(p3.z - p1.z);
    D[3] = p1.x*p1.x + p1.y*p1.y + p1.z*p1.x - p3.x*p3.x - p3.y*p3.y - p3.z*p3.z;

    Eigen::Matrix<double,3,3> a_center;//系数矩阵
    a_center<<A[1],B[1],C[1],
            A[2],B[2],C[2],
            A[3],B[3],C[3];
    Eigen::Matrix<double,3,3> a_inverse=a_center.inverse();//系数矩阵的逆
    //std::cout<<a_center<<std::endl;
    //std::cout<<"inverse: "<<a_inverse<<std::endl;
    if(a_inverse.size()==0){
        std::cout<<"输入有误，矩阵不可逆"<<std::endl;
        return;
    }
    //解方程组，求圆心，半径
    Eigen::Matrix<double,3,1> p0_c;//圆心
    Eigen::Matrix<double,3,1> D_m={D[1],D[2],D[3]};
    p0_c=-a_inverse*D_m;
    double x0,y0,z0;
    x0=p0_c(0,0);
    y0=p0_c(1,0);
    z0=p0_c(2,0);

    double r_tmp = (p1.x-x0) * (p1.x-x0) + (p1.y-y0) * (p1.y-y0)+(p1.z-z0) * (p1.z-z0);
    r_circle = sqrt(r_tmp);
    printf("x0=%.3lf  y0=%.3lf  z0=%.3lf,  R=%.3lf\n",x0,y0,z0,r_circle);
    std::cout<<std::endl;//刷新缓冲区


    //新坐标轴的建立
    Eigen::Matrix<double,3,1> u;//u
    double det_u=sqrt((p1.x-x0) * (p1.x-x0) +(p1.y-y0) * (p1.y-y0)+(p1.z-z0) *(p1.z-z0));
    u<<(p1.x-x0)/det_u, (p1.y-y0)/det_u,(p1.z-z0)/det_u;
    //std::cout<<"u= "<<u<<std::endl;
    Eigen::Matrix<double,3,1> w;//w
    double det_w=sqrt(A[1] * A[1]+B[1]* B[1]+C[1]*C[1]);
    w<<A[1]/det_w,B[1]/det_w,C[1]/det_w;
    //std::cout<<"w= "<<w<<std::endl;
    Eigen::Matrix<double,3,1> v=w.cross(u);//v 两个相互垂直的单位向量，×乘后仍是单位向量
    //std::cout<<"v= "<<v<<std::endl;

    //四阶齐次变换矩阵的合成 ,提取块大小为(p,q),起始于(i,j)	matrix.block(i,j,p,q)


    Eigen::Matrix<double,3,3>R;
    R<<u,v,w;
    Tr.block<3,3>(0,0)=R;
    Tr.block<3,1>(0,3)=p0_c;//圆心
    Tr.block(3,0,1,4)<<0,0,0,1;
    std::cout<<"Tr= \n"<<Tr<<std::endl;
    //求逆
    Eigen::Matrix<double,4,4>Tr_in=Tr.inverse();
    std::cout<<"Tr_in= \n"<<Tr_in<<std::endl;


    //求p3新坐标
    Eigen::Matrix<double,4,1>uvw3;  //新坐标
    Eigen::Matrix<double,4,1>xyz3;
    xyz3<<p3.x,p3.y,p3.z,1;
    uvw3=Tr_in*xyz3;
    //求θ3,为弧度类型
    double theta3=0;
    if(uvw3(1,0)>=0){
        theta3= atan2(uvw3(1,0),uvw3(0,0));
    }else {
        theta3=2*M_PI + atan2(uvw3(1,0),uvw3(0,0));

    }

    Len=theta3*r_circle;//圆弧长度
    std::cout<<"Len= "<<Len<<std::endl;

}


//把uvw距离点转为实际xyz坐标点, vec_pt存放插补点
std::vector<Point> transformCircle(std::vector<double>lt, std::vector<Point>&vec_pt){
    double theta;
    Eigen::Matrix<double,4,1>xyz_t;
    Eigen::Matrix<double,4,1>uvw_t;
    Point p_tmp;
    vec_pt.clear();
    for(std::vector<double>::size_type i=0;i<lt.size();i++){
        theta=lt[i]/r_circle;
        uvw_t(0,0)=r_circle*cos(theta);
        uvw_t(1,0)=r_circle*sin(theta);
        uvw_t(2,0)=0;
        uvw_t(3,0)=1;
        xyz_t=Tr*uvw_t; //用了Tr
        p_tmp.x=xyz_t(0,0);
        p_tmp.y=xyz_t(1,0);
        p_tmp.z=xyz_t(2,0);
        vec_pt.push_back(p_tmp);
    }

    return vec_pt;
}


