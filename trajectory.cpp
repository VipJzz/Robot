#include "trajectory.h"



//逆运动学
Stance Trajectory::inverseTh(Point i,QMatrix4x4 m,Stance oldst)
{
    double nx=m(0,0),   ox=m(0,1),   ax=m(0,2),
            ny=m(1,0),  oy=m(1,1),  ay=m(1,2),
            nz=m(2,0),  oz=m(2,1),   az=m(2,2);
//    qDebug()<<nx<<"\t"<<ox<<"\t"<<ax<<"\t"<<"\n"
//           <<ny<<"\t"<<oy<<"\t"<<ay<<"\t"<<"\n"
//           <<nz<<"\t"<<oz<<"\t"<<az<<"\t"<<"\n";

    /*  末端工具坐标系转换到机器人末端，平移变换
        [ nx, ox, ax, px - ax*z - nx*x - ox*y]
        [ ny, oy, ay, py - ay*z - ny*x - oy*y]
        [ nz, oz, az, pz - az*z - nz*x - oz*y]
        [  0,  0,  0,                       1]
    */
    double xpos=i.x-ax*d6;
    double ypos=i.y-ay*d6;
    double zpos=i.z-az*d6;

    int singularFlag=1;//singularFlag==0时，代表奇异解
    /*--------------------------------------
            |  th2 th3  |   +th5 |th4    th6|
            |           |   -th5 |th4    th6|
        th1 | ---------  ------- ----------
            |  th2 th3' |   -th5 |th4    th6|
            |           |   -th5 |th4    th6|
        ---- ----------- ------- ----------
            |  th2 th3  |   +th5 |th4    th6|
            |           |   -th5 |th4    th6|
        th1 | --------   ------- ----------
            |  th2 th3' |   +th5 |th4    th6|
            |           |   -th5 |th4    th6|
    -----------------------------------------


      */
    //局部变量覆盖外部global变量
    double th1,th2,th3,th4,th5,th6;
    vector<Stance>solution(8);
    //求逆解的具体步奏
    //th1
    solution[0].th1=atan2(ypos,xpos)*180/M_PI;
    for(vector<Stance>::size_type i=1;i<4;i++){
        solution[i].th1=solution[0].th1;
    }
    solution[4].th1=atan2(-ypos,-xpos)*180/M_PI;
    for(vector<Stance>::size_type i=5;i<8;i++){
        solution[i].th1=solution[4].th1;
    }


    for(vector<Stance>::size_type i=0;i<8;i++){
        //th1 0-3,4-7两组
        if(i==0||i==1||i==2||i==3)th1=solution[0].th1;
        else th1=solution[4].th1;
        //th2参数 随th1变化
        double k1;
        if(abs(sin(th1*M_PI/180))<1e-6)//如果太小就不能做分母，会丧失精度
            k1=xpos/cos(th1*M_PI/180)-a1;//用px
        else
            k1=ypos/sin(th1*M_PI/180)-a1;//用py
        double k2=zpos-d1;
        double K=-(d4*d4+a3*a3-a2*a2-k1*k1-k2*k2)/(2*a2);
        //th3参数 随th1变化
        double m=xpos*cos(th1*M_PI/180)+ypos*sin(th1*M_PI/180)-a1;
        double n=zpos-d1;
        double H=(m*m+n*n-a2*a2-a3*a3-d4*d4)/(2*a2);

        if(k1*k1+k2*k2-K*K<0)singularFlag=0;//sqrt(k1*k1+k2*k2-K*K)无解，无法进行下面的计算
        /**********************************/
        if(i==0||i==1||i==4||i==5){
            solution[i].th2=(atan2(-k2,k1)+atan2(K,sqrt(k1*k1+k2*k2-K*K)))*180/M_PI;
            solution[i].th3=(atan2(a3,d4)-atan2(H,sqrt(a3*a3+d4*d4-H*H)))*180/M_PI;
        }
        else{
            solution[i].th2=(atan2(-k2,k1)+atan2(K,-sqrt(k1*k1+k2*k2-K*K)))*180/M_PI;
            solution[i].th3=(atan2(a3,d4)-atan2(H,-sqrt(a3*a3+d4*d4-H*H)))*180/M_PI;

        }
    }
    //腕关节
    for(vector<Stance>::size_type i=0;i<8;i=i+2){
        th1=solution[i].th1;
        th2=solution[i].th2;
        th3=solution[i].th3;
        //th5 R33
        double C5=ax*cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th3*M_PI/180) - az*cos(th3*M_PI/180)*sin(th2*M_PI/180) - az*cos(th2*M_PI/180)*sin(th3*M_PI/180) + ay*cos(th2*M_PI/180)*cos(th3*M_PI/180)*sin(th1*M_PI/180) - ax*cos(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - ay*sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180);
        double S5=sqrt(1-C5*C5);//双解
        solution[i].th5=atan2(S5,C5)*180/M_PI;
        solution[i+1].th5=atan2(-S5,C5)*180/M_PI;



        if(abs(S5)>1e-6){
              //th4 R13 R23
            double S4=-(ax*sin(th1*M_PI/180) - ay*cos(th1*M_PI/180))/S5;
            double C4=-(az*cos(th2*M_PI/180)*cos(th3*M_PI/180) - az*sin(th2*M_PI/180)*sin(th3*M_PI/180) + ax*cos(th1*M_PI/180)*cos(th2*M_PI/180)*sin(th3*M_PI/180) + ax*cos(th1*M_PI/180)*cos(th3*M_PI/180)*sin(th2*M_PI/180) + ay*cos(th2*M_PI/180)*sin(th1*M_PI/180)*sin(th3*M_PI/180) + ay*cos(th3*M_PI/180)*sin(th1*M_PI/180)*sin(th2*M_PI/180))/S5;

            solution[i].th4=atan2(S4,C4)*180/M_PI;//S5有+-2种
            solution[i+1].th4=atan2(-S4,-C4)*180/M_PI;//==solution[i].th4+-180
               //th6 R31 R32
            double C6=(nx*cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th3*M_PI/180) - nz*cos(th3*M_PI/180)*sin(th2*M_PI/180) - nz*cos(th2*M_PI/180)*sin(th3*M_PI/180) + ny*cos(th2*M_PI/180)*cos(th3*M_PI/180)*sin(th1*M_PI/180) - nx*cos(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - ny*sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180))/S5;
            double S6=-(ox*cos(th1*M_PI/180)*cos(th2*M_PI/180)*cos(th3*M_PI/180) - oz*cos(th3*M_PI/180)*sin(th2*M_PI/180) - oz*cos(th2*M_PI/180)*sin(th3*M_PI/180) + oy*cos(th2*M_PI/180)*cos(th3*M_PI/180)*sin(th1*M_PI/180) - ox*cos(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180) - oy*sin(th1*M_PI/180)*sin(th2*M_PI/180)*sin(th3*M_PI/180))/S5;

            solution[i].th6=atan2(S6,C6)*180/M_PI;//S5有+-2种
            solution[i+1].th6=atan2(-S6,-C6)*180/M_PI;

        }else{//若S5=0,为奇异，th4保持不变
             solution[i].th4=oldst.th4;//oldStance
             solution[i+1].th4=oldst.th4;
             //th6 R21 R22
             double S46=nx*sin(th1*M_PI/180) - ny*cos(th1*M_PI/180);
             double C46=ox*sin(th1*M_PI/180) - oy*cos(th1*M_PI/180);
             solution[i].th6=atan2(S46,C46)*180/M_PI-solution[i].th4;
             solution[i+1].th6=atan2(S46,C46)*180/M_PI-solution[i+1].th4;
        }

    }

    //最优解选取,选择与当前关节角相比运动量最小的一组作为最终解
    vector<Stance>sub_abs_st(8);
    for(vector<Stance>::size_type i=0;i<8;i++){
        sub_abs_st[i].th1=abs(solution[i].th1-oldst.th1);
        sub_abs_st[i].th2=abs(solution[i].th2-oldst.th2);
        sub_abs_st[i].th3=abs(solution[i].th3-oldst.th3);
        sub_abs_st[i].th4=abs(solution[i].th4-oldst.th4);
        sub_abs_st[i].th5=abs(solution[i].th5-oldst.th5);
        sub_abs_st[i].th6=abs(solution[i].th6-oldst.th6);
    }
    double mixsum=0;
    vector<Stance>::size_type index=0;
    for(vector<Stance>::size_type i=0;i<8;i++){
        //分配权重
        double tmp=sub_abs_st[i].th1*3+sub_abs_st[i].th2*3+sub_abs_st[i].th3*2
                +sub_abs_st[i].th4+sub_abs_st[i].th5+sub_abs_st[i].th6;
        if(i==0||tmp<mixsum){
            mixsum=tmp;
            index=i;
        }
    }
