#include <raylib.h>
#include "Engine.h"

Window_engine::Window_engine(int width, int height, std::string name) {
	this->width = width;
	this->height = height;
	this->name = name;
	InitWindow(this->width, this->height, this->name.c_str());
}

void Window_engine::Set_color_clear(Color color) {
	this->color_clear = color;
}

Color Window_engine::Get_color_clear() {
	return this->color_clear;
}