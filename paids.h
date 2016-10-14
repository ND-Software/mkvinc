#ifndef PAIDS_H
#define PAIDS_H

#include <QDialog>

namespace Ui {
class Paids;
}

class Paids : public QDialog
{
    Q_OBJECT

public:
    explicit Paids(QWidget *parent = 0);
    ~Paids();

private slots:
    void on_pushButton_4_clicked();



    void on_pushButton_clicked();

signals:

   void paidst(int id);

private:
    Ui::Paids *ui;
};

#endif // PAIDS_H
