#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

int main() {
  configureClocks();
  lcd_init();
  createMaze();
}

void drawPlayer(int col, int row, unsigned short color) {
  fillRectangle(col,row,4,4,color);
}

u_char width = screenWidth, height = screenHeight;
void createMaze() {
  u_char mazeBar = width-20;
  clearScreen(COLOR_BLACK);
  drawPlayer(mazeBar+5,8,COLOR_RED);
  fillRectangle(0,0,width,5,COLOR_WHITE);              //top
  fillRectangle(0,0,5,height,COLOR_WHITE);             //left
  fillRectangle(0,(height-5),width,5,COLOR_WHITE);     //bot
  fillRectangle((width-5),0,5,height,COLOR_WHITE);     //right
  fillRectangle(20,15,mazeBar,5,COLOR_WHITE);
  fillRectangle(0,30,mazeBar,5,COLOR_WHITE);
  fillRectangle(20,45,mazeBar,5,COLOR_WHITE);
  fillRectangle(0,60,mazeBar,5,COLOR_WHITE);
  fillRectangle(20,75,mazeBar,5,COLOR_WHITE);
  fillRectangle(0,90,mazeBar,5,COLOR_WHITE);
  fillRectangle(20,105,mazeBar,5,COLOR_WHITE);
  fillRectangle(0,120,mazeBar,5,COLOR_WHITE);
  fillRectangle(mazeBar,120,5,25,COLOR_WHITE);
  fillRectangle((mazeBar-15),135,5,25,COLOR_WHITE);
  fillRectangle((mazeBar-30),120,5,25,COLOR_WHITE);
  fillRectangle((mazeBar-45),135,5,25,COLOR_WHITE);
  fillRectangle((mazeBar-60),120,5,25,COLOR_WHITE);
  fillRectangle((mazeBar-75),135,5,25,COLOR_WHITE);
  fillRectangle((mazeBar-95),135,10,10,COLOR_YELLOW);
}
