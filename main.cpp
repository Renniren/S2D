#include "S2D.h"

int main()
{
  
    RenderWindow window(VideoMode(800, 600), "window");
    GAME_WINDOW = &window;
    
 
    
    player* test = new player();
    test->parent_level = current_level;

    while(GAME_WINDOW->isOpen())
    {
    #ifdef S2D_DEBUG
            GAME_WINDOW->setTitle(game_debug_name + current_world.name);
    #endif
    #ifndef S2D_DEBUG
            GAME_WINDOW->setTitle(game_name);
    #endif

            float currentFrame = static_cast<float>(sf);
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
        
        if(doClear) GAME_WINDOW->clear(current_world.clear_color);
        
        while (GAME_WINDOW->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) GAME_WINDOW->close();
        }

        update_active_objects();
        
        GAME_WINDOW->display();
    }


  return 0;
}
