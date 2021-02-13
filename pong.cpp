#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

// simple pong paddle game for c++
// created for cs437 game design
// @author Johnny Clapham
// to compile:
//   put cpp in bin
//   cmake ..
//   cd debug




class Paddle
{
   public:
      int ySize = 50; // paddle height
      int xSize = 10; // paddle width

      int xPositionOne = 0; //x location for player 1
      int xPositionTwo = 790; //x location for player 2
      int yPosition = 300; //y location

      void moveUp()
      {
        yPosition -=10; //decrease pixels from top
        return;
      }

      void moveDown()
      {
        yPosition +=10; // increase pixels from top
        return;
      }
};

class Ball
{
   public:
      int radius = 10; // circle radius

      int xPosition = 100; //x location
      int yPosition = 100; //y location

      void move(int xDirection,int yDirection, int ballSpeed){
        //direction should be +1 or -1
        //ballSpeed can be any number (default 1)
        xPosition += ballSpeed * xDirection;
        yPosition += ballSpeed * yDirection;
        return;
      }

      void resetBall(){
        xPosition=400;
        yPosition=300;
      }
};













int main(int argc, char** argv)
{
  // create main window & disable resize
  sf::RenderWindow App(sf::VideoMode(800,600,32),
          "Pong Game - SFML - By Johnny Clapham"
          ,sf::Style::Titlebar | sf::Style::Close);

  App.clear(sf::Color::Black); //start with a blue background (change later)
  App.display();

  //set sound buffer for pong sound
  sf::SoundBuffer bufferpongshort;
  if (!bufferpongshort.loadFromFile("resources/pongshort2.wav")){
    printf("\npong sound failed\n");
    //error
  }

  //set sound buffer for ping sound
  sf::SoundBuffer bufferpingshort;
  if (!bufferpingshort.loadFromFile("resources/pingshort.wav")){
    printf("\nping sound failed\n");
    //error
  }

  //set sound buffer for score sound
  sf::SoundBuffer bufferscoreshort;
  if (!bufferscoreshort.loadFromFile("resources/scoreshort.wav")){
    printf("\nscore sound failed\n");
    //error
  }

  sf::Music music;
  if (!music.openFromFile("resources/backgroundtheme.ogg")){
    printf("\nscore sound failed\n");
    //error
  }



  sf::Sound pongshort;
  sf::Sound pingshort;
  sf::Sound scoreshort;
  pongshort.setBuffer(bufferpongshort);
  pingshort.setBuffer(bufferpingshort);
  scoreshort.setBuffer(bufferscoreshort);


  //Initialize our font
  sf::Font font;
  if (!font.loadFromFile("resources/ACETONE.ttf")){
    printf("\ngame closed\n");}


  //Initialize a paddle object for player 1
  Paddle paddlePlayer1;
  //Initialize a paddle object for player 2
  Paddle paddlePlayer2;
  //Initialize a ball object
  Ball myBall;

  //create sfml rectangleOne with attributes of the paddlePlayer1
  sf::RectangleShape rectangleOne;
  rectangleOne.setSize(sf::Vector2f(paddlePlayer1.xSize, paddlePlayer1.ySize));
  rectangleOne.setFillColor(sf::Color::Red);
  rectangleOne.setOutlineThickness(1);
  rectangleOne.setPosition(paddlePlayer1.xPositionOne, paddlePlayer1.yPosition);

  //create sfml rectangleOne with attributes of the paddlePlayer2
  sf::RectangleShape rectangleTwo;
  rectangleTwo.setSize(sf::Vector2f(paddlePlayer2.xSize, paddlePlayer2.ySize));
  rectangleTwo.setFillColor(sf::Color::Red);
  rectangleTwo.setOutlineThickness(1);
  rectangleTwo.setPosition(paddlePlayer2.xPositionTwo, paddlePlayer2.yPosition);

  //create sfml ball with attributes from the myBall object
  sf::CircleShape circle(myBall.radius);
  circle.setPosition(400, 300);
  circle.setFillColor(sf::Color(255, 50, 50));

  //create our redraw flag
  int redrawFlag =1;

  //create our text object to display score
  int score1=10, score2 = 20;


  //create sfml text to display score to player
  sf::Text scoreText; //updated during re-rendering
  scoreText.setFont(font); // font is a sf::Font
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::Green);
  scoreText.setStyle(sf::Text::Bold);
  scoreText.setPosition(250,0);
  //initialize both players score @0
  int player1Score=0;
  int player2Score=0;




  sf::Clock clock;
  int frame = 0;
  int speed = 3;
  int xDirection=speed;
  int yDirection=speed;
  int startBallMovementFlag=0;
  int ballSpeed = 1;


  music.play();

  //##########################
  //##########################
  //###start main game loop###
  while(App.isOpen())
  {


    frame+=1;
    App.setFramerateLimit(60);
    //sf::Time elapsed = clock.restart();
    //redrawFlag=0; //turn redraw flag off

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //##################EVENT BLOCK###########################
    // process events
    sf::Event Event;
    while(App.pollEvent(Event)){

              // Exit
              if(Event.type == sf::Event::Closed){
                App.close();
                printf("\ngame closed\n");
              }

              // key pressed event
              if (Event.type == sf::Event::KeyPressed)
              {

                      // exit key: exit game
                      if (Event.key.code == sf::Keyboard::Key::Escape){
                          App.close();
                          std::cout << "Game closed\n";
                        }

                      // down arrow: paddle down
                      if (Event.key.code == sf::Keyboard::Key::Space){
                          startBallMovementFlag = 1;
                          std::cout << "Space pressed! Ball should now move.\n";
                          music.stop();
                        }
                    //update the rectangleOne position to be drawn in render
                    //rectangleOne.setPosition(paddlePlayer1.xPositionOne, paddlePlayer1.yPosition);
              }
    }
    //###################END EVENT BLOCK#######################
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//8888888888888888888888888888888888888888888888888888888888888888888888888888
//8888888888888888888 PADDLE MOVEMENT CODE 88888888888888888888888888888888888
//8888888888888888888888888888888888888888888888888888888888888888888888888888
      //new iskeypressed methods ensure BUTTER SMOOTH paddle movement
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
               std::cout << "Paddle moving up\n";
               paddlePlayer1.moveUp();
               //if we are at max height stay there
               if (paddlePlayer1.yPosition<0){paddlePlayer1.yPosition=0;}
               //update rectangleOne position to render
               rectangleOne.setPosition(paddlePlayer1.xPositionOne, paddlePlayer1.yPosition);
               //signal render updated
               redrawFlag=1;
      }
      //new iskeypressed methods ensure BUTTER SMOOTH paddle movement
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      {
                std::cout << "Paddle moving down\n";
                paddlePlayer1.moveDown();
                //if we are at min height stay there
                if (paddlePlayer1.yPosition>550){paddlePlayer1.yPosition=550;}
                //update rectangleOne position to render
                rectangleOne.setPosition(paddlePlayer1.xPositionOne, paddlePlayer1.yPosition);
                //signal render updated
                redrawFlag=1;
      }

      //new iskeypressed methods ensure BUTTER SMOOTH paddle movement
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
               std::cout << "Paddle moving up\n";
               paddlePlayer2.moveUp();
               //if we are at max height stay there
               if (paddlePlayer2.yPosition<0){paddlePlayer2.yPosition=0;}
               //update rectangleOne position to render
               rectangleTwo.setPosition(paddlePlayer2.xPositionTwo, paddlePlayer2.yPosition);
               //signal render updated
               redrawFlag=1;
      }
      //new iskeypressed methods ensure BUTTER SMOOTH paddle movement
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
                std::cout << "Paddle moving down\n";
                paddlePlayer2.moveDown();
                //if we are at min height stay there
                if (paddlePlayer2.yPosition>550){paddlePlayer2.yPosition=550;}
                //update rectangleOne position to render
                rectangleTwo.setPosition(paddlePlayer2.xPositionTwo, paddlePlayer2.yPosition);
                //signal render updated
                redrawFlag=1;
      }
