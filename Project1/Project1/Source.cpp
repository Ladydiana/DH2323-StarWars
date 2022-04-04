// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{
	screen = InitializeSDL(SCREEN_WIDTH, SCREEN_HEIGHT);
	while (NoQuitMessageSDL())
	{
		Draw();
	}
	SDL_SaveBMP(screen, "screenshot.bmp");
	return 0;
}


void DrawRomanianFlag() {

	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{

		for (int x = 0; x < SCREEN_WIDTH / 3; ++x)
		{
			vec3 red(139, 0, 0);
			PutPixelSDL(screen, x, y, red);

		}

		for (int x = SCREEN_WIDTH / 3; x < 2 * (SCREEN_WIDTH / 3); ++x)
		{
			vec3 yellow(1.000, 0.833, 0.224);
			PutPixelSDL(screen, x, y, yellow);
		}

		for (int x = 2 * (SCREEN_WIDTH / 3); x < SCREEN_WIDTH; ++x)
		{

			vec3 blue(0, 0, 1);
			PutPixelSDL(screen, x, y, blue);
		}
	}

}

void Draw()
{
	DrawRomanianFlag();
	

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);
}