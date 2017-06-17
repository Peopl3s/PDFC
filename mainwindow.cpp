#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "pdfc.h"
#include "drop.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("PDFC");
    setWindowIcon(QIcon("pdf-odf.png"));

    setqss();
    createMenu();

    QLabel *lpdf=new QLabel ("PDF");
    QLabel *lodt=new QLabel ("ODF");
    QLabel *format=new QLabel ("Select the desired format:");

    pdf=new PDFC;
    QWidget *w=new QWidget;

    title=new QLabel("Download files");
    cmd=new QPushButton("Upload files");
    cmd->setToolTip("Upload files");

    window=new Drop;
    window->setMinimumHeight(300);

    pb=new QProgressBar;

    pdfcmd=new QRadioButton;
    pdfcmd->setCheckable(true);
    odt=new QRadioButton;
    odt->setCheckable(true);

    connect(cmd,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(this,SIGNAL(fileIsOpen()),this,SLOT(Cvt()));
    connect(window,SIGNAL(DropOv()),this, SLOT(Cvt()));
    connect(pdfcmd,SIGNAL(toggled(bool)),pdf,SLOT(setPdf()));
    connect(odt,SIGNAL(toggled(bool)),pdf,SLOT(setOdt()));

    pdfcmd->setChecked(true);

    QHBoxLayout *h=new QHBoxLayout;
    h->addStretch(1);
    h->addWidget(format);
    h->setAlignment(format,Qt::AlignCenter);
    h->addWidget(lpdf);
    h->addWidget(pdfcmd);
    h->addWidget(lodt);
    h->addWidget(odt);
    h->addStretch(1);

    QVBoxLayout *v=new QVBoxLayout;
    v->addWidget(title);
    v->addWidget(window);
    v->addWidget(pb);
    v->setAlignment(Qt::AlignLeft);
    v->addLayout(h);
    v->addWidget(cmd);
    v->addStretch(1);
    w->setLayout(v);

    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openFile()
{
    list.clear();

    QString s=QFileDialog::getOpenFileName(this,"Open File");

    if(!s.isEmpty())
    {
        list<<s;
        emit fileIsOpen();
    }
}
void MainWindow::Cvt()
{
    list+=window->getList();
    pb->reset();
    pb->setRange(0,list.size());

    int x=0;

    while(!list.isEmpty())
    {
        path=list.takeFirst();
        pdf->setPath(path);
        pdf->convert();
        path.clear();
        ++x;
        pb->setValue(x);
        QApplication::processEvents();
    }
    list.clear();
}
void MainWindow::setqss()
{
    QFile file("style.qss");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    this->setStyleSheet(strCSS);
}
void MainWindow::createMenu()
{
    QMenu *m=new QMenu("About");

    QAction *a=new QAction("About",0);
    a->setText("About PDFC");
    a->setShortcut(QKeySequence("CTRL+S"));
    a->setToolTip("Information about PDFC");
    a->setStatusTip("Information about PDFC");
    a->setWhatsThis("Information about PDFC");
    a->setIcon(QPixmap("info.png"));

    connect(a,SIGNAL(triggered(bool)),this,SLOT(info()));

    m->addAction(a);

    menuBar()->addMenu(m);
}

void MainWindow::info()
{
    QMessageBox::information(0,"About","This program is used to convert "
                                       "doc/docx files to pdf or odf format."
                                       " Converted files are saved in the Temp folder the program directory.");
}
