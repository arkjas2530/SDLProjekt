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
			gScreenSurface = SDL_GetWindowSurface(gWindow); // Pobiera przestrze� i nak�ada j� na okno
			return true;
		}
	}
}

bool SDLLoad::load()
{
	gImage = SDL_LoadBMP(nameBMP.c_str());

	//trzeba po rozszerzaniu chwyta� zn�w przestrze� lin. 53
	//Czy trzeba zrobi� tutaj obsluge b�ed�w (52,53)? Zastan�w si� !
	SDL_SetWindowSize(gWindow, gImage->w, gImage->h);
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	if (!gImage)
	{
		std::cout << "Can't load img. Check error -> " << SDL_GetError << std::endl;
		return false;
	}
	return true;
}

std::vector<SDL_Color> SDLLoad::pixelArr()
{
	std::vector<SDL_Color> buffor;
	for (int i = 0; i < gImage->h;++i)
	{
		for (int j = 0;j < gImage->w;++j)
		{
			buffor.push_back(getPixel(j, i, gImage));
		}
	}
	return buffor;
}

SDL_Color SDLLoad::getPixel(int x, int y,SDL_Surface *image)
{
		SDL_Color color;
		Uint32 col = 0;
		if ((x >= 0) && (x<image->w) && (y >= 0) && (y<image->h)) {
			//determine position
			char* pPosition = (char*)image->pixels;
			//offset by y
			pPosition += (image->pitch*y);
			//offset by x
			pPosition += (image->format->BytesPerPixel*x);
			//copy pixel data
			memcpy(&col, pPosition, image->format->BytesPerPixel);
			//convert color
			SDL_GetRGB(col, image->format, &color.r, &color.g, &color.b);
		}
		return color;
}

void SDLLoad::setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B,SDL_Surface *image)
{
	if ((x >= 0) && (x < image->w) && (y >= 0) && (y < image->h))
	{
		/* Zamieniamy poszczeg�lne sk�adowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(image->format, R, G, B);

		/* Pobieramy informacji ile bajt�w zajmuje jeden pixel */
		int bpp = image->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *)image->pixels + y * image->pitch + x * bpp;

		/* Ustawiamy warto�� pixela, w zale�no�ci od formatu powierzchni tylko 24 bit*/
		if (bpp == 3)
		{
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			/* update the screen (aka double buffering) */
		}
	}
}

void SDLLoad::saveToBMP(std::vector<SDL_Color> buffor)
{
	SDL_Surface *nowa = nullptr;
	nowa = SDL_SetVideoMode(width, height, 32,
		SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_Setvideo
	SDL_BlitSurface(nowa, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	unsigned long long k = 0;
	for (int i = 0; i < gImage->h;++i)
	{
		for (int j = 0;j < gImage->w;++j)
		{
			setPixel(j, i, buffor[k].r, buffor[k].g, buffor[k].b, nowa);
			++k;
		}
	}

	SDL_SaveBMP(nowa, "kociel.bmp");


}

SDLLoad::~SDLLoad()
{
	//Dealokacja przestrzeni
	SDL_FreeSurface(gImage);
	gImage = NULL;

	//Niszczenie Okna
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Wy��czanie SDL
	SDL_Quit();
}
