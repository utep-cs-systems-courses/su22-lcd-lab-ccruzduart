
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

#define LED BIT6

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)


static char switch_update_interrupt_sense() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init() {
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

char  switchDown = 0;

void switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();
  switchDown = ~p2val & SWITCHES;
  //movement();
}

char scoreCount = '0', scoreCount2 = '0', playerX, playerY;
int secondCount2 = 0, createMazeV = 1, redrawScreen = 1;
int moveLeft = 0, moveRight = 0, moveUp = 0, moveDown = 0;
int coin1 = 1, coin2 = 1, coin3 = 1, sound1 = 0, sound2 = 0;

void movement() {
  // player reach goal
  if (playerX >= 12 && playerX <= 23 && playerY >= 134 && playerY <= 146 ) {
    createMazeV = 1;
    coin1 = 1;
    coin2 = 1;
    coin3 = 1;
    sound2 = 1;
  }
  
  //botton 1 is being press player move to left
  if(switchDown == 1) {
    if((playerX <= 6) ||
       (playerY >= 25 && playerY <= 35 && playerX <= 109) || 
       (playerY >= 55 && playerY <= 65 && playerX <= 109) ||
       (playerY >= 85 && playerY <= 95 && playerX <= 109) ||
       (playerY >= 116 && playerY <= 142 && playerX <= 115 && playerX >= 110) ||
       (playerY >= 116 && playerY <= 142 && playerX <= 85 && playerX >= 80) ||
       (playerY >= 116 && playerY <= 142 && playerX <= 55 && playerX >= 50) ||
       (playerY >= 135 && playerX <= 100 && playerX >= 95) ||
       (playerY >= 135 && playerX <= 70 && playerX >=65) ||
       (playerY >= 135 && playerX <= 40 && playerX >= 35)) {
      switchDown = 0;
    }
    else {                                                   
      moveLeft = 1;
      switchDown = 0;
    }
    
    // botton 2 is being press player move down
  } else if(switchDown == 2) { 
    if ((playerY >= 149) ||
	(playerX <= 108 && playerY <= 29) ||      
	(playerX >= 20 && playerY <= 44 && playerY >= 39) ||
	(playerX <= 108 && playerY <= 59 && playerY >= 54) ||
	(playerX >= 20 && playerY <= 74 && playerY >= 69) ||
	(playerX <= 108 && playerY <= 89 && playerY >=84) ||
	(playerX >= 20 && playerY <= 104 && playerY >= 99) ||
	(playerX <= 114 && playerY <= 119 && playerY >= 114) ||
	(playerX <= 70 && playerX >= 59 && playerY <= 135) ||
	(playerX <= 100 && playerX >= 89 && playerY <= 135) ||
	(playerX <= 40 && playerX >= 29 && playerY <= 135)) {
      switchDown = 0;
    } else {                                             
      moveDown = 1;
      switchDown = 0;
    }
    
    // button 3 is being press player move up  
  } else if(switchDown == 4) {             
    if ((playerY <= 21) ||
	(playerX <= 108 && playerY <= 36) ||           
	(playerX >= 20 && playerY <= 51 && playerY >= 46) ||
	(playerX <= 108 && playerY <= 66 && playerY >= 61) ||
	(playerX >= 20 && playerY <= 81 && playerY >= 76) ||
	(playerX <= 108 && playerY <= 96 && playerY >= 91) ||
	(playerX >= 20 && playerY <= 111 && playerY >= 106) ||
	(playerX <= 108 && playerY <= 126 && playerY >=121) ||
	(playerX >= 104 && playerX <= 115 && playerY >= 140) ||
	(playerX >= 74 && playerX <= 85 && playerY >= 140) ||
	(playerX >= 44 && playerX <= 55 && playerY >= 140)) {
      switchDown = 0;
    } else {                                         
      moveUp = 1;
      switchDown = 0;
    }
    
    // button 4 is being press player move to the right
  } else if(switchDown == 8) {
    if ((playerX >= 117) ||
	(playerY >= 40 && playerY <= 49 && playerX <= 21) ||
	(playerY >= 70 && playerY <= 79 && playerX <= 21) ||
	(playerY >= 101 && playerY <= 110 && playerX <= 21) ||
	(playerY >= 116 && playerY <= 142 && playerX <= 115 && playerX >= 110) ||
	(playerY >= 116 && playerY <= 142 && playerX <= 85 && playerX >= 80) ||
	(playerY >= 116 && playerY <= 142 && playerX <= 55 && playerX >= 50) ||
	(playerY >= 135 && playerX <= 100 && playerX >= 95) ||
	(playerY >= 135 && playerX <= 70 && playerX >= 65) ||
	(playerY >= 135 && playerX <=40 && playerX >= 35)) {
      switchDown = 0;
    } else {                                            
      moveRight = 1;
      switchDown = 0;
    }
  }
}

void erasePlayer() {
  fillRectangle(playerX,playerY,5,5,COLOR_NAVY);
}

void drawPlayer() {
  fillRectangle(playerX,playerY,5,5,COLOR_RED);
}

void scoreUpdate() {
  if(scoreCount >= '9'){
    scoreCount2++;
    scoreCount = '0';
  }
  drawString5x7(3,3,"Score: ",COLOR_GOLD,COLOR_BLACK);
  drawChar5x7(41,3,scoreCount2,COLOR_GOLD,COLOR_BLACK);
  drawChar5x7(47,3,scoreCount,COLOR_GOLD,COLOR_BLACK);
}

