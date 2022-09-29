#ifndef S2D_MAIN_HEADER
#define S2D_MAIN_HEADER

#include <string>
#include <vector>
#include<box2d.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include<functional>
#include <SFML/Graphics.hpp>

#ifndef GUARD_S2D_DEFINES
#define GUARD_S2D_DEFINES

//#define S2D_DEBUG

#endif // !S2D_DEFINES

#ifndef GUARD_S2D_SETTINGS
#define GUARD_S2D_SETTINGS

std::string game_name = "S2D Game";
std::string game_debug_name = "S2D Test Game (Debug): ";

#endif

#ifndef GUARD_S2D_EVENTS
#define GUARD_S2D_EVENTS


#endif

#ifndef GUARD_S2D_MACROS
#define GUARD_S2D_MACROS

//Macros for static class member definitons. Unnecessary, but sometimes convenient.
#define MStaticDefinition(type, cls, name) type cls::name = type()
#define MStaticPointerDefinition(type, cls) type cls::type = new type()

#define Instantiate(x) new x()
#define init_behavior ActiveObjects.push_back(this)
#define init_updatable UpdatableObjects.push_back(this)

#define TOO_MANY_TEXTURES TextureManager::LoadedTextures.size() >= 256
#define S2D_DEBUG 1
#define S2D_RELEASE 0
#define IS_DEBUG (S2DRuntime::get()->release_mode == S2D_DEBUG)

#endif

