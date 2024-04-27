#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "observer.h"
#include "window.h"
#include "cell.h"


class Cell;

class GraphicsDisplay: public Observer{
    Xwindow *window;
    int GridSize;

    public:
    GraphicsDisplay();
    void notify(Cell &c) override;
    SubscriptionType subType() override;
    void DrawGrid(int n);
    void UpdateWindow(int r, int c, bool isOn);
    int promptUser(const std::string &s); 
    void displayString(int x, int y, std::string msg);
    std::vector<int> getCell(); // Processes mouse click
    

    ~GraphicsDisplay();


};
