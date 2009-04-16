#ifndef SMSHTTP_H
#define SMSHTTP_H

#include <QtGui/QMainWindow>
#include <QSettings>

#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QDialog>

const QString appId="795846979";//795846979



namespace Ui
{
    class smshttpClass;
}

class smshttp : public QMainWindow
{
    Q_OBJECT

public:
    smshttp(QWidget *parent = 0);
    ~smshttp();
    QString userPhone;
    QString userPass;
    QString creditsLeft;
    QString recPhone;
    QString smsText;
    QSettings settings;
       QStringList contactsPhones;
       QStringList contactsNames;
    void showSmsPanel(bool s);
    void showInfo(QString str,bool state);
    void setCreditsLeft(QString val);
    int parseFile(QString file);
    int parseContacts(QString file);
    void download(QString action,QString data);
    void readSettings();
    void getContacts();


    public slots:
    void logIn();
    void showHelp();
    void sendSms();
    void updateChars();
    void showNumber(int num);

private:
    Ui::smshttpClass *ui;


};


#endif // SMSHTTP_H
