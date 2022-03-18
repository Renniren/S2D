#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef S2D_DEFINES
#define S2D_DEFINES

#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef S2D_SETTINGS
#define S2D_SETTINGS

string game_name = "S2D Game";
string game_debug_name = "S2D Test Game (Debug): ";

#endif

#ifndef S2D_EVENTS
#define S2D_EVENTS


#endif

#ifndef S2D_MACROS
#define S2D_MACROS

#define init_behavior ActiveObjects.push_back(&(*this))

#endif

RenderWindow* GAME_WINDOW;
sf::Event event;

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
	static bool res;
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

class object
{
public:
	int instance_id;

	virtual string to_string()
	{

		return "";
	}
};

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
		clamp(Scale, -1, 1);

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

float time::delta = 0, time::deltaUnscaled = 0;
Int64 time::current = 0, time::last = 0;
Time time::_time = Time();
Clock time::global_clock = Clock();

float time::Scale = 1;

class World
{
public:
	string name;
	Color clear_color;
};

class Level
{
public:
	string name;
	World world_settings;

	Level(string name, World settings)
	{
		this->name = name;
		this->world_settings = settings;
	}
};

World DefaultWorld = { "World", Color::Black };
World ActiveWorld = DefaultWorld;

Level* DefaultLevel = new Level(string("Default Level"), DefaultWorld);
Level* ActiveLevel = DefaultLevel;

//keeps record of every loaded texture, and their accompanying sprite to keep textures alive
vector<pair<Texture*, Sprite*>> LoadedTextures;
void CreateTexturePair(Texture* tex, Sprite* spr)
{
	LoadedTextures.push_back(pair<Texture*, Sprite*>(tex, spr));
}

Sprite CreateSprite(string texturepath)
{
	Texture* texture = new Texture();
	Sprite* ret;
	if (!texture->loadFromFile(texturepath)) return Sprite();
	ret = new Sprite(*texture);
	CreateTexturePair(texture, ret);
	ret->setOrigin(0.25f, 0.25f);
	return *ret;
}

class GameObject
{
public:
	enum simulate_flags { SimulateOnlyWhenLevelActive, SimulateAlways };


	Vector2f position, scale;
	Level* parent_level;
	Sprite sprite;
	simulate_flags flags = simulate_flags::SimulateOnlyWhenLevelActive;
	string name;

	float rotation;
	bool active, draw = true;
	static vector<GameObject*> ActiveObjects;

	void levelChanged()
	{

	}

	virtual void update(){}

	void tick()
	{
		if (!active) return;
		switch (this->flags)
		{
		case SimulateAlways:
			if (draw)
			{
				sprite.setPosition(position);
				sprite.setRotation(rotation);
				sprite.setScale(scale);
				GAME_WINDOW->draw(sprite);
			}
				
			update();
			break;

		case SimulateOnlyWhenLevelActive:
			if (parent_level->name != ActiveLevel->name) return;
			if (draw)
			{
				sprite.setPosition(position);
				sprite.setRotation(rotation);
				sprite.setScale(scale);
				GAME_WINDOW->draw(sprite);
			}

			update();
			break;
		}
	}

	GameObject(bool setActive)
	{
		active = setActive;
		parent_level = nullptr;
		rotation = 0;
		position = Vector2f(0, 0);
		name = "new WorldObject";
	}
};



class Camera : public GameObject
{
	float zoom = 10;

	Camera() : GameObject(true)
	{
		init_behavior;
	}
};

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

vector<GameObject*> GameObject::ActiveObjects = vector<GameObject*>();

void UpdateGameObjects()
{
	for (size_t i = 0; i < GameObject::ActiveObjects.size(); i++)
	{
		GameObject::ActiveObjects[i]->tick();
	}
}

class Physics
{
public:
	static Vector2f Gravity;

	enum CollisionShape { Box, Circle, Triangle, None };

	class PhysicsObject : public GameObject
	{
		float gravityInfluence = 0.01f;
	public:
		float mass = 1;
		float drag = 0;

		bool isStatic = false;
		bool respectsTime = true;

		Vector2f velocity;
		PhysicsObject() : GameObject(true)
		{
			init_behavior;
		}

		void update()
		{
			if (respectsTime)
			{
				velocity -= Gravity * gravityInfluence * time::delta;
				position += velocity * time::delta;
			}
			else
			{
				velocity -= Gravity * gravityInfluence * time::deltaUnscaled;
				position += velocity * time::deltaUnscaled;
			}
		}
	};
};


Vector2f Physics::Gravity = Vector2f(0, -9.81f);

class PhysicsTestObject : public Physics::PhysicsObject
{
public:
	PhysicsTestObject()
	{
		position = Vector2f(1, 4);
		scale = Vector2f(0.03, 0.03);
		sprite = CreateSprite("sprites\\circle.png");
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
		sprite = CreateSprite("sprites\\circle.png");
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
			position.x += speed * time::deltaUnscaled;
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
