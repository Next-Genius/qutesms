#ifndef MEMBER_H
#define MEMBER_H

#include <QWidget>

#include "ui_member.h"
#include "smshttp.h"

class smshttp;

class Member : public QWidget
{
	Q_OBJECT

public:
	Member(QWidget *parent, QString *name = NULL, int index = 0);

	Ui::memberWidget ui;
	int index;
	QString phone;

private:

private slots:
	void on_pb_memberRemove_clicked();


signals:
	void memberRemoved(int index);
};

#endif // MEMBER_H
