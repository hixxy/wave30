#ifndef _WAVEFILE_H_
#define _WAVEFILE_H_

#include <string>
#include <vector>

typedef signed short BitDepth;
typedef std::vector<BitDepth> AudioBuffer;

class WaveFile {
public :
	WaveFile(const char* filename);

	void write();
	void test_fillWithMetronome();// Burp
	void open(const char* filename);

	const static unsigned short tempo		= 170;
	const static unsigned long	sampleRate	= 44100;
	const static unsigned short channels	= 2;
	//const static unsigned short numBuffers	= 1;
	double bufferSize;

	AudioBuffer buffer;
	std::string name;

};

#endif