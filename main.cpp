/**     Arduino Sonar
    FJS. February 2016
  Application to visualize the output of an arduino-based sonar.
  06-02-2016. Version 1.0. First working version.
  07-02-2016. Solved list out of bounds bug.
*/


#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
