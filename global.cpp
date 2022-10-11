#include"global.h"

//定义  基本参数------h头文件声明，cpp文件定义，如果在头文件里定义，其他文件一包含头文件，那么就重复定义了。
//声明之所以放在头文件，就是包含头文件就不用多余的声明了

//line
 Point p1(60,190,190),p2(185,100,250),e;
 Limit lim;
 double Tf=0;//共用的Tf
 double  L=0;
 std::vector<double>St_l;
std::vector<double>Vt_l;
 std::vector<double>At_l;
 std::vector<Point>Pt_l;

 int bugflag =0;//默认为0；


 //circle
 Point p1c,p2c,p3c;//确定圆弧的三个输入点
 std::vector<double> St_c;//记录每个时隔的S
 std::vector<double> Vt_c;//记录每个时隔的V
 std::vector<double> At_c;//记录每个时隔的A
 std::vector<Point>Pt_c;//S转化来的坐标


 //Q
 QMatrix4x4   rotStart(1,0,0,0,
                   0,0,1,0,
                   0,-1,0,0,
                   0,0,0,1);

 QMatrix4x4   rotEnd(-1, 0,0,0,
                   0, 1,0,0,
                   0,0,-1,0,
                   0,0,0,1);
