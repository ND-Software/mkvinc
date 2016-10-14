#include "delclient.h"
#include "ui_delclient.h"

DelClient::DelClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelClient)
{
    ui->setupUi(this);
}

DelClient::~DelClient()
{
    delete ui;
}

void DelClient::on_cancel_clicked()
{
    this->close();
}

void DelClient::on_ok_clicked()
{

        emit delClientId(ui->id->value());
        ui->id->setValue(0);
        this->close();


}
