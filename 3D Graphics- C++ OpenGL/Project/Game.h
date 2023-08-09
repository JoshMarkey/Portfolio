#pragma once
#include <SDL2/SDL.h>
#include "rend.h"
#include <vector>
//#include "Level.h"
#include "Player.h"
#include "Camera.h"
#include "Block.h"
#include "OrthoCamera.h"
#include <memory>
#include "SkyBox.h"
#include "Laser.h"

struct Laser;

struct Game
{
	Game();

	SDL_Window* m_window;

	std::shared_ptr<Player> m_player;
	std::shared_ptr < Camera> m_camera;
	std::shared_ptr < OrthoCamera> m_orthoCam;
	std::vector<Block> m_floor;

	void run();

	//Quad
	Vao m_Quad;

	std::shared_ptr<Texture> m_gameOver;

	//Player
	std::shared_ptr<Texture> m_playerTexture;
	std::shared_ptr<Model> m_playerModel;

	//Block
	void loadBlocks();
	std::shared_ptr<Model> m_blockModel;
	std::vector<std::shared_ptr<Texture>> m_blockTextures;

	//Skybox
	std::shared_ptr<Texture> m_skyBoxTexture;
	std::shared_ptr<SkyBox> m_skybox;
	std::shared_ptr<Shader> m_SkyBoxShader;

	//Laser
	std::shared_ptr<Model> m_LaserModel;
	std::shared_ptr<Model> m_SkyModel;
	std::shared_ptr<Texture> m_LaserTexture;
	std::shared_ptr<Laser> m_Laser;

	//shaders
	std::shared_ptr<Shader> m_lightShader;
	std::shared_ptr<Shader> m_GUIShader;
	std::shared_ptr<Shader> m_MergeShader;
	std::shared_ptr<Shader> m_LightKeyShader;
	std::shared_ptr<Shader> m_BlurShader;


	std::shared_ptr<RenderTexture> m_FirstRT;
	std::shared_ptr<RenderTexture> m_LightKeyRT;
	std::shared_ptr<RenderTexture> m_Blur1RT;
	std::shared_ptr<RenderTexture> m_Blur2RT;
	std::shared_ptr<RenderTexture> m_MergeRT;

	//Render Textures

	//std::vector<bool> m_downKeys;
	float m_deltaTime;

	glm::vec2 m_mouseDelta;
	bool pressW;
	bool pressA;
	bool pressS;
	bool pressD;
	bool pressSpace;

};

