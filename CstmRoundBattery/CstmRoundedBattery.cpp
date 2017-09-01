#include "CstmRoundedBattery.h"

CstmRoundedBattery::CstmRoundedBattery(QWidget *parent) :
    QWidget(parent)
{
    m_currentValue=60;
    m_maxValue =100;
    m_warnValue = m_maxValue / 5;
    m_frameWidth = 5;
     m_warnValueColor = QColor("#FF0000");
     m_batteryColor = QColor("#00FF00");
     m_frameColor = QColor("#000000");
     m_headerColor = QColor("#000000");
     m_warnChgFrame = true;
     radiusX = 20;
     radiusY = 20;
}

void CstmRoundedBattery::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);//Indicates that the engine should antialias edges of primitives if possible.
    drawFrame(&painter);
    drawBattery(&painter);
    painter.end();
}
void CstmRoundedBattery::drawFrame(QPainter *painter)
{
    painter->save();
    //dream battery frame
    m_headWidth=this->width()/BETTERY_HEADER_WIDTH_RATIO;
    qreal batteryWidth = this->width() - m_headWidth;

    QPointF topLeftPoint(0,0);
    QPointF bottomRightPoint(batteryWidth,this->height());
    m_batteryRect=QRectF(topLeftPoint,bottomRightPoint);
    painter->setBrush(Qt::NoBrush);

    if((false != m_warnChgFrame) && (m_currentValue < m_warnValue))
        painter->setPen(QPen(m_warnValueColor,m_frameWidth));
    else
        painter->setPen(QPen(m_frameColor,m_frameWidth));  //battery frame color and width

    painter->drawRoundedRect(m_batteryRect,radiusX,radiusY,Qt::AbsoluteSize);

    //dream battery header
    QPointF headRectTopLeft(m_batteryRect.topRight().x(),height()/(2* BETTERY_HEADER_HEIGHT_RATIO));
    QPointF headRectBottomRight(width(),height()-height()/(2 * BETTERY_HEADER_HEIGHT_RATIO));
    QRectF headRect(headRectTopLeft,headRectBottomRight);
    QLinearGradient headRectGradient(headRect.topLeft(),headRect.bottomLeft());
    if((false != m_warnChgFrame) && (m_currentValue < m_warnValue))
    {
        headRectGradient.setColorAt(0.0,m_warnValueColor);
        headRectGradient.setColorAt(0.5,m_warnValueColor);
        headRectGradient.setColorAt(1.0,m_warnValueColor);
    }
    else
    {
        headRectGradient.setColorAt(0.0,m_headerColor);
        headRectGradient.setColorAt(0.5,m_headerColor);
        headRectGradient.setColorAt(1.0,m_headerColor);
    }
    painter->setBrush(headRectGradient);
    painter->drawRect(headRect);

    painter->restore();
}

void CstmRoundedBattery::drawBattery(QPainter *painter)
{
    painter->save();

    QLinearGradient batteryGradient(QPointF(0,0),QPointF(0,height()));

    if(m_currentValue < m_warnValue)
    {
        batteryGradient.setColorAt(0.0,m_warnValueColor);
        batteryGradient.setColorAt(0.5,m_warnValueColor);
        batteryGradient.setColorAt(1.0,m_warnValueColor);
    }
    else
    {
        batteryGradient.setColorAt(0.0,m_batteryColor);
        batteryGradient.setColorAt(0.5,m_batteryColor);
        batteryGradient.setColorAt(1.0,m_batteryColor);
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    QPointF topLeftPot(m_batteryRect.topLeft().x()+m_frameWidth,m_batteryRect.topLeft().y()+m_frameWidth);

    //
    qreal unit=(m_batteryRect.width()- 2 * m_frameWidth)/m_maxValue;
    qreal wid=m_currentValue * unit;
    QPointF bottomRightPot(topLeftPot.x()+wid, m_batteryRect.bottomRight().y()- m_frameWidth);

    painter->drawRoundedRect(QRectF(topLeftPot,bottomRightPot),radiusX,radiusY,Qt::AbsoluteSize);

    painter->restore();
}

void CstmRoundedBattery::setWarnChgFrame(bool warnChgFrame)
{
    m_warnChgFrame = warnChgFrame;
}

QColor CstmRoundedBattery::headerColor() const
{
    return m_headerColor;
}

void CstmRoundedBattery::setHeaderColor(const QColor &headerColor)
{
    m_headerColor = headerColor;
}

QColor CstmRoundedBattery::frameColor() const
{
    return m_frameColor;
}

void CstmRoundedBattery::setFrameColor(const QColor &frameColor)
{
    m_frameColor = frameColor;
}

QColor CstmRoundedBattery::batteryColor() const
{
    return m_batteryColor;
}

void CstmRoundedBattery::setBatteryColor(const QColor &batteryColor)
{
    m_batteryColor = batteryColor;
}

QColor CstmRoundedBattery::warnValueColor() const
{
    return m_warnValueColor;
}

void CstmRoundedBattery::setWarnValueColor(const QColor &warnValueColor)
{
    m_warnValueColor = warnValueColor;
}

qint32 CstmRoundedBattery::frameWidth() const
{
    return m_frameWidth;
}

void CstmRoundedBattery::setFrameWidth(const qint32 &frameWidth)
{
    m_frameWidth = frameWidth;
}

qreal CstmRoundedBattery::value() const
{
    return m_currentValue;
}

void CstmRoundedBattery::setValue(const qreal &value)
{
    if(value < 0)
        m_currentValue = 0;
    else if(value > m_maxValue)
        m_currentValue = m_maxValue;
    else
        m_currentValue = value;
}

qreal CstmRoundedBattery::warnValue() const
{
    return m_warnValue;
}

void CstmRoundedBattery::setWarnValue(const qreal &warnValue)
{
    if(warnValue <= 0)
        m_warnValue = 1;
    else if(warnValue > m_maxValue)
        m_warnValue = m_maxValue / 5;
    else
        m_warnValue = warnValue;
}

qreal CstmRoundedBattery::maxValue() const
{
    return m_maxValue;
}

void CstmRoundedBattery::setMaxValue(const qreal &maxValue)
{
    if(maxValue <= 0 )
        m_maxValue = 1;
    m_maxValue = maxValue;
    if(m_maxValue < m_warnValue)
        m_warnValue = m_maxValue / 5 ;
}

void CstmRoundedBattery::setRoundRadius(const qreal x, const qreal y)
{
    radiusX = x;
    radiusY = y;
}
