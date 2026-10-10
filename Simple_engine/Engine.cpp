#include <raylib.h>
#include "Engine.h"
#include "Render.h"
#include <string>
#include <memory>
#include <iostream>
#include "api_modules.h"
#include <cstdlib>
#include <ctime>
#include <raylib.h>


std::shared_ptr<Player>player;


Engine::~Engine() {
	this->win.reset();
}



void Engine::RenderObjects() {
	int i = 0;
	for (auto& o : Objects) {
		if (o->GetStatusMovingCam() == false) {
			if (o->GetRender()) {
				if (!o->GetSuicide()) {
					o->draw();
				}
				else {
					this->Objects.erase(Objects.begin() + i);
				}
			}
		}
		i++;
	}
}

void Engine::RenderObjectsWithCam() {
	int i = 0;

	BeginMode2D(this->cam);
	for (auto& o : Objects) {
		
		if (o->GetStatusMovingCam() == true) {
			if (o->GetRender()) {
				if (!o->GetSuicide()) {
					o->draw();
				}
				else {
					this->Objects.erase(Objects.begin() + i);
				}
			}
		}
		i++;
	}
	EndMode2D();
}

void Engine::CreateEntity(Object_status st, bool is_render, bool is_cam, bool is_col) {
	this->Objects.push_back(std::make_shared<Entity>(st, is_render, is_cam, is_col));
	int index = Objects.size() - 1;
	Objects[index]->SetPointerCam(&cam);
	Objects[index]->SetPointerGame(this);
	Objects[index]->SetFlag("Entity");
}

void Engine::CreateEntityTexture(Object_status st, bool is_render, const char* name, float angle, bool is_cam, bool is_col) {
	this->Objects.push_back(std::make_shared<Entity_texture>(st, is_render, angle, is_cam, is_col));
	int index = Objects.size() - 1;
	Objects[index]->SetPointerCam(&cam);
	Objects[index]->SetPointerGame(this);
	Objects[index]->SetFlag("Entity_texture");

	auto it = this->Textures.find(name);
	if (it != this->Textures.end()) {
		std::dynamic_pointer_cast<Entity_texture>(Objects[index])->SetTexture(it->second);
		std::dynamic_pointer_cast<Entity_texture>(Objects[index])->SetNameTexture(it->first);
	}
}

void Engine::Init_fps(int fps) {
	SetTargetFPS(fps);
}


void Engine::InitPlayer(Object_status st, bool is_render, const char* name, float angle, bool is_visible_cam, bool is_gravity) {
	this->player = std::make_shared<Player>(st, is_render, angle, is_visible_cam, is_gravity);
	this->player->SetPointerCam(&this->cam);
	this->player->SetPointerGame(this);

	auto it = this->Textures.find(name);
	
	if(it->second != nullptr)this->player->SetTexture(it->second);
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
	InitPlayer({ 50, 50, 50, 50, WHITE }, true, "Red", 0, true, false);
}



void Engine::Init_engine() {
	InitWindow(640, 720, "UNDERTALE", RED);
	Init_fps(60);
	InitTextures();
	Init_user();
	Init_music();
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	InitCam();
	
}

void Engine::InitTexture(std::string name, std::string path) {
	
	const char* p = path.c_str();

	if (this->Textures.find(name.c_str()) != this->Textures.end()) {
		Print("This texture is created!");
		return;
	}

	auto tex = std::shared_ptr<Texture2D>(
		new Texture2D(LoadTexture(p)),
		[](Texture2D* t) {
			if (t->id != 0) {
				UnloadTexture(*t);
				t->id = 0;
			}
			delete t;
		}
	);
	this->Textures.insert({ name, tex });
}

void Engine::InitTextures() {
	InitTexture("ERROR", "assets\\System\\Error_texture.png");
	InitTexture("Chara", "assets\\chara.png");
	InitTexture("Red", "assets\\Red_soul.png");
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


void Engine::UnloadTextureManager(const char* name) {
	if (name == "") return;
	auto tex = this->Textures.find(name);
	if (tex != this->Textures.end()) {
		UnloadTexture(*tex->second);
		tex->second->id = 0;
		this->Textures.erase(name);
		
		for (auto& o : Objects) {
			std::dynamic_pointer_cast<Entity_texture>(o);
			if (o->GetFlag() == "Entity_texture") {
				if (std::dynamic_pointer_cast<Entity_texture>(o)->GetNameTexture() == name) {
					auto texture_error = this->Textures.find("ERROR");
					if (texture_error != this->Textures.end()) {
						std::dynamic_pointer_cast<Entity_texture>(o)->SetTexture(texture_error->second);
						std::dynamic_pointer_cast<Entity_texture>(o)->SetNameTexture("ERROR");
						
					}
					
				}
			}
			
		}
		
		Print("Texture is delete");
	}
	

}


void Engine::CreateEntityText(Object_status st, bool is_render, bool is_cam, bool is_colision, int font_size, Color color_text, std::string text) {
	this->Objects.push_back(std::make_shared<Entity_text>(st, is_render, is_cam, is_colision, font_size, color_text, text));
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

		DrawText("V 1.1", 100, 50, 48, BLUE);
		UpdateLogic();
		RenderObjectsWithCam();

		EndDrawing();
	}
}