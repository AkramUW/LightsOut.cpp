#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height} {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open d" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask | ButtonPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[5][10]={"white", "black", "red", "green", "blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make w non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XFontStruct* font_info = XQueryFont(d, XGContextFromGC(gc));
  int text_width = XTextWidth(font_info, msg.c_str(), msg.length());
  int font_height = font_info->ascent + font_info->descent;
  XClearArea(d, w, x, y - font_info->ascent, max(130,text_width), font_height, False);
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  XFreeFontInfo(NULL, font_info, 1);
}

int Xwindow::drawPrompt(const std::string &s) {
  XEvent event;
  bool running = true;
  std::string input;
  int x = 20, y = 50;  // Text position

  XFontStruct* font_info = XQueryFont(d, XGContextFromGC(gc));
  int text_width = XTextWidth(font_info, s.c_str(), s.length());
  int font_height = font_info->ascent + font_info->descent;

  while(running) {
      XNextEvent(d, &event);

      if (event.type == Expose) {
          XDrawRectangle(d, w, gc, 10, 10, 480, 80);  // Draw the rectangle
          XDrawString(d, w, gc, x, y, s.c_str(), s.length());  // Draw the prompt
      }

      if (event.type == KeyPress) {
          char buf[128] = {0};
          KeySym keysym;
          int len = XLookupString(&event.xkey, buf, sizeof(buf), &keysym, nullptr);

          if (keysym == XK_Return) {
              running = false;
          } else if (keysym == XK_BackSpace && !input.empty()) {
                input.pop_back();
                // Recalculate the input width
                int input_width = XTextWidth(font_info, input.c_str(), input.length());
                XClearArea(d, w, x + text_width, y - font_info->ascent, 400 - text_width, font_height, False);
                // Redraw the input
                XDrawString(d, w, gc, x + text_width + 50, y, input.c_str(), input.length());
            } else if (isdigit(buf[0])) {
                input += buf[0];
                // Clear the input area before drawing the new input
                int input_width = XTextWidth(font_info, input.c_str(), input.length());
                XClearArea(d, w, x + text_width, y - font_info->ascent, 400 - text_width, font_height, False);
                // Redraw the input
                XDrawString(d, w, gc, x + text_width + 50, y, input.c_str(), input.length());
            }
      }
  }
  XFreeFontInfo(NULL, font_info, 1);
  XClearWindow(d,w);
  return stoi(input);
}

vector<int> Xwindow::trackClick(){
  vector<int> ret;
  XEvent event;
  XSelectInput(d, w, ButtonPressMask);
        while (true) {
            XNextEvent(d, &event);
            if (event.type == ButtonPress) {
                // Extract the x and y coordinates
                int x = event.xbutton.x;
                int y = event.xbutton.y;
                ret.push_back(x);
                ret.push_back(y);
                return ret;
            }
        }

}

