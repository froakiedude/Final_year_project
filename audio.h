#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

class Audio
{
    public:
        BYTE* pFileBytes;
        const char* filename;
        Audio(const char* filename);
        void play();
        void setVolume(float volume);

};