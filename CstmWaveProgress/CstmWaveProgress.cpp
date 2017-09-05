#include "CstmWaveProgress.h"
#include <QDebug>

CstmWaveProgress::CstmWaveProgress(QWidget *parent)
    : QWidget(parent)
{
    maxValue =100;
    minValue =0;
    currentValue = 50;
    updataTime = 50;
    borderWidth=20;

    waterDensity = 5;
    waterHeight = 5.0;
    offset = 0;

    textColor = QColor("#FF0000");
    waveColor = QColor("#00FF00");
    borderColor = QColor("#000000");
    widgetStyle = WidgetStyle_Circle;

    timer = new QTimer(this);
    timer->start(updataTime);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()),Qt::UniqueConnection);
}

CstmWaveProgress::~CstmWaveProgress()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

void CstmWaveProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBorder(&painter);
    drawValue(&painter);
    drawText(&painter);

    painter.end();
}

void CstmWaveProgress::drawValue(QPainter *painter)
{
    int height = this-> height();
    int width = this->width();
    int side = qMin(width, height);

    // y = A * sin(ωx + φ) + k
    double percent = 1 - (double)(currentValue - minValue) / (maxValue - minValue);    //calculate current percentage
    double w = waterDensity * M_PI / width;   //Number of sinusoidal cycles
    double A = height * waterHeight / 100;       //height of the wave

    double k = height * percent;

    QPainterPath waterPath1;
    QPainterPath waterPath2;

    waterPath1.moveTo(0, height);
    waterPath2.moveTo(0, height);

    offset += 0.6;
    if (offset > (width / 2)) {
        offset = 0;
    }

    for(int x = 0; x <= width; x++) {
        double waterY1 = (double)(A * sin(w * x + offset)) + k;
        double waterY2 = (double)(A * sin(w * x + offset + (width / 2 * w))) + k;

        if (this->currentValue == minValue) {
            waterY1 = height;
            waterY2 = height;
        }
        if (this->currentValue == maxValue) {
            waterY1 = 0;
            waterY2 = 0;
        }
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }

    waterPath1.lineTo(width, height);
    waterPath2.lineTo(width, height);

    QPainterPath bigPath;
    if (widgetStyle == WidgetStyle_Rect) {
        width = width - borderWidth * 2;
        height = height - borderWidth * 2;
        bigPath.addRect(borderWidth, borderWidth, width, height);
    } else if (widgetStyle == WidgetStyle_Circle) {
        side = side - borderWidth * 2;
        bigPath.addEllipse(QPointF(this->width() / 2, this->height()/2), side/2, side/2);
    } else if (widgetStyle == WidgetStyle_Ellipse) {
        width = width - borderWidth * 2;
        height = height - borderWidth * 2;
        bigPath.addEllipse(borderWidth, borderWidth, width, height);
    }

    painter->save();

    QPainterPath path;
    painter->setPen(Qt::NoPen);
    QColor waterColor1 = waveColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = waveColor;
    waterColor2.setAlpha(180);


    path = bigPath.intersected(waterPath1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);

    path = bigPath.intersected(waterPath2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);

    painter->restore();
}

void CstmWaveProgress::drawBorder(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(borderColor,borderWidth));
    int side = qMin(this->width(), this->height());
    int width = this->width()/2;
    int height = this->height()/2;
    int radius = side/2 - borderWidth/2;
    if (widgetStyle == WidgetStyle_Rect)
    {
       painter->drawRect(this->rect() - QMargins(borderWidth/2,borderWidth/2,borderWidth/2,borderWidth/2));
    }
    else if (widgetStyle == WidgetStyle_Circle)
    {
        painter->drawEllipse(QPointF(width,height),radius,radius);
    }
    else if (widgetStyle == WidgetStyle_Ellipse)
    {
        painter->drawEllipse(QPointF(width,height),width - borderWidth/2,height - borderWidth/2);
    }
    painter->restore();

}

void CstmWaveProgress::drawText(QPainter *painter)
{
    painter->save();

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(textColor,5));

    int side = qMin(this->width(), this->height());
    int width = this->width()/2;
    int height = this->height()/2;
    int radius = side/2 - borderWidth/2;

    int startRectX = width - radius;
    int startRectY = height - radius/2;

    QFont font = painter->font();
    font.setPixelSize(radius);
    painter->setFont(font);
    QRect textRect = QRect(startRectX,startRectY,2*radius,radius);
    painter->drawText(textRect,Qt::AlignCenter,QString::number(currentValue));
    painter->restore();
}

void CstmWaveProgress::setTextColor(const QColor &value)
{
    textColor = value;
}

void CstmWaveProgress::setOffset(double value)
{
    offset = value;
}

void CstmWaveProgress::setUpdataTime(int value)
{
    if(value < 0)
        updataTime = 0;
    else
        updataTime = value;
}

void CstmWaveProgress::setWaterHeight(double value)
{
    if(value < 0)
        waterHeight = 0;
    else
        waterHeight = value;
    timer->stop();
    timer->start(updataTime);
}

void CstmWaveProgress::setWaterDensity(double value)
{
    if(value < 0)
        waterDensity = 0;
    else
        waterDensity = value;
}

void CstmWaveProgress::setMaxValue(double value)
{
    if(value < minValue)
        minValue = value;
    maxValue = value;
}

void CstmWaveProgress::setMinValue(double value)
{
    if(value > maxValue)
        maxValue = value;
    minValue = value;
}

void CstmWaveProgress::setCurrentValue(double value)
{
    if(value < minValue)
        currentValue = minValue;
    else if(value > maxValue)
        currentValue = maxValue;
    else
        currentValue = value;
}

void CstmWaveProgress::setWidgetStyle(const WidgetStyle &value)
{
    if(value != WidgetStyle_Rect && value !=  WidgetStyle_Circle && value != WidgetStyle_Ellipse)
        widgetStyle = WidgetStyle_Circle;
    else
        widgetStyle = value;
}

void CstmWaveProgress::setBorderColor(const QColor &value)
{
    borderColor = value;
}

void CstmWaveProgress::setWaveColor(const QColor &value)
{
    waveColor = value;
}

void CstmWaveProgress::setBorderWidth(int value)
{
    if(value < 0)
        borderWidth = 0;
    else
        borderWidth = value;
}
