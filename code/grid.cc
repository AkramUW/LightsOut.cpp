#include <iostream>
#include "grid.h"
using namespace std;

Grid::Grid() {
  gridSize=0;
  // Text display for testing
  td = nullptr;
  // Create empty Graphics Display
  gd = new GraphicsDisplay();
}

Grid::~Grid() {
  clearGrid();
}

int Grid::getSize(){
  return gridSize;
}

void Grid::clearGrid() {
  for(auto &row:theGrid){row.clear();}
  theGrid.clear();
  gridSize = 0;
  delete td;
  delete gd;
  td = nullptr;
}

bool Grid::isWon() const { 
  for(auto row: theGrid){
    for (auto col: row){
      if (col.getState()){
        return false;
      }
    }
  }
  return true;
}

void Grid::init() {
  // Clear old grid if not empty
  if (gridSize !=0){clearGrid();}
  // Get n
  int n = gd->promptUser("Please proivde the grid size:");
  // Init
  gridSize = n;
  theGrid.resize(n);
  td = new TextDisplay(n);
  // Draw grid on GraphicsDisplay
  gd->DrawGrid(n);
  // Attaching Observers
  int r = 0;
  for (auto &row:theGrid){
    row.resize(n); 
    int c = 0;
    for(auto &col:row){  
      col=Cell();
      col.setCoords(r,c);
      col.attach(td);
      col.attach(gd);
      c++;
    }
    r++;
  }
  // Setting Cell Observers
  r = 0;
  for (auto &row:theGrid){
    int c = 0;
    for(auto &col : row){
      if (r < gridSize - 1){col.attach(&theGrid.at(r+1).at(c));}
      if (r > 0){col.attach(&theGrid.at(r-1).at(c));}
      if (c < gridSize - 1){col.attach(&theGrid.at(r).at(c+1));}
      if (c > 0){col.attach(&theGrid.at(r).at(c-1));}
      c++;
    }
    r++;
  }
}

void Grid::turnOn(int r, int c) {
  theGrid.at(r).at(c).setOn();
  theGrid.at(r).at(c).notifyAllObservers();
}

void Grid::toggle(int r, int c) {
  theGrid.at(r).at(c).toggle();
  theGrid.at(r).at(c).notifySwitchObservers();
  theGrid.at(r).at(c).notifyAllObservers();
}

int Grid::getChallenge(){
  return gd->promptUser("How many moves do you think you need to win?");

}

void Grid::drawString(const std::string &s){
  gd->displayString(20,50,s);
}

void Grid::playMove(){
  auto coods = gd->getCell();
  toggle(coods[1], coods[0]);
}

ostream &operator<<(ostream &out, const Grid &g) {
  out << *g.td;
  return out;
}


