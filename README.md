# LightsOut
Lights Out Game implemented using C++ and X11 GUI library 

## Game Description



https://github.com/AkramUW/LightsOut.cpp/assets/37009741/d3903f31-59f7-45ac-92fd-1aa8227fffa7

In the [Lights Out Game](https://en.wikipedia.org/wiki/Lights_Out_(game)), you start out by providing your desired Grid size (n), then a grid of n x n cells is generated with n random cells turned on. Clicking on a cell toggles it on and off, as well as its neighbours in a cross(+) pattern. The goal of the player is to clear the board in a certain number of moves. 

The bigger n gets, the harder the game is and the more moves you get. A 2x2 grid is trivial for anybody, a 3x3 grid is more challenging and so on. X11 can handle loading up to 100x100 cells, but the game would be impossibly difficult at that point.

## How to Play

<ol>
<li>Download X11 server: 

[Windows](https://sourceforge.net/projects/xming/) or  [Mac/Linux](https://www.cyberciti.biz/faq/apple-osx-mountain-lion-mavericks-install-xquartz-server/)
 </li>
<li> Download the executable <code>lightsout</code> from this git repo</li>
<li>Make Sure the X11 server is running, run the executable from your terminal and start playing </li>
</ol>

## Implementation

The Lights out game makes use of the Observer Pattern. Each cell in the grid has a set of observers including not only its neighbouring cells but also the GraphicDisplay and the TextDisplay (which was used for testing). Each observer has one of two types: <code>All</code> meaning it's subscribed to all events, including when the cell is switched on during initialization, and <code>SwitchOnly</code> which is primarily for neighboring cells to be notified when their neighbour is toggled.
