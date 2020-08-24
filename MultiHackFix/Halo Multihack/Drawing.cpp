//-------------------------------------------
#include "SysIncludes.h"
#include "Font.h"
//-------------------------------------------
LPDIRECT3DDEVICE9 lpDevice;	
//-------------------------------------------
CD3DFont *g_Font;	
//-------------------------------------------
void DrawString(float x, float y, char* string, D3DCOLOR color, DWORD dwFlags=0UL)
{
	g_Font->DrawTextA(x,y,color,string,dwFlags);
}
//-------------------------------------------
struct Vertex
{
	float x,y,z,h;
	DWORD Color;
};
//-------------------------------------------
void DrawLine(float x, float y, float x2, float y2,  D3DCOLOR Color)
{
	Vertex V[2] ={ 
		{ (float)x , (float)y, 0.0f, 1.0f, Color},
		{ (float)x2 , (float)y2 , 0.0f, 1.0f, Color},};
		lpDevice->SetTexture(0, NULL);
		lpDevice->SetPixelShader(NULL);
		lpDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
		lpDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
		lpDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		lpDevice->DrawPrimitiveUP( D3DPT_LINELIST, 2, V, sizeof( Vertex ) );
}
//-------------------------------------------
void DrawFillRect( float x, float y, float w, float h, D3DCOLOR Color )
{
	Vertex V[4] ={
		{x,y+h, 0, 1, Color},
		{x,y, 0, 1, Color},
		{(x+w),y+h, 0, 1, Color},
		{x+w,y, 0, 1, Color}};
		lpDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
		lpDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		lpDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		lpDevice->SetTexture( 0, NULL );
		lpDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, V, sizeof( Vertex ) );
}
//-------------------------------------------
void DrawRect(float x, float y, float w, float h, float px, D3DCOLOR color)
{
	DrawFillRect(x, y, w, px, color);
	DrawFillRect(x, y, px, h, color);
	DrawFillRect((x+w), y, px, h, color);
	DrawFillRect(x, (y+h), w+px, px, color);
	return;
}
//-------------------------------------------
void DrawRoundRect(float x, float y, float w, float h, float px, D3DCOLOR color)
{
	DrawFillRect(x, y-px, w, px, color);
	DrawFillRect(x-px, y, px, h, color);
	DrawFillRect(x+w, y, px, h, color);
	DrawFillRect(x, y+h, w, px, color);
}
//-------------------------------------------
D3DCOLOR GetHealthColor(float currentHealth)
{
	if(currentHealth > 89 && currentHealth <= 100)
		return D3DCOLOR_ARGB(255, 0, 255, 0);
	else if(currentHealth > 79 && currentHealth < 90)
		return D3DCOLOR_ARGB(255, 0, 255, 155);
	else if(currentHealth > 69 && currentHealth < 80)
		return D3DCOLOR_ARGB(255, 255, 255, 0);
	else if(currentHealth > 59 && currentHealth < 70)
		return D3DCOLOR_ARGB(255, 255, 205, 0);
	else if(currentHealth > 49 && currentHealth < 60)
		return D3DCOLOR_ARGB(255, 255, 170, 0);
	else if(currentHealth > 39 && currentHealth < 50)
		return D3DCOLOR_ARGB(255, 255, 128, 0);
	else if(currentHealth > 29 && currentHealth < 40)
		return D3DCOLOR_ARGB(255, 255, 97, 0);
	else if(currentHealth > 19 && currentHealth < 30)
		return D3DCOLOR_ARGB(255, 255, 58, 0);
	else if(currentHealth > 9 && currentHealth < 20)
		return D3DCOLOR_ARGB(255, 255, 0, 66);
	else if(currentHealth > 1 && currentHealth < 9)
		return D3DCOLOR_ARGB(255, 255, 0, 0);
	else
		return D3DCOLOR_ARGB(255, 255, 0, 0);
}
//-------------------------------------------
void DrawHealthBar(float x, float y, float w, float h, float health, D3DCOLOR color, bool shield)
{
	float barPercentage = w * health / 100.0f;
	if (shield)
		DrawFillRect(x+1, y+1, barPercentage-1, h-1, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
		DrawFillRect(x+1, y+1, barPercentage-1, h-1, GetHealthColor(health));
	DrawRect(x , y, w, h, 1, color);
}
//-------------------------------------------
void DrawESPBox(float x, float y, float w, float h, float px, D3DCOLOR color)
{	//Top
	DrawFillRect(x,y,w/2,px,color);	
	DrawFillRect(x+w,y,w/2,px,color);
	//TopLeft
	DrawFillRect(x,y,px,w/2,color);
	//TopRight
	DrawFillRect(x+w+w/2,y,px,w/2,color);
	//Bottom
	DrawFillRect(x,y+h,w/2,px,color);	
	DrawFillRect(x+w,y+h,w/2,px,color);
	//BottomLeft
	DrawFillRect(x,y+h-w/2,px,w/2,color);
	//BottomRight
	DrawFillRect(x+w+w/2,y+h-w/2,px,w/2 +px,color);
}