#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setCentralWidget(ui->openGLWidget);//会把GL全屏，其他控件



    resize(1200,800);
    //setFixedSize(400,400);

    connect(ui->PBinit,&QPushButton::clicked,this,[=](){
        inputInit(lim); //包括一切输入

    });




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDrawRect_triggered()
{
    ui->openGLWidget->drawShape(GLWidget::Rect);
}

void MainWindow::on_actionClear_triggered()
{
    ui->openGLWidget->drawShape(GLWidget::None);
}

void MainWindow::on_actionWireFrame_triggered()
{
     ui->openGLWidget->setWireFraem(ui->actionWireFrame->isChecked());
}



void MainWindow::on_th1Slider_valueChanged(int value)
{
     ui->openGLWidget->m_robot->setTh1(value);
}


void MainWindow::on_th2Slider_valueChanged(int value)
{
    ui->openGLWidget->m_robot->setTh2(value);
}


void MainWindow::on_th3Slider_valueChanged(int value)
{
    ui->openGLWidget->m_robot->setTh3(value);
}


void MainWindow::on_th4Slider_valueChanged(int value)
{
    ui->openGLWidget->m_robot->setTh4(value);
}


void MainWindow::on_th5Slider_valueChanged(int value)
{
    ui->openGLWidget->m_robot->setTh5(value);
}


void MainWindow::on_th6Slider_valueChanged(int value)
{
    ui->openGLWidget->m_robot->setTh6(value);
}


void MainWindow::inputInit(Limit &lim){
    //修改的都是全局变量
    setLim.inputInit(lim);

    rotStart(0, 0)=ui->r11->text().toFloat();
    rotStart(0, 1)=ui->r12->text().toFloat();
    rotStart(0, 2)=ui->r13->text().toFloat();
    rotStart(1, 0)=ui->r21->text().toFloat();
    rotStart(1, 1)=ui->r22->text().toFloat();
    rotStart(1, 2)=ui->r23->text().toFloat();
    rotStart(2, 0)=ui->r31->text().toFloat();
    rotStart(2, 1)=ui->r32->text().toFloat();
    rotStart(2, 2)=ui->r33->text().toFloat();
    rotEnd(0, 0)=ui->r11_2->text().toFloat();
    rotEnd(0, 1)=ui->r12_2->text().toFloat();
    rotEnd(0, 2)=ui->r13_2->text().toFloat();
    rotEnd(1, 0)=ui->r21_2->text().toFloat();
    rotEnd(1, 1)=ui->r22_2->text().toFloat();
    rotEnd(1, 2)=ui->r23_2->text().toFloat();
    rotEnd(2, 0)=ui->r31_2->text().toFloat();
    rotEnd(2, 1)=ui->r32_2->text().toFloat();
    rotEnd(2, 2)=ui->r33_2->text().toFloat();
    if(ui->comboBox->currentIndex()==0){    //直线


        p1.setPiont(ui->startX->text().toDouble(),
                    ui->startY->text().toDouble(),
                    ui->startZ->text().toDouble() );
        p2.setPiont(ui->targetX->text().toDouble(),
                    ui->targetY->text().toDouble(),
                    ui->targetZ->text().toDouble() );
        ui->openGLWidget->m_robot->inverseInit(line);   //robot初始化应该放在外部参数输入完之后
    }else if(ui->comboBox->currentIndex()==1){


        p1c.setPiont(ui->startX->text().toDouble(),
                    ui->startY->text().toDouble(),
                    ui->startZ->text().toDouble() );
        p3c.setPiont(ui->targetX->text().toDouble(),
                    ui->targetY->text().toDouble(),
                    ui->targetZ->text().toDouble() );
        p2c.setPiont(ui->midx->text().toDouble(),
                    ui->midy->text().toDouble(),
                    ui->midz->text().toDouble() );
        ui->openGLWidget->m_robot->inverseInit(circle);//robot初始化应该放在外部参数输入完之后
    }

}

void MainWindow::on_tab_currentChanged(int index)
{
    if(index==0){   //tab的index 在UI编辑页面可以查看
        ui->openGLWidget->invflag=true;
    } else{
        ui->openGLWidget->invflag=false;
    }
}


void MainWindow::on_switchPosition_clicked()
{
    QString startx=ui->startX->text();
    QString starty=ui->startY->text();
    QString startz=ui->startZ->text();
    ui->startX->setText(ui->targetX->text());
    ui->startY->setText(ui->targetY->text());
    ui->startZ->setText(ui->targetZ->text());
    ui->targetX->setText(startx);
    ui->targetY->setText(starty);
    ui->targetZ->setText(startz);

}


void MainWindow::on_actionSet_limit_triggered()
{
    //Setting *setLim=new Setting;    //创建在堆区，程序结束不会释放
    setLim.show();  //确保只有一份，放在mainwindow类的private

}

