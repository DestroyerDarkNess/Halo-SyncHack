//-------------------------------------------
#include "SysIncludes.h"
#include "Functions.h"
#include "Drawing.h"
#include "Menu.h"
#include "Sounds.h"
//-------------------------------------------
cvar_s cvar;
float X = 25;
float Y = 15;
float WIDTH = 180;
float I_SPC = 15;
float T_SPC = 16.1f;
int Selector = 0;	
int ShowMenu = 0;
int NO;
MENU_ITEM Menu_Item[64];
//-------------------------------------------
#define MC_ITEMY(index)			(Y+(index*I_SPC)+T_SPC+(T_SPC/2))
#define MC_ITEMY1(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)-1)
#define MC_ITEMY2(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+20)
#define MC_ITEMY3(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+41)
#define MC_MSY					(Y+T_SPC+(T_SPC/2))
//-------------------------------------------
void getfield(char *str,char *dst, int no)
{
	char *ptr;
	int i;
	for(i=1; (ptr=strchr(str,(char)'|'))!=NULL ; i++){
		if(i==no)break;
		str=ptr+1;}
	if(ptr){
		i=(int)(ptr-str);
		strncpy_s(dst, _TRUNCATE, str, i);
		dst[i]=0;}
	else
		strcpy_s(dst, _TRUNCATE, str);
}
//-------------------------------------------
int nofields(char *str)
{
	char *ptr;
	int  no;	
	for(no=1; (ptr=strchr(str,(char)'|'))!=NULL; no++)str=ptr+1;
	return no;
}
//-------------------------------------------
void additem(char *title, char *states, I_TYPE type, int *value, int show, int when)
{	
	if(show==when){
		strcpy_s(Menu_Item[NO].title,title);	
		getfield(states,Menu_Item[NO].state, *value+1);
		Menu_Item[NO].type=type;
		Menu_Item[NO].maxval=nofields(states);
		Menu_Item[NO].val=value;
		NO++;
	}
}
//-------------------------------------------
void acat(char *title, char *states, int *value){additem(title, states, T_CATEGORY, value, 0, 0);}
void aitem(char *title, char *states, int *value, int category){additem(title, states, T_ITEM, value, category, 1);}
//-------------------------------------------
void MenuFrame( char *title, char *about)
{
	//Title
	DrawFillRect(X,Y+3,WIDTH,T_SPC,C_BOX2);
	DrawRoundRect(X,Y+3,WIDTH,T_SPC,1,C_BORDER);
	DrawString(X+WIDTH/2,Y+5,title,C_TITLE,DT_CENTER|DT_SHADOW);

	//Main
	DrawFillRect(X,MC_MSY,WIDTH,(NO*I_SPC),C_BOX);
	DrawRoundRect(X,MC_MSY,WIDTH,(NO*I_SPC),1,C_BORDER);

	//Left Box
	DrawFillRect(X-10,MC_MSY,5,(NO*I_SPC)+42,C_BOX2);
	DrawRoundRect(X-10,MC_MSY,5,(NO*I_SPC)+42,1,C_BORDER);

	//Right Box
	DrawFillRect(X+WIDTH+5,MC_MSY,5,(NO*I_SPC)+42,C_BOX2);
	DrawRoundRect(X+WIDTH+5,MC_MSY,5,(NO*I_SPC)+42,1,C_BORDER);

	//Clock
	DrawFillRect(X,MC_ITEMY1(NO)+(T_SPC/2)-2, WIDTH/2-3, T_SPC, C_BOX);
	DrawRoundRect(X,MC_ITEMY1(NO)+(T_SPC/2)-2, WIDTH/2-3, T_SPC, 1, C_BORDER);
	DrawString(X + WIDTH/4,MC_ITEMY1(NO)+(T_SPC/2)+2,  TIME(), C_TITLE,DT_CENTER|DT_SHADOW);

	//FPS
	DrawFillRect(X+(WIDTH)/2+3,MC_ITEMY1(NO)+(T_SPC/2)-2,WIDTH/2-3,(T_SPC),C_BOX);
	DrawRoundRect(X+(WIDTH)/2+3,MC_ITEMY1(NO)+(T_SPC/2)-2,WIDTH/2-3,(T_SPC), 1, C_BORDER);	
	DrawString(X+(WIDTH)/4 *3 ,MC_ITEMY1(NO)+(T_SPC/2)+2, FPS(), C_TITLE,DT_CENTER|DT_SHADOW);

	//About
	DrawFillRect(X,MC_ITEMY2(NO)+(T_SPC/2)-2,WIDTH,(T_SPC),C_BOX2);
	DrawRoundRect(X,MC_ITEMY2(NO)+(T_SPC/2)-2,WIDTH,(T_SPC), 1, C_BORDER);	
	DrawString(X+WIDTH/2,MC_ITEMY2(NO)+(T_SPC/2)+2,about, C_TITLE,DT_CENTER|DT_SHADOW);

	NO=0;
};
//-------------------------------------------
void MenuControl()
{
	for (int Index = 0; Index < NO ; Index++)
	{
		D3DCOLOR color=(*(Menu_Item[Index].val)>0)?C_ON:C_OFF;
		D3DCOLOR color1=(*(Menu_Item[Index].val)>0)?C_ON2:C_OFF2;
		D3DCOLOR color2=(*(Menu_Item[Index].val)>0)?C_ON2:C_OFF3;
		if(Menu_Item[Index].type==T_CATEGORY)color = C_CAT;
		if(Selector==Index)DrawFillRect(X,MC_ITEMY(Index),WIDTH,I_SPC,C_CUR);//Selector
		if(Menu_Item[Index].type!=T_CATEGORY)
		{
			DrawFillRect(X+5,MC_ITEMY(Index)+5, 5, 5.1f, color2);
			DrawRoundRect(X+5,MC_ITEMY(Index)+5, 5, 5.1f,1, C_BORDER);
		}
		if(Menu_Item[Index].type==T_CATEGORY)
		{
			color1=C_CAT;
			DrawString(X+4,MC_ITEMY(Index)+2,Menu_Item[Index].title,color1,DT_SHADOW);//Category title
		}
		else
			DrawString(X+16,MC_ITEMY(Index)+2,Menu_Item[Index].title,color,DT_SHADOW);//Title

		DrawString(X+WIDTH-4,MC_ITEMY(Index)+2,Menu_Item[Index].state, color1, DT_RIGHT | DT_SHADOW );//State
	}

	if(GetAsyncKeyState(VK_LEFT )&1 && (*Menu_Item[Selector].val)>0){
		(*Menu_Item[Selector].val)-=1;
		playsoundmem(SWITCH);

	}
	if(GetAsyncKeyState(VK_RIGHT)&1 && (*Menu_Item[Selector].val)<(Menu_Item[Selector].maxval-1)){
		(*Menu_Item[Selector].val)+=1;
		playsoundmem(SWITCH);
	}

	if(GetAsyncKeyState(VK_UP)&1){
		Selector=(Selector==0)?(NO-1):(Selector-1);
		playsoundmem(MOVE);
	}

	if(GetAsyncKeyState(VK_DOWN)&1){
		Selector=(Selector+1)%NO;
		playsoundmem(MOVE);
	}

}
//-------------------------------------------
void DrawMenu()
{
	if(GetAsyncKeyState(VK_INSERT)&1)ShowMenu=!ShowMenu;
	if(ShowMenu){
		MenuFrame("Halo Hook!","by TG");
		//-------------------------------------------	
		acat("BOT","Show|Hide",&cvar.bot.main);
		aitem("Aimbot","OFF|ON",&cvar.bot.aimbot,cvar.bot.main);
		aitem("Aimkey","L-Mouse|R-Mouse|Shift Key|Control Key",&cvar.bot.aimkey,cvar.bot.main);
		aitem("Triggerbot","OFF|ON",&cvar.bot.triggerbot,cvar.bot.main);		;
		//-------------------------------------------
		acat("D3D","Show|Hide",&cvar.d3d.main);
		aitem("Nofog","OFF|ON",&cvar.d3d.nofog, cvar.d3d.main);	
		aitem("Fullbright","OFF|ON",&cvar.d3d.fullbright, cvar.d3d.main);
		aitem("Whitewalls","OFF|ON",&cvar.d3d.whitewalls, cvar.d3d.main);
		aitem("Lightinvert","OFF|ON",&cvar.d3d.lightinvert, cvar.d3d.main);
		aitem("Wireframe","OFF|ON",&cvar.d3d.wireframe, cvar.d3d.main);	
		aitem("Crosshair","OFF|Red|Green|Blue",&cvar.d3d.crosshair, cvar.d3d.main);
		aitem("Clock & FPS","OFF|ON",&cvar.d3d.clockfps, cvar.d3d.main);
		//-------------------------------------------
		acat("ESP","Show|Hide",&cvar.esp.main);
		aitem("Enable","OFF|All Players|Enemy Only",&cvar.esp.enable,cvar.esp.main);
		aitem("Name","OFF|ON",&cvar.esp.name,cvar.esp.main);		
		aitem("Distance","OFF|ON",&cvar.esp.distance,cvar.esp.main);			
		aitem("Health","OFF|ON",&cvar.esp.health,cvar.esp.main);
		aitem("2D Box","OFF|ON",&cvar.esp.box,cvar.esp.main);
		//-------------------------------------------
		acat("MEMORY","Show|Hide",&cvar.memory.main);
		aitem("Fov","Default|80|90|100|110|120", &cvar.memory.fov, cvar.memory.main);
		aitem("Thirdperson","OFF|1|2|3|4|5", &cvar.memory.thirdperson, cvar.memory.main);
		aitem("Radar","OFF|All|Friendly", &cvar.memory.radar, cvar.memory.main);
		aitem("Unlock Console","OFF|ON", &cvar.memory.console, cvar.memory.main);
		aitem("Unlock DevmodeCE","OFF|ON", &cvar.memory.devmode, cvar.memory.main);
		aitem("Green Arrow","Default|Red Team|Blue Team", &cvar.memory.greenarrow, cvar.memory.main);
		//-------------------------------------------
		acat("VISUALS","Show|Hide",&cvar.visual.main);
		aitem("Wallhack","OFF|ON",&cvar.visual.wallhack, cvar.visual.main);
		aitem("Chams","OFF|ON",&cvar.visual.chams, cvar.visual.main);
		aitem("Chams-Color","Change|Color-F|Color-B",&cvar.visual.chamscolor, cvar.visual.main);
		//-------------------------------------------
		MenuControl();
	}
}