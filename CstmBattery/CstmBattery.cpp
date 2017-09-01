#include "CstmBattery.h"

CstmBattery::CstmBattery(QWidget *parent) :
    QWidget(parent)
{
    m_currentValue=10;
    m_maxValue =100;
    m_warnValue = m_maxValue / 5;
    m_frameWidth = 5;
     m_warnValueColor = QColor("#FF0000");
     m_batteryColor = QColor("#00FF00");
     m_frameColor = QColor("#000000");
     m_headerColor = QColor("#000000");
     m_warnChgFrame = true;
}

void CstmBattery::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);//Indicates that the engine should antialias edges of primitives if possible.
    drawFrame(&painter);
    drawBattery(&painter);
    painter.end();
}
void CstmBattery::drawFrame(QPainter *painter)
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

    painter->drawRect(m_batteryRect);

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

void CstmBattery::drawBattery(QPainter *painter)
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
    qreal unit=m_batteryRect.width()/m_maxValue;
    qreal wid=m_currentValue*unit;
    QPointF bottomRightPot(wid,m_batteryRect.bottomRight().y()- m_frameWidth);
    painter->drawRect(QRectF(topLeftPot,bottomRightPot));

    painter->restore();
}

void CstmBattery::setWarnChgFrame(bool warnChgFrame)
{
    m_warnChgFrame = warnChgFrame;
}

QColor CstmBattery::headerColor() const
{
    return m_headerColor;
}

void CstmBattery::setHeaderColor(const QColor &headerColor)
{
    m_headerColor = headerColor;
}

QColor CstmBattery::frameColor() const
{
    return m_frameColor;
}

void CstmBattery::setFrameColor(const QColor &frameColor)
{
    m_frameColor = frameColor;
}

QColor CstmBattery::batteryColor() const
{
    return m_batteryColor;
}

void CstmBattery::setBatteryColor(const QColor &batteryColor)
{
    m_batteryColor = batteryColor;
}

QColor CstmBattery::warnValueColor() const
{
    return m_warnValueColor;
}

void CstmBattery::setWarnValueColor(const QColor &warnValueColor)
{
    m_warnValueColor = warnValueColor;
}

qint32 CstmBattery::frameWidth() const
{
    return m_frameWidth;
}

void CstmBattery::setFrameWidth(const qint32 &frameWidth)
{
    m_frameWidth = frameWidth;
}

qreal CstmBattery::value() const
{
    return m_currentValue;
}

void CstmBattery::setValue(const qreal &value)
{
    if(value < 0)
        m_currentValue = 0;
    else if(value > m_maxValue)
        m_currentValue = m_maxValue;
    else
        m_currentValue = value;
}

qreal CstmBattery::warnValue() const
{
    return m_warnValue;
}

void CstmBattery::setWarnValue(const qreal &warnValue)
{
    if(warnValue <= 0)
        m_warnValue = 1;
    else if(warnValue > m_maxValue)
        m_warnValue = m_maxValue / 5;
    else
        m_warnValue = warnValue;
}

qreal CstmBattery::maxValue() const
{
    return m_maxValue;
}

void CstmBattery::setMaxValue(const qreal &maxValue)
{
    if(maxValue <= 0 )
        m_maxValue = 1;
    m_maxValue = maxValue;
    if(m_maxValue < m_warnValue)
        m_warnValue = m_maxValue / 5 ;
}
