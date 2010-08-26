#include <QDomDocument>
#include <QMessageBox>
#include <QUrl>
#include <QFile>
#include <QSslCertificate>
#include <QSslConfiguration>
#include <QDesktopServices>

#include "smshttp.h"
#include "ui_smshttp.h"

#include "member.h"
#include "ui_help.h"


smshttp::smshttp(QWidget *parent) : QMainWindow(parent), ui(new Ui::smshttpClass)
{
#ifdef WIN32
	settings = new QSettings("Settings\\QuteSms", QSettings::IniFormat);
#else
	settings = new QSettings;
#endif
	ui->setupUi(this);
	readSettings();

	if (ui->cb_rememberMe->isChecked()) {
		ui->cb_autoLogin->setEnabled(true);
	} else {
		ui->cb_autoLogin->setEnabled(false);
	}

	connect(&confirmationTimer, SIGNAL(timeout()), this, SLOT(getConfirmation()));
	connect(ui->userPhone, SIGNAL(returnPressed()), this, SLOT(logIn()));
	connect(ui->userPass, SIGNAL(returnPressed()), this, SLOT(logIn()));
	connect(ui->cb_rememberMe, SIGNAL(stateChanged(int)), this, SLOT(rememberMeStateChanged(int)));
	connect(ui->cb_autoLogin, SIGNAL(stateChanged(int)), this, SLOT(saveSettings()));
	connect(ui->cb_validation, SIGNAL(stateChanged(int)), this, SLOT(saveSettings()));
	connect(ui->cb_confirmation, SIGNAL(stateChanged(int)), this, SLOT(saveSettings()));
	connect(ui->pb_logIn, SIGNAL(clicked()), this, SLOT(logIn()));
	connect(ui->pb_send, SIGNAL(clicked()), this, SLOT(sendSms()));
	connect(ui->smsText, SIGNAL(textChanged()), this, SLOT(updateChars()));
	connect(ui->pb_help, SIGNAL(clicked()), this, SLOT(showHelp()));
	connect(ui->pb_manageContacts, SIGNAL(clicked()), this, SLOT(manageContactsGroups()));
	connect(ui->cb_confirmation, SIGNAL(stateChanged(int)), this, SLOT(waitConfirmation(int)));
	connect(ui->nameHint, SIGNAL(textChanged(const QString &)), this, SLOT(nameHintChanged(const QString &)));
	connect(ui->nameHint, SIGNAL(returnPressed()), this, SLOT(nameHintReturnPressed()));
	connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));

	showInfo(QString("Welcome - Please log in"), false);
	logged = false;

	show();

	if (ui->cb_autoLogin->isChecked())
		logIn();
}

smshttp::~smshttp()
{
	delete ui;
}

void smshttp::openSmsHttp()
{
	QDesktopServices::openUrl(QUrl("http://www.smshttp.com"));
}

void smshttp::showHelp()
{
	QDialog dlg;
	Ui::helpDialog ui;
	ui.setupUi(&dlg);
	dlg.adjustSize();

	connect(ui.buttonBox, SIGNAL(accepted()), &dlg, SLOT(accept()));
	connect(ui.pb_openSmsHttp, SIGNAL(clicked()), this, SLOT(openSmsHttp()));
	dlg.exec();
}

void smshttp::rememberMeStateChanged(int state)
{
	if (state == Qt::Unchecked)
		ui->cb_autoLogin->setEnabled(false);
	else
		ui->cb_autoLogin->setEnabled(true);
	saveSettings();
}

