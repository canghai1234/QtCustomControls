#include "CstmTimepanel.h"

#include<QMessageBox>
#include<QFont>

CstmTimepanel::CstmTimepanel(QWidget *parent) :
    QWidget(parent), timeId(0), flag(false), colorNum1(0), colorNum2(256)
{
//    setWindowFlags(Qt::FramelessWindowHint);
//    this->setFixedHeight(300);
//    this->setFixedWidth(300);
    color_CentralPoint = QColor(65,65,65);
    color_CentralPanel = QColor(235, 235, 235);
    color_Margin = QColor(179, 196, 204);
    color_5Minute = QColor(153, 198, 138);
    color_perMinute = QColor(0, 64, 0);
    color_IndicatorHour = QColor(248,7,7);
    color_IndicatorMinute = QColor(78,86,245);
    color_IndicatorSecond = QColor(133,243,180);

    timeId = startTimer(1000);
    timeValue = QTime::currentTime();

    setColor(item_5Minute,QColor(Qt::yellow));
    setColor(item_IndicatorSecond,QColor("#00F5FF"));
    setColor(item_Margin,QColor(Qt::black));
}

CstmTimepanel::~CstmTimepanel()
{

}

void CstmTimepanel::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timeId)
    {
       timeValue = QTime::currentTime();
       update();
    }
}

void CstmTimepanel::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter;
    painter.begin(this);

    drawInit();
    drawBackground(&painter);
    drawTray(&painter);
//    drawTimeShow(&painter);
    drawIndicatorHour(&painter);
    drawIndicatorMinute(&painter);
    drawIndicatorSecond(&painter);
    drawIndicatorCenter(&painter);

    painter.end();
}

void CstmTimepanel::drawInit()
{
    /************************************************************************/
    /*
       QPointF centerPol;
       float halfLen;
       float backgroundOutRadius,backgroundInnerRadius;
       float trayOutRadius,trayInnerRadius, trayBetweenRadius;
       float hourIndicatorLen,minuteIndicatorLen, secondIndicaetorLen;
       float centerCircle;
       float timeTextLen;
       */
    /************************************************************************/
    int minSize = qMin(this->width(),this->height());
    centerPol.setX(minSize / 2.0);
    centerPol.setY(minSize / 2.0);

    halfLen = minSize / 2.0;//半径

    backgroundOutRadius = halfLen * 0.99;
    backgroundInnerRadius = halfLen *0.95;

    trayOutRadius = halfLen * 0.85;
    trayInnerRadius = halfLen * 0.78;
    trayBetweenRadius = halfLen * 0.82;

    hourIndicatorLen = halfLen * 0.7;
    minuteIndicatorLen = halfLen * 0.6;
    secondIndicaetorLen = halfLen *0.5;

    centerCircle = halfLen * 0.03;

    timeTextLen = halfLen *0.4;
}

//绘制外边框
void CstmTimepanel::drawBackground(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ///////////////////////////////////////////
//    QRadialGradient out(centerPol, backgroundOutRadius, centerPol);
//    out.setColorAt(0.0, QColor(255, 232, 221));
//    out.setColorAt(0.9, QColor(210, 220, 163));
//    out.setColorAt(1.0, QColor(179, 196, 204));
    painter->setBrush(color_Margin);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(centerPol, backgroundOutRadius, backgroundOutRadius);

//    QRadialGradient inner(centerPol, backgroundOutRadius, centerPol);
//    inner.setColorAt(0.0, QColor(252, 252, 252));
//    inner.setColorAt(0.70, QColor(235, 235, 235));
//    inner.setColorAt(0.85, QColor(215, 215, 215));
//    inner.setColorAt(0.95, QColor(180, 180, 180));
//    inner.setColorAt(1.0, QColor(170, 170, 170));
    painter->setBrush(color_CentralPanel);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(centerPol, backgroundInnerRadius, backgroundInnerRadius);
    ///////////////////////////////////////////
    painter->restore();
}

//绘制刻度
void CstmTimepanel::drawTray(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ///////////////////////////////////////////
    painter->translate(centerPol); //设置原点
    painter->rotate(-(60 + 90));  //旋转坐标系 -150°

    painter->save();
    QPen pen;
    for (unsigned int i = 0; i <= /*60*/72; ++i)
    {
        if (!(i % 5))   //every 5 minute
        {
            pen.setWidth(3);
            pen.setColor(color_5Minute);
            painter->setPen(pen);

            painter->drawLine(0, trayInnerRadius, 0, trayOutRadius);// 5's multiple

            /////////////////////////////////////////
            painter->save();
            painter->translate(0, trayInnerRadius*0.88); //Translates the coordinate, reset base point
            switch (i / 5 + 1) // i = 0 5 10 15 ... 70
            {
            case 1:painter->rotate(150); break;
            case 2:painter->rotate(120); break;
            case 3:painter->rotate(90); break;
            case 4:painter->rotate(60); break;
            case 5:painter->rotate(30); break;
            case 6:painter->rotate(0); break;
            case 7:painter->rotate(-30); break;
            case 8:painter->rotate(-60); break;
            case 9:painter->rotate(-90); break;
            case 10:painter->rotate(-120); break;
            case 11:painter->rotate(-150); break;
            case 12:painter->rotate(-180); break;
            }
            QFont font("Courier New", trayInnerRadius*0.1);
            font.setBold(true);
            painter->setFont(font);
            if (i / 5 + 1 <= 12) //draw num
            {
                pen.setWidth(3);
                pen.setColor(QColor(165, 159, 217));
                painter->setPen(pen);
                painter->drawText(-(trayInnerRadius*0.07), 0, QString::number(i / 5 + 1));
            }
            painter->restore();
            /////////////////////////////////////////
        }
        else // minute
        {
            pen.setWidth(1);
            pen.setColor(color_perMinute);
            painter->setPen(pen);

            painter->drawLine(0, trayBetweenRadius, 0, trayOutRadius);
        }

        painter->rotate(6);
    }
    painter->restore();
    ///////////////////////////////////////////

    painter->restore();
}

