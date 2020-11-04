/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     chendu <chendu@uniontech.com>
*
* Maintainer: chendu <chendu@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "progressdialog.h"

#include <DFontSizeManager>

#include <QBoxLayout>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>



ProgressDialog::ProgressDialog(QWidget *parent):
    DAbstractDialog(parent)
{
    initUI();
    initConnect();
}

void ProgressDialog::initUI()
{
    setWindowFlags((windowFlags() & ~ Qt::WindowSystemMenuHint /*& ~Qt::Dialog*/) | Qt::Window);
    setFixedWidth(m_defaultWidth);
    setMinimumHeight(m_defaultHeight);

    // 标题栏显示有几个任务正在进行
    m_titlebar = new DTitlebar(this);
    m_titlebar->setFixedHeight(50);
    m_titlebar->layout()->setContentsMargins(0, 0, 0, 0);
    m_titlebar->setMenuVisible(false);
    m_titlebar->setIcon(QIcon::fromTheme("deepin-compressor"));
    m_titlebar->setFixedWidth(m_defaultWidth);
    m_titlebar->setTitle(tr("%1 task(s) in progress").arg(1));
    m_titlebar->setBackgroundTransparent(true);

    QVBoxLayout *contentlayout = new QVBoxLayout;

    // 显示当前任务
    m_tasklable = new DLabel(this);
    m_tasklable->setText(tr("Task") + ": ");
    m_tasklable->setForegroundRole(DPalette::WindowText);
    DFontSizeManager::instance()->bind(m_tasklable, DFontSizeManager::T6, QFont::Medium);

    // 显示当前文件名
    m_filelable = new DLabel(this);
    m_filelable->setText(tr("Extracting") + ":");
    m_filelable->setForegroundRole(DPalette::TextTips);
    DFontSizeManager::instance()->bind(m_filelable, DFontSizeManager::T8, QFont::Normal);

    // 显示进度
    m_circleprogress = new  DProgressBar(this);
    m_circleprogress->setFixedSize(336, 6);
    m_circleprogress->setValue(0);

    contentlayout->setContentsMargins(20, 0, 10, 0);
    contentlayout->addWidget(m_tasklable, 0, Qt::AlignLeft | Qt::AlignVCenter);
    contentlayout->addSpacing(7);
    contentlayout->addWidget(m_filelable, 0, Qt::AlignLeft | Qt::AlignVCenter);
    contentlayout->addSpacing(7);
    contentlayout->addWidget(m_circleprogress, 0, Qt::AlignLeft | Qt::AlignVCenter);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->setContentsMargins(0, 0, 10, 20);
    mainlayout->setSpacing(0);
    mainlayout->addWidget(m_titlebar);
    mainlayout->addLayout(contentlayout);

    setLayout(mainlayout);
//    m_extractdialog = new ExtractPauseDialog(this);
}

void ProgressDialog::initConnect()
{
//    connect(m_extractdialog, &ExtractPauseDialog::sigbuttonpress, this, &ProgressDialog::slotextractpress);
}

/**
 * @brief ProgressDialog::setCurrentTask 设置当前压缩文件名
 * @param file
 */
void ProgressDialog::setCurrentTask(const QString &file)
{
    QFileInfo fileinfo(file);
    m_tasklable->setText(tr("Task") + ":" + fileinfo.fileName());
}

/**
 * @brief ProgressDialog::setCurrentFile 设置正在提取的文件名
 * @param file
 */
void ProgressDialog::setCurrentFile(const QString &file)
{
    // 对字符串长度进行...划分
    QFontMetrics elideFont(m_filelable->font());
    m_filelable->setText(elideFont.elidedText(tr("Extracting") + ":" + file, Qt::ElideMiddle, 330));
}

/**
 * @brief ProgressDialog::setProcess 设置进度
 * @param value
 */
void ProgressDialog::setProcess(int value)
{
    if ((m_dPerent - value) == 0 || (m_dPerent > value)) {
        return ;
    }
    m_dPerent = value;

    if (100 != m_circleprogress->value()) {
        m_circleprogress->setValue(value);
    }
}

/**
 * @brief ProgressDialog::setFinished 提取结束
 * @param path
 */
void ProgressDialog::setFinished()
{
//    if (100 != m_circleprogress->value()) {
//        setWindowTitle("");
    m_circleprogress->setValue(0);
    m_dPerent = 0;
//        m_filelable->setText(tr("Extraction successful") + ":" + tr("Extract to") + path);
//    m_extractdialog->reject();
    //reject();
    hide();
////        m_filelable->setText(tr("Extracting") + ":");
////        emit extractSuccess(tr("Extraction successful", "progressdialog"));
//        emit sigResetPercentAndTime();
//    }
}

/**
 * @brief ProgressDialog::clearprocess 清除进度
 */
void ProgressDialog::clearprocess()
{
    m_dPerent = 0;
    m_circleprogress->setValue(0);
}

void ProgressDialog::closeEvent(QCloseEvent *)
{
//    if (m_circleprogress->value() < 100 && m_circleprogress->value() > 0) {
//        accept();
//        m_extractdialog->move(this->geometry().topLeft()); //解决提取时取消提示框不居中显示
//        m_extractdialog->exec();
//    }
}

/**
 * @brief ProgressDialog::slotextractpress 是否取消提取
 * @param index
 */
void ProgressDialog::slotextractpress(int index)
{
    qDebug() << index;
    if (1 == index) { // 取消提取
        emit stopExtract();
        emit sigResetPercentAndTime();
    } else {
        exec();
    }
}
