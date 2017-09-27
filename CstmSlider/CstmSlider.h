/*
 * CstmSlider is a slider with  an arrow that customed .
 *
 * You can custom the slider by using those functions:
 *     void setSliderHeight(int value);
 *     void setSliderColor(const QColor &value);
 *     void setSliderBorderColor(const QColor &value);
 *     void setSliderBorderWidth(int value);
 *
 * You can custom the handle by those functions:
 *     void setHandleRadius(int value);
 *     void setHandleColor(const QColor &value);
 *     void setHandleBorderColor(const QColor &value);
 *     void setHandleBorderWidth(int value);
 *
 * You can also custom the arrow , the arrow is showing the direction of moving.
 *     void setArrowColor(const QColor &value);
 *     void setArrowWidth(int value);
 *
 * And you maybe need to set the Max value and the Min Value.You can set the current value, and the function is a slot.
 * Also,  you can also set the slider color between the start position with the current position of handle.
 *     void setMinValue(int value);
 *     void setMaxValue(int value);
 *     void setValueColor(const QColor &value);
 *     void setCurrentValue(int value);
 *
 * While you changed the value by move the handle,  a signal would be emited.
 *     void signal_valueChanged(int value);
 *
*/

#ifndef CSTMSLIDER_H
#define CSTMSLIDER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class CstmSlider : public QWidget
{
    Q_OBJECT

public:
    CstmSlider(QWidget *parent = 0);
    ~CstmSlider();

    void setValueColor(const QColor &value);
    void setSliderHeight(int value);
    void setSliderColor(const QColor &value);
    void setSliderBorderColor(const QColor &value);
    void setSliderBorderWidth(int value);

    void setMinValue(int value);
    void setMaxValue(int value);

    void setHandleRadius(int value);
    void setHandleColor(const QColor &value);
    void setHandleBorderColor(const QColor &value);
    void setHandleBorderWidth(int value);

    void setArrowColor(const QColor &value);
    void setArrowWidth(int value);

signals:
    void signal_valueChanged(int value);

public slots:
    void setCurrentValue(int value);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:


    void drawSlider(QPainter* painter);
    void drawHander(QPainter* painter);
    void drawArrow(QPainter* painter);
    void drawValue(QPainter* painter);
private:
    //value
    int minValue;
    int maxValue;
    int currentValue;
    QColor valueColor;
    //slider
    int sliderHeight;
    QColor sliderColor;
    QColor sliderBorderColor;
    int sliderBorderWidth;

    //handle
    int handleRadius;
    QColor handleColor;
    QColor handleBorderColor;
    int handleBorderWidth;
    QColor arrowColor;
    int arrowWidth;

    //class various
    bool isIncrease;
    bool handleIsPress;
    QPointF mousePressPoint;
    double centerPointerX;
    int midPos;
    int widgetWidth;

};

#endif // CSTMSLIDER_H
