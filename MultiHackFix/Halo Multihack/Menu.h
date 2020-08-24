//-------------------------------------------
enum I_COLORS{  // Item Colors
	C_OFF	 =	D3DCOLOR_ARGB(255, 200, 200, 200),
	C_ON	 =  D3DCOLOR_ARGB(255, 255, 255, 255),
	C_OFF2	 =	D3DCOLOR_ARGB(255, 200, 200, 200),
	C_OFF3	 =	D3DCOLOR_ARGB(255, 255,   0,  0 ),
	C_ON2	 =  D3DCOLOR_ARGB(255,   0, 255,  0 ),
	C_CAT	 =	D3DCOLOR_ARGB(255, 255,   0,  0 ),
	C_INFO	 =	D3DCOLOR_ARGB(255,	 0, 191, 255),
	C_INFO2	 =	D3DCOLOR_ARGB(255, 250, 250, 250),
	C_CUR	 =	D3DCOLOR_ARGB(255,	 0, 191, 255),
	C_FOOTER =	D3DCOLOR_ARGB(255,   0, 255,  0 ),
	C_TITLE	 =	D3DCOLOR_ARGB(255,   0, 255,  0 )
};
//-------------------------------------------
enum BK_COLORS{ // BackGround Colors
	C_BOX    = D3DCOLOR_ARGB(220,50,50,50),
	C_BOX2   = D3DCOLOR_ARGB(220,255,0,0),
	C_BORDER = D3DCOLOR_ARGB(220,5,5,5)
};
//-------------------------------------------
enum I_TYPE{
	T_ITEM = 0,
	T_CATEGORY = 1,
};
//-------------------------------------------
typedef struct{
	char title[64];
	char state[256];
	int	 type;
	int	 *val;
	int  maxval;
}MENU_ITEM;
//-------------------------------------------
struct cvar_s{

	struct d3d_c{
		int main, nofog, fullbright, whitewalls, lightinvert, wireframe, crosshair, clockfps;
	}d3d;

	struct visuals_c{
		int main, wallhack, chams, chamscolor;
	}visual;

	struct esp_c
	{
		int main, enable, name, distance, health, box;
	}esp;

	struct bot_c
	{
		int main, aimbot, aimkey, triggerbot;
	}bot;

	struct memory_s
	{
		int main, fov, thirdperson, radar, devmode, console, greenarrow;
	}memory;

};extern cvar_s cvar;
//-------------------------------------------
void DrawMenu();
//-------------------------------------------