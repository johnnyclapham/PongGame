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

      int xPosition = 0; //x location
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

  App.clear(sf::Color::Blue); //start with a blue background (change later)
  App.display();


  //Initialize a paddle object
  Paddle myPaddle;
  //Initialize a paddle object
  Ball myBall;

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

  //create sfml rectangle with attributes of the myPaddle
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(myPaddle.xSize, myPaddle.ySize));
  rectangle.setFillColor(sf::Color::Red);
  rectangle.setOutlineThickness(1);
  rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);

  //create sfml ball with attributes from the myBall object
  sf::CircleShape circle(myBall.radius);
  circle.setPosition(400, 300);
  circle.setFillColor(sf::Color(255, 50, 50));

  //create our redraw flag
  int redrawFlag;

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
  int speed = 6;
  int xDirection=speed;
  int yDirection=speed;
  int startBallMovementFlag=0;
  int ballSpeed = 1;


  //##########################
  //##########################
  //###start main game loop###
  while(App.isOpen())
  {
    frame+=1;
    App.setFramerateLimit(60);
    //sf::Time elapsed = clock.restart();
    redrawFlag=0; //turn redraw flag off

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
                        }
                    //update the rectangle position to be drawn in render
                    //rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);
              }
    }
    //###################END EVENT BLOCK#######################
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




      //new iskeypressed methods ensure BUTTER SMOOTH paddle movement
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
               std::cout << "Paddle moving up\n";
               myPaddle.moveUp();
               //if we are at max height stay there
               if (myPaddle.yPosition<0){myPaddle.yPosition=0;}
               //update rectangle position to render
               rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);
               //signal render updated
               redrawFlag=1;
      }
      //new iskeypressed methods ensure BUTTER SMOOTH paddle movement
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
                std::cout << "Paddle moving down\n";
                myPaddle.moveDown();
                //if we are at min height stay there
                if (myPaddle.yPosition>600){myPaddle.yPosition=600;}
                //update rectangle position to render
                rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);
                //signal render updated
                redrawFlag=1;
      }



      //!!!below is ball movement code
      if (startBallMovementFlag==1){ //if the game has started
        myBall.move(xDirection,yDirection,ballSpeed);

        //!!!!if/else for left and right sides of court
        if(myBall.xPosition<=0){
                //if our ball is within the y of our paddle, we hit ball
                if((myBall.yPosition>=(myPaddle.yPosition-5))  &&
                   (myBall.yPosition<=(myPaddle.yPosition+myPaddle.ySize+5))){
                     std::cout << "HIT!\n";
                     xDirection=xDirection*-1;
                     pingshort.play();

                } else { // else the player scores
                  startBallMovementFlag = 0; //disable ball movement
                  myBall.resetBall();
                  player2Score++;
                  scoreshort.play();
                }

        } else if (myBall.xPosition>=800){
                xDirection=xDirection*-1;
                pingshort.play();
                //player1Score++;
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
          std::string scoreString = "Player 1: " + std::to_string(player1Score) +
                                    "    "       +
                                    "Player 2: " + std::to_string(player2Score) +
                                    "\nPress spacebar to release ball\n"+
                                    "Press up/ down arrows to move paddle.";
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
        App.draw(rectangle); //draw our myPaddle object
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






  }

  //end program
  return 0;
}
