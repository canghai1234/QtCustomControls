#include "CstmSpinButton.h"

CstmSpinButton::CstmSpinButton(QWidget *parent) : QWidget(parent)
{
    buttonWidth = 60;
    borderWidth = 1;
    symbolWidth = 4;

    backgroundColor = QColor(255,255,255,255);
    minusButtonColor = QColor(238,238,238,255);
    minusButtonClickColor = QColor(71,172,250,255);
    plusButtonColor = QColor(238,238,238,255);
    plusButtonClickColor = QColor(71,172,250,255);
    spaceColor = QColor(255,255,255,255);
    borderColor = QColor(0,0,0,255);
    minusClickColor  = QColor(255,255,255,255);
    plusClickColor = QColor(255,255,255,255);
    minusColor = QColor(0,0,0,255);
    plusColor= QColor(0,0,0,255);

    minusPressed = plusPressed =false;

    this->setFixedSize(125,40);
}

void CstmSpinButton::setButtonWidth(int value)
{
    buttonWidth = value;
    if(buttonWidth > (this->width()/2))
        buttonWidth = (this->width()/2);
}

void CstmSpinButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(this->rect());

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(borderColor,borderWidth));
    painter.setBrush(spaceColor);
    painter.drawRect(buttonWidth,0,this->width() - buttonWidth*2 , this->height());

    drawMinusButton(&painter);
    drawMinusSymbol(&painter);
    drawPlusButton(&painter);
    drawPlusSymbol(&painter);
}

void CstmSpinButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QPointF point = event->pos();
    if (point.x() <= this->height()/2.0)
    {
        int yLength =sqrt((this->height()/2.0) *( this->height()/2.0) - (this->height()/2.0 - point.x()) * (this->height()/2.0 - point.x()));
        if ((point.y() >= (this->height()/2.0 - yLength )) && (point.y() <= (this->height()/2.0 - yLength)) )
        {
            minusPressed = true;
            emit signal_minusPressed();
        }
    }
    else if(point.x() <= buttonWidth)
    {
        minusPressed = true;
        emit signal_minusPressed();
    }
    else if (point.x() >= this->width() - this->height()/2.0)
    {
        int circleCenterX = this->width() - this->height()/2.0;
        int yLength =sqrt((this->height()/2.0) *( this->height()/2.0) - (point.x() - circleCenterX) * (point.x() - circleCenterX) );
        if( ((point.y() >= (this->height()/2.0 - yLength )) && (point.y() <= (this->height()/2.0 - yLength)) ))
        {
            emit signal_plusPressed();
            plusPressed = true;
        }
    }
    else if(point.x() > (this->width() - buttonWidth))
    {
        plusPressed = true;
        emit signal_plusPressed();
    }
    this->update();
}

void CstmSpinButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QPointF point = event->pos();
    if (point.x() <= this->height()/2.0)
    {
        int yLength =sqrt((this->height()/2.0) *( this->height()/2.0) - (this->height()/2.0 - point.x()) * (this->height()/2.0 - point.x()));
        if ((point.y() >= (this->height()/2.0 - yLength )) && (point.y() <= (this->height()/2.0 - yLength)) )
        {
            if(true == minusPressed)
                emit signal_minusClicked();
            minusPressed = false;
            emit signal_minusReleased();
        }
    }
    else if(point.x() <= buttonWidth)
    {
        if(true == minusPressed)
            emit signal_minusClicked();
        minusPressed = false;
        emit signal_minusReleased();
    }
    else if (point.x() >= this->width() - this->height()/2.0)
    {
        int circleCenterX = this->width() - this->height()/2.0;
        int yLength =sqrt((this->height()/2.0) *( this->height()/2.0) - (point.x() - circleCenterX) * (point.x() - circleCenterX) );
        if( ((point.y() >= (this->height()/2.0 - yLength )) && (point.y() <= (this->height()/2.0 - yLength)) ))
        {
            if(true == plusPressed)
                emit signal_plusClicked();
            plusPressed = false;
            emit signal_plusReleased();
        }
    }
    else if(point.x() > (this->width() - buttonWidth))
    {
        if(true == plusPressed)
            emit signal_plusClicked();
        plusPressed = false;
        emit signal_plusReleased();
    }
    else
    {
        minusPressed = false;
        plusPressed = false;
    }
    this->update();
}

void CstmSpinButton::drawMinusButton(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(borderColor,borderWidth));
    if( true != minusPressed)
        painter->setBrush(minusButtonColor);
    else
        painter->setBrush(minusButtonClickColor);

    QPainterPath minusPath;
    minusPath.moveTo(this->height()/2,0);
    minusPath.lineTo(buttonWidth,0);
    minusPath.lineTo(buttonWidth, this->height());
    minusPath.lineTo(this->height()/2,this->height());
    minusPath.arcTo(0,0,this->height(),this->height(),-90,-180);
    painter->drawPath(minusPath);
    painter->restore();
}

