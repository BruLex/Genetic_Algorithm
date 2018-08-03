#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generic.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Generic generic [CNT_GEN];
    Generic genBuf [CNT_GEN];
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sort();
    void count_normFx(int gran);
    void rulet();
    void GenDev();
    int global_iter=0;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
