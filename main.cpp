#include "S2D.h"

sf::Event event;
int main()
{
	S2DRuntime* runtime = new S2DRuntime();

	RenderWindow window(VideoMode(800, 600), "window");
	runtime->GAME_WINDOW = &window;
	
	time::init();
	
	S2DRuntime::Instance = runtime;

	TestPlayer* test = new TestPlayer();
	PhysicsTestObject* test2 = new PhysicsTestObject();
	test->parent_level = LevelManager::ActiveLevel;
	test2->parent_level = LevelManager::ActiveLevel;
	while(runtime->GAME_WINDOW->isOpen())
	{
	#ifdef S2D_DEBUG
		runtime->GAME_WINDOW->setTitle(game_debug_name + LevelManager::ActiveLevel->world_settings.name);
	#endif
	#ifndef S2D_DEBUG
			GAME_WINDOW->setTitle(game_name);
	#endif

		if(doClear) runtime->GAME_WINDOW->clear(LevelManager::ActiveLevel->world_settings.clear_color);

		while (runtime->GAME_WINDOW->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) runtime->GAME_WINDOW->close();
		}

		time::update();
		UpdateGameObjects();
		
		runtime->GAME_WINDOW->display();
	}


  return 0;
}
