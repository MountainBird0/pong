#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"
#include "Brick.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1902, 1080), "Pong!", Style::Fullscreen);

    Bat bat(1920.f * 0.5, 1080.f - 20);
    Ball ball(1920.f * 0.5, 0.f);

    vector<Brick> bricks;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bricks.push_back(Brick(i * 150, j * 150));
        }
    }

    bool prevColSide = false;
    bool prevColTop = false;
    bool prevColBat = false;

    bool prevColBri = false;

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

        for (Brick &brick : bricks) // 튕기기
        {
            bool colBri = ballBound.intersects(brick.GetGlobalBounds());
            if (!prevColBri && colBri)
            {
                ball.reboundBatOrTop();
                for (Brick &brick : bricks) // 지우기
                {
                    brick.CrashCheck(ball);

                }
                bricks.erase(remove_if(begin(bricks), end(bricks), [](Brick &b)
                    {
                        return b.crash;
                    }), end(bricks));
                break;
            }
                prevColBri = colBri;
        }

        
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
        if (ballBound.top + ballBound.height > windowSize.y)
        {
            ball.reboundBottom();
        }

        prevColSide = colSide;
        prevColTop = colTop;
        prevColBat = colBat;
        
        // update
        bat.Update(deltaTime);
        ball.Update(deltaTime);
        

        // draw
        window.clear();

        window.draw(bat.GetShape());
        window.draw(ball.GetShape());
        for (Brick &brick : bricks)
        {
            window.draw(brick.GetShape());
        }

        window.display();
    }

    return 0;
}