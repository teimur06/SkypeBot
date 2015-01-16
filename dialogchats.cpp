#include "dialogchats.h"
#include "ui_dialogchats.h"

DialogChats::DialogChats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChats)
{
    ui->setupUi(this);
    ui->buttonBox->buttons().value(0)->setText("Войти в чат");
    ui->buttonBox->buttons().value(1)->setText("Отмена");
}

DialogChats::~DialogChats()
{
    delete ui;
}


// Устанавливает в параметри list список строк ChatList, а selectitems выделяет нужные строки
void DialogChats::setListTopic(QList<QString> &list, QList<QString> &selectitems)
{
    foreach (QString l, list)
        ui->ChatList->addItem(l);


    foreach (QString s, selectitems)
    {
        QList <QListWidgetItem *> items = ui->ChatList->findItems(s,Qt::MatchRecursive);
        foreach (QListWidgetItem * item, items) {
            item->setSelected(true);
        }
    }
}


QStringList DialogChats::getListTopic()
{
    QStringList list;

        QList<QListWidgetItem*> items = ui->ChatList->selectedItems();
        foreach (QListWidgetItem* item, items)
        {
            list.append(  item->text()  );
        }
    return list;
}

void DialogChats::on_ChatList_doubleClicked(const QModelIndex &)
{
    this->accepted();
    this->close();
}
