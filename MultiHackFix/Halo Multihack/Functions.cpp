//-------------------------------------------
#include "SysIncludes.h"
//-------------------------------------------
bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask)  
			return 0;
	return (*szMask) == NULL;
}
//-------------------------------------------
DWORD FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i<dwLen; i++)
		if (bCompare((BYTE*)(dwAddress+i),bMask,szMask))  
			return (DWORD)(dwAddress+i);
	return 0;
}
//-------------------------------------------
void playsound(LPCSTR sound){sndPlaySoundA(sound,SND_ASYNC);}
void playsoundmem(LPCSTR sound){sndPlaySoundA(sound,SND_ASYNC|SND_MEMORY);}
//-------------------------------------------
char dlldir[MAX_PATH];
//-------------------------------------------
char *GetDirectoryFile(char *filename)
{
	static char path [512];
	strcpy_s(path,dlldir);
	strcat_s(path,filename);
	return path;
}
//-------------------------------------------
void print_log (const char *fmt, ...)
{
	static char prevmsg[4096];
	static int repcount = 0;
	char logbuf[4096];
	va_list va;
	FILE *f;
	va_start (va, fmt);
	vsprintf_s (logbuf, fmt, va);
	va_end (va);
	if (!strcmp (prevmsg, logbuf)){
		repcount++;
		return;
	}
	else{repcount = 0;}
	fopen_s(&f,GetDirectoryFile("\\Log.txt"),  "a");
	fprintf_s (f, "%s\n", logbuf);
	fclose (f);
	strcpy_s (prevmsg, logbuf);
}
//-------------------------------------------
char* FPS(void)
{
	static int Frames = 0;
	static float LastTickCount = 0.0f;
	static float CurrentTickCount;
	static char cfps[16];
	CurrentTickCount = clock() * 0.001f;
	Frames++;
	if((CurrentTickCount - LastTickCount) > 1.0f){
		LastTickCount = CurrentTickCount;
		sprintf_s(cfps,"FPS: %d",Frames);
		Frames = 0;}
	return cfps;
}
//-------------------------------------------
char* TIME(void)
{
	static char ctime[32];
	time_t t = time(0);
	struct tm current_tm;
	localtime_s(&current_tm, &t);
	if (current_tm.tm_hour==0)
		sprintf_s(ctime, "%d:%02d:%02d AM", current_tm.tm_hour +12, current_tm.tm_min, current_tm.tm_sec);
	else if(current_tm.tm_hour==12)
		sprintf_s(ctime, "%d:%02d:%02d PM", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
	else if(current_tm.tm_hour>12)
		sprintf_s(ctime, "%d:%02d:%02d PM", current_tm.tm_hour -12, current_tm.tm_min, current_tm.tm_sec);
	else
		sprintf_s(ctime, "%d:%02d:%02d AM", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
	return ctime;
}
//-------------------------------------------