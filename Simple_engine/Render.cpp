#include <raylib.h>
#include "Engine.h"

Engine_render::Engine_render(int widht, int height, std::string name, Color cl_color) : Window_engine(widht, height, name) {
	this->color_clear = cl_color;
	
}

void Engine_render::RenderClear() {
	ClearBackground(this->color_clear);
}



void Engine_render::RenderAll() {
	RenderClear();
	
}