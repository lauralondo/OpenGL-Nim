/* londo_hw2.c
 * Laura Londo
 * 14 February 2014
 * HW #2
 *
 * This is a simple version fo the game of nim. the user plays against the
 * computer. Each player can remove any number of stones from one of the
 * three piles. Whoever removes the last stone wins. The User moves first.
 *
 * Directions:
 *	 Click on a pile (or column) to choose the pile to pick from.
 * 	 Enter a number from 1 to 3 to remove that number of stones from the pile.
 * 	 Press the right arrow key to allow the computer to take its turn.
 * 	 Press the escape key at any time to exit the game.
 *
 * The game ends when there are no more stones to pick up. A green circle
 * means the user won. A red X means the user lost.
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>

float WINDOW_SIZE = 700;
int piles[3] = {3, 3, 3};	//the number of rocks in each pile
int curPile = -1;			//the curently selected pile
int turn = 0;				//0 = user's turn,  1 = comp's turn


//creates a gl triangle fan circle of indicated radius and segments
//(requires math.h)
void flatCircle(float cx, float cy, float radius, int segments) {
	float phi, x1, y1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);					//center vertex
	for (int j = 0; j<=segments; j++) {	//for every segment,
		phi = 2 * M_PI * j / segments;	//calculate the new vertex
		x1 = radius * cos(phi) + cx;
		y1 = radius * sin(phi) + cy;
		glVertex2f(x1, y1);
	}
	glEnd();
} //end circle

//creates a gl triangle fan circle of indicated radius and segments
//(requires math.h)
void circle(float cx, float cy, float radius, int segments) {
	float phi, x1, y1;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.4,0.4,0.4);
	glVertex2f(cx, cy);					//center vertex
	glColor3f(0.1,0.1,0.1);
	for (int j = 0; j<=segments; j++) {	//for every segment,
		phi = 2 * M_PI * j / segments;	//calculate the new vertex
		x1 = radius * cos(phi) + cx;
		y1 = radius * sin(phi) + cy;
		glVertex2f(x1, y1);
	}
	glEnd();
} //end circle


//returns 0 if there are still rocks available, or 1 if the game is over
int gameOver(void) {
	for(int i=0; i<3; i++)
		if(piles[i] > 0) return 0;
	return 1;
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//3 background colors

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	if(curPile != 0) glColor3f(0.42, 1.0, 0.87);	//light blue
	glVertex2f(-1.0, -1.0);
	glVertex2f(-1.0, 1.0);
	if(curPile != 0) glColor3f(0.14, 0.62, 0.76); 	//darker blue
	glVertex2f((-1.0/3.0), 1.0);
	glVertex2f((-1.0/3.0), -1.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	if(curPile != 1) glColor3f(0.69, 0.29, 0.74);	//purple
	glVertex2f((-1.0/3.0), -1.0);
	glVertex2f((-1.0/3.0), 1.0);
	if(curPile != 1) glColor3f(0.92, 0.33, 0.38);	//reddish
	glVertex2f((1.0/3.0), 1.0);
	glVertex2f((1.0/3.0), -1.0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	if(curPile != 2) glColor3f(0.99, 0.54, 0.41);	//orange
	glVertex2f((1.0/3.0), -1.0);
	glVertex2f((1.0/3.0), 1.0);
	if(curPile != 2) glColor3f(1.0, 0.82, 0.53);	//yellow
	glVertex2f(1.0, 1.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	//draw stones or gameover screen

	if(!gameOver()){					//if there are more rocks,
		float x = -2.0/3.0;					//x position to draw circle
		for(int i=0; i<3; i++) {			//for each pile,
			float y = -2.0/3.0;				//y position to draw circle
			for(int j=0; j<piles[i]; j++) {	//for each bean in the pile,
				circle(x, y, 0.2, 50);		//draw circle
				y += 2.0/3.0;				//increment y position
			}
			x += 2.0/3.0;					//increment x position
		}
	}
	else {								//else the game is over
		glBegin(GL_POLYGON);				//grey rectangle
		glColor3f(0.2,0.2,0.2);
		glVertex2f(-1.0,0.5);
		glVertex2f(1.0,0.5);
		glVertex2f(1.0,-0.5);
		glVertex2f(-1.0,-0.5);
		glEnd();

		if(turn == 1) {						//if player won
			glColor3f(0.61,0.97,0.49);		//green circle
			flatCircle(0.0,0.0,0.4,100);
			glColor3f(0.2,0.2,0.2);
			flatCircle(0.0,0.0,0.3,100);
		}
		else {								//else computer won
			glColor3f(0.95,0.35,0.40);		//red X
			glBegin(GL_POLYGON);
			glVertex2f(-0.1, 0.0);
			glVertex2f(-0.5, 0.4);
			glVertex2f(-0.3, 0.4);
			glVertex2f(0.0, 0.1);
			glVertex2f(0.3, 0.4);
			glVertex2f(0.5, 0.4);
			glVertex2f(0.1, 0.0);
			glVertex2f(0.5, -0.4);
			glVertex2f(0.3, -0.4);
			glVertex2f(0.0, -0.1);
			glVertex2f(-0.3, -0.4);
			glVertex2f(-0.5, -0.4);
			glEnd();
		}
		turn = -1;						//set turn to -1 to prevent further action
	}
	glFlush();							//flush image to the screen
}


//mouse callback. checks which pile the user selects
void myMouse(int butt, int state, int x, int y)
{
	if (state == GLUT_DOWN && butt == GLUT_LEFT_BUTTON  &&  turn==0) {
		if (x < WINDOW_SIZE/3.0)			//if clicked in the first column
			curPile = 0;
		else if( x > WINDOW_SIZE/3.0  &&  x < 2*WINDOW_SIZE/3.0) //if second column
			curPile = 1;
		else								//else third column
			curPile = 2;
		glutPostRedisplay();				//redisplay to show selection
	}
}


//The keyboard callback
void myKeyboard(char key, int x, int y) {
	int k = (int)key;

	if (k == 27)					//if the user types ESC
		exit(0);					//exit the program
	//if the user types 1-3, a pile has been selected, and it is the user's turn
	else if(k>=49  &&  k<=51  &&  curPile!=-1  &&  turn==0) {
		k -= 48;
		if(piles[curPile] >= k)		//if there are enough rocks in the pile,
			piles[curPile] -= k;	//remove k rocks
		else {						//user chose too many rocks
			printf("THERE AREN'T THAT MANY ROCKS!\n");
			exit(0);
		}
		curPile = -1;				//no pile is curently selected
		turn = 1;					//computer's turn
		glutPostRedisplay();		//redisplay to show removed rocks
	}
}



//The special keys callback. take comp's turn when right arrow pressed
void mySpecialKey(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT  &&  turn == 1)	//if comp's turn & right arrow pressed
	{
		int sub;						//the number of rocks to remove
		do {
			curPile = rand()%3;			//choose the pile to remove from (0-2)
		} while(piles[curPile]==0); 	//try again if the pile is empty

		do {
			sub = rand()%(piles[curPile])+1;//choose the number of rocks to remove (1-3)
		} while(piles[curPile]<sub);	//try again if we chose too many rocks

		piles[curPile] -= sub;			//remove rocks from the pile
		curPile = -1;					//no pile currently selected
		turn = 0;						//player's turn
		glutPostRedisplay();			//redisplay showing removed stones
	}
}


//reshape callback. adjusts both the clipping box and viewport. keeps proportions unchanged
void myReshape(int w, int h) {
	float aspectRatio = 1.0;

	//Compute the aspect ratio of the resized window
	aspectRatio = (float)h / (float)w;

	// Adjust the clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h >= w)
		gluOrtho2D(-1.0, 1.0, -aspectRatio, aspectRatio);
	else
		gluOrtho2D(-1.0/aspectRatio, 1.0/aspectRatio, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	//adjust the viewport
	glViewport(0, 0, w, h);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0,0);					//window position
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);	//window size
	glutCreateWindow ("The Game of Nim");			//window name
	glClearColor(0.0, 0.0, 0.0, 0.0);				//background color
	glClear(GL_COLOR_BUFFER_BIT);

	//The four following statements set up the viewing rectangle
	glMatrixMode(GL_PROJECTION);					// use proj. matrix
	glLoadIdentity();								// load identity matrix
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);				// set orthogr. proj.
	glMatrixMode(GL_MODELVIEW);						// back to modelview m.

	srand(time(NULL));								// seed the random number generator
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKey);
	glutReshapeFunc(myReshape);

	glutMainLoop();
  	return 0;
}
