#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xmlFile = new CoreXmlParse(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parseXml_clicked()
{
    xmlFile->initXmlFile();
}

void MainWindow::on_printInfo_clicked()
{
    xmlFile->startParse();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

//    qDebug()<<index.data().toString();
//    qDebug()<<index.row();
//    qDebug()<<index.column();
}







void MainWindow::on_writeXml_clicked()
{
    xmlFile->writeXml();
}
