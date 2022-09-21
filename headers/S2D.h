#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef GUARD_S2D_DEFINES
#define GUARD_S2D_DEFINES

//#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef GUARD_S2D_SETTINGS
#define GUARD_S2D_SETTINGS

string game_name = "S2D Game";
string game_debug_name = "S2D Test Game (Debug): ";

#endif

#ifndef GUARD_S2D_EVENTS
#define GUARD_S2D_EVENTS


#endif

#ifndef GUARD_S2D_MACROS
#define GUARD_S2D_MACROS

#define init_behavior ActiveObjects.push_back(this)

#define TOO_MANY_TEXTURES TextureManager::LoadedTextures.size() >= 256
#define S2D_DEBUG 1
#define S2D_RELEASE 0
#define IS_DEBUG (S2DRuntime::get()->release_mode == S2D_DEBUG)

#endif

enum SimulationMode { SimulateOnlyWhenLevelActive, SimulateAlways };

class object
{
public:
	int instance_id;

	virtual string to_string()
	{
		return "";
	}
};

class Updatable
{
public:
	SimulationMode flags = SimulationMode::SimulateOnlyWhenLevelActive;

	bool active;
	virtual void update() {}
};


class World
{
public:
	string name;
	Color clear_color;

	World()
	{

	}

	World(string name, Color bg)
	{
		this->name = name;
		this->clear_color = bg;
	}
};

class Level
{
public:
	string name;
	World world_settings;
	int id;

	Level(string name, World settings)
	{
		this->name = name;
		this->world_settings = settings;
	}
};

class S2DRuntime
{
public:
	int release_mode = S2D_RELEASE;
	RenderWindow* GAME_WINDOW = nullptr;
	
	static S2DRuntime* Instance;
	static S2DRuntime* get()
	{
		static bool n = (Instance == nullptr);
		if (n)
		{
			Instance = new S2DRuntime();
		}

		return Instance;
	}
};

enum LoadLevelType {Override, Background};
class LevelManager
{
public:
	static Level* DefaultLevel;
	static Level* ActiveLevel;
	vector<Level*>LoadedLevels = vector<Level*>();
	
	void LoadLevel(Level level, LoadLevelType mode = LoadLevelType::Override)
	{
		switch (mode)
		{
			case LoadLevelType::Override:

			break;

			case LoadLevelType::Background:

			break;
		}
	}

	void SetLevel(Level* destination)
	{
		if (destination == nullptr)
		{
			printf("\nError when setting level: provided level was null.");
			return;
		}
		if (ActiveLevel != nullptr)
		{
			if (destination->name != ActiveLevel->name)
			{
				ActiveLevel = destination;
			}
		}
	}
};

Level* LevelManager::DefaultLevel = new Level(string("Default Level"), World("World", Color::Black));
Level* LevelManager::ActiveLevel = LevelManager::DefaultLevel;

