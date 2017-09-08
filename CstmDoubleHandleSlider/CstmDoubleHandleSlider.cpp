#include "CstmDoubleHandleSlider.h"
#include <QDebug>

CstmDoubleHandleSlider::CstmDoubleHandleSlider(QWidget *parent)
    : QWidget(parent)
{

    isHorizontal = true; // set the slider is Horizontal or Vertical

    borderWidth = 5;
    borderColor = QColor("#000000");
    midSelectedColor = QColor("#FFFFF0");
    midColor = QColor("#FFFF00");
    sliderColor = QColor("#FF0000");
    sliderThickness = 50;

    maxValue = 100;
    minValue = 0;
    hand1Value = 20;
    hand2Value = 80;

    hand1_Color = QColor("#00FF00");
    hand2_Color = QColor("#0000FF");

    hand1SelectedColor = QColor("#009900");
    hand2SelectedColor = QColor("#000099");

    hand1BorderColor = hand2BorderColor = borderColor;
    hand1BorderWidth = hand2BorderWidth = borderWidth;

    hand1Height = hand2Height = 2* sliderThickness;
    hand1Width = hand2Width = 2* sliderThickness;

    hand1Style = hand2Style = SliderStyle_Circle;

    if(true != isHorizontal)
    {
        sliderLength = this->height() - hand1Height/2 - hand2Height/2;

        hand1_X = this->width()/2;
        hand1_Y = hand1Height/2 + (hand1Value - minValue)/(maxValue - minValue)* sliderLength;
        hand2_X = hand1_X;
        hand2_Y = this->height() - hand2Height/2 - (maxValue - hand2Value)/(maxValue - minValue)*sliderLength;
    }
    else
    {
        sliderLength = this->width() - hand1Width/2 - hand2Width/2;

        hand1_X = hand1Width/2 + (hand1Value - minValue)/(maxValue - minValue)* sliderLength;
        hand1_Y = this->height()/2;
        hand2_X = this->width() - hand2Width/2 -(maxValue - hand2Value)/(maxValue - minValue)*sliderLength;
        hand2_Y = hand1_Y;
    }
    handle1Seleced = false;
    handle2Seleced = false;
    handleBothSeleced = false;
}

CstmDoubleHandleSlider::~CstmDoubleHandleSlider()
{

}

void CstmDoubleHandleSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    updateValue();
    QPainter painter(this);
    drawSlider(&painter); //draw the slider
    drawSelect(&painter); //draw the slidet between two handles
    drawHandle1(&painter); //draw the handle on top/left
    drawHandle2(&painter); //draw the handle on bottom/right
}

void CstmDoubleHandleSlider::mousePressEvent( QMouseEvent *event )
{
    Q_UNUSED(event)
    mousePressPoint = mapFromGlobal(QCursor::pos());
    if(true !=isHorizontal) //the slider is Vertical
    {
        if (mousePressPoint.y()>=(hand1_Y - hand1Height/2)&& mousePressPoint.y()<=(hand1_Y + hand1Height/2))
            handle1Seleced = true;
        else if (mousePressPoint.y()>=(hand2_Y - hand2Height/2)&&mousePressPoint.y()<=(hand2_Y + hand2Height/2))
            handle2Seleced = true;
        else if (mousePressPoint.y()>(hand1_Y + hand1Height/2)&&mousePressPoint.y()<(hand2_Y - hand2Height/2))
            handleBothSeleced = true;
    }
    else //the slider is Horizontal
    {
        if (mousePressPoint.x()>=(hand1_X - hand1Width/2)&& mousePressPoint.x()<=(hand1_X + hand1Width/2))
            handle1Seleced = true;
        else if (mousePressPoint.x()>=(hand2_X - hand2Width/2)&&mousePressPoint.x()<=(hand2_X + hand2Width/2))
            handle2Seleced = true;
        else if (mousePressPoint.x()>(hand1_X + hand1Width/2)&&mousePressPoint.x()<(hand2_X - hand2Width/2))
            handleBothSeleced = true;
    }
    update();
}

