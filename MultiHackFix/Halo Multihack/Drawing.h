#include"Font.h"
//-------------------------------------------
extern LPDIRECT3DDEVICE9 lpDevice;
extern CD3DFont *g_Font;
//-------------------------------------------
#define C_BLACK(alpha)       D3DCOLOR_ARGB (alpha,0,0,0)
#define C_WHITE(alpha)       D3DCOLOR_ARGB (alpha,255,255,255)
#define C_RED(alpha)         D3DCOLOR_ARGB (alpha,255,0,0)
#define C_LIME(alpha)        D3DCOLOR_ARGB (alpha,0,255,0)
#define C_BLUE(alpha)        D3DCOLOR_ARGB (alpha,0,0,255)
#define C_YELLOW(alpha)      D3DCOLOR_ARGB (alpha,255,255,0)
#define C_AQUA(alpha)        D3DCOLOR_ARGB (alpha,0,255,255)
#define C_FUCHSIA(alpha)     D3DCOLOR_ARGB (alpha,255,0,255)
#define C_SILVER(alpha)      D3DCOLOR_ARGB (alpha,192,192,192)
#define C_GRAY(alpha)        D3DCOLOR_ARGB (alpha,128,128,128)
#define C_MAROON(alpha)      D3DCOLOR_ARGB (alpha,128,0,0)
#define C_OLIVE(alpha)       D3DCOLOR_ARGB (alpha,128,128,0)
#define C_GREEN(alpha)       D3DCOLOR_ARGB (alpha,0,128,0)
#define C_PURPLE(alpha)      D3DCOLOR_ARGB (alpha,128,0,128)
#define C_TEAL(alpha)        D3DCOLOR_ARGB (alpha,0,128,128)
#define C_NAVY(alpha)        D3DCOLOR_ARGB (alpha,0,0,128)
//-------------------------------------------
void DrawString(float x, float y, char* string, D3DCOLOR color, DWORD dwFlags=0UL);
void DrawLine(float x, float y, float x2, float y2,  D3DCOLOR Color);
void DrawFillRect(float x, float y, float w, float h, D3DCOLOR color);
void DrawRect(float x, float y, float w, float h, float px, D3DCOLOR color);
void DrawRoundRect(float x, float y, float w, float h, float px, D3DCOLOR color);
void DrawHealthBar(float x, float y, float w, float h, float health, D3DCOLOR color, bool shield);
void DrawESPBox(float x, float y, float w, float h, float px, D3DCOLOR color);
//-------------------------------------------