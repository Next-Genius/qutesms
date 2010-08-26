#include <QListWidgetItem>
#include <QDomDocument>

#include "messages.h"

Messages::Messages(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pb_done, SIGNAL(clicked()), this, SLOT(close()));

	sms = (smshttp *) parent;

	ui.cb_autoDelete->setChecked(sms->autoDelete);
	ui.cb_display->blockSignals(true);
	ui.cb_display->setCurrentIndex(sms->displayCount);
	ui.cb_display->blockSignals(false);

	if (sms->webService("GetLogMessages", "&RowCount="+ui.cb_display->currentText()))
		return;

	parseLogMessages();
}

void Messages::parseLogMessages()
{
	QDomDocument doc("SMSHttpResult");
	QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));

	// if file could not be opened
	if (!doc.setContent(&file)) {
		file.close();
		return;
	}

	ui.lw_messages->clear();

	// close the file and start parsing
	file.close();
	QDomElement root = doc.documentElement();
	QDomElement g = root.firstChildElement("Messages");
	
	if (g.isNull())
		return;

	QDomNodeList messages;
	messages = g.elementsByTagName("SMSHttpMessages");

	if (sms->earlyFirst) {
		for (int i = messages.count() - 1; i >= 0 ; i--) {
			QListWidgetItem *item = new QListWidgetItem();
			QDomNode node = messages.at(i);
			Message *m = new Message(node, ui.lw_messages);

			QSize qs = QSize(200, 140);
			item->setSizeHint(qs);

			ui.lw_messages->addItem(item);
			ui.lw_messages->setItemWidget(item, m);

			connect(m, SIGNAL(messageDeleted(QString&)), this, SLOT(on_messageDeleted(QString&)));
		}
	} else {
		for (int i = 0; i < messages.count(); i++) {
			QListWidgetItem *item = new QListWidgetItem();
			QDomNode node = messages.at(i);
			Message *m = new Message(node, ui.lw_messages);

			QSize qs = QSize(200, 140);
			item->setSizeHint(qs);

			ui.lw_messages->addItem(item);
			ui.lw_messages->setItemWidget(item, m);

			connect(m, SIGNAL(messageDeleted(QString&)), this, SLOT(on_messageDeleted(QString&)));
		}
	}
}

void Messages::on_messageDeleted(QString &id)
{
	Message* message;

	for (int i = 0; i < ui.lw_messages->count(); i++) {
		QListWidgetItem *item = ui.lw_messages->item(i);
		message = (Message *) ui.lw_messages->itemWidget(item);
		if (message->id.compare(id) == 0) {
			sms->webService("DeleteSMS", "&MsgID="+id);

			item = ui.lw_messages->takeItem(i);
			delete item;
			break;
		}
	}

	/* Reload the list (a new slot was just freed !) */
	on_pb_earlyFirst_clicked();
}

void Messages::on_cb_autoDelete_stateChanged (int state)
{
	sms->autoDelete = state;
}

void Messages::on_cb_display_currentIndexChanged(int index)
{
	if (sms->webService("GetLogMessages", "&RowCount="+ui.cb_display->currentText()))
		return;

	parseLogMessages();	
	sms->displayCount = index;
}

void Messages::on_pb_earlyFirst_clicked()
{
	if (!sms->earlyFirst) {
		sms->earlyFirst = true;
		if (sms->webService("GetLogMessages", "&RowCount="+ui.cb_display->currentText()))
			return;

		parseLogMessages();	
	}
}

void Messages::on_pb_oldFirst_clicked()
{
	if (sms->earlyFirst) {
		sms->earlyFirst = false;
		if (sms->webService("GetLogMessages", "&RowCount="+ui.cb_display->currentText()))
			return;

		parseLogMessages();	
	}
}

void Messages::closeEvent(QCloseEvent *event)
{
	sms->messageWindowSize = size();
}
