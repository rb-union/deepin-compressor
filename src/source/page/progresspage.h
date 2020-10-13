/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     gaoxiang <gaoxiang@uniontech.com>
*
* Maintainer: gaoxiang <gaoxiang@uniontech.com>
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

#ifndef PROGRESSPAGE_H
#define PROGRESSPAGE_H

#include "uistruct.h"

#include <DWidget>
#include <DLabel>
#include <DProgressBar>
#include <DSuggestButton>

DWIDGET_USE_NAMESPACE

// 进度界面
class ProgressPage : public DWidget
{
public:
    explicit ProgressPage(QWidget *parent = nullptr);
    ~ProgressPage() override;

    /**
     * @brief setProgressType   设置进度类型
     * @param eType 类型
     */
    void setProgressType(Progress_Type eType);

    /**
     * @brief setArchiveName    设置压缩包名称和文件总大小
     * @param strArchiveName    压缩包名称
     * @param qTotalSize    总大小
     */
    void setArchiveName(const QString &strArchiveName, qint64 qTotalSize);

    /**
     * @brief setProgress   设置当前进度
     * @param iPercent  进度值
     */
    void setProgress(int iPercent);

    /**
     * @brief setCurrentFileName    设置当前文件名
     * @param strFileName   文件名
     */
    void setCurrentFileName(const QString &strFileName);


private:
    /**
     * @brief initUI    初始化界面
     */
    void initUI();

    /**
     * @brief initConnections   初始化信号槽
     */
    void initConnections();

    /**
     * @brief refreshSpeedAndRemainingTime  刷新速度和剩余时间大小
     */
    void refreshSpeedAndRemainingTime();

private:
    DLabel *m_pPixmapLbl;       // 类型图片
    DLabel *m_pArchiveNameLbl;  // 压缩包名称
    DProgressBar *m_pProgressBar;   // 进度条
    DLabel *m_pFileNameLbl;     // 文件名称
    DLabel *m_pSpeedLbl;        // 速度
    DLabel *m_pRemainingTimeLbl;    // 剩余时间
    DPushButton *m_pCancelBtn;      // 取消按钮
    DSuggestButton *m_pPauseContinueButton; // 暂停继续按钮

    Progress_Type m_eType;      // 进度类型
    qint64 m_qTotalSize;         // 文件大小
    int m_iPerent;      // 进度值
};

#endif // COMPRESSPAGE_H
