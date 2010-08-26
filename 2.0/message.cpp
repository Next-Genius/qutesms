#include "message.h"

Message::Message(QDomNode &node, QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	ui.lb_to->setText("To: "+node.firstChildElement("ContactName").text());
	QString date = node.firstChildElement("Date").text().left(10) + "   " + node.firstChildElement("Date").text().right(8);
	ui.lb_date->setText("Date: "+date);
	ui.lb_status->setText("Status: "+node.firstChildElement("Status").text());
	ui.messageText->setText(node.firstChildElement("Msg").text());
	id = node.firstChildElement("ID").text();
}

void Message::on_pb_delete_clicked()
{
	emit messageDeleted(id);
}
