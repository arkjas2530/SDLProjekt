#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h>  
#include "Menu.h"

using namespace std;



int main(int argc, char* args[])
{
	//_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	Menu menu;
	menu.firstLevel();
	
	system("pause");
	return 0;
}