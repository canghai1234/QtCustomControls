#include "CstmSliderSwitch.h"

CstmSliderSwitch::CstmSliderSwitch(QWidget *parent) : QWidget(parent)
{
    isRounded	= false;
    onStateCorlor = QColor(173,255,47);
    offStateCorlor = QColor(232,232,232);
    sliderCorlor = QColor(148,0,211);
    textCorlor = QColor(43,0,173);
    switchBorderCorlor = QColor(0,255,0);
    sliderBorderCorlor = QColor(255,0,0);
    switchBorderWidth = 5;
    sliderBorderWidth = 5;

    textfont= QFont(QString::fromLocal8Bit("SONG TI"), 10);
    onStateString =  QString::fromLocal8Bit("ON");
    offStateString =  QString::fromLocal8Bit("OFF");
    switchState = false;
    this->resize(120,80);
}

void CstmSliderSwitch::mousePressEvent(QMouseEvent * event)
{
    QPoint	cursorpos = event->pos();
    int		x = cursorpos.x();

    if (event->button() == Qt::LeftButton) {
        bool tmp_state = switchState;
        if (x < width() / 2.0)
            switchState = true;
        else
            switchState = false;

        if(tmp_state != switchState)
            emit StateChanged(switchState);
    }

    repaint();

    QWidget::mousePressEvent(event);
}

void CstmSliderSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QRect widgetrect(0, 0, width(), height());
    drawBackground(&painter, widgetrect, switchState);
    drawText(&painter, widgetrect, switchState);
    drawSlider(&painter, widgetrect, switchState);
}

