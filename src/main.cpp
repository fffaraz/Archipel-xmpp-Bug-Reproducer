#include <QtGui/QApplication>

#include "windowmain.h"
#include "QXmppLogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowMain w;
    w.show();

    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::StdoutLogging);

    return a.exec();
}
