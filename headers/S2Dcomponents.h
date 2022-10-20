#pragma once
#ifndef S2D_INTENRAL_COMPONENTS
#define S2D_INTENRAL_COMPONENTS
#include<S2Dinternal.h>

//Test Classes -----------

class BehaviorTest : public Behavior
{
public:

	int c;
	void PreUpdate()
	{
		std::cout << "pre update works" << std::endl;
	}

	void Update()
	{
		std::cout << "update works" << std::endl;
		if (c >= 100)
		{
			RequestDestroy();
		}
	}

	void GetComponentWorksCheck()
	{
		std::cout << "get component works" << std::endl;
	}

	void LateUpdate()
	{
		c++;
		std::cout << "late update works" << std::endl;
	}
};

class BehaviorInheritanceTest : public BehaviorTest
{
public:


	void PreUpdate()
	{
		std::cout << "inheritance pre update works" << std::endl;
	}

	void Update()
	{
		std::cout << "inheritance update works" << std::endl;
		if (c >= 100)
		{
			RequestDestroy();
		}
	}

	void GetComponentWorksCheck()
	{
		std::cout << "inheritance get component works" << std::endl;
	}

	void LateUpdate()
	{
		c++;
		std::cout << "inheritance late update works" << std::endl;
	}
};

class PhysicsTestObject : public GameObject
{
public:
	PhysicsTestObject() : GameObject(true)
	{
		init_gameobject;
		hasPhysics = true;
		position = sf::Vector2f(1, 4);
		scale = sf::Vector2f(0.03, 0.03);
		sprite = TextureManager::CreateSprite("sprites\\circle.png");
	}

	void update()
	{
		using namespace std;
		//cout << position.y << endl;
		if (position.y > 600)
		{
			position.y = -600;
			velocity.Zero();
		}
	}
};

class Particle : public GameObject
{
	float p;
public:
	float lifetime;

	Particle(float l) : GameObject(true)
	{
		init_gameobject;
		name = "Particle";
		lifetime = l;
		p = 0;
	}

	void update()
	{
		//std::cout << "fuck" << std::endl;
		p += time::delta;
		if (p >= lifetime)
		{
			p = 0;
			RequestDestroy();
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
	float lifetime = 3;
	GameObjectSprite sprite;
	std::vector<Particle*> particles = std::vector<Particle*>();

	ParticleSystem() : GameObject(true)
	{
		init_gameobject;
		sprite = TextureManager::CreateSprite("sprites\\square.png");
		maxParticles = 34;
	}

	void emit(int amt = 1)
	{
		for (size_t i = 0; i < amt; i++)
		{
			Particle* particle = new Particle(lifetime);
			particle->position = position;

			particle->velocity += sf::Vector2f(s2random(-speed, speed),
				s2random(-speed, speed));
			particle->angularVelocity += s2random(-10, 10);
			particle->active = true;
			particle->hasPhysics = true;
			particle->sprite = sprite;
			particle->scale = sf::Vector2f(0.02f, 0.02f);
			particle->drawMode = DrawWhenLevelActive;
			particles.push_back(particle);
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


#endif // !S2D_INTENRAL_COMPONENTS