//draw central point
void CstmTimepanel::drawIndicatorCenter(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ///////////////////////////////////////////////
//    QRadialGradient _centerCircle(centerPol, centerCircle, centerPol);
//    _centerCircle.setColorAt(0.0, QColor(65,65,65));
//    _centerCircle.setColorAt(0.5, QColor(120,120,120));
//    _centerCircle.setColorAt(1.0, QColor(65,65,65));
    painter->setBrush(color_CentralPoint);
    painter->drawEllipse(centerPol, centerCircle, centerCircle);
    ///////////////////////////////////////////////

    painter->restore();
}

void CstmTimepanel::drawIndicatorHour(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //////////////////////////////////////////
    painter->translate(centerPol);
    painter->rotate(-(60 + 90));

    float hour = timeValue.hour() % 12;
    float minute = timeValue.minute();
    if (hour - 1 < 0) //12点
    {
        painter->rotate(-(30-(minute / 60 * 30)));
    }
    else
    {
        painter->rotate((--hour * 30) + minute / 60 * 30);
    }

    const QPoint point[] =
    {
        QPoint(-(hourIndicatorLen*0.04), -(hourIndicatorLen*0.1)),
        QPoint((hourIndicatorLen*0.02), -(hourIndicatorLen*0.1)),
        QPoint((hourIndicatorLen*0.02), (hourIndicatorLen*0.85)),
        QPoint(-(hourIndicatorLen*0.04), (hourIndicatorLen*0.85))
    };
    painter->setPen(Qt::NoPen);
    painter->setBrush(color_IndicatorHour);
    painter->setOpacity(0.6);
    painter->drawConvexPolygon(point, 4);
    //////////////////////////////////////////

    painter->restore();
}

void CstmTimepanel::drawIndicatorMinute(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ///////////////////////////////////////////////////////
    painter->translate(centerPol);
    painter->rotate(-(90 + 90));

    float minute = timeValue.minute();
    painter->rotate(360/60 * minute);

    const QPoint point[] =
    {
        QPoint(-(minuteIndicatorLen*0.03), -(minuteIndicatorLen*0.12)),
        QPoint((minuteIndicatorLen*0.02), -(minuteIndicatorLen*0.12)),
        QPoint((minuteIndicatorLen*0.02), (minuteIndicatorLen*1.2)),
        QPoint(-(minuteIndicatorLen*0.03), (minuteIndicatorLen*1.2))
    };
    painter->setPen(Qt::NoPen);
    painter->setBrush(color_IndicatorMinute);
    painter->drawConvexPolygon(point, 4);
    ///////////////////////////////////////////////////////

    painter->restore();
}

void CstmTimepanel::drawIndicatorSecond(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ///////////////////////////////////////////////////////
    painter->translate(centerPol);
    painter->rotate(-(90 + 90));

    float second = timeValue.second();

    painter->rotate(360 / 60 * second);

    const QPoint point[] =
    {
        QPoint(-(secondIndicaetorLen*0.02), -(secondIndicaetorLen*0.4)),
        QPoint((secondIndicaetorLen*0.01), -(secondIndicaetorLen*0.4)),
        QPoint((secondIndicaetorLen*0.01), (secondIndicaetorLen*1.6)),
        QPoint(-(secondIndicaetorLen*0.02), (secondIndicaetorLen*1.6))
    };
    painter->setPen(Qt::NoPen);
    painter->setBrush(color_IndicatorSecond);
    painter->drawConvexPolygon(point, 4);
    ///////////////////////////////////////////////////////

    painter->restore();
}

void CstmTimepanel::drawTimeShow(QPainter *painter)
{
    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    /////////////////////////////////////////////////////////
    painter->translate(centerPol);

    QString timeAP;
    if (timeValue.hour() <= 12)
    {
        timeAP = "AM";
    }
    else
    {
        timeAP = "PM";
    }

    painter->setFont(QFont("Courier New", timeTextLen*0.25));
    painter->setPen(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    painter->drawText(-(timeTextLen*1.05), -(timeTextLen*0.6), QString("%1 %2").arg(timeAP).arg(timeValue.toString()));
    /////////////////////////////////////////////////////////

    painter->restore();
}

void CstmTimepanel::setColor(CstmTimepanel::Item item, QColor color)
{
    switch (item) {
    case item_5Minute:
        color_5Minute = color;
        break;
    case item_CentralPanel:
        color_CentralPanel = color;
        break;
    case item_CentralPoint:
        color_CentralPoint = color;
        break;
    case item_IndicatorHour:
        color_IndicatorHour = color;
        break;
    case item_IndicatorMinute:
        color_IndicatorMinute = color;
        break;
    case item_IndicatorSecond:
        color_IndicatorSecond = color;
        break;
    case item_Margin:
        color_Margin = color;
        break;
    case item_perMinute:
        color_perMinute = color;
        break;
    default:
        break;
    }
}



























