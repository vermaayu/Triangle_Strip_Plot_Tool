// TriangleStripPlotTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <fstream>

#define W_WIDTH  1000
#define W_HEIGHT  1000

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
Point arr[100];
int index = 0;
int flag = 0;

/////////////////////////////////////////////////////////////////////////////////

void drawDot(float x, float y) {
	//glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0,1.0,0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
}


void drawLine(float x1 , float y1, float x2, float y2){
	//glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
	glEnd();
	glFlush();
}


void drawStrip(float x1 , float y1, float x2, float y2, float x3, float y3){
	//glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
	glFlush();
}




/*-----------------------Mouse Click Fn--------------------------*/


void mouse(int button, int state , int x , int y) {
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
{	cout << "(" << (x-(W_WIDTH/2)) << ", " << ((W_HEIGHT/2)-y) << ")\n" << endl;			// Figures will be made in the first quadrant.
	arr[index].setxy((float)(x-(W_WIDTH/2)),(float)((W_HEIGHT/2)-y));
    index++;
	
}
	
else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
{
	ofstream myfile;
	myfile.open ("Coordinate.txt");
	for(int i = 0 ;i<(sizeof(arr)/sizeof(*arr)); i++)
	{
		myfile << "(" << arr[i].x << ", " << arr[i].y << ")\n";
	}
	myfile.close();
}

else if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
{


}

	
glutPostRedisplay();					//////////////////////////////Check this
}

/*--------------Window Creation Specs--------------------------------------*/


void display()
{
	


	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to black and opaque
	//glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
	//glutMouseFunc(mouse);

	drawDot(arr[index-1].x, arr[index-1].y);
	
	if(flag >= 3)
	{
		drawStrip(arr[index-3].x , arr[index-3].y, arr[index-2].x, arr[index-2].y, arr[index-1].x, arr[index-1].y);

		//cout<< "\n "<<arr[index-2].x << " "<< arr[index-2].y << " - "<< arr[index-1].x << " " << arr[index-1].y << " - " << arr[index].x << " " << arr[index].y <<endl;
		
		//cout<< arr[index].x << " " << arr[index].y <<endl;


		drawLine(arr[index-2].x, arr[index-2].y, arr[index-1].x, arr[index-1].y);
	}

	else
	{
		drawLine(arr[index-1].x, arr[index-1].y, arr[index].x, arr[index].y);
		flag++;

	}

	glFlush(); 
}
/*--------------Window Creation Specs Ends--------------------------------------*/


/*----------------------------------------------XoX-------------------------------------------------------------------------------*/

int main(int argc,char **argv)
{
	
	glutInit(&argc,argv);	
	
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(2000,200);
	glutCreateWindow("Triangle_Strip_Workspace");
	gluOrtho2D(-(W_WIDTH/2), W_WIDTH/2,-(W_HEIGHT/2),W_HEIGHT/2);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	
	
	
	glutMainLoop();
	
	return 0;
}