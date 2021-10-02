/* A simple calculator, with sqlite.It was for a University Project.
 * All Rights Reserved By Stelios Trimis */

#include "calculator.h"
#include "ui_calculator.h"


double calcVal=0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool powTrigger = false;
bool modTrigger = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; i++){
        QString butName="Button" +QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()),this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButton()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButton()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButton()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButton()));
    connect(ui->Modulo, SIGNAL(released()), this, SLOT(MathButton()));
    connect(ui->Pow, SIGNAL(released()), this, SLOT(MathButton()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButton()));
    connect(ui->Sqrt, SIGNAL(released()), this, SLOT(SqrtButton()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
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

void Calculator::MathButton(){
     divTrigger = false;
     multTrigger = false;
     addTrigger = false;
     subTrigger = false;
     powTrigger = false;
     modTrigger = false;
    QString displayVal=ui->Display->text();
    calcVal=displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    else if(QString::compare(butVal, "Pow", Qt::CaseInsensitive) == 0){
        powTrigger = true;
    }
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    }
    else{
        modTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButton(){



    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger || powTrigger || modTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }
        else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }
        else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }
        else if(divTrigger){
            solution = calcVal / dblDisplayVal;
        }
        else if(powTrigger){
            solution = qPow(calcVal, dblDisplayVal);
        }
        else{
            solution = fmod(calcVal, dblDisplayVal);
        }
     }
     ui->Display->setText(QString::number(solution));


     db conn;
     if(!conn.connOpen()){

         QMessageBox::critical(this,"Σφάλμα","Η βάση δεδομένων δεν άνοιξε!");
     }
     conn.connOpen();
     QSqlQuery qry;

     qry.prepare("insert into calculator (Equals)"
                 "values (:Equals)" );

     qry.bindValue(":Equals", solution);

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

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]+");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearButton(){
    double solution=0.0;
    QString displayVal=ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(dblDisplayVal!=0.0){
        ui->Display->setText(QString::number(solution));
    }
}

void Calculator::SqrtButton(){
    QString displayVal=ui->Display->text();
    double dblDisplayVal = qSqrt(displayVal.toDouble());
    ui->Display->setText(QString::number(dblDisplayVal));
}

void Calculator::on_pushButton_clicked()
{
    geomatrical *su = new geomatrical();
    su->show();
    this->close();
}


