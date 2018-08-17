#include "mainwindow.h"
#include <QLinearGradient>
#include <qmath.h>


CstmSpeedPanel::CstmSpeedPanel(QWidget *parent)
    : QWidget(parent)
{
    resize(400,400);
    m_startAngle = 150; //顺时针角度
    m_endAngle = 30;

    m_refSize = 200;
    m_radius = m_refSize /2;

    m_minSpeed = 0;   //由于绘制刻度，需要为5倍数
    m_maxSpeed = 220; //由于绘制刻度，需要为5倍数
    m_curSpeed = m_minSpeed;
    //速度对应的角度
    m_anglePerVel = (360.0 - (m_startAngle - m_endAngle)) / (m_maxSpeed - m_minSpeed);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // >> 里程窗口
    m_lcd_Mileage = new QLCDNumber;
    m_lbl_Mileage = new QLabel;
    m_layout_mileage = new QHBoxLayout;
    m_layout_mileage->setSpacing(4);
    m_layout_mileage->setMargin(0);

    m_layout_mileage->addWidget(m_lcd_Mileage);
    m_layout_mileage->addWidget(m_lbl_Mileage);

    m_wgt_mileage = new QWidget(this);
    m_wgt_mileage->setLayout(m_layout_mileage);
    m_wgt_mileage->resize(width()*0.4,30);

    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    m_lbl_Mileage->setPalette(palette);
    QFont ft = m_lbl_Mileage->font();
    ft.setPixelSize(24);
    m_lbl_Mileage->setFont(ft);
    m_lbl_Mileage->setText("KM");

    m_lcd_Mileage->setDigitCount(8);
    m_lcd_Mileage->setSegmentStyle(QLCDNumber::Flat);    // 设置显示外观
    m_lcd_Mileage->setStyleSheet("border: 1px solid green; color: green; background: silver;");
    m_wgt_mileage->show();
    // <<  里程窗口

}

CstmSpeedPanel::~CstmSpeedPanel()
{


}

void CstmSpeedPanel::setCurentSpeed(int speed)
{
    m_curSpeed = speed;
    update();
}

void CstmSpeedPanel::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float scale = qMin(width(),height());
    //设置缩放比例和原点的先后顺序很重要
    painter.scale(scale/m_refSize,scale/m_refSize);
    painter.translate(m_refSize/2,m_refSize/2); //设置坐标原点

    drawFrame(painter);
    drawDividing(painter);//绘制刻度
    drawNumberIndicator(painter);//绘制指示数字
    drawNumberSpeed(painter);//显示数字速度
    drawIndicator(painter);//绘制速度指针
//    QPoint pos = m_wgt_mileage->mapFromParent(QPoint(-m_wgt_mileage->width()/2,40));

    m_wgt_mileage->setGeometry((width() - m_wgt_mileage->width()) / 2 + 30,height() - m_wgt_mileage->height() - 60,m_wgt_mileage->width(),m_wgt_mileage->height());

}

void CstmSpeedPanel::drawFrame(QPainter &painter)
{
    painter.save();
    painter.setPen(Qt::NoPen);//确保没有边框线----填满，不留边界线
    QLinearGradient lg1(-m_radius,-m_radius,m_radius,m_radius);//渐变区域
    lg1.setColorAt(0.1,Qt::white);
    lg1.setColorAt(1,Qt::black);
//    lg1.setSpread(QGradient::ReflectSpread);//渐变样式
    painter.setBrush(lg1);
    painter.drawEllipse(-m_radius,-m_radius,m_refSize,m_refSize);

    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0,0),90,90);
    painter.restore();
}

//绘制数字指示
void CstmSpeedPanel::drawNumberIndicator(QPainter &painter)
{
    painter.save();

    painter.setPen(Qt::white);

    double x,y;
    double angle, angleArc;
    double w,h;
    QFontMetricsF fm(this->font());

    for (int i = m_minSpeed; i <= m_maxSpeed; i+= 20)//每隔20Km设置一个数字
    {
        angle = 360 - (m_startAngle + (i - m_minSpeed) * m_anglePerVel); //角度
        angleArc = angle * 3.14 / 180; //转换为弧度

        x = 65 * cos(angleArc);
        y = -65 * sin(angleArc); // 负号的意义在于 Y轴正方向向下

        QString speed = QString::number(i);

        if (i % 20 == 0)
        {
            w = fm.width(speed);
            h = fm.height();
            painter.drawText(QPointF(x - w / 2,y + h/4),speed);
        }
    }

    painter.restore();
}

//绘制刻度
void CstmSpeedPanel::drawDividing(QPainter &painter)
{
    painter.save();
    painter.rotate(m_startAngle);//将坐标系顺时针旋转150°，到达起始位置

    QPen pen(Qt::white);
    painter.setPen(pen);

    int step = (m_maxSpeed - m_minSpeed) / 5;
    double angleStep = (360.0 - (m_startAngle - m_endAngle)) / step;

    for (int i = m_minSpeed; i <= m_maxSpeed; i += 5)
    {
        if (i >= 140){ //绘制红色
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }

        if (i % 20 == 0){//粗线
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawLine(88,0,75,0);

        }else if (i % 10 == 0){//中等
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawLine(88,0,80,0);

        }else if (i % 5 == 0){ //短线
            pen.setWidth(0);
            painter.setPen(pen);
            painter.drawLine(83,0,80,0);
        }
        painter.rotate(angleStep);
    }

    painter.restore();
}

void CstmSpeedPanel::drawNumberSpeed(QPainter &painter)
{
    painter.save();
    painter.setPen(Qt::white);
    QString speed = QString("%1 KM/H").arg(m_curSpeed);
    QFontMetricsF fm(this->font());
    qreal w = fm.size(Qt::TextSingleLine,speed).width();
    painter.drawText(-w/2,-20,speed);

    painter.restore();
}

void CstmSpeedPanel::drawIndicator(QPainter &painter)
{
    painter.save();
    //绘制指针

    double curAngle = m_startAngle + m_curSpeed * m_anglePerVel;
    painter.rotate(curAngle); //旋转坐标系

    QRadialGradient haloGradient(0, 0, 60, 0, 0);  //辐射渐变
    haloGradient.setColorAt(0, QColor(60,60,60));
    haloGradient.setColorAt(1, QColor(160,160,160)); //灰
    painter.setPen(Qt::white); //定义线条文本颜色  设置线条的颜色
    painter.setBrush(haloGradient);//刷子定义形状如何填满 填充后的颜色

    static const QPointF points[3] = {
        QPointF(0.0, 2),
        QPointF(0.0, -2),
        QPointF(70.0, 0),
    };
    painter.drawPolygon(points,3); //绘制指针
    painter.restore();

    painter.save();
    //绘制旋转中心
    QRadialGradient rg(0,0,10);
    rg.setColorAt(0.0,Qt::darkGray);
    rg.setColorAt(0.5,Qt::white);
    rg.setColorAt(1.0,Qt::darkGray);
    painter.setPen(Qt::NoPen);
    painter.setBrush(rg);
    painter.drawEllipse(QPoint(0,0),5,5);

    painter.restore();
}
