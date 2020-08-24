//-------------------------------------------
int IsCE = 0;
DWORD ADR_Map;
DWORD ADR_Fov;
DWORD ADR_SetFov;
DWORD ADR_ZoomFix;
DWORD ADR_Radar;
DWORD ADR_BlueArrow;
//-------------------------------------------
void WriteInt(DWORD dwAddress, INT value){WriteProcessMemory( GetCurrentProcess(), (LPVOID)dwAddress, (LPVOID) &value, sizeof(value), NULL );}
void WriteByte(DWORD dwAddress, BYTE value){WriteProcessMemory( GetCurrentProcess(), (LPVOID)dwAddress, (LPCVOID)&value, sizeof(value), NULL );}
void WriteFloat(DWORD dwAddress, FLOAT value){WriteProcessMemory( GetCurrentProcess(), (LPVOID)dwAddress, (LPCVOID)&value, sizeof(value), NULL );}
//-------------------------------------------


void PistolAimAssist()
{
	char map[64];
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)ADR_Map, &map, sizeof(map), 0);
	string mapname = map;

    if (cvar.bot.triggerbot)
    {
		if (IsCE) 
		{	
			if (mapname.find("bloodgulch") != string::npos)	
			{
			WriteFloat(0x406584BC, 0.09235988f);//Auto - Aim Angle
			WriteFloat(0x406584BC + 4, 50);//Auto - Aim range
			WriteFloat(0x406584BC + 8, 0.1097198f);//Magnetism Angle
			WriteFloat(0x406584BC + 12, 50);//Magnetism Range
		
			}	
		}else{
			if (mapname.find("bloodgulch") != string::npos)
			{
			WriteFloat(0x4066CE08, 0.09235988f);//Auto - Aim Angle
			WriteFloat(0x4066CE08 + 4, 50.0f);//Auto - Aim range
			WriteFloat(0x4066CE08 + 8, 0.1097198f);//Magnetism Angle
			WriteFloat(0x4066CE08 + 12, 50.0f);//Magnetism Range	
			}
		}
	} 
}

