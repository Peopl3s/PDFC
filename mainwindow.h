#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QMainWindow>
#include "pdfc.h"
#include "drop.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void fileIsOpen();
public slots:
    void openFile();
    void Cvt();
    void setqss();
    void createMenu();
    void info();
private:
    Ui::MainWindow *ui;
    PDFC *pdf;
    QLabel *title;
    Drop *window;
    QPushButton *cmd;
    QString path;
    QList<QString> list;
    QProgressBar *pb;
    QRadioButton *pdfcmd,*odt;
};

#endif // MAINWINDOW_H