void smshttp::logIn()
{
	if (logged) {
		logOut(true);
	} else {
		/* Log in */
		userPhone = ui->userPhone->text();
		userPass = ui->userPass->text();

		if (userPhone.isEmpty()) {
			showInfo("Enter your phone number", false);
			ui->userPhone->setFocus();
			return;
		} else if (userPass.isEmpty()) {
			showInfo("Enter your smshttp password", false);
			ui->userPass->setFocus();
			return;
		} else {
			ui->pb_logIn->setEnabled(false);
			showInfo("Connecting ...", false);
		}

		if (webService("GetBalance", "")) {
			ui->pb_logIn->setEnabled(true);
			return;
		}
		switch (parseBalance()) {
		case 1:
			ui->userPhone->setStyleSheet("color: grey;");
			ui->userPass->setStyleSheet("color: grey;");

			saveSettings();

			showInfo("Gathering contacts info");
			if (getContacts()) {
				ui->pb_logIn->setEnabled(true);
				return;
			}
			ui->cb_contacts->clear();
			ui->cb_contacts->addItem("");
			ui->cb_contacts->setCurrentIndex(0);
			ui->cb_contacts->addItems(contactNamesSorted);
				

			showInfo("Gathering groups info");
			if (getGroups()) {
				ui->pb_logIn->setEnabled(true);
				return;
			}
			ui->pb_manageContacts->setEnabled(true);
			ui->pb_manageMessages->setEnabled(true);

			ui->pb_logIn->setText("Log &Out");
			ui->pb_logIn->setEnabled(true);
			ui->pb_logIn->setIcon(QIcon(":/icons/dialog-close.png"));
			ui->userPhone->setEnabled(false);
			ui->userPass->setEnabled(false);
			ui->cb_rememberMe->setEnabled(false);
			ui->cb_autoLogin->setEnabled(false);
			ui->nameHint->setFocus();
			showInfo("Logged In");
			logged = true;
			break;
		case 10:
			showInfo("Login failed", false);
			ui->userPhone->setStyleSheet("color: red;");
			ui->userPass->setStyleSheet("color: red;");
			logOut(false);
			break;
		case 0:
			showInfo("Could not make connexion.", false);
			logOut(false);
			break;
		default:
			showInfo("An unknow error occured.", false);
			logOut(false);
		}
	}
}

void smshttp::logOut(bool showWelcome)
{
	ev.quit();

	if (showWelcome)
		showInfo(QString("Welcome - Please log in"), false);
	ui->creditsLeft->setText("");
	ui->pb_logIn->setText("Log &In");
	ui->pb_logIn->setIcon(QIcon(":/icons/dialog-ok-apply.png"));
	ui->pb_logIn->setEnabled(true);
	ui->pb_manageContacts->setEnabled(false);
	ui->pb_manageMessages->setEnabled(false);

	ui->userPhone->setStyleSheet("color: black;");
	ui->userPass->setStyleSheet("color: black;");

	if (!ui->cb_rememberMe->isChecked()) {
		ui->userPhone->setText("");
		ui->userPass->setText("");
	} else {
		ui->cb_autoLogin->setEnabled(true);
	}

	ui->cb_contacts->clear();
	ui->contactPhone->setText("");
	ui->smsText->clear();

	disconnect(ui->cb_groups, SIGNAL(currentIndexChanged(int)), this, SLOT(getMembers(int)));
	ui->cb_groups->clear();
	ui->sendList->clear();

	ui->userPhone->setEnabled(true);
	ui->userPass->setEnabled(true);
	ui->cb_rememberMe->setEnabled(true);
	ui->userPhone->setFocus();
	logged = false;
}


void smshttp::updateChars()
{
	int mod = 160;
	int length = ui->smsText->toPlainText().length();

	if (length == 0) {
		ui->lb_charLeft->setText("");
		return;
	}

	if (length > mod) {
		mod=154;
	}
	smsNeeded = 1 + length / mod;
	ui->lb_charLeft->setText(QString("%1 SMS - %2 chars left").arg(smsNeeded).arg(mod-length%mod));

}

#include "ui_add.h"
bool smshttp::smsValidation()
{
	if (!ui->cb_validation->isChecked())
		return true;

	ui->pb_send->setEnabled(false);
	ui->smsText->setEnabled(false);
	showInfo("SMS validation");

	QMessageBox msg;
	msg.setWindowTitle("Validation");

	QString txt = "Sending SMS to :";
	for (int i = 0; i < ui->sendList->count(); i++) {
		Member *m = (Member *)ui->sendList->itemWidget(ui->sendList->item(i));
		txt.append(QString("\n  - %1 (%2)").arg(m->ui.lb_name->text()).arg(m->phone));
	}
	msg.setText(txt);

	txt = QString("Message:\n");
	txt.append(ui->smsText->toPlainText());
	msg.setInformativeText(txt);
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msg.setDefaultButton(QMessageBox::Ok);

	int ret = msg.exec();

	switch (ret) {
	case QMessageBox::Ok:

		return true;
	default:
		showInfo("Canceled - SMS not sent");
		ui->pb_send->setEnabled(true);
		ui->smsText->setEnabled(true);
		return false;
	}
}

