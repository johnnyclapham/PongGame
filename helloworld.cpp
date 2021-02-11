#include <SFML/Graphics.hpp>
#include <iostream>

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



int main(int argc, char** argv)
{
  // create main window & disable resize
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML", sf::Style::Titlebar | sf::Style::Close);
  App.clear(sf::Color::Blue); //start with a blue background (change later)
  App.display();


  //Initialize a paddle object
  Paddle myPaddle;

  //create a rectangle object with attributes of our paddle
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(myPaddle.xSize, myPaddle.ySize));
  rectangle.setFillColor(sf::Color::Red);
  rectangle.setOutlineThickness(1);
  rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);

  //create our redraw flag
  int redrawFlag;

  // start main game loop
  while(App.isOpen())
  {
    redrawFlag=0; //turn flag off

    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
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
              std::cout << "Paddle moving up\n";
              //myPaddle.yPosition-=10;
              myPaddle.moveUp();

              if (myPaddle.yPosition<0){ //if we are at max height stay there
                myPaddle.yPosition=0;
              }
              redraw=1;
            }

          // down arrow: paddle down
          if (Event.key.code == sf::Keyboard::Key::Down){
              std::cout << "Paddle moving down\n";
              //myPaddle.yPosition+=10;
              myPaddle.moveDown();

              if (myPaddle.yPosition>600){ //if we are at min height stay there
                myPaddle.yPosition=600;
              }
              redraw=1;
            }


      }


      //#########################################
      //redraw the game view if requested by logic
      if (redrawFlag==1){
        std::cout << "Drawing\n";
        App.clear(sf::Color::Black);
        rectangle.setPosition(myPaddle.xPosition, myPaddle.yPosition);
        App.draw(rectangle);
        App.display();
      }
      //#########################################


    }
  }

  //end program
  return 0;
}
