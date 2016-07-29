#ifndef UGINE_AUDIOLISTENER_H
#define UGINE_AUDIOLISTENER_H

class Listener {
public:
	static Listener& Instance();
	void SetPosition(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void SetOrientation(float x, float y, float z);
protected:
	Listener();
	~Listener() {}
private:
	static Listener* listener;
};

#endif
