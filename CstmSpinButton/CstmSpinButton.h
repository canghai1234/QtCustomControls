/*
 * CstmSpinButton is a widget like QSpinBox , but the CstmSpinButton does not have a Label OR a input Control.
 * CstmSpinButton like a button. It emit a signal while the Minus Button was clicked, and it will emit press signal
 * while it was pressed, and emit a release signal while released.
 *
 * To use this Customed Control, It's better that set the width of the widget greater than the height.Or it won't work
 * as you expected.And the width must be twice ot more as the height.
 *
 * And also, You'd better use the function "setFixSize(int w,int h)" Or "setFixSize(QSize size)" to set the size of the widget.
 *
 * You can use those functions to custom the control.
 *     void setButtonWidth(int value);
 *     void setSymbolWidth(int value);
 *     void setFixedSize(int w,int h);
 *     void setFixedSize(QSize size);
 *     void setSpaceColor(const QColor &value);
 *     void setBackgroundColor(const QColor &value);
 *     void setBorderColor(const QColor &value);
 *     void setBorderWidth(int value);
 *
 *
 * And those functions to custom the Minus Button and the Plus Button .
 *     void setMinusButtonColor(const QColor &value);
 *     void setMinusButtonClickColor(const QColor &value);
 *     void setMinusColor(const QColor &value);
 *     void setMinusClickColor(const QColor &value);
 *     void setPlusButtonColor(const QColor &value);
 *     void setPlusButtonClickColor(const QColor &value);
 *     void setPlusColor(const QColor &value);
 *     void setPlusClickColor(const QColor &value);
 *
*/



#ifndef CSTMSPINBUTTON_H
#define CSTMSPINBUTTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class CstmSpinButton : public QWidget
{
    Q_OBJECT
public:
    explicit CstmSpinButton(QWidget *parent = nullptr);

    void setButtonWidth(int value);
    void setSymbolWidth(int value);
    void setFixedSize(int w,int h);
    void setFixedSize(QSize size);

    void setSpaceColor(const QColor &value);
    void setBackgroundColor(const QColor &value);
    void setBorderColor(const QColor &value);
    void setBorderWidth(int value);

    void setMinusButtonColor(const QColor &value);
    void setMinusButtonClickColor(const QColor &value);
    void setMinusColor(const QColor &value);
    void setMinusClickColor(const QColor &value);

    void setPlusButtonColor(const QColor &value);
    void setPlusButtonClickColor(const QColor &value);
    void setPlusColor(const QColor &value);
    void setPlusClickColor(const QColor &value);

signals:
    void signal_minusPressed();
    void signal_minusReleased();
    void signal_minusClicked();
    void signal_plusPressed();
    void signal_plusReleased();
    void signal_plusClicked();

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void drawMinusButton(QPainter* painter);
    void drawMinusSymbol(QPainter* painter);
    void drawPlusButton(QPainter* painter);
    void drawPlusSymbol(QPainter* painter);

    int buttonWidth;
    int borderWidth;
    int symbolWidth;
    QColor backgroundColor;
    QColor minusButtonColor;
    QColor minusButtonClickColor;
    QColor minusColor;
    QColor minusClickColor;
    QColor plusButtonColor;
    QColor plusButtonClickColor;
    QColor plusColor;
    QColor plusClickColor;
    QColor spaceColor;
    QColor borderColor;



    bool minusPressed , plusPressed;
};

#endif // CSTMSPINBUTTON_H