void drawCoints() {
  if(coin1) fillRectangle(50,23,5,5,COLOR_YELLOW);
  else fillRectangle(50,23,5,5,COLOR_NAVY);

  if(coin2) fillRectangle(45,38,5,5,COLOR_YELLOW);
  else fillRectangle(45,38,5,5,COLOR_NAVY);

  if(coin3) fillRectangle(30,98,5,5,COLOR_YELLOW);
  else fillRectangle(30,98,5,5,COLOR_NAVY);

  if(playerX >= 49 && playerX <= 56 && playerY >= 22 && playerY <= 29) {
    if(coin1){
      sound1 = 1;
      scoreCount++;
    }
    coin1 = 0;
  }
  if(playerX >= 44 && playerX <= 51 && playerY >= 37 && playerY <= 44) {
    if(coin2){
      sound1 = 1;
      scoreCount++;
    }
    coin2 = 0;
  }
  if(playerX >= 29 && playerX <= 36 && playerY >= 97 && playerY <= 104) {
    if(coin3){
      sound1 = 1;
      scoreCount++;
    }
    coin3 = 0;
  }
}

void updateScreen() {
  drawCoints();
  scoreUpdate();
  if(moveLeft) {
    erasePlayer();
    playerX -= 5;
    drawPlayer();
    moveLeft = 0;
  }
  if(moveRight) {
    erasePlayer();
    playerX += 5;
    drawPlayer();
    moveRight = 0;
  }
  if(moveUp) {
    erasePlayer();
    playerY -= 5;
    drawPlayer();
    moveUp = 0;
  }
  if(moveDown) {
    erasePlayer();
    playerY += 5;
    drawPlayer();
    moveDown = 0;
  }
}

u_char width = screenWidth, height = screenHeight;

void createMaze() {                                     //Initialize the maze
  u_char mazeBar = width-20;                            
  clearScreen(COLOR_NAVY);                              // maze background
  fillRectangle(0,0,width,15,COLOR_BLACK);              //score background
  playerX = 10;
  playerY = 23;
  drawPlayer();
  drawCoints();
  scoreUpdate();
  fillRectangle(0,15,width,5,COLOR_WHITE);              //top
  fillRectangle(0,15,5,height,COLOR_WHITE);             //left
  fillRectangle(0,(height-5),width,5,COLOR_WHITE);      //bot
  fillRectangle((width-5),15,5,height,COLOR_WHITE);     //right
  fillRectangle(0,30,mazeBar,5,COLOR_WHITE);            //first bar
  fillRectangle(20,45,mazeBar,5,COLOR_WHITE);           //second bar
  fillRectangle(0,60,mazeBar,5,COLOR_WHITE);            //third bar
  fillRectangle(20,75,mazeBar,5,COLOR_WHITE);           //4 bar
  fillRectangle(0,90,mazeBar,5,COLOR_WHITE);            //5 bar
  fillRectangle(20,105,mazeBar,5,COLOR_WHITE);          //6 bar
  fillRectangle(0,120,mazeBar,5,COLOR_WHITE);           //7 baR
  fillRectangle(mazeBar,120,5,25,COLOR_WHITE);          //1 horizontal bar
  fillRectangle((mazeBar-15),135,5,25,COLOR_WHITE);     //2 horizontal bar
  fillRectangle((mazeBar-30),120,5,25,COLOR_WHITE);     //3 hor bar 
  fillRectangle((mazeBar-45),135,5,25,COLOR_WHITE);     //4 hor bar 
  fillRectangle((mazeBar-60),120,5,25,COLOR_WHITE);     //5 hor bar
  fillRectangle((mazeBar-75),135,5,25,COLOR_WHITE);     //6 hor bar
  fillRectangle((mazeBar-95),135,10,10,COLOR_GREEN);    //finish
  buzzerOff();
}

void wdt_c_handler() {
  static int secCount = 0;
  secCount++;
  if(secCount >= 25){
    if(switchDown){
      movement();
    }
    redrawScreen = 1;
    secCount = 0;
  }
  if(sound1) {
    coinSound();
  }
  if(sound2) {
    endSound();
  }
}

int soundCount = 0;
void coinSound() {
  soundCount++;
  if(soundCount <= 50){
    buzzer_set_period(5000);
  }
  else {
    sound1 = 0;
    soundCount = 0;
    buzzerOff();
  }
}

void endSound() {
  soundCount++;
  if(soundCount >= 50)
    buzzer_set_period(3500);
  if(soundCount >= 125)
    buzzer_set_period(4500);
  if(soundCount >= 175)
    buzzer_set_period(5500);
  if(soundCount >= 250) {
    sound2 = 0;
    soundCount = 0;
    buzzerOff();
  }
    
}
void main() {
  P1DIR |= LED;
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();
  or_sr(0x8);

  while (1) {
    if(createMazeV) {
      createMaze();
      createMazeV = 0;
    }
    if(redrawScreen) {
      redrawScreen = 0;
      updateScreen();
    }
    P1OUT &= ~LED;
    or_sr(0x10);
    P1OUT |= LED;
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
 
