/*
 * CstmSliderSwitch is a switch control, you can click the switch to change the status.
 *
 * You can use the function to change the status,and the function is a slot .
 *     void setSwitchStatus(bool value);
 *
 * The control emit a signal while the status changed by click.
 * void StateChanged(bool state);
 *
 * You can custom the switch by those functions :
 *     void setSwitchIsRounded(bool value);
 *     void setSwitchBorderCorlor(const QColor &value);
 *     void setSwitchBorderWidth(int value);
 *     void setSliderCorlor(const QColor &value);
 *     void setSliderBorderCorlor(const QColor &value);
 *     void setSliderBorderWidth(int value);
 *     void setOnStateCorlor(const QColor &value);
 *     void setOffStateCorlor(const QColor &value);
 *     void setOnStateString(const QString &value);
 *     void setOffStateString(const QString &value);
 *     void setTextCorlor(const QColor &value);
 *     void setTextfont(const QFont &value);
 *
*/

#ifndef CSTMSLIDERSWITCH_H
#define CSTMSLIDERSWITCH_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>


class CstmSliderSwitch : public QWidget
{
    Q_OBJECT
private:
    bool  isRounded;
    QColor onStateCorlor;
    QColor offStateCorlor;
    QColor sliderCorlor;
    QColor textCorlor;
    QFont textfont;
    QString onStateString;
    QString offStateString;
    bool switchState;
    int switchBorderWidth;
    int sliderBorderWidth;
    QColor switchBorderCorlor;
    QColor sliderBorderCorlor;

public:
    CstmSliderSwitch(QWidget *parent = 0);
    void setSwitchIsRounded(bool value);
    void setOnStateCorlor(const QColor &value);
    void setOffStateCorlor(const QColor &value);
    void setOnStateString(const QString &value);
    void setOffStateString(const QString &value);
    void setSliderCorlor(const QColor &value);
    void setTextCorlor(const QColor &value);
    void setTextfont(const QFont &value);

    void setSwitchBorderWidth(int value);
    void setSliderBorderWidth(int value);
    void setSwitchBorderCorlor(const QColor &value);
    void setSliderBorderCorlor(const QColor &value);

public slots:
    void setSwitchStatus(bool value);

signals:
    void StateChanged(bool state);

protected:
    virtual void	mousePressEvent(QMouseEvent * event);
    virtual void	paintEvent(QPaintEvent *event);

protected:
    void drawBackground(QPainter *painter, QRect &rect, bool state);
    void drawText(QPainter *painter, QRect &rect, bool state);
    void drawSlider(QPainter *painter, QRect &rect, bool state);
};

#endif // CSTMSLIDERSWITCH_H
