#include "S2D.h"

int main()
{
  
    RenderWindow window(VideoMode(800, 600), "window");
    GAME_WINDOW = &window;
    
    time::init();
    
    TestPlayer* test = new TestPlayer();
    test->parent_level = ActiveLevel;
    while(GAME_WINDOW->isOpen())
    {
    #ifdef S2D_DEBUG
            GAME_WINDOW->setTitle(game_debug_name + ActiveWorld.name);
    #endif
    #ifndef S2D_DEBUG
            GAME_WINDOW->setTitle(game_name);
    #endif
        if(doClear) GAME_WINDOW->clear(ActiveWorld.clear_color);
        

        while (GAME_WINDOW->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) GAME_WINDOW->close();
        }

        time::update();
        UpdateGameObjects();
        
        GAME_WINDOW->display();
    }


  return 0;
}
