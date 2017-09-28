/*
 * CstmGroupButton provide a control that likes a group of QRadioButton, but it can not set text, you can only set the the icon of every button.
 * If you press a position of one of the button, it will emit a signal that the the button number。  The number is started from 0.
 *
 *
 * You can custom the widget by those functions:
 *     void setButtonSelectedColor(const QColor &value);
 *     void setButtonColor(const QColor &value);
 *     void setBorderWidth(int value);
 *     void setBorderSelectedWidth(int value);
 *     void setBorderColor(const QColor &value);
 *     void setBorderSelectedColor(const QColor &value);
 *     void setBorderRadius(int value);
 *     void setSelectedBorderRadius(int value);
 *     void setIconWidth(int value);
 *     void setIconHeight(int value);
 *     void setButtonHeight(int value);
 *     void setButtonSelectedHeight(int value);
 *
 * You can also changed the button count and the current selected button:
 *     void setButtonCount(int value);
 *     void setCurrentSelected(int value); //public slot
 *
 * If  you press at the position of the button, it will emit the signal:
 *     void signal_valueChanged(int buttonNumber);
 *
 *
*/


#ifndef CSTMGROUPBUTTON_H
#define CSTMGROUPBUTTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <QPixmap>

class CstmGroupButton : public QWidget
{
    Q_OBJECT
public:
    explicit CstmGroupButton(QWidget *parent = nullptr);

    void setButtonIcon(const int buttonNumber,const QPixmap &pixmap);

    void setButtonSelectedColor(const QColor &value);
    void setButtonColor(const QColor &value);
    void setBorderWidth(int value);
    void setBorderSelectedWidth(int value);
    void setBorderColor(const QColor &value);
    void setBorderSelectedColor(const QColor &value);
    void setBorderRadius(int value);
    void setSelectedBorderRadius(int value);
    void setIconWidth(int value);
    void setIconHeight(int value);

    void setButtonCount(int value);
    void setButtonHeight(int value);
    void setButtonSelectedHeight(int value);

signals:
    void signal_valueChanged(int buttonNumber);

public slots:
    void setCurrentSelected(int value);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    //border
    int borderWidth;
    int borderSelectedWidth;
    QColor borderColor;
    QColor borderSelectedColor;
    int BorderRadius;
    int SelectedBorderRadius;

    //size
    int buttonCount;
    int buttonHeight;
    int buttonSelectedHeight;
    int iconWidth;
    int iconHeight;

    QColor buttonColor;
    QColor buttonSelectedColor;

    int currentSelected;
private:
    QList<QPixmap> listButtonPixmap;
    QList<int> listButtonPixmapID;

    int buttonWidth;
    int centerY;
    void updateButtonParameter();

    void drawAllButton(QPainter* painter);
    void drawSelectedButton(QPainter* painter);
    void drawPixmap(QPainter* painter);
};

#endif // CSTMGROUPBUTTON_H
