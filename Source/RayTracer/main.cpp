#include "Renderer.h"
#include <iostream>
#include "Random.h"
#include "Camera.h"
#include "Scene.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World\n";
	seedRandom((uint32_t)time(nullptr));
	Renderer renderer = Renderer();
	renderer.Initialize();
	renderer.CreateWindow("RayTracing", 1200, 800);
	Canvas canvas(1200, 800, renderer);
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	//Scene scene = Scene(color3_t(random(0,255), random(0, 255), random(0, 255)), color3_t(random(0, 255), random(0, 255), random(0, 255))); // sky color could be set with the top and bottom color
	Scene scene = Scene(color3_t(1, 1, 1), color3_t(0, 0, 0)); // sky color could be set with the top and bottom color
	
	scene.SetCamera(camera);
	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		//for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random(0, 1200), random(0, 800) }, { random(0, 255), random(0, 255), random(0, 255), 1 });

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