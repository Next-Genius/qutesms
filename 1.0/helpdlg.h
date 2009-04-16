#ifndef HELPDLG_H
#define HELPDLG_H

 //CONFIG DIALOG INTERFACE
#include "ui_help.h"
//#include <QtGui>
#include <QtGui/QDialog>


  class HelpDlg : public QDialog, private Ui::Ui_Dialog {
     Q_OBJECT

	 public:
     	 SettingsDialog(QWidget *parent = 0);


 };



#endif // UI_HELP_H
