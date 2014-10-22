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

#define		SCREEN_HEIGHT	8
#define		SCREEN_WIDTH	11
#define		BLOCK_SIZE		8
#define		TRUE			1
#define		FALSE			0
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)


void main() {

	unsigned char	x, y;
	signed char 	xVel, yVel;


	// === Initialize system ================================================
	IFG1=0; /* clear interrupt flag1 */
	WDTCTL=WDTPW+WDTHOLD; /* stop WD */


	init();
	initNokia();
	clearDisplay();
	x=9;		y=4;
	xVel=1;		yVel=1;
	drawBlock(y,x,yVel,xVel);

	while(1){
// Boundary Control for ball path and bounces
		if (y<=0 && yVel<0) {

			yVel = -1*yVel;
		} else if (y>=SCREEN_HEIGHT && yVel>0){
			yVel = -1*yVel;
		}
		if (x<=0 && xVel<0) {
			xVel = -1*xVel;
		} else if (x>=SCREEN_WIDTH && xVel>0){
			xVel = -1*xVel;
		}

// Update Ball's Position
		x=x+xVel;
		y=y+yVel;

/*
		if (UP_BUTTON == 0) {
			while(UP_BUTTON == 0);
			if (y>=1) y=y-1;
			button_press = TRUE;
		} else if (DOWN_BUTTON == 0) {
			while(DOWN_BUTTON == 0);
			if (y<=6) y=y+1;
			button_press = TRUE;
		}

*/

		clearDisplay();
		drawBlock(y,x,yVel,xVel);
// Then I created a delay timer
		long i;
		for(i=0; i<60000; i++);

	}

}
