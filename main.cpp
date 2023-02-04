#include "S2D.h"
#include <time.h>       /* time */
#include<process.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

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

void DoDebug()
{
	using namespace std;
	static float f = 0, total = 0;
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

	static bool st = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
	{
		if (!st)
		{
			UpdateEngine(60); // Simulate 60 frames of gameplay at once.
			st = true;
		}
	}
	else
	{
		st = false;
	}
}

//Implement some way of building a pipe to the C# side of the engine that'd handle data serialization.
//https://stackoverflow.com/questions/11196379/send-data-to-another-c-program
//https://stackoverflow.com/questions/1906561/communication-between-c-and-c-sharp-through-pipe

int main()
{
	using namespace std;
	srand(time(NULL));
	InitializeEngine();
	
	stringstream ss;
	ss << GetWorkingDirectory().c_str();
	ss << "\\bin\\serializer.exe";

	const char* p = ss.str().c_str();

	//system(ss.str().c_str());

	cout << GetWorkingDirectory() << endl;
	Camera* cam = new Camera();
	cam->isMain = true;
	TestPlayer* test = Instantiate(TestPlayer);
	PhysicsTestObject* test2 = Instantiate(PhysicsTestObject);
	UpdatableTest* test3 = Instantiate(UpdatableTest);
	ParticleSystem* ps = Instantiate(ParticleSystem);
	ps->emitting = true;
	
	
	GameObject* floor = new GameObject();
	floor->MakeStandalone();
	floor->sprite = TextureManager::CreateSprite("resources\\sprites\\squareSmall.png");
	floor->position = Vector2(-20, 40);
	floor->scale = Vector2(0.1f, 0.1f);

	Rigidbody* rb = AddComponent<Rigidbody>(floor);
	rb->isStatic = true;
	rb->UpdateRigidbody();

	BehaviorInheritanceTest* bh = AddComponent<BehaviorInheritanceTest>(cam);
	GetComponent<BehaviorInheritanceTest>(cam)->GetComponentWorksCheck();
	
	printf("init");
	while (S2DRuntime::Instance->GAME_WINDOW->isOpen())
	{
		while (S2DRuntime::Instance->GAME_WINDOW->pollEvent(event))
		{
			//ImGui::SFML::ProcessEvent(*S2DRuntime::Instance->GAME_WINDOW, event);
			if (event.type == sf::Event::Closed) S2DRuntime::Instance->GAME_WINDOW->close();
		}
		//floor->sprite = TextureManager::CreateSprite("\\sprites\\square.png");
		S2DRuntime::Instance->GAME_WINDOW->clear(LevelManager::ActiveLevel->level->world_settings.clear_color);
		DoDebug();
		UpdateEngine();
		S2DRuntime::Instance->GAME_WINDOW->display();
		if (TOO_MANY_TEXTURES) TextureManager::RegenerateLoadedTextureList();
	}

	LevelSerializer().SerializeLevel();

	system("pause");
	return 0;
}
