#include "jieqthashwidget.h"
#include "./ui_jieqthashwidget.h"

JieQtHashWidget::JieQtHashWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JieQtHashWidget)
{
    ui->setupUi(this);
}

JieQtHashWidget::~JieQtHashWidget()
{
    delete ui;
}

