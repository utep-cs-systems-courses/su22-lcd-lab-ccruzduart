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
  movement();
}

int main() {
  configureClocks();
  lcd_init();
  switch_init();
  createMaze();
  enableWDTInterrupts();
  buzzer_init();
  or_sr(0x8);
}

char scoreCount = '0';
char playerX = 10;
char playerY = 23;
int secondCount2 = 0;
void movement() {
  int buzzerCount = 0;
  while(~switch_update_interrupt_sense() & switchDown){
    secondCount2++;
    if (playerX >= 15 && playerX <= 25 && playerY >= 134 && playerY <= 140 ) {
      scoreCount ++;
      scoreUpdate();
      buzzer_set_period(3500);
      buzzer_set_period(4000);
      buzzer_set_period(5000);
      //buzzerOff();
      playerX = 10;
      playerY = 23;
      createMaze();
    }
    if(switchDown == 1 && secondCount2 >= 3500) {
      if(playerX <= 6){
	switchDown = 0;
	secondCount2 = 0;
      }
      else if((playerY >= 25 && playerY <= 35 && playerX <= 109) ||
	      (playerY >= 55 && playerY <= 65 && playerX <= 109) ||
	      (playerY >= 85 && playerY <= 95 && playerX <= 109) ||
	      (playerY >= 116 && playerY <= 142 && playerX <= 115 && playerX >= 110) ||
	      (playerY >= 116 && playerY <= 142 && playerX <= 85 && playerX >= 80) ||
	      (playerY >= 116 && playerY <= 142 && playerX <= 55 && playerX >= 50) ||
	      (playerY >= 135 && playerX <= 100 && playerX >= 95) ||
	      (playerY >= 135 && playerX <= 70 && playerX >=65) ||
	      (playerY >= 135 && playerX <= 40 && playerX >= 35)){
	switchDown = 0;
	secondCount2 = 0;
      }
      else {
	erasePlayer();
	playerX -= 1;
	drawPlayer();
	secondCount2 = 0;
	if(((playerX >= 44 && playerX <= 46) && (playerY >= 36 && playerY <= 39)) ||
	   ((playerX >= 29 && playerX <= 31) && (playerY >= 96 && playerY <= 99))){
	  buzzerCount++;
	  if(buzzerCount >= 3) {
	    buzzerOff();
	    scoreCount++;
	    scoreUpdate();
	  }
	  else buzzer_set_period(5500);
	  secondCount2 = 0;
	}
      }
    } else if(switchDown == 2 && secondCount2 >= 3500) {
      if(playerY >= 149){
	switchDown = 0;
	secondCount2 = 0;
      } else if ((playerX <= 108 && playerY <= 29) ||
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
	secondCount2 = 0;
      } else {
	erasePlayer();
	playerY += 1;
	drawPlayer();
	secondCount2 = 0;
      }
    } else if(switchDown == 4 && secondCount2 >= 3500) {
      if(playerY <= 21) {
	switchDown = 0;
	secondCount2 = 0;
      } else if ((playerX <= 108 && playerY <= 36) ||
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
	secondCount2 = 0;
      } else {
	erasePlayer();
	playerY -= 1;
	drawPlayer();
	secondCount2 = 0;
      }
    } else if(switchDown == 8 && secondCount2 >= 3500) {
      if(playerX >= 117) {
	switchDown = 0;
	secondCount2 = 0;
      } else if ((playerY >= 40 && playerY <= 49 && playerX <= 21) ||
		 (playerY >= 70 && playerY <= 79 && playerX <= 21) ||
		 (playerY >= 101 && playerY <= 110 && playerX <= 21) ||
		 (playerY >= 116 && playerY <= 142 && playerX <= 115 && playerX >= 110) ||
		 (playerY >= 116 && playerY <= 142 && playerX <= 85 && playerX >= 80) ||
		 (playerY >= 116 && playerY <= 142 && playerX <= 55 && playerX >= 50) ||
		 (playerY >= 135 && playerX <= 100 && playerX >= 95) ||
		 (playerY >= 135 && playerX <= 70 && playerX >= 65) ||
		 (playerY >= 135 && playerX <=40 && playerX >= 35)) {
	switchDown = 0;
	secondCount2 = 0;
      } else {
	erasePlayer();
	playerX += 1;
	drawPlayer();
	secondCount2 = 0;
	if ((playerX >= 49 && playerX <= 51) && (playerY >= 22 && playerY <= 24)) {
	  secondCount2 = 0;
	  buzzerCount++;
	  if(buzzerCount >= 3) {
	    buzzerOff();
	    scoreCount++;
	    scoreUpdate();
	  }
	  else buzzer_set_period(5500);
	  //buzzerOff();
	}
      }
    }else if(secondCount2 >= 3500){
      secondCount2 = 0;
      buzzerOff();
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
  drawString5x7(3,3,"Score: ",COLOR_GOLD,COLOR_BLACK);
  drawChar5x7(42,3,scoreCount,COLOR_GOLD,COLOR_BLACK);
}

u_char width = screenWidth, height = screenHeight;
void createMaze() {                                     //Initialize the maze
  u_char mazeBar = width-20;                            
  clearScreen(COLOR_NAVY);
  fillRectangle(0,0,width,15,COLOR_BLACK);
  drawPlayer();
  fillRectangle(50,23,5,5,COLOR_YELLOW);
  fillRectangle(45,38,5,5,COLOR_YELLOW);
  fillRectangle(30,98,5,5,COLOR_YELLOW);
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

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

int secondCount = 0;
void __interrupt_vec(WDT_VECTOR) WDR() {
  secondCount++;
  if(secondCount >= 125) {
    secondCount = 0;
  }
}
  
