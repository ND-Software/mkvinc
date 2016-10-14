#include "modclient.h"
#include "ui_modclient.h"

ModClient::ModClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModClient)
{
    ui->setupUi(this);
}

ModClient::~ModClient()
{
    delete ui;
}

void ModClient::on_pushButton_2_clicked()
{
    this->close();
}

void ModClient::on_pushButton_clicked()
{
    if(ui->name->text().size()!=0 && ui->surname->text().size()!=0 &&
       ui->tel->text().size()!=0 && ui->direction->text().size()!=0 &&
       ui->mail->text().size()!=0 && ui->ipc->text().size()!=0 &&
       ui->ips->text().size()!=0 && ui->mac->text().size()!=0){

        emit alterClient(ui->id->value(),ui->name->text(),
                         ui->surname->text(),ui->tel->text(),
                         ui->direction->text(),ui->mail->text(),
                         ui->ipc->text(),ui->ips->text(),
                         ui->mac->text(),ui->plan->value(),
                         ui->price->value()
                    );
        ui->name->setText("");
        ui->surname->setText("");
        ui->direction->setText("");
        ui->tel->setText("");
        ui->mail->setText("");
        ui->ipc->setText("");
        ui->ips->setText("");
        ui->mac->setText("");
        ui->price->setValue(0);
        ui->plan->setValue(0);
        this->close();

    }



}
