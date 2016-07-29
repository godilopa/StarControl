#include "../include/audiobuffer.h"
#include "../include/string.h"
#include "../include/file.h"
#include "AL/al.h"
#include "AL/alc.h"

#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb_vorbis.c"

AudioBuffer::AudioBuffer(const String & filename):alBuffer(0)
{

	if (filename.ExtractExt() == "wav") {

		alGenBuffers(1, &alBuffer);
		File file(filename, FILE_READ);
		file.Seek(16);
		uint32 fmtChunkSize;
		file.ReadBytes(&fmtChunkSize, 4);
		uint16 audioFormat;
		file.ReadBytes(&audioFormat, 2);
		uint16 channels;
		file.ReadBytes(&channels, 2);
		file.Seek(24);
		uint32 sampleRate;
		file.ReadBytes(&sampleRate, 4);
		file.Seek(34);
		uint16 bitsPerSample;
		file.ReadBytes(&bitsPerSample, 2);
		uint16 extraParamSize;
		if (fmtChunkSize != 16) {
			file.ReadBytes(&extraParamSize, 2);
			file.Seek(38 + extraParamSize);
		}
		char texto[5];
		texto[4] = '\0';

		while (String(texto) != "data") {

			file.ReadBytes(texto, 4);
		}

		uint32 dataSize;
		uint32* data;
		file.ReadBytes(&dataSize, 4);
		data = (uint32*)malloc(dataSize);
		file.ReadBytes(data, dataSize);

		ALenum format;

		if (bitsPerSample == 8) {
			if (channels == 1) {
				format = AL_FORMAT_MONO8;
			}
			else {
				format = AL_FORMAT_STEREO8;
			}
		}

		if (bitsPerSample == 16) {
			if (channels == 1) {
				format = AL_FORMAT_MONO16;
			}
			else {
				format = AL_FORMAT_STEREO16;
			}
		}

		alBufferData(alBuffer, format, data, dataSize, sampleRate);
		free(data);
	}
	else if (filename.ExtractExt() == "ogg") {
		stb_vorbis* stb_vorbis;

		stb_vorbis = stb_vorbis_open_filename(filename.ToCString(), nullptr, nullptr);
		if (stb_vorbis == nullptr) return;

		stb_vorbis_info info = stb_vorbis_get_info(stb_vorbis);
		uint32 dataSize = stb_vorbis_stream_length_in_samples(stb_vorbis) *  info.channels;
		int16* buffer = (int16*)malloc(dataSize  * sizeof(uint16));
		stb_vorbis_get_samples_short_interleaved(stb_vorbis, info.channels,(short *) buffer, dataSize);
		alGenBuffers(1, &alBuffer);
		ALenum format;
		if (info.channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else {
			format = AL_FORMAT_STEREO16;
		}
		alBufferData(alBuffer, format, buffer, dataSize * sizeof(int16), info.sample_rate);
		free(buffer);
		stb_vorbis_close(stb_vorbis);
	}




}

AudioBuffer::~AudioBuffer(void)
{
	alDeleteBuffers(1, &alBuffer);
}


