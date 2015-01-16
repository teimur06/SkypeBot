#include "skype.h"

Skype::Skype(QString objectCom, QObject *parent) :
    QAxObject(objectCom,parent),
    objectsChats(NULL)
{
    client = this->querySubObject("Client",QVariant());
    initChats();
}

Skype::~Skype()
{
    foreach (QAxObject * o, AxChatsPointer) {
        delete o;
    }
    if (objectsChats) delete objectsChats;
     delete client;
}

void Skype::initChats()
{
    AxChatsPointer.clear();
    AxChatsName.clear();
    objectsChats = this->querySubObject("Chats", QVariant());
    if (objectsChats != NULL)
    {
        QVariant countChat = objectsChats->dynamicCall("Count", QVariant());
        for (int i = 1; i <= countChat.toInt(); i++)
        {
            QAxObject * chat = objectsChats->querySubObject("Item(int)", QVariant(i));
            QString friendlyName = chat->dynamicCall("FriendlyName",QVariant()).toString();
            QString topic = chat->dynamicCall("Topic",QVariant()).toString();
            QString name = chat->dynamicCall("Name",QVariant()).toString();
          //  qDebug() << "topic = " + topic + " | name = "+name;
            if (friendlyName != "")
            {
                this->AxChatsPointer[name] = chat;
                if (topic != "")
                  this->AxChatsName[topic+" | "+friendlyName] = name;
                else
                  this->AxChatsName[friendlyName] = name;
            } else
              delete chat;
        }
    }
}


bool Skype::IsRunning()
{
    QVariant skypeIsRunning =  client->dynamicCall("IsRunning",QVariant());
    if (skypeIsRunning.toBool()) return true; else  return false;
}


void Skype::startSkype()
{
    if (!IsRunning())  client->dynamicCall("Start()",QVariant());
}


void Skype::exitSkype()
{
    if (IsRunning())  client->dynamicCall("Shutdown()",QVariant());
}


QList <QString> Skype::getTopicChatsList()
{

    return this->AxChatsName.keys();
}


QString Skype::getNameChat(QString topic)
{
    return this->AxChatsName[topic];
}

// Возвращает строку "Topic | FriendlyName" чата, по имени чата name
// Сделанно из за глюка что не у всех чатов видит topic
QString Skype::getTopicChat(QString name)
{
    if (AxChatsPointer.keys().contains(name))
    {
        QString result;
        QString topic = AxChatsPointer[name]->dynamicCall("Topic",QVariant()).toString();
        QString friendlyName = AxChatsPointer[name]->dynamicCall("FriendlyName",QVariant()).toString();
        if (friendlyName != "")
        {
            if (topic != "")
                result = topic+" | "+friendlyName;
            else
                result = friendlyName;
        }
        return result;
    }
    else return "";
}



void Skype::sendMessageChat(QString name,QString message)
{
    this->AxChatsPointer[name]->querySubObject("SendMessage(QString)",message);
}
