#ifndef CSTMCHUNKBATTERY_H
#define CSTMCHUNKBATTERY_H

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
 *
 * The function is setting the count of the chunk,default is 5, the min value is 1.The value can not  be lower than 1.
 * void setChunkCount(const qint32 &chunkCount);
 *
 * The function is setting the ration of the chunk and the space between the chunks,default is 5 ,if the value lower than 1, the value will chage to 1.
 * void setChunkRatio(const qreal &chunkRatio);
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

class CstmChunkBattery : public QWidget
{
Q_OBJECT
public:
    explicit CstmChunkBattery(QWidget *parent = 0);

    void setMaxValue(const qreal &maxValue);

    void setWarnValue(const qreal &warnValue);

    void setValue(const qreal &value);

    void setFrameWidth(const qint32 &frameWidth);

    void setWarnValueColor(const QColor &warnValueColor);

    void setBatteryColor(const QColor &batteryColor);

    void setFrameColor(const QColor &frameColor);

    void setHeaderColor(const QColor &headerColor);

    void setWarnChgFrame(bool warnChgFrame);

    void setRoundRadius(const qreal x, const qreal y);

    void setChunkCount(const qint32 &chunkCount);

    void setChunkRatio(const qreal &chunkRatio);

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
    qint32 m_chunkCount;
    qreal m_chunkRatio;
    QColor m_warnValueColor;
    QColor m_batteryColor;
    QColor m_frameColor;
    QColor m_headerColor;
    qreal radiusX,radiusY;

    qreal m_headWidth;
    QRectF m_batteryRect;
};

#endif //CSTMCHUNKBATTERY_H
