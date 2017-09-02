#CstmChunkBattery

![CstmChunkBattery](../IMAGE/CstmChunkBattery.png)


<p> use the follow function to set the MAX value of the battery, default is 100.

	void setMaxValue(const qreal &maxValue);

<p> use the follow function to set the CURRENT value of the battery, default is 60.
	void setValue(const qreal &value);

<p> use the follow function to set the WARN value of the battery, default is 1/5 of the Max Value.While the CURRENT value is lower then
<p> the WARN value ,the brush color of the battery will change .

	 void setWarnValue(const qreal &warnValue);

<p> Those functions are setting the color of the battery.  you can set the frame color , header color , battery color and warn color.
<p> By default , the color of the frame and header are Black, the color of the battery is Green , the warn color is Red.

	void setWarnValueColor(const QColor &warnValueColor);
	void setBatteryColor(const QColor &batteryColor);
	void setFrameColor(const QColor &frameColor);
	void setHeaderColor(const QColor &headerColor);

<p> The follow function is to set if the color of the frame and header would change while the CURRENT value was lower than the WARN value.
<p> Default is True.

	void setFrameWidth(const qint32 &frameWidth);

<p> You can use the follow function to set the Radius of the round,Default is 20.

	void setRoundRadius(const qreal x, const qreal y);

<p> The function is setting the count of the chunk,default is 5, the min value is 1.The value can not  be lower than 1.
	
	void setChunkCount(const qint32 &chunkCount);

<p> The function is setting the ration of the chunk and the space between the chunks,default is 5 ,if the value lower than 1, the value will chage to 1.

	 void setChunkRatio(const qreal &chunkRatio);
*/
