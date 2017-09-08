/*
 * This class provide a two handles slider .You have a very high degree of freedom to modify the various properties of the slider.
 *
 * You can use the function to set the slider is Horizontal or Vertical.
 *     void setIsHorizontal(bool value);
 *
 * You can set the thickness of the slider. If the slider is Horizontal the thickness holds the Height of the slider, of Width of the slider while is Vertical.
 * You can also the set Color of the slider and the Border,of course you can change the width of border .
 *     void setSliderThickness(int value);
 *     void setSliderColor(const QColor &value);
 *     void setBorderWidth(int value);
 *     void setBorderColor(const QColor &value);
 *
 * For the Handle. you can set the handle color, selected color, border color, shape, border width, handle width,hand height.
 *     void setHand1Color(const QColor &value);
 *     void setHand1SelectedColor(const QColor &value);
 *     void setHand1BorderColor(const QColor &value);
 *     void setHand1BorderWidth(int value);
 *     void setHand1Width(int value);
 *     void setHand1Height(int value);
 *     void setHand1Style(const SliderStyle &value);
 *
 *     void setHand2Color(const QColor &value);
 *     void setHand2SelectedColor(const QColor &value);
 *     void setHand2BorderColor(const QColor &value);
 *     void setHand2BorderWidth(int value);
 *     void setHand2Width(int value);
 *     void setHand2Height(int value);
 *     void setHand2Style(const SliderStyle &value);
 *
 * NOTE: If the shape of the handle is Circle, Only the height  is effective. You can set kindle of shaples to the two handles.
 *
 * You can set the Max and Min value. and you can also set the valus of the handles.
 *     void setMaxValue(double value);
 *     void setMinValue(double value);
 *     void setHand1Value(double value); //slot
 *     void setHand2Value(double value); //slot
 *
 * If you Press the space between the handles, the both handles would slide.
 * And also you can set the color between the handles, and the selected color.
 *     void setMidSelectedColor(const QColor &value);
 *     void setMidColor(const QColor &value);
 *
 * If the value of the handle changed , it would emit a signal.
 *     void signal_hand1ValueChanged(qreal value);
 *     void signal_hand2ValueChanged(qreal value);
 *
*/

#ifndef CSTMDOUBLEHANDLESLIDER_H
#define CSTMDOUBLEHANDLESLIDER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include <QColor>

enum SliderStyle
{
    SliderStyle_Rect,
    SliderStyle_Circle,
    SliderStyle_Ellipse
};

class CstmDoubleHandleSlider : public QWidget
{
	Q_OBJECT

public:
    CstmDoubleHandleSlider(QWidget *parent = 0);
    ~CstmDoubleHandleSlider();

    void setIsHorizontal(bool value);

    void setSliderThickness(int value);
    void setSliderColor(const QColor &value);
    void setBorderWidth(int value);
    void setBorderColor(const QColor &value);

    void setHand1Color(const QColor &value);
    void setHand1SelectedColor(const QColor &value);
    void setHand1BorderColor(const QColor &value);
    void setHand1BorderWidth(int value);
    void setHand1Width(int value);
    void setHand1Height(int value);
    void setHand1Style(const SliderStyle &value);

    void setHand2Color(const QColor &value);
    void setHand2SelectedColor(const QColor &value);
    void setHand2BorderColor(const QColor &value);
    void setHand2BorderWidth(int value);
    void setHand2Width(int value);
    void setHand2Height(int value);
    void setHand2Style(const SliderStyle &value);

    void setMaxValue(double value);
    void setMinValue(double value);

    void setMidSelectedColor(const QColor &value);
    void setMidColor(const QColor &value);

signals:
    void signal_hand1ValueChanged(qreal value);
    void signal_hand2ValueChanged(qreal value);

public slots:
    void setHand1Value(double value);
    void setHand2Value(double value);

protected:
    void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
    bool handle1Seleced;
    bool handle2Seleced;
    bool handleBothSeleced;

    void drawSlider(QPainter *painter);
    void drawSelect(QPainter *painter);
    void drawHandle1(QPainter *painter);
    void drawHandle2(QPainter *painter);

    qreal maxValue,minValue,hand1Value,hand2Value;
    qreal hand1_X,hand1_Y,hand2_X,hand2_Y;
    int sliderLength;

    bool isHorizontal;

    int borderWidth;
    QColor borderColor;
    QColor sliderColor;
    QColor midSelectedColor;
    QColor midColor;
    int sliderThickness;

    QColor hand1_Color;
    QColor hand1SelectedColor;
    QColor hand1BorderColor;
    int hand1BorderWidth;
    int hand1Width;
    int hand1Height;
    SliderStyle hand1Style;

    QColor hand2_Color;
    QColor hand2SelectedColor;
    QColor hand2BorderColor;
    int hand2BorderWidth;
    int hand2Width;
    int hand2Height;
    SliderStyle hand2Style;

    QPointF mousePressPoint;
    int sliderTopLeft_X, sliderTopLeft_Y;

    void updateValue();
    void updateAfterSetValue();
};

#endif // CSTMDOUBLEHANDLESLIDER_H
