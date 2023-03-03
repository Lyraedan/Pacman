#include "AudioPlayer.h"
#include <iostream>
#include <Windows.h>

bool AudioPlayer::PlayWav(const char * filename, bool loop)
{
	if(loop)
		return PlaySound(filename, NULL, SND_LOOP | SND_ASYNC);

	return PlaySound(filename, NULL, SND_ASYNC);
}

bool AudioPlayer::PlayWavOnce(char * filename, float audioLength, float audioLengthMul, int priority, bool loop)
{
	bool doPlay = false;
	if (priority >= currentSoundPriority) {
		SetCurrentPriority(priority);

		if (currentAudioFile != filename) {
			currentAudioPosition = 0;
			currentAudioFile = filename;
			currentSoundLength = audioLength;
			currentSoundMultiplier = audioLengthMul;
		}

		if (currentAudioPosition == 0) {
			doPlay = PlayWav(currentAudioFile, loop);
		}
	}

	currentAudioPosition++;
	if (currentAudioPosition >= currentSoundLength * currentSoundMultiplier) {
		currentAudioPosition = 0;
		SetCurrentPriority(0);
		currentAudioFile = "";
		currentSoundLength = 0;
		currentSoundMultiplier = 0;
	}
	return true;
}

bool AudioPlayer::Stop()
{
	currentAudioPosition = 0;
	currentSoundPriority = 0;
	currentAudioFile = "";
	currentSoundLength = 0;
	currentSoundMultiplier = 0;
	return PlaySound(NULL, NULL, 0);
}
