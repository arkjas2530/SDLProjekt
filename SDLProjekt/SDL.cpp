#include "SDL.h"


SDL::SDL(bool ifCompression, int width, int height)
	:gWindow(NULL),gScreenSurface(NULL),gImage(NULL)
{
	if (!init(ifCompression,width,height))
	{
		getchar();getchar();
		exit(-1);
	}
}

bool SDL::init(bool ifCompression, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL can't be initialize, check error -> " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Data Compression", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!gWindow)
		{
			std::cout << "Window can't be create, check error -> " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			//Get window Surface
			if (!ifCompression)
			{
				gImage = SDL_CreateRGBSurface(0, width, height, 24,0,0,0,0);
				SDL_SetWindowSize(gWindow, gImage->w, gImage->h);
			}

			gScreenSurface = SDL_GetWindowSurface(gWindow); // Pobiera przestrzeñ i nak³ada j¹ na okno

			return true;
		}
	}
}

bool SDL::load(std::string _name)
{	

	size_t pos = _name.find(".bmp");
	if (pos == std::string::npos)
	{
		LoadSaveExc exc;
		exc.setName(_name);
		exc.setMsg("Wrong file extension was entered. Correct file extension is bmp");
		throw exc;
	}

	nameBMP = _name;
	gImage = SDL_LoadBMP(nameBMP.c_str());
	if (!gImage)
	{
		LoadSaveExc exc;
		exc.setName(nameBMP);
		exc.setMsg("SDL_Surface was nullptr, probably file don't exist");
		throw exc;
	}
	SDL_SetWindowSize(gWindow, gImage->w, gImage->h);
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	return true;
}

std::vector<SDL_Color> SDL::pixelArr()
{
	std::vector<SDL_Color> buffor;
	buffor.reserve(gImage->h*gImage->w);

	for (int i = 0; i < gImage->h;++i)
	{
		for (int j = 0;j < gImage->w;++j)
		{
			buffor.push_back(getPixel(j, i, gImage));
		}
	}
	return std::move(buffor);
}

SDL_Color SDL::getPixel(int x, int y,SDL_Surface *image) 
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
		return std::move(color);
}

void SDL::setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B,SDL_Surface *image)
{
	if ((x >= 0) && (x < image->w) && (y >= 0) && (y < image->h))
	{
		/* Zamieniamy poszczególne sk³adowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(image->format, R, G, B);

		/* Pobieramy informacji ile bajtów zajmuje jeden pixel */
		int bpp = image->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *)image->pixels + y * image->pitch + x * bpp;

		/* Ustawiamy wartoœæ pixela, w zale¿noœci od formatu powierzchni tylko 24 bit*/
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
/*
SaveToBMP in 2 option
1opt. for SDL_Color
2opt. for Uint8 packing
*/
void SDL::saveToBMP(const std::vector<SDL_Color> &buffor)
{
	unsigned int k = 0;
	for (int i = 0; i < gImage->h; ++i)
	{
		for (int j = 0; j < gImage->w; ++j)
		{
			setPixel(j, i, buffor[k].r, buffor[k].g, buffor[k].b, gImage);
			++k;
		}
	}
	SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);

	std::cout << "Podaj nazwe pliku wyjsciowego: " << std::endl;
	

	std::cin >> nameBMP;

	size_t pos = nameBMP.find(".bmp");
	if (pos == std::string::npos)
	{
		LoadSaveExc exc;
		exc.setName(nameBMP);
		exc.setMsg("Wrong file extension was entered. Correct file extension is bmp");
		throw exc;
	}

	SDL_SaveBMP(gImage, nameBMP.c_str());
	gImage = nullptr;
}
void SDL::saveToBMP(const std::vector<Uint8> &buffor)
{
	
	unsigned int k = 0;
	Uint8 r, g, b;
	for (int i = 0; i < gImage->h; ++i)
	{
		for (int j = 0; j < gImage->w; ++j)
		{

			r = buffor[k++];
			g = buffor[k++];
			b = buffor[k++];


			setPixel(j, i, r, g, b, gImage);
			
		}
	}
	SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	std::cout << "Podaj nazwe pliku wyjsciowego: " << std::endl;
	std::cin >> nameBMP;

	size_t pos = nameBMP.find(".bmp");
	if (pos == std::string::npos)
	{
		LoadSaveExc exc;
		exc.setName(nameBMP);
		exc.setMsg("Wrong file extension was entered. Correct file extension is bmp");
		throw exc;
	}
	SDL_SaveBMP(gImage, nameBMP.c_str());
	gImage = nullptr;
}
SDL::~SDL()
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
