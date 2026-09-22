#include <memory>
#include <vector>
#include <raylib.h>
#include "Engine.h"
#include "Entity.h"
#include <iostream>

void GetPointerEntityTexture(std::shared_ptr<Entity>& entity, std::shared_ptr<Entity_texture>& entity_texture) {
	entity_texture = std::dynamic_pointer_cast<Entity_texture>(entity);
	if (entity_texture == nullptr) {
		std::cout << "return nullptr!" << std::endl;
	}
}



