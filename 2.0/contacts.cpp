#include <QListWidgetItem>
#include <QDomDocument>
#include <QKeyEvent>

#include "ui_add.h"
#include "contacts.h"

Contacts::Contacts(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pb_done, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.lw_contacts, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(changeSelected(QListWidgetItem *, QListWidgetItem *)));
	connect(ui.lw_contacts, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_itemClicked(QListWidgetItem *)));
	connect(ui.lw_contacts, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(on_itemDoubleClicked(QListWidgetItem *)));
 	connect(ui.cb_groups, SIGNAL(currentIndexChanged(int)), this, SLOT(getMembers()));

	this->installEventFilter(this);

	sms = (smshttp *) parent;
	selected = NULL;

	updateContacts();
 	updateGroups();
	ui.cb_groups->setCurrentIndex(0);
}

void Contacts::updateContacts()
{
	
	ui.lw_contacts->blockSignals(true);
	ui.lw_contacts->clear();

	sms->getContacts();

	for (int i = 0; i < sms->contactNames.size(); i++) {
		QListWidgetItem *item = new QListWidgetItem();
		Contact *c = new Contact(ui.lw_contacts, sms,
					 (QString *)&sms->contactNamesSorted.at(i),
					 (QString *)&sms->contactPhones.at(sms->findContactIndex(sms->contactNamesSorted.at(i))));
		connect(c, SIGNAL(contactEdited(Contact *)), this, SLOT(on_contactEdited(Contact *)));


		QSize qs = QSize(200, 40);
		item->setSizeHint(qs);

		ui.lw_contacts->addItem(item);
		ui.lw_contacts->setItemWidget(item, c);
	}

	ui.lw_contacts->blockSignals(false);
}

void Contacts::updateGroups()
{
	disconnect(ui.cb_groups, SIGNAL(currentIndexChanged(int)), this, SLOT(getMembers()));
		//ui.cb_groups->blockSignals(true);

	ui.cb_groups->clear();
	ui.cb_groups->addItems(sms->groupNamesSorted);
	getMembers();
	updateMembers();

	connect(ui.cb_groups, SIGNAL(currentIndexChanged(int)), this, SLOT(getMembers()));
		//ui.cb_groups->blockSignals(false);
}

void Contacts::changeSelected(QListWidgetItem *current, QListWidgetItem *previous)
{
	Contact *c = (Contact *)ui.lw_contacts->itemWidget(previous);
	if (c != NULL) {
		c->selected = false;
		c->ui.pb_contactEdit->setEnabled(false);
		c->editContact(false);
	}

	qDebug() << "changeSelected !";
	c = (Contact *)ui.lw_contacts->itemWidget(current);
	c->ui.pb_contactEdit->setEnabled(true);
	c->selected = true;
	selected = c;
}

void Contacts::on_itemDoubleClicked(QListWidgetItem *item)
{
	Contact *c = (Contact *)ui.lw_contacts->itemWidget(item);
	c->editContact(true);
}

void Contacts::on_pb_contactAdd_clicked()
{
	QDialog dlg;
	Ui::Dialog ui;
	ui.setupUi(&dlg);
	dlg.adjustSize();

	connect(ui.buttonBox, SIGNAL(accepted()), &dlg, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), &dlg, SLOT(reject()));

	if (dlg.exec() == QDialog::Accepted) {
		/* Check that this name is not already used */
		for (int i = 0; i < sms->contactNames.size(); i++) {
			if (sms->contactNames.at(i) == ui.name->text()) {
				this->ui.lw_contacts->setCurrentItem(this->ui.lw_contacts->item(i));
				return;
			}
		}

		if (!ui.name->text().isEmpty() && !ui.phone->text().isEmpty()) {
			sms->webService("CreateContact", "&ContactTel="+ui.phone->text()+"&ContactName="+ui.name->text());
			updateContacts();
			for (int i = 0; i < this->ui.lw_contacts->count(); i++) {
				if (sms->contactNamesSorted.at(i).compare(ui.name->text()) == 0) {
					this->ui.lw_contacts->setCurrentRow(i);
					break;
				}
			}
		}
	}
}

void Contacts::on_pb_contactRemove_clicked()
{
 	if (selected == NULL)
		return;

	sms->webService("DeleteContact", "&ContactTel="+selected->ui.lb_phone->text());
	updateContacts();
}

void Contacts::on_contactEdited(Contact *c)
{
	updateContacts();
	for (int i = 0; i < ui.lw_contacts->count(); i++) {
		if (sms->contactNamesSorted.at(i).compare(c->ui.lb_name->text()) == 0) {
			ui.lw_contacts->setCurrentRow(i);
			break;
		}
	}
}


