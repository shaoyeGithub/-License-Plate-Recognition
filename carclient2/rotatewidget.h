#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include "login.h"
#include <QStackedWidget>
#include <QPropertyAnimation>
class RotateWidget : public QStackedWidget
{
    Q_OBJECT

public:
    RotateWidget(QWidget *parent = NULL);
    ~RotateWidget();

private:

    // 绘制旋转效果;
    void paintEvent(QPaintEvent* event);

private slots:
    // 开始旋转窗口;
    void onRotateWindow();
    // 窗口旋转结束;
    void onRotateFinished();

private:
    // 当前窗口是否正在旋转;
    bool m_isRoratingWindow;



    int m_nextPageIndex;
};

#endif // ROTATEWIDGET_H