void CstmSliderSwitch::drawBackground(QPainter *painter, QRect &rect, bool state)
{
    painter->save();
    int	x1 = rect.left(); int y1 = rect.top();
    int	x2 = rect.right(); int y2 = rect.bottom();
    int height = rect.height();

    if (true != isRounded) {		//rectangular background ,rectangular slider
        painter->setPen(QPen(switchBorderCorlor, switchBorderWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        if (false != state ) 	//on
            painter->setBrush(offStateCorlor);
        else 				//off
            painter->setBrush(onStateCorlor);
        painter->drawRoundedRect(rect, 5.0, 5.0);
    }
    else {	//RoundRect background , slider slider
        //path
        QPainterPath path;

        path.moveTo(x1 + height / 2.0, y1);
        path.arcTo(QRectF(x1, y1, height, height), 90, 180);
        path.lineTo(x2 - height / 2.0, y2);
        path.arcTo(QRectF(x2 - height, y1, height, height), 270, 180);
        path.lineTo(x1 + height / 2.0, y1);

        QPainterPath pathrect;
        pathrect.moveTo(rect.left(), rect.top());
        pathrect.lineTo(rect.left(), rect.bottom());
        pathrect.lineTo(rect.right(), rect.bottom());
        pathrect.lineTo(rect.right(), rect.top());
        pathrect.lineTo(rect.left(), rect.top());

        QPainterPath interpath = path.intersected(pathrect);
        painter->setPen(QPen(switchBorderCorlor, switchBorderWidth, Qt::SolidLine,
                             Qt::RoundCap, Qt::RoundJoin));
        if (false != state) //on
            painter->setBrush(offStateCorlor);
        else //off
            painter->setBrush(onStateCorlor);

        painter->drawPath(interpath);
    }
    painter->restore();
}

void CstmSliderSwitch::drawText(QPainter *painter, QRect &rect, bool state)
{
    painter->save();

    int	x1 = rect.left(); int y1 = rect.top();
    int width = rect.width(); int height = rect.height();

    QPen textPen(textCorlor);
    painter->setFont(textfont);
    if (false != state ) {		//on
        painter->setPen(textPen);
        painter->drawText((int)(x1 + width / 2.0), y1, (int)(width / 2.0), height, Qt::AlignCenter,onStateString);
    }
    else {					//off
        painter->setPen(textPen);
        painter->drawText(x1, y1, (int)(width / 2.0), height, Qt::AlignCenter,offStateString );
    }
    painter->restore();
}

void CstmSliderSwitch::drawSlider(QPainter *painter, QRect &rect, bool state)
{
    painter->save();
    QRect sliderect;
    painter->setPen(QPen(sliderBorderCorlor, sliderBorderWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(sliderCorlor);

    if (true != isRounded) {		//rectangular background ,rectangular slider
        if (false != state ) {		//on
            sliderect.setLeft(rect.left() + 2);
            sliderect.setTop(rect.top() + 2);
            sliderect.setWidth((int)(rect.width() / 2.0 - 4));
            sliderect.setHeight(rect.height() - 4);
        }
        else {					//off
            sliderect.setLeft(rect.right() - (int)(rect.width() / 2.0) + 2);
            sliderect.setTop(rect.top() + 2);
            sliderect.setWidth((int)(rect.width() / 2.0 - 4));
            sliderect.setHeight(rect.height() - 4);
        }
            painter->drawRoundedRect(sliderect, 5.0, 5.0);

        //draw line  on the slider
        painter->setPen(QColor(54, 54, 54));
        painter->drawLine(sliderect.left() + sliderect.width() / 2.0,	  sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0, sliderect.bottom() - sliderect.height() / 4.0 - 2);
        painter->drawLine(sliderect.left() + sliderect.width() / 2.0 - 5, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 - 5, sliderect.bottom() - sliderect.height() / 4.0 - 2);
        painter->drawLine(sliderect.left() + sliderect.width() / 2.0 + 5, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 + 5, sliderect.bottom() - sliderect.height() / 4.0 - 2);

        painter->setPen(QColor(134, 134, 134));
        painter->drawLine(sliderect.left() + sliderect.width() / 2.0 + 1,	  sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 + 1, sliderect.bottom() - sliderect.height() / 4.0 - 2);
        painter->drawLine(sliderect.left() + sliderect.width() / 2.0 - 5 + 1, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 - 5 + 1, sliderect.bottom() - sliderect.height() / 4.0 - 2);
        painter->drawLine(sliderect.left() + sliderect.width() / 2.0 + 5 + 1, sliderect.top() + sliderect.height() / 4.0 + 2, sliderect.left() + sliderect.width() / 2.0 + 5 + 1, sliderect.bottom() - sliderect.height() / 4.0 - 2);
    }
    else {	//RoundRect background , slider slider
        if (false != state) {		//on
            sliderect.setLeft(rect.left() + 2);
            sliderect.setTop(rect.top() + 2);
            sliderect.setWidth(rect.height() - 4 );
            sliderect.setHeight(rect.height() - 4);
        }
        else {					//off
            sliderect.setLeft(rect.right() -  rect.height() + 4 - 2);
            sliderect.setTop(rect.top() + 2);
            sliderect.setWidth(rect.height() - 4 );
            sliderect.setHeight(rect.height() - 4);
        }
        QRect sliderRect;
        sliderRect = sliderect.intersected(rect);
        painter->drawEllipse(sliderRect);
    }

    painter->restore();
}

void CstmSliderSwitch::setOnStateCorlor(const QColor &value)
{
    onStateCorlor = value;
}

void CstmSliderSwitch::setOffStateCorlor(const QColor &value)
{
    offStateCorlor = value;
}

void CstmSliderSwitch::setOnStateString(const QString &value)
{
    onStateString = value;
}

void CstmSliderSwitch::setOffStateString(const QString &value)
{
    offStateString = value;
}

void CstmSliderSwitch::setSliderCorlor(const QColor &value)
{
    sliderCorlor = value;
}

void CstmSliderSwitch::setTextCorlor(const QColor &value)
{
    textCorlor = value;
}

void CstmSliderSwitch::setTextfont(const QFont &value)
{
    textfont = value;
}

void CstmSliderSwitch::setSwitchStatus(bool value)
{
    switchState = value;
    repaint();
}

void CstmSliderSwitch::setSwitchBorderWidth(int value)
{
    switchBorderWidth = value;
    if(switchBorderWidth < 0)
        switchBorderWidth = 0;
}

void CstmSliderSwitch::setSliderBorderWidth(int value)
{
    sliderBorderWidth = value;
    if(sliderBorderWidth < 0)
        sliderBorderWidth = 0;
}

void CstmSliderSwitch::setSwitchBorderCorlor(const QColor &value)
{
    switchBorderCorlor = value;
}

void CstmSliderSwitch::setSliderBorderCorlor(const QColor &value)
{
    sliderBorderCorlor = value;
}

void CstmSliderSwitch::setSwitchIsRounded(bool value)
{
    isRounded = value;
}
