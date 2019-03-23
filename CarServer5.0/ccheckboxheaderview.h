#ifndef CCHECKBOXHEADERVIEW
#define CCHECKBOXHEADERVIEW
#include <QtGui>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>

class CCheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    CCheckBoxHeaderView( int checkColumnIndex,
             Qt::Orientation orientation,
             QWidget * parent = 0) :
    QHeaderView(orientation, parent)
    {
        m_checkColIdx = checkColumnIndex;
        isChecked = false;
    }
    bool isChecked;
signals:
    void checkStausChange(bool);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
    {
        painter->save();
        QHeaderView::paintSection(painter, rect, logicalIndex);
        painter->restore();
        if (logicalIndex == m_checkColIdx)
        {
            QStyleOptionButton option;
            int width = 10;
            for (int i=0; i<logicalIndex; ++i)
            width += sectionSize( i );
            option.rect = QRect(3, 5, 21, 21);
            if (isChecked)
                option.state = QStyle::State_On;
            else
                option.state = QStyle::State_Off;
    //        this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
            this->style()->drawControl(QStyle::CE_CheckBox, &option, painter);
        }

    }
    void mousePressEvent(QMouseEvent *event)
    {
        if (visualIndexAt(event->pos().x()) == m_checkColIdx)
        {
            if (isChecked)
                isChecked = false;
            else
                isChecked = true;
            this->updateSection(m_checkColIdx);
            emit checkStausChange(isChecked);
        }

        QHeaderView::mousePressEvent(event);
    }

private:

    int m_checkColIdx;
};
#endif // CCHECKBOXHEADERVIEW

