#ifndef UGINE_AUDIOSOURCE_H
#define UGINE_AUDIOSOURCE_H

class String;
class AudioBuffer;
class AudioStream;

class AudioSource {
public:
	AudioSource(AudioBuffer* buffer);
	AudioSource(const String& filename);
	~AudioSource();
	void SetPitch(float pitch);
	void SetGain(float gain);
	void SetLooping(bool loop);
	void SetPosition(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	unsigned int GetID() { return source; }
	void Play();
	void Stop();
	void Pause();
	bool IsPlaying() const;
private:
	unsigned int source;
	AudioStream* stream;
};

#endif