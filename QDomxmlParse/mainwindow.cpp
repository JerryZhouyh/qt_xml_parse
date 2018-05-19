#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parseXml_clicked()
{
    xmlFile.initXmlFile();
}

void MainWindow::on_printInfo_clicked()
{
    xmlFile.startParse();
}
