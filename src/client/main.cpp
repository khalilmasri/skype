#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "program.hpp"

#include <thread>
#include <QApplication>
#include <iostream>
#include <QFile>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QFile stylesheetFile("../misc/stylesheet/Fibrary.qss");
    stylesheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(stylesheetFile.readAll());
    a.setStyleSheet(styleSheet);

    Program *program = new Program();

    int res = a.exec();

    delete program;

    return res;
}
