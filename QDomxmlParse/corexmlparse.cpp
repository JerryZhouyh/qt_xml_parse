#include "corexmlparse.h"
#include "ui_mainwindow.h"
/*uiParam:从mainwindow传来的ui界面参数*/
CoreXmlParse::CoreXmlParse(Ui::MainWindow *uiParam)
{
    ui=uiParam;
    model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Name")<<QStringLiteral("info"));
    ui->treeView->setModel(model);
}

void CoreXmlParse::startParse()
{
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    //    QStandardItem* item0 = new QStandardItem("0");
    //    QStandardItem* item1 = new QStandardItem("1");
    //    QStandardItem* item2 = new QStandardItem("2");
    //    model->appendRow(item0);
    //    item0->appendRow(item1);
    //    item1->appendRow(item2);
    int m=0;
    do{
        m = readNode(n,0);
        n = n.nextSibling();
    }while(m);
}

void CoreXmlParse::initXmlFile()
{
    filePath = QFileDialog::getOpenFileName();
    QFile file(filePath);
    if(!file.open(QIODevice::ReadWrite)){
        qDebug()<<"Error!!!can't open file:"<<filePath;
        return;
    }
    if(!doc.setContent(&file)){
        qDebug()<<"Error!!!QDomDocument can't set content";
        file.close();
        return;
    }
    file.close();
}

int CoreXmlParse::readNode(QDomNode node, int deepCount, QStandardItem* item)
{
    if(!node.isNull() && node.isElement()){
        QDomElement e = node.toElement();
        QDomNodeList list = e.childNodes();
        if(item == NULL){
            item = new QStandardItem(e.tagName());
            model->appendRow(item);
        }
        int tempCount = list.count();
        if(tempCount<=1){
            QStandardItem* itemChild = new QStandardItem(e.tagName());
            item->appendRow(itemChild);
            item->setChild(itemChild->index().row(),1,new QStandardItem(e.text()));
            qDebug()<<"   "<<e.tagName()<<":"<<e.text();
        }else{
            QStandardItem* itemChild = new QStandardItem(e.tagName());
            item->appendRow(itemChild);
            qDebug()<<deepCount++<<e.tagName();
            for(int i=0;i<tempCount;i++){
                readNode(list.at(i),deepCount,itemChild);
            }
        }
    }else if(node.isNull()){
        return false;
    }
    return true;
}
