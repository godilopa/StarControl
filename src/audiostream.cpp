#include "../include/audiostream.h"
#include "../include/audiosource.h"
#include "../include/string.h"
#include "AL/al.h"
#include "AL/alc.h"

Array<AudioStream*> AudioStream::streams;

AudioStream::AudioStream(const String & filename, AudioSource * source)
{

	buffers[0] = buffers[1] = 0;
	AudioStream::source = source;
	stream = stb_vorbis_open_filename(filename.ToCString(), nullptr, nullptr);
	if (!stream) return;
	info = stb_vorbis_get_info(stream);
	samplesLeft = stb_vorbis_stream_length_in_samples(stream) * info.channels;
	alGenBuffers(2, buffers);
	Stream(buffers[0]);
	Stream(buffers[1]);
	alSourceQueueBuffers(AudioStream::source->GetID(), 2, buffers);
	streams.Add(this);
}

AudioStream::~AudioStream()
{
	AudioStream* delThis = this;
	stb_vorbis_close(stream);
	streams.Remove(delThis);
	alDeleteBuffers(2, buffers);
}

void AudioStream::UpdateAll()
{
	for (int i = 0; i < streams.Size(); i++) {
		streams[i]->Update();
	}
}

void AudioStream::Update()
{	//Hacer con variable auxiliar
	ALint buffersProcessed;
	alGetSourcei(source->GetID(), AL_BUFFERS_PROCESSED, &buffersProcessed);
	while (buffersProcessed--) {
		uint32 buffer;
		alSourceUnqueueBuffers(source->GetID(), 1, &buffer);
		if (Stream(buffer)) {
			alSourceQueueBuffers(source->GetID(), 1, &buffer);
		}
		else if (shouldLoop) {
			stb_vorbis_seek_start(stream);
			samplesLeft = stb_vorbis_stream_length_in_samples(stream) * info.channels;
			if (Stream(buffer)) alSourceQueueBuffers(source->GetID(), 1, &buffer);
		}
	}
}

bool AudioStream::Stream(unsigned int buffer)
{
	ALenum format;
	if (info.channels == 1) {
		format = AL_FORMAT_MONO16;
	}
	else {
		format = AL_FORMAT_STEREO16;
	}

	int16 pcm[32768];
	int size = stb_vorbis_get_samples_short_interleaved(stream, info.channels, pcm, 32768);
	if (!size) {
		return false;
	}
	else {
		alBufferData(buffer, format, pcm, size * info.channels * sizeof(short), info.sample_rate);
		samplesLeft -= size;
		return true;
	}


}
