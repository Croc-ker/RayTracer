#include "Renderer.h"
#include <iostream>

int main(int argc, char* argv[]) {
	std::cout << "Hello World\n";

	Renderer renderer = Renderer();
	renderer.Initialize();
	renderer.CreateWindow("RayTracing", 400, 300);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();
	return 0;
}