#pragma once
#include <raylib.h>
#include <string>
#include <memory>
#include "Render.h"
#include <vector>
#include "Entity.h"
#include "Audio.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include "Player.h"

struct ashab_tamaev {
	std::unique_ptr<std::string>Machina;
};


class Window_engine {
private:
	int width, height;
	std::string name;
protected:
	Color color_clear;
public:
	Window_engine(int width, int height, std::string name);

	void Set_color_clear(Color color);
	Color Get_color_clear();
};

class Engine_render : public Window_engine {
protected:

public:
	Engine_render(int widht, int height, std::string name, Color cl_color);
	void RenderClear();
	void RenderAll();
};


class DeltaTimeGame {
private:
	float second = 0;
	bool is_work = false;
public:
	void UpdateTime();
	float GetTime() {
		return this->second;
	}
	void start();
	void stop();
	void reset();
};

class Engine {
private:

	int width;
	int height;

	Camera2D cam = { 0 };
	void InitWindow(int width, int height, std::string name, Color color);
	void Init_fps(int fps);
	void Init_user();
	void Init_music();
	void InitPlayer(Object_status st, bool is_render, const char* texture_path, float angle, bool is_visible_cam, bool is_gravity);
	void InitCam();

protected:

	std::shared_ptr<Engine_render>win;
	
	std::shared_ptr<Player>player;
	std::unique_ptr<Music_player>music_player;
public:

	std::vector<std::shared_ptr<Entity>>Objects;

	~Engine();
	void Init_engine();
	void RenderObjects();
	void RenderObjectsWithCam();
	void CreateEntity(Object_status st, bool is_render, bool is_cam, bool is_col);
	void CreateEntityTexture(Object_status st, bool is_render, const char* texture_path, float angle, bool is_cam, bool is_col);
	
	std::shared_ptr<Player>GetPlayer();

	void UpdateLogic();
	void UpdateEngine();

};