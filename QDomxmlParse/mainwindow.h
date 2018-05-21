#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <corexmlparse.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_parseXml_clicked();

    void on_printInfo_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_writeXml_clicked();

private:
    Ui::MainWindow *ui;
    CoreXmlParse *xmlFile;
};

#endif // MAINWINDOW_H
