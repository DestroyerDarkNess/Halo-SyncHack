//-------------------------------------------
DWORD FindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask);
//-------------------------------------------
void playsound(LPCSTR sound);
void playsoundmem(LPCSTR sound);
//-------------------------------------------
extern char dlldir[MAX_PATH];
//-------------------------------------------
char *GetDirectoryFile(char *filename);
//-------------------------------------------
void print_log (const char *fmt, ...);
//-------------------------------------------
char* FPS(void);
//-------------------------------------------
char* TIME(void);
//-------------------------------------------