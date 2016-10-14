#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include<QtSql/QSqlDriver>
#include"clients.h"
//#include<QDebug>
#include<vector>
using namespace std;
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT



public:

    explicit Login(QWidget *parent = 0);
    ~Login();
    //funciones de conexion con mysql
    bool Connect(){
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setPort(3306);
        db.setHostName("localhost");
        db.setDatabaseName("prueba");
        db.setUserName("root");
        db.setPassword("root");


        if(db.open()){return true;}
        return false;
    }

    void InitializeQuery(){qry = new QSqlQuery(db);} // esta funcion inicializa el query con la base de datos
    //esta funcion valida el inicio de sesion comun
    bool validate(QString usr,QString psw){
        int ac;
        qry->prepare("select * from adminusers where usr='"+usr+"' and  psw='"+psw+"';");
        qry->exec();
        int c=0;
        while(qry->next()){
            c++;
            ac=qry->value(1).toInt();
        }
        if(c==1){ clients->SETACCESS(ac); InitiateClients();return true;}
        return false;

    }
    //esta funcnion valida el inicio de sesion de desarrollador
    bool validateDeveloper(QString usr,QString psw){
        int ac;
        qry->prepare("select * from adminusers where usr='"+usr+"' and  psw='"+psw+"' and aclvl=2;");
        qry->exec();
        int c=0;
        while(qry->next()){
            c++;
            ac=qry->value(1).toInt();
        }
        if(c==1){clients->SETACCESS(ac);return true;}
        return false;

    }

    //funciones para inicializar ventanas
    //inicia la ventana clientes que es escensial para abrir las demas
    void InitiateClients(){
         clients->setModal(true);
         clients->show();

    }

    //carga porprimera vez la tabla de clientes
    void ChargeClients(){
        qry->prepare("select * from clients;");
        qry->exec();
        clients->setQueryModel(qry);

    }
    //cuenta la cantidad de clientes
    int cc(){
        int x=0;
        qry->prepare("select * from clients");
        qry->exec();
        while(qry->next()){
            x++;
        }
        return x;
    }



