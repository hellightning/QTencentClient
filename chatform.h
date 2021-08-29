#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>

class ClientAdapter;

typedef QString Message;
namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

private slots:
    void on_sendMessageButton_clicked();

    void on_closeFormButton_clicked();

private:
    Ui::ChatForm *ui;
    void init_list_widget(QList<Message>);
    void update_list_widget(Message);
};

#endif // CHATFORM_H
