#ifndef SA_OPTIONS_H
#define SA_OPTIONS_H

#include "AppState.h"
#include "iobserver.h"
#include "eventsconstants.h"
class CCheckButton;
class Font;

class SA_Options : public AppState, public IEventObserver {
public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:
	Font * m_font;
	CCheckButton * m_enemyAvatarCheckButton;
	CCheckButton * m_enemyDreadnoughtCheckButton;
	CCheckButton * m_playerAvatarCheckButton;
	CCheckButton * m_playerDreadnoughtCheckButton;
	bool ToGame();
	bool OnEvent(Event e);
};

#endif