void smshttp::sendSms()
{
	QString smsText;

	smsText = ui->smsText->toPlainText();
	if (smsText.isEmpty()) {
		showInfo("Enter your SMS text");
		ui->smsText->setFocus();
		return;
	}

	waitingTime = 3;

	/* Sending to a group */

	if (ui->sendList->count() * smsNeeded > creditsLeft.toInt()) {
		// Re-check, just in case we did not buy more sms meanwhile ...
		if (webService("GetBalance", ""))
			return;
		parseBalance();
		if (ui->sendList->count() > creditsLeft.toInt()) {
			ui->lb_creditsLeft->setStyleSheet("color: red;");
			ui->creditsLeft->setStyleSheet("color: red;");
			showInfo("Not enough credits left to send SMS");
			return;
		}
	}

	if (ui->sendList->count() == 0) {
		showInfo("Select people to send this SMS to");
		ui->sendList->setFocus();
		return;
	}

	if (!smsValidation())
		return;

	/* Send SMS one by one */
	messageIds.clear();
	for (int i = 0; i < ui->sendList->count(); i++) {
		Member *m = (Member *)ui->sendList->itemWidget(ui->sendList->item(i));
		showInfo(QString("Sending SMS #%1 (%2) ...").arg(i+1).arg(m->phone));
		webService("SendSMS", "&Tel="+m->phone+"&Msg="+smsText);
		QString id = getId();
		if (!id.isEmpty())
			messageIds << id;
		qDebug() << "Sending SMS to " << m->phone;
	}

	// Update balance
	if (webService("GetBalance", ""))
		return;
	parseBalance();

	if (ui->cb_confirmation->checkState() == Qt::Checked) {
		showInfo("Waiting for delivery confirmation ...");
		confirmationTimer.start(waitingTime * 1000);
	} else {
		ui->pb_send->setEnabled(true);
		ui->smsText->setEnabled(true);

		if (autoDelete) {
			for (int i = 0; i < messageIds.count(); i++) {
				webService("DeleteSMS", "&MsgID="+messageIds.at(i));
			}
		}
	}
}

void smshttp::on_pb_clear_clicked()
{
	ui->contactPhone->setText("");
	ui->nameHint->setText("");
	ui->sendList->clear();
	ui->smsText->clear();
	ui->nameHint->setFocus();
}

void smshttp::manageContactsGroups()
{
	contactsWindow = new Contacts(this);
	contactsWindow->resize(contactWindowSize);
	contactsWindow->show();
}

void smshttp::on_pb_manageMessages_clicked()
{
	messagesWindow = new Messages(this);
	messagesWindow->resize(messageWindowSize);
	messagesWindow->show();
}

int smshttp::getContacts()
{
	if (webService("GetContacts", ""))
		return downloadError;
	parseContacts();

	return 0;
}

int smshttp::getGroups()
{
	disconnect(ui->cb_groups, SIGNAL(currentIndexChanged(int)), this, SLOT(getMembers(int)));

	if (webService("GroupGetAll", ""))
		return downloadError;
	parseGroups();
	// Populate comboBox
	ui->cb_groups->clear();
	ui->cb_groups->addItems(groupNamesSorted);
	ui->cb_groups->setCurrentIndex(0);
	getMembers(0);
	connect(ui->cb_groups, SIGNAL(currentIndexChanged(int)), this, SLOT(getMembers(int)));
	return 0;
}

void smshttp::getMembers(int index)
{
	QString id = groupIds.at(findGroupIndex(ui->cb_groups->itemText(index)));

	if (webService("GroupMemberGetAll", "&GroupID="+id))
		return;
	parseMembers();
}

void smshttp::on_contactsAdd_clicked()
{
	if (ui->cb_contacts->currentText().isEmpty()) {
		showInfo("Chose a contact", true);
		ui->nameHint->setFocus();
		return;
	}

	QStringList names;
	names << ui->cb_contacts->currentText();
	addToSendList(names);
}

void smshttp::on_groupsAdd_clicked()
{
	QStringList list = memberNamesSorted;
	addToSendList(list);
}

