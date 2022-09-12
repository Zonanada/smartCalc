#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


extern "C" {
    #include "../ponat.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    // void digist_numbers();
    // void on_pushButton_dot_clicked();
    void operations();
//    void on_pushButton_5_clicked();
    void on_pushButton_peer_clicked();
};
#endif // MAINWINDOW_H
