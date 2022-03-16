#include <S2D.h>

int main()
{
  
    RenderWindow window(VideoMode(800, 600), "window");
    GAME_WINDOW = &window;
    
    evh = new S2D_event_handler();
    
    printf("Hello world!");
  
    sf::Event event;
    player* test = new player();

    while(GAME_WINDOW->isOpen())
    {
        while (GAME_WINDOW->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GAME_WINDOW->close();
        }

        __raise evh->game_tick();

        GAME_WINDOW->setTitle(game_name + current_world.name);
        if(doClear) GAME_WINDOW->clear(current_world.clear_color);
        GAME_WINDOW->display();
    }


  return 0;
}
