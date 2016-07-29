#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include "control.h"
#include "types.h"
#include "string.h"
class Font;
class Image;

class CCheckButton: public AControl{
public:
	CCheckButton();
	~CCheckButton();
	bool Init(const String name, uint16 x_pos, uint16 y_pos, const String& checkedDisabled, const String& checkedEnabled);

	virtual void Update();
	virtual void Render();
	virtual bool OnEvent(Event e);

	uint16 GetX() const { return m_x; }
	uint16 GetY() const { return m_y; }
	String GetName() const { return m_name; }
	bool GetEnabled() const { return m_enabled; }
	void SetX(uint16 x) { m_x = x; }
	void SetY(uint16 y) { m_x = y; }
	void SetEnabled(bool enabled) { m_enabled = enabled; }
private:
	void SetButtonStatus(bool enabled);
	bool m_enabled;
	Font * m_fontName;
	Image * m_enabledImage;
	Image * m_disabledImage;
	Image * m_activeImage;
	uint16 m_x, m_y;
	String m_name;
	bool m_onFocus;
};


#endif