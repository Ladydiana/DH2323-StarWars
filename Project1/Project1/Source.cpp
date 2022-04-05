// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#ifdef _DEBUG 
#define _ITERATOR_DEBUG_LEVEL 0 
#include <crtdbg.h> 
#endif
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
vector<vec3> stars(1000);
double f = SCREEN_HEIGHT / 2;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Interpolate(float a, float b, vector<float>& result);
void Interpolate(vec3 a, vec3 b, vector<vec3>& result);


void LinearInterpolation();
void DrawRomanianFlag();
void DrawRainbow();
void setStarPositions();
void DrawStars();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{

	setStarPositions();


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


void setStarPositions() {
	float r,x,y;

	for (int s = 0; s < stars.size(); ++s) {
		//-1 <= x <= 1
		x = float(rand()) / float(RAND_MAX);
		if (rand() % 2 == 0) stars[s].x = x;
		else stars[s].x = (-1)* x;
		//-1 <= y <= 1
		y = float(rand()) / float(RAND_MAX);
		if (rand() % 2 == 0) stars[s].y = y;
		else stars[s].y = (-1) * y;
		// 0 < z <= 1
		stars[s].z = float(rand()) / float(RAND_MAX);
	}
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

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);

}

void Interpolate(vec3 a, vec3 b, vector<vec3>& result){

	int sz = result.size();

	//We need to interpolate all 3 colors of the points
	//1. Calculating the step for each color
	double rStep = (b.r - a.r) / (sz-1);
	double gStep = (b.g - a.g) / (sz - 1);
	double bStep = (b.b - a.b) / (sz - 1);


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
	vector<vec3> result(SCREEN_WIDTH);
	

	Interpolate(topLeft, bottomLeft, resultLH);
	Interpolate (topRight, bottomRight, resultRH);

	for (int y = 0; y < SCREEN_HEIGHT; ++y) {

		// Interpolate width row by row
		Interpolate(resultLH[y], resultRH[y], result);

		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			PutPixelSDL(screen, x, y, result[x]);
		}
	}

	/*for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			PutPixelSDL(screen, x, y, result[x]);
		} 
	}*/

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);
}


void DrawStars() {
	SDL_FillRect(screen, 0, 0);
	if (SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	vector<double> v(stars.size());
	vector<double> u(stars.size());
	vec3 white(1, 1, 1);;
	for (size_t s = 0; s < stars.size(); ++s)
	{
		u[s] = f * (stars[s].x / stars[s].z) + (SCREEN_WIDTH / 2);
		v[s] = f * (stars[s].y / stars[s].z) + (SCREEN_HEIGHT / 2);

		PutPixelSDL(screen, u[s], v[s], white);
	}
	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void Draw()
{
	//DrawRomanianFlag();
	//DrawRainbow();
	DrawStars();


	
}