#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    //setFixedSize(400,400);

}

Setting::~Setting()
{
    delete ui;
}

void Setting::inputInit(Limit &lim){
    lim.A_max=ui->lE_Amax->text().toDouble();
    lim.V_max=ui->lE_Vmax->text().toDouble();
    lim.V_st=ui->IE_Vs->text().toDouble();
    lim.J=ui->IE_J->text().toDouble();
    lim.interval=ui->interval->value();//ms单位

}
