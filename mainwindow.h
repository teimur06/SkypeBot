#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ActiveQt/QAxObject>
#include <QDebug>
#include <QMap>
#include <QTime>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QClipboard>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QTextCodec>
#include "Clog.h"
#include "skype.h"
#include "dialogchats.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void testRunningSkype();
    void closeConnectionSkype();
private slots:
    void getMessageSkype(IDispatch*, TChatMessageStatus);
    void on_aStartSkype_triggered();
    void on_aExit_triggered();
    void exception(int num, QString arg1,QString arg2,QString arg3);
    void aboutToShowMenu ();
    void on_aExitSkype_triggered();
    void on_aConnectToSkype_triggered();

    void on_aDisconnectSkype_triggered();
    void activatedTrey(QSystemTrayIcon::ActivationReason);
    void on_aRefreshDictionary_triggered();
    void changeEvent(QEvent *e);
    void acceptedDialogChats();
    void on_aDialogChats_triggered();
    void setConfigNameChat(QStringList &chat);

private:
    Clog clog;
    bool isSkypeConnect;
    bool isXMLError;
    Ui::MainWindow *ui;
    Skype * AxSkype;
    QMap <QString, QStringList  > reply;
    QSystemTrayIcon *trIcon;
    QStringList nameChat;
    DialogChats * dialogChats;
    QString config;
    QString LogFileName;

};

#endif // MAINWINDOW_H
