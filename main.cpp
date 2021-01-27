#include "stdfix.h"
#include <SFML/Graphics.hpp>
#include <sstream>

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

    //rock
    Texture textureRock;
    textureRock.loadFromFile("project image/rock.png");
    Sprite spriteRock;
    spriteRock.setTexture(textureRock);
    spriteRock.setPosition(400,100);   
    bool rock=false;
    float rockSpeed=70.0f;

    //food
    Texture textureFood;
    textureFood.loadFromFile("project image/food.png");
    Sprite spriteFood;
    spriteFood.setTexture(textureFood);
    spriteFood.setPosition(300,100);
    bool food=false;
    float foodSpeed=70.0f;

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
    bool grass1=false;
    float grass1Speed=0.0f;
      
    Texture textureGrasmove2;
    textureGrasmove2.loadFromFile("project image/grass move.jpg");
    Sprite spriteGrasmove2;
    spriteGrasmove2.setTexture(textureGrasmove2);
    spriteGrasmove2.setPosition(510,0);
    bool grass2=false;
    float grass2Speed=0.0f;

    //shark
    Texture textureShark;
    textureShark.loadFromFile("project image/shark.png");
    Sprite spriteShark;
    spriteShark.setTexture(textureShark);
    spriteShark.setPosition(370,400);    

    //shooter
    Texture textureShooter;
    textureShooter.loadFromFile("project image/shooter.png");
    Sprite spriteShooter;
    spriteShooter.setTexture(textureShooter);
    spriteShooter.setPosition(400,350);    

    Clock clock; 

    //foodBar
    Texture textureFoodBar;
    textureFoodBar.loadFromFile("project image/frame.png");
    Sprite spriteFoodBar;
    spriteFoodBar.setTexture(textureFoodBar);
    spriteFoodBar.setPosition(10,10);   

    RectangleShape foodBar;
    float foodBarwidth =200;
    float foodBarheight =80;
    foodBar.setSize(Vector2f(foodBarwidth,foodBarheight));
    foodBar.setFillColor(Color::White);
    foodBar.setPosition(10,10);

    Time gamefoodTotal;
    float foodRemaining =37.0f;
    float foodBarwidthperSecond = foodBarwidth / foodRemaining;
   
    //texts
    Text massageText;
    Text foodText;
    Text RecordText;

    Font font;
    font.loadFromFile("font.ttf");

    massageText.setFont(font);
    massageText.setString("Press Enter to start!");
    massageText.setCharacterSize(75);
    massageText.setFillColor(Color::Black);
    massageText.setPosition(40,250);

    foodText.setFont(font); 
    foodText.setString("food");
    foodText.setCharacterSize(80);
    foodText.setFillColor(Color::Black);
    foodText.setPosition(10,0);

    RecordText.setFont(font);
    RecordText.setString("Record = 0");
    RecordText.setCharacterSize(30);
    RecordText.setFillColor(Color::Black);
    RecordText.setPosition(350,0);

    bool pause=true;

    float a;
    int record;
    int hold=0;

    while (window.isOpen()){
        
        
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Return)){
            pause=false;
            record =0;
            float foodRemaining =37.0f;
            foodBarwidth=200;
            foodBar.setSize(Vector2f(200,80));
        }
        if(pause==false){

            //changing foodBar Size
            Time dt=clock.restart();            
            foodRemaining -=dt.asSeconds();
            foodBar.setSize(Vector2f(foodBarwidthperSecond*foodRemaining,foodBarheight));
            if(foodRemaining<= 0.0f){
                pause=true;
                massageText.setString("Out of food!!");
                massageText.setPosition(160,250);
            }
        //record
        hold ++; 
        record +=hold/20;
        if(hold==20)
            hold=0;
        std::stringstream ss;
        ss << "Record = " << record;
        RecordText.setString(ss.str());    

        if(!grass1){
            //grass1 speed
            srand(time(NULL)*2);
            grass1Speed = (rand()%50+50);
            spriteGrasmove1.setPosition(100,-200);
            grass1=true;
        }else{
            //moving grass1
            spriteGrasmove1.setPosition(
            100,spriteGrasmove1.getPosition().y+(grass1Speed*dt.asSeconds()));
            
            if(spriteGrasmove1.getPosition().y >810){
                grass1=false;
            }
        }

        if(!grass2){
            //grass2 speed
            srand(time(NULL)*6);
            grass2Speed = (rand()%50+50);
            spriteGrasmove2.setPosition(510,-200);
            grass2=true;
        }else{
            //moving grass2
            spriteGrasmove2.setPosition(
                510,spriteGrasmove2.getPosition().y+(grass2Speed * dt.asSeconds()));
        
            if(spriteGrasmove2.getPosition().y >810){
                grass2=false;
            }
        }

        if(!food){
            //x food
            srand(time(NULL)*3);
            float x=(rand()%560)+101;
            spriteFood.setPosition(x,-40);
            food=true;
        }else{
            //moving food
            spriteFood.setPosition(
            spriteFood.getPosition().x,    
            spriteFood.getPosition().y+(foodSpeed * dt.asSeconds()));
            float a= spriteFood.getPosition().x;
            if(spriteFood.getPosition().y >810){
                food=false;
            }
        }

        if(!rock){
            //x rock
            srand(time(NULL)*3);
            float x=(rand()%540)+101;
            do{
            float x=(rand()%540)+101;
            }while(a==x);
            spriteRock.setPosition(x,-60);
            rock=true;
        }else{
            //moving rock
            spriteRock.setPosition(
            spriteRock.getPosition().x,    
            spriteRock.getPosition().y+(rockSpeed * dt.asSeconds()));
        
            if(spriteRock.getPosition().y >810){
                rock=false;
            }
        }
        }

        window.clear();
        
        window.draw(spriteBackground);
        window.draw(spriteFood);
        window.draw(spriteRock);
        window.draw(spriteShark);
        window.draw(spriteGrasside1);
        window.draw(spriteGrasside2);
        window.draw(spriteGrasmove1);
        window.draw(spriteGrasmove2);
        window.draw(spriteShooter);
        window.draw(foodBar);
        window.draw(spriteFoodBar);
        window.draw(foodText);
        window.draw(RecordText);

        if(pause==true){
            window.draw(massageText);
        }

        window.display();
    }

    return 0;
}