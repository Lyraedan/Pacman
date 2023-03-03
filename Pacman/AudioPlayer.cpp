#include "AudioPlayer.h"
#include <iostream>
#include <Windows.h>

bool AudioPlayer::PlayWav(const char * filename)
{
	return PlaySound(filename, NULL, SND_ASYNC);
}

bool AudioPlayer::PlayWavOnce(char * filename, float audioLength, float audioLengthMul)
{
	bool doPlay = false;
	if (currentAudioFile != filename) {
		currentAudioPosition = 0;
		currentAudioFile = filename;
	}

	if (currentAudioPosition == 0) {
		doPlay = PlayWav(currentAudioFile);
	}
	currentAudioPosition++;
	if (currentAudioPosition >= audioLength * audioLengthMul) {
		currentAudioPosition = 0;
		currentAudioFile = "";
	}
	return true;
}
