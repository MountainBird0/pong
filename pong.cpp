#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1902, 1080), "Pong!", Style::Fullscreen);

    Bat bat(1920.f * 0.5, 1080.f - 20);
    Ball ball(1920.f * 0.5, 0.f);

    bool prevColSide = false;
    bool prevColTop = false;
    bool prevColBat = false;

    Clock clock;

    while (window.isOpen())
    {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    
        Sides dir = Sides::NONE;

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            dir = Sides::LEFT;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            dir = Sides::RIGHT;
        }
        bat.SetMoveDir(dir);
           
        // 테스트
        FloatRect ballBound = ball.GetGlobalBounds();
        Vector2u windowSize = window.getSize(); // 윈도우에 할당된 사이즈 받음
        
        bool colSide = ballBound.left < 0.f ||
            ballBound.left + ballBound.width > windowSize.x;
        bool colTop = ballBound.top < 0.f;
        bool colBat = ballBound.intersects(bat.GetGlobalBounds());

        if (!prevColSide && colSide)
        {
            ball.reboundSides();
        }
        if (!prevColTop && colTop)
        {
            ball.reboundBatOrTop();
        }
        if (!prevColBat && colBat)
        {
            ball.reboundBatOrTop();
        }
        else if (ballBound.top + ballBound.height > windowSize.y)
        {
            ball.reboundBottom();
        }

        prevColSide = colSide;
        prevColTop = colTop;
        prevColBat = colBat;



        // update
        bat.Update(deltaTime); // 업데이트
        ball.Update(deltaTime);



        // draw
        window.clear();

        window.draw(bat.GetShape());
        window.draw(ball.GetShape());

        window.display();
    }

    return 0;
}