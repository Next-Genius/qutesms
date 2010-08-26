#include "member.h"

Member::Member(QWidget *parent, QString *name, int index) : QWidget(parent)
{
	ui.setupUi(this);
	ui.lb_name->setText(QString(*name));
	this->index = index;
}

void Member::on_pb_memberRemove_clicked()
{
	emit memberRemoved(index);
}
