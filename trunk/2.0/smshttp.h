#ifndef SMSHTTP_H
#define SMSHTTP_H

#include <QtGui/QMainWindow>
#include <QSettings>

#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QDialog>
#include <QStatusBar>
#include <QTimer>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include "contacts.h"
#include "messages.h"

#define WEBSERVICE_FILE	"webservice"

const QString appId="795846979";

class Contacts;
class Messages;
class smshttp;

namespace Ui
{
	class smshttpClass;
}

class smshttp : public QMainWindow
{
	Q_OBJECT

public:
	smshttp(QWidget *parent = 0);
	~smshttp();

	Ui::smshttpClass *ui;

	int webService(QString action,QString data);
	int getContacts();
	int getGroups();
	void parseMembers();
	void addToSendList(QStringList &names);
	int downloadError;
	int findContactIndex(const QString &contact);
	int findGroupIndex(const QString &group);
	int findMemberIndex(const QString &member);

	QStringList contactPhones;
	QStringList contactNames;
	QStringList contactNamesSorted;
	QStringList groupNames;
	QStringList groupNamesSorted;
	QStringList groupIds;
	QStringList memberNames;
	QStringList memberNamesSorted;
	QStringList memberPhones;
	QStringList messageIds;
	bool logged;
	bool autoDelete;
	bool earlyFirst;
	int displayCount;
	QSize contactWindowSize;
	QSize messageWindowSize;

public slots:
	void getMembers(int index);

private slots:
	void saveSettings();
	void logIn();
	void logOut(bool showWelcome);
	void rememberMeStateChanged(int state);
	void showHelp();
	void openSmsHttp();
	void sendSms();
	void on_pb_clear_clicked();
	void updateChars();
	void manageContactsGroups();
	void on_pb_manageMessages_clicked();
	void memberRemoved(int index);
	void downloadFinished(QNetworkReply *reply);
	void getConfirmation();
	void waitConfirmation(int state);
	void nameHintChanged(const QString &text);
	void nameHintReturnPressed();
	void on_groupsAdd_clicked();
	void on_contactsAdd_clicked();
	void on_phoneAdd_clicked();
	void on_contactPhone_returnPressed();

private:
	Contacts *contactsWindow;
	Messages *messagesWindow;
	QNetworkAccessManager manager;
	QEventLoop ev;
	QTimer confirmationTimer;
	int waitingTime;
	QString userPhone;
	QString userPass;
	QString creditsLeft;
	QString creditsLeftToday;
	int smsNeeded;
	QSettings *settings;
	int nameHintPreviousSize;
	void readSettings();
	void showSmsPanel(bool s);
	void showInfo(QString str,bool state = true);
	bool smsValidation();
	void setCreditsLeft();
	int parseBalance();
	QString getId();
	void messageDelivered(QString id);
	bool parseDeliveries();
	void parseContacts();
	void parseGroups();

protected:
	void closeEvent(QCloseEvent *event);
};


#endif // SMSHTTP_H