void smshttp::on_phoneAdd_clicked()
{
	if (ui->contactPhone->text().isEmpty()) {
		showInfo("Enter your correspondant phone number", true);
		ui->contactPhone->setFocus();
		return;
	}

	QStringList names;
	names << ui->contactPhone->text();
	addToSendList(names);
}

void smshttp::showSmsPanel(bool s)
{
	ui->creditsBox->setEnabled(s);
	ui->smsBox->setEnabled(s);
}

void smshttp::showInfo(QString str, bool state)
{
	ui->statusBar->showMessage(str);
	showSmsPanel(state);
}

void smshttp::setCreditsLeft()
{
	ui->creditsLeft->setText(creditsLeft);
}

void smshttp::parseContacts()
{
	QDomDocument doc("SMSHttpResult");
	QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));

	// if file could not be opened
	if(!doc.setContent(&file)) {
		file.close();
		return;
	}

	contactNames.clear();
	contactPhones.clear();

	// close the file and start parsing
	file.close();
	QDomElement root = doc.documentElement();
	QDomElement c = root.firstChildElement("Contacts");
	if (!c.isNull()) {
		QDomNodeList contacts;
		QDomNodeList phones;
		contacts = c.elementsByTagName("Name");
		phones = c.elementsByTagName("Tel");
		for (int i = 0; i < contacts.count(); i++){
			contactNames << contacts.at(i).toElement().text();
			contactPhones << phones.at(i).toElement().text();
		}
	}
	contactNamesSorted = contactNames;
	contactNamesSorted.sort();
}

int smshttp::parseBalance()
{
	QDomDocument doc("SMSHttpResult");
	QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));

	// if file could not be opened
	if (!doc.setContent(&file)) {
		file.close();
		return 0;
	}

	// close the file and start parsing
	file.close();
	QDomElement root = doc.documentElement();
	QDomNode n = root.firstChild();
	while (!n.isNull()) {
		if (n.isElement()) {
			QDomElement e = n.toElement();
			if (e.tagName()=="ErrorCode") {
				switch (e.text().toInt()) {
				case 10:
					return 10;
				case 200:
					///login succesfull
					break;

				default:
					/// exit Dunno how to deal with this one.
					return 0;
				}
			}

			if (e.tagName()=="CreditsLeft") {
				creditsLeft=e.text();
				if (creditsLeft.toInt() > 0) {
					ui->lb_creditsLeft->setStyleSheet("color: black;");
					ui->creditsLeft->setStyleSheet("color: black;");
				}
			}

			if (e.tagName()=="CreditsLeftToday")
				creditsLeftToday=e.text();

			setCreditsLeft();

/*			if (e.tagName()=="Messages") {
			QDomNode m = n.firstChild();
			if (!m.isNull()) {
			QDomNode sms = m.firstChildElement("ID");
			if (!sms.isNull()) {
			lastSMSId = sms.toElement().text();
			break;
			}
			}
			}
*/
			n = n.nextSibling();
		}
	}


	return 1;
}

QString smshttp::getId()
{
	QString id;
	QDomDocument doc("SMSHttpResult");
	QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));
	
	// if file could not be opened
	if (!doc.setContent(&file)) {
		file.close();
		return id;
	}
	
#ifdef DEBUG
	file.copy(QDir::currentPath()+QDir::separator()+WEBSERVICE_FILE+"sending");
#endif

	// close the file and start parsing
	file.close();

	QDomElement root = doc.documentElement();
	QDomElement messages = root.firstChildElement("Messages");
	if (messages.isNull())
		return id;
	QDomElement m = messages.firstChildElement("SMSHttpMessages");
	if (!m.isNull()) {
		QDomElement id_elem = m.firstChildElement("ID");
		if (!id_elem.isNull()) {
			id = id_elem.text();
		}
	}

	return id;
}

