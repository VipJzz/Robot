#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QPushButton>
#include"line.h"
#include"gltest.h"
#include"setting.h"
#include"robot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDrawRect_triggered();

    void on_actionClear_triggered();

    void on_actionWireFrame_triggered();

    void on_th1Slider_valueChanged(int value);

    void on_th2Slider_valueChanged(int value);

    void on_th3Slider_valueChanged(int value);

    void on_th4Slider_valueChanged(int value);

    void on_th5Slider_valueChanged(int value);

    void on_th6Slider_valueChanged(int value);

    void inputInit(Limit &lim);

    void on_tab_currentChanged(int index);

    void on_switchPosition_clicked();

    void on_actionSet_limit_triggered();

private:
    Ui::MainWindow *ui;
    Setting setLim;
    Robot *robot1;

};

#endif // MAINWINDOW_H
