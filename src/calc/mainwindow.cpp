#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <iostream>
#include <string.h>
#include <math.h>
#include <cmath>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    listenConnect();
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::buildGraph(char *str) {
    QLineSeries *series = new QLineSeries();
    QChart *chart = new QChart();
    double formX = ui->formX->value();
    double upToX = ui->upToX->value();
    double formY = ui->formY->value();
    double upToY = ui->upToY->value();
    int tangens = strstr(str, "tan") ? 1 : 0;

    for (double i = formX; i < upToX + 0.01; i += 0.05) {
        char *strRun = changeXOnDouble(str, i);
        while(strchr(strRun, 'X') != NULL) {
            char *ptr = changeXOnDouble(strRun, i);
            free(strRun);
            strRun = ptr;
    }
        char *strNum = strRun ? ponat(strRun) : NULL;
        if (strcmp(strNum, "Incorrect input") != 0) {
            double numAtof = atof(strNum);
                if (tangens) {
                    *series << QPointF(i, numAtof) << QPointF(i, numAtof+0.05);
                    chart->addSeries(series);
                    series = new QLineSeries();
                } else {
                    *series << QPointF(i, numAtof);
                }
        }
        if(strRun) free(strRun);
        if(strNum) free(strNum);
    }


    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(formX, upToX);
    chart->axes(Qt::Vertical).first()->setRange(formY, upToY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(720, 520);
    chartView->setParent(ui->horizontalFrame);
}

void MainWindow::listenConnect() {
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_left_bkt, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_right_bkt, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_multiplay, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_stage, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_CE, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_peer, SIGNAL(clicked()), this, SLOT(peer()));
    connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph()));
}


void MainWindow::operations() {
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;
    if (button->text() == "CE") {
        new_label = ui->result_show->text();
        new_label.resize(new_label.size() - 1);
    }
    if (button->text() == "AC") {
        new_label = "0";
        ui->pushButton_CE->setText("CE");
    }

    if (ui->result_show->text() == "0" && button->text() != "." && button->text() != "+" && button->text() != "-") {
        ui->result_show->setText("");
    }

    if(button->text() == "+") new_label = ui->result_show->text()+"+";
    if(button->text() == "0") new_label = ui->result_show->text()+"0";
    if(button->text() == "1") new_label = ui->result_show->text()+"1";
    if(button->text() == "2") new_label = ui->result_show->text()+"2";
    if(button->text() == "3") new_label = ui->result_show->text()+"3";
    if(button->text() == "4") new_label = ui->result_show->text()+"4";
    if(button->text() == "5") new_label = ui->result_show->text()+"5";
    if(button->text() == "6") new_label = ui->result_show->text()+"6";
    if(button->text() == "7") new_label = ui->result_show->text()+"7";
    if(button->text() == "8") new_label = ui->result_show->text()+"8";
    if(button->text() == "9") new_label = ui->result_show->text()+"9";
    if(button->text() == ".") new_label = ui->result_show->text()+".";
    if(button->text() == "(") new_label = ui->result_show->text()+"(";
    if(button->text() == ")") new_label = ui->result_show->text()+")";
    if(button->text() == "+") new_label = ui->result_show->text()+"+";
    if(button->text() == "mod") new_label = ui->result_show->text()+"mod";
    if(button->text() == "*") new_label = ui->result_show->text()+"*";
    if(button->text() == "/") new_label = ui->result_show->text()+"/";
    if(button->text() == "-") new_label = ui->result_show->text()+"-";
    if(button->text() == "sin") new_label = ui->result_show->text()+"sin(";
    if(button->text() == "^") new_label = ui->result_show->text()+"^";
    if(button->text() == "tan") new_label = ui->result_show->text()+"tan(";
    if(button->text() == "√") new_label = ui->result_show->text()+"sqrt(";
    if(button->text() == "ln") new_label = ui->result_show->text()+"log10(";
    if(button->text() == "acos") new_label = ui->result_show->text()+"acos(";
    if(button->text() == "cos") new_label = ui->result_show->text()+"cos(";
    if(button->text() == "log") new_label = ui->result_show->text()+"log(";
    if(button->text() == "asin") new_label = ui->result_show->text()+"asin(";
    if(button->text() == "atan") new_label = ui->result_show->text()+"atan(";
    if(button->text() == "X") new_label = ui->result_show->text()+"X";

    ui->result_show->setText(new_label);

}

void MainWindow::peer() {
    std::string cstr = ui->result_show->text().toStdString().substr(0,50);
    char *str = new char();
    for (int i =0; i < cstr.size(); i++) {
        *(str+i) = cstr[i];
        *(str+i+1) = '\0';
    }

    char *result = ponat(str);
    cstr = result;
    QString label = QString::fromUtf8(cstr.c_str());

    ui->result_show->setText(label);
    free(result);

    ui->pushButton_CE->setText("AC");
}


void MainWindow::graph() {
    QString outputStr = ui->result_show->text();
    std::string cstr = outputStr.toStdString().substr(0,30);
    double formX = ui->formX->value();
    double upX = ui->upToX->value();
    double formY = ui->formY->value();
    double upY = ui->upToY->value();
    ui->setupUi(this);
    ui->formX->setValue(formX);
    ui->upToX->setValue(upX);
    ui->formY->setValue(formY);
    ui->upToY->setValue(upY);
    ui->result_show->setText(outputStr);
    char *str = new char();
    for (int i =0; i < cstr.size(); i++) {
        *(str+i) = cstr[i];
        *(str+i+1) = '\0';
    }
    char *ptr = strchr(str, 'X');


    if(ptr != NULL) {
        buildGraph(str);

    } else {
        ui->result_show->setText("Incorrect input");
    }

    ui->pushButton_CE->setText("AC");

    listenConnect();
    delete str;
}

