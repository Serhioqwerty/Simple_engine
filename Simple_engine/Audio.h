#pragma once
#include <raylib.h>
#include <memory>


class Music_player {
private:
	std::unique_ptr<Music>music;
	std::unique_ptr<Sound>sound;
	bool is_work = false;
	bool is_work_sound = false;
	float second;
	float total_second;
public:
	Music_player();
	~Music_player();
	
	void LoadMusic(const char* path);
	void LoadAudio(const char* path);

	void UpdateMusicStreamClass();
};