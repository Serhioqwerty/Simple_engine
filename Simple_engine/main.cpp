#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include "Engine.h"

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));

	Engine engine;
	engine.Init_engine();


	engine.UpdateEngine();
}