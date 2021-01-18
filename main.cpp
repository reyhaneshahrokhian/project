#include "stdfix.h"
#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
    VideoMode vm(800,600);
    RenderWindow window(vm,"River raid",Style::Fullscreen);

    //beckground
    Texture textureBackground;
    textureBackground.loadFromFile("project image/river.jpg");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
    
    //grass sides
    Texture textureGrasside1;
    textureGrasside1.loadFromFile("project image/grass side.jfif");
    Sprite spriteGrasside1;
    spriteGrasside1.setTexture(textureGrasside1);
    spriteGrasside1.setPosition(0,0);

    Texture textureGrasside2;
    textureGrasside2.loadFromFile("project image/grass side.jfif");
    Sprite spriteGrasside2;
    spriteGrasside2.setTexture(textureGrasside2);
    spriteGrasside2.setPosition(700,0);

    //grass move
    Texture textureGrasmove1;
    textureGrasmove1.loadFromFile("project image/grass move.jpg");
    Sprite spriteGrasmove1;
    spriteGrasmove1.setTexture(textureGrasmove1);
    spriteGrasmove1.setPosition(100,0);
      
    Texture textureGrasmove2;
    textureGrasmove2.loadFromFile("project image/grass move.jpg");
    Sprite spriteGrasmove2;
    spriteGrasmove2.setTexture(textureGrasmove2);
    spriteGrasmove2.setPosition(510,0);

    //shark
    Texture textureShark;
    textureShark.loadFromFile("project image/shark.png");
    Sprite spriteShark;
    spriteShark.setTexture(textureShark);
    spriteShark.setPosition(370,400);    

    //food
    Texture textureFood;
    textureFood.loadFromFile("project image/food.png");
    Sprite spriteFood;
    spriteFood.setTexture(textureFood);
    spriteFood.setPosition(300,100);

    //shooter
    Texture textureShooter;
    textureShooter.loadFromFile("project image/shooter.png");
    Sprite spriteShooter;
    spriteShooter.setTexture(textureShooter);
    spriteShooter.setPosition(400,350);    

    //rock
    Texture textureRock;
    textureRock.loadFromFile("project image/rock.png");
    Sprite spriteRock;
    spriteRock.setTexture(textureRock);
    spriteRock.setPosition(400,100);    

    while (window.isOpen()){
        
        
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

        window.clear();
        
        window.draw(spriteBackground);
        window.draw(spriteFood);
        window.draw(spriteShark);
        window.draw(spriteGrasside1);
        window.draw(spriteGrasside2);
        window.draw(spriteGrasmove1);
        window.draw(spriteGrasmove2);
        window.draw(spriteShooter);
        window.draw(spriteRock);

        window.display();
    }

    return 0;
}