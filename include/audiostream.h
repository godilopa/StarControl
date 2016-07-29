#ifndef UGINE_AUDIOSTREAM_H
#define UGINE_AUDIOSTREAM_H

#include "array.h"
#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb_vorbis.c"
class String;
class AudioSource;


class AudioStream {
public:
	AudioStream(const String& filename, AudioSource* source);
	~AudioStream();
	void SetLooping(bool looping) { shouldLoop = looping; }
	static void UpdateAll();
protected:
	void Update();
	bool Stream(unsigned int buffer);
private:
	static Array<AudioStream*> streams;
	AudioSource* source;
	stb_vorbis* stream;
	stb_vorbis_info info;
	unsigned int buffers[2];
	size_t samplesLeft;
	bool shouldLoop;
};


#endif
