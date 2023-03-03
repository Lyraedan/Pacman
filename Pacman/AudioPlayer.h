class AudioPlayer {
	public:
		bool PlayWav(const char* filename);
		bool PlayWavOnce(char* filename, float audioLength, float audioLengthMul);

	private:
		float currentAudioPosition = 0;
		char* currentAudioFile = "";
};