/* A simple calculator, with sqlite.It was for a University Project.
 * All Rights Reserved By Stelios Trimis */

#ifndef GEOMATRICAL_H
#define GEOMATRICAL_H

#include <QDialog>
#include <calculator.h>
#include <QtMath>

namespace Ui {
class geomatrical;
}

class geomatrical : public QDialog
{
    Q_OBJECT

public:
    explicit geomatrical(QWidget *parent = nullptr);
    ~geomatrical();

private:
    Ui::geomatrical *ui;

private slots:

    void on_typical_clicked();
    void NumPressed2();
    void ClearButton2();
    void sinButton();
    void cosButton();
    void tanButton();
    void ChangeNumberSignn();
    //void dbfun();
    void on_Equals_clicked();
};

#endif // GEOMATRICAL_H