//    qDebug()<<" th1="<<solution[index].th1<<" th2="<<solution[index].th2<<" th3="<<solution[index].th3<<
//    " th4="<<solution[index].th4<<" th5="<<solution[index].th5<<" th6="<<solution[index].th6;

    return solution[index];
}

queue<Stance> LinePlanning::planning()
{
    initLine(p1,p2,L,e);//直线初始化
    splanning(L,lim,Tf,St_l,Vt_l,At_l);//规划
    transformLine(St_l,Pt_l,L,e);//转换为坐标

    std::vector<QMatrix4x4> vec_m;
    //rotStart,rotEnd 来自界面输入
    vec_m=QInterpolation(rotStart,rotEnd, Tf, lim.interval);
   // path.clear();//清空正运动时，或之前遗留的path点。

    while(!StPath.empty())StPath.pop();//清空
    //getCurStance();
    StPath.push(initialStance);
    for(int i=0,j=0;i<Pt_l.size();i++){
        //vec_m短0.1
        if(j<vec_m.size()-1){
            j++;
        }
        Stance st=inverseTh(Pt_l[i],vec_m[j],StPath.back());

        StPath.push(st); //画出的轨迹是从p1-p2

//        qDebug()<<" th1="<<st.th1<<" th2="<<st.th2<<" th3="<<st.th3<<
//            " th4="<<st.th4<<" th5="<<st.th5<<" th6="<<st.th6<<"\n";
//        qDebug()<<" x="<<Pt_l[i].x <<" y="<<Pt_l[i].y<<" z="<<Pt_l[i].z<<"\n";
        //path.push_back(Point(Pt_l[i].x,Pt_l[i].y,Pt_l[i].z));//轨迹path暂时设为已知
    }
    return StPath;
}




queue<Stance> CirclePlanning::planning()
{
    initCircle(p1c,p2c,p3c,l_circle);
    splanning(l_circle,lim,Tf,St_c,Vt_c,At_c);
    transformCircle(St_c,Pt_c);
    std::vector<QMatrix4x4> vec_m;

    vec_m=QInterpolation(rotStart,rotEnd, Tf, lim.interval);
   // path.clear();//清空正运动时，或之前遗留的path点。

    while(!StPath.empty())StPath.pop();//清空
    //getCurStance();
    StPath.push(initialStance);
    for(int i=0,j=0;i<Pt_c.size();i++){
        //vec_m短0.1
        if(j<vec_m.size()-1){
            j++;
        }
        Stance st=inverseTh(Pt_c[i],vec_m[j],StPath.back());

        StPath.push(st); //画出的轨迹是从p1-p2
    }
    return StPath;
}
