#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    AxSkype(NULL),
    isSkypeConnect(false),
    nameChat(""),
    isXMLError(true),
    config("config.xml"),
    LogFileName(QApplication::applicationDirPath()+"\\SkypeBot.log")
{
    ui->setupUi(this);
    QObject::connect(ui->menu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowMenu ()));
    QObject::connect(ui->menu_3, SIGNAL(aboutToShow()), this, SLOT(aboutToShowMenu ()));
    clog.setModule(QApplication::applicationName());


    clog.setlog(LogFileName);

    clog.setLevel(10);

    clog << "Инициализация";

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    on_aRefreshDictionary_triggered();
    trIcon = new QSystemTrayIcon(this);
    QObject::connect(trIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(activatedTrey(QSystemTrayIcon::ActivationReason)));
    trIcon->setIcon(QIcon(":/icon/ico.ico"));
    trIcon->setToolTip("Ботик");
    trIcon->show();

}

MainWindow::~MainWindow()
{
    closeConnectionSkype();
    delete trIcon;
    delete ui;
}

void MainWindow::testRunningSkype()
{
    if (isXMLError)
    {
        ui->aConnectToSkype->setEnabled(false);
        ui->aDisconnectSkype->setEnabled(false);
        ui->aExitSkype->setEnabled(false);
        ui->aStartSkype->setEnabled(false);
        ui->aDialogChats->setEnabled(false);
        return;
    }

    if (AxSkype && isSkypeConnect)
    {
        if (AxSkype->IsRunning())
        {
           ui->aStartSkype->setEnabled(false);
           ui->aExitSkype->setEnabled(true);
           ui->aDialogChats->setEnabled(true);
        }
        else
        {
           ui->aStartSkype->setEnabled(true);
           ui->aExitSkype->setEnabled(false);
           ui->aDialogChats->setEnabled(false);
        }
        ui->aConnectToSkype->setEnabled(false);
        ui->aDisconnectSkype->setEnabled(true);
    } else
    {
        ui->aDisconnectSkype->setEnabled(false);
        ui->aConnectToSkype->setEnabled(true);
        ui->aStartSkype->setEnabled(false);
        ui->aExitSkype->setEnabled(false);
        ui->aDialogChats->setEnabled(false);
    }
}

// Обработка принятого сообщения в скайпе
void MainWindow::getMessageSkype(IDispatch* pMessage, TChatMessageStatus Status)
{
    QAxObject *Message= new QAxObject((IUnknown*)pMessage); // Получаем интерфейс
    QString nameChat_ = Message->dynamicCall("ChatName",QVariant()).toString(); // Получаем имя чата в которое кем то отправленно сообщение
    if ( Status == cmsReceived && (nameChat.contains(nameChat_) )) // убеждаемся что сообщения пришло не от нас Status == cmsReceived и то что чат является выбранным нами для диалога
    {
      QString message =  Message->dynamicCall("body",QVariant()).toString(); // получаем само сообщение

      QList <QString> keys = reply.keys(); // Получаем все ключи на которые реагирует бот, которые мы указали в конфиге
      foreach(QString key, keys)
      {
          QRegExp rx(key,Qt::CaseInsensitive); // Устанавливаем ключ для проверки сообщения не обращая внимания на регистр Qt::CaseInsensitive
          if (rx.lastIndexIn(message) != -1)
          {
            // Сообщения подходит по ключу
            int rand = qrand() % reply[key].count(); // Генерируем случайное число, для того что бы выбрать случайный ответ из возможных по данному ключу
            AxSkype->sendMessageChat(nameChat_,reply[key][rand]); // Отправляем наш случайный ответ
          }
      }
    }
    delete Message;
}

void MainWindow::on_aStartSkype_triggered()
{
    AxSkype->startSkype();
    testRunningSkype();
}

void MainWindow::on_aExit_triggered()
{
    QApplication::exit(0);
}


void MainWindow::exception(int num, QString arg1,QString arg2,QString arg3)
{
    clog << "Num:" << QString::number(num) << "arg1 =" <<arg1 << "arg2 =" <<arg2 << "arg3 =" <<arg3;
}


void MainWindow::aboutToShowMenu ( )
{
   testRunningSkype();
}

void MainWindow::on_aExitSkype_triggered()
{
    AxSkype->exitSkype();
    testRunningSkype();
}

void MainWindow::on_aConnectToSkype_triggered()
{
    if (!isSkypeConnect)
    {
        AxSkype = new Skype("Skype4COM.Skype", this);
        if (AxSkype!= NULL)
        {
            testRunningSkype();
            QObject::connect(AxSkype, SIGNAL(MessageStatus(IDispatch*, TChatMessageStatus)), this, SLOT(getMessageSkype(IDispatch*, TChatMessageStatus)));
            QObject::connect(AxSkype, SIGNAL(exception(int,QString,QString,QString)), this, SLOT(exception(int,QString,QString,QString)));


            if (AxSkype->IsRunning())
            {
                isSkypeConnect = true;
            }
        } else QMessageBox::critical(this,"Ошибка соединения со скайпом","Error");
    }
}



