#include <QKeyEvent>

#include "contact.h"

Contact::Contact(QWidget *parent, smshttp *sms, QString *name, QString *phone) : QWidget(parent)
{
	this->sms = sms;

	ui.setupUi(this);
	ui.nameEdit->hide();
	ui.phoneEdit->hide();
	ui.lb_name->setText(QString(*name));
 	ui.lb_phone->setText(QString(*phone));

	this->phone = *phone;

	// Filter out weird key return press
	this->installEventFilter(this);

	connect(ui.nameEdit, SIGNAL(returnPressed()), this, SLOT(editingDone()));
	connect(ui.phoneEdit, SIGNAL(returnPressed()), this, SLOT(editingDone()));
}

void Contact::editingDone()
{
	editContact(false);
}

void Contact::on_pb_contactEdit_clicked()
{
	if (!selected)
		return;

	editContact(!ui.nameEdit->isVisible());
}

void Contact::editContact(bool on)
{
	if (on) {
		ui.lb_name->hide();
		ui.lb_phone->hide();
		ui.nameEdit->setText(ui.lb_name->text());
		ui.nameEdit->show();
		ui.phoneEdit->setText(ui.lb_phone->text());
		ui.phoneEdit->show();
		ui.nameEdit->setFocus();

	} else {
		if (!ui.nameEdit->isVisible())
			return;

		if (ui.lb_name->text() != ui.nameEdit->text() ||
		    ui.lb_phone->text() != ui.phoneEdit->text()) {
			sms->webService("DeleteContact", "&ContactTel="+ui.lb_phone->text());
			ui.lb_name->setText(ui.nameEdit->text());
			ui.lb_phone->setText(ui.phoneEdit->text());
			sms->webService("CreateContact", "&ContactTel="+ui.lb_phone->text()+"&ContactName="+ui.lb_name->text());
			emit(contactEdited(this));
		}

		ui.lb_name->show();
		ui.lb_phone->show();
		ui.nameEdit->hide();
		ui.phoneEdit->hide();
	}
}

bool Contact::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent->key() == Qt::Key_Return) {
			return true;
		}
	}

	// standard event processing
	return QObject::eventFilter(obj, event);
}
