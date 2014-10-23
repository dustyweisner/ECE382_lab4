/*
*Lab 4 - mixing C and assembly
*Dustin Weisner, USAFA / 20 Oct 2014 / 20 Oct 2014
*Documentation: None
*/
#include <msp430g2553.h>

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(signed char row, signed char col, signed char yVelocity, signed char xVelocity);
//extern void drawPaddle(signed char rowPaddle, signed char colPaddle, signed char  direction);

#define		SCREEN_HEIGHT	8
#define		SCREEN_WIDTH	11
#define		BLOCK_HEIGHT	8
#define		TRUE			1
#define		FALSE			0

#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)


void main() {

	signed char	x, y;
	signed char xVel, yVel;
	signed char xPad, yPad;
	unsigned char drawpaddle;
	long delaySpeed;


	unsigned char	gameover;


	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */


	init();
	initNokia();
	clearDisplay();
	x=3;		y=SCREEN_HEIGHT/2;
	xVel=1;		yVel=1;
	drawpaddle = FALSE;
	yPad = SCREEN_HEIGHT/2;
	xPad = 0;
	drawBlock(y,x,yVel,xVel);
	drawpaddle = TRUE;
	drawBlock(yPad,xPad,0,0);
	drawpaddle = FALSE;
	gameover=FALSE;
	delaySpeed=100000;
	//drawPaddle(yPad, xPad, direction);

	while(1){
// Boundary Control for ball path and bounces
		if (y<=0 && yVel<0) {

			yVel = -1*yVel;
		} else if (y>=SCREEN_HEIGHT && yVel>0){
			yVel = -1*yVel;
		}
		if (x<=xPad && xVel<0) {
			if (y==yPad||y==yPad+1){
				xVel = -1*xVel;
			} else gameover=TRUE;
		} else if (x>=SCREEN_WIDTH && xVel>0){
			xVel = -1*xVel;
		}
// IF game is not over, update game
		if (gameover==FALSE) {

// Update Ball's Position
			x=x+xVel;
			y=y+yVel;
			clearDisplay();
			drawBlock(y,x,yVel,xVel);

// Programs up and down presses for the paddle

			if (UP_BUTTON==0 && yPad>0) {
				yPad=yPad-1;
			} else if (DOWN_BUTTON==0 && yPad<=SCREEN_HEIGHT-2){
				yPad=yPad+1;
			}

// if statement to change volatile int
			drawpaddle = TRUE;
			drawBlock(yPad,xPad,0,0);
			drawBlock(yPad+1,xPad,0,0);
			drawpaddle = FALSE;

// Then I created a delay timer and made the Speed increase as game continues
			long i;
			for(i=0; i<delaySpeed; i++);
			delaySpeed=delaySpeed-100;

		} else {
			x=0;
			y=0;
			clearDisplay();

			while(1){


			clearDisplay();


			// G
			if (x>=0 && x<=SCREEN_WIDTH) {
			drawBlock(1,x+0,0,0);
			drawBlock(1,x+1,0,0);
			drawBlock(1,x+2,0,0);
			drawBlock(1,x+3,0,0);
			drawBlock(1,x+4,0,0);
			drawBlock(2,x+0,0,0);
			drawBlock(2,x+4,0,0);
			drawBlock(3,x+0,0,0);
			drawBlock(4,x+0,0,0);
			drawBlock(4,x+2,0,0);
			drawBlock(4,x+3,0,0);
			drawBlock(4,x+4,0,0);
			drawBlock(5,x+0,0,0);
			drawBlock(5,x+4,0,0);
			drawBlock(6,x+0,0,0);
			drawBlock(6,x+1,0,0);
			drawBlock(6,x+2,0,0);
			drawBlock(6,x+3,0,0);
			drawBlock(6,x+4,0,0);
			}

			//A

			char A = 6;
			if ((x+A)>=0 && (x+A)<=SCREEN_WIDTH) {
			drawBlock(1,A+x+0,0,0);
			drawBlock(1,A+x+1,0,0);
			drawBlock(1,A+x+2,0,0);
			drawBlock(1,A+x+3,0,0);
			drawBlock(1,A+x+4,0,0);
			drawBlock(2,A+x+0,0,0);
			drawBlock(2,A+x+4,0,0);
			drawBlock(3,A+x+0,0,0);
			drawBlock(3,A+x+1,0,0);
			drawBlock(3,A+x+2,0,0);
			drawBlock(3,A+x+3,0,0);
			drawBlock(3,A+x+4,0,0);
			drawBlock(4,A+x+0,0,0);
			drawBlock(4,A+x+4,0,0);
			drawBlock(5,A+x+0,0,0);
			drawBlock(5,A+x+4,0,0);
			drawBlock(6,A+x+0,0,0);
			drawBlock(6,A+x+4,0,0);
			}

			//M
			char M = A + 6;
			if ((x+M)>=0 && (x+M)<=SCREEN_WIDTH) {
			drawBlock(1,M+x+0,0,0);
			drawBlock(1,M+x+1,0,0);
			drawBlock(1,M+x+3,0,0);
			drawBlock(2,M+x+0,0,0);
			drawBlock(2,M+x+2,0,0);
			drawBlock(3,M+x+0,0,0);
			drawBlock(4,M+x+0,0,0);
			drawBlock(5,M+x+0,0,0);
			drawBlock(6,M+x+0,0,0);
			drawBlock(1,M+x+4,0,0);
			drawBlock(2,M+x+4,0,0);
			drawBlock(3,M+x+4,0,0);
			drawBlock(4,M+x+4,0,0);
			drawBlock(5,M+x+4,0,0);
			drawBlock(6,M+x+4,0,0);
			}

			//M

			char E = M + 6;

			if ((x+E)>=0 && (x+E)<=SCREEN_WIDTH) {
			drawBlock(1,E+x+0,0,0);
			drawBlock(1,E+x+1,0,0);
			drawBlock(1,E+x+2,0,0);
			drawBlock(1,E+x+3,0,0);
			drawBlock(2,E+x+0,0,0);
			drawBlock(3,E+x+0,0,0);
			drawBlock(3,E+x+1,0,0);
			drawBlock(3,E+x+2,0,0);
			drawBlock(4,E+x+0,0,0);
			drawBlock(5,E+x+0,0,0);
			drawBlock(6,E+x+0,0,0);
			drawBlock(6,E+x+1,0,0);
			drawBlock(6,E+x+2,0,0);
			drawBlock(6,E+x+3,0,0);
			}


// Loop message
			if(x<=-18) {
				x=SCREEN_WIDTH;
			} else x-=1;
			
// Delay the scroll movement
			long i;

			for(i=0; i<90000; i++);











		}
		}
	}
}
