#include <raylib.h>
#include "Engine.h"
#include "Render.h"
#include <string>
#include <memory>
#include <iostream>
#include "api_modules.h"
#include <cstdlib>
#include <ctime>


std::shared_ptr<Player>player;


Engine::~Engine() {
	this->win.reset();
}



void Engine::RenderObjects() {
	for (auto& o : Objects) {
		o->draw();
	}
}

void Engine::CreateEntity(Object_status st, bool is_render) {
	this->Objects.push_back(std::make_shared<Entity>(st, is_render));

}

void Engine::CreateEntityTexture(Object_status st, bool is_render, const char* texture_path, float angle) {
	this->Objects.push_back(std::make_shared<Entity_texture>(st, is_render, texture_path, angle));
}

void Engine::Init_fps(int fps) {
	SetTargetFPS(fps);
}


void Engine::InitPlayer(Object_status st, bool is_render, const char* texture_path, float angle) {
	this->player = std::make_shared<Player>(st, is_render, texture_path, angle);
}

void Engine::Init_music() {
	this->music_player = std::make_unique<Music_player>();
}

void Engine::Init_user() {
	InitPlayer({ 50, 50, 50, 50, WHITE }, true, "assets\\Red_soul.png", 0);
}



void Engine::Init_engine() {
	this->win = std::make_shared<Engine_render>(640, 720, "Undertale", RED);
	Init_fps(60);
	Init_user();
	Init_music();
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
}

std::shared_ptr<Player> Engine::GetPlayer() {
	return this->player;
}

void DeltaTimeGame::UpdateTime() {
	if (this->is_work) {
		float Delta = GetFrameTime();
		this->second += Delta;
	}
}

void DeltaTimeGame::reset() {
	this->second = 0;
	this->is_work = false;
}

void DeltaTimeGame::start() {
	this->is_work = true;
}

void DeltaTimeGame::stop() {
	this->is_work = false;
}




void Engine::UpdateEngine() {
	while (!WindowShouldClose()) {



		BeginDrawing();


		this->win->RenderClear();

		RenderObjects();
		
		this->player->Update_player();
		UpdateLogic();

		EndDrawing();
	}
}