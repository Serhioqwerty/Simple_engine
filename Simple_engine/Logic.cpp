#include "Engine.h"
#include <raylib.h>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include "api_modules.h"
#include <format>

enum class Type_collision {FIRST_LEVEL, AZART};

Type_collision type = Type_collision::FIRST_LEVEL;

DeltaTimeGame timer;
float time_sec;
bool is_operation = false;
bool activate = false;

DeltaTimeGame hz;

struct data_logic {
	bool the_first_is_spawned;
	int index_first;
};


DeltaTimeGame message_time;

bool is_message1_view = true;

std::string meesage1 = "you are crazy";

data_logic logi;

int index;
double points = 0;

std::shared_ptr<Player>pl;

void Engine::UpdateLogic() {
	timer.start();
	hz.start();
	time_sec = timer.GetTime();
	if ((float)hz.GetTime() >= GetFrameTime()) {
		CreateEntity({ static_cast<float>(std::rand() % 5000), static_cast<float>(std::rand() % 5000), 20, 20, GREEN }, true, true);
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
			if (type == Type_collision::FIRST_LEVEL) {

				points += 200;
			}
			else if (type == Type_collision::AZART) {
				int fortune = std::rand() % 300;
				if (fortune < 150) points += 400;
				if (fortune == 150) points *= points;
				if (fortune > 150 and fortune < 200) points += points / 65536;
				if (fortune == 200) points *= 10;
				if (fortune > 200 and fortune < 300) fortune += 500;
			}
			Objects.erase(Objects.begin() + i);
		
		}
	}

	DrawText(std::format("{:.1000}", std::to_string(points)).c_str(), 100, 50, 32, YELLOW);
	
	timer.UpdateTime();
	hz.UpdateTime();
	if (points >= 1000 and is_message1_view == true) {
		message_time.start();
		DrawText(meesage1.c_str(), 100, 100, 32, YELLOW);
		Print((int)message_time.GetTime());
		if ((int)message_time.GetTime() == 3) {

			is_message1_view = false;
			message_time.stop();
			message_time.reset();
			type = Type_collision::AZART;
		}
		
		message_time.UpdateTime();
	}

	if (!Objects.empty()) {
		int last_index = Objects.size() - 1;
		if (last_index < 0) last_index = 0;
		if (Objects[last_index] != nullptr) {
			float d = GetDistance(this->player, this->Objects.at(last_index));
			Print("Distance: ", d);
		}
	}
	
	
	
}