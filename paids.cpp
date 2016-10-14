#include "paids.h"
#include "ui_paids.h"

Paids::Paids(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paids)
{
    ui->setupUi(this);
}

Paids::~Paids()
{
    delete ui;
}

void Paids::on_pushButton_4_clicked()
{
    this->close();
}



void Paids::on_pushButton_clicked()
{
    emit paidst(ui->paidid->value());

}
