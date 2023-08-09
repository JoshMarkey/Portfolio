#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <vector>
#include "rend.h"
#include "Game.h"


int main(int argc, char* argv[])
{
	
	Game game;
	game.run();
	return 0;
}
