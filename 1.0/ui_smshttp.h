/********************************************************************************
** Form generated from reading ui file 'smshttp.ui'
**
** Created: Thu Apr 16 20:29:22 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SMSHTTP_H
#define UI_SMSHTTP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_smshttpClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *logFrame;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *userPhone;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *userPass;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *logInPB;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *saveSettingsCb;
    QPushButton *helpPB;
    QFrame *smsFrame;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *recPhone;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QComboBox *contactsCB;
    QPlainTextEdit *smsText;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_2;
    QPushButton *sendPB;
    QLabel *statusLbl;
    QFrame *statusFrame;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *creditsLeft;
    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *charLeft;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *smshttpClass)
    {
    if (smshttpClass->objectName().isEmpty())
        smshttpClass->setObjectName(QString::fromUtf8("smshttpClass"));
    smshttpClass->resize(520, 364);
    centralWidget = new QWidget(smshttpClass);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    logFrame = new QFrame(centralWidget);
    logFrame->setObjectName(QString::fromUtf8("logFrame"));
    logFrame->setMaximumSize(QSize(253, 137));
    logFrame->setFrameShape(QFrame::StyledPanel);
    logFrame->setFrameShadow(QFrame::Raised);
    gridLayout_2 = new QGridLayout(logFrame);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setMargin(11);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label = new QLabel(logFrame);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout_2->addWidget(label);

    userPhone = new QLineEdit(logFrame);
    userPhone->setObjectName(QString::fromUtf8("userPhone"));

    horizontalLayout_2->addWidget(userPhone);


    gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_2 = new QLabel(logFrame);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout->addWidget(label_2);

    userPass = new QLineEdit(logFrame);
    userPass->setObjectName(QString::fromUtf8("userPass"));
    userPass->setEchoMode(QLineEdit::Password);

    horizontalLayout->addWidget(userPass);


    gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    logInPB = new QPushButton(logFrame);
    logInPB->setObjectName(QString::fromUtf8("logInPB"));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/dialog-ok-apply.png")), QIcon::Normal, QIcon::Off);
    logInPB->setIcon(icon);

    horizontalLayout_3->addWidget(logInPB);


    gridLayout_2->addLayout(horizontalLayout_3, 2, 0, 1, 1);

    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    saveSettingsCb = new QCheckBox(logFrame);
    saveSettingsCb->setObjectName(QString::fromUtf8("saveSettingsCb"));

    horizontalLayout_8->addWidget(saveSettingsCb);

    helpPB = new QPushButton(logFrame);
    helpPB->setObjectName(QString::fromUtf8("helpPB"));
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/help-about.png")), QIcon::Normal, QIcon::Off);
    helpPB->setIcon(icon1);

    horizontalLayout_8->addWidget(helpPB);


    gridLayout_2->addLayout(horizontalLayout_8, 3, 0, 1, 1);


    gridLayout->addWidget(logFrame, 0, 0, 1, 1);

    smsFrame = new QFrame(centralWidget);
    smsFrame->setObjectName(QString::fromUtf8("smsFrame"));
    smsFrame->setMinimumSize(QSize(256, 100));
    smsFrame->setFrameShape(QFrame::StyledPanel);
    smsFrame->setFrameShadow(QFrame::Raised);
    gridLayout_3 = new QGridLayout(smsFrame);
    gridLayout_3->setSpacing(6);
    gridLayout_3->setMargin(11);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    label_6 = new QLabel(smsFrame);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_7->addWidget(label_6);

    recPhone = new QLineEdit(smsFrame);
    recPhone->setObjectName(QString::fromUtf8("recPhone"));

    horizontalLayout_7->addWidget(recPhone);


    gridLayout_3->addLayout(horizontalLayout_7, 0, 0, 1, 1);

    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    label_3 = new QLabel(smsFrame);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setMaximumSize(QSize(84, 169));

    horizontalLayout_9->addWidget(label_3);

    contactsCB = new QComboBox(smsFrame);
    contactsCB->setObjectName(QString::fromUtf8("contactsCB"));

    horizontalLayout_9->addWidget(contactsCB);


    gridLayout_3->addLayout(horizontalLayout_9, 1, 0, 1, 1);

    smsText = new QPlainTextEdit(smsFrame);
    smsText->setObjectName(QString::fromUtf8("smsText"));

    gridLayout_3->addWidget(smsText, 2, 0, 1, 1);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    pushButton_2 = new QPushButton(smsFrame);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    QIcon icon2;
    icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/edit-clear.png")), QIcon::Normal, QIcon::Off);
    pushButton_2->setIcon(icon2);

    horizontalLayout_4->addWidget(pushButton_2);

    sendPB = new QPushButton(smsFrame);
    sendPB->setObjectName(QString::fromUtf8("sendPB"));
    sendPB->setEnabled(true);
    QIcon icon3;
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/mail-mark-unread.png")), QIcon::Normal, QIcon::Off);
    sendPB->setIcon(icon3);

    horizontalLayout_4->addWidget(sendPB);


    gridLayout_3->addLayout(horizontalLayout_4, 3, 0, 1, 1);


    gridLayout->addWidget(smsFrame, 0, 1, 3, 1);

    statusLbl = new QLabel(centralWidget);
    statusLbl->setObjectName(QString::fromUtf8("statusLbl"));
    QPalette palette;
    QBrush brush(QColor(26, 44, 204, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    QBrush brush1(QColor(116, 115, 111, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    statusLbl->setPalette(palette);
    QFont font;
    font.setPointSize(11);
    statusLbl->setFont(font);
    statusLbl->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(statusLbl, 1, 0, 1, 1);

    statusFrame = new QFrame(centralWidget);
    statusFrame->setObjectName(QString::fromUtf8("statusFrame"));
    statusFrame->setMinimumSize(QSize(184, 38));
    statusFrame->setFrameShape(QFrame::StyledPanel);
    statusFrame->setFrameShadow(QFrame::Raised);
    layoutWidget = new QWidget(statusFrame);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(8, 8, 134, 21));
    horizontalLayout_6 = new QHBoxLayout(layoutWidget);
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setMargin(11);
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    creditsLeft = new QLabel(layoutWidget);
    creditsLeft->setObjectName(QString::fromUtf8("creditsLeft"));
    creditsLeft->setMinimumSize(QSize(52, 18));
    creditsLeft->setMaximumSize(QSize(90, 54));

    horizontalLayout_6->addWidget(creditsLeft);

    label_4 = new QLabel(layoutWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_6->addWidget(label_4);

    layoutWidget1 = new QWidget(statusFrame);
    layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
    layoutWidget1->setGeometry(QRect(10, 30, 202, 22));
    horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setMargin(11);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    charLeft = new QLabel(layoutWidget1);
    charLeft->setObjectName(QString::fromUtf8("charLeft"));
    charLeft->setMinimumSize(QSize(200, 0));

    horizontalLayout_5->addWidget(charLeft);


    gridLayout->addWidget(statusFrame, 2, 0, 1, 1);

    smshttpClass->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(smshttpClass);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 520, 26));
    smshttpClass->setMenuBar(menuBar);
    mainToolBar = new QToolBar(smshttpClass);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    smshttpClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(smshttpClass);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    smshttpClass->setStatusBar(statusBar);

#ifndef QT_NO_SHORTCUT
    label->setBuddy(userPhone);
    label_2->setBuddy(userPass);
    label_6->setBuddy(recPhone);
#endif // QT_NO_SHORTCUT

    QWidget::setTabOrder(userPhone, userPass);
    QWidget::setTabOrder(userPass, logInPB);
    QWidget::setTabOrder(logInPB, saveSettingsCb);
    QWidget::setTabOrder(saveSettingsCb, recPhone);
    QWidget::setTabOrder(recPhone, smsText);
    QWidget::setTabOrder(smsText, sendPB);
    QWidget::setTabOrder(sendPB, pushButton_2);

    retranslateUi(smshttpClass);
    QObject::connect(logInPB, SIGNAL(toggled(bool)), statusFrame, SLOT(setShown(bool)));
    QObject::connect(smsText, SIGNAL(modificationChanged(bool)), sendPB, SLOT(setShown(bool)));
    QObject::connect(pushButton_2, SIGNAL(clicked()), smsText, SLOT(clear()));

    QMetaObject::connectSlotsByName(smshttpClass);
    } // setupUi

    void retranslateUi(QMainWindow *smshttpClass)
    {
    smshttpClass->setWindowTitle(QApplication::translate("smshttpClass", "smshttp", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("smshttpClass", "Number   :", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("smshttpClass", "Password :", 0, QApplication::UnicodeUTF8));
    logInPB->setText(QApplication::translate("smshttpClass", "Log In", 0, QApplication::UnicodeUTF8));
    saveSettingsCb->setText(QApplication::translate("smshttpClass", "Remeber Me", 0, QApplication::UnicodeUTF8));
    helpPB->setText(QApplication::translate("smshttpClass", "Help", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("smshttpClass", "Send To :", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("smshttpClass", "Contacts:", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("smshttpClass", "Clear", 0, QApplication::UnicodeUTF8));
    sendPB->setText(QApplication::translate("smshttpClass", "Send", 0, QApplication::UnicodeUTF8));
    statusLbl->setText(QApplication::translate("smshttpClass", "Welcome", 0, QApplication::UnicodeUTF8));
    creditsLeft->setText(QString());
    label_4->setText(QApplication::translate("smshttpClass", "Credits left.", 0, QApplication::UnicodeUTF8));
    charLeft->setText(QString());
    Q_UNUSED(smshttpClass);
    } // retranslateUi

};

namespace Ui {
    class smshttpClass: public Ui_smshttpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMSHTTP_H
