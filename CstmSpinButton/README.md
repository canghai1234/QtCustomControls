# CstmSpinButton

![CstmSpinButton](../IMAGE/CstmSpinButton.png)

<p>CstmSpinButton is a widget like QSpinBox , but the CstmSpinButton does not have a Label Or a input Control.
<p>CstmSpinButton like a button. It emit a signal while the Minus Button was clicked, and it will emit press signal while it was pressed, and emit a release signal while released.
<p>To use this Customed Control, It's better that set the width of the widget greater than the height.Or it won't work as you expected.And the width must be twice ot more as the height.
<p>And also, You'd better use the function "setFixSize(int w,int h)" Or "setFixSize(QSize size)" to set the size of the widget.
<p>
<p>You can use those functions to custom the control.

	void setButtonWidth(int value);
	void setSymbolWidth(int value);
	void setFixedSize(int w,int h);
	void setFixedSize(QSize size);
	void setSpaceColor(const QColor &value);
	void setBackgroundColor(const QColor &value);
	void setBorderColor(const QColor &value);
	void setBorderWidth(int value);


<p>And those functions to custom the Minus Button and the Plus Button .

	void setMinusButtonColor(const QColor &value);
	void setMinusButtonClickColor(const QColor &value);
	void setMinusColor(const QColor &value);
	void setMinusClickColor(const QColor &value);
	void setPlusButtonColor(const QColor &value);
	void setPlusButtonClickColor(const QColor &value);
	void setPlusColor(const QColor &value);
	void setPlusClickColor(const QColor &value); 