void smshttp::parseGroups()
{
	QDomDocument doc("SMSHttpResult");
	QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));

	// if file could not be opened
	if (!doc.setContent(&file)) {
		file.close();
		return;
	}

	groupNames.clear();
	groupIds.clear();

	// close the file and start parsing
	file.close();
	QDomElement root = doc.documentElement();
	QDomElement g = root.firstChildElement("Groups");
	if (!g.isNull()) {
		QDomNodeList groups;
		QDomNodeList ids;
		groups = g.elementsByTagName("Name");
		ids = g.elementsByTagName("GroupID");
		for (int i = 0; i < groups.count(); i++){
			groupNames << groups.at(i).toElement().text();
			groupIds << ids.at(i).toElement().text();
		}
	}
	groupNamesSorted = groupNames;
	groupNamesSorted.sort();
}

void smshttp::parseMembers()
{
	QDomDocument doc("SMSHttpResult");
	QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));

	// if file could not be opened
	if (!doc.setContent(&file)) {
		file.close();
		return;
	}

	memberNames.clear();
	memberPhones.clear();

	// close the file and start parsing
	file.close();
	QDomElement root = doc.documentElement();
	QDomElement c = root.firstChildElement("Contacts");
	if (!c.isNull()) {
		QDomNodeList members, phones;
		members = c.elementsByTagName("Name");
		phones = c.elementsByTagName("Tel");
		for (int i = 0; i < members.count(); i++){
			memberNames << members.at(i).toElement().text();
			memberPhones << phones.at(i).toElement().text();
		}
	}
	memberNamesSorted = memberNames;
	memberNamesSorted.sort();
}

void smshttp::addToSendList(QStringList &names)
{
	int index;

	for (int i = 0; i < names.size(); i++) {
		// Check that some entries are not already present in the list
		bool removed = false;
		for (int j = 0; j < ui->sendList->count(); j++) {
			Member *m = (Member *)ui->sendList->itemWidget(ui->sendList->item(j));
			if (m->ui.lb_name->text().compare(names.at(i)) == 0) {
				names.removeAt(i);
				removed = true;
				break;
			}
		}
		if (removed)
			continue;

		// Add to list view
		QListWidgetItem *item = new QListWidgetItem();
		Member *m = new Member(ui->sendList, (QString *)&names.at(i), ui->sendList->count());
		index = findContactIndex(names.at(i));
		if (index >= 0)
			m->phone = contactPhones.at(index);
		else
			m->phone = names.at(i);

		QSize qs = QSize(100, 20);
		item->setSizeHint(qs);
		connect(m, SIGNAL(memberRemoved(int)), this, SLOT(memberRemoved(int)));

		ui->sendList->addItem(item);
		ui->sendList->setItemWidget(item, m);
	}

	ui->sendList->setCurrentRow(ui->sendList->count() - 1);
	ui->smsText->setFocus();
}

void smshttp::memberRemoved(int index)
{
	Member* member;

	for (int i = 0; i < ui->sendList->count(); i++) {
		QListWidgetItem *item = ui->sendList->item(i);
		member = (Member *) ui->sendList->itemWidget(item);
		if (member->index == index) {
			item = ui->sendList->takeItem(i);
			delete item;
			break;
		}
	}
}

void smshttp::saveSettings()
{
	settings->beginGroup("User");
	settings->setValue("userRemember", ui->cb_rememberMe->isChecked());
	if (ui->cb_rememberMe->isChecked()) {
		settings->setValue("userPhone", ui->userPhone->text());
		settings->setValue("userPass", ui->userPass->text());
		settings->setValue("userAutoLogin", ui->cb_autoLogin->isChecked());
	}
	settings->setValue("userValidation", ui->cb_validation->isChecked());
	settings->setValue("userConfirmation", ui->cb_confirmation->isChecked());
	settings->setValue("userAutoDelete", autoDelete);
	settings->setValue("userDisplayCount", displayCount);
	settings->setValue("userEarlyFirst", earlyFirst);
	settings->endGroup();

	settings->beginGroup("Window");
	settings->setValue("size", size());
	settings->setValue("pos", pos());
	settings->setValue("contactWindowSize", contactWindowSize);
	settings->setValue("messageWindowSize", messageWindowSize);
	settings->endGroup();
}

