#ifndef MODCLIENT_H
#define MODCLIENT_H

#include <QDialog>

namespace Ui {
class ModClient;
}

class ModClient : public QDialog
{
    Q_OBJECT

public:
    explicit ModClient(QWidget *parent = 0);
    ~ModClient();

private slots:
    void on_pushButton_2_clicked();



    void on_pushButton_clicked();

signals:
    void alterClient(int id,QString name,QString surname,QString tel,QString dir,
                     QString mail,QString ipc,QString ips,QString mac,
                     int plan,float price);

private:
    Ui::ModClient *ui;
};

#endif // MODCLIENT_H
