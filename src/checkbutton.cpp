#include "../include/checkbutton.h"
#include "../include/guimanager.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/image.h"
#include "../include/font.h"
#include "../include/math.h"

CCheckButton::CCheckButton(){
	m_onFocus = false;
	m_enabled = false;
	m_fontName = new Font("data/arial16.png");
	CGuiManager::Instance().AddControl(G_CLICK, this);
}

CCheckButton::~CCheckButton() {
	delete m_fontName;
	CGuiManager::Instance().DeleteControl(G_CLICK, this);
}

bool CCheckButton::Init(const String name, uint16 x_pos, uint16 y_pos, const String& checkedEnabled, const String& checkedDisabled){
	m_name = name;
	m_x = x_pos;
	m_y = y_pos;
	m_enabledImage = ResourceManager::Instance().LoadImage(checkedEnabled);
	m_enabledImage->SetMidHandle();
	m_disabledImage = ResourceManager::Instance().LoadImage(checkedDisabled);
	m_disabledImage->SetMidHandle();
	m_activeImage = m_disabledImage;
	return true;
}

void CCheckButton::Update(){
	//Comprobamos si el raton esta dentro de la imagen
	m_onFocus = PointInRect(CInputManager::Instance().GetMouseX(), CInputManager::Instance().GetMouseY(),
		m_x - m_activeImage->GetWidth() / 2, m_y - m_activeImage->GetHeight() / 2,
		m_activeImage->GetWidth(), m_activeImage->GetHeight());
}

void CCheckButton::Render(){
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	m_fontName->Render(m_name, m_x + 20, m_y - 10);
	Renderer::Instance().DrawImage(m_activeImage, m_x, m_y);
}

bool CCheckButton::OnEvent(Event e){
	if (m_onFocus){
		switch (e){
			case G_CLICK:
				SetButtonStatus(m_enabled);
				return false;
		}
	}

	return false;
}

void CCheckButton::SetButtonStatus(bool enabled){
	if (!enabled){
		m_activeImage = m_enabledImage;
		m_enabled = !enabled;
	}
	else{
		m_activeImage = m_disabledImage;
		m_enabled = !enabled;
	}
}

