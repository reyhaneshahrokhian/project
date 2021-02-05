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
    spriteRock.setPosition(320,-250);
    bool rock=false;

    //food
    Texture textureFood;
    textureFood.loadFromFile("project image/food.png");
    Sprite spriteFood;
    spriteFood.setTexture(textureFood);
    spriteFood.setPosition(300,100);
    bool food=false;

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
    spriteGrasmove1.setPosition(100,-200);
      
    Texture textureGrasmove2;
    textureGrasmove2.loadFromFile("project image/grass move.jpg");
    Sprite spriteGrasmove2;
    spriteGrasmove2.setTexture(textureGrasmove2);
    spriteGrasmove2.setPosition(500,-400);

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

    //explosion 
    Texture textureExplosion1;
    textureExplosion1.loadFromFile("project image/step 1.png");
    Sprite spriteExplosion1;
    spriteExplosion1.setTexture(textureExplosion1); 
    spriteExplosion1.setPosition(810,610);

    Texture textureExplosion2;
    textureExplosion2.loadFromFile("project image/step 2.png");
    Sprite spriteExplosion2;
    spriteExplosion2.setTexture(textureExplosion2);
    spriteExplosion2.setPosition(810,610);

    Texture textureExplosion3;
    textureExplosion3.loadFromFile("project image/step 3.png");
    Sprite spriteExplosion3;
    spriteExplosion3.setTexture(textureExplosion3); 
    spriteExplosion3.setPosition(810,610);           

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
    gameover.loadFromFile("project sound/gameover.wav");
    sf::Sound Gameover;
    Gameover.setBuffer(gameover);
    
    //sound eating
    sf::SoundBuffer eating;
    eating.loadFromFile("project sound/food.wav");
    sf::Sound Food;
    Food.setBuffer(eating);

    //sound rock
    sf::SoundBuffer breakingrock;
    breakingrock.loadFromFile("project sound/rock.wav");
    sf::Sound Rock;
    Rock.setBuffer(breakingrock);  

    //sound shooter
    sf::SoundBuffer shooter;
    shooter.loadFromFile("project sound/shooter.wav");
    sf::Sound Shooter;
    Shooter.setBuffer(shooter);    

    bool pause=true;

    float xfood,xgrass1=100,xgrass2=500,xrock=320,xshark=370,xshooter,xexp;
    float yfood,ygrass1=-170,ygrass2=-370,yrock=-250,yshark=400,yshooter,yexp;
    bool touch=false;
    int record;
    int hold=0;
    int highscore;
    bool checkshoot=false;
    int number=1;
    int explosion=0,countexp=0;

    //file for records
    fstream recordfile;
    recordfile.open("record.txt");

    while (window.isOpen()){
        
        
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Return)){
            pause=false;
            number=1;
            rock=false;
            record =0;
            foodRemaining =37.0f;
            foodBarwidth=200;
            foodBar.setSize(Vector2f(200,80));
            foodBar.setFillColor(Color::White);
            foodBar.setPosition(10,10);
            xshark=370;
            yshark=400;
            spriteShark.setPosition(xshark,yshark);  
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

            if(!food){
                //x food
                srand(time(NULL));
                xfood=(rand()%560)+101;
                spriteFood.setPosition(xfood,-40);
                food=true;
            }else{
                //moving food
                yfood=yfood+2;
                spriteFood.setPosition(xfood,yfood);
                if(yfood >610){
                    food=false;
                }
            }

            //moving grasses and rock
            if(number==1){
                ygrass1=ygrass1+2;
                ygrass2=ygrass2+2;
                spriteGrasmove1.setPosition(xgrass1,ygrass1);
                spriteGrasmove2.setPosition(xgrass2,ygrass2);
                if(!rock){
                    yrock=yrock+2;
                    spriteRock.setPosition(xrock,yrock);
                }    
                if(ygrass2>=600){
                    number=2;
                    ygrass1=-170;
                    ygrass2=-170;
                    srand(time(NULL));
                    do{
                       xrock=(rand()%100)+301;
                    }while(xfood==xrock);
                    yrock=-170;  
                    rock=false;              
                }
            }
            if(number==2){
                ygrass1=ygrass1+2;
                ygrass2=ygrass2+2;
                spriteGrasmove1.setPosition(xgrass1,ygrass1);
                spriteGrasmove2.setPosition(xgrass2,ygrass2);
                if(!rock){
                    yrock=yrock+2;
                    spriteRock.setPosition(xrock,yrock);   
                }                
                if(ygrass2>=600){
                    number=3;
                    ygrass1=-370;
                    ygrass2=-170;
                    srand(time(NULL));
                    do{
                       xrock=(rand()%100)+301;
                    }while(xfood==xrock);
                    yrock=-250;   
                    rock=false;                 
                }
            } 
            if(number==3){
                ygrass1=ygrass1+2;
                ygrass2=ygrass2+2;
                spriteGrasmove1.setPosition(xgrass1,ygrass1);
                spriteGrasmove2.setPosition(xgrass2,ygrass2);   
                if(!rock){             
                    yrock=yrock+2;
                    spriteRock.setPosition(xrock,yrock);  
                }              
                if(ygrass1>=600){
                    number=1;
                    ygrass1=-170;
                    ygrass2=-370;
                    srand(time(NULL));
                    do{
                       xrock=(rand()%100)+301;
                    }while(xfood==xrock);
                    yrock=-250;
                    rock=false;                    
                }
            }
            //shooting
            if(Keyboard::isKeyPressed(Keyboard::Z) ||Keyboard::isKeyPressed(Keyboard::X) ||Keyboard::isKeyPressed(Keyboard::C)){
                checkshoot=true;
                xshooter=xshark+50;
                yshooter=yshark;
                Shooter.play();
            }
            if(checkshoot){
                spriteShooter.setPosition(xshooter,yshooter);
                yshooter=yshooter-10;
                if(yshooter<=(yrock+80) && yshooter>=yrock && xshooter>=xrock && xshooter<=(xrock+80)){
                    rock=true;
                    xexp=xrock;
                    yexp=yrock;
                    yrock=-80;
                    spriteRock.setPosition(xrock,yrock);
                    spriteShooter.setPosition(810,610);
                    explosion=1;
                    Rock.play();
                    checkshoot=false;
                }
            }

            //animation
            if(explosion==1){
                spriteExplosion1.setPosition(xexp,yexp);
                countexp++;
                if(countexp==5){ 
                    explosion=2;
                    countexp=0;
                    spriteExplosion1.setPosition(810,610);
                }                  
            }else if(explosion==2){
                spriteExplosion2.setPosition(xexp,yexp);
                countexp++;
                if(countexp==5){ 
                    explosion=3;
                    countexp=0;
                    spriteExplosion2.setPosition(810,610);
                }
                             
            }else if(explosion==3){
                spriteExplosion3.setPosition(xexp,yexp);
                countexp++;
                if(countexp==5){ 
                    explosion=0;
                    countexp=0;
                    spriteExplosion3.setPosition(810,610);
                }                
            }         
 

            //eating food
            if((xshark+100)>=xfood && xshark<=(xfood+30) && yshark>=yfood && yshark<=(yfood+40)){
                foodRemaining =37.0f;
                foodBarwidth=200;
                foodBar.setSize(Vector2f(200,80));  
                yfood=1000;
                spriteFood.setPosition(xfood,yfood);
                Food.play();          
            }else if(xshark<=(xfood+30) && (xshark+100)>=xfood && (yshark+200)>=yfood && (yshark+200)<=(yfood+40)){
                foodRemaining =37.0f;
                foodBarwidth=200;
                foodBar.setSize(Vector2f(200,80)); 
                yfood=1000; 
                spriteFood.setPosition(xfood,yfood);
                Food.play();          
            }        

            //be sensitive to grass
            if(xshark<=300 && yshark<=(ygrass1+200) && yshark>=ygrass1){
                touch=true;  
            }else if(xshark<=300 && (yshark+200)<=(ygrass1+200) && (yshark+200)>=ygrass1){
                touch=true;
            }else if((xshark+70)>=500 && (yshark+200)>=ygrass2 && (yshark+200)<=(ygrass2+200)){
                touch=true; 
            }else if((xshark+70)>=500 && yshark>=ygrass2 && yshark<=(ygrass2+200)){
                touch=true;
            }else if(xshark<=100 || (xshark+70)>=700){
                touch=true;
            }

            //be sesitive to rock
            if((xshark+100)>=xrock && xshark<=(xrock+100)  && yshark>=yrock && yshark<=(yrock+100)){
                touch=true;
                yrock=1000;
                spriteRock.setPosition(xrock,yrock);
            }else if(xshark<=(xrock+100) && (xshark+100)>=xrock && (yshark+200)>=yrock && (yshark+200)<=(yrock+100)){
                touch=true;
                yrock=1000;
                spriteRock.setPosition(xrock,yrock);
            }

            if(touch==true){
                pause=true;
                massageText.setString("Game over!!");
                massageText.setPosition(160,250);  
                Gameover.play();  
                yrock=1000;
                spriteRock.setPosition(xrock,yrock);                     
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
        window.draw(spriteExplosion1);
        window.draw(spriteExplosion2);
        window.draw(spriteExplosion3);

        if(pause==true){
            window.draw(massageText);   
            touch=false;     
        }

        window.display();
    }
    return 0;
}