#include "S2D.h"
#include <time.h>       /* time */
#include<process.h>

sf::Event event;

void RunDestroyTest()
{
	using namespace sf;
	using namespace std;
	
	static vector<TestPlayer*> plys = vector<TestPlayer*>();
	static bool d = false;
	
	if (isKeyPressedTap(Keyboard::P))
	{
		if (!d)
		{
			cout << "sadfdf";
			printf("\ntest");
			for (size_t i = 0; i < 30; i++)
			{
				plys.push_back(new TestPlayer());
			}

			for (size_t i = 0; i < plys.size(); i++)
			{
				plys[i]->RequestDestroy();
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
}

bool SaveLevel()
{
	//Here, a C# program will be called to convert our level to a JSON file since C++ can't do that for us.
	//For later reference: 
	//https://stackoverflow.com/questions/14821787/c-program-to-execute-another-program-with-command-line-arguments
	// https://gotask.net/programming/serialize-and-deserialize-object-in-cpp-using-rapidjson/
	// https://github.com/eyalmolad/gotask/blob/master/C%2B%2B/RapidJSONSample/DataSample.json
	//system("ProjectPath\\Converter.exe\\" + Arguments)
	return false;
}

int main()
{
	using namespace std;
	srand(time(NULL));
	InitializeEngine();
	
	Camera* cam = new Camera();
	cam->isMain = true;
	TestPlayer* test = Instantiate(TestPlayer);
	PhysicsTestObject* test2 = Instantiate(PhysicsTestObject);
	UpdatableTest* test3 = Instantiate(UpdatableTest);
	ParticleSystem* ps = Instantiate(ParticleSystem);
	ps->emitting = true;
	

	AddComponent<BehaviorInheritanceTest>(cam);
	GetComponent<BehaviorInheritanceTest>(cam)->GetComponentWorksCheck();

	float f = 0, total = 0;

	int x = 2;
	int y = 6;
	int xy = x | y;
	cout << xy << endl;

	printf("init");
	while(S2DRuntime::Instance->GAME_WINDOW->isOpen())
	{
		while (S2DRuntime::Instance->GAME_WINDOW->pollEvent(event))
		{ 
			if (event.type == sf::Event::Closed) S2DRuntime::Instance->GAME_WINDOW->close();
			//if (event.type == sf::Event::Resized) S2DRuntime::Instance->GAME_WINDOW->close();
		}

		f += time::delta;
		total += time::delta;
		if (f >= 3)
		{
			cout << time::delta << endl;
			cout << total << endl;
			cout << "3 seconds have passed" << endl;
			f = 0;
		}

		RunDestroyTest();
		S2DRuntime::Instance->GAME_WINDOW->clear(LevelManager::ActiveLevel->level->world_settings.clear_color);
		
		UpdateEngine();
		
		S2DRuntime::Instance->GAME_WINDOW->display();
		if (TOO_MANY_TEXTURES) TextureManager::RegenerateLoadedTextureList();
	}

	return 0;
}
