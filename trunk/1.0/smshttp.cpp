#include "smshttp.h"
#include "ui_smshttp.h"
#include <QDomDocument>
#include <QMessageBox>



smshttp::smshttp(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::smshttpClass)
{
    ui->setupUi(this);
    readSettings();
    connect (ui->logInPB,SIGNAL(clicked()),this,SLOT(logIn()));
    connect (ui->sendPB,SIGNAL(clicked()),this,SLOT( sendSms()));
    connect (ui->smsText,SIGNAL(textChanged()),this,SLOT(updateChars()));
    connect (ui->helpPB,SIGNAL(clicked()),this,SLOT(showHelp()));
    connect (ui->contactsCB,SIGNAL(currentIndexChanged(int)),this,SLOT(showNumber(int)));
    showSmsPanel(false);
}

void smshttp::showHelp(){
 QFile inputFile(":/icons/aboutText.txt");
     inputFile.open(QIODevice::ReadOnly);
     QTextStream in(&inputFile);
     QMessageBox msgBox;
 msgBox.setText(in.read(1000));
 msgBox.setTextFormat(Qt::RichText);
 msgBox.exec();

  //  QMessageBox::about(this,"About",in.read(1000));
}

 void smshttp::showNumber(int num){
     ui->recPhone->setText(contactsPhones.at(num));
 }

void smshttp::updateChars(){
    int mod=160;
    int length=ui->smsText->toPlainText().length();
    if (length > 160) {
        mod=154;
        ui-> charLeft->setText(QString("%1 chars left in the %2 SMS").arg(mod-length%160).arg(1+length/mod));
        return;
    }
   ui-> charLeft->setText(QString("%1 chars left in the %2 SMS").arg(mod-length%mod).arg(1+length/mod));

}

smshttp::~smshttp()
{
    delete ui;
}


void smshttp::sendSms(){
     showInfo("Sending SMS...",true);
    recPhone=ui->recPhone->text();
    smsText=ui->smsText->toPlainText();
    QString smsData="ApplicationID="+appId+"&UserTel="+userPhone+"&Password="+userPass+"&Tel="+recPhone+"&Msg="+smsText; 
    qDebug()<<smsData;
download("SendSMS","\""+smsData+"\"");

switch (parseFile("SendSMS")){
    case 1:
        showInfo("SMS sent",true);
        setCreditsLeft( creditsLeft);
        break;
    case 10:
        showInfo("Sending SMS failed",true);
        break;
    case 0:
        showInfo("Could not read File.",true);

        break;
    default:
        showInfo("An unknow error occured.",true);
    }

}


void smshttp::logIn(){
userPhone=ui->userPhone->text();
userPass=ui->userPass->text();
showInfo("Making Connexion",true);
QString balanceData="ApplicationID="+appId+"&UserTel="+userPhone+"&Password="+userPass;
download("GetBalance","\""+balanceData+"\"");
switch (parseFile("GetBalance")){
    case 1:

        showInfo("Gathering Contacts",true);
        setCreditsLeft( creditsLeft);
        if (ui->saveSettingsCb->isChecked()) {
        settings.beginGroup("User");
        settings.setValue("userPhone",userPhone);
        settings.setValue("userPass",userPass);
        settings.endGroup();
    }
        getContacts();
        showInfo("Logged In",true);
        break;
    case 10:
        showInfo("Login failed",false);
        break;
    case 0:
        showInfo("Could not make connexion.",false);

        break;
    default:
        showInfo("An unknow error occured.",false);
    }

}


void smshttp::getContacts(){
QString contactsData="ApplicationID="+appId+"&UserTel="+userPhone+"&Password="+userPass;
download("GetContacts","\""+contactsData+"\"");
parseContacts("GetContacts");
ui->contactsCB->addItems(contactsNames);
}
void smshttp::showSmsPanel(bool s){
    ui->statusFrame->setVisible(s);
    ui->smsFrame->setVisible(s);
}

void smshttp::showInfo(QString str,bool state){
     ui->statusLbl->setText(str);
     showSmsPanel(state);
     //qDebug(str);
}

void smshttp::setCreditsLeft(QString val){
    ui->creditsLeft->setText(val);
}

int smshttp::parseContacts(QString fileName){
    QDomDocument doc( "SMSHttpResult" );
QFile file(QDir::currentPath()+QDir::separator ()+fileName);
///if file could not be opened
 if( !doc.setContent( &file ) )
 {
   file.close();
   return 0;
 }
 ///close the file and start parsing
 file.close();
 QDomElement root = doc.documentElement();
 QDomNode n = root.firstChild();
 while (!n.isNull()) {
     if (n.isElement()) {
         QDomElement e = n.toElement();
    if (e.tagName()=="Contacts") {
        QDomNodeList contacts;
        QDomNodeList phones;
       contacts= e.elementsByTagName("Name");
       phones= e.elementsByTagName("Tel");
      for (int i=0;i<contacts.count();i++){
          contactsNames<<contacts.at(i).toElement().text();
          contactsPhones<<phones.at(i).toElement().text();
      }
       qDebug()<<contacts.count();
           }
      n = n.nextSibling();
    }
 }
  return 1;
}

int smshttp::parseFile(QString fileName){
QDomDocument doc( "SMSHttpResult" );
QFile file(QDir::currentPath()+QDir::separator ()+fileName);
///if file could not be opened
 if( !doc.setContent( &file ) )
 {
   file.close();
   return 0;
 }
 ///close the file and start parsing
 file.close();
 QDomElement root = doc.documentElement();
 QDomNode n = root.firstChild();
 while (!n.isNull()) {
     if (n.isElement()) {
         QDomElement e = n.toElement();
        // qDebug() << "Element name: " << e.tagName() << e.text()<<endl;
         if (e.tagName()=="ErrorCode"){
             switch (e.text().toInt()) {
                 case 10:

                        return 10;
                 case 200:
                        ///login succefull
                        break;

                 default:
                        /// exit Dunno how to deal with this one.
                        return 0;
             }
         }

         if (e.tagName()=="CreditsLeft"){
             creditsLeft=e.text();
         //break;
        }
     n = n.nextSibling();
 }
    }
  return 1;
}



void smshttp::download(QString action,QString data){
QProcess *process = new QProcess();
///set conexion timeout to 9
process->execute( "wget --timeout=9  -O " + action+ " --no-check-certificate  --post-data="+data+" https://smsc.vianett.no/smshttp/Service.asmx/"+action+"?" );
}

 void smshttp::readSettings(){
        ///@todo use default geometry constarin

     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());
         ///restore previewDock and toolbars positions
     restoreState(settings.value("state").toByteArray(),0);
         ///restore last directory
     //filesDir=(settings.value("dir","").toString());
     settings.endGroup();

     settings.beginGroup("User");
    ui->userPhone->setText(settings.value("userPhone","").toString());
    ui->userPass->setText(settings.value("userPass","").toString());
    settings.endGroup();
}
