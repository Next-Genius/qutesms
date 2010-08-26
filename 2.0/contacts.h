#ifndef CONTACTS_H
#define CONTACTS_H

#include <QDialog>

#include "smshttp.h"
#include "ui_contacts.h"
#include "contact.h"

class smshttp;
class Contact;

class Contacts : public QDialog
{
	Q_OBJECT

public:
	Contacts(QWidget *parent = 0);

private:
	Ui::contactWindow ui;

	void updateContacts();
	void updateGroups();
	void parseMembers();
	void updateMembers();

	smshttp *sms;
	Contact *selected;

private slots:
	void changeSelected(QListWidgetItem *current, QListWidgetItem *previous);
	void on_itemDoubleClicked(QListWidgetItem *item);
	void on_pb_contactAdd_clicked();
	void on_pb_contactRemove_clicked();
	void on_contactEdited(Contact *c);
	void on_pb_groupAdd_clicked();
	void on_pb_groupRemove_clicked();
	void on_pb_groupRename_clicked();
	void getMembers();
	void on_pb_memberAdd_clicked();
	void on_pb_memberRemove_clicked();

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void closeEvent(QCloseEvent *event);

};

#endif