void CstmDoubleHandleSlider::mouseMoveEvent( QMouseEvent *event )
{
    Q_UNUSED(event)
    QPointF point = event->pos();

    if(true !=isHorizontal) //the slider is Vertical
    {
        if (handle1Seleced)
        {
            if (point.y()>=(hand1_Y - hand1Height/2)&& point.y()<=(hand1_Y + hand1Height/2))
            {
                hand1_Y = hand1_Y +  (point.y() - mousePressPoint.y()); //calculate the Y coordinate of Hand1

                mousePressPoint = point;
                if(hand1_Y < sliderTopLeft_Y )  //the handle1 can not slide out of the slider range
                {
                    hand1_Y = sliderTopLeft_Y;
                    mousePressPoint.setY(hand1_Y );
                }
                else if( hand1_Y > hand2_Y ) //the handle1 can not be setted  on the bottom of the handle2
                {
                    hand1_Y = hand2_Y;
                    mousePressPoint.setY(hand1_Y );
                }

                hand1Value = (hand1_Y - sliderTopLeft_Y)/sliderLength*(maxValue - minValue) + minValue ;
                emit signal_hand1ValueChanged(hand1Value);
            }
        }else if (handle2Seleced)
        {
            if  (point.y()>=(hand2_Y - hand2Height/2)&&point.y()<=(hand2_Y + hand2Height/2))
            {
                hand2_Y = hand2_Y -  (mousePressPoint.y() - point.y());

                mousePressPoint = point;
                if(hand2_Y < hand1_Y ) //the handle2 can not slide out of the slider range
                {
                    hand2_Y = hand1_Y;
                    mousePressPoint.setY(hand2_Y );
                }
                else if( hand2_Y > sliderTopLeft_Y + sliderLength ) //the handle2 can not be setted  on the top of the handle1
                {
                    hand2_Y =  sliderTopLeft_Y + sliderLength;
                    mousePressPoint.setY(hand2_Y );
                }

                hand2Value = maxValue - (sliderTopLeft_Y + sliderLength - hand2_Y)/sliderLength*(maxValue - minValue) ;
                emit signal_hand2ValueChanged(hand2Value);
            }
        }else if(handleBothSeleced)
        {
            if (point.y()>(hand1_Y + hand1Height/2)&&point.y()<(hand2_Y - hand2Height/2))
            {
                qreal tmpHand1Y = hand1_Y;
                qreal tmpHand2Y = hand2_Y;
                hand1_Y = hand1_Y +  (point.y() - mousePressPoint.y());
                hand2_Y = hand2_Y -  (mousePressPoint.y() - point.y());

                if(hand1_Y < sliderTopLeft_Y ) //the handle1 can not slide out of the slider range
                {
                    hand1_Y = sliderTopLeft_Y;
                    hand2_Y = tmpHand2Y;
                }
                else if( hand2_Y > sliderTopLeft_Y + sliderLength ) //the handle2 can not slide out of the slider range
                {
                    hand2_Y =  sliderTopLeft_Y + sliderLength;
                    hand1_Y = tmpHand1Y;
                }
                mousePressPoint = point;

                hand1Value = (hand1_Y - sliderTopLeft_Y)/sliderLength*(maxValue - minValue) + minValue ;
                hand2Value =maxValue - (sliderTopLeft_Y + sliderLength - hand2_Y)/sliderLength*(maxValue - minValue) ;
                emit signal_hand1ValueChanged(hand1Value);
                emit signal_hand2ValueChanged(hand2Value);
            }
        }
    }
    else //the slider is Horizontal
    {
        if (handle1Seleced)
        {
            if (point.x()>=(hand1_X - hand1Width/2)&& point.x()<=(hand1_X + hand1Width/2))
            {
                hand1_X = hand1_X +  (point.x() - mousePressPoint.x());

                mousePressPoint = point;
                if(hand1_X < sliderTopLeft_X ) //the handle1 can not slide out of the slider range
                {
                    hand1_X = sliderTopLeft_X;
                    mousePressPoint.setX(hand1_X );
                }
                else if( hand1_X > hand2_X )  //the handle1 can not be setted  on the right of the handle2
                {
                    hand1_X = hand2_X;
                    mousePressPoint.setX(hand1_X );
                }

                hand1Value = (hand1_X - sliderTopLeft_X)/sliderLength*(maxValue - minValue) + minValue ;
                emit signal_hand1ValueChanged(hand1Value);
            }
        }else if (handle2Seleced)
        {
            if (point.x()>=(hand2_X - hand2Width/2)&&point.x()<=(hand2_X + hand2Width/2))
            {
                hand2_X = hand2_X -  (mousePressPoint.x() - point.x());

                mousePressPoint = point;
                if(hand2_X < hand1_X )//the handle2 can not be setted  on the left of the handle1
                {
                    hand2_X = hand1_X;
                    mousePressPoint.setX(hand2_X );
                }
                else if( hand2_X > sliderTopLeft_X + sliderLength ) //the handle2 can not slide out of the slider range
                {
                    hand2_X =  sliderTopLeft_X + sliderLength;
                    mousePressPoint.setX(hand2_X );
                }

                hand2Value = maxValue - (sliderTopLeft_X + sliderLength - hand2_X)/sliderLength*(maxValue - minValue) ;
                emit signal_hand2ValueChanged(hand2Value);
            }
        }else  if(handleBothSeleced)
        {
            if (point.x()>(hand1_X + hand1Width/2)&&point.x()<(hand2_X - hand2Width/2))
            {
                qreal tmpHand1X = hand1_X;
                qreal tmpHand2X = hand2_X;
                hand1_X = hand1_X +  (point.x() - mousePressPoint.x());
                hand2_X = hand2_X -  (mousePressPoint.x() - point.x());

                if(hand1_X < sliderTopLeft_X ) //the handle1 can not slide out of the slider range
                {
                    hand1_X = sliderTopLeft_X;
                    hand2_X = tmpHand2X;
                }
                else if( hand2_X > sliderTopLeft_X + sliderLength ) //the handle2 can not slide out of the slider range
                {
                    hand2_X =  sliderTopLeft_X + sliderLength;
                    hand1_X = tmpHand1X;
                }
                mousePressPoint = point;

                hand1Value = (hand1_X - sliderTopLeft_X)/sliderLength*(maxValue - minValue) + minValue ;
                hand2Value = maxValue - (sliderTopLeft_X + sliderLength - hand2_X)/sliderLength*(maxValue - minValue) ;
                emit signal_hand1ValueChanged(hand1Value);
                emit signal_hand2ValueChanged(hand2Value);
            }
        }
    }
    update();
}

