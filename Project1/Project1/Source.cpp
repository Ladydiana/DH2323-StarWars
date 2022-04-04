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
#include <algorithm>

//Visual Studio won't compile without these 2 lines below.
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;
vec3 topLeft(1, 0, 0); // red
vec3 topRight(0, 0, 1); // blue
vec3 bottomLeft(0, 1, 0); // green
vec3 bottomRight(1, 1, 0); // yellow

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Interpolate(float a, float b, vector<float>& result);
void Interpolate(vec3 a, vec3 b, vector<vec3>& result);


void LinearInterpolation();
void DrawRomanianFlag();
void DrawRainbow();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{

	

	//LinearInterpolation();
	screen = InitializeSDL(SCREEN_WIDTH, SCREEN_HEIGHT);
	while (NoQuitMessageSDL())
	{
		Draw();
	}
	SDL_SaveBMP(screen, "screenshot.bmp");
	return 0;
}


 /*void LinearInterpolation() {
	vector<float> result(10); // Create a vector width 10 floats
	Interpolate(5, 14, result); // Fill it with interpolated values
	int s = result.size();
	for (int i = 0; i < s; ++i)
		cout << result[i] << " "; // Print the result to the terminal
} */

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

void Interpolate(vec3 a, vec3 b, vector<vec3>& result){

	int sz = result.size();

	//We need to interpolate all 3 colors of the points
	//1. Calculating the step for each color
	double rStep = (b.r - a.r) / (sz-1);
	double gStep = (b.g - a.g) / (sz - 1);
	double bStep = (b.b - a.b) / (sz - 1);

	//for (int x = 0; x < sz; ++x) {}

	//result[i].r = a.r + distance_r*i;
	//std::vector<float> step(sz);
	//std::generate_n(std::back_inserter(step), size, []() { static double d = 0; return d += rStep; });

	for (int x = 0; x <sz; ++x) {
		result[x].r = a.r + rStep * x;
		result[x].g = a.g + gStep * x;
		result[x].b = a.b + bStep * x;
	}



}

void DrawRainbow() {

	//Height interporlation
	vector<vec3> resultLH(SCREEN_HEIGHT);
	vector<vec3> resultRH(SCREEN_HEIGHT);

	Interpolate(topLeft, bottomLeft, resultLH);
	Interpolate(topRight, bottomRight, resultRH);


	
}

void Draw()
{
	DrawRomanianFlag();
	

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);
}