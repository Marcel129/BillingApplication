#ifndef MY_CLASSS_H
#define MY_CLASSS_H

#include <QObject>
#include <qdebug.h>

class my_classs : public QObject
{
    Q_OBJECT
    QString my_text;
    QStringList combolist;
public:
    Q_PROPERTY(QString my_text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QStringList comboList READ getList NOTIFY listChanged)
    explicit my_classs(QObject *parent = nullptr);
    int foo() {return 2;};

public slots:
    void setText(QString txt){
        my_text = txt;
        emit textChanged();
        qDebug()<<"Ustawiono text! Text: " << txt;
    }
    QString  getText(){
        qDebug() << "Odczytano text!";
        return my_text;
    }
    QStringList getList(){
        return combolist;
    }
    void addToList(const QString & s){
        combolist.push_back(s);
    }
signals:
void textChanged();
void listChanged();
};

#endif // MY_CLASSS_H
