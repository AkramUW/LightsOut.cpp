#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include "grid.h"
using namespace std;

int main() {
  // Raises an exception if cin.fail() or cin.eof() are true.
  //cin.exceptions(ios::eofbit|ios::failbit);
  int moves = 0;
  srand(time(0));
  


  try{

    // Game Loop:
    while(true){
      Grid g;
      g.init();
      int counter = 0;
      int size = g.getSize();
      moves =  size > 3 ? 4*size : 2*size ;
      while(counter < size){
        g.turnOn(rand()%size, rand()%size);
        counter++;
      }
    // Processing moves
      bool game_over = false;
      while(!game_over){
        g.drawString("You got "+ to_string(moves)+" moves left");
        if (moves==1){g.drawString(" 1 Move Left!");} 
        if (moves==0 && !g.isWon()){g.drawString("You Lost!"); game_over = true;continue;}
        else if (g.isWon()){g.drawString("Congrats! You won"); game_over = true;continue;}
        g.playMove();
        moves--;
      }
    }
  } catch (const std::exception& e){
    std::cerr << "An exception occurred: " << e.what() << std::endl;
  }
} // main
