#include "CstmGroupButton.h"

CstmGroupButton::CstmGroupButton(QWidget *parent) : QWidget(parent)
{
     borderWidth =1;
     borderSelectedWidth = 1;
     borderColor = QColor(0,0,0,255);
     borderSelectedColor = QColor(0,0,0,255);
     BorderRadius = 10;
     SelectedBorderRadius = 5;

     iconWidth = 30;
     iconHeight = 30;

     buttonColor = QColor(238,238,238,255);
     buttonSelectedColor = QColor(71,172,250,255);

    buttonCount = 4;
    buttonHeight = 40;
    buttonSelectedHeight = 55;
    currentSelected = 0;
}

void CstmGroupButton::setButtonIcon(const int buttonNumber, const QPixmap &pixmap)
{
    if(buttonNumber < buttonCount)
    {
        bool pixIsExisted = false;
        for(int listID = 0;listID < listButtonPixmapID.size(); ++ listID)
        {
            if(buttonNumber == listButtonPixmapID.at(listID) )
            {
                listButtonPixmap.removeAt(listID);
                listButtonPixmap.insert(listID,pixmap);
                pixIsExisted = true;
            }
        }
        if(true != pixIsExisted)
        {
            listButtonPixmap.push_back(pixmap);
            listButtonPixmapID.push_back(buttonNumber);
        }
    }
}

void CstmGroupButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);
    updateButtonParameter();
    QPainter painter(this);
    drawAllButton(&painter);
    drawSelectedButton(&painter);
    drawPixmap(&painter);
}

void CstmGroupButton::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    for(int buttonID = 0 ; buttonID < buttonCount; ++ buttonID)
    {
        if((point.y() > (centerY - buttonHeight/2)) && (point.y() <  (centerY - buttonHeight/2 + buttonHeight)))
        {
            if((point.x() > buttonID * buttonWidth) && (point.x() < (buttonID + 1 ) * buttonWidth))
            {
                currentSelected = buttonID;
                emit signal_valueChanged(buttonID);
                break;
            }
        }
    }
    this->update();
}

void CstmGroupButton::setIconHeight(int value)
{
    iconHeight = value;
    if(iconHeight < 0)
        iconHeight = 0;
    else if(iconHeight > buttonHeight)
        iconHeight = buttonHeight;
}

void CstmGroupButton::setIconWidth(int value)
{
    iconWidth = value;
    if(iconWidth < 0)
        iconWidth = 0;
    else if(iconWidth > buttonWidth)
        iconWidth = buttonWidth;
}

void CstmGroupButton::setButtonSelectedHeight(int value)
{
    buttonSelectedHeight = value;
    if(buttonSelectedHeight < buttonHeight)
        buttonSelectedHeight = buttonHeight;
    else if(buttonSelectedHeight > this->height())
        buttonSelectedHeight = this->height();
}

void CstmGroupButton::setButtonHeight(int value)
{
    buttonHeight = value;
    if(buttonHeight < 0)
        buttonHeight = 0;
    else if(buttonHeight >  buttonSelectedHeight)
        buttonHeight = buttonSelectedHeight;
}

void CstmGroupButton::setButtonCount(int value)
{
    buttonCount = value;
    if(buttonCount < 1)
        buttonCount = 1;
}

void CstmGroupButton::setSelectedBorderRadius(int value)
{
    SelectedBorderRadius = value;
    if(SelectedBorderRadius < 0)
        SelectedBorderRadius = 0;
    else if(SelectedBorderRadius >  buttonSelectedHeight/2)
        SelectedBorderRadius =  buttonSelectedHeight/2;
}

void CstmGroupButton::setBorderRadius(int value)
{
    BorderRadius = value;
    if(BorderRadius < 0)
        BorderRadius = 0;
    else if(BorderRadius >  buttonHeight/2)
        BorderRadius =  buttonHeight/2;
}

void CstmGroupButton::setBorderSelectedColor(const QColor &value)
{
    borderSelectedColor = value;
}

void CstmGroupButton::setBorderColor(const QColor &value)
{
    borderColor = value;
}

void CstmGroupButton::setBorderSelectedWidth(int value)
{
    borderSelectedWidth = value;
    if(borderSelectedWidth < 0)
        borderSelectedWidth = 0;
    else if(borderSelectedWidth >  buttonSelectedHeight/2)
        borderSelectedWidth =  buttonSelectedHeight/2;
}

void CstmGroupButton::setBorderWidth(int value)
{
    borderWidth = value;
    if(borderWidth < 0)
        borderWidth = 0;
    else if(borderWidth >  buttonHeight/2)
        borderWidth =  buttonHeight/2;
}

void CstmGroupButton::setButtonColor(const QColor &value)
{
    buttonColor = value;
}

void CstmGroupButton::setButtonSelectedColor(const QColor &value)
{
    buttonSelectedColor = value;
}

void CstmGroupButton::setCurrentSelected(int value)
{
    currentSelected = value;
    if(currentSelected < 0 )
        currentSelected = 0;
    else if(currentSelected >= buttonCount)
        currentSelected = buttonCount - 1;
    this->update();
}

void CstmGroupButton::updateButtonParameter()
{
    buttonWidth = this->width()/buttonCount;
    centerY = this->height() /2;
}

void CstmGroupButton::drawAllButton(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(borderColor,borderWidth));
    painter->setBrush(buttonColor);
    painter->drawRoundedRect(0,centerY - buttonHeight/2,this->width(),buttonHeight,BorderRadius,BorderRadius,Qt::AbsoluteSize);

    QPainterPath path;
    for(int buttonID = 1; buttonID < buttonCount; buttonID ++ )
    {
        path.moveTo(buttonWidth * buttonID ,centerY - buttonHeight/2);
        path.lineTo(buttonWidth * buttonID ,centerY - buttonHeight/2 + buttonHeight);
    }
    painter->drawPath(path);
    painter->restore();
}

void CstmGroupButton::drawSelectedButton(QPainter *painter)
{
    painter->save();
    QRect rect;
    rect.setRect(buttonWidth * (currentSelected) ,centerY - buttonSelectedHeight/2 ,buttonWidth , buttonSelectedHeight);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(borderSelectedColor,borderSelectedWidth));
    painter->setBrush(buttonSelectedColor);
    painter->drawRoundedRect(rect,SelectedBorderRadius,SelectedBorderRadius,Qt::AbsoluteSize);
    painter->restore();
}

void CstmGroupButton::drawPixmap(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    for(int buttonID = 0 ; buttonID < buttonCount; ++ buttonID)
    {
        for(int number = 0; number < listButtonPixmapID.size(); ++ number)
        {
            if(buttonID == listButtonPixmapID.at(number))
            {
                if(listButtonPixmap.size() > number)
                    if(false  == (listButtonPixmap.at(number).isNull()))
                    {
                        QPixmap pix = listButtonPixmap.at(number);
                        QRectF rect;
                        qreal rectX = buttonID * buttonWidth + (buttonWidth - iconWidth)/2.0;
                        qreal rectY = centerY - iconHeight/2.0 ;
                        rect.setRect(rectX,rectY,iconWidth,iconHeight);
                        painter->drawPixmap(rect,pix,pix.rect());
                    }
            }
        }
    }
    painter->restore();
}
