#ifndef SA_MENU_H
#define SA_MENU_H

#include "AppState.h"
#include "iobserver.h"
#include "eventsconstants.h"
class CButton;
class Image;

class SA_Menu : public AppState, public IEventObserver{
public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:
	Image * m_title;
	CButton * m_buttonPlay;
	bool OnEvent(Event e);
};

#endif
