#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QtSimPanel.h"

int main(int argc, char *argv[])
{
    QtSimPanel SimPanel(argc, argv);
    SimPanel.startApp();
    return 0;
}
