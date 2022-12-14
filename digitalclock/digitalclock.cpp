/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "digitalclock.h"

#include <QTime>
#include <QTimer>


DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint |Qt::Tool | Qt::X11BypassWindowManagerHint);//?????????/??????/????????????
    setAttribute(Qt::WA_TranslucentBackground);//????????????

    setSegmentStyle(Filled);//???????????????
    setStyleSheet("background:transparent;color:#00ccff;"); //???????????? ???????????????
    setDigitCount(8); //????????????
    setMode(QLCDNumber::Dec); //???????????????
    resize(300,120);//????????????  ??????????????????????????????
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);
    showTime();

    //    setWindowTitle(tr("Digital Clock"));


}

//#include <QDebug>
void DigitalClock::showTime()

{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    //    qDebug()<<text;
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    display(text);
}
void DigitalClock::mousePressEvent(QMouseEvent *e)
{
    //????????????
    this->setFocus();
    if(Qt::LeftButton == e->button() && 0 == (Qt::WindowMaximized & this->windowState()))
    {
        QPoint temp=e->globalPos();
        pLast=temp;    //???????????????????????????
        e->ignore();
    }
    m_bPressed = true; //???????????????????????????
    if(Qt::RightButton == e->button() )
    {
        int ret = QMessageBox::question(this,  "??????",  "?????????????????????????????????",
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
      if(ret == QMessageBox::Yes)
       {
//          this->close();
          QApplication::exit(0);
       }
      else {

      }
    }

}

void DigitalClock::mouseMoveEvent(QMouseEvent *e)
{
    if(this->isMaximized()) //?????????????????????????????????????????????
        return;

    if((e->buttons() & Qt::LeftButton) && m_bPressed)//????????????
    {
        QPoint ptemp=e->globalPos();              //????????????????????????
/*        ptemp=ptemp-pLast;                        //??????????????????
        ptemp=ptemp+pos(); */                       //?????????????????????pos()??? + ?????????????????????ptemp??? = ??????????????????
        move(ptemp);                              //???????????????????????????
    }

}

void DigitalClock::mouseReleaseEvent(QMouseEvent *e)
{
    QApplication::restoreOverrideCursor();//????????????????????????
    e->ignore();
    m_bPressed = false;
}

