#include "corexmlparse.h"

CoreXmlParse::CoreXmlParse()
{

}

void CoreXmlParse::startParse()
{
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    int m=readNode(n,0);
    while(m){
        n = n.nextSibling();
        m = readNode(n,0);
        //qDebug()<<"m:"<<m;
    }
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

int CoreXmlParse::readNode(QDomNode node, int deepCount)
{
    if(!node.isNull() && node.isElement()){
        QDomElement e = node.toElement();
        QDomNodeList list = e.childNodes();
        int tempCount = list.count();
        if(tempCount<=1){
            qDebug()<<"   "<<e.tagName()<<":"<<e.text();
        }else{
            qDebug()<<deepCount++<<e.tagName();
            for(int i=0;i<tempCount;i++){
                readNode(list.at(i),deepCount);
            }
        }
    }else if(node.isNull()){
       return false;
    }
    return true;
}
