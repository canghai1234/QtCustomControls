#ifndef CSTMROUNDEDBATTERY_H
#define CSTMROUNDEDBATTERY_H

/*
 * use the follow function to set the MAX value of the battery, default is 100.
 *  void setMaxValue(const qreal &maxValue);
 *
 * use the follow function to set the CURRENT value of the battery, default is 60.
 *  void setValue(const qreal &value);
 *
 * use the follow function to set the WARN value of the battery, default is 1/5 of the Max Value.While the CURRENT value is lower then
 * the WARN value ,the brush color of the battery will change .
 * void setWarnValue(const qreal &warnValue);
 *
 * Those functions are setting the color of the battery.  you can set the frame color , header color , battery color and warn color.
 * By default , the color of the frame and header are Black, the color of the battery is Green , the warn color is Red.
 * void setWarnValueColor(const QColor &warnValueColor);
 * void setBatteryColor(const QColor &batteryColor);
 * void setFrameColor(const QColor &frameColor);
 * void setHeaderColor(const QColor &headerColor);
 *
 * The follow function is to set if the color of the frame and header would change while the CURRENT value was lower than the WARN value.
 * Default is True.
 * void setFrameWidth(const qint32 &frameWidth);
 *
 * You can use the follow function to set the Radius of the round,Default is 20.
 * void setRoundRadius(const qreal x, const qreal y);
*/


#include <QWidget>
#include <QPointF>
#include <QRectF>
#include <QSize>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>

#define BETTERY_HEADER_WIDTH_RATIO (int)20
#define BETTERY_HEADER_HEIGHT_RATIO (int)2

class CstmRoundedBattery : public QWidget
{
Q_OBJECT
public:
    explicit CstmRoundedBattery(QWidget *parent = 0);

    qreal maxValue() const;
    void setMaxValue(const qreal &maxValue);

    qreal warnValue() const;
    void setWarnValue(const qreal &warnValue);

    qreal value() const;
    void setValue(const qreal &value);

    qint32 frameWidth() const;
    void setFrameWidth(const qint32 &frameWidth);

    QColor warnValueColor() const;
    void setWarnValueColor(const QColor &warnValueColor);

    QColor batteryColor() const;
    void setBatteryColor(const QColor &batteryColor);

    QColor frameColor() const;
    void setFrameColor(const QColor &frameColor);

    QColor headerColor() const;
    void setHeaderColor(const QColor &headerColor);

    void setWarnChgFrame(bool warnChgFrame);

    void setRoundRadius(const qreal x, const qreal y);
protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const
    {
        return QSize(200,120);
    }

private:
    void drawFrame(QPainter* painter);
    void drawBattery(QPainter* painter);
private:
    bool m_warnChgFrame;
    qreal m_warnValue;
    qreal m_maxValue;
    qreal m_currentValue;
    qint32 m_frameWidth;
    QColor m_warnValueColor;
    QColor m_batteryColor;
    QColor m_frameColor;
    QColor m_headerColor;
    qreal radiusX,radiusY;

    qreal m_headWidth;
    QRectF m_batteryRect;
};

#endif // CSTMROUNDEDBATTERY_H
