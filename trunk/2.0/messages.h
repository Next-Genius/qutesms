#ifndef MESSAGES_H
#define MESSAGES_H

#include <QDialog>

#include "smshttp.h"
#include "ui_messages.h"
#include "message.h"

class smshttp;
class Message;

class Messages : public QDialog
{
	Q_OBJECT

public:
	Messages(QWidget *parent = 0);

private slots:
	void on_cb_autoDelete_stateChanged(int state);
	void on_cb_display_currentIndexChanged(int index);
	void on_messageDeleted(QString &id);
	void on_pb_earlyFirst_clicked();
	void on_pb_oldFirst_clicked();

private:
	void parseLogMessages();

	Ui::messageWindow ui;
	smshttp *sms;
protected:
	void closeEvent(QCloseEvent *event);
};

#endif