void MainWindow::closeConnectionSkype()
{

    if (isSkypeConnect)
    {
        if (AxSkype) {delete AxSkype; AxSkype = NULL;}
        isSkypeConnect = false;
    }
}

void MainWindow::on_aDisconnectSkype_triggered()
{
    closeConnectionSkype();
    testRunningSkype();
}

void MainWindow::on_aRefreshDictionary_triggered()
{
    reply.clear();
    nameChat.clear();
    QFile* file = new QFile(this->config);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file->isOpen())
    {
        QMessageBox::critical(this,"Ошибка открытия файла","Не открылся файл: " +file->fileName());
        clog << "Ошибка открытия файла XML: " + file->fileName() + " | error->"+file->errorString();
        return;
    }
    QXmlStreamReader config(file);
    QString attribut;
    QStringList resent;
    while (!config.atEnd() && !config.hasError())
    {
        QXmlStreamReader::TokenType tocken = config.readNext();
        if (tocken == QXmlStreamReader::StartDocument)
            continue;
        if (tocken == QXmlStreamReader::StartElement)
        {
            if (config.name() == "t")
            {
              if (config.attributes().hasAttribute("reg"))
              {
                 attribut = config.attributes().value("reg").toString();
              }
            }

            if (config.name() == "reply")
            {
                resent.append(config.readElementText());
            }

            if (config.name() == "namechat")
            {
                nameChat.append(config.readElementText());
            }

        }

        if(tocken == QXmlStreamReader::EndElement)
        {
            if (config.name() == "t")
            {
              reply[attribut] = resent;
              resent.clear();
            }
        }
    }



    if (config.hasError())
    {
        QMessageBox::critical(this,"Ошибка парсинга словаря",config.errorString());
        clog << "Ошибка парсера XML: " + config.errorString();
    } else isXMLError = false;
    file->close();
}


void MainWindow::activatedTrey(QSystemTrayIcon::ActivationReason arg)
{
    if (arg == QSystemTrayIcon::DoubleClick)
    {
        if (this->isHidden())
        {
            this->show();
            this->setWindowState( (this->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
            this->raise();
            this->activateWindow();
        }

    }

}


void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange && isMinimized())
    {
        event->ignore();

        QTimer::singleShot(0, this, SLOT(hide()));

    }
    else
        QMainWindow::changeEvent(event);
}

void MainWindow::on_aDialogChats_triggered()
{
    dialogChats = new DialogChats(this);
    QObject::connect(dialogChats,SIGNAL(accepted()),this,SLOT(acceptedDialogChats()));
    QList<QString> topics = AxSkype->getTopicChatsList();
    QList<QString> selectTopicFriendlyName;
    foreach (QString tNameChat, nameChat) {
      selectTopicFriendlyName.append( AxSkype->getTopicChat(tNameChat) );
    }
    dialogChats->setListTopic(topics,selectTopicFriendlyName);
    dialogChats->exec();
    delete dialogChats;
}

void MainWindow::setConfigNameChat(QStringList &chat)
{
    int  countNameChatNode;
    countNameChatNode = 0;
    QDomDocument opt;
    QFile iFile(this->config);

    if (!iFile.open(QFile::ReadOnly))
    {
        clog << "Ошибка открытия файла: " + this->config + "Сообщение: " + iFile.errorString();
        QMessageBox::critical(this,"Ошибка открытия файла: " + this->config,iFile.errorString());
        return;
    }

    opt.setContent(&iFile);
    iFile.close();
    QDomElement element = opt.documentElement();
    QDomNodeList domNodeList = element.childNodes();
    QList <QDomNode>  listNode;
    listNode.clear();
    for (int i = 0; i<domNodeList.count(); i++)
    {
        if (domNodeList.item(i).nodeName() == "namechat") listNode.append(domNodeList.item(i));
    }

    foreach (QDomNode n, listNode) {
        element.removeChild(n);
    }

    for (int i = 0; i<chat.count(); i++)
    {
        QDomElement domElement = opt.createElement("namechat");
        QDomText domText = opt.createTextNode(chat[i]);
        domElement.appendChild(domText);
        element.appendChild( domElement );
    }

    QFile oFile(this->config);
    oFile.remove();
    oFile.open(QFile::ReadWrite);
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 6, QDomNode::EncodingFromTextStream);
    oFile.close();
}

void MainWindow::acceptedDialogChats()
{
    QStringList topicsName = dialogChats->getListTopic ();
    QStringList setConfigChats;
    setConfigChats.clear();
    foreach (QString topicChat, topicsName) {
        setConfigChats.append(AxSkype->getNameChat(topicChat));
    }

    this->setConfigNameChat(setConfigChats);
    this->on_aRefreshDictionary_triggered();
    this->on_aDisconnectSkype_triggered();
    this->on_aConnectToSkype_triggered();
    QMessageBox::information(this,"Информация","Готово ");
}
