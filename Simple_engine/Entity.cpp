#include <raylib.h>
#include "Entity.h"
#include <string>
#include <iostream>
#include "api_modules.h"

Entity::Entity(Object_status st, bool is_render, bool is_cam) {
	this->sprite = st;
	this->is_render = is_render;
	this->arg = "/Default /no_texture";
	this->is_moving_object_with_cam = is_cam;
}

void Entity::SetPointerCam(Camera2D* cam) {
	this->CamPointer = cam;
}

Entity::~Entity() {
	this->CamPointer = nullptr;
}

bool Entity::GetStatusMovingCam() {
	return this->is_moving_object_with_cam;
}

void Entity::SetColor(Color color) {
	this->sprite.color = color;
}

void Entity::move(float dx, float dy) {
	this->sprite.x += dx * GetFrameTime();
	this->sprite.y += dy * GetFrameTime();
}

void Entity::add_size(float d_width, float d_height) {
	this->sprite.width += d_width;
	this->sprite.height += d_height;
}

Vector2 Entity::GetPos() {
	return { this->sprite.x, this->sprite.y };
}

void Entity::draw() {
	if (this->is_render == true) {
		
		DrawRectangle(this->sprite.x, this->sprite.y, this->sprite.width, this->sprite.height, this->sprite.color);
		
	}
	
}

Rectangle Entity::GetRect() {
	return { this->sprite.x, this->sprite.y, this->sprite.width, this->sprite.height };
}


Entity_texture::Entity_texture(Object_status st, bool is_render, const char* texture_path, float angle, bool is_cam) : Entity(st, is_render, is_cam) {
	this->texture = LoadTexture(texture_path);
	this->angle = angle;
}

Entity_texture::~Entity_texture() {
	UnloadTexture(this->texture);
}

Object_status Entity::GetSpriteInfo() {
	return this->sprite;
}

void Entity_texture::draw() {
	Vector2 size_texture = { texture.width, texture.height };
	Vector2 vec = GetWorldToScreen2D({ sprite.x, sprite.y }, *this->CamPointer);
	DrawTexturePro(this->texture, { 0, 0, size_texture.x, size_texture.y}, {vec.x, vec.y, this->sprite.width * this->CamPointer->zoom, this->sprite.height * this->CamPointer->zoom}, {0, 0}, this->angle, WHITE);
}

float Entity_texture::GetAngle() {
	return this->angle;
}

void Entity_texture::SetAngle(float angle) {
	this->angle = angle;
}

void Entity_texture::AddAngle(float angle) {
	this->angle += angle;
}

Player::Player(Object_status st, bool is_render, const char* texture_path, float angle, bool is_visible_cam) : Entity_texture(st, is_render, texture_path, angle, true) {
	this->is_visible_cam = is_visible_cam;
}

bool Player::GetStatusCam() {
	return this->is_visible_cam;
}


Player::~Player() {
	
}

void Player::Update_keyboard() {
	if (IsKeyDown(this->key_move[0])) this->vector_move.y = -speed;
	else if (IsKeyDown(this->key_move[1])) this->vector_move.y = speed;
	else {
		this->vector_move.y = 0;
	}
	if (IsKeyDown(this->key_move[2])) this->vector_move.x = -speed;
	else if (IsKeyDown(this->key_move[3])) this->vector_move.x = speed;
	else {
		this->vector_move.x = 0;
	}
}

void Player::SetTargetCam(bool st) {
	if (this->is_visible_cam == st) Print("Warning: is_visible_cam code true");
	this->is_visible_cam = st;
}

void Player::Update_player() {
	this->Update_keyboard();
	this->move(this->vector_move.x, this->vector_move.y);
	this->draw();
}