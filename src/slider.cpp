#include "../include/slider.h"
#include "../include/guimanager.h"
#include "../include/resourcemanager.h"
#include "../include/renderer.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/font.h"
#include "../include/screen.h"

CSlider::CSlider(){
	m_onFocus = false;
	m_font_name = new Font("data/arial16.png");
}

CSlider::~CSlider() {
	CGuiManager::Instance().DeleteControl(G_CLICK, this);
	CGuiManager::Instance().DeleteControl(G_DRAG, this);
	delete m_font_name;
}

bool CSlider::Init(const String& name, uint16 x_pos, uint16 y_pos, const String& sliderImage, const String& ballImage,
					int32 minval, int32 maxval){
	m_name = name;
	m_sliderImage = ResourceManager::Instance().LoadImage(sliderImage);
	m_ballImage = ResourceManager::Instance().LoadImage(ballImage);
	m_ballImage->SetMidHandle();
	m_x = x_pos;
	m_y = y_pos;
	m_ballX = x_pos;
	m_ballY = y_pos;
	m_minval = minval;
	m_maxval = maxval;
	CGuiManager::Instance().AddControl(G_CLICK, this);
	CGuiManager::Instance().AddControl(G_DRAG, this);
	return true;

}

void CSlider::ChangeBall(){ 
	if (CInputManager::Instance().GetMouseX() >= m_x && CInputManager::Instance().GetMouseX() <= m_x + m_sliderImage->GetWidth()){
		m_ballX = CInputManager::Instance().GetMouseX();
		ChangeValue();
	}
}

void CSlider::ChangeValue(){
	double x1 = m_x;
	double x2 = m_x + m_sliderImage->GetWidth();
	double y1 = m_minval;
	double y2 = m_maxval;
	m_value = y1 + (y2 - y1) / (x2 - x1) * (m_ballX - x1);
}

void CSlider::Update(){
	//Comprobamos si el raton esta dentro de la imagen
	m_onFocus = PointInRect(CInputManager::Instance().GetMouseX(), CInputManager::Instance().GetMouseY(),
							m_x, m_y, m_sliderImage->GetWidth(), m_sliderImage->GetHeight());
}

void CSlider::Render(){
	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	m_font_name->Render(m_name, m_x + 60, m_y - 20);
	Renderer::Instance().DrawImage(m_sliderImage, m_x, m_y);
	Renderer::Instance().DrawImage(m_ballImage, m_ballX, m_ballY);
}

bool CSlider::OnEvent(Event e){
	if (m_onFocus){
		switch (e){
			case G_CLICK:
				ChangeBall();
				return false;
			case G_DRAG:
				ChangeBall();
				return false;
		}
	}

	return false;
}