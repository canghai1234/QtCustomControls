#ifndef CSTMSPEEDPANEL_H
#define CSTMSPEEDPANEL_H

/*
 This widget was created by flist ( https://github.com/flistliu )

*/

#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

class CstmSpeedPanel : public QWidget
{
    Q_OBJECT

public:
    CstmSpeedPanel(QWidget *parent = 0);
    ~CstmSpeedPanel();

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void setCurentSpeed(int speed);

private:
    void drawFrame(QPainter& painter);//绘制边框与背景
    void drawNumberIndicator(QPainter& painter);//绘制指示数字
    void drawDividing(QPainter& painter);//绘制刻度
    void drawNumberSpeed(QPainter &painter);//显示数字速度
    void drawIndicator(QPainter& painter);//绘制速度指针

private:
    int m_startAngle;
    int m_endAngle;

    int m_refSize; //绘制的参考大小
    int m_radius;

    int m_minSpeed;
    int m_maxSpeed;
    int m_curSpeed;
    double m_anglePerVel;//每KM 对应的 角度

    QLCDNumber *m_lcd_Mileage;//显示总里程
    QLabel *m_lbl_Mileage;
    QHBoxLayout* m_layout_mileage;
    QWidget* m_wgt_mileage;
};

#endif // CSTMSPEEDPANEL_H
