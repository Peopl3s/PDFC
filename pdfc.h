#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QAxWidget>
#include <QAxObject>
#include <QtWebKit>
#include <QPrinter>
#include <algorithm>

class PDFC: public QObject{
    Q_OBJECT
protected:
    QString pathfile;
    QAxObject *word;
    QPrinter *printer;
    bool pdff;
public:
    explicit PDFC(QObject *p=0);
    PDFC(const PDFC&)=delete;
    PDFC& operator=(const PDFC&)=delete;
    virtual ~PDFC()
    {
       word->dynamicCall("Quit()");
       delete word;
    }
signals:
    void converted(const QString&);
public slots:
    void convert();
    void pdf_odf(const QString&);
    void setPath(const QString&);
    void setPdf();
    void setOdt();
};

