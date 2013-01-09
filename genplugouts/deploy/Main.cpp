
#include "UmlCom.h"
#include "UmlItem.h"
#include "UmlComponent.h"
#include "UmlClass.h"
#include <QApplication>
#include <QDir>
#include "../../src/Logging/QsLog.h"
#include "../../src/Logging/QsLogDest.h"
// the program is called with the socket port number in argument

int main(int argc, char ** argv)
{
    if (argc != 2)
        return 0;
    QsLogging::Logger & logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    QDir dir;
    dir.setPath(qApp->applicationDirPath());
    dir.remove(QString("deploy") + QString(".log"));
    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath(QString("deploy") + QString(".log")));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(sLogPath));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    QLOG_INFO() << " STARTING DEPLOY";
    if (UmlCom::connect(QString(argv[1]).toUInt())) {
        try {
            UmlCom::trace("<b>Deploy classes</b> release 1.1 (C++ version)<br>");
            UmlCom::targetItem()->deploy();
            UmlCom::trace("Done");
        }
        catch (...) {
        }

        // must be called to cleanly inform that all is done
        UmlCom::bye();
    }

    UmlCom::close();
    return 0;
}