void smshttp::readSettings()
{
	settings->beginGroup("Window");
	resize(settings->value("size", QSize(560, 560)).toSize());
	move(settings->value("pos", QPoint(200, 200)).toPoint());
	restoreState(settings->value("state").toByteArray(),0);
	contactWindowSize = settings->value("contactWindowSize", QSize(600, 450)).toSize();
	messageWindowSize = settings->value("messageWindowSize", QSize(500, 450)).toSize();
	settings->endGroup();

	settings->beginGroup("User");
	ui->cb_rememberMe->setChecked(settings->value("userRemember","").toBool());
	if (ui->cb_rememberMe->isChecked()) {
		ui->userPhone->setText(settings->value("userPhone","").toString());
		ui->userPass->setText(settings->value("userPass","").toString());
		ui->cb_autoLogin->setChecked(settings->value("userAutoLogin","").toBool());
	}
	ui->cb_validation->setChecked(settings->value("userValidation","").toBool());
	ui->cb_confirmation->setChecked(settings->value("userConfirmation","").toBool());
	autoDelete = settings->value("userAutoDelete","").toBool();
	displayCount = settings->value("userDisplayCount","").toInt();
	earlyFirst = settings->value("userEarlyFirst","").toBool();
	settings->endGroup();
}


int smshttp::webService(QString action, QString data)
{
	QString common="ApplicationID="+appId+"&UserTel="+userPhone+"&Password="+userPass;
	QString url_s = QString("https://smsc.vianett.no/smshttp/Service.asmx/"+action+"?"+common+data);
 	QNetworkRequest request;

 	request.setUrl(QUrl(url_s));

#ifdef DEBUG
	qDebug() << "Webservice: " << action;
#endif

	downloadError = 0;
	QNetworkReply *reply = manager.get(request);
 	reply->ignoreSslErrors();

	// Wait until the download is finished (or timed out)
	ev.exec();
	return downloadError;
}

void smshttp::downloadFinished(QNetworkReply *reply)
{
        QUrl url = reply->url();

        if (reply->error()) {
		showInfo("An error occured, check your internet connection", false);
		downloadError = reply->error();
		ev.quit();
		logOut(false);
		return;
        } else {
		QString path = url.path();
		QFile file(QDir::currentPath() + QDir::separator() + QString(WEBSERVICE_FILE));
		if (!file.open(QIODevice::WriteOnly)) {
			ev.quit();
			return;
		}
		file.write(reply->readAll());
		file.close();
        }

        reply->deleteLater();

	ev.quit();
}


/* Returns true if the last SMS was delivered or */
/* if the delivery state could not be obtained */
bool smshttp::parseDeliveries()
{
	QDomDocument doc( "SMSHttpResult" );
	QFile file(QDir::currentPath()+QDir::separator()+WEBSERVICE_FILE);

	// if file could not be opened
	if (!doc.setContent(&file)) {
		file.close();
		return true;
	}

	// close the file and start parsing
	file.close();
	QDomElement root = doc.documentElement();
	QDomElement error = root.firstChildElement("ErrorCode");
	if (error.isNull())
		return true;
	if (error.text().toInt() == 30) {
		// SMS not yet in the queue ?
		return false;
	} else if (error.text().toInt() != 200) {
		// Unheld error
		return true;
	}

	QDomElement messages = root.firstChildElement("Messages");
	if (messages.isNull())
		return true;
	QDomElement m = messages.firstChildElement("SMSHttpMessages");
	while (!m.isNull()) {
		QDomElement id = m.firstChildElement("ID");
#ifdef DEBUG
		file.copy(QDir::currentPath()+QDir::separator()+WEBSERVICE_FILE+id.text());
#endif
		if (!id.isNull()) {
			// Check that this message ID is part of the messages we have sent
			bool ok = false;
			for (int i = 0; i < messageIds.count(); i++) {
				if (id.text().compare(messageIds.at(i)) == 0) {
					ok = true;
					break;
				}
			}
			
			if (!ok) {
				m = m.nextSiblingElement("SMSHttpMessages");
				continue;
			}
			
			QDomElement status = m.firstChildElement("Status");
			if (!status.isNull()) {
				if (status.text() == "DELIVRD") {
					showInfo("SMS delivered");
					if (autoDelete)
						webService("DeleteSMS", "&MsgID="+id.text());
					messageDelivered(id.text());
				} else if (status.text() == "ACCEPTD") {
					showInfo("Your correspondant phone is off - SMS will be delivered later");
					if (autoDelete)
						webService("DeleteSMS", "&MsgID="+id.text());
					messageDelivered(id.text());
				} else if (status.text() == "EXPIRED") {
					showInfo("Could not deliver the SMS");
					if (autoDelete)
						webService("DeleteSMS", "&MsgID="+id.text());
					messageDelivered(id.text());
				}
			}
		}
		m = m.nextSiblingElement("SMSHttpMessages");
	}

	return messageIds.count() == 0 ? true : false;
}

