#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_cancel_clicked()
{
    this->close();
}

void Register::on_ok_clicked()
{
  if(ui->aclvl->value()==1 || ui->aclvl->value()==0){
      if(ui->usr->text().size()!=0 && ui->psw->text().size()!=0){
         emit getAdminData(ui->usr->text(),ui->psw->text(),ui->aclvl->value());
         this->close();
      }
  }else{
      ui->Alert->setText("El nivel Dado no es Valido Ingrese Valores entre 1 y 0");
  }
}
