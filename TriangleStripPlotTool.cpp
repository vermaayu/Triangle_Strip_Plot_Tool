// TriangleStripPlotTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <fstream>

#define W_WIDTH  500
#define W_HEIGHT  500

using namespace std;



class Point{										// Points
public:
	float x, y;
	void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }
    //operator overloading for '=' sign
    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }

};

/////////////////////GLOBAL VARIABLES////////////////////////////////////////////

float h1,h2;
Point arr[10];
int index = 0;
int flag = 0;

/////////////////////////////////////////////////////////////////////////////////

void drawDot(int x, int y) {
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0,1.0,0.0);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}


void drawLine(float x1 , float y1, float x2, float y2){
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
	glEnd();
}


void drawStrip(float x1 , float y1, float x2, float y2, float x3, float y3){
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
}




/*-----------------------Mouse Click Fn--------------------------*/


void mouse(int button, int state , int x , int y) {
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
{	cout << "(" << (x) << ", " << (500-y) << ")\n" << endl;			// Figures will be made in the first quadrant.
	arr[index].setxy((float)x,(float)(500 - y));
    index++;
	drawDot(x,y);
}
	
else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
{
	ofstream myfile;
	myfile.open ("Coordinate.txt");
	for(int i = 0 ;i<(sizeof(arr)/sizeof(*arr)); i++){
		myfile << "(" << arr[i].x << ", " << arr[i].y << ")\n";
	}
	myfile.close();

}

	if(flag == 3)
	{
		drawStrip(arr[index-2].x , arr[index-2].y, arr[index-1].x, arr[index-1].y, arr[index].x, arr[index].y);
	}
	else
	{
		flag++;
	}


	glutPostRedisplay();					//////////////////////////////Check this
}

/*--------------Window Creation Specs--------------------------------------*/
void init()
{
	glClearColor(0.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
	
 
   glFlush(); 
}
/*--------------Window Creation Specs Ends--------------------------------------*/


/*----------------------------------------------XoX-------------------------------------------------------------------------------*/

int main(int argc,char **argv)
{
	
	glutInit(&argc,argv);		
	
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(2000,200);
	glutCreateWindow("Triangle_Strip_Workspace");
	
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	
	return 0;
}