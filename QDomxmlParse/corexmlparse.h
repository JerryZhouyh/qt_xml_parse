#ifndef COREXMLPARSE_H
#define COREXMLPARSE_H

#include <QDomDocument>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QTreeView>
#include <QStandardItemModel>
#include <QMainWindow>
namespace Ui {
class MainWindow;
}
class CoreXmlParse
{
public:
    CoreXmlParse(Ui::MainWindow *uiParam);
    //start xml node
    void startParse();
    //init xml file
    void initXmlFile();
private:
    //parse xml node
    int readNode(QDomNode node,int deepCount,QStandardItem* item=NULL);
    //treeView model
    QStandardItemModel *model;
    QDomDocument doc;
    QString filePath;
    Ui::MainWindow *ui;
};

#endif // COREXMLPARSE_H
