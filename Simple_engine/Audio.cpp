#include <memory>
#include "Audio.h"
#include <raylib.h>

Music_player::Music_player() {
	this->music = std::make_unique<Music>();
	this->sound = std::make_unique<Sound>();
	this->second = 0;
}

Music_player::~Music_player() {
	if (is_work) {
		UnloadMusicStream(*music);
	}
	UnloadSound(*sound);
}

void Music_player::LoadMusic(const char* path) {
	*this->music = LoadMusicStream(path);
	PlayMusicStream(*this->music);
	this->is_work = true;
	this->total_second = GetMusicTimeLength(*this->music);
}

void Music_player::LoadAudio(const char* path) {
	*this->sound = LoadSound(path);
	PlaySound(*this->sound);
	this->is_work_sound = true;
}

void Music_player::UpdateMusicStreamClass() {
	UpdateMusicStream(*this->music);
	this->second = GetMusicTimePlayed(*this->music);
	if (((total_second - second) < 2) == 1) {
		StopMusicStream(*this->music);
		UnloadMusicStream(*this->music);
		this->is_work = false;
	}
}