void FixChams()
{

	//Fix chams for original map only	
	char map[64];
	ReadProcessMemory(GetCurrentProcess(),(LPVOID) ADR_Map, &map,sizeof(map),0);	
	string mapname = map;
	if (IsCE)
	{
		if (cvar.visual.chams){ 
			if (mapname.find("bloodgulch") != string::npos) 			
				WriteInt(0x4050C9FC, 3892512399);
			else if (mapname.find("beavercreek") != string::npos) 
				WriteInt(0x406DBC38, 3816292868);
			else if (mapname.find("sidewinder") != string::npos) 
				WriteInt(0x404F0F34, 3870688578);
			else if (mapname.find("damnation") != string::npos) 		
				WriteInt(0x406E01BC, 3863807193);
			else if (mapname.find("ratrace") != string::npos) 
				WriteInt(0x404D9008, 3846112203); 
			else if (mapname.find("prisoner") != string::npos) 	
				WriteInt(0x404D4C80, 3861382324);
			else if (mapname.find("hangemhigh") != string::npos) 
				WriteInt(0x406CCF94, 3828351676);
			else if (mapname.find("chillout") != string::npos)
				WriteInt(0x406CB93C, 3812688333);
			else if (mapname.find("carousel") != string::npos)   		
				WriteInt(0x406D32CC, 3812032963);
			else if (mapname.find("boardingaction") != string::npos)
				WriteInt(0x406E5750, 3833725710);        
			else if (mapname.find("wizard") != string::npos) 	
				WriteInt(0x404D6228, 3818652200);
			else if (mapname.find("putput") != string::npos) 		
				WriteInt(0x406CCC4C, 3847422943);      
			else if (mapname.find("longest") != string::npos) 
				WriteInt(0x406D0A9C, 3844932537);
			else if (mapname.find("icefields") != string::npos) 
				WriteInt(0x40766D1C, 3834381080);				 			
			else if (mapname.find("deathisland") != string::npos) 	
				WriteInt(0x407CBE78, 3876980130);  	 		 
			else if (mapname.find("dangercanyon") != string::npos)
				WriteInt(0x407A51F0, 3851551774);
			else if (mapname.find("infinity") != string::npos)
				WriteInt(0x4079FB30, 3876259223); 		
			else if (mapname.find("timberland") != string::npos) 	
				WriteInt(0x407A2948, 3874489724);			 		 		 	
			else if (mapname.find("gephyrophobia") != string::npos)
				WriteInt(0x4074C604, 3868132635);}
		if (!cvar.visual.chams){ 
			if (mapname.find("bloodgulch") != string::npos) 			 	
				WriteInt(0x4050C9FC, 3792437400);
			else if (mapname.find("beavercreek") != string::npos)  
				WriteInt(0x406DBC38, 3868656931); 	
			else if (mapname.find("sidewinder") != string::npos) 		 
				WriteInt(0x404F0F34, 3789488235);
			else if (mapname.find("damnation") != string::npos) 
				WriteInt(0x406E01BC, 3869312301); 
			else if (mapname.find("ratrace") != string::npos) 	
				WriteInt(0x404D9008, 3785621552);	  		
			else if (mapname.find("prisoner") != string::npos) 
				WriteInt(0x404D4C80, 3784900645);  
			else if (mapname.find("hangemhigh") != string::npos)
				WriteInt(0x406CCF94, 3865511155);   
			else if (mapname.find("chillout") != string::npos)
				WriteInt(0x406CB93C, 3865314544);	  
			else if (mapname.find("carousel") != string::npos)	
				WriteInt(0x406D32CC, 3866690821);    
			else if (mapname.find("boardingaction") != string::npos) 
				WriteInt(0x406E5750, 3868656931);
			else if (mapname.find("wizard") != string::npos)
				WriteInt(0x404D6228, 3785359404);
			else if (mapname.find("putput") != string::npos)
				WriteInt(0x406CCC4C, 3864397026);   
			else if (mapname.find("longest") != string::npos)
				WriteInt(0x406D0A9C, 3866100988);
			else if (mapname.find("icefields") != string::npos)	
				WriteInt(0x40766D1C, 3884844570);
			else if (mapname.find("deathisland") != string::npos)
				WriteInt(0x407CBE78, 3897296600);	 		 
			else if (mapname.find("dangercanyon") != string::npos) 
				WriteInt(0x407A51F0, 3889170012);	 		
			else if (mapname.find("infinity") != string::npos)
				WriteInt(0x4079FB30, 3888449105);
			else if (mapname.find("timberland") != string::npos) 
				WriteInt(0x407A2948, 3887138365);
			else if (mapname.find("gephyrophobia") != string::npos)
				WriteInt(0x4074C604, 3886089773);}
	}else{
		if (cvar.visual.chams){
			if (mapname.find("bloodgulch") != string::npos)
				WriteInt(0x4050E6DC, 3892512399); 
			else if (mapname.find("beavercreek") != string::npos) 
				WriteInt(0x40716820, 3816292868);
			else if (mapname.find("sidewinder") != string::npos)
				WriteInt(0x404F1D74, 3870688578);
			else if (mapname.find("damnation") != string::npos)
				WriteInt(0x407197A4, 3863807193);
			else if (mapname.find("ratrace") != string::npos) 
				WriteInt(0x404D8E04, 3846112203);
			else if (mapname.find("prisoner") != string::npos)
				WriteInt(0x404D47FC, 3861382324);
			else if (mapname.find("hangemhigh") != string::npos) 
				WriteInt(0x40706C18, 3828351676);
			else if (mapname.find("chillout") != string::npos)
				WriteInt(0x407053F0, 3812688333);
			else if (mapname.find("carousel") != string::npos)
				WriteInt(0x4070D1CC, 3812032963);  
			else if (mapname.find("boardingaction") != string::npos)
				WriteInt(0x4072040C, 3833725710);
			else if (mapname.find("wizard") != string::npos)
				WriteInt(0x404D601C, 3818652200);
			else if (mapname.find("putput") != string::npos)
				WriteInt(0x4070638C, 3847422943);
			else if (mapname.find("longest") != string::npos) 
				WriteInt(0x4070AD20, 3844932537);
			else if (mapname.find("icefields") != string::npos)
				WriteInt(0x407A8508, 3834381080);		 		
			else if (mapname.find("deathisland") != string::npos)	
				WriteInt(0x40811040, 3876980130);	 
			else if (mapname.find("dangercanyon") != string::npos)
				WriteInt(0x407E8980, 3851551774);	 		 
			else if (mapname.find("infinity") != string::npos)
				WriteInt(0x407E173C, 3876259223);			 		
			else if (mapname.find("timberland") != string::npos)
				WriteInt(0x407E4A64, 3874489724);				 		 		 
			else if (mapname.find("gephyrophobia") != string::npos)
				WriteInt(0x4078E50C, 3868132635);} 
		if (!cvar.visual.chams){
			if (mapname.find("bloodgulch") != string::npos)
				WriteInt(0x4050E6DC, 3792437400); 
			else if (mapname.find("beavercreek") != string::npos) 
				WriteInt(0x40716820, 3868656931);
			else if (mapname.find("sidewinder") != string::npos)
				WriteInt(0x404F1D74, 3789488235);
			else if (mapname.find("damnation") != string::npos)
				WriteInt(0x407197A4, 3869312301);
			else if (mapname.find("ratrace") != string::npos) 
				WriteInt(0x404D8E04, 3785621552);
			else if (mapname.find("prisoner") != string::npos)
				WriteInt(0x404D47FC, 3784900645);
			else if (mapname.find("hangemhigh") != string::npos) 
				WriteInt(0x40706C18, 3865511155);
			else if (mapname.find("chillout") != string::npos)
				WriteInt(0x407053F0, 3865314544);
			else if (mapname.find("carousel") != string::npos)
				WriteInt(0x4070D1CC, 3866690821);  
			else if (mapname.find("boardingaction") != string::npos)
				WriteInt(0x4072040C, 3868656931);
			else if (mapname.find("wizard") != string::npos)
				WriteInt(0x404D601C, 3785359404);
			else if (mapname.find("putput") != string::npos)
				WriteInt(0x4070638C, 3864397026);
			else if (mapname.find("longest") != string::npos) 
				WriteInt(0x4070AD20, 3866100988);
			else if (mapname.find("icefields") != string::npos)
				WriteInt(0x407A8508, 3884844570);		 		
			else if (mapname.find("deathisland") != string::npos)	
				WriteInt(0x40811040, 3897296600);	 
			else if (mapname.find("dangercanyon") != string::npos)
				WriteInt(0x407E8980, 3889170012);	 		 
			else if (mapname.find("infinity") != string::npos)
				WriteInt(0x407E173C, 3888449105);			 		
			else if (mapname.find("timberland") != string::npos)
				WriteInt(0x407E4A64, 3887138365);				 		 		 
			else if (mapname.find("gephyrophobia") != string::npos)
				WriteInt(0x4078E50C, 3886089773);}
	}
}
//-------------------------------------------
float DegreeToRadian(float angle)
{
	return ((3.141593F * angle) / 180.0F);
}
//-------------------------------------------
void setFov (float fov)
{
	if (*(float*)ADR_ZoomFix < 1 )
	{
		WriteProcessMemory(GetCurrentProcess(), (LPVOID) ADR_Fov, (PBYTE)"\x89\x93\xAC\x00\x00\x00", 6, NULL);
	}
	else
	{		
		WriteProcessMemory(GetCurrentProcess(), (LPVOID) ADR_Fov, (PBYTE)"\x90\x90\x90\x90\x90\x90", 6, NULL);	
		WriteFloat(ADR_SetFov, DegreeToRadian(fov));
	}
}
//-------------------------------------------
void SetThirdperson(float fov)
{	
	if (IsCE)
	{
		int IsInVehicle = 0;		  
		ReadProcessMemory(GetCurrentProcess(),(void*)(0x64764C-0x148),&IsInVehicle,sizeof(IsInVehicle),0);
		if (cvar.memory.thirdperson && IsInVehicle==0)
		{
		
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) 0x448C3C, (PBYTE)"\xE9\xDF\x23\x1F\x00", 5, NULL);	
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) 0x44644B, (PBYTE)"\x66\xC7\x41\x56\x01\x00", 6, NULL);
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) (0x64764C + 0x08), &fov, sizeof(fov), NULL);
		}
		else
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x448C3C, (PBYTE)"\x8B\x14\x10\x41\x89", 5, NULL );
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) 0x44644B, (PBYTE)"\x66\xC7\x41\x56\x00\x00", 6, NULL);
		}
	}else{

		int IsInVehicle = 0;		  
		ReadProcessMemory(GetCurrentProcess(),(void*)(0x6AC71C-0x148),&IsInVehicle,sizeof(IsInVehicle),0);
		if (cvar.memory.thirdperson && IsInVehicle==0)
		{	
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x4482CC, (PBYTE)"\xE9\x4F\x8D\x25\x00", 5, NULL );		
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) 0x445AEB, (PBYTE)"\x66\xC7\x41\x56\x01\x00", 6, NULL);
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) (0x6AC71C + 0x08), &fov, sizeof(fov), NULL);
		}
		else
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)  0x4482CC, (PBYTE)"\x8B\x14\x10\x41\x89", 5, NULL );	
			WriteProcessMemory(GetCurrentProcess(), (LPVOID) 0x445AEB, (PBYTE)"\x66\xC7\x41\x56\x00\x00", 6, NULL);
		}
	}
}
//-------------------------------------------
DWORD WINAPI HackThread(LPVOID)
{
	while (true){
		//-------------------------------------------

		if (IsCE)
			if (cvar.memory.devmode)
				WriteByte(0x6BD15E,0x01);
			else
				WriteByte(0x6BD15E,0x00);	
		//-------------------------------------------
		if (cvar.memory.console)
		{
			if (IsCE)
				WriteByte(0x651F51,0x01);
			else	
				WriteByte(0x6B7021,0x01);	
		}
		else
		{		
			if (IsCE)
				WriteByte(0x651F51,0x00);
			else	
				WriteByte(0x6B7021,0x00);
		}
		//-------------------------------------------
		Aimbot();
		switch (cvar.bot.aimkey){
		case 0:
			Aimkey = VK_LBUTTON;
			break;
		case 1:
			Aimkey = VK_RBUTTON;
			break;
		case 2:
			Aimkey = VK_SHIFT;
			break;
		case 3:
			Aimkey = VK_CONTROL;
			break;}

		//-------------------------------------------	
		FixChams();

		//PistolAimAssist();
	
	    //-------------------------------------------
		if (cvar.bot.triggerbot)		  	
			//-------------------------------------------
			if (*(int*)0x400008CC==1)
			{								  
				mouse_event(0x0002,0,0,0,0);
				Sleep(60);							 
				mouse_event(0x0004,0,0,0,0);
			}
			
			//-------------------------------------------

			switch (cvar.memory.thirdperson){
			case  0:
				SetThirdperson(0);
				break;
			case  1:
				SetThirdperson(1);
				break;
			case  2:
				SetThirdperson(2);
				break;
			case  3:
				SetThirdperson(3);
				break;
			case  4:
				SetThirdperson(4);
				break;
			case  5:
				SetThirdperson(5);
				break;}

			//-------------------------------------------

			switch (cvar.memory.fov){	
			case 0:
				setFov(70);
				break;
			case 1:
				setFov(80);
				break;
			case 2:
				setFov(90);
				break;
			case 3:
				setFov(100);
				break;
			case 4:
				setFov(110);
				break;
			case 5:
				setFov(120);
				break;}
			//-------------------------------------------	

			switch(cvar.memory.greenarrow)
			{	
			case 0:
					WriteProcessMemory(GetCurrentProcess(), (LPVOID) ADR_BlueArrow, (PBYTE)"\x8B\x6C\x0A\x20\x74\x71", 6, NULL );
					break;
			case 1:
					WriteProcessMemory(GetCurrentProcess(), (LPVOID) ADR_BlueArrow, (PBYTE)"\xBD\x00\x00\x00\x00\x90", 6, NULL );
					break;
			case 2:
					WriteProcessMemory(GetCurrentProcess(), (LPVOID) ADR_BlueArrow, (PBYTE)"\xBD\x01\x00\x00\x00\x90", 6, NULL );
					break;
			}

           //400008A0 = 1 byte - 0 for rader, 16 for none radar
			//-------------------------------------------
			switch (cvar.memory.radar){
			case 0:
				WriteInt(ADR_Radar, 10);
				break;
			case 1:
				WriteInt(ADR_Radar, 11);
				break;
			case 2:
				WriteInt(ADR_Radar, 75);
				break;}
			//-------------------------------------------
			Sleep(1);
	}
}