double dist(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((double)(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

int random(int min, int max)
{
	std::random_device rseed;
	std::mt19937 rng(rseed());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

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

float random(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

enum SimulationMode { SimulateOnlyWhenLevelActive, SimulateAlways };
enum DrawMode { DrawWhenLevelActive, DrawAlways, DontDraw };

class object
{
public:
	int instance_id;

	virtual std::string to_string()
	{
		return "";
	}
};

struct Vector2
{
public:
	float x, y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}


	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const Vector2& d)
	{
		this->x = d.x;
		this->y = d.y;
	}

	inline Vector2 operator * (float n)
	{
		this->x *= n;
		this->x *= n;
		return *this;
	}

	inline Vector2 operator = (Vector2 n)
	{
		this->x = n.x;
		this->y = n.y;
		return *this;
	}

	inline Vector2 operator *= (float n)
	{
		this->x *= n;
		this->y *= n;
		return *this;
	}

	inline Vector2 operator += (Vector2 other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2 operator -= (Vector2 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	
	//Operators defined for compatibility

	inline Vector2 operator += (sf::Vector2f other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2 operator -= (sf::Vector2f other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	inline Vector2 operator = (sf::Vector2f n)
	{
		this->x = n.x;
		this->y = n.y;
		return *this;
	}

	inline operator sf::Vector2f()
	{
		return sf::Vector2f(this->x, this->y);
	}

	inline operator b2Vec2()
	{
		return b2Vec2(this->x, this->y);
	}
};

class Updatable
{
public:
	SimulationMode flags = SimulationMode::SimulateOnlyWhenLevelActive;

	bool u_active;
	virtual void update() {}
	virtual void post_update() {}
	virtual void onDestroyed(){}
	void u_tick()
	{
		if(u_active)update();
	}

	void u_post_update()
	{
		if (this == nullptr) return;

		if (u_active)post_update();
	}

	void destroyed() { onDestroyed(); }

	static std::vector<Updatable*> UpdatableObjects;
};

class Physics
{
public:
	static Vector2 Gravity;
	enum collisionShape { Box, Circle, Triangle, None };

	bool CheckCirclevsCircle(sf::Vector2f a, sf::Vector2f b, float rad1, float rad2)
	{
		return dist(a, b) < rad1 || dist(b, a) < rad2;
	}
};

class World
{
public:
	std::string name;
	sf::Color clear_color;

	World()
	{

	}

	World(std::string name, sf::Color bg)
	{
		this->name = name;
		this->clear_color = bg;
	}
};

class Level
{
public:
	std::string name;
	World world_settings;
	int id;

	Level(std::string name, World settings)
	{
		this->name = name;
		this->world_settings = settings;
	}
};

class LevelInstance
{
public:
	Level* instanceOf;
	b2World* physicsWorld = nullptr;
	LevelInstance(Level* levelToInstance)
	{
		this->instanceOf = levelToInstance;
		physicsWorld = new b2World(Physics::Gravity);
	}
};

class S2DRuntime
{
public:
	int release_mode = S2D_RELEASE;
	sf::RenderWindow* GAME_WINDOW = nullptr;
	
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
	std::vector<Level*>LoadedLevels = std::vector<Level*>();
	
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

Level* LevelManager::DefaultLevel = new Level(std::string("Default Level"), World("World", sf::Color::Black));
Level* LevelManager::ActiveLevel = LevelManager::DefaultLevel;

Vector2 Physics::Gravity = Vector2(0, 9.81f);
//sf::Vector2f Physics::Gravity = sf::Vector2f(0, 9.81f);

S2DRuntime* S2DRuntime::Instance = nullptr;

bool doClear = true;

bool isKeyPressedTap(sf::Keyboard::Key query)
{
	static bool res = false;
	if (sf::Keyboard::isKeyPressed(query))
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
	static sf::Clock global_clock;
	static sf::Time _time;
	static sf::Int64 last, current;

public:
	static float delta, deltaUnscaled, physicsDelta;
	static float Scale;

	static void init()
	{
		global_clock = sf::Clock();
	}

	static void update()
	{
		clamp(Scale, 0, 1);

		_time = global_clock.getElapsedTime();
		current = _time.asMilliseconds();
		delta = current - last;
		deltaUnscaled = delta;

		delta /= 1000;
		deltaUnscaled /= 1000;

		delta *= Scale;
		last = current;
	}
};

float			time::Scale						= 1;
float			time::delta						= 0,
				time::physicsDelta				= 0.02f,
				time::deltaUnscaled		= 0;
sf::Int64	time::current			= 0,
				time::last					= 0;
sf::Time	time::_time				= sf::Time();
sf::Clock	time::global_clock	= sf::Clock();

//Created so that when a GameObject needs to be destroyed, we can also clean up the Sprite/Texture it also created.
struct S2DTextureSpritePair
{
public:
	int id;
	sf::Texture* tex;
	sf::Sprite* sprite;

	S2DTextureSpritePair(int n, sf::Texture* t, sf::Sprite* s)
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
	sf::Sprite s;

	GameObjectSprite()
	{
		tsp_id = -1;
		s = sf::Sprite();
	}

	GameObjectSprite(int tsp_id, sf::Sprite s)
	{
		this->tsp_id = tsp_id;
		this->s = s;
	}
};

class TextureManager
{
public:
	static std::vector<S2DTextureSpritePair> LoadedTextures;

	static S2DTextureSpritePair CreateTexturePair(sf::Texture* tex, sf::Sprite* spr)
	{
		S2DTextureSpritePair tsp = S2DTextureSpritePair(LoadedTextures.size(), tex, spr);
		LoadedTextures.push_back(tsp);
		return tsp;
	}

	static void RegenerateLoadedTextureList()
	{
		int null_id = -1;
		std::vector<S2DTextureSpritePair> new_list = std::vector<S2DTextureSpritePair>();
		for (int i = 0; i < LoadedTextures.size(); i++)
		{
			if (&LoadedTextures[i] == nullptr) continue;
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

	static GameObjectSprite CreateSprite(std::string texturepath)
	{
		sf::Texture* texture = new sf::Texture();
		sf::Sprite* ret;
		if (!texture->loadFromFile(texturepath)) return GameObjectSprite(-1, sf::Sprite());
		ret = new sf::Sprite(*texture);
		S2DTextureSpritePair s = CreateTexturePair(texture, ret);
		ret->setOrigin(0.25f, 0.25f);
		return GameObjectSprite(s.id, *ret);
	}
};

//std::vector<S2DTextureSpritePair> TextureManager::LoadedTextures = std::vector<S2DTextureSpritePair>();

MStaticDefinition(std::vector<S2DTextureSpritePair>, TextureManager, LoadedTextures);

class GameObject : public Updatable
{
public:
	Vector2 position, scale;
	Level* parent_level;
	GameObjectSprite sprite;
	std::string name;
	
	float mass = 1;
	float drag = 0;
	float gravityInfluence = 1;

	bool active;
	bool isStatic = false;
	bool hasPhysics = false;
	bool respectsTime = true;
	bool awaitingDestroy = false;

	DrawMode drawMode = DrawMode::DrawWhenLevelActive;
	Physics::collisionShape CollisionShape;
	sf::Vector2f velocity;
	
	float rotation;
	static std::vector<GameObject*> ActiveObjects;

	struct DestroyRequest
	{
	public:
		GameObject* des;
		bool destroyed;

		DestroyRequest(GameObject* g)
		{
			this->des = g;
		}
	};

	static std::vector<DestroyRequest> DestroyRequests;

	static void RebuildDestroyRequestList()
	{
		std::vector<DestroyRequest> old = std::vector< DestroyRequest>(DestroyRequests);
		std::vector<DestroyRequest> _new = std::vector< DestroyRequest>();
		for (size_t i = 0; i < old.size(); i++)
		{
			if (!old[i].destroyed)
			{
				_new.push_back(old[i]);
			}
		}

		DestroyRequests = _new;
	}

	static void MakeDestroyRequest(GameObject* g)
	{
		DestroyRequests.push_back(DestroyRequest(g));
	}

	static void ManageDestroyRequests()
	{
		for (size_t i = 0; i < DestroyRequests.size(); i++)
		{
			if (DestroyRequests[i].des != nullptr)
			{
				DestroyRequests[i].des->DestroyImmediate();
				DestroyRequests[i].destroyed = true;
			}
		}
		RebuildDestroyRequestList();
	}

	void levelChanged()
	{

	}

	void updatePhysics()
	{
		if (!hasPhysics) return;
		if (respectsTime)
		{
			velocity += (sf::Vector2f)Physics::Gravity * gravityInfluence * time::physicsDelta * time::Scale;
			position += velocity * time::physicsDelta * time::Scale;
		}
		else
		{
			velocity -= (sf::Vector2f)Physics::Gravity * gravityInfluence * time::physicsDelta;
			position += velocity * time::physicsDelta;
		}
	}

	/*
		GameObjects that want to be destroyed must a request to be destroyed, which is then handled at the very start of 
		the game loop. 
		This cannot simply be handled within an Update loop as code that runs on a GameObject that's meant
		to have been destroyed will likely cause an access violation.
		This also could not have been done within Post Update as sending the OnDestroy event led to another access violation.

		Then, the Class Updater will flush destroyed/null GameObjects from the list of active GameObjects to further prevent this
		from happening.
	*/

	void RequestDestroy()
	{
		MakeDestroyRequest(this);
		awaitingDestroy = true;
		destroyed();
	}

	void DestroyImmediate()
	{
		active = false;
		u_active = false;
		
		TextureManager::CleanUpTexturePair(sprite.tsp_id);
		delete this;
	}

	void checkSceneValid()
	{
		if (parent_level == nullptr)
		{
			//printf((std::string("\nGameObject \"").append(name).append("\" has no parent Scene!")).c_str());
			__debugbreak();
			return;
		}
	}

	void draw()
	{
		if (drawMode == DrawMode::DontDraw) return;
		sprite.s.setPosition(position);
		sprite.s.setRotation(rotation);
		sprite.s.setScale(scale);
		S2DRuntime::get()->GAME_WINDOW->draw(sprite.s);
	}

	void forceDraw()
	{
		sprite.s.setPosition(position);
		sprite.s.setRotation(rotation);
		sprite.s.setScale(scale);
		S2DRuntime::get()->GAME_WINDOW->draw(sprite.s);
	}

	void tick()
	{
		if (!active) return;
		
		switch (this->flags)
		{
		case SimulateAlways:
				checkSceneValid();
				updatePhysics();
				update();
				
			break;

		case SimulateOnlyWhenLevelActive:
			if (parent_level->name == LevelManager::ActiveLevel->name)
			{
				checkSceneValid();
				updatePhysics();
				update();
			}
			break;
		}

		switch (drawMode)
		{
		case DrawMode::DrawAlways:
			if (&sprite.s != nullptr)
			{
				draw();
			}
			break;

		case DrawMode::DrawWhenLevelActive:
			if (parent_level->name == LevelManager::ActiveLevel->name)
			{
				if (&sprite.s != nullptr)
				{
					draw();
				}
			}
			break;
		}
	}

	void after_tick()
	{
		if (this == nullptr) return;
		
		post_update();
	}

	GameObject(bool setActive = true)
	{
		active = setActive;
		parent_level = LevelManager::ActiveLevel;
		rotation = 0;
		position = sf::Vector2f(0, 0);
		name = "new WorldObject";
	}




	void MakeStandalone()
	{
		init_behavior;
	}
};

MStaticDefinition(std::vector<GameObject::DestroyRequest>, GameObject, DestroyRequests);

class Camera : public GameObject
{
public:
	bool isMain;
	float zoom = 1;
	sf::View view;

	void buildView()
	{
		if (isMain)
		{
			sf::Vector2u rect = S2DRuntime::get()->GAME_WINDOW->getSize();
			view = sf::View(position, (sf::Vector2f)rect);
			view.setRotation(rotation);
			view.zoom(zoom);
			S2DRuntime::get()->GAME_WINDOW->setView(view);
		}
	}


	Camera() : GameObject(true)
	{
		init_behavior;
		drawMode = DrawMode::DontDraw;

		name = "new Camera";
		buildView();
	}
	

	void update()
	{
		using namespace sf;
		buildView();
	}
};

class Particle : public GameObject
{
	float p;
public:
	float lifetime;

	Particle(float l) : GameObject(true)
	{
		init_behavior;
		l = lifetime;
	}

	void update()
	{
		//std::cout << "fuck" << std::endl;
		p += time::delta;
		if (p >= lifetime)
		{
			p = 0;
			//RequestDestroy();
		}
	}
};

class ParticleSystem : public GameObject
{
private:
	float d;
public:
	bool emitting;
	int maxParticles;
	float duration;
	float speed = 2;
	float delay = 0.2f;
	float lifetime = 5;
	GameObjectSprite sprite;
	std::vector<Particle*> particles = std::vector<Particle*>();

	ParticleSystem() : GameObject(true)
	{
		init_behavior;
		sprite = TextureManager::CreateSprite("sprites\\square.png");
		maxParticles = 34;
	}

	void emit(int amt = 1)
	{
		if (amt == 1)
		{
			Particle* particle = new Particle(lifetime);
			particle->position = position;

			particle->velocity += sf::Vector2f(random(-speed, speed),
				random(-speed, speed));
			particle->active = true;
			particle->hasPhysics = true;
			particle->sprite = sprite;
			particle->scale = sf::Vector2f(0.02f, 0.02f);
			particle->drawMode = DrawWhenLevelActive;
			particles.push_back(particle);
		}
		else if (amt > 1)
		{
			for (size_t i = 0; i < amt; i++)
			{
				Particle* particle = new Particle(lifetime);
				particle->position = position;

				particle->velocity += sf::Vector2f(random(-speed, speed),
					random(-speed, speed));
				particle->active = true;
				particle->hasPhysics = true;
				particle->sprite = sprite;
				particle->scale = sf::Vector2f(0.02f, 0.02f);
				particle->drawMode = DrawWhenLevelActive;
				particles.push_back(particle);
			}
		}
	}

	void update()
	{
		if (emitting)
		{
			d += time::delta;
			if (d >= delay)
			{
				emit();
				d = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			emit(20);
		}
	}
};

std::vector<GameObject*> GameObject::ActiveObjects = std::vector<GameObject*>();
std::vector<Updatable*> Updatable::UpdatableObjects = std::vector<Updatable*>();

class ClassUpdater
{
public:

	static void UpdateUpdatables()
	{
		for (size_t i = 0; i < Updatable::UpdatableObjects.size(); i++)
		{
			if (Updatable::UpdatableObjects[i] == nullptr)
			{
				continue;
			}
			Updatable::UpdatableObjects[i]->u_tick();
		}
	}

	static void PostUpdateUpdatables()
	{
		for (size_t i = 0; i < Updatable::UpdatableObjects.size(); i++)
		{
			if (Updatable::UpdatableObjects[i] == nullptr)
			{
				continue;
			}
			Updatable::UpdatableObjects[i]->u_post_update();
		}
	}

	static void RebuildGameObjectList()
	{
		std::vector<GameObject*> old = GameObject::ActiveObjects;
		std::vector<GameObject*> _new = std::vector<GameObject*>();
		for (size_t i = 0; i < old.size(); i++)
		{
			if (old[i] == nullptr) continue;

			if (!old[i]->awaitingDestroy)
			{
				_new.push_back(old[i]);
			}
		}

		GameObject::ActiveObjects = _new;
	}
	
	static void UpdateGameObjects()
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

	static void PostUpdateGameObjects()
	{
		for (size_t i = 0; i < GameObject::ActiveObjects.size(); i++)
		{
			if (GameObject::ActiveObjects[i] == nullptr)
			{
				continue;
			}
			GameObject::ActiveObjects[i]->after_tick();
		}
	}
};

class UpdatableTest : public Updatable
{
public:
	UpdatableTest()
	{
		init_updatable;
	}

	void update()
	{
		
	}

	void post_update()
	{
		//std::cout << "\nfuck";
	}
};

class PhysicsTestObject : public GameObject
{
public:
	PhysicsTestObject() : GameObject(true)
	{
		init_behavior;
		hasPhysics = true;
		position = sf::Vector2f(1, 4);
		scale = sf::Vector2f(0.03, 0.03);
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

		scale = sf::Vector2f(0.03, 0.03);
		sprite = TextureManager::CreateSprite("sprites\\square.png");
	}

	void onDestroyed()
	{
		printf("\nNOOOOOOOOOOOOoooooooo");
	}

	void post_update()
	{
		using namespace sf;
		RectangleShape bb = RectangleShape(scale);
		bb.setFillColor(Color(0, 255, 0, 200));
		bb.setPosition(position);
		S2DRuntime::get()->GAME_WINDOW->draw(bb);
	}

	void update()
	{
		using namespace sf;
		
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
			RequestDestroy();
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
			
		}
	}
};

#endif