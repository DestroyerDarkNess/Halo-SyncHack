//-------------------------------------------
#include "SysIncludes.h"
#include "Functions.h"
#include "Drawing.h"
#include "Menu.h"
#include "EspAimbot.h"
#include "MemoryHack.h"
//-------------------------------------------
int pFontSize = 5;
char pFaceName[MAX_PATH] = "Arial";
//-------------------------------------------
D3DVIEWPORT9 pViewport;
int CreateShader = 0;
IDirect3DPixelShader9 *PS0,*PS1;
LPDIRECT3DPIXELSHADER9 colorf,colorb;
//-------------------------------------------
LPDIRECT3DVERTEXBUFFER9 pStreamData;
UINT pOffsetInBytes = 0;
UINT pStride;
#define PlayerModel  (NumVertices == 69 || NumVertices == 507 || NumVertices == 560 || NumVertices == 852 || NumVertices == 1590 || NumVertices == 2123)
//-------------------------------------------
HRESULT GenerateShader(IDirect3DPixelShader9 **pShader, float r, float g, float b ) 
{ 
	char szShader[ MAX_PATH ]; 
	ID3DXBuffer *pShaderBuf = NULL;
	sprintf_s( szShader, "ps_2_0\ndef c0, %.1f, %.1f, %.1f, 1.0f\nmov oC0,c0", r, g, b);
	D3DXAssembleShader( szShader, sizeof( szShader ), NULL, NULL, 0, &pShaderBuf, NULL );
	if( FAILED( lpDevice->CreatePixelShader((const DWORD*)pShaderBuf->GetBufferPointer(), pShader)) )return E_FAIL; 
	return S_OK; 
}
//-------------------------------------------
DWORD cColorBack[3]={0,255,0}, CurrentColorBack;
DWORD cColorFront[3]={255,0,0}, CurrentColorFront;
//-------------------------------------------
void ColorChams(LPDIRECT3DDEVICE9 pDevice)
{
	if ((cvar.visual.chamscolor==1)|(cvar.visual.chamscolor==2))
	{
		DrawFillRect(g_fxCenter-175-10, 120, 350, 80 , C_BOX); //Overall Background
		DrawString(g_fxCenter-170, 135, "R" ,C_RED(255),DT_SHADOW); //Text infront of Sliders
		DrawString(g_fxCenter-170, 150, "G" ,C_LIME(255),DT_SHADOW); //Text infront of Sliders
		DrawString(g_fxCenter-170, 165, "B" ,C_BLUE(255),DT_SHADOW); //Text infront of Sliders
		DrawRoundRect(g_fxCenter-175-10,120,350,80,1,C_BORDER);
		DrawFillRect(g_fxCenter-175+25, 135+3, 255, 8, D3DCOLOR_ARGB(255,255,0,0));//Red Slider Bar
		DrawRect(g_fxCenter-175+25, 135+3, 255, 8,1,C_WHITE(255) );
		DrawFillRect(g_fxCenter-175+25, 150+3, 255, 8, D3DCOLOR_ARGB(255,0,255,0) );//Green Slider Bar
		DrawRect(g_fxCenter-175+25, 150+3, 255, 8,1,C_WHITE(255) );
		DrawFillRect(g_fxCenter-175+25, 165+3,255, 8, D3DCOLOR_ARGB(255,0,0,255) );//Blue Slider Bar
		DrawRect(g_fxCenter-175+25, 165+3,255, 8,1,C_WHITE(255) );
	}	
	if (cvar.visual.chamscolor==1)
	{
		DrawFillRect((float) g_fxCenter-175+25+cColorFront[0], 135+3, 2, 9, C_WHITE(255));//Red Slider		
		DrawFillRect((float) g_fxCenter-175+25+cColorFront[1], 150+3, 2, 9, C_WHITE(255));//Green Slider
		DrawFillRect((float) g_fxCenter-175+25+cColorFront[2], 165+3, 2, 9, C_WHITE(255));//Blue Slider
		DrawFillRect(g_fxCenter+255/2-12, 135,40, 40, D3DCOLOR_ARGB(255, cColorFront[0], cColorFront[1], cColorFront[2]) );//Final Color Box
		DrawString(g_fxCenter-175+50, 180, "Color-Front: 1/2/3, Inc and Dec: 4/5" ,C_WHITE(255),DT_SHADOW);
		if(GetAsyncKeyState(0x34) && cColorFront[CurrentColorFront] < 255){
			cColorFront[CurrentColorFront]++;
			GenerateShader( &colorf,(1.0f/255)* cColorFront[0],(1.0f/255)* cColorFront[1],(1.0f/255)* cColorFront[2]);}
		if(GetAsyncKeyState(0x35) && cColorFront[CurrentColorFront] > 0){
			cColorFront[CurrentColorFront]--; 
			GenerateShader( &colorf,(1.0f/255)* cColorFront[0],(1.0f/255)* cColorFront[1],(1.0f/255)* cColorFront[2]);}	
		if(GetAsyncKeyState(0x31)&1)
			CurrentColorFront = 0;
		else if(GetAsyncKeyState(0x32)&1)
			CurrentColorFront = 1;
		else if(GetAsyncKeyState(0x33)&1)
			CurrentColorFront = 2;
	}
	if (cvar.visual.chamscolor==2)
	{
		DrawFillRect((float) g_fxCenter-175+25+cColorBack[0], 135+3, 2, 9, C_WHITE(255));//Red Slider		
		DrawFillRect((float) g_fxCenter-175+25+cColorBack[1], 150+3, 2, 9, C_WHITE(255));//Green Slider
		DrawFillRect((float) g_fxCenter-175+25+cColorBack[2], 165+3, 2, 9, C_WHITE(255));//Blue Slider
		DrawFillRect(g_fxCenter+255/2-12, 135,40, 40, D3DCOLOR_ARGB(255, cColorBack[0], cColorBack[1], cColorBack[2]) );//Final Color Box	
		DrawString(g_fxCenter-175+50, 180, "Color-Bedind: 1/2/3, Inc and Dec: 4/5" ,C_WHITE(255),DT_SHADOW);				
		if(GetAsyncKeyState(0x34) && cColorBack[CurrentColorBack] < 255){
			cColorBack[CurrentColorBack]++;
			GenerateShader( &colorb,(1.0f/255)* cColorBack[0],(1.0f/255)* cColorBack[1],(1.0f/255)* cColorBack[2]);}
		if(GetAsyncKeyState(0x35) && cColorBack[CurrentColorBack] > 0){
			cColorBack[CurrentColorBack]--; 	
			GenerateShader( &colorb,(1.0f/255)* cColorBack[0],(1.0f/255)* cColorBack[1],(1.0f/255)* cColorBack[2]);}	
		if(GetAsyncKeyState(0x31)&1) 
			CurrentColorBack = 0;
		else if(GetAsyncKeyState(0x32)&1) 
			CurrentColorBack = 1;
		else if(GetAsyncKeyState(0x33)&1)
			CurrentColorBack = 2;
	}
}
//-------------------------------------------
void DrawCrosshair(D3DCOLOR color)
{
	DrawFillRect(g_fxCenter-10, g_fyCenter-1, 20, 2, color);	
	DrawFillRect(g_fxCenter-1, g_fyCenter-10, 2, 20, color);
}
//-------------------------------------------
typedef HRESULT (WINAPI *T_EndScene)(LPDIRECT3DDEVICE9 pDevice);
T_EndScene O_EndScene;
//-------------------------------------------
HRESULT WINAPI H_EndScene(LPDIRECT3DDEVICE9 pDevice)
{		
	if (!lpDevice)
		lpDevice=pDevice;

	if (pDevice->GetViewport(&pViewport) == D3D_OK)	
	{
		g_fxCenter = ( float )(pViewport.Width/2);
		g_fyCenter = ( float )(pViewport.Height/2);
	}

	if (g_Font==NULL)
	{
		g_Font = new CD3DFont(pFaceName, pFontSize, D3DFONT_BOLD);	
		g_Font->InitDeviceObjects(lpDevice);	
		g_Font->RestoreDeviceObjects();		
	}

	if (!CreateShader)
	{	
		char Shader0[] = "ps_2_0\ndef c1, 1.0, 0.0, 0.0, 1.0\nmov oC0, c0\nmov oDepth, c0.b\n";
		ID3DXBuffer *pBuf0 = NULL;
		D3DXAssembleShader(Shader0, sizeof(Shader0), NULL, NULL, 0, &pBuf0, NULL);
		pDevice->CreatePixelShader((const DWORD*)pBuf0->GetBufferPointer(), &PS0);	
		pBuf0->Release();

		char Shader1[] = "ps_2_0\ndef c2, 0.0, 0.0, 1.0, 1.0\nmov oC0, c0\nmov oDepth, c0.r\n";
		ID3DXBuffer *pBuf1 = NULL;
		D3DXAssembleShader(Shader1, sizeof(Shader1), NULL, NULL, 0, &pBuf1, NULL);
		pDevice->CreatePixelShader((const DWORD*)pBuf1->GetBufferPointer(), &PS1);	
		pBuf1->Release();

		char Shader2[]="ps_2_0\ndef c0, 1.0, 0.0, 0.0, 1.0\nmov oC0,c0";
		ID3DXBuffer *pBuf2 = NULL;
		D3DXAssembleShader( Shader2, sizeof( Shader2 ), NULL, NULL, 0, &pBuf2, NULL );
		pDevice->CreatePixelShader((const DWORD*)pBuf2->GetBufferPointer(), &colorf);
		pBuf2->Release();

		char Shader3[]="ps_2_0\ndef c0, 0.0, 1.0, 0.0, 1.0\nmov oC0,c0";
		ID3DXBuffer *pBuf3 = NULL;
		D3DXAssembleShader( Shader3, sizeof( Shader3 ), NULL, NULL, 0, &pBuf3, NULL );
		pDevice->CreatePixelShader((const DWORD*)pBuf3->GetBufferPointer(), &colorb);
		pBuf3->Release();

		CreateShader=1;
	}


	DrawMenu();

	ColorChams(pDevice);

	Esp();

	switch (cvar.d3d.crosshair)
	{
	case 1:
		DrawCrosshair(C_RED(255));
		break;
	case 2:
		DrawCrosshair(C_LIME(255));
		break;
	case 3:
		DrawCrosshair(C_BLUE(255));
		break;
	}

	if(cvar.d3d.clockfps)
	{
		char buff[MAX_PATH];
		sprintf_s(buff,"%s %s",TIME(),FPS());
		DrawString(g_fxCenter,15,buff,C_LIME(255),DT_CENTER|DT_SHADOW);
	}
	return O_EndScene(pDevice);
}
//-------------------------------------------
typedef HRESULT (WINAPI *T_Reset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters);
T_Reset O_Reset;
//-------------------------------------------
HRESULT WINAPI H_Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	if (g_Font)
	{
		g_Font->~CD3DFont();
		g_Font=NULL;
	}
	return  O_Reset( pDevice, pPresentationParameters );
}
//-------------------------------------------
typedef HRESULT (WINAPI* T_DrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type,INT BaseVertexIndex,UINT MinIndex,UINT NumVertices,UINT StartIndex,UINT PrimitiveCount);
T_DrawIndexedPrimitive O_DrawIndexedPrimitive;
//-------------------------------------------
HRESULT WINAPI H_DrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type,INT BaseVertexIndex,UINT MinIndex,UINT NumVertices,UINT StartIndex,UINT PrimitiveCount)
{

	if (pDevice->GetStreamSource(NULL, &pStreamData, &pOffsetInBytes, &pStride) == D3D_OK)	
		pStreamData->Release();
	//D3D hacks
	if(pStride==56)
	{
		if(cvar.d3d.nofog)
			pDevice->SetRenderState( D3DRS_ALPHAFUNC, 1 );

		if(cvar.d3d.fullbright)
			pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );

		if(cvar.d3d.whitewalls)
			pDevice->SetRenderState( D3DRS_ZFUNC,2);

		if(cvar.d3d.lightinvert)
			pDevice->SetRenderState( D3DRS_SRCBLEND , 10 );

		if(cvar.d3d.wireframe)
			pDevice->SetRenderState( D3DRS_FILLMODE, 2 );

	}
	//Wallhack
	if (cvar.visual.wallhack  &&  pStride == 68 &&  PlayerModel)
	{
		pDevice->SetPixelShader(PS0);  
		O_DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
		pDevice->SetPixelShader(PS1);
	} 
	//Chams
	if (cvar.visual.chams &&  pStride == 68 && PlayerModel)
	{
		pDevice->SetRenderState( D3DRS_ZENABLE,false ); //behind wall
		pDevice->SetPixelShader(colorb);
		O_DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
		pDevice->SetRenderState( D3DRS_ZENABLE, true );  //visable
		pDevice->SetPixelShader(colorf);
		pDevice->SetRenderState( D3DRS_FILLMODE, 3);	
	}

	return O_DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}
