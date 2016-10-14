#include "clients.h"
#include "ui_clients.h"
#include<stdlib.h>
Clients::Clients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clients)
{
    ui->setupUi(this);



    QObject::connect(reg,SIGNAL(getAdminData(QString,QString,int)),this,SLOT(getRegisterData(QString,QString,int)));
    QObject::connect(adclient,SIGNAL(getClientData(QString,QString,QString,QString,QString,QString,QString,QString,int,float)),this,SLOT(sendNewClient(QString,QString,QString,QString,QString,QString,QString,QString,int,float)));
    QObject::connect(dcl,SIGNAL(delClientId(int)),this,SLOT(getClientToDel(int)));
    QObject::connect(mdcl,SIGNAL(alterClient(int,QString,QString,QString,QString,QString,QString,QString,QString,int,float)),this,SLOT(GetAlterClient(int,QString,QString,QString,QString,QString,QString,QString,QString,int,float)));
    QObject::connect(pd,SIGNAL(paidst(int)),this,SLOT(alterpaid(int)));




}




Clients::~Clients()
{
    delete ui;
}

void Clients::on_pushButton_5_clicked()
{
    this->close();
}

void Clients::on_register_2_clicked()
{
 if(ACESS>0){
  reg->setModal(true);
  reg->show();
}
}

void Clients::on_new_user_clicked()
{
    if(ACESS>0){
        adclient->setModal(true);
        adclient->show();
    }
}

void Clients::on_delete_2_clicked()
{
    if(ACESS>0){
        dcl->setModal(true);
        dcl->show();
    }
}

void Clients::on_alter_clicked()
{
    if(ACESS>0){
    mdcl->setModal(true);
    mdcl->show();
    }
}

void Clients::on_pays_clicked()
{

   if(ACESS>0){
      emit refreshpays();
      Clients::ui->tableView->setModel(mod);

   }
}

void Clients::on_clientstable_clicked()
{
    emit refreshclients();
    Clients::ui->tableView->setModel(mod);

}

void Clients::on_add_clicked()
{
    if(ACESS>0){
    QString a,b;
    a.setNum(ui->month->value());
    b.setNum(ui->year->value());
    emit addPayDate(a,b);
    emit refreshpays();
    }

}

void Clients::on_Filter_clicked()
{
   if(ui->Surname_filter->text().size()!=0 && ui->Mac_filter->text().size()!=0){
       emit filterSetdual(ui->Surname_filter->text(),ui->Mac_filter->text());
       Clients::ui->tableView->setModel(mod);
   }else{
       if(ui->Surname_filter->text().size()!=0 && ui->Mac_filter->text().size()==0){
           emit filterSetsingle(ui->Surname_filter->text());
           Clients::ui->tableView->setModel(mod);
       }else{
           emit filterSetsingletwo(ui->Mac_filter->text(),1);
           Clients::ui->tableView->setModel(mod);
       }
   }

}

void Clients::on_estados_pagos_clicked()
{
    //int a;
    if(ACESS>0){

          pd->setModal(true);
          pd->show();




    }
}

void Clients::on_impagos_clicked()
{
    if(ACESS>0){
        emit refreshnotpays();
        Clients::ui->tableView->setModel(mod);
    }
}