private slots:
    //modifica el estados de los pagos del id parametro
    void recivePaidStatus(int id){

        qry->prepare("update pagos set status = 'pagado' where id = :d");
        qry->bindValue(":d",id);
        qry->exec();
    }

    //funciones filter
    //esta flitra cuando solo se recibe el apellido
    void Filterssingle(QString A){
        qry->prepare("select * from clients where client_surname = :cs");
        qry->bindValue(":cs",A);
        qry->exec();
        clients->setQueryModel(qry);

    }
    //esta filtra cuando se recibe mac
    void Filterssingletwo(QString B,int a=0){
        a=0;
        qry->prepare("select * from clients where mac = :mc");
        qry->bindValue(":mc",B);
        qry->exec();
        clients->setQueryModel(qry);

    }
    //esta filtra cual se recibe apellido y mac
    void Filtersdual(QString A,QString B){

        qry->prepare("select * from clients where client_surname = :cs and mac = :mc");
        qry->bindValue(":cs",A);
        qry->bindValue(":mc",B);
        qry->exec();
        clients->setQueryModel(qry);

    }



    bool isIN(QString X,QString AS[],int l){
          for(int a=0;a<l;a++){if(X==AS[a]){return true;}}
          return false;
    }
    void emailNotPays(QString NP[],QString dateI){
        qry->prepare("select mail from pagos where date_paid= :date and status= 'sin pagar'");
        qry->bindValue(":date",dateI);
        qry->exec();
        int c=0;
        while(qry->next()){
            NP[c]=qry->value(0).toString();
            c++;
        }
        for(int i=0;i<c;i++){
            BuildDatandStore(NP[i],dateI);
        }
    }

    void BuildDatandStore(QString mail,QString dateI){
        QString apellido,direccion,mac;
        int plan;
        qry->prepare("select * from clients where mail=:m");
        qry->bindValue(":m",mail);
        qry->exec();
        while(qry->next()){
            apellido=qry->value(10).toString();
            mac=qry->value(9).toString();
            direccion=qry->value(2).toString();
            plan=qry->value(5).toInt();
        }
        qry->prepare("insert into impagos(apellido,direccion,mail,plan,periodo,mac) values(:a,:d,:m,:p,:pe,:mac)");
        qry->bindValue(":a",apellido);
        qry->bindValue(":d",direccion);
        qry->bindValue(":m",mail);
        qry->bindValue(":p",plan);
        qry->bindValue(":pe",dateI);
        qry->bindValue(":mac",mac);
        qry->exec();

    }


    // crea un nuevo mes de pago para todos los clientes registrados por mail
    void newPaidDate(QString A,QString B){
        QString NotPays[2050];
        int fechaanterior=A.toInt()-1;
        QString auxA;
        auxA.setNum(fechaanterior);
        QString dateI=auxA+"/"+B;
        //qDebug()<<auxA<<endl;
        //qDebug()<<dateI<<endl;
        emailNotPays(NotPays,dateI);
        QString dateP=A+"/"+B;
        QString Auxiliar[2050];
        int d=0;
        qry->prepare("select * from pagos where date_paid = :dp");
        qry->bindValue(":dp",dateP);
        qry->exec();
        while(qry->next()){
            Auxiliar[d]=qry->value(1).toString();
            d++;
        }
        QString mails[2050];
        int c=0;
        qry->exec("select * from clients;");
        while(qry->next()){
            if(isIN(qry->value(3).toString(),Auxiliar,d)==false){
                mails[c]=qry->value(3).toString();
                c++;
            }

        }

        for(int a=0;a<c;a++){

            qry->prepare("insert into pagos(mail,date_paid,status) values(:m,:d,'sin pagar')");
            qry->bindValue(":m",mails[a]);
            qry->bindValue(":d",dateP);
            qry->exec();
        }

    }
    // slots predeterminados de ui (inicializados en el cpp
    void on_Log_clicked();

    void on_user_returnPressed();

    void on_password_returnPressed();

    void on_Develop_clicked();

    //actualiza las tablas de clientes
    void refreshClients(){
         qry->prepare("select * from clients;");
         qry->exec();
         clients->setQueryModel(qry);

    }
    //actualiza lastables de pagos
    void refreshPays(){
        qry->prepare("select * from pagos;");
        qry->exec();
        clients->setQueryModel(qry);
    }
    void refreshNotPays(){
        qry->prepare("select * from impagos;");
        qry->exec();
        clients->setQueryModel(qry);
    }



   // registra un nuevo administrador
    void setAdminToDb(QString usr,QString psw,int lvl){

        qry->prepare("insert into adminusers(aclvl,usr,psw) values(:l,:a,:p)");
        qry->bindValue(":l",lvl);
        qry->bindValue(":a",usr);
        qry->bindValue(":p",psw);

        qry->exec();


    }
    // registra un nuevo cliente
    void setNewClient(QString name,QString surname,QString direction,QString tel,QString mail,QString ipc,QString ips,QString mac,int plan,float price){

        qry->prepare("insert into clients(client_name,direction,mail,tel,plan,price,ip_client,ip_service,mac,client_surname) values(:cn,:dir,:ml,:tl,:pl,:pp,:ip_c,:ip_s,:mc,:cs)");
        qry->bindValue(":cn",name);
        qry->bindValue(":dir",direction);
        qry->bindValue(":ml",mail);
        qry->bindValue(":tl",tel);
        qry->bindValue(":pl",plan);
        qry->bindValue(":pp",price);
        qry->bindValue(":ip_c",ipc);
        qry->bindValue(":ip_s",ips);
        qry->bindValue(":mc",mac);
        qry->bindValue(":cs",surname);
        qry->exec();


    }
    //borra un cliente por id
    void DELCLIENTID(int id){
        qry->prepare("delete from clients where id=:d");
        qry->bindValue(":d",id);
        qry->exec();
        qry->prepare("alter table clients auto_increment=:i");
        qry->bindValue(":i",id);
        qry->exec();
    }

    // modifica un cliente
    void ALTERCLIENT(int id,QString name,QString surname,QString tel,QString dir,
                     QString mail,QString ipc,QString ips,QString mac,
                     int plan,float price){

        qry->prepare("update clients set client_name=:n , direction=:d , mail=:m , tel=:t , plan=:pn , price=:pr , ip_client=:ipclient , ip_service=:ipservice , mac=:mc , client_surname=:srname where id=:i");
        qry->bindValue(":n",name);
        qry->bindValue(":d",dir);
        qry->bindValue(":m",mail);
        qry->bindValue(":t",tel);
        qry->bindValue(":pn",plan);
        qry->bindValue(":pr",price);
        qry->bindValue(":ipclient",ipc);
        qry->bindValue(":ipservice",ips);
        qry->bindValue(":mc",mac);
        qry->bindValue(":srname",surname);
        qry->bindValue(":i",id);
        qry->exec();


    }




    void on_pushButton_clicked();

private:
    QSqlDatabase db;
    QSqlQuery *qry;
    Ui::Login *ui;
    Clients *clients = new Clients(this);


};
#endif // LOGIN_H
