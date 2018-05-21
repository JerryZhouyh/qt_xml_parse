#include "corexmlparse.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
/*uiParam:从mainwindow传来的ui界面参数*/
CoreXmlParse::CoreXmlParse(Ui::MainWindow *uiParam)
{
    ui=uiParam;
    model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()
         <<QStringLiteral("Name")<<QStringLiteral("info")<<QStringLiteral("lineNum"));
    ui->treeView->setModel(model);
    selectModel = ui->treeView->selectionModel();
    connect(selectModel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(slotCurrentChanged(QModelIndex,QModelIndex)));
}

void CoreXmlParse::startParse()
{
    QDomElement docElem = doc.documentElement();
    //docElem.elementsByTagName()

    QDomNode n = docElem.firstChild();

    model->clear();
    model->setHorizontalHeaderLabels(QStringList()
           <<QStringLiteral("Name")<<QStringLiteral("info")<<QStringLiteral("lineNum"));
    int m=0;
    do{
        m = readNode(n,0);
        n = n.nextSibling();
    }while(m);
}

void CoreXmlParse::initXmlFile()
{
    filePath = QFileDialog::getOpenFileName(NULL,"chose","F://QTProject/QT_Project");
    QFile file(filePath);
    if(!file.open(QIODevice::ReadWrite)){
        qDebug()<<"Error!!!can't open file:"<<filePath;
        return;
    }
    doc.clear();
    if(!doc.setContent(&file)){
        qDebug()<<"Error!!!QDomDocument can't set content";
        file.close();
        return;
    }
    file.close();
}

void CoreXmlParse::writeXml()
{
    QString floderPath = QFileDialog::getExistingDirectory()+"/new.xml";
    QFile file(floderPath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
    QTextStream out(&file);
    out<<doc;
    file.close();
}

int CoreXmlParse::readNode(QDomNode node, int deepCount, QStandardItem* item)
{
    if(!node.isNull() && node.isElement()){
        QDomElement e = node.toElement();
        QDomNodeList list = e.childNodes();
        int flag=1;//用于判断传入的Item是否为空值
        if(item == NULL){
            item = new QStandardItem(e.tagName());
            model->appendRow(item);
            flag=0;
        }
        int tempCount = list.count();
        if(tempCount<=1){
            if(flag){
                QStandardItem* itemChild = new QStandardItem(e.tagName());
                item->appendRow(itemChild);
                item->setChild(itemChild->index().row(),1,new QStandardItem(e.text()));
                item->setChild(itemChild->index().row(),2,new QStandardItem( QString::number(e.lineNumber())));
                qDebug()<<"   "<<e.tagName()<<":"<<e.text()<<e.lineNumber()<<" "<<e.columnNumber();
            }

        }else{
            QStandardItem* itemChild;
            if(flag){
                itemChild = new QStandardItem(e.tagName());
                item->appendRow(itemChild);
            }else{
                itemChild =item;
            }
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

void CoreXmlParse::slotCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QString name,data,lineNum;
    if(previous.column()==0){
        name = previous.data().toString();
        data = previous.sibling(previous.row(),1).data().toString();
        lineNum = previous.sibling(previous.row(),2).data().toString();
    }else{
        name = previous.sibling(previous.row(),0).data().toString();
        data = previous.data().toString();
        lineNum = previous.sibling(previous.row(),2).data().toString();
    }
    qDebug()<<"name:"<<name<<"data:"<<data;
    QDomElement root = doc.documentElement();
    QDomNodeList list = root.elementsByTagName(name);
    int tempCount = list.count();
    qDebug()<<"tempCount:"<<tempCount;
    for(int i=0;i<list.count();i++){
        QDomElement e = list.at(i).toElement();
        if(e.lineNumber()==lineNum.toInt())
           e.firstChild().setNodeValue(data);
    }
}
