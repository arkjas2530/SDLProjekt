#include "SDLLoad.h"



SDLLoad::SDLLoad(std::string _name)
	:gWindow(NULL),gScreenSurface(NULL),gImage(NULL),nameBMP(_name)
{
	if (!init())
	{
		system("pause");
		exit(-1);
	}
	if (!load())
	{
		system("pause");
		exit(-1);
	}
	SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
}

bool SDLLoad::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL can't be initialize, check error -> " << SDL_GetError << std::endl;
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("KOTEL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!gWindow)
		{
			std::cout << "Window can't be create, check error -> " << SDL_GetError << std::endl;
			return false;
		}
		else
		{
			//Get window Surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			return true;
		}
	}
}

bool SDLLoad::load()
{
	gImage = SDL_LoadBMP(nameBMP.c_str());

	//Dlaczego nie dzia³a rozszerzanie trzeba po rozszerzaniu chwytaæ znów przestrzeñ lin. 53
	//Czy trzeba zrobiæ tutaj obsluge b³edów (52,53)? Zastanów siê !
	SDL_SetWindowSize(gWindow, gImage->w, gImage->h);
	gScreenSurface = SDL_GetWindowSurface(gWindow);

	if (!gImage)
	{
		std::cout << "Can't load img. Check error -> " << SDL_GetError << std::endl;
		return false;
	}
	return true;
}


SDLLoad::~SDLLoad()
{
	//Dealokacja przestrzeni
	SDL_FreeSurface(gImage);
	gImage = NULL;

	//Niszczenie Okna
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Wy³¹czanie SDL
	SDL_Quit();
}
