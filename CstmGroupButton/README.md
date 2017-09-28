# CstmGroupButton 

![CstmGroupButton ](../IMAGE/CstmGroupButton .png)

<p> CstmGroupButton provide a control that likes a group of QRadioButton, but it can not set text, you can only set the the icon of every button.
<p> If you press a position of one of the button, it will emit a signal that the the button number。  The number is started from 0.


<p> You can custom the widget by those functions:

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
     void setButtonHeight(int value);
     void setButtonSelectedHeight(int value);
 
<p> You can also changed the button count and the current selected button:

	void setButtonCount(int value);  
    void setCurrentSelected(int value); //public slot

<p> If  you press at the position of the button, it will emit the signal:

     void signal_valueChanged(int buttonNumber);
