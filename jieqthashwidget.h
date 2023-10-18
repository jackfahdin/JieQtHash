#ifndef JIEQTHASHWIDGET_H
#define JIEQTHASHWIDGET_H

#include <QWidget>

#include "filehashthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class JieQtHashWidget; }
QT_END_NAMESPACE

class JieQtHashWidget : public QWidget
{
    Q_OBJECT

public:
    JieQtHashWidget(QWidget *parent = nullptr);
    ~JieQtHashWidget();

    // 拖拽事件
    void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;
    // 关闭事件
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;

    // 开始校验
    void startHash(QStringList fileList);

private slots:
    // 重置进度条
    void resetProgressBar(int count);
    // 添加信息
    void addMessage(QString message);
    void filterListMessage(QStringList listmessage);
    // 当前进度改变
    void currentChange(int progress);
    // 总进度改变
    void totalChange(int index);
    // 重置打开按钮
    void resetOpen();

    // 自动槽函数
    void on_pushButtonOpen_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonCopy_clicked();

    void on_pushButtonSlave_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::JieQtHashWidget *ui;

    // 哈希校验线程
    FileHashThread* fileHashThread;
};
#endif // JIEQTHASHWIDGET_H
