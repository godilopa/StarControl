#include "../include/audiosource.h"
#include "../include/audiobuffer.h"
#include "../include/audiostream.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioSource::AudioSource(AudioBuffer * buffer)
{
	stream = nullptr;
	alGenSources(1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcef(source, AL_LOOPING, false);
	alSourcei(source, AL_BUFFER, buffer->GetBuffer());
}

AudioSource::AudioSource(const String& filename) 
{
	alGenSources(1, &source);
	stream = new AudioStream(filename, this);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcef(source, AL_LOOPING, false);
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &source);
}

void AudioSource::SetPitch(float pitch)
{
	alSourcef(source, AL_PITCH, pitch);
}

void AudioSource::SetGain(float gain)
{
	alSourcef(source, AL_GAIN, gain);
}

void AudioSource::SetLooping(bool loop)
{
	if (!stream) {
		alSourcef(source, AL_LOOPING, loop);
	}
	else {
		stream->SetLooping(true);
	}

}

void AudioSource::SetPosition(float x, float y, float z)
{
	alSource3f(source, AL_POSITION, x, y, z);
}

void AudioSource::SetVelocity(float x, float y, float z)
{
	alSource3f(source, AL_VELOCITY, x, y, z);
}

void AudioSource::Play()
{
	alSourcePlay(source);
}

void AudioSource::Stop()
{
	alSourceStop(source);
}

void AudioSource::Pause()
{
	alSourcePause(source);
}

bool AudioSource::IsPlaying() const
{
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return state;
}