//8888888888888888888888888888888888888888888888888888888888888888888888888888
//888888888888888888888 END PADDLE MOVEMENT CODE 88888888888888888888888888888
//8888888888888888888888888888888888888888888888888888888888888888888888888888


      //!!!below is ball movement code
      if (startBallMovementFlag==1){ //if the game has started
        myBall.move(xDirection,yDirection,ballSpeed);

        //!!!!if/else for left and right sides of court
        //we take into account paddle width (10) & ball radius (10) 20 padding
        if(myBall.xPosition<=20){
                //if our ball is within the y of our paddle, we hit ball
                if((myBall.yPosition>=(paddlePlayer1.yPosition-10))  &&
                   (myBall.yPosition<=(paddlePlayer1.yPosition+paddlePlayer1.ySize+10))){
                     std::cout << "HIT!\n";
                     xDirection=xDirection*-1;
                     pingshort.play();
                     ballSpeed+=0.5;

                } else { // else the player scores
                  startBallMovementFlag = 0; //disable ball movement
                  myBall.resetBall(); //reset the ball to middle of screen
                  player2Score++; //increase the player score
                  scoreshort.play(); //play our sound effect
                  ballSpeed=1; //decrease back to default
                }
        //we take into account paddle width (10) & ball radius (10) 20 padding
        } else if (myBall.xPosition>=780){
                //if our ball is within the y of our paddle, we hit ball
                if((myBall.yPosition>=(paddlePlayer2.yPosition-10))  &&
                   (myBall.yPosition<=(paddlePlayer2.yPosition+paddlePlayer2.ySize+10))){
                     std::cout << "HIT!\n";
                     xDirection=xDirection*-1;
                     pingshort.play();
                     ballSpeed+=0.5;

                } else { // else the player scores
                  startBallMovementFlag = 0; //disable ball movement
                  myBall.resetBall(); //reset ball to middle of screen
                  player1Score++; //increase player score
                  scoreshort.play(); //play sound effect
                  ballSpeed=1; //decrease back to default
                }
        }

        //!!!!if/else for top and bottom sides of court
        if (myBall.yPosition<=0){
                yDirection=yDirection*-1;
                pongshort.play();

        } else if (myBall.yPosition>=600){
                yDirection=yDirection*-1;
                pongshort.play();
        }



        //update circle position for our ball coordinates to render
        circle.setPosition(myBall.xPosition, myBall.yPosition);
        redrawFlag=1; //We must signal our ball has moved

      }
      // std::cout << "Ball y: ";
      // std::cout << myBall.yPosition;
      // std::cout << "./";




      if(player1Score<11 && player2Score<11){
        //set the score with updated values
        //if the game is fresh, show controls
        if(player1Score==0 && player2Score==0){
          std::string scoreString = std::string("New Game Started!\n\nControls:\n")+
                                    std::string("Release Ball: Spacebar.\n")+
                                    std::string("Movement: W/S & Up/Down");
                                    scoreText.setString(scoreString);
        } else {
          std::string scoreString = "Player 1: " + std::to_string(player1Score) +
                                    "    "       +
                                    "Player 2: " + std::to_string(player2Score);
                                    scoreText.setString(scoreString);
        }




      } else {
        if (player1Score==11){
          //player 1 wins
          std::string scoreString = std::string("Player 1 wins with 11 points!\n")+
                                    std::string("Press any key to restart game.\n")+
                                    std::string("Press Esc. key to exit.");
          scoreText.setString(scoreString);
          player1Score=0;
          player2Score=0;
        } else {
          //player 2 wins
          std::string scoreString = std::string("Player 2 wins with 11 points!\n")+
                                    std::string("Press any key to restart game.\n")+
                                    std::string("Press Esc. key to exit.");
          scoreText.setString(scoreString);
          player1Score=0;
          player2Score=0;
        }
      }











      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      //#############GAME VIEW###################
      //#########################################
      //redraw the game view if logic has updated
      if (redrawFlag==1){
        // std::cout << "Drawing frame #:";
        // std::cout << frame;
        // std::cout << ".\n";

        App.clear(sf::Color::Black); //clear screen for drawing
        //draw the objects
        App.draw(circle); //draw our myBall object
        App.draw(rectangleOne); //draw our paddlePlayer1 object
        App.draw(rectangleTwo); //draw our paddlePlayer1 object
        App.draw(scoreText); //draw our score text
        //display our new rendered scene
        App.display();
      }
      //#########################################
      //############END GAME VIEW################
      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      // std::cout << "Drawing frame #:";
      // std::cout << frame;
      // std::cout << ".\n";
      sf::sleep(sf::milliseconds(1));
      redrawFlag=0; //turn off render fag again






  }

  //end program
  return 0;
}
