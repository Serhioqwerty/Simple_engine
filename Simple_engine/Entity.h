#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <functional>
#include <memory>

using type_script = std::function<bool(double)>;

struct Object_status {
	float x, y, width, height;
	Color color;
};

class Engine;

class Entity {
protected:
	Object_status sprite;
	std::vector <type_script>scripts;
	bool is_moving_object_with_cam;
	Camera2D* CamPointer;
	bool is_collision;
	Engine* engine;
	bool is_killer = false;
private:
	bool is_render;
	std::string arg;
	
public:
	void SetPos(Vector2 pos);
	void SetPointerGame(Engine* engine);
	Entity(Object_status st, bool is_render, bool is_cam, bool is_colision);
	void SetPointerCam(Camera2D* cam);
	Object_status GetSpriteInfo();
	void SetColor(Color color);
	void move(float dx, float dy);
	void SetKiller(bool st);
	bool GetKiller();
	Vector2 GetPos();
	void add_size(float d_width, float d_height);
	//1 аргумент: лямда функции, 2 аргумент: входные данные (любые)
	template <typename F,  typename... Args>
	void add_script(F func, Args&&... arg) {
		func(std::forward<Args>(arg)...);
	}
	virtual ~Entity();
	virtual void draw();
	Rectangle GetRect();
	bool GetStatusMovingCam();
	bool GetStatusCollision();
};
class Entity_texture : public Entity {
private:
	float angle;
protected:
	Texture2D texture;
	float scale;
public:
	Entity_texture(Object_status st, bool is_render, const char* texture_path, float angle, bool is_cam, bool is_colision);
   ~Entity_texture() override;
    void draw() override;
	float GetAngle();
	void SetAngle(float angle);
	void AddAngle(float angle);


};

