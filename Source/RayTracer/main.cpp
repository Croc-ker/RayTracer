#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <iostream>
#include "Canvas.h"
#include "Plane.h"
#include "Triangle.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello World\n";

	Renderer renderer = Renderer();
	renderer.Initialize();
	renderer.CreateWindow("RayTracing", 800, 600);
	Canvas canvas(800, 600, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	Scene scene(8, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);


	// create objects -> add to scene
	srand(time(NULL));
	// create objects -> add to scene
	//for (int i = 0; i < 10; i++)
	//{
	//	std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
	//	auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -1 }, glm::vec3{ 1 }), random(0.1f, 0.5f), material);
	//	scene.AddObject(std::move(sphere));
	//}

	std::shared_ptr<Material>planeMaterial = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 }, planeMaterial);
	scene.AddObject(std::move(plane));

	//std::shared_ptr<Material>triMaterial = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	//auto triangle = std::make_unique<Triangle>(glm::vec3{ 0, 5, -10 }, glm::vec3{ -5, 0, -10 }, glm::vec3{ 5, 0, -10 }, triMaterial);
	//scene.AddObject(std::move(triangle));

	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	canvas.Clear({ 0, 0, 0, 1 });
	//for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random01() * 400, random01() * 300 }, { random01(),random01(),random01(), 1 });
	scene.Render(canvas, 15);
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