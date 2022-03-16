#include <S2D.h>

int main()
{
  
  RenderWindow window(VideoMode(800, 600), "window");
  GAME_WINDOW = &window;
  printf("Hello world!");
  
    sf::Event event;
    while(GAME_WINDOW->isOpen())
    {
        while (GAME_WINDOW->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GAME_WINDOW->close();
        }
        GAME_WINDOW->setTitle(game_name + current_world.name);
        if(doClear) GAME_WINDOW->clear(current_world.clear_color);
        GAME_WINDOW->display();
    }


  return 0;
}
