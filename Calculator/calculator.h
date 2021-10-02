/* A simple calculator, with sqlite.It was for a University Project.
 * All Rights Reserved By Stelios Trimis */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QtMath>
#include <cmath>
#include <geomatrical.h>
#include <db.h>
namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
    void MathButton();
    void EqualButton();
    void ChangeNumberSign();
    void ClearButton();
    void SqrtButton();
    void on_pushButton_clicked();
};


#endif // CALCULATOR_H
