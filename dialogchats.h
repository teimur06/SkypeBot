#ifndef DIALOGCHATS_H
#define DIALOGCHATS_H

#include <QDialog>
#include <QStringList>
#include <QAbstractButton>
#include <QDebug>
#include <QWidgetItem>


namespace Ui {
class DialogChats;
}

class DialogChats : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChats(QWidget *parent = 0);
    ~DialogChats();
    void setListTopic(QList<QString> &list, QList<QString> &selectitems);
    QStringList getListTopic();
private slots:
    void on_ChatList_doubleClicked(const QModelIndex &index);

private:
    Ui::DialogChats *ui;
};

#endif // DIALOGCHATS_H
