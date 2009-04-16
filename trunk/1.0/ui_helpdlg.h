/********************************************************************************
** Form generated from reading ui file 'helpdlg.ui'
**
** Created: Thu Apr 16 18:16:12 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_HELPDLG_H
#define UI_HELPDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;
    QLabel *label;

    void setupUi(QWidget *Form)
    {
    if (Form->objectName().isEmpty())
        Form->setObjectName(QString::fromUtf8("Form"));
    Form->resize(400, 195);
    buttonBox = new QDialogButtonBox(Form);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(40, 160, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    textBrowser = new QTextBrowser(Form);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setEnabled(true);
    textBrowser->setGeometry(QRect(10, 10, 371, 151));
    label = new QLabel(Form);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(20, 160, 91, 18));
    QFont font;
    font.setPointSize(7);
    label->setFont(font);

    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    textBrowser->setHtml(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">QuteSms allow you to send Sms from your smshttp account. if you don't already have one please go <a href=\"http://www.smshttp.com\"><span style=\" text-decoration: underline; color:#0000ff;\">here</span></a> to create one.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Copyright smsHttp.com 2009.</p>\n"
"<p style=\"-qt-paragrap"
        "h-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Uses </span><a href=\"oxygen Icons\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">oxygen Icons</span></a><span style=\" font-size:8pt;\"> under GPL license.Coded by Aminesay. </span></p></body></html>", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Form", "Version 1.0 b", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDLG_H
