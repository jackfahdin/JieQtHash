#include "jieqthashwidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "JieQtHash_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    JieQtHashWidget w;
    w.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    w.setWindowTitle("文件校验");
    w.show();
    return a.exec();
}
