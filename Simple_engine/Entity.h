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
	bool is_render;
	bool is_suicide = false;
	std::string flag;
private:
	
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

	void SetRender(bool is);
	bool GetRender();

	void SetSuicide(bool is);
	bool GetSuicide();

	void SetFlag(std::string flag);
	std::string GetFlag();
};


class Entity_text : public Entity {
private:
	int font_size;
	std::string text;
	Color color_text;

public:
	Entity_text(Object_status st, bool is_render, bool is_cam, bool is_colision, int font_size, Color color_text, std::string text);
	~Entity_text() override;
	void draw() override;
	void SetText(std::string text);
};

class Entity_texture : public Entity {
private:
	float angle;
protected:
	std::weak_ptr<Texture2D> texture;
	float scale;

	std::string name_texture;
public:
	Entity_texture(Object_status st, bool is_render, float angle, bool is_cam, bool is_colision);
   ~Entity_texture() override;
    void draw() override;
	float GetAngle();
	void SetTexture(std::shared_ptr<Texture2D> texture);
	void SetNameTexture(std::string name);
	std::string GetNameTexture();
	void SetAngle(float angle);
	void AddAngle(float angle);
	
	

};

