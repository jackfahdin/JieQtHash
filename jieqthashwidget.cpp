#include "jieqthashwidget.h"
#include "./ui_jieqthashwidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QMimeData>
#include <QDateTime>

JieQtHashWidget::JieQtHashWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JieQtHashWidget)
{
    ui->setupUi(this);

    fileHashThread = new FileHashThread();
    connect(fileHashThread, SIGNAL(hashStarted(int)), this, SLOT(resetProgressBar(int)));
    //connect(fileHashThread, SIGNAL(hashResult(QString)), this, SLOT(addMessage(QString)));
    connect(fileHashThread, SIGNAL(hashResultList(QStringList)), this, SLOT(filterListMessage(QStringList)));
    connect(fileHashThread, SIGNAL(hashError(QString)), this, SLOT(addMessage(QString)));
    connect(fileHashThread, SIGNAL(hashProgressChanged(int)), this, SLOT(currentChange(int)));
    connect(fileHashThread, SIGNAL(hashIndexChanged(int)), this, SLOT(totalChange(int)));
    connect(fileHashThread, SIGNAL(hashEnded()), this, SLOT(resetOpen()));
}

JieQtHashWidget::~JieQtHashWidget()
{
    delete ui;
    delete fileHashThread;
}

void JieQtHashWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if(ui->pushButtonOpen->isEnabled() &&
        event->mimeData()->hasUrls())
    {
        QList<QUrl> urls = event->mimeData()->urls();

        int i = 0;
        while (i < urls.length())
        {
            QString path = urls[i].toLocalFile();
            QFileInfo info(path);

            if (!info.isFile())
                break;

            i++;
        }

        if (i == urls.length())
        {
            event->acceptProposedAction();
            return;
        }
    }
    event->ignore();
}

void JieQtHashWidget::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();

    QStringList fileList;
    for (int i = 0; i < urls.count(); i++)
        fileList << urls[i].toLocalFile();

    startHash(fileList);
}

void JieQtHashWidget::closeEvent(QCloseEvent* event)
{
    fileHashThread->setStop(true);
    fileHashThread->wait();

    event->accept();
}

void JieQtHashWidget::resetProgressBar(int count)
{
    ui->progressBarFile->setValue(0);
    ui->progressBarTotal->setMaximum(count);
    ui->progressBarTotal->setValue(0);
}

void JieQtHashWidget::addMessage(QString message)
{
    ui->pushButtonClear->setEnabled(true);
    ui->pushButtonCopy->setEnabled(true);
    ui->pushButtonSlave->setEnabled(true);

    ui->plainTextEditMessage->appendPlainText(message);
}

void JieQtHashWidget::filterListMessage(QStringList listMessage)
{
    QString messsge;
    messsge = QString("文件: %1\n").arg(listMessage.at(0));

    // 文件日期
    if(ui->checkBoxDate->isChecked())
        messsge += QString("日期: %1\n").arg(listMessage.at(1));
    if(ui->checkBoxSize->isChecked())
        messsge += QString("大小: %1字节\n").arg(listMessage.at(2));
    if(ui->checkBoxMD5->isChecked())
        messsge += QString("MD5: %1\n").arg(listMessage.at(4));
    if(ui->checkBoxSHA->isChecked())
        messsge += QString("SHA1: %1\n").arg(listMessage.at(5));
    if(ui->checkBoxSHA256->isChecked())
        messsge += QString("SHA256: %1\n").arg(listMessage.at(6));

    if(!messsge.isEmpty())
        addMessage(messsge);

}

void JieQtHashWidget::currentChange(int progress)
{
    ui->progressBarFile->setValue(progress);
}

void JieQtHashWidget::totalChange(int index)
{
    ui->progressBarTotal->setValue(index);
}

void JieQtHashWidget::resetOpen()
{
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonOpen->setEnabled(true);
}

void JieQtHashWidget::startHash(QStringList fileList)
{
    ui->pushButtonOpen->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);

    fileHashThread->setFileList(fileList);
    fileHashThread->setStop(false);
    fileHashThread->start();
}

void JieQtHashWidget::on_pushButtonOpen_clicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, NULL, NULL, "所有文件(*.*)");
    if (fileList.size() > 0)
        startHash(fileList);
}


void JieQtHashWidget::on_pushButtonClear_clicked()
{
    ui->pushButtonClear->setEnabled(false);
    ui->pushButtonCopy->setEnabled(false);
    ui->pushButtonSlave->setEnabled(false);
    // 清除message内容时重置进度条
    ui->progressBarFile->setValue(0);
    ui->progressBarTotal->setValue(0);

    ui->plainTextEditMessage->clear();
}


void JieQtHashWidget::on_pushButtonCopy_clicked()
{
    QString message = ui->plainTextEditMessage->toPlainText();
    QApplication::clipboard()->setText(message);
}


void JieQtHashWidget::on_pushButtonSlave_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, NULL, "JieQtHash_" +
                                                QDateTime::currentDateTime()
                                                .toString("yyyyMMdd_hhmmss") + ".txt",
                                                "文本文件(*.txt);;所有文件(*.*)");
    if (path.isEmpty())
        return;

    QString message = ui->plainTextEditMessage->toPlainText();

    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(message.toUtf8());
        file.close();
    }
    else
        QMessageBox::critical(this, "错误", "文件打开失败");
}


void JieQtHashWidget::on_pushButtonStop_clicked()
{
    ui->pushButtonStop->setEnabled(false);
    fileHashThread->setStop(true);
}


void JieQtHashWidget::on_pushButtonClose_clicked()
{
    QApplication::quit();
}

