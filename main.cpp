#include "mainwindow.hpp"

#include "gen/config.hpp"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription("Puzzle games bundle.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("game", QCoreApplication::translate("main", "Game to play."));
    parser.addOptions({
        {"l", QCoreApplication::translate("main", "Displays list of avaliable games.")},
    });
    parser.process(a);

    const QStringList args = parser.positionalArguments();

    MainWindow w;
    w.show();
    return a.exec();
}
