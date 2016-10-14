#ifndef DELCLIENT_H
#define DELCLIENT_H

#include <QDialog>

namespace Ui {
class DelClient;
}

class DelClient : public QDialog
{
    Q_OBJECT

public:
    explicit DelClient(QWidget *parent = 0);
    ~DelClient();

private slots:
    void on_cancel_clicked();

    void on_ok_clicked();

signals:
    void delClientId(int id);

private:
    Ui::DelClient *ui;
};

#endif // DELCLIENT_H
