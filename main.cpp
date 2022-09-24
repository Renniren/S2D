#include "S2D.h"
#include <time.h>       /* time */


sf::Event event;
int main()
{
	using namespace sf;
	using namespace std;
	srand(time(NULL));

	S2DRuntime* runtime = new S2DRuntime();
	RenderWindow window(VideoMode(800, 600), "window");
	runtime->GAME_WINDOW = &window;
	
	time::init();

	S2DRuntime::Instance = runtime;
	Camera* cam = new Camera();
	cam->isMain = true;
	TestPlayer* test = Instantiate(TestPlayer);
	PhysicsTestObject* test2 = Instantiate(PhysicsTestObject);
	UpdatableTest* test3 = Instantiate(UpdatableTest);
	ParticleSystem* ps = Instantiate(ParticleSystem);
	//test->parent_level = LevelManager::ActiveLevel;
	//test2->parent_level = LevelManager::ActiveLevel;
	//cam->parent_level = LevelManager::ActiveLevel;
	
	if (runtime->release_mode == S2D_RELEASE)
	{
		runtime->GAME_WINDOW->setTitle(game_name);
	}

	if (runtime->release_mode == S2D_DEBUG)
	{
		runtime->GAME_WINDOW->setTitle(game_debug_name + LevelManager::ActiveLevel->world_settings.name);
	}

	vector<TestPlayer*> plys = vector<TestPlayer*>();
	bool d;
	printf("init");
	while(runtime->GAME_WINDOW->isOpen())
	{

			/*#ifdef S2D_DEBUG
		
	#endif
	#ifndef S2D_DEBUG
			GAME_WINDOW->setTitle(game_name);
	#endif*/

		if(doClear) runtime->GAME_WINDOW->clear(LevelManager::ActiveLevel->world_settings.clear_color);

		while (runtime->GAME_WINDOW->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) runtime->GAME_WINDOW->close();
		}

		if (isKeyPressedTap(Keyboard::P))
		{
			if (!d)
			{
				cout << "sadfdf";
				printf("\ntest");
				for (size_t i = 0; i < 3; i++)
				{
					plys.push_back(new TestPlayer());
				}

				for (size_t i = 0; i < plys.size(); i++)
				{
					plys[i]->Destroy();
				}
				TextureManager::RegenerateLoadedTextureList();
				d = true;
				printf("\nCompleted test");

			}
		}
		else
		{
			d = false;
		}

		time::update();
		ClassUpdater::UpdateUpdatables();
		ClassUpdater::UpdateGameObjects();
		//ClassUpdater::PostUpdateUpdatables();
		//ClassUpdater::PostUpdateGameObjects();
		runtime->GAME_WINDOW->display();
		if (TOO_MANY_TEXTURES) TextureManager::RegenerateLoadedTextureList();
	}


  return 0;
}
