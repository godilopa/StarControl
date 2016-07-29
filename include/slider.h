#ifndef _SLIDER_H
#define _SLIDER_H

#include "control.h"
#include "string.h"
#include "types.h"
class Font;
class Image;

class CSlider : public AControl{
public:
	CSlider();
	~CSlider();
	bool Init(const String& name, uint16 x_pos, uint16 y_pos, const String& sliderImage, const String& ballImage, 
				int32 minval = -500, int32 maxval = 500);

	virtual void Update();
	virtual void Render();
	virtual bool OnEvent(Event e);

	uint16 GetX() const { return m_x; }
	uint16 GetY() const { return m_y; }
	double GetMinVal() const { return m_minval; }
	double GetMaxVal() const { return m_maxval; }
	double GetValue() const { return m_value; }
	void SetX(uint16 x) { m_x = x; }
	void SetY(uint16 y) { m_x = y; }
	void SetMinVal(double minval) { m_minval = minval; }
	void SetMaxVal(double maxval) { m_maxval = maxval; }
private:
	Font * m_font_name;
	String m_name;
	Image * m_sliderImage;
	Image * m_ballImage;
	uint16 m_x, m_y;
	uint16 m_ballX, m_ballY;
	double m_minval, m_maxval, m_value;
	bool m_onFocus;
	void ChangeBall();
	void ChangeValue();
};

#endif