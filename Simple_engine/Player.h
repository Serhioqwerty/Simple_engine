#pragma once
#include <raylib.h>
#include "Entity.h"
#include <memory>

class Player : public Entity_texture {
private:
	const float speed = 200;
	const int key_move[4] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
	Vector2 vector_move = { 0, 0 };
	void Update_keyboard();
	bool is_visible_cam = false;
	Vector2 old_pos;
	bool is_gravity;
	const float gravity = 9.8;
	float is_check_collided = false;

public:

	Player(Object_status st, bool is_render, const char* texture_path, float angle, bool is_visible_cam, bool is_gravity);
	~Player() override;
	void Update_player();
	bool GetStatusCam();
	void SetTargetCam(bool st);
	void SetGravity(bool st);

	

};