void CstmSpinButton::drawMinusSymbol(QPainter *painter)
{
    painter->save();

    int symbolLength = buttonWidth /3 ;
    if(symbolLength > (2*  this->height()/3))
        symbolLength = (2*  this->height()/3);
    int minusSymbolMidX = buttonWidth/2;

    if( true != minusPressed)
        painter->setPen(QPen(minusColor,symbolWidth));
    else
        painter->setPen(QPen(minusClickColor,symbolWidth));

    QPainterPath minusPath;
    minusPath.moveTo(minusSymbolMidX - symbolLength/2  , this->height()/2);
    minusPath.lineTo(minusSymbolMidX + symbolLength/2 , this->height()/2);
    painter->drawPath(minusPath);
    painter->restore();
}

void CstmSpinButton::drawPlusButton(QPainter *painter)
{
    painter->save();
    int buttonRadius =  this->height()/2;
    int width = this->width();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(borderColor,borderWidth));
    if( true != plusPressed)
        painter->setBrush(plusButtonColor);
    else
        painter->setBrush(plusButtonClickColor);

    QPainterPath plusPath;
    plusPath.moveTo(width - buttonRadius,0);
    plusPath.lineTo(width - buttonWidth,0);
    plusPath.lineTo(width - buttonWidth, this->height());
    plusPath.lineTo(width - buttonRadius,this->height());
    plusPath.arcTo(width - buttonRadius*2,0,this->height(),this->height(),-90,180);
    painter->drawPath(plusPath);
    painter->restore();
}

void CstmSpinButton::drawPlusSymbol(QPainter *painter)
{
    painter->save();
    int symbolLength = buttonWidth /3 ;
    if(symbolLength > (2*  this->height()/3))
        symbolLength = (2*  this->height()/3);
    int width = this->width();
    int plusSymbolMidX = width -buttonWidth/2;

    if( true != plusPressed)
        painter->setPen(QPen(plusColor,symbolWidth));
    else
        painter->setPen(QPen(plusClickColor,symbolWidth));

    QPainterPath minusPath;
    minusPath.moveTo(plusSymbolMidX - symbolLength/2 , this->height()/2);
    minusPath.lineTo(plusSymbolMidX + symbolLength/2 , this->height()/2);
    minusPath.moveTo(plusSymbolMidX , this->height()/2 - symbolLength/2);
    minusPath.lineTo(plusSymbolMidX , this->height()/2 + symbolLength/2);
    painter->drawPath(minusPath);
    painter->restore();
}

void CstmSpinButton::setBorderColor(const QColor &value)
{
    borderColor = value;
}

void CstmSpinButton::setPlusClickColor(const QColor &value)
{
    plusClickColor = value;
}

void CstmSpinButton::setPlusColor(const QColor &value)
{
    plusColor = value;
}

void CstmSpinButton::setMinusClickColor(const QColor &value)
{
    minusClickColor = value;
}

void CstmSpinButton::setMinusColor(const QColor &value)
{
    minusColor = value;
}

void CstmSpinButton::setBackgroundColor(const QColor &value)
{
    backgroundColor = value;
}

void CstmSpinButton::setSymbolWidth(int value)
{
    symbolWidth = value;
    if(symbolWidth > this->height()/5)
        symbolWidth = this->height()/5;
    if(symbolWidth < 0)
        symbolWidth = 0;
}

void CstmSpinButton::setBorderWidth(int value)
{
    borderWidth = value;
    if(borderWidth > this->height()/5)
        borderWidth = this->height()/5;
    else if(borderWidth < 0)
        borderWidth = 0;
}

void CstmSpinButton::setFixedSize(int w, int h)
{
    if(w < 2*h)
        this->setFixedWidth( 2*h);
    else
        this->setFixedWidth(w);
    this->setFixedHeight(h);
}

void CstmSpinButton::setFixedSize(QSize size)
{
    if(size.width() < size.height() * 2)
        this->setFixedWidth( size.height() * 2);
    else
        this->setFixedWidth(size.width());
    this->setFixedHeight(size.height());
}

void CstmSpinButton::setSpaceColor(const QColor &value)
{
    spaceColor = value;
}

void CstmSpinButton::setPlusButtonClickColor(const QColor &value)
{
    plusButtonClickColor = value;
}

void CstmSpinButton::setPlusButtonColor(const QColor &value)
{
    plusButtonColor = value;
}

void CstmSpinButton::setMinusButtonClickColor(const QColor &value)
{
    minusButtonClickColor = value;
}

void CstmSpinButton::setMinusButtonColor(const QColor &value)
{
    minusButtonColor = value;
}