void CstmDoubleHandleSlider::mouseReleaseEvent( QMouseEvent *event )
{
    Q_UNUSED(event)
    handle1Seleced=false;
    handle2Seleced=false;
    handleBothSeleced = false;
    update();
}

void CstmDoubleHandleSlider::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setBrush(sliderColor);
    painter->setPen(QPen(borderColor,borderWidth,Qt::SolidLine,Qt::RoundCap));
    QRect sliderRect;
    if(true != isHorizontal)  //vertical
    {
        sliderTopLeft_X = (this->width() - sliderThickness) / 2 ;
        sliderTopLeft_Y = hand1Width /2 ;
        sliderRect.setRect(sliderTopLeft_X,sliderTopLeft_Y,sliderThickness,sliderLength);
    }
    else
    {
        sliderTopLeft_X =hand1Width/2;
        sliderTopLeft_Y = this->height() / 2 - sliderThickness/2 ;
        sliderRect.setRect(sliderTopLeft_X,sliderTopLeft_Y, sliderLength, sliderThickness);
    }
    painter->drawRect(sliderRect);
    painter->restore();
}

void CstmDoubleHandleSlider::drawSelect(QPainter *painter)
{
    painter->save();
    if ( false != handleBothSeleced)
    {
        painter->setBrush(midSelectedColor);
        painter->setPen(QPen(borderColor,borderWidth,Qt::SolidLine,Qt::RoundCap));
    }
    else
    {
        painter->setBrush(midColor);
        painter->setPen(QPen(borderColor,borderWidth,Qt::SolidLine,Qt::RoundCap));
    }
    QRect selectRect;
    if(true != isHorizontal)  //vertical
    {
        selectRect.setRect(hand1_X - sliderThickness/2 ,hand1_Y,sliderThickness,hand2_Y - hand1_Y);
    }
    else
    {
        selectRect.setRect(hand1_X,hand1_Y - sliderThickness/2, hand2_X - hand1_X, sliderThickness);
    }
    painter->drawRect(selectRect);
    painter->restore();
}

