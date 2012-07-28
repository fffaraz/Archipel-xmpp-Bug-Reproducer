#include <QtGui/QApplication>
#include "mainwindow.h"

#include "QXmppLogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::StdoutLogging);

    return a.exec();
}
