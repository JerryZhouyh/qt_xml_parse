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
#include <QtCore/QObject>
namespace Ui {
class MainWindow;
}

struct NodeInfo{
    QString name;
    QString data;
};



class CoreXmlParse:public QObject
{
    Q_OBJECT
public:
    CoreXmlParse(Ui::MainWindow *uiParam);
    //start xml node
    void startParse();
    //init xml file
    void initXmlFile();
    //write xml
    void writeXml();
private:
    //parse xml node
    int readNode(QDomNode node,int deepCount,QStandardItem* item=NULL);
    //treeView model
    QItemSelectionModel *selectModel;
    QStandardItemModel *model;
    QDomDocument doc;
    QString filePath;
    Ui::MainWindow *ui;
private slots:
    void slotCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
};

#endif // COREXMLPARSE_H
