#ifndef SA_PLAYING_H
#define SA_PLAYING_H

#include "AppState.h"

class SA_Playing : public AppState{
public:
	virtual void Run();
	virtual void Draw();
	virtual void ProcessInput();
	virtual void Activate();
	virtual void Deactivate();
private:

};

#endif
