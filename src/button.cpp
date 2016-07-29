#include "../include/button.h"
#include "../include/guimanager.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/image.h"
#include "../include/math.h"

CButton::CButton(){
	CGuiManager::Instance().AddControl(G_CLICK, this);
	m_onFocus = false;
}

CButton::~CButton() {
	CGuiManager::Instance().DeleteControl(G_CLICK, this);
}

bool CButton::Init(const String name, uint16 x_pos, uint16 y_pos, const String& normalImage, const String& pushImage){
	m_name = name;
	m_x = x_pos;
	m_y = y_pos;
	m_normalImage = ResourceManager::Instance().LoadImage(normalImage);
	m_normalImage->SetMidHandle();
	m_pushImage = ResourceManager::Instance().LoadImage(pushImage);
	m_pushImage->SetMidHandle();
	return true;
}

void CButton::Update(){
	//Comprobamos si el raton esta dentro de la imagen
	m_onFocus = PointInRect(CInputManager::Instance().GetMouseX(), CInputManager::Instance().GetMouseY(),
		m_x - m_normalImage->GetWidth() / 2, m_y - m_normalImage->GetHeight() / 2,
		m_normalImage->GetWidth(), m_normalImage->GetHeight());
}

void CButton::Render(){
	if (!m_onFocus){
		Renderer::Instance().DrawImage(m_normalImage, m_x, m_y);
	}
	else if (m_onFocus){
		Renderer::Instance().DrawImage(m_pushImage, m_x, m_y);
	}
}

bool CButton::OnEvent(Event e){
	if (m_onFocus){ //Take into account events if the focus is on the button
		switch (e){
			case G_CLICK:
				for (uint32 i = 0; i < m_observers.Size(); i++){
					return m_observers[i]->OnEvent(e);
				}

			return false;
		}
	}

	return false;
}