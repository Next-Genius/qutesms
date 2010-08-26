#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>

#include "ui_contact.h"
#include "smshttp.h"

class smshttp;

class Contact : public QWidget
{
	Q_OBJECT

public:
	Contact(QWidget *parent = 0, smshttp *sms = NULL, QString *name = NULL, QString *phone = NULL);

	void editContact(bool on);

	Ui::contactWidget ui;
	bool selected;
	QString phone;

private slots:
	void on_pb_contactEdit_clicked();
	void editingDone();

private:
	smshttp *sms;

signals:
	void contactEdited(Contact *c);

protected:
	bool eventFilter(QObject *obj, QEvent *event);

};

#endif // CONTACT_H
