#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <iostream>
#include "Canvas.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World\n";

	Renderer renderer = Renderer();
	renderer.Initialize();
	renderer.CreateWindow("RayTracing", 800, 600);
	Canvas canvas(800, 600, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);

	Scene scene(20); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);


	// create objects -> add to scene
	srand(time(NULL));
	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -1 }, glm::vec3{ 1 }), random(0.1f, 0.5f), material);
		scene.AddObject(std::move(sphere));
	}

	canvas.Clear({ 0, 0, 0, 1 });
	//for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random01() * 400, random01() * 300 }, { random01(),random01(),random01(), 1 });
	scene.Render(canvas, 50);
	canvas.Update();

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
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}



		renderer.PresentCanvas(canvas);


	}

	renderer.Shutdown();
	return 0;
}