#include "S2D.h"

int main()
{
  
    RenderWindow window(VideoMode(800, 600), "window");
    GAME_WINDOW = &window;
    
    evh = new S2D_event_handler();
    
    printf("Hello world!");
  
    sf::Event event;
    player* test = new player();
    test->parent_level = current_level;
    printf(test->parent_level->name.c_str());

    test->scale = Vector2f(0.03, 0.03);
    test->sprite = *create_sprite("sprites\\circle.png");

    while(GAME_WINDOW->isOpen())
    {
        GAME_WINDOW->setTitle(game_name + current_world.name);
        if(doClear) GAME_WINDOW->clear(current_world.clear_color);
        while (GAME_WINDOW->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GAME_WINDOW->close();
        }

        for (size_t i = 0; i < world_object::active_objects.size(); i++)
        {
            world_object::active_objects[i]->tick();
        }

        GAME_WINDOW->display();
    }


  return 0;
}
