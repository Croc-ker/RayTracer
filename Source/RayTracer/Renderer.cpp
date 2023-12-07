#include "Renderer.h"
#include <iostream>
#include "Canvas.h"

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error" << SDL_GetError() << std::endl;
		return false;
	}
	return false;
}

void Renderer::Shutdown()
{
	if (m_window) SDL_DestroyWindow(m_window);
	if (m_renderer) SDL_DestroyRenderer(m_renderer);

	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	m_renderer = SDL_CreateRenderer(m_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return false;
}

void Renderer::PresentCanvas(const Canvas& canvas)
{
	// copy canvas texture to renderer
	SDL_RenderCopy(m_renderer, canvas.m_texture, 0, 0);
	// present renderer to screen
	SDL_RenderPresent(m_renderer);
}


