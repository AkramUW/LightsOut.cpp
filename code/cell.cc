#include "observer.h"
#include "cell.h"
using namespace std;

Cell::Cell() : r{0}, c{0} {}

bool Cell::getState() const { return isOn; }
int Cell::getRow() const { return r; }
int Cell::getCol() const { return c; }

void Cell::setOn() {
  isOn= true;
}

void Cell::toggle() {
  isOn = !isOn;
}

void Cell::setCoords(int r, int c) { this->r = r; this->c = c; }

void Cell::attach(Observer *o) {
  observers.emplace_back(o);
}

void Cell::notify(Cell &c) {
  this->toggle();
  this->notifyAllObservers(); 
}

SubscriptionType Cell::subType() {
  return SubscriptionType::SwitchOnly;
}

void Cell::notifyAllObservers() {
  for(long unsigned int i = 0; i < observers.size(); i++){
    if (observers.at(i)->subType() == SubscriptionType::All){
      observers.at(i)->notify(*this);
    } 
  }

}

void Cell::notifySwitchObservers() {
  for (Observer* obs:observers){
    if(obs->subType() == SubscriptionType::SwitchOnly){
      obs->notify(*this);
    }
  }
}
