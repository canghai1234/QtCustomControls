#include "CstmChunkBattery.h"

CstmChunkBattery::CstmChunkBattery(QWidget *parent) :
    QWidget(parent)
{
    m_currentValue=79;
    m_maxValue =100;
    m_warnValue = m_maxValue / 5;
    m_frameWidth = 5;
    m_chunkCount = 5;
    m_chunkRatio = 5.0;
    m_warnValueColor = QColor("#FF0000");
    m_batteryColor = QColor("#00FF00");
    m_frameColor = QColor("#000000");
    m_headerColor = QColor("#000000");
    m_warnChgFrame = true;
    radiusX = 20.0;
    radiusY = 20.0;
}

void CstmChunkBattery::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);//Indicates that the engine should antialias edges of primitives if possible.
    drawFrame(&painter);
    drawBattery(&painter);
    painter.end();
}
void CstmChunkBattery::drawFrame(QPainter *painter)
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

void CstmChunkBattery::drawBattery(QPainter *painter)
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

    qreal unit = (m_batteryRect.width()- 2 * m_frameWidth) /(m_chunkRatio * m_chunkCount + m_chunkCount - 1) ;
    qreal chunWid = unit * m_chunkRatio;

    qreal  eachChunkValue =  m_maxValue / m_chunkCount;
    int showChunkCount = m_currentValue /eachChunkValue + 1;
    if(showChunkCount >m_chunkCount )
        showChunkCount = m_chunkCount;
    QPointF chunkTopLeftPoint = topLeftPot;
    for(int i = 0;i < showChunkCount;++i )
    {
        QPointF bottomRightPot(chunkTopLeftPoint.x()+chunWid, m_batteryRect.bottomRight().y()- m_frameWidth);
        painter->drawRoundedRect(QRectF(chunkTopLeftPoint,bottomRightPot),radiusX,radiusY,Qt::AbsoluteSize);
        chunkTopLeftPoint.setX(bottomRightPot.x() + unit);
    }

    painter->restore();
}

void CstmChunkBattery::setChunkRatio(const qreal &chunkRatio)
{
    if(chunkRatio < 1)
        m_chunkRatio = 1;
    else
        m_chunkRatio = chunkRatio;
}

void CstmChunkBattery::setChunkCount(const qint32 &chunkCount)
{
    if(chunkCount < 1)
        m_chunkCount = 1;
    else
        m_chunkCount = chunkCount;
}

void CstmChunkBattery::setWarnChgFrame(bool warnChgFrame)
{
    m_warnChgFrame = warnChgFrame;
}

void CstmChunkBattery::setHeaderColor(const QColor &headerColor)
{
    m_headerColor = headerColor;
}

void CstmChunkBattery::setFrameColor(const QColor &frameColor)
{
    m_frameColor = frameColor;
}

void CstmChunkBattery::setBatteryColor(const QColor &batteryColor)
{
    m_batteryColor = batteryColor;
}


void CstmChunkBattery::setWarnValueColor(const QColor &warnValueColor)
{
    m_warnValueColor = warnValueColor;
}


void CstmChunkBattery::setFrameWidth(const qint32 &frameWidth)
{
    if(m_frameWidth < 0 )
        m_frameWidth = 0;
    else
        m_frameWidth = frameWidth;
}


void CstmChunkBattery::setValue(const qreal &value)
{
    if(value < 0)
        m_currentValue = 0;
    else if(value > m_maxValue)
        m_currentValue = m_maxValue;
    else
        m_currentValue = value;
}

void CstmChunkBattery::setWarnValue(const qreal &warnValue)
{
    if(warnValue <= 0)
        m_warnValue = 1;
    else if(warnValue > m_maxValue)
        m_warnValue = m_maxValue / 5;
    else
        m_warnValue = warnValue;
}


void CstmChunkBattery::setMaxValue(const qreal &maxValue)
{
    if(maxValue <= 0 )
        m_maxValue = 1;
    m_maxValue = maxValue;
    if(m_maxValue < m_warnValue)
        m_warnValue = m_maxValue / 5 ;
}

void CstmChunkBattery::setRoundRadius(const qreal x, const qreal y)
{
    if (x < 0)
        radiusX = 0;
    else
        radiusX = x;
    if (y < 0)
        radiusY = 0;
    else
        radiusY = y;
}
