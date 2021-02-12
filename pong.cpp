#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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

      void move(int direction, int ballSpeed){
        //direction should be +1 or -1
        //ballSpeed can be any number (default 1)
        xPosition += ballSpeed * direction;
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

  //Initialize our font
  sf::Font font;
  if (!font.loadFromFile("arial.ttf")){
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
  scoreText.setFillColor(sf::Color::Red);
  scoreText.setStyle(sf::Text::Bold);
  scoreText.setPosition(250,0);
  //initialize both players score @0
  int player1Score=0;
  int player2Score=0;




  sf::Clock clock;
  int frame = 0;
  int direction=10;
  int startBallMovementFlag=0;
  int ballSpeed = 1;


  //##########################
  //##########################
  //###start main game loop###
  while(App.isOpen())
  {
    frame+=1;
    App.setFramerateLimit(30);
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
                      // up arrow: paddle up
                      if (Event.key.code == sf::Keyboard::Key::Up){
                          //std::cout << "Paddle moving up\n";
                          myPaddle.moveUp();
                          //if we are at max height stay there
                          if (myPaddle.yPosition<0){
                            myPaddle.yPosition=0;
                          }
                          redrawFlag=1;
                        }

                      // down arrow: paddle down
                      if (Event.key.code == sf::Keyboard::Key::Down){
                          //std::cout << "Paddle moving down\n";
                          myPaddle.moveDown();
                          //if we are at min height stay there
                          if (myPaddle.yPosition>600){
                            myPaddle.yPosition=600;
                          }
                          redrawFlag=1;
                        }

                      // down arrow: paddle down
                      if (Event.key.code == sf::Keyboard::Key::Space){
                          startBallMovementFlag = 1;
                          std::cout << "Space pressed! Ball should now move.\n";
                        }
              }
    }
    //###################END EVENT BLOCK#######################
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!









      if (startBallMovementFlag==1){ //if the game has started
        myBall.move(direction,ballSpeed);
        // std::cout << "Ball x: ";
        // std::cout << myBall.xPosition;
        // std::cout << "./";
        if(myBall.xPosition<=0){
          int upperLim = myPaddle.yPosition-30;
          int lowerLim = myPaddle.yPosition+30;

          //if our ball is within the y of our paddle, we hit ball
          if((myBall.yPosition>=myPaddle.yPosition)  &&
             (myBall.yPosition<=(myPaddle.yPosition+myPaddle.ySize))){
               std::cout << "HIT!\n";
               direction=direction*-1;

          } else { // else the player scores
            startBallMovementFlag = 0; //disable ball movement
            myBall.resetBall();
            player2Score++;
          }




        } else if (myBall.xPosition>=800){
          direction=direction*-1;
          //player1Score++;
        }

        redrawFlag=1; //We must signal our ball has moved

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
        //set positions of objects
        rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);
        circle.setPosition(myBall.xPosition, myBall.yPosition);

        //draw the objects
        App.draw(circle); //draw our myBall object
        App.draw(rectangle); //draw our myPaddle object

        //set the score with updated values
        std::string scoreString = "Player 1: " + std::to_string(player1Score) +
                                  "    "       +
                                  "Player 2: " + std::to_string(player2Score);
        scoreText.setString(scoreString);
        App.draw(scoreText); //draw our score text

        //display our new rendered scene
        App.display();
      }
      //#########################################
      //############END GAME VIEW################
      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@







  }

  //end program
  return 0;
}
