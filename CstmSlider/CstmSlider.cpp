#include "CstmSlider.h"
#include <QDebug>

CstmSlider::CstmSlider(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(500,200);
    sliderHeight = 30 ;
    sliderColor = QColor(255,255,255,255);
    sliderBorderColor = QColor(0,0,0,255);
    sliderBorderWidth = 2;

    handleRadius = 20;
    handleColor = QColor(138,43,226,255);
    handleBorderColor = QColor(0,0,0,255);
    handleBorderWidth = 2;

    arrowColor = QColor(0,0,0,255);
    arrowWidth = 2;

    minValue = 0;
    maxValue = 100;
    currentValue = 20;
    valueColor = QColor(68,178,255,255);
    isIncrease = true;
    handleIsPress = false;

    widgetWidth = this->width();
    centerPointerX = ((this->width() - 2.0 * handleRadius) / (maxValue - minValue)) * ( currentValue - minValue) + handleRadius ;
}

CstmSlider::~CstmSlider()
{

}

void CstmSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    midPos = this->height()/2;
    if(widgetWidth != this->width())
        centerPointerX = ((this->width() - 2.0 * handleRadius) / (maxValue - minValue)) * ( currentValue - minValue) + handleRadius ;

    QPainter painter(this);
    drawSlider(&painter);
    drawValue(&painter);
    drawHander(&painter);
    drawArrow(&painter);
}

void CstmSlider::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mousePressPoint = mapFromGlobal(QCursor::pos());

    if ((mousePressPoint.x()>=(centerPointerX - handleRadius ))&&(mousePressPoint.x() <= (centerPointerX +handleRadius)))
    {
        if ((mousePressPoint.y()>=(midPos - handleRadius ))&&(mousePressPoint.y() <= (midPos +handleRadius)))
            handleIsPress = true;
    }
}

void CstmSlider::mouseMoveEvent(QMouseEvent *event)
{
    QPointF point = event->pos();
    if(true == handleIsPress)
        if (point.x()>=(centerPointerX - handleRadius)&& point.x()<=(centerPointerX + handleRadius))
        {
            qreal direction = point.x() - mousePressPoint.x() ;
            if(direction >= 0)
                isIncrease = true;
            else
                isIncrease = false;

            centerPointerX = centerPointerX + direction; //calculate the X coordinate of Handle
            mousePressPoint = point;
            if(centerPointerX < handleRadius )  //the Handle can not slide out of the slider range
            {

                centerPointerX = handleRadius;
                mousePressPoint.setX(centerPointerX );
            }
            else if( centerPointerX > (this->width() - handleRadius) )
            {
                centerPointerX = this->width() - handleRadius;
                mousePressPoint.setX(centerPointerX );
            }
            currentValue = ((centerPointerX - handleRadius)/(this->width() - 2.0* handleRadius))*(maxValue - minValue) + minValue ;
            emit signal_valueChanged(currentValue);
        }
    this->update();
}

void CstmSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    handleIsPress = false;
    this->update();
}

void CstmSlider::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(sliderBorderColor,sliderBorderWidth));
    painter->setBrush(sliderColor);
    painter->setRenderHint(QPainter::Antialiasing);
    QRect rect(0,(midPos - sliderHeight/2),this->width() , sliderHeight);
    painter->drawRoundedRect(rect,sliderHeight/2,sliderHeight/2,Qt::AbsoluteSize);

    painter->restore();
}

void CstmSlider::drawHander(QPainter *painter)
{
    painter->save();

    painter->setPen(QPen(handleBorderColor,handleBorderWidth));
    painter->setBrush(handleColor);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(QPoint(centerPointerX,midPos) , handleRadius,handleRadius);

    painter->restore();
}

void CstmSlider::drawArrow(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(arrowColor,arrowWidth));
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    if(false != isIncrease)
    {
        path.moveTo(centerPointerX - handleRadius/4.0  ,midPos - handleRadius/2.0);
        path.lineTo(centerPointerX + handleRadius/4.0 ,midPos);
        path.lineTo(centerPointerX - handleRadius/4.0  , midPos + handleRadius/2.0);
    }
    else
    {
        path.moveTo(centerPointerX + handleRadius/4.0  ,midPos - handleRadius/2.0);
        path.lineTo(centerPointerX - handleRadius/4.0 ,midPos);
        path.lineTo(centerPointerX + handleRadius/4.0  , midPos + handleRadius/2.0);
    }
    painter->drawPath(path);
    painter->restore();
}

void CstmSlider::drawValue(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(sliderBorderColor,sliderBorderWidth));
    painter->setBrush(valueColor);
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.moveTo(sliderHeight/2  + sliderBorderWidth ,midPos -sliderHeight/2 );
    path.lineTo(centerPointerX,midPos -sliderHeight/2);
    path.lineTo(centerPointerX,midPos + sliderHeight/2);
    path.lineTo(sliderHeight/2+ sliderBorderWidth,midPos  + sliderHeight/2 );
    path.arcTo(0,midPos -sliderHeight/2 ,sliderHeight,sliderHeight,-90,-180);

    painter->drawPath(path);
    painter->restore();
}

void CstmSlider::setValueColor(const QColor &value)
{
    valueColor = value;
}

void CstmSlider::setArrowWidth(int value)
{
    arrowWidth = value;
    if(arrowWidth > handleRadius - handleBorderWidth)
        arrowWidth =  handleRadius - handleBorderWidth ;
    else if(arrowWidth < 0)
        arrowWidth = 0;
}

void CstmSlider::setArrowColor(const QColor &value)
{
    arrowColor = value;
}

void CstmSlider::setSliderColor(const QColor &value)
{
    sliderColor = value;
}

void CstmSlider::setHandleBorderWidth(int value)
{
    handleBorderWidth = value;
    if(handleBorderWidth > handleRadius)
        handleBorderWidth = handleRadius;
}

void CstmSlider::setHandleBorderColor(const QColor &value)
{
    handleBorderColor = value;
}

void CstmSlider::setHandleColor(const QColor &value)
{
    handleColor = value;
}

void CstmSlider::setHandleRadius(int value)
{
    handleRadius = value;
    if(handleRadius >this->height() )
        handleRadius = this->height();
}

void CstmSlider::setCurrentValue(int value)
{
    currentValue = value;
    if(currentValue > maxValue)
        currentValue = maxValue;
    else if(currentValue < minValue)
        currentValue = minValue;
}

void CstmSlider::setMaxValue(int value)
{
    maxValue = value;
    if(maxValue < minValue)
        maxValue = minValue;
    if(currentValue > maxValue)
        currentValue = maxValue;
}

void CstmSlider::setMinValue(int value)
{
    minValue = value;
    if(minValue > maxValue)
        minValue = maxValue;
    if(currentValue < minValue)
        currentValue = minValue;
}

void CstmSlider::setSliderBorderWidth(int value)
{
    sliderBorderWidth = value;
    if(sliderBorderWidth >sliderHeight/2 )
        sliderBorderWidth = sliderHeight/2;
}

void CstmSlider::setSliderBorderColor(const QColor &value)
{
    sliderBorderColor = value;
}

void CstmSlider::setSliderHeight(int value)
{
    sliderHeight = value;
    if(sliderHeight > this->height())
    {
        sliderHeight = this->height();
    }
}
