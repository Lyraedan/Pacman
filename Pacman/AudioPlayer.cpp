#include "AudioPlayer.h"
#include <iostream>
#include <Windows.h>

bool AudioPlayer::PlayWav(const char * filename)
{
	return PlaySound(filename, NULL, SND_SYNC);
}
