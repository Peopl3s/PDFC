#pragma once
#include <QtWidgets>
class Drop final : public QLabel {
    Q_OBJECT
private:
    QList<QString> listOfpaths;
signals:
    void DropOv();
public slots:
    QList<QString> getList() const
    {
        return listOfpaths;
    }

protected:
    virtual void dragEnterEvent(QDragEnterEvent* pe) override
    {
        listOfpaths.clear();
        if (pe->mimeData()->hasFormat("text/uri-list")) {
            pe->acceptProposedAction();
        }
    }
    virtual void dropEvent(QDropEvent* pe) override
    {
        listOfpaths.clear();

        QList<QUrl> urlList = pe->mimeData()->urls();
        QString str;

        foreach(QUrl url, urlList)
        {
            str += url.toString() + "\n";
            listOfpaths.push_back(url.toString());
        }

        setText("Dropped:\n" + str);
        emit DropOv();
    }
    virtual void paintEvent(QPaintEvent *e) override
    {
        QPainter p(this);
        QPen pen(Qt::DashLine);
        pen.setColor(Qt::cyan);
        pen.setWidth(2);
        pen.setCapStyle(Qt::RoundCap);
        p.setPen(pen);
        p.drawRect(this->rect().topLeft().x()+10,this->rect().topLeft().y()+5,this->rect().bottomRight().x()-20,this->rect().bottomRight().y()-10);

        QLabel::paintEvent(e);
    }

public:
    explicit Drop(QWidget* pwgt = 0) : QLabel("Drop Area", pwgt)
    {
        setFrameStyle(QFrame::StyledPanel);
        setAlignment(Qt::AlignCenter);
        setStyleSheet("QLabel {color: black ;padding: 15px; }");
        setAcceptDrops(true);
    }
    ~Drop(){}
    Drop(const Drop&)=delete;
    Drop& operator=(const Drop&)=delete;
};

