#include "stdfix.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
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
    spriteGrasmove2.setPosition(500,0);
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
    Text HighscoreText;

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
    RecordText.setString("Score = 0");
    RecordText.setCharacterSize(30);
    RecordText.setFillColor(Color::Black);
    RecordText.setPosition(350,30);

    HighscoreText.setFont(font);
    HighscoreText.setString("Highscore = ");
    HighscoreText.setCharacterSize(30);
    HighscoreText.setFillColor(Color::Black);
    HighscoreText.setPosition(320,0);

    //sound gameover
    sf::SoundBuffer gameover;
    if(!gameover.loadFromFile("project sound/gameover.wav")){
        cout<<"gfhg";
    }
    sf::Sound Gameover;
    Gameover.setBuffer(gameover);
    
 /*   //sound eating
    sf::SoundBuffer eating;
    if(!eating.loadFromFile("project sound/food.wav")){
        cout<<"jjj";
    }
    sf::Sound Food;
    Food.setBuffer(eating);

    //sound rock
    sf::SoundBuffer breakingrock;
    if(!eating.loadFromFile("project sound/rock.wav")){
        cout<<"hhhh";
    }
    sf::Sound Rock;
    Rock.setBuffer(breakingrock);  

    //sound shooter
    sf::SoundBuffer shooter;
    if(!eating.loadFromFile("sproject sound/shooter.wav")){
        cout<<"yyyy";
    }
    sf::Sound Shooter;
    Shooter.setBuffer(shooter); */   

    bool pause=true;

    float xfood,xgrass1,xgrass2,xrock,xshark=370;
    float yfood,ygrass1,ygrass2,yrock,yshark=400;
    bool touch=false;
    int record;
    int hold=0;
    int highscore;

    //file for records
    fstream recordfile;
    recordfile.open("record.txt");

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
            foodBar.setFillColor(Color::White);
            foodBar.setPosition(10,10);
            
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
                Gameover.play();
            }

            //getting positions
            xgrass1= spriteGrasmove1.getPosition().x;
            ygrass1= spriteGrasmove1.getPosition().y; 
            xgrass2= spriteGrasmove2.getPosition().x;
            ygrass2= spriteGrasmove2.getPosition().y;
            xfood= spriteFood.getPosition().x;
            yfood= spriteFood.getPosition().y; 
            xrock= spriteRock.getPosition().x;
            yrock= spriteRock.getPosition().y;            

            //moving shark
            if((Keyboard::isKeyPressed(Keyboard::Right)) || Keyboard::isKeyPressed(Keyboard::D)){
                xshark=xshark+3;
                spriteShark.setPosition(xshark,yshark);
            }
            if((Keyboard::isKeyPressed(Keyboard::Left)) || Keyboard::isKeyPressed(Keyboard::A)){
                xshark=xshark-3;
                spriteShark.setPosition(xshark,yshark);
            }    
            if((Keyboard::isKeyPressed(Keyboard::Up)) || Keyboard::isKeyPressed(Keyboard::W)){
                if((yshark-3)>150){
                    yshark=yshark-3;
                    spriteShark.setPosition(xshark,yshark);
                }
            }                
            if((Keyboard::isKeyPressed(Keyboard::Down)) || Keyboard::isKeyPressed(Keyboard::S)){
                if((yshark+3)<600){
                    yshark=yshark+3;
                    spriteShark.setPosition(xshark,yshark);
                }
            }


        //record
        hold ++; 
        record +=hold/20;
        if(hold==20)
            hold=0;
        std::stringstream ss;
        ss << "Score = " << record;
        RecordText.setString(ss.str());  
        recordfile>>highscore;
        std::stringstream SS;
        SS<<"highscore = "<<highscore;
        HighscoreText.setString(SS.str());      
        if(highscore<record){
            recordfile.open("record.txt",std::ofstream::out|std::ofstream::trunc); 
            recordfile<<record;
            std::stringstream SS;
            SS<<"highscore = "<<record;
            HighscoreText.setString(SS.str());   
            recordfile.close();

        }
        
        if(!grass1){
            //grass1 speed
            srand(time(NULL)*2);
            grass1Speed = (rand()%50+50);
            spriteGrasmove1.setPosition(100,-200);
            grass1=true;
        }else{
            //moving grass1
            spriteGrasmove1.setPosition(100,spriteGrasmove1.getPosition().y+(grass1Speed*dt.asSeconds()));            
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
            spriteGrasmove2.setPosition(510,spriteGrasmove2.getPosition().y+(grass2Speed * dt.asSeconds()));       
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
            if(spriteFood.getPosition().y >810){
                food=false;
            }
        }

        if(!rock){
            //x rock
            srand(time(NULL)*3);
            float x=(rand()%520)+101;
            do{
            float x=(rand()%520)+101;
            }while(xfood==x);
            spriteRock.setPosition(x,-80);
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

        //eating food
        if((xshark+100)>=xfood && xshark<=(xfood+30) && yshark>=yfood && yshark<=(yfood+40)){
            float foodRemaining =37.0f;
            foodBarwidth=200;
            foodBar.setSize(Vector2f(200,80));  
            yfood=1000;
         //   Food.play();          
        }else if(xshark<=(xfood+30) && (xshark+100)>=xfood && (yshark+200)>=yfood && (yshark+200)<=(yfood+40)){
            float foodRemaining =37.0f;
            foodBarwidth=200;
            foodBar.setSize(Vector2f(200,80)); 
            yfood=1000; 
        //    Food.play();          
        }        

        //be sensitive to grass
        if(xshark<=300 && yshark>=ygrass1 && yshark<=(grass1-200)){
            touch=true;  
        }else if(xshark<=300 && (yshark+200)>=ygrass1 && (yshark+200)<=(ygrass1-200)){
            touch=true;
        }else if((xshark+100)>=500 && (yshark+200)>=ygrass2 && (yshark+200<=ygrass2+200)){
            touch=true; 
        }else if((xshark+100)>=500 && yshark>=ygrass2 && yshark<=(ygrass2+200)){
            touch=true;
        }else if(xshark<=100 || (xshark+100)>=700){
            touch=true;
        }

        //be sesitive to rock
        if((xshark+100)>=xrock && xshark<=(xrock+80)  && yshark>=yrock && yshark<=(yrock+80)){
            touch=true;
        }else if(xshark<=(xrock+80) && (xshark+100)>=xrock && (yshark+200)>=yrock && (yshark+200)<=(yrock+80)){
            touch=true;
        }

        if(touch==true){
            pause=true;
            massageText.setString("Game over!!");
            massageText.setPosition(160,250);  
            Gameover.play();         
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
        window.draw(HighscoreText);

        if(pause==true){
            window.draw(massageText);        
        }

        window.display();
    }
    return 0;
}