#include "audio.h"

//void ReadWavFileIntoMemory(std::string fname, BYTE** pb, DWORD *fsize){
//   std::ifstream f(fname, std::ios::binary);
//
//   f.seekg(0, std::ios::end);
//   int lim = f.tellg();
//   *fsize = lim;
//
//   *pb = new BYTE[lim];
//   f.seekg(0, std::ios::beg);
//
//   f.read((char *)*pb, lim);
//
//   f.close();
//

Audio::Audio(const char* filename){
   filename = filename;
}

void Audio::play(){
   PlaySound((LPCSTR)pFileBytes, NULL, SND_MEMORY | SND_ASYNC);
}

void Audio::setVolume(float volume){
   //DWORD dwFileSize;
   //BYTE* pFileBytes;
   //ReadWavFileIntoMemory("assets/audio/music.wav", &pFileBytes, &dwFileSize); 
   //BYTE* pDataOffset = (pFileBytes + 40); 
   //__int16 * p = (__int16 *)(pDataOffset + 8);
   //for (int i = 80 / sizeof(*p); i < dwFileSize / sizeof(*p); i++){
   //    p[i] = (float)p[i] * volume;
   //}
}