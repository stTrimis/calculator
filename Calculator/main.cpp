/* A simple calculator, with sqlite.It was for a University Project.
 * All Rights Reserved By Stelios Trimis */

#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}
