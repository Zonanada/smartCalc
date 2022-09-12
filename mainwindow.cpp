#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <iostream>
#include <string.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::operations()
{
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

    if(ui->result_show->text() == "0") ui->result_show->setText("");
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
    if(button->text() == "x") new_label = ui->result_show->text()+"*";
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


    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_peer_clicked()
{
    std::string cstr = ui->result_show->text().toStdString().substr(0,30);
    char *str = new char(255);
    for (int i =0; i < cstr.size(); i++) {
        *(str+i) = cstr[i];
        *(str+i+1) = '\0';
    }
    std::cout << str << std::endl << "\n";
    ponat(str);
    std::cout << str << std::endl << "\n";
    cstr = str;
    QString label = QString::fromUtf8(cstr.c_str());

    ui->result_show->setText(label);
    delete str;

    ui->pushButton_CE->setText("AC");



}

