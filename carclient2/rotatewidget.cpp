#include "rotatewidget.h"
#include <QPropertyAnimation>

RotateWidget::RotateWidget(QWidget *parent)
    : QStackedWidget(parent)
    , m_isRoratingWindow(false)
    , m_nextPageIndex(0)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint| Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    // 给窗口设置rotateValue属性;
    this->setProperty("rotateValue", 0);
    initRotateWindow();
}

RotateWidget::~RotateWidget()
{

}



// 开始旋转窗口;
void RotateWidget::onRotateWindow()
{
    // 如果窗口正在旋转，直接返回;
    if (m_isRoratingWindow)
    {
        return;
    }
    m_isRoratingWindow = true;

    if(currentIndex()==0)
    {
        m_nextPageIndex =1;
    }else
    {
        m_nextPageIndex =0;
    }
    //m_nextPageIndex = (currentIndex() + 1) >= count() ? 0 : (currentIndex() + 1);
    QPropertyAnimation *rotateAnimation = new QPropertyAnimation(this, "rotateValue");
    // 设置旋转持续时间;
    rotateAnimation->setDuration(600);
    // 设置旋转角度变化趋势;
    rotateAnimation->setEasingCurve(QEasingCurve::InCubic);
    // 设置旋转角度范围;
    rotateAnimation->setStartValue(0);
    rotateAnimation->setEndValue(180);
    connect(rotateAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(repaint()));
    connect(rotateAnimation, SIGNAL(finished()), this, SLOT(onRotateFinished()));
    // 隐藏当前窗口，通过不同角度的绘制来达到旋转的效果;
    currentWidget()->hide();
    rotateAnimation->start();
}

// 旋转结束;
void RotateWidget::onRotateFinished()
{
    m_isRoratingWindow = false;
    setCurrentWidget(widget(m_nextPageIndex));
    repaint();
}

// 绘制旋转效果;
void RotateWidget::paintEvent(QPaintEvent* event)
{
    if (m_isRoratingWindow)
    {
        // 小于90度时;
        int rotateValue = this->property("rotateValue").toInt();
        if (rotateValue <= 90)
        {
            QPixmap rotatePixmap(currentWidget()->size());
            currentWidget()->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateValue, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, rotatePixmap);
        }
        // 大于90度时
        else
        {
            QPixmap rotatePixmap(widget(m_nextPageIndex)->size());
            widget(m_nextPageIndex)->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateValue + 180, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, rotatePixmap);
        }
    }
    else
    {
        //return __super::paintEvent(event);
    }
}
