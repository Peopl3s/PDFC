#include <QtCore>
#include <QtWidgets>
#include <QAxWidget>
#include <QAxObject>
#include <QtWebKit>
#include <QPrinter>
#include <algorithm>
#include "pdfc.h"
PDFC::PDFC(QObject *p):QObject(p)
{
    word= new  QAxObject("Word.Application");
    word->setProperty("DisplayAlerts", 0);

    connect(this,SIGNAL(converted(QString)),this,SLOT(pdf_odf(QString)));

}
void PDFC::convert()
{
    pathfile.replace('//',"\\");
    QString ext=pathfile.mid(pathfile.lastIndexOf('.')+1);

    if (ext=="docx" || ext=="doc")
    {
        QString name=pathfile.mid(pathfile.lastIndexOf("/")+1,pathfile.lastIndexOf(".")-1-pathfile.lastIndexOf("/"));
        QString ws=QDir::currentPath()+"/"+name;

        ws.replace('//',"\\");

        QVariant confirmconversions(false);
        QVariant readonly(false);
        QVariant addtorecentfiles(false);
        QVariant passworddocument("");
        QVariant passwordtemplate("");
        QVariant revert(false);

        word->querySubObject("Documents")->querySubObject("Open(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)", pathfile,confirmconversions, readonly, addtorecentfiles, passworddocument, passwordtemplate,	revert);

        QVariant newFileName(ws);
        QVariant fileFormat(10); //Saving as filtered html
        QVariant LockComments(false);
        QVariant Password("");
        QVariant recent(true);
        QVariant writePassword("");
        QVariant ReadOnlyRecommended(false);

        word->querySubObject("ActiveDocument")->querySubObject("SaveAs(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)",    newFileName, fileFormat, LockComments, Password, recent, writePassword, ReadOnlyRecommended);
        word->querySubObject("ActiveDocument")->dynamicCall("Close (boolean)", false);

        emit  converted(name);

    } else QMessageBox::critical(0,"Error","Wront type of file");
}
void PDFC::pdf_odf(const QString &st)
{

    QFile f(st);
    f.open(QIODevice::ReadOnly);
    QTextStream textstream(&f);

    QString htmlstr;
    htmlstr=textstream.readAll().toUtf8();

    QTextEdit* ptxt = new QTextEdit;
    ptxt->setHtml(htmlstr);

    if(pdff)
    {
        printer=new QPrinter(QPrinter::HighResolution);
        printer->setOutputFormat(QPrinter::PdfFormat);
        printer->setOutputFileName("Temp/"+st+".pdf");
        ptxt->document()->print(printer);
    } else {
        QTextDocumentWriter writer;
        writer.setFormat("odf");
        writer.setFileName("Temp/"+st+".odf");
        writer.write(ptxt->document());
    }
    f.close();
    pathfile.clear();
    f.remove();
}
void PDFC::setPath(const QString &s)
{
    pathfile=s;
}
void PDFC::setPdf()
{
    pdff=true;
}
void PDFC::setOdt()
{
    pdff=false;
}
