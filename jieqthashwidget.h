#ifndef JIEQTHASHWIDGET_H
#define JIEQTHASHWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class JieQtHashWidget; }
QT_END_NAMESPACE

class JieQtHashWidget : public QWidget
{
    Q_OBJECT

public:
    JieQtHashWidget(QWidget *parent = nullptr);
    ~JieQtHashWidget();

private:
    Ui::JieQtHashWidget *ui;
};
#endif // JIEQTHASHWIDGET_H
