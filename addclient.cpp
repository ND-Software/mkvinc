#include "addclient.h"
#include "ui_addclient.h"

Addclient::Addclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addclient)
{
    ui->setupUi(this);
}

Addclient::~Addclient()
{
    delete ui;
}

void Addclient::on_ok_clicked()
{
    if(ui->name->text().size()!=0 && ui->surname->text().size()!=0 && ui->Direction->text().size()!=0 && ui->Tel->text().size()!=0 &&
            ui->Mail->text().size()!=0 && ui->ip_client->text().size()!=0 &&
            ui->ip_serv->text().size()!=0 && ui->MAC->text().size()!=0){
    emit getClientData(ui->name->text(),ui->surname->text()
                       ,ui->Direction->text(),ui->Tel->text(),
                       ui->Mail->text(),ui->ip_client->text(),
                       ui->ip_serv->text(),ui->MAC->text(),
                       ui->plan->value(),ui->price->value()
                       );
        ui->name->setText("");
        ui->surname->setText("");
        ui->Direction->setText("");
        ui->Tel->setText("");
        ui->Mail->setText("");
        ui->ip_client->setText("");
        ui->ip_serv->setText("");
        ui->MAC->setText("");
        ui->price->setValue(0);
        ui->plan->setValue(0);
        this->close();
    }else{
        ui->Alert->setText("No puede haber campos vacios.");
    }
}

void Addclient::on_cancel_clicked()
{
    this->close();
}
