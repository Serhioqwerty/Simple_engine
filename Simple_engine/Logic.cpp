#include "Engine.h"
#include <raylib.h>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include "api_modules.h"

DeltaTimeGame timer;
float time_sec;
bool is_operation = false;
bool activate = false;

DeltaTimeGame hz;

struct data_logic {
	bool the_first_is_spawned;
	int index_first;
};


data_logic logi;

int index;
int points = 0;

std::shared_ptr<Player>pl;

void Engine::UpdateLogic() {
	timer.start();
	hz.start();
	time_sec = timer.GetTime();
	if ((int)hz.GetTime() == 1) {
		CreateEntity({ static_cast<float>(std::rand() % 500), static_cast<float>(std::rand() % 500), 20, 20, GREEN }, true);
		hz.reset();
		if (logi.the_first_is_spawned != true) {
			logi.the_first_is_spawned = true;
			logi.index_first = Objects.size() - 1;
			Print("Index: ", logi.index_first);
			Print("Pointer: ", Objects[logi.index_first]);
		}
	}

	for (int i = logi.index_first; i < Objects.size(); i++) {
		if (CheckCollisionRecs(this->player->GetRect(), Objects[i]->GetRect())) {
			Objects.erase(Objects.begin() + i);
			points += 200;
		
		}
	}

	DrawText(std::to_string(points).c_str(), 100, 50, 32, YELLOW);
	
	timer.UpdateTime();
	hz.UpdateTime();
	if ((int)time_sec % 1) {
		std::cout << "Second: " << time_sec << std::endl;
	}
	
}