void Contacts::on_pb_groupAdd_clicked()
{
	QDialog dlg;
	Ui::Dialog ui;
	ui.setupUi(&dlg);
	ui.lb_phone->setVisible(false);
	ui.phone->setVisible(false);
	dlg.adjustSize();

	connect(ui.buttonBox, SIGNAL(accepted()), &dlg, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), &dlg, SLOT(reject()));

	if (dlg.exec() == QDialog::Accepted) {
		if (!ui.name->text().isEmpty()) {
			sms->webService("GroupAdd", "&GroupName="+ui.name->text());
			sms->getGroups();
			updateGroups();
			for (int i = 0; i < sms->groupNames.count(); i++) {
				if (sms->groupNames.at(i) == ui.name->text()) {
					this->ui.cb_groups->setCurrentIndex(i);
					break;
				}
			}
		}
	}
}

void Contacts::on_pb_groupRemove_clicked()
{
	QString groupID = sms->groupIds.at(sms->findGroupIndex(ui.cb_groups->currentText()));

	sms->webService("GroupDelete", "&GroupID="+groupID);
	sms->getGroups();
	updateGroups();
}

void Contacts::on_pb_groupRename_clicked()
{
	if (ui.cb_groups->count() == 0)
		return;

	QDialog dlg;
	Ui::Dialog ui;
	ui.setupUi(&dlg);
	ui.lb_phone->setVisible(false);
	ui.phone->setVisible(false);
	dlg.adjustSize();

	connect(ui.buttonBox, SIGNAL(accepted()), &dlg, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), &dlg, SLOT(reject()));

	if (dlg.exec() == QDialog::Accepted) {
		if (!ui.name->text().isEmpty()) {
			sms->webService("GroupRename", "&GroupID="+sms->groupIds.at(sms->findGroupIndex(this->ui.cb_groups->currentText()))+"&GroupName="+ui.name->text());
			sms->getGroups();
			updateGroups();
			for (int i = 0; i < sms->groupNames.count(); i++) {
				if (sms->groupNames.at(i) == ui.name->text()) {
					this->ui.cb_groups->setCurrentIndex(i);
					break;
				}
			}
		}
	}
}



void Contacts::getMembers()
{
	QString groupID = sms->groupIds.at(sms->findGroupIndex(ui.cb_groups->currentText()));

	sms->webService("GroupMemberGetAll", "&GroupId="+groupID);
	sms->parseMembers();
	updateMembers();
}

void Contacts::updateMembers()
{
	ui.lw_members->clear();

	for (int i = 0; i < sms->memberNames.size(); i++) {
		QListWidgetItem *item = new QListWidgetItem();
		Contact *c = new Contact(ui.lw_members, sms,
					 (QString *)&sms->memberNamesSorted.at(i),
					 (QString *)&sms->memberPhones.at(sms->findMemberIndex(sms->memberNamesSorted.at(i))));

		c->ui.pb_contactEdit->setVisible(false);

		QSize qs = QSize(200, 40);
		item->setSizeHint(qs);

		ui.lw_members->addItem(item);
		ui.lw_members->setItemWidget(item, c);
	}
}

void Contacts::on_pb_memberAdd_clicked()
{
	int i = ui.lw_contacts->currentRow();
	QListWidgetItem *item = ui.lw_contacts->currentItem();

	if (item && item->isSelected()) {
		/* Check that it is not already in this group */
		for (int j = 0; j < sms->memberNames.size(); j++) {
			if (sms->memberNames.at(j) == sms->contactNamesSorted.at(i))
				return;
		}

		/* Add it */
		QString groupID = sms->groupIds.at(sms->findGroupIndex(ui.cb_groups->currentText()));
		QString memberTel = sms->contactPhones.at(sms->findContactIndex(sms->contactNamesSorted.at(i)));

		sms->webService("GroupMemberAdd", "&GroupID="+groupID+"&MemberTel="+memberTel);
		getMembers();
		updateMembers();
	}	
}

void Contacts::on_pb_memberRemove_clicked()
{
	QListWidgetItem *item = ui.lw_members->currentItem();
	Contact *c = (Contact *)ui.lw_members->itemWidget(item);

	if (item && item->isSelected()) {
		QString groupID = sms->groupIds.at(sms->findGroupIndex(ui.cb_groups->currentText()));
		QString memberTel = c->phone;

		sms->webService("GroupMemberRemove", "&GroupID="+groupID+"&MemberTel="+memberTel);
		getMembers();
		updateMembers();
	}
}


bool Contacts::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent->key() == Qt::Key_Enter) {
			qDebug("Contacts Ate key press %d", keyEvent->key());
			return true;
		}
	}

	// standard event processing
	return QObject::eventFilter(obj, event);
}

void Contacts::closeEvent(QCloseEvent *event)
{
	sms->contactWindowSize = size();
}
