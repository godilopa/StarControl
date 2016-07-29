#ifndef APPSTATE_H
#define APPSTATE_H

class AppState {
public:
	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void ProcessInput() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};

#endif
