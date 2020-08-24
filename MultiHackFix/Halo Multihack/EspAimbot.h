#include "Structs.h"
//-------------------------------------------
#define PI 3.141592653589793f
Object_Table_Header *ObjectTableHeader = (Object_Table_Header*)ObjectTableHeaderAddy;
Static_Player_Header *StaticPlayerHeader = (Static_Player_Header*)StaticPlayerHeaderAddy;
ALocal *Local = (ALocal*)LocalAddy;
ACamera *Camera;
Object_Table_Array *ObjectTableArray;
AMasterchief *Masterchief;
AMasterchief *LocalMC;
Static_Player *StaticPlayer;
Static_Player *LocalPlayer;
dzHook gHook;
float g_fxCenter = 0, g_fyCenter = 0;
int Aimkey = VK_LBUTTON;
DWORD ZoomFix;
//-------------------------------------------
bool GetPlayerByIndex(unsigned int index)
{
	StaticPlayer = 0, ObjectTableArray = 0, Masterchief = 0;
	StaticPlayer = (Static_Player*)(StaticPlayerHeader->FirstPlayer + (index * StaticPlayerHeader->SlotSize));
	if(StaticPlayer->ObjectID != 65535 && StaticPlayer->ObjectID != 0)
	{
		if(StaticPlayer->ObjectIndex != Local->ObjectIndex && StaticPlayer->ObjectID != Local->ObjectID)
		{
			ObjectTableArray = (Object_Table_Array*)(ObjectTableHeader->FirstObject + (StaticPlayer->ObjectIndex * ObjectTableHeader->Size));
			Masterchief = (AMasterchief*)ObjectTableArray->Offset;
			return true;
		}
	}
	return false;
}
//-------------------------------------------
bool GetLocalPlayer(unsigned int index)
{
	LocalPlayer = 0, ObjectTableArray = 0, LocalMC = 0;
	LocalPlayer = (Static_Player*)(StaticPlayerHeader->FirstPlayer + (index * StaticPlayerHeader->SlotSize));
	if (!IsBadReadPtr(LocalPlayer, 4))
	{
		if (!IsBadReadPtr((LPCVOID)&LocalPlayer->ObjectID, 4))
		{
			//if (!IsBadReadPtr((LPCVOID)LocalPlayer->ObjectID, 4))
			{
				if (LocalPlayer->ObjectID != 65535 && LocalPlayer->ObjectID != 0)
				{
					ObjectTableArray = (Object_Table_Array*)(ObjectTableHeader->FirstObject + (LocalPlayer->ObjectIndex * ObjectTableHeader->Size));
					LocalMC = (AMasterchief*)ObjectTableArray->Offset;
					return true;
				}
			}
		}
	}
	return false;
}
//-------------------------------------------
float Get2dDistance(float x, float y){return ((float)sqrt((x * x) + (y * y)));}
//-------------------------------------------
float GetAngleDistance(float fLocal[3],float f2Enemy[3]){return (float)(60 * acos(sin(fLocal[1]) * sin(f2Enemy[1]) + cos(fLocal[1]) * cos(f2Enemy[1]) * cos(f2Enemy[0] - fLocal[0])));}
//-------------------------------------------
float Deg2Rad(float deg){return (float)(deg * (PI/180.0f));}
//-------------------------------------------
bool GetAngleToEnemy(unsigned int index)
{
	float mx,my,mz;

	if(GetPlayerByIndex(index))
	{
		if (!IsBadReadPtr(Masterchief, 4))
		{
			mx = Masterchief->Head[10] - Camera->m_fWorld[0];
			my = Masterchief->Head[11] - Camera->m_fWorld[1];
			mz = Masterchief->Head[12] - Camera->m_fWorld[2];

			gHook.m_fDist = Get2dDistance(mx, my);
			gHook.m_fRot[0] = (float)atanf(my / mx);
			gHook.m_fRot[1] = (float)atan2f(mz, gHook.m_fDist);

			if (gHook.m_fRot[0] < 0.0f)
				gHook.m_fRot[0] *= -1.0f;

			if (mx < 0.0f && my >= 0.0f)
				gHook.m_fRot[0] = (float)(PI - gHook.m_fRot[0]);
			if (mx < 0.0f && my < 0.0f)
				gHook.m_fRot[0] = (float)(PI + gHook.m_fRot[0]);
			if (mx > 0.0f && my < 0.0f)
				gHook.m_fRot[0] = (float)(2.0f * PI - gHook.m_fRot[0]);
			return true;
		}
	} 
	return false;
}
//-------------------------------------------
void GetLengths()
{ 
	gHook.m_fTrueBX = sinf(gHook.m_fAng[0]) * gHook.m_fDist; 
	gHook.m_fAX = cosf(gHook.m_fAng[0]) * gHook.m_fDist;
	if(LocalMC->m_cZoom00 == -1)
		gHook.m_fExtremeBX = (float)tanf( ( Camera->m_fFov - 0.12f )  / 2.0f ) * gHook.m_fAX;
	else if(LocalMC->m_cZoom00 == 0)
		gHook.m_fExtremeBX = (float)tanf( ( Camera->m_fFov - 0.08f )  / 2.0f ) * gHook.m_fAX;
	else if(LocalMC->m_cZoom00 == 1)
		gHook.m_fExtremeBX = (float)tanf( ( Camera->m_fFov - 0.02f )  / 2.0f ) * gHook.m_fAX;
	gHook.m_fTrueBY = sinf(gHook.m_fAng[1]) * gHook.m_fDist; 
	gHook.m_fAY = cosf(gHook.m_fAng[1]) * gHook.m_fDist;
	if(LocalMC->m_cZoom00 == -1)
		gHook.m_fExtremeBY = tanf( ( ( ( Camera->m_fFov - 0.08f ) / g_fxCenter ) * g_fyCenter) / 2.0f ) * gHook.m_fAY;
	else if(LocalMC->m_cZoom00 == 0)
		gHook.m_fExtremeBY = tanf( ( ( ( Camera->m_fFov - 0.08f ) / g_fxCenter ) * g_fyCenter) / 2.0f ) * gHook.m_fAY;
	else if(LocalMC->m_cZoom00 == 1)
		gHook.m_fExtremeBY = tanf( ( ( ( Camera->m_fFov - 0.02f ) / g_fxCenter ) * g_fyCenter) / 2.0f ) * gHook.m_fAY;
}
//-------------------------------------------
void GetScreenSpace()
{
	float cir = Deg2Rad(360.0f);

	if((Local->m_fRot[0] > gHook.m_fRot[0]) && ((Local->m_fRot[0] - gHook.m_fRot[0]) < PI))
	{
		gHook.m_fAng[0] = Local->m_fRot[0] - gHook.m_fRot[0];
		GetLengths();
		gHook.m_fScreen[0] = g_fxCenter + (g_fxCenter * (gHook.m_fTrueBX / gHook.m_fExtremeBX));
	}

	else if((Local->m_fRot[0] < gHook.m_fRot[0]) && ((gHook.m_fRot[0] - Local->m_fRot[0]) < PI))
	{
		gHook.m_fAng[0] = gHook.m_fRot[0] - Local->m_fRot[0];
		GetLengths();
		gHook.m_fScreen[0] = g_fxCenter - (g_fxCenter * (gHook.m_fTrueBX / gHook.m_fExtremeBX));
	}

	else if((Local->m_fRot[0] > gHook.m_fRot[0]) && ((Local->m_fRot[0] - gHook.m_fRot[0]) > PI))
	{
		gHook.m_fAng[0] = gHook.m_fRot[0] +  (cir - Local->m_fRot[0]);
		GetLengths();
		gHook.m_fScreen[0] = g_fxCenter - (g_fxCenter * (gHook.m_fTrueBX / gHook.m_fExtremeBX));
	}

	else if((Local->m_fRot[0] < gHook.m_fRot[0]) && ((gHook.m_fRot[0] - Local->m_fRot[0]) > PI))
	{
		gHook.m_fAng[0] = Local->m_fRot[0] +  (cir - gHook.m_fRot[0]);
		GetLengths();
		gHook.m_fScreen[0] = g_fxCenter + (g_fxCenter * (gHook.m_fTrueBX / gHook.m_fExtremeBX));
	}

	if(Local->m_fRot[1] < gHook.m_fRot[1])
	{
		gHook.m_fAng[1] = gHook.m_fRot[1] - Local->m_fRot[1];
		GetLengths();
		gHook.m_fScreen[1] = g_fyCenter - (g_fyCenter * (gHook.m_fTrueBY / gHook.m_fExtremeBY));
	}

	else if(Local->m_fRot[1] > gHook.m_fRot[1])
	{
		gHook.m_fAng[1] = Local->m_fRot[1] - gHook.m_fRot[1];
		GetLengths();
		gHook.m_fScreen[1] = g_fyCenter + (g_fyCenter * (gHook.m_fTrueBY / gHook.m_fExtremeBY));
	}

	else if(Local->m_fRot[1] == gHook.m_fRot[1])
		gHook.m_fScreen[1] = g_fyCenter;
}
//-------------------------------------------
void Esp()
{	
	if (cvar.esp.enable)	
		for(unsigned int i = 0; i < StaticPlayerHeader->MaxSlots; i++)
			if(GetAngleToEnemy(i))
				if(GetLocalPlayer(Local->PlayerIndex)){		
					GetScreenSpace();

					if (cvar.esp.enable==2){
						if(LocalPlayer->Team == StaticPlayer->Team)
							continue;}

					if(gHook.m_fAng[0] > Deg2Rad(90.0f))
						continue;

					char pName[64];
					sprintf_s(pName, "%S", StaticPlayer->PlayerName0);		
					float pHealth;		

					pHealth = (Masterchief->Health / 1.000000f * 100.0f);
					float pShield;
					pShield = (Masterchief->Shield_00 / 1.00000f * 100.0f);

					if (cvar.esp.distance)
					{
						char pDist[64];
						sprintf_s(pDist, "%.0f m", gHook.m_fDist); 
						DrawString(gHook.m_fScreen[0] -5, gHook.m_fScreen[1]-40, pDist, C_WHITE(255),DT_SHADOW);
					}

					float boxw, boxh;

					if (*(float*)ZoomFix < 1 )
					{
						boxw = 400.0f / gHook.m_fDist;
						boxh = 1200.0f / gHook.m_fDist;

					}else
					{
						boxw = 200.0f / gHook.m_fDist;
						boxh = 600.0f / gHook.m_fDist;
					}

					if(StaticPlayer->Team == 0)
					{	

						if (cvar.esp.box)DrawESPBox( gHook.m_fScreen[0] - boxw /2, gHook.m_fScreen[1] -5 , boxw, boxh, 1, C_RED(255));

						if (cvar.esp.name)
							if (cvar.esp.distance)
								DrawString(gHook.m_fScreen[0]-5,gHook.m_fScreen[1]-55, pName, C_RED(255),DT_SHADOW);	
							else	
								DrawString(gHook.m_fScreen[0]-5,gHook.m_fScreen[1]-40, pName,  C_RED(255),DT_SHADOW);

						if (cvar.esp.health){
							if (pShield>0)
							{
								DrawHealthBar(gHook.m_fScreen[0]-5, gHook.m_fScreen[1] -25, 25 , 4, pShield, C_RED(255), true);
								gHook.m_fScreen[1]  += 4;
							}
							DrawHealthBar(gHook.m_fScreen[0]-5, gHook.m_fScreen[1] -25, 25, 4, pHealth, C_RED(255), false);		
							gHook.m_fScreen[1]  += 4;}
					}
					else
					{		

						if (cvar.esp.box)DrawESPBox( gHook.m_fScreen[0] - boxw /2, gHook.m_fScreen[1] -5 , boxw, boxh, 1, C_BLUE(255));

						if (cvar.esp.name)
							if (cvar.esp.distance)
								DrawString(gHook.m_fScreen[0]-5,gHook.m_fScreen[1]-55, pName, C_BLUE(255),DT_SHADOW);	
							else	
								DrawString(gHook.m_fScreen[0]-5,gHook.m_fScreen[1]-40, pName, C_BLUE(255),DT_SHADOW);	

						if (cvar.esp.health){
							if (pShield>0)
							{
								DrawHealthBar(gHook.m_fScreen[0]-5, gHook.m_fScreen[1] -25, 25 , 4, pShield, C_BLUE(255), true);
								gHook.m_fScreen[1]  += 4;
							}
							DrawHealthBar(gHook.m_fScreen[0]-5, gHook.m_fScreen[1] -25, 25, 4, pHealth, C_BLUE(255), false);		
							gHook.m_fScreen[1]  += 4;}
					}
				}

}
//-------------------------------------------
void Aimbot(void)
{  
	try
	{
		if (cvar.bot.aimbot && GetAsyncKeyState(Aimkey) && StaticPlayerHeader->IsInMainMenu == 0)
		{
			if (gHook.m_bAim)
			{
				for (unsigned short i = 0; i < StaticPlayerHeader->MaxSlots; i++)
				{
					if (GetAngleToEnemy(i))
					{
						if (GetLocalPlayer(Local->PlayerIndex))
						{
							if (LocalPlayer->Team == StaticPlayer->Team)
								continue;
							float dist = GetAngleDistance(Local->m_fRot, gHook.m_fRot);
							if (dist != 0 && (dist < gHook.m_fShortest || gHook.m_fShortest == 0))
							{
								gHook.m_fShortest = dist;
								gHook.m_uiClosest = i;
							}
						}
					}
				}
				gHook.m_fShortest = 0;
				gHook.m_bAim = false;
			}
			else
			{
				if (GetAngleToEnemy(gHook.m_uiClosest))
				{
					Local->m_fRot[0] = gHook.m_fRot[0];
					Local->m_fRot[1] = gHook.m_fRot[1];
				}
				else
					gHook.m_bAim = true;
			}
		}
		else
			gHook.m_bAim = true;
	}
	catch (const std::exception&)
	{
	}
}