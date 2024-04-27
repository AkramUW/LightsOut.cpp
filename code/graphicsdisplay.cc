#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay() {
    // Create an Xwindow object with a 500x500 window
    window = new Xwindow(500, 500);
     GridSize = 0;
}

GraphicsDisplay::~GraphicsDisplay() {
    delete window;  // Release the memory allocated for the Xwindow object
}

SubscriptionType GraphicsDisplay::subType(){
    return SubscriptionType::All;
}

void GraphicsDisplay::notify(Cell &c){
    UpdateWindow(c.getRow(), c.getCol(), c.getState());
}

void GraphicsDisplay::DrawGrid(int n) {
    // Calculate the size of each grid cell
    int cellSize = 500 / n;

    // Draw vertical grid lines
    for (int i = 0; i <= n; ++i) {
        int x = i * cellSize;
        window->fillRectangle(x, 0, 1, 500, Xwindow::Red); // Draw red vertical line
    }

    // Draw horizontal grid lines
    for (int i = 0; i <= n; ++i) {
        int y = i * cellSize;
        window->fillRectangle(0, y, 500, 1, Xwindow::Red); // Draw red horizontal line
    }

    GridSize = n;
}

void GraphicsDisplay::UpdateWindow(int r, int c, bool isOn) {
    if (r >= 0 && r < GridSize && c >= 0 && c < GridSize) {
        // Calculate the size of each grid cell
        int cellSize = 500 / GridSize;

        // Calculate the coordinates of the cell
        int x = c == 0 ? 0 : c * cellSize+1 ;
        int y = r == 0 ? 0 : r * cellSize+1 ;

        // Toggle the color of the cell
        window->fillRectangle(x, y, cellSize-1, cellSize-1, isOn ? Xwindow::Black : Xwindow::White);
    }
}

int GraphicsDisplay::promptUser(const std::string &s){
    return window->drawPrompt(s);
}

void GraphicsDisplay::displayString(int x, int y, std::string msg){
    window->drawString(x,y,msg);
}
std::vector<int> GraphicsDisplay::getCell(){
    int cellSize = 500 / GridSize;
    auto click_pos = window->trackClick();
    for(auto &e : click_pos){e /=cellSize;}
    return click_pos; // {r,c}
}
