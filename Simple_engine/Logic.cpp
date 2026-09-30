#include "Engine.h"
#include <raylib.h>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include "api_modules.h"
#include <format>
#include "Player.h"

DeltaTimeGame timer;

bool is_disable_cam = false;
bool is_disable_cam2 = true;
bool is_loaded_texture_1 = false;

int index_object;
int index_obj_1;

std::shared_ptr<Player>pl;

void Engine::UpdateLogic() {
	timer.start();

	if (is_disable_cam == false) {
		this->player->SetTargetCam(false);
		is_disable_cam = true;
		timer.reset();
	}
	if (is_disable_cam2 == true and timer.GetTime() > 1) {
		this->player->SetTargetCam(true);
		is_disable_cam2 = false;
		timer.reset();
	}
	if (is_disable_cam2 == false and timer.GetTime() > 1) {
		if (is_loaded_texture_1 == false) {
			CreateEntityTexture({ 10, 10, 50, 50, WHITE }, true, "assets\\chara.png", 0, false, true);
			CreateEntityTexture({ 200, 20, 50, 50, WHITE }, true, "assets\\chara.png", 0, false, true);
			CreateEntityTexture({ 400, 30, 50, 50, WHITE }, true, "assets\\chara.png", 0, false, true);
			CreateEntity({ 0, 1000, 1000, 300, GREEN }, true, true, true);
			CreateEntity({ 100, 950, 300, 50, GRAY }, true, true, true);
			
			is_loaded_texture_1 = true;
			index_object = Objects.size() - 1;
			player->SetGravity(true);
		}
	}

	

	
	timer.UpdateTime();
}