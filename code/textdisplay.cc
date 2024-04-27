#include <iostream>
#include "textdisplay.h"
#include "cell.h"
using namespace std;

const char CELL_ON = 'X';
const char CELL_OFF = '_';


TextDisplay::TextDisplay(int n): gridSize{n} {
  theDisplay.resize(n);
  for(auto &row:theDisplay){
    row.assign(n,CELL_OFF);
  }
}

void TextDisplay::notify(Cell &c) {
  int col = c.getCol();
  int row = c.getRow();
  char curr = theDisplay.at(row).at(col);
  if (curr == CELL_ON) {theDisplay.at(row).at(col) = CELL_OFF;}
  else{theDisplay.at(row).at(col) = CELL_ON;}
}

TextDisplay::~TextDisplay() {}

SubscriptionType TextDisplay::subType() {
  return SubscriptionType::All;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for(int row = 0; row < td.gridSize; row++ ){
    for (int col = 0; col < td.gridSize; col++){
      out << td.theDisplay.at(row).at(col);
    }
    out << endl;
  }
  return out;
}
