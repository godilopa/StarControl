#ifndef SA_GAMEOVER_H
#define SA_GAMEOVER_H

#include "AppState.h"
#include "iobserver.h"
class CSlider;
class Font;

class SA_GameOver : public AppState, public IEventObserver {
public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
	virtual bool OnEvent(Event e);
private:
	Font * m_font;
	CSlider * m_slider;
};

#endif