void CstmDoubleHandleSlider::drawHandle1(QPainter *painter)
{
    painter->save();
    if ( false != handle1Seleced)
    {
        painter->setBrush(hand1SelectedColor);
        painter->setPen(QPen(Qt::blue,1,Qt::SolidLine,Qt::RoundCap));
    }
    else
    {
        painter->setBrush(hand1_Color);
        painter->setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
    }

    if (hand1Style == SliderStyle_Rect) {
        painter->drawRect(hand1_X - hand1Width/2 , hand1_Y - hand1Height/2, hand1Width, hand1Height);
    } else if (hand1Style == SliderStyle_Circle) {
        painter->drawEllipse(QPoint(hand1_X,hand1_Y),hand1Height/2,hand1Height/2);
    } else if (hand1Style == SliderStyle_Ellipse) {
        painter->drawEllipse(QPoint(hand1_X,hand1_Y),hand1Width/2,hand1Height/2);
    }
    painter->restore();
}

void CstmDoubleHandleSlider::drawHandle2(QPainter *painter)
{
    painter->save();
    if (false != handle2Seleced)
    {
        painter->setBrush(hand2SelectedColor);
        painter->setPen(QPen(Qt::blue,1,Qt::SolidLine,Qt::RoundCap));
    }
    else
    {
        painter->setBrush(hand2_Color);
        painter->setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
    }

    if (hand2Style == SliderStyle_Rect) {
        painter->drawRect(hand2_X - hand2Width/2 , hand2_Y - hand2Height/2, hand2Width, hand2Height);
    } else if (hand2Style == SliderStyle_Circle) {
        painter->drawEllipse(QPoint(hand2_X,hand2_Y),hand2Height/2,hand2Height/2);
    } else if (hand2Style == SliderStyle_Ellipse) {
        painter->drawEllipse(QPoint(hand2_X,hand2_Y),hand2Width/2,hand2Height/2);
    }
    painter->restore();
}

void CstmDoubleHandleSlider::setHand1SelectedColor(const QColor &value)
{
    hand1SelectedColor = value;
}

void CstmDoubleHandleSlider::setHand2SelectedColor(const QColor &value)
{
    hand2SelectedColor = value;
}

void CstmDoubleHandleSlider::setMidColor(const QColor &value)
{
    midColor = value;
}

void CstmDoubleHandleSlider::setMidSelectedColor(const QColor &value)
{
    midSelectedColor = value;
}

void CstmDoubleHandleSlider::setHand2Value(double value)
{
    if(hand2Value < minValue)
        hand2Value = minValue;
    else if(hand2Value > maxValue)
        hand2Value = maxValue;
    else if(hand2Value < hand1Value)
        hand2Value = hand1Value;
    else
        hand2Value = value;

    updateAfterSetValue();
}

