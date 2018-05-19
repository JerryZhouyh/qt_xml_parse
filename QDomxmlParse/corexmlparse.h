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

class CoreXmlParse
{
public:
    CoreXmlParse();
    //start xml node
    void startParse();
    //init xml file
    void initXmlFile();
private:
    //parse xml node
    int readNode(QDomNode node,int deepCount);
    //treeView model
    QStandardItemModel *model;
    QDomDocument doc;
    QString filePath;
};

#endif // COREXMLPARSE_H
