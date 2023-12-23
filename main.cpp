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
    // 删除最大化与最小化
    // w.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    w.setWindowTitle("文件校验 1.0.1");
    // 设置窗口标志，使其保持在顶部
    w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.show();
    return a.exec();
}
