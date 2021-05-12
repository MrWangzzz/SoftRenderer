#pragma once
#include<SDL.h>
class FPS
{
public:
	FPS();
	static int GetFPS() 
	{
		while (true) {
			Uint64 start = SDL_GetPerformanceCounter();
			// Do event loop
			// Do physics loop
			// Do rendering loop
			Uint64 end = SDL_GetPerformanceCounter();

			float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
			return 1.0f / elapsed;
		}
	}
private:

};

FPS::FPS()
{
}
