#ifndef BUTTON_H
#define BUTTON_H

#include "control.h"
#include "types.h"
#include "string.h"
class Image;

class CButton: public AControl{
public:
	CButton();
	~CButton();
	bool Init(const String name, uint16 x_pos, uint16 y_pos, const String& normalImage, const String& pushImage);

	virtual void Update();
	virtual void Render();
	virtual bool OnEvent(Event e);

	uint16 GetX() const { return m_x; }
	uint16 GetY() const { return m_y; }
	String GetName() const { return m_name; }
	void SetX(uint16 x) {  m_x = x; }
	void SetY(uint16 y) { m_x = y; }
private: //¿por qué protected en diapositivas?
	Image * m_normalImage;
	Image * m_pushImage;
	uint16 m_x, m_y;
	String m_name;
	bool m_onFocus;
};


#endif