double dist(Vector2f a, Vector2f b)
{
	return sqrt((double)(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

class Physics
{
public:
	static Vector2f Gravity;
	enum collisionShape { Box, Circle, Triangle, None };

	bool CheckCirclevsCircle(Vector2f a, Vector2f b, float rad1, float rad2)
	{
		return dist(a, b) < rad1 || dist(b, a) < rad2;
	}

	
};


Vector2f Physics::Gravity = Vector2f(0, 9.81f);

void test()
{
	
}


S2DRuntime* S2DRuntime::Instance = nullptr;

bool doClear = true;

void clamp(float& num, float&& lower, float&& upper)
{
	if (num < lower) num = lower;
	if (num > upper) num = upper;
}

void clamp(int& num, int lower, int upper)
{
	if (num < lower) num = lower;
	if (num > upper) num = upper;
}



bool isKeyPressedTap(sf::Keyboard::Key query)
{
	static bool res = false;
	if (Keyboard::isKeyPressed(query))
	{
		if (!res)
		{
			res = true;
			return true;
		}
	}
	else
	{
		res = false;
	}
	return false;
}


class time
{
	static Clock global_clock;
	static Time _time;
	static Int64 last, current;

public:
	static float delta, deltaUnscaled;
	static float Scale;

	static void init()
	{
		global_clock = Clock();
	}

	static void update()
	{
		clamp(Scale, 0, 1);

		_time = global_clock.getElapsedTime();
		current = _time.asMilliseconds();
		delta = current - last;
		deltaUnscaled = delta;

		delta /= 10;
		deltaUnscaled /= 10;

		delta *= Scale;
		last = current;
	}
};

float		time::Scale					= 1;
float		time::delta					= 0, 
			time::deltaUnscaled	= 0;
Int64	time::current				= 0, 
			time::last						= 0;
Time		time::_time					= Time();
Clock	time::global_clock		= Clock();

//Created so that when a GameObject needs to be destroyed, we can also clean up the Sprite/Texture it also created.
struct S2DTextureSpritePair
{
public:
	int id;
	Texture* tex;
	Sprite* sprite;

	S2DTextureSpritePair(int n, Texture* t, Sprite* s)
	{
		this->id = n;
		this->tex = t;
		this->sprite = s;
	}
};

struct GameObjectSprite
{
public:
	int tsp_id;
	Sprite s;

	GameObjectSprite()
	{
		tsp_id = -1;
		s = Sprite();
	}

	GameObjectSprite(int tsp_id, Sprite s)
	{
		this->tsp_id = tsp_id;
		this->s = s;
	}
};

class TextureManager
{
public:
	static vector<S2DTextureSpritePair> LoadedTextures;
	static S2DTextureSpritePair CreateTexturePair(Texture* tex, Sprite* spr)
	{
		S2DTextureSpritePair tsp = S2DTextureSpritePair(LoadedTextures.size(), tex, spr);
		LoadedTextures.push_back(tsp);
		return tsp;
	}

	static void RegenerateLoadedTextureList()
	{
		int null_id = -1;
		vector<S2DTextureSpritePair> new_list = vector<S2DTextureSpritePair>();
		for (size_t i = 0; i < LoadedTextures.size(); i++)
		{
			if (LoadedTextures[i].id != null_id)
			{
				new_list.push_back(LoadedTextures[i]);
			}
		}
		LoadedTextures.clear();
		LoadedTextures = new_list;
	}

	static void CleanUpTexturePair(int id)
	{
		for (size_t i = 0; i < LoadedTextures.size(); i++)
		{
			if (LoadedTextures[i].id == id)
			{
				delete LoadedTextures[i].tex;
				delete LoadedTextures[i].sprite;
				LoadedTextures[i].id = -1;
				break;
			}
		}
	}

	static GameObjectSprite CreateSprite(string texturepath)
	{
		Texture* texture = new Texture();
		Sprite* ret;
		if (!texture->loadFromFile(texturepath)) return GameObjectSprite(-1, Sprite());
		ret = new Sprite(*texture);
		S2DTextureSpritePair s = CreateTexturePair(texture, ret);
		ret->setOrigin(0.25f, 0.25f);
		return GameObjectSprite(s.id, *ret);
	}
};

vector<S2DTextureSpritePair> TextureManager::LoadedTextures = vector<S2DTextureSpritePair>();

class GameObject : public Updatable
{
public:
	Vector2f position, scale;
	Level* parent_level;
	GameObjectSprite sprite;
	string name;
	

	float mass = 1;
	float drag = 0;
	float gravityInfluence = 0.01f;

	bool isStatic = false;
	bool hasPhysics = false;
	bool respectsTime = true;

	Physics::collisionShape CollisionShape;
	Vector2f velocity;
	
	float rotation;
	bool active, draw = true;
	static vector<GameObject*> ActiveObjects;

	void levelChanged()
	{

	}

	void updatePhysics()
	{
		if (!hasPhysics) return;
		if (respectsTime)
		{
			velocity += Physics::Gravity * gravityInfluence * time::delta;
			position += velocity * time::delta;
		}
		else
		{
			velocity -= Physics::Gravity * gravityInfluence * time::deltaUnscaled;
			position += velocity * time::deltaUnscaled;
		}
	}

	void Destroy()
	{
		TextureManager::CleanUpTexturePair(sprite.tsp_id);
		delete this;
	}

	void tick()
	{
		if (!active) return;
		if(parent_level == nullptr)
		{
			printf((string("\nGameObject \"").append(name).append("\" has no parent Scene!")).c_str());
			__debugbreak();
			return;
		}
		switch (this->flags)
		{
		case SimulateAlways:
			if (draw && &sprite.s != nullptr)
			{
				updatePhysics();
				sprite.s.setPosition(position);
				sprite.s.setRotation(rotation);
				sprite.s.setScale(scale);
				S2DRuntime::get()->GAME_WINDOW->draw(sprite.s);
			}
				
			update();
			break;

		case SimulateOnlyWhenLevelActive:
			if (parent_level->name != LevelManager::ActiveLevel->name) return;
			if (draw && &sprite.s != nullptr)
			{
				updatePhysics();
				sprite.s.setPosition(position);
				sprite.s.setRotation(rotation);
				sprite.s.setScale(scale);
				S2DRuntime::get()->GAME_WINDOW->draw(sprite.s);
			}

			update();
			break;
		}
	}

	GameObject(bool setActive)
	{
		active = setActive;
		parent_level = LevelManager::ActiveLevel;
		rotation = 0;
		position = Vector2f(0, 0);
		name = "new WorldObject";
	}
};

class Camera : public GameObject
{
public:
	float zoom = 10;
	sf::View view;

	Camera() : GameObject(true)
	{
		init_behavior;
		name = "new Camera";
		draw = false;
		view = sf::View();
	}

	void update()
	{
		view.move(position);
		view.rotate(rotation);
	}
};



vector<GameObject*> GameObject::ActiveObjects = vector<GameObject*>();

void UpdateGameObjects()
{
	for (size_t i = 0; i < GameObject::ActiveObjects.size(); i++)
	{
		if (GameObject::ActiveObjects[i] == nullptr)
		{
			continue;
		}
		GameObject::ActiveObjects[i]->tick();
	}
}



class PhysicsTestObject : public GameObject
{
public:
	PhysicsTestObject() : GameObject(true)
	{
		init_behavior;
		hasPhysics = true;
		position = Vector2f(1, 4);
		scale = Vector2f(0.03, 0.03);
		sprite = TextureManager::CreateSprite("sprites\\circle.png");
	}
};

class TestPlayer : public GameObject, public object
{
public:
	float speed = 4.0f;

	TestPlayer() : GameObject(true)
	{
		init_behavior;

		scale = Vector2f(0.03, 0.03);
		sprite = TextureManager::CreateSprite("sprites\\circle.png");
	}

	void update()
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			position.y -= speed * time::deltaUnscaled;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			position.y += speed * time::deltaUnscaled;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			position.x -= speed * time::deltaUnscaled;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			position.x += speed * time::delta;
		}

		if (Keyboard::isKeyPressed(Keyboard::X))
		{
			printf("test");
			Destroy();
		}



		float incr = 0.02f;
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			time::Scale += incr * time::deltaUnscaled;
		}

		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			time::Scale -= incr * time::deltaUnscaled;
		}

		if (isKeyPressedTap(Keyboard::Y))
		{
			draw = !draw;
		}
	}
};



#endif
