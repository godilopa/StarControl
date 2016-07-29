#ifndef RENDER_H
#define RENDER_H

#include "component.h"
class Sprite;
class String;
class Image;
class AudioBuffer;
class AudioSource;

class CRender : public Component{
public:
	CRender(CEntity * entity);
	void Init(const String& file, const String& entityName);
	virtual ~CRender();
	virtual void Update(double elapsed);
	virtual void ReceiveMessage(Message * msg);
private:
	void TrasladarEntidad();
	void DestruirEntidad();
	AudioSource * m_audioExplosion;
	AudioBuffer * m_audioBufferExplosion;
	Sprite * m_sprite;
	Image * m_explosionImage;

};

#endif