#ifndef SETTING_H
#define SETTING_H
#include<QPushButton>
#include"line.h"
#include"gltest.h"
#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

    void inputInit(Limit &lim);



private:
    Ui::Setting *ui;
};

#endif // SETTING_H
