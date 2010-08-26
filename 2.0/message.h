#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QDomDocument>

#include "ui_message.h"

class Message : public QWidget
{
	Q_OBJECT

public:
	Message(QDomNode &node, QWidget *parent = 0);
	QString id;

private slots:
	void on_pb_delete_clicked();

private:
	Ui::messageWidget ui;

signals:
	void messageDeleted(QString &id);
};

#endif
