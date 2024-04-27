#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  int gridSize;    // Size of the grid.
  int challenge; // Number of moves to win
  TextDisplay *td; // The text display.
  GraphicsDisplay *gd;
  

  void clearGrid();   // Frees the grid.

 public:
  Grid(); // Grid is initially 0x0
  ~Grid();
  
  bool isWon() const; // Returns whether or not grid is in a winning state.
  void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
  int getSize();
  void drawString(const std::string &s);
  int getChallenge();
  void playMove();
  void turnOn(int r, int c);  // Sets cell at row r, col c to On.
  void toggle(int r, int c);  // Toggles cell at row r, col c.
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
