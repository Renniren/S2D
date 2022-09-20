#include "S2D.h"

int main()
{

    S2DGameRuntime::init();
    TestPlayer* test = new TestPlayer();
    PhysicsTestObject* test2 = new PhysicsTestObject();
    test->parent_level = ActiveLevel;
    test2->parent_level = ActiveLevel;
    while(S2DGameRuntime::get()->Window->isOpen())
    {
        if (IS_DEBUG)
        {
            S2DGameRuntime::get()->Window->setTitle(game_debug_name + ActiveWorld.name);
        }
        else
        {
            S2DGameRuntime::get()->Window->setTitle(game_name);
        }

        if(doClear) S2DGameRuntime::get()->Window->clear(ActiveWorld.clear_color);

        while (S2DGameRuntime::get()->Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) S2DGameRuntime::get()->Window->close();
        }

        time::update();
        UpdateGameObjects();
        
        S2DGameRuntime::get()->Window->display();
    }


  return 0;
}
