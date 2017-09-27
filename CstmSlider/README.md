# CstmSlider 

![CstmSlider ](../IMAGE/CstmSlider .png)


CstmSlider is a slider with  an arrow that customed .
<p> You can custom the slider by using those functions:

     void setSliderHeight(int value);
     void setSliderColor(const QColor &value);
     void setSliderBorderColor(const QColor &value);
     void setSliderBorderWidth(int value);

<p> You can custom the handle by those functions:

     void setHandleRadius(int value);
     void setHandleColor(const QColor &value);
     void setHandleBorderColor(const QColor &value);
     void setHandleBorderWidth(int value);

 You can also custom the arrow , the arrow is showing the direction of moving.

     void setArrowColor(const QColor &value);
     void setArrowWidth(int value);

<p> And you maybe need to set the Max value and the Min Value.You can set the current value, and the function is a slot.
<p> Also,  you can also set the slider color between the start position with the current position of handle.

     void setMinValue(int value);
     void setMaxValue(int value);
     void setValueColor(const QColor &value);
     void setCurrentValue(int value);

<p> While you changed the value by move the handle,  a signal would be emited.

     void signal_valueChanged(int value);