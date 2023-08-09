#include "Game.h"

Game::Game()
{
	//Init all of SDL/OpenGL
	m_window = SDL_CreateWindow("OpenGL_Demo",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 800, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	SDL_GL_SetSwapInterval(-1);

	SDL_WarpMouseInWindow(NULL, 400, 400);

	//Input variables
	m_mouseDelta = glm::vec2(0, 0);
	pressW = false;
	pressA = false;
	pressS = false;
	pressD = false;
	pressSpace = false;

	//Shaders
	m_lightShader = std::make_shared<Shader>("Shaders/light/FragShader.txt", "Shaders/light/VertShader.txt");
	m_GUIShader = std::make_shared<Shader>("Shaders/GUI/FragShader.txt", "Shaders/GUI/VertShader.txt");
	m_SkyBoxShader = std::make_shared<Shader>("Shaders/SkyBox/FragShader.txt", "Shaders/SkyBox/VertShader.txt");

	//Bloom Shaders
	m_BlurShader = std::make_shared<Shader>("Shaders/PostProcess/blur.txt", "Shaders/GUI/VertShader.txt");
	m_MergeShader = std::make_shared<Shader>("Shaders/PostProcess/merge.txt", "Shaders/GUI/VertShader.txt");
	m_LightKeyShader = std::make_shared<Shader>("Shaders/PostProcess/threshold.txt", "Shaders/GUI/VertShader.txt");


	//GUI VAO Quad
	std::shared_ptr<Vbo> pos = std::make_shared<Vbo>();
	pos->add(glm::vec3(-0.5f, 0.70f, 0.0f));
	pos->add(glm::vec3(-0.5f, -0.70f, 0.0f));
	pos->add(glm::vec3(0.5f, -0.70f, 0.0f));
	pos->add(glm::vec3(0.5f, -0.70f, 0.0f));
	pos->add(glm::vec3(0.5f, 0.70f, 0.0f));
	pos->add(glm::vec3(-0.5f, 0.70f, 0.0f));


	std::shared_ptr<Vbo> coords = std::make_shared<Vbo>();
	coords->add(glm::vec2(0.0f, 0.0f));
	coords->add(glm::vec2(0.0f, 1.0f));
	coords->add(glm::vec2(1.0f, 1.0f));
	coords->add(glm::vec2(1.0f, 1.0f));
	coords->add(glm::vec2(1.0f, 0.0f));
	coords->add(glm::vec2(0.0f, 0.0f));

	m_Quad = Vao();
	m_Quad.addVbo(pos);
	m_Quad.addVbo(coords);

	//Laser
	m_LaserTexture = std::make_shared<Texture>("Models/Laser/Texture.png");
	m_LaserModel = std::make_shared<Model>("Models/Laser/Model.obj");

	//Player
	m_playerTexture = std::make_shared<Texture>("Models/Steve/Texture.png");
	m_playerModel = std::make_shared<Model>("Models/Steve/Model.obj");

	//load all block textures
	loadBlocks();

	for (int j = -1; j < 2; j++)
	{
		for (int i = -1; i < 10; i++)
		{
			m_floor.push_back(Block(this, glm::vec3(i, -1, j)));
		}
	}

	//Skybox
	m_skyBoxTexture = std::make_shared<Texture>("Models/SkyBox/night.png");
	m_SkyModel = std::make_shared<Model>("Models/SkyBox/Cube.obj");
	m_skybox = std::make_shared<SkyBox>(this);

	//GUI Texture
	m_gameOver = std::make_shared<Texture>("Models/GameOver/GameOver.png");

	//GameObjects
	m_Laser = std::make_shared<Laser>(this);
	m_player = std::make_shared<Player>(this);
	m_camera = std::make_shared<Camera>(this);
	m_orthoCam = std::make_shared<OrthoCamera>(this);

}

void Game::run()
{
	bool playing = true;
	bool running = true;
	SDL_Event e = { 0 };
	std::vector < double > fps_times;

	bool dm = false;
	bool dm2 = false;
	bool flicker = false;

	unsigned int lastTime = SDL_GetTicks();
	unsigned int currentTime;

	while (running)
	{
		// Calculate delta time
		currentTime = SDL_GetTicks();
		float deltaT = (float)(currentTime - lastTime) / 1000;
		lastTime = currentTime;


		m_mouseDelta.x = 0;
		m_mouseDelta.y = 0;
		//This resets the bloom render textures on each loop to clear all data. 
		//Without it, the game only runs a single frame
		m_FirstRT = std::make_shared<RenderTexture>(800, 800);
		m_Blur1RT = std::make_shared<RenderTexture>(800, 800);
		m_Blur2RT = std::make_shared<RenderTexture>(800, 800);
		m_MergeRT = std::make_shared<RenderTexture>(800, 800);
		m_LightKeyRT = std::make_shared<RenderTexture>(800, 800);




		//get events
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				//this bool stops the camera teleporting when you initially enter the mouse into the window
				dm = true;
				if (dm2)
				{
					m_mouseDelta.x += e.motion.x - 400;
					m_mouseDelta.y += e.motion.y - 400;
				}
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_w)
				{
					pressW = true;
				}
				else if (e.key.keysym.sym == SDLK_a)
				{
					pressA = true;
				}
				else if (e.key.keysym.sym == SDLK_s)
				{
					pressS = true;
				}
				else if (e.key.keysym.sym == SDLK_d)
				{
					pressD = true;
				}
				else if (e.key.keysym.sym == SDLK_SPACE)
				{
					pressSpace = true;
				}
			}
			else if (e.type == SDL_KEYUP)
				if (e.key.keysym.sym == SDLK_w)
				{
					pressW = false;
				}

				else if (e.key.keysym.sym == SDLK_a)
				{
					pressA = false;
				}
				else if (e.key.keysym.sym == SDLK_s)
				{
					pressS = false;
				}
				else if (e.key.keysym.sym == SDLK_d)
				{
					pressD = false;
				}
				else if (e.key.keysym.sym == SDLK_SPACE)
				{
					pressSpace = false;
				}
		}
		//Send mouse to center of screen
		SDL_WarpMouseInWindow(NULL, 400, 400);
		if (dm)
		{
			dm2 = true;
		}
		//Run all Tick functions of game objects
		if (playing)
		{
			m_Laser->tick(deltaT);

			playing = m_player->tick(deltaT);

			m_camera->tick(deltaT);
		}
		/////////RENDER//////////////


		//Prepare matrices to be bound
		glm::mat4 GUIModelMat = glm::scale(glm::translate(glm::mat4(1), glm::vec3(400, 400, 0)), glm::vec3(800, 572, 1));
		glm::mat4 GUIProjectionMat = m_orthoCam->getProjection();

		m_BlurShader->bindMatrix("u_Projection", GUIProjectionMat);
		m_MergeShader->bindMatrix("u_Projection", GUIProjectionMat);
		m_LightKeyShader->bindMatrix("u_Projection", GUIProjectionMat);

		m_LightKeyShader->bindMatrix("u_Model", GUIModelMat);
		m_MergeShader->bindMatrix("u_Model", GUIModelMat);
		m_BlurShader->bindMatrix("u_Model", GUIModelMat);

		//Clear shader ready for a new frame
		m_lightShader->clear();

		//Bind first Render Texture
		//This texture allows me to do bloom
		m_FirstRT->bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Render the skybox first so that everything else is ontop
		m_skybox->render(m_camera->getView(), m_camera->getProjection());
		m_Laser->render(m_camera->getView(), m_camera->getProjection());

		for (int i = 0; i < m_floor.size(); i++)
		{
			m_floor[i].render(m_camera->getView(), m_camera->getProjection());
		}

		m_player->render(m_camera->getView(), m_camera->getProjection());

		m_FirstRT->unbind();

		//BLOOM
		
		//Find areas on the screen which are brightest
		m_LightKeyRT->bind();
		m_LightKeyShader->renderRT(&m_Quad, m_FirstRT->getTexture());
		m_LightKeyRT->unbind();

		//initial blue using brightest pixels
		m_Blur1RT->bind();
		m_BlurShader->renderRT(&m_Quad, m_LightKeyRT->getTexture());
		m_Blur1RT->unbind();
		//further blur using ping-pong render textures
		for (int i = 0; i < 4; i++)
		{
			m_Blur2RT->bind();
			m_BlurShader->renderRT(&m_Quad, m_Blur1RT->getTexture());
			m_Blur2RT->unbind();

			m_Blur1RT->bind();
			m_BlurShader->renderRT(&m_Quad, m_Blur2RT->getTexture());
			m_Blur1RT->unbind();
		}
		
		//add the original scene to the blured texture using a special render function
		m_MergeRT->bind();

		m_MergeShader->render2Textures(&m_Quad, "u_Texture2",m_FirstRT->getTexture(),"u_Texture1", m_Blur1RT->getTexture());
		m_MergeRT->unbind();
		

		//render the fnial texture to the screen
		m_GUIShader->bindOrthoMatrix(GUIProjectionMat, GUIModelMat);

		m_GUIShader->renderRT(&m_Quad, m_MergeRT->getTexture());

		//if the player has lost, display gameover
		if (!playing)
		{
			GUIModelMat = glm::scale(glm::translate(glm::mat4(1), glm::vec3(400, 400, 0)), glm::vec3(400, 200, 0));
			m_GUIShader->bindOrthoMatrix(GUIProjectionMat, GUIModelMat);

			m_GUIShader->renderOrtho(&m_Quad, m_gameOver.get());
		}

		//push rendered window onto screen
		SDL_GL_SwapWindow(m_window);		
	}
}

//This was used previously for many textures however is redundant now
void Game::loadBlocks()
{
	//Block
	m_blockModel = std::make_shared<Model>("Models/Block/Cube/Cube.obj");
	//Textures
	m_blockTextures = std::vector<std::shared_ptr<Texture>>();
	m_blockTextures.push_back(std::make_shared<Texture>("Models/Block/Texture/GRASS.png"));
}

