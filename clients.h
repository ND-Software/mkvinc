#ifndef CLIENTS_H
#define CLIENTS_H

#include <QDialog>
#include"register.h"
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include"addclient.h"
#include"delclient.h"
#include"modclient.h"
#include"paids.h"

namespace Ui {
class Clients;
}

class Clients : public QDialog
{
    Q_OBJECT

public:

    //estabece el modelo decarga de tablas
    void setQueryModel(QSqlQuery *md){
        mod->setQuery(*md);
    }
    //revisa los niveles de acceso
    void SETACCESS(int ac){ACESS=ac;}



    explicit Clients(QWidget *parent = 0);
    ~Clients();

private slots:
    void on_pushButton_5_clicked();
    void on_register_2_clicked();
    void getRegisterData(QString usr,QString psw,int lvl){
        emit addadmin(usr,psw,lvl);

    }
    void sendNewClient(QString name,QString surname,QString direction,QString tel,QString mail,QString ipc,QString ips,QString mac,int plan,float price){
        emit getNewClient(name,surname,direction,tel,mail,ipc,ips,mac,plan,price);
        emit refreshclients();
    }
    void on_new_user_clicked();
    void getClientToDel(int id){emit ReSendIdToDel(id);emit refreshclients();}


    void on_delete_2_clicked();
    void GetAlterClient(int id,QString name,QString surname,QString tel,QString dir,
                        QString mail,QString ipc,QString ips,QString mac,int plan,float price)
    {emit SendAlterClient(id,name,surname,tel,dir,mail,ipc,ips,mac,plan,price);emit refreshclients();}

    void alterpaid(int id){
         emit SetPaid(id);
         emit refreshpays();
    }


    void on_alter_clicked();

    void on_pays_clicked();

    void on_clientstable_clicked();

    void on_add_clicked();

    void on_Filter_clicked();

    void on_estados_pagos_clicked();

    void on_impagos_clicked();

signals:
    void SetPaid(int id);
    void filterSetdual(QString A,QString B);
    void filterSetsingle(QString A);
    void filterSetsingletwo(QString A,int b=0);

    void refreshclients();
    void refreshpays();
    void refreshnotpays();
    void addPayDate(QString A,QString B);
    void addadmin(QString usr,QString psw,int lvl);
    void getNewClient(QString name,QString surname,QString direction,QString tel,QString mail,QString ipc,QString ips,QString mac,int plan,float price);
    void ReSendIdToDel(int id);
    void SendAlterClient(int id,QString name,QString surname,QString tel,QString dir,
                         QString mail,QString ipc,QString ips,QString mac,
                         int plan,float price);

    void OpenPagos();

private:
    Ui::Clients *ui;
    QSqlQueryModel *mod =  new QSqlQueryModel();
    QSqlQuery *ry;
    Register *reg = new Register(this);
    int ACESS;
    Addclient *adclient = new Addclient(this);
    DelClient *dcl =new DelClient(this);
    ModClient *mdcl = new ModClient(this);
    Paids *pd = new Paids(this);

};

#endif // CLIENTS_H
