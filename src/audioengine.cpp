#include "../include/audioengine.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioEngine* AudioEngine::engine = nullptr;

AudioEngine & AudioEngine::Instance()
{
	if (!engine)
		engine = new AudioEngine();
	return *engine;
}

void AudioEngine::Init()
{
	device = alcOpenDevice(nullptr);
	context = alcCreateContext((ALCdevice*)device, nullptr);
	alcMakeContextCurrent((ALCcontext*)context);
}

void AudioEngine::Finish()
{
	alcDestroyContext((ALCcontext*)context);
	alcCloseDevice((ALCdevice*)device);
}

AudioEngine::~AudioEngine(void)
{
}
