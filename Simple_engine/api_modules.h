#pragma once
#include <memory>
#include <vector>
#include <raylib.h>
#include "Entity.h"
#include <cmath>

void GetPointerEntityTexture(std::shared_ptr<Entity>& entity, std::shared_ptr<Entity_texture>& entity_texture);


//секция где функции просто не могут разделяться на С++ и Header

//Для преобразование из оригинального обьекта в любой обьект (НУЖЕН ОБЬЕКТ НАСЛЕДНИК ENTITY)
template<typename T>


void GetPointerObject(std::shared_ptr<Entity>& entity, std::shared_ptr<T>& object) {
	object = std::dynamic_pointer_cast<T>(entity);
}


//эта функция преобразует из одного класса в другой (НУЖНО ЧТОБЫ ОДИН КЛАСС НАЛСЕДОВАЛ)
template<typename first_class, typename second_class>

void GetPointerObjectFromClass(std::shared_ptr<first_class>& entity, std::shared_ptr<second_class>& object) {
	object = std::dynamic_pointer_cast<second_class>(entity);
}

template<typename first_class_obj, typename second_class_obj>

float GetDistance(Entity object1, Entity object2) {
	Vector2 pos1 = object1->GetPos();
	Vector2 pos2 = object2->GetPos();
	return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}


//СТРОГО ДЛЯ ENTITY И ЕГО НАСЛЕДНИКАХ И ТОЛЬКО ЕСЛИ ЭТО УКАЗАТЕЛЬ
template<typename first_class_obj, typename second_class_obj>
float GetDistance(first_class_obj& Object_1, second_class_obj& Object_2) {
	Vector2 o1 = Object_1->GetPos();
	Vector2 o2 = Object_2->GetPos();
	return sqrt((o1.x - o2.x) * (o1.x - o2.x) + (o1.y - o2.y) * (o1.y - o2.y));
}

template<typename... Arg>
void Print(Arg&&... arg) {
	(std::cout << ... << arg) << std::endl;
}


//СТРОГО ENTITY И ЕГО НАСЛЕДНИКОВ И ТЕХ, У КОГО ЕСТЬ МЕТОД GETPOS()

