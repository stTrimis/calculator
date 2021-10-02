/* A simple calculator, with sqlite.It was for a University Project.
 * All Rights Reserved By Stelios Trimis */

#include "geomatrical.h"
#include "ui_geomatrical.h"
#include "db.h"
#include <calculator.h>

double calcVal2 = 0.0;

geomatrical::geomatrical(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::geomatrical)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal2));
    QPushButton *numButtons[10];
    for(int i=0; i<10; i++){
        QString butName="Button" +QString::number(i);
        numButtons[i] = geomatrical::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()),this,
                SLOT(NumPressed2()));
    }
    connect(ui->CosB, SIGNAL(released()), this, SLOT(cosButton()));
    connect(ui->SinB, SIGNAL(released()), this, SLOT(sinButton()));
    connect(ui->TanB, SIGNAL(released()), this, SLOT(tanButton()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButton2()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSignn()));
}



geomatrical::~geomatrical()
{
    delete ui;
}

void geomatrical::NumPressed2(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble()==0) || (displayVal.toDouble()== 0.0)){
        ui->Display->setText(butVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal));
    }
}

void geomatrical::on_typical_clicked(){
    Calculator *su = new Calculator();
    su->show();
    this->close();
}

void geomatrical::sinButton(){
    QString displayVal=ui->Display->text();
    double dblDisplayVal = qSin(displayVal.toDouble());
    ui->Display->setText(QString::number(dblDisplayVal));
    on_Equals_clicked();
}

void geomatrical::cosButton(){
    QString displayVal=ui->Display->text();
    double dblDisplayVal = qCos(displayVal.toDouble());
    ui->Display->setText(QString::number(dblDisplayVal));
    on_Equals_clicked();
}

void geomatrical::tanButton(){
    QString displayVal=ui->Display->text();
    double dblDisplayVal = qTan(displayVal.toDouble());
    ui->Display->setText(QString::number(dblDisplayVal));
    on_Equals_clicked();
}

void geomatrical::ClearButton2(){
    double solution=0.0;
    QString displayVal=ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(dblDisplayVal!=0.0){
        ui->Display->setText(QString::number(solution));
    }
}

void geomatrical::ChangeNumberSignn(){
   QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]+");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
        on_Equals_clicked();
    }
}

void geomatrical::on_Equals_clicked(){
    QString displayVal = ui->Display->text();
    db conn;
    if(!conn.connOpen()){

        QMessageBox::critical(this,"Σφάλμα","Η βάση δεδομένων δεν άνοιξε!");
    }
    conn.connOpen();
    QSqlQuery qry;

    qry.prepare("insert into geomatrical (Equals)"
                "values (:Equals)" );

    qry.bindValue(":Equals", displayVal);

    if(qry.exec())
    {
       QMessageBox::information(this,"Αποθήκευση ","save");

       conn.connClose();
     }
    else
    {
         QMessageBox::critical(this,"Σφάλμα","Ελέγξτε τα στοιχεία σας");
    }
}
