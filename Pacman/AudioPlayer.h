class AudioPlayer {
	public:
		bool PlayWav(const char* filename, bool loop);
		bool PlayWavOnce(char* filename, float audioLength, float audioLengthMul, int priority, bool loop);
		bool Stop();

	private:
		float currentAudioPosition = 0;
		int currentSoundPriority = 0;
		float currentSoundLength = 0;
		float currentSoundMultiplier = 0;
		char* currentAudioFile = "";
};