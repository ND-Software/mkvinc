#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{

    ui->setupUi(this);
    if(Connect()){ui->status->setText("Conectado...");}else{ui->status->setText("Error de conexion..");}
    InitializeQuery();
    QObject::connect(clients,SIGNAL(addPayDate(QString,QString)),this,SLOT(newPaidDate(QString,QString)));
    QObject::connect(clients,SIGNAL(refreshclients()),this,SLOT(refreshClients()));
    QObject::connect(clients,SIGNAL(refreshpays()),this,SLOT(refreshPays()));
    QObject::connect(clients,SIGNAL(addadmin(QString,QString,int)),this,SLOT(setAdminToDb(QString,QString,int)));
    QObject::connect(clients,SIGNAL(getNewClient(QString,QString,QString,QString,QString,QString,QString,QString,int,float)),this,SLOT(setNewClient(QString,QString,QString,QString,QString,QString,QString,QString,int,float)));
    QObject::connect(clients,SIGNAL(ReSendIdToDel(int)),this,SLOT(DELCLIENTID(int)));
    QObject::connect(clients,SIGNAL(SendAlterClient(int,QString,QString,QString,QString,QString,QString,QString,QString,int,float)),this,SLOT(ALTERCLIENT(int,QString,QString,QString,QString,QString,QString,QString,QString,int,float)));
    QObject::connect(clients,SIGNAL(filterSetsingle(QString)),this,SLOT(Filterssingle(QString)));
    QObject::connect(clients,SIGNAL(filterSetsingletwo(QString,int)),this,SLOT(Filterssingletwo(QString,int)));
    QObject::connect(clients,SIGNAL(filterSetdual(QString,QString)),this,SLOT(Filtersdual(QString,QString)));
    QObject::connect(clients,SIGNAL(SetPaid(int)),this,SLOT(recivePaidStatus(int)));
    QObject::connect(clients,SIGNAL(refreshnotpays()),this,SLOT(refreshNotPays()));


}



Login::~Login()
{
    delete ui;
}

void Login::on_Log_clicked()
{
    if(!db.open()){Connect();}
    if(validate(ui->user->text(),ui->password->text())){

        ChargeClients();
        ui->label->setText("");

    }else{
        ui->label->setText("Usuario o contrseña erroneos");
    }

}

void Login::on_user_returnPressed()
{
    if(!db.open()){Connect();}
    if(validate(ui->user->text(),ui->password->text())){
       ChargeClients();
       ui->label->setText("");
    }else{
        ui->label->setText("Usuario o contrseña erroneos");
    }


}

void Login::on_password_returnPressed()
{
    if(!db.open()){Connect();}
    if(validate(ui->user->text(),ui->password->text())){
        ChargeClients();
        ui->label->setText("");
    }else{
        ui->label->setText("Usuario o contrseña erroneos");
    }


}

void Login::on_Develop_clicked()
{
    if(!db.open()){Connect();}
    validateDeveloper(ui->user->text(),ui->password->text());
}