void CstmDoubleHandleSlider::setHand1Value(double value)
{
    if(hand1Value < minValue)
        hand1Value = minValue;
    else  if(hand1Value > maxValue)
        hand1Value = maxValue;
    else if(hand1Value > hand2Value)
        hand1Value = hand2Value;
    else
        hand1Value = value;

    updateAfterSetValue();
}

void CstmDoubleHandleSlider::setMinValue(double value)
{
    if(value > maxValue)
        minValue = maxValue;
    else
        minValue = value;

    if(hand1Value < minValue)
        hand1Value = minValue;
    if(hand2Value < minValue)
        hand2Value = minValue;

}

void CstmDoubleHandleSlider::setMaxValue(double value)
{
    if(value < minValue)
        maxValue = minValue;
    else
        maxValue = value;

    if(hand1Value > maxValue)
        hand1Value = maxValue;
    if(hand2Value > maxValue)
        hand2Value = maxValue;
}

void CstmDoubleHandleSlider::setHand2BorderWidth(int value)
{
    hand2BorderWidth = value;
}

void CstmDoubleHandleSlider::setHand2BorderColor(const QColor &value)
{
    hand2BorderColor = value;
}

void CstmDoubleHandleSlider::setHand1BorderWidth(int value)
{
    hand1BorderWidth = value;
}

void CstmDoubleHandleSlider::setHand1BorderColor(const QColor &value)
{
    hand1BorderColor = value;
}

void CstmDoubleHandleSlider::setHand2Style(const SliderStyle &value)
{
    hand2Style = value;
}

void CstmDoubleHandleSlider::setHand2Height(int value)
{
    hand2Height = value;
}

void CstmDoubleHandleSlider::setHand2Width(int value)
{
    hand2Width = value;
}

void CstmDoubleHandleSlider::setHand1Style(const SliderStyle &value)
{
    hand1Style = value;
}

void CstmDoubleHandleSlider::setHand1Height(int value)
{
    hand1Height = value;
}

void CstmDoubleHandleSlider::setHand1Width(int value)
{
    hand1Width = value;
}

void CstmDoubleHandleSlider::setHand2Color(const QColor &value)
{
    hand2_Color = value;
}

void CstmDoubleHandleSlider::setHand1Color(const QColor &value)
{
    hand1_Color = value;
}

void CstmDoubleHandleSlider::setSliderColor(const QColor &value)
{
    sliderColor = value;
}

void CstmDoubleHandleSlider::setBorderColor(const QColor &value)
{
    borderColor = value;
}

void CstmDoubleHandleSlider::setBorderWidth(int value)
{
    borderWidth = value;
}

void CstmDoubleHandleSlider::setIsHorizontal(bool value)
{
    isHorizontal = value;
}

void CstmDoubleHandleSlider::setSliderThickness(int value)
{
    sliderThickness = value;
}


void CstmDoubleHandleSlider::updateValue()
{
    if(true != isHorizontal)
    {
        sliderLength = this->height() - hand1Height/2 - hand2Height/2;
        hand1_X = hand2_X = this->width()/2;
    }
    else
    {
        sliderLength = this->width() - hand1Width/2 - hand2Width/2;
        hand1_Y = hand2_Y = this->height()/2;
    }
}

void CstmDoubleHandleSlider::updateAfterSetValue()
{
    if(true != isHorizontal)
    {
        hand1_Y = hand1Height/2 + (hand1Value - minValue)/(maxValue - minValue)* sliderLength;
        hand2_Y = this->height() - hand2Height/2 - (maxValue - hand2Value)/(maxValue - minValue)*sliderLength;
    }
    else
    {
        hand1_X = hand1Width/2 + (hand1Value - minValue)/(maxValue - minValue)* sliderLength;
        hand2_X = this->width() - hand2Width/2 -(maxValue - hand2Value)/(maxValue - minValue)*sliderLength;
    }
}
