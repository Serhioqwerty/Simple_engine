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
		if (o->GetStatusMovingCam() == false) {
			o->draw();
		}
	}
}

void Engine::RenderObjectsWithCam() {


	BeginMode2D(this->cam);
	for (auto& o : Objects) {
		
		if (o->GetStatusMovingCam() == true) {
			o->draw();
		}
		
	}
	EndMode2D();
}

void Engine::CreateEntity(Object_status st, bool is_render, bool is_cam, bool is_col) {
	this->Objects.push_back(std::make_shared<Entity>(st, is_render, is_cam, is_col));
	int index = Objects.size() - 1;
	Objects[index]->SetPointerCam(&cam);
	Objects[index]->SetPointerGame(this);

}

void Engine::CreateEntityTexture(Object_status st, bool is_render, const char* texture_path, float angle, bool is_cam, bool is_col) {
	this->Objects.push_back(std::make_shared<Entity_texture>(st, is_render, texture_path, angle, is_cam, is_col));
	int index = Objects.size() - 1;
	Objects[index]->SetPointerCam(&cam);
	Objects[index]->SetPointerGame(this);
}

void Engine::Init_fps(int fps) {
	SetTargetFPS(fps);
}


void Engine::InitPlayer(Object_status st, bool is_render, const char* texture_path, float angle, bool is_visible_cam, bool is_gravity) {
	this->player = std::make_shared<Player>(st, is_render, texture_path, angle, is_visible_cam, is_gravity);
	this->player->SetPointerCam(&this->cam);
	this->player->SetPointerGame(this);
}

void Engine::InitWindow(int width, int height, std::string name, Color color) {
	this->win = std::make_shared<Engine_render>(width, height, name, color);
	this->width = width;
	this->height = height;
}

void Engine::InitCam() {
	if (this->player->GetStatusCam() == true) cam.target = this->player->GetPos();
	cam.offset = { (float)this->width / 2, (float)this->height / 2 };
	cam.zoom = 1;
	cam.rotation = 0;
}

void Engine::Init_music() {
	this->music_player = std::make_unique<Music_player>();
}

void Engine::Init_user() {
	InitPlayer({ 50, 50, 50, 50, WHITE }, true, "assets\\Red_soul.png", 0, true, false);
}



void Engine::Init_engine() {
	InitWindow(640, 720, "UNDERTALE", RED);
	Init_fps(60);
	Init_user();
	Init_music();
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	InitCam();
	
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
		if (this->player->GetStatusCam() == true) {
			this->cam.target = this->player->GetPos();
			this->cam.offset = { (float)this->width / 2, (float)this->height / 2 };
		}

		UpdateLogic();
		RenderObjectsWithCam();

		EndDrawing();
	}
}