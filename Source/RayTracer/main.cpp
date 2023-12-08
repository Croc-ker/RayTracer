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
#include "Mesh.h"

inline void InitScene01(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);
	int xOffset = 10;
	// create objects -> add to scene
	for (int x = -3; x < 3; x++)
	{
		for (int z = -43; z < 3; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.1f, 0.5f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ .2f, .7f, .2f }));
	scene.AddObject(std::move(plane));

	auto bigSphere = std::make_unique<Sphere>(glm::vec3{ 2, 1, -10 }, 1, std::make_shared<Lambertian>(color3_t{ 0.5f }));
	scene.AddObject(std::move(bigSphere));

	bigSphere = std::make_unique<Sphere>(glm::vec3{ -2, 1.1f, -14 }, 1.1f, std::make_shared<Dielectric>(color3_t{ 1 }, 1.33));
	scene.AddObject(std::move(bigSphere));

	auto massiveBackgroundSphere1 = std::make_unique<Sphere>(glm::vec3{ 8, 7, -70 }, 20, std::make_shared<Dielectric>(color3_t{ 1 }, 1.02));
	scene.AddObject(std::move(massiveBackgroundSphere1));

	massiveBackgroundSphere1 = std::make_unique<Sphere>(glm::vec3{ -16, 7, -60 }, 20, std::make_shared<Dielectric>(color3_t{ 1 }, 1.02));
	scene.AddObject(std::move(massiveBackgroundSphere1));

	auto pillar = std::make_unique<Mesh>(std::make_shared<Metal>(color3_t{ .2f, .1f, .8f }, 1.5f));
	pillar->Load("models/cube.obj", glm::vec3{ -2.5, 2, -4 }, glm::vec3{ 33, 33, 0 }, glm::vec3{ .9f, 6, 1.1f });
	scene.AddObject(std::move(pillar));

	pillar = std::make_unique<Mesh>(std::make_shared<Dielectric>(color3_t{ .1f, .2f, .8f }, 1.04f));
	pillar->Load("models/cube.obj", glm::vec3{ 2.5, 2, -5 }, glm::vec3{ 33, 0, 33 }, glm::vec3{ 1.1f, 6, .9f });
	scene.AddObject(std::move(pillar));

}

inline void InitScene02(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//cube
	auto cube = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	cube->Load("models/cube.obj", glm::vec3{ -1, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(cube));

	//sphere
	auto sphere = std::make_unique<Sphere>(glm::vec3{ .5f, 0.5f, 0 }, 0.5f, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(sphere));

	//floor
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));

	//back wall
	plane = std::make_unique<Plane>(glm::vec3{ 0, 0, -5 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));

	//ceiling
	plane = std::make_unique<Plane>(glm::vec3{ 0, 2.5f, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));

	//light
	auto light = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 1 }, 15.0f));
	light->Load("models/cube.obj", glm::vec3{ 0, 2.5f, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0.5f, 0.1f, 0.5f });
	scene.AddObject(std::move(light));

	//left wall (red)
	plane = std::make_unique<Plane>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(plane));

	//right wall (green)
	plane = std::make_unique<Plane>(glm::vec3{ 2, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
	scene.AddObject(std::move(plane));

	//behind camera wall
	plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 10 }, glm::vec3{ 0, 0, -1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));
}

int main(int argc, char* argv[]) {

	const int width = 400;
	const int height = 300;
	const int samples = 400;
	const int depth = 9;

	std::cout << "Hello World\n";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);

	Canvas canvas(width, height, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	scene.SetCamera(camera);

	srand(time(NULL));

	InitScene01(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
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

