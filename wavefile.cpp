#include <limits>
#include <iostream>
#include <fstream>
#include "wavefile.h"

WaveFile::WaveFile(const char* filename) {
	name=filename;
	bufferSize=(4.0/((double)tempo/60.0))*(4.0*(double)sampleRate);
	buffer=AudioBuffer((size_t)bufferSize);
}

template<typename _Ty> void write(std::ofstream& stream, const _Ty& ty) {
	stream.write((const char*)&ty, sizeof(_Ty));
}

void printa(char a[]) {//I don't even care
	for(unsigned i=0; i<4; ++i) {
		std::cout << a[i];
	}
	std::cout << std::endl;
}

void WaveFile::write() {
	std::ofstream stream(std::string(name+".wav").c_str(), std::ios::binary);

	stream.write("RIFF", 4);
	::write<int>(stream, 36+bufferSize);
	stream.write("WAVE", 4);
	stream.write("fmt ", 4);
	::write<int>(stream, 16);
	::write<short>(stream, 1);
	::write<unsigned short>(stream, channels);
	::write<int>(stream, sampleRate);
	::write<int>(stream, sampleRate*channels*sizeof(BitDepth));
	::write<short>(stream, channels*sizeof(BitDepth));
	::write<short>(stream, 8*sizeof(BitDepth));
	stream.write("data", 4);
	stream.write((const char*)&bufferSize, 4);
	stream.write((const char*)&buffer[0], bufferSize);
	stream.close();
}

void WaveFile::open(const char* filename) {
	std::ifstream stream(filename, std::ios::binary);

	//this is all temporary shit because I didn't wanna write a header struct
	//canonical RIFF .wav header
	char chunkId[4];
	int chunkSize=0;
	char format[4];
	char formatId[4];
	int formatSize=0;
	short format2=0;
	short channels=0;
	int samplerate=0;
	int byterate=0;
	short align=0;
	int bitsPerSample=0;
	char dataId[4];
	int dataSize;

	stream.read(chunkId, 4);
	stream.read(reinterpret_cast<char*>(&chunkSize), 4);
	stream.read(format, 4);
	stream.read(formatId, 4);
	stream.read(reinterpret_cast<char*>(&formatSize), 4);
	stream.read(reinterpret_cast<char*>(&format2), 2);
	stream.read(reinterpret_cast<char*>(&channels), 2);
	stream.read(reinterpret_cast<char*>(&samplerate), 4);
	stream.read(reinterpret_cast<char*>(&byterate), 4);
	stream.read(reinterpret_cast<char*>(&align), 2);
	stream.read(reinterpret_cast<char*>(&bitsPerSample), 2);
	if(format2!=1) {return;}//if wav is not PCM format, return because of things.
	stream.read(dataId, 4);
	stream.read(reinterpret_cast<char*>(&dataSize), 4);//Somehow, this isn't correct.
	stream.close();

	printa(chunkId);
	std::cout << "chunkSize:\t\t" << chunkSize << std::endl;
	printa(format);
	printa(formatId);
	std::cout << "formatSize:\t\t" << formatSize << std::endl;
	std::cout << "format2:\t\t" << format2 << std::endl;
	std::cout << "channels:\t\t" << channels << std::endl;
	std::cout << "samplerate:\t\t" << samplerate << std::endl;
	std::cout << "byterate:\t\t" << byterate << std::endl;
	std::cout << "align:\t\t\t" << align << std::endl;
	std::cout << "bitsPerSample:\t\t" << bitsPerSample << std::endl;
	printa(dataId);
	std::cout << "dataSize:\t\t" << dataSize << std::endl;
}

void WaveFile::test_fillWithMetronome() {
	BitDepth volume=std::numeric_limits<BitDepth>::max();
	for(unsigned long i=0; i<4; ++i) {
		int j=(i*(0.25*bufferSize*0.5));
		buffer[j]=buffer[j+(channels)-1]=volume*0.5;
	}
}