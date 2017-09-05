#ifndef CSTMTIMEPANEL_H
#define CSTMTIMEPANEL_H

#include <QWidget>

#include <QTimerEvent>
#include <QPaintEvent>
#include <QPainter>

#include<QTime>

class CstmTimepanel : public QWidget
{
    Q_OBJECT
public:
    explicit CstmTimepanel(QWidget *parent = 0);
    ~CstmTimepanel();

protected:
    int timeId;
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    bool flag;

    void drawInit();
    void drawBackground(QPainter *);
    void drawTray(QPainter *);
    void drawIndicatorCenter(QPainter *);
    void drawIndicatorHour(QPainter *);
    void drawIndicatorMinute(QPainter *);
    void drawIndicatorSecond(QPainter *);
    void drawTimeShow(QPainter *);

private:
    QPointF centerPol;
    float halfLen;
    float backgroundOutRadius, backgroundInnerRadius;
    float trayOutRadius, trayInnerRadius, trayBetweenRadius;
    float hourIndicatorLen, minuteIndicatorLen, secondIndicaetorLen;
    float centerCircle;
    float timeTextLen;

    unsigned int colorNum1,colorNum2;

    QTime timeValue;

    QColor color_CentralPoint,
    color_CentralPanel,
    color_Margin,
    color_5Minute,
    color_perMinute,
    color_IndicatorHour,
    color_IndicatorMinute,
    color_IndicatorSecond;

    enum Item{
        item_CentralPoint,
        item_CentralPanel,
        item_Margin,
        item_5Minute,
        item_perMinute,
        item_IndicatorHour,
        item_IndicatorMinute,
        item_IndicatorSecond,
    };

    void setColor(Item item,QColor color);

};

#endif // CSTMTIMEPANEL_H
