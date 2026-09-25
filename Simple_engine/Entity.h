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

class Entity {
protected:
	Object_status sprite;
	std::vector <type_script>scripts;
	bool is_moving_object_with_cam;
	Camera2D* CamPointer;

private:
	bool is_render;
	std::string arg;

public:
	
	Entity(Object_status st, bool is_render, bool is_cam);
	void SetPointerCam(Camera2D* cam);
	Object_status GetSpriteInfo();
	void SetColor(Color color);
	void move(float dx, float dy);
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
};
class Entity_texture : public Entity {
private:
	float angle;
protected:
	Texture2D texture;
	float scale;
public:
	Entity_texture(Object_status st, bool is_render, const char* texture_path, float angle, bool is_cam);
   ~Entity_texture() override;
    void draw() override;
	float GetAngle();
	void SetAngle(float angle);
	void AddAngle(float angle);


};

class Player : public Entity_texture {
private:
	const float speed = 200;
	const int key_move[4] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
	Vector2 vector_move = { 0, 0 };
	void Update_keyboard();
	bool is_visible_cam = false;
public:
	
	Player(Object_status st, bool is_render, const char* texture_path, float angle, bool is_visible_cam);
	~Player() override;
	void Update_player();
	bool GetStatusCam();
	void SetTargetCam(bool st);


};