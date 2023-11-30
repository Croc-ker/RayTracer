#include "Renderer.h"
#include <iostream>
#include "Random.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World\n";
	seedRandom((uint32_t)time(nullptr));
	Renderer renderer = Renderer();
	renderer.Initialize();
	renderer.CreateWindow("RayTracing", 1200, 800);
	Canvas canvas(1200, 800, renderer);
	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });

		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random(0, 1200), random(0, 800)}, {random(0, 255), random(0, 255), random(0, 255), 1});

		canvas.Update();

		renderer.PresentCanvas(canvas);

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