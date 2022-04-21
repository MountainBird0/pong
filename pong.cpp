#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"
#include "Brick.h"

using namespace sf;
using namespace std;

#include <random>
#include <sstream>
#include <SFML/Audio.hpp>


int main()
{
    Font fontDIGI; // 폰트 파일 불러옴
    fontDIGI.loadFromFile("fonts/DS-DIGI.TTF");

    Text textMessage;
    textMessage.setFont(fontDIGI);
    Text textScore;
    textScore.setFont(fontDIGI);
    Text textLife;
    textLife.setFont(fontDIGI);

    textMessage.setString("press enter to start");
    textScore.setString("score = 0");
    textLife.setString("Life = 3");

    textMessage.setCharacterSize(75);
    textScore.setCharacterSize(50);
    textLife.setCharacterSize(50);

    textMessage.setFillColor(Color::White);
    textScore.setFillColor(Color::White);
    textLife.setFillColor(Color::White);

    textScore.setPosition(20, 20);
    textLife.setPosition(20, 80);

    RenderWindow window(VideoMode(1902, 1080), "Pong!", Style::Fullscreen);

    Bat bat(1920.f * 0.5, 1080.f - 20);
    //Ball ball(1920.f * 0.5, 1080.f - 100);
    Ball ball(1920.f * 0.5, 0.f);

    // 동적배열
    Brick *brickarr = new Brick[5];
    for (int i = 0; i < 5; i++)
    {
        brickarr[i] = {i * 150.f, 580.f};
    }

    vector<Brick> bricks;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bricks.push_back(Brick(i * 150, j * 100));
        }
    }

    bool prevColSide = false;
    bool prevColTop = false;
    bool prevColBat = false;

    bool prevColBri = false;

    Clock clock;

    int score = 0;
    int life = 3;

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


        for (int i = 0; i < 5; i++)
        {
            bool colBri = ballBound.intersects(brickarr[i].GetGlobalBounds());

            if (!prevColBri && colBri)
            {
                ball.reboundBatOrTop();               
                score++;

                for (Brick &brick : bricks) // 지우기
                {
                    brick.CrashCheck(ball);
                    brickarr[i] = {3000, 3000};
                    //brickarr = NULL;
                }
                //break;
            }
            prevColBri = colBri;
        }


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
                score++;
                //break;
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
            life--;
        }

        prevColSide = colSide;
        prevColTop = colTop;
        prevColBat = colBat;
        

        if (life == 0)
        {
            window.close();
        }

        // 동적배열




        // update
        bat.Update(deltaTime);
        ball.Update(deltaTime);

        stringstream ss;
        ss << "Score = " << score;
        textScore.setString(ss.str());

        stringstream ls;
        ls << "Life = " << life;
        textLife.setString(ls.str());
        

        // draw
        window.clear();

        window.draw(bat.GetShape());
        window.draw(ball.GetShape());
        for (Brick &brick : bricks)
        {
            window.draw(brick.GetShape());
        }
        window.draw(textScore);
        window.draw(textLife);

        for (int i = 0; i < 5; i++)
        {
            window.draw(brickarr[i].GetShape());
        }

        window.display();
    }

    delete[]brickarr;
    bricks.clear();
    return 0;
}