void smshttp::messageDelivered(QString id)
{
	for (int i = 0; i < messageIds.count(); i++) {
		if (messageIds.at(i).compare(id) == 0) {
			messageIds.removeAt(i);
			break;
		}
	}
}

void smshttp::getConfirmation()
{
	webService("GetDeliveries", "");
	if (parseDeliveries() && ui->cb_confirmation->checkState() == Qt::Checked && logged) {
		ui->pb_send->setEnabled(true);
		ui->smsText->setEnabled(true);
		confirmationTimer.stop();
	} else {
		confirmationTimer.stop();
		waitingTime++;
		confirmationTimer.start(waitingTime * 1000);
	}
}

void smshttp::waitConfirmation(int state)
{
	if (state == Qt::Unchecked && confirmationTimer.isActive()) {
		showInfo("");
		confirmationTimer.stop();
		ui->pb_send->setEnabled(true);
		ui->smsText->setEnabled(true);		
	}
}


void smshttp::closeEvent(QCloseEvent *event)
{
	saveSettings();
}

void smshttp::nameHintChanged(const QString &text)
{
	QString txt = text;

	if (nameHintPreviousSize == txt.size())
		txt = txt.left(txt.size() - 1);
	nameHintPreviousSize = txt.size();

	disconnect(ui->nameHint, SIGNAL(textChanged(const QString &)), this, SLOT(nameHintChanged(const QString &)));

	if (txt.isEmpty() &&
	    ui->cb_contacts->count() != contactNames.size()) {
		ui->cb_contacts->clear();
		ui->cb_contacts->addItem("");
		ui->cb_contacts->setCurrentIndex(0);
		ui->cb_contacts->addItems(contactNamesSorted);
		nameHintPreviousSize = 0;
		ui->nameHint->setText("");
		connect(ui->nameHint, SIGNAL(textChanged(const QString &)), this, SLOT(nameHintChanged(const QString &)));
		return;
	}

	QString previous = ui->cb_contacts->currentText();
	QStringList contactNamesTemp = contactNamesSorted;
	for (int i = 0; i < contactNamesTemp.size(); i++) {
		if (contactNamesTemp.at(i).left(txt.size()).toUpper() != txt.toUpper()) {
			contactNamesTemp.removeAt(i);
			i--;
		}
	}

	if (contactNamesTemp.size() > 0) {
		ui->cb_contacts->clear();
		ui->cb_contacts->addItems(contactNamesTemp);
		ui->cb_contacts->setCurrentIndex(0);
		ui->nameHint->setText(contactNamesTemp.at(0));
		ui->nameHint->setCursorPosition(txt.size());
		ui->nameHint->setSelection(txt.size(), contactNamesTemp.at(0).size());
	} else {
		ui->cb_contacts->clear();
		ui->cb_contacts->addItem("");
		ui->cb_contacts->setCurrentIndex(0);
		ui->cb_contacts->addItems(contactNamesSorted);
	}

	connect(ui->nameHint, SIGNAL(textChanged(const QString &)), this, SLOT(nameHintChanged(const QString &)));
}

void smshttp::nameHintReturnPressed()
{
	on_contactsAdd_clicked();
}

void smshttp::on_contactPhone_returnPressed()
{
	on_phoneAdd_clicked();
}

int smshttp::findContactIndex(const QString &contact)
{
	for (int i = 0; i < contactNames.size(); i++) {
		if (contactNames.at(i) == contact)
			return i;
	}
	return -1;
}

int smshttp::findGroupIndex(const QString &group)
{
	for (int i = 0; i < groupNames.size(); i++) {
		if (groupNames.at(i) == group)
			return i;
	}
	return -1;
}

int smshttp::findMemberIndex(const QString &member)
{
	for (int i = 0; i < memberNames.size(); i++) {
		if (memberNames.at(i) == member)
			return i;
	}
	return -1;
}
