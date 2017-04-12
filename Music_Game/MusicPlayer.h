#pragma once

#include "fmod.hpp"

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();

	void setSound(char* fileName);
	void play();
	void update();

private:

	FMOD::System     *system;
	FMOD::Sound      *sound = 0;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT       result;
	unsigned int version;

	FMOD::DSP *spectrumDSP;
	FMOD_DSP_PARAMETER_FFT *fftparameter;

	unsigned int len = 1024;

	void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
	#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)
};