//-------------------------------------------
void WINAPI Init_Dx()
{
	/*
	DWORD *VTable;
	DWORD hD3D = NULL;
	while(!hD3D)hD3D = (DWORD)GetModuleHandleA("d3d9.dll");
	DWORD ppDevice = FindPattern(hD3D, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86",  "xx????xx????xx");
	if (ppDevice){
		memcpy( &VTable, (void *)(ppDevice + 2), 4);
		O_EndScene = (T_EndScene)DetourFunction((PBYTE)VTable[42], (PBYTE)H_EndScene);
		O_Reset = (T_Reset)DetourFunction((PBYTE)VTable[16], (PBYTE)H_Reset);
		O_DrawIndexedPrimitive = (T_DrawIndexedPrimitive)DetourFunction((PBYTE)VTable[82], (PBYTE)H_DrawIndexedPrimitive);

	}
	*/
	LPDIRECT3D9 pD3D;
	D3DPRESENT_PARAMETERS g_d3dpp;
	LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
	HWND hWnd;

	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return;
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	hWnd = FindWindow(0, "Halo");
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice)))
		return;

	PDWORD pVTable = (PDWORD)g_pd3dDevice;
	pVTable = (PDWORD)pVTable[0];

	//CH4::Utils::DbgPrint("[B#] EndScene: 0x%p",pVTable[42]);//5
	//CH4::Utils::DbgPrint("[B#] Reset: 0x%p",pVTable[16]);//5
	O_EndScene = (T_EndScene)DetourFunction((PBYTE)pVTable[42], (PBYTE)H_EndScene);
	O_Reset = (T_Reset)DetourFunction((PBYTE)pVTable[16], (PBYTE)H_Reset);
	O_DrawIndexedPrimitive = (T_DrawIndexedPrimitive)DetourFunction((PBYTE)pVTable[82], (PBYTE)H_DrawIndexedPrimitive);

	if (g_pd3dDevice)
		g_pd3dDevice->Release();
	if (pD3D)
		pD3D->Release();
}
//-------------------------------------------
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpreserved )
{
	switch(dwReason){	
	case DLL_PROCESS_ATTACH:{
		DisableThreadLibraryCalls(hinstDLL);	
		//-------------------------------------------
		GetModuleFileNameA((HMODULE)hinstDLL,dlldir,sizeof(dlldir));
		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break; }}
		//-------------------------------------------
		GetPrivateProfileStringA("Font","FontName","",pFaceName,MAX_PATH,GetDirectoryFile("Settings.ini"));
		pFontSize = GetPrivateProfileIntA("Font","FontSize",5, GetDirectoryFile("Settings.ini"));
		//-------------------------------------------
		DWORD CameraAddy = FindPattern(0x401000,0x1E4000,(PBYTE)"\x89\x1D\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x3B\xC3" , "xx????x????xx");	
		CameraAddy = *(DWORD*)(CameraAddy+2)+180;
		Camera = (ACamera*)(CameraAddy);
		//-------------------------------------------
		//Get Map Addy
		ADR_Map = FindPattern(0x401000,0x1E4000,(PBYTE)"\x85\xC0\x0F\x8C\x00\x00\x00\x00\x3D\x00\x00\x00\x00\x0F\x8F\x00\x00\x00\x00" , "xxxx????x????xx????");		
		ADR_Map = *(DWORD*)(ADR_Map+20);
		//-------------------------------------------
		//Get Fov Addy 
		ADR_Fov = FindPattern(0x401000,0x1E4000,(PBYTE)"\x89\x42\x04\x89\x4A\x08\x8B\x93\x00\x00\x00\x00" , "xxxxxxxx????") + 12;
		ADR_SetFov = FindPattern(0x401000,0x1E4000,(PBYTE)"\x56\xE8\x00\x00\x00\x00\xD9\x05\x00\x00\x00\x00" , "xx????xx????");	
		ADR_ZoomFix  = *(DWORD*)(ADR_SetFov+8)+48;
		ZoomFix  = ADR_ZoomFix;
		ADR_SetFov = *(DWORD*)(ADR_SetFov+94);

		//-------------------------------------------	
		//Get BlueArrow Addy
		ADR_BlueArrow = FindPattern(0x401000,0x1E4000,(PBYTE)"\x81\xE2\x00\x00\x00\x00\xC1\xE2\x09\x83\xFE\xFF" , "xx????xxxxxx") + 12;

		//-------------------------------------------
		//Get Radar Addy	
		ADR_Radar = FindPattern(0x401000,0x1E4000,(PBYTE)"\x8B\xEF\x89\x6C\x24\x18\xA1\x00\x00\x00\x00" , "xxxxxxx????");	
		ADR_Radar = *(DWORD*)(ADR_Radar+7);

		//-------------------------------------------
		ADR_BlueArrow = FindPattern(0x401000,0x1E4000,(PBYTE)"\x81\xE2\x00\x00\x00\x00\xC1\xE2\x09\x83\xFE\xFF" , "xx????xxxxxx") + 12;
		//-------------------------------------------
		//Code cave for Thirdperson
		char lpFileName[MAX_PATH];
		GetModuleFileNameA( NULL,lpFileName, sizeof(lpFileName) );
		string str = lpFileName;
		if (str.find("haloce") != string::npos) 			
		{ 	
			IsCE=1;	
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x63B000, (PBYTE)"\x4C\x76\x64\x00\x50\x76\x64\x00\x54\x76\x64\x00", 12, NULL);				
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x63B020, (PBYTE)"\x8B\x14\x10\x41\xA3\x10\xB0\x63\x00\x89\x1D\x14\xB0\x63\x00\x89\x2D\x1C\xB0\x63\x00\x03\xC3\x8B\x2D\x00\xB0\x63\x00\x3B\xE8\x74\x2D\x8B\x2D\x04\xB0\x63\x00\x3B\xE8\x74\x23\x8B\x2D\x08\xB0\x63\x00\x3B\xE8\x74\x19\xA1\x10\xB0\x63\x00\x8B\x1D\x14\xB0\x63\x00\x8B\x2D\x1C\xB0\x63\x00\x89\x14\x18\xE9\xD5\xDB\xE0\xFF\xA1\x10\xB0\x63\x00\x8B\x1D\x14\xB0\x63\x00\x8B\x2D\x1C\xB0\x63\x00\xE9\xBF\xDB\xE0\xFF", 100, NULL );
		}
		else if (str.find("halo") != string::npos) 
		{
			IsCE = 0;
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x6A1000, (PBYTE)"\x1C\xC7\x6A\x00\x20\xC7\x6A\x00\x24\xC7\x6A\x00", 12, NULL);
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x6A1020,(PBYTE) "\x8B\x14\x10\x41\xA3\x10\x10\x6A\x00\x89\x1D\x14\x10\x6A\x00\x89\x2D\x1C\x10\x6A\x00\x03\xC3\x8B\x2D\x00\x10\x6A\x00\x3B\xE8\x74\x2D\x8B\x2D\x04\x10\x6A\x00\x3B\xE8\x74\x23\x8B\x2D\x08\x10\x6A\x00\x3B\xE8\x74\x19\xA1\x10\x10\x6A\x00\x8B\x1D\x14\x10\x6A\x00\x8B\x2D\x1C\x10\x6A\x00\x89\x14\x18\xE9\x65\x72\xDA\xFF\xA1\x10\x10\x6A\x00\x8B\x1D\x14\x10\x6A\x00\x8B\x2D\x1C\x10\x6A\x00\xE9\x4F\x72\xDA\xFF", 100, NULL );
		}
		//-------------------------------------------
		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)Init_Dx,NULL,NULL,NULL);
		CreateThread(NULL,NULL,HackThread,NULL,NULL,NULL);
		//-------------------------------------------
		break;}
	case DLL_PROCESS_DETACH:
		{
			break;
		}
	}
	return TRUE;
}
//-------------------------------------------