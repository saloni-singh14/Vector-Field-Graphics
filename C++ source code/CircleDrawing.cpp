#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

int pntX1, pntY1, r;
int screenX = 640, screenY = 480;
GLfloat R = 0, G = 1, B = 1;//R,G, and B values for color determination

void plot(int x, int y)
{
	GLfloat mycolour[3] = { R,G,B };// blue
	glColor3fv(mycolour);        // blue using vector of floats
   //glColor3f(1.0, 0.0, 0.0);      // red using floats
  // glColor3ub(0, 255, 0);           // green using unsigned bytes
	glBegin(GL_POINTS);
	glVertex2i(x + screenX/2+pntX1, y + screenY/2 + pntY1);
	glEnd();
}

void my_Init(void)
{
	/// <summary>
	/// Initialises the window where pixels are drawn.
	/// </summary>
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(2.3f, 2.5f, 0.5f);
	glPointSize(0.5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenX, 0, screenY);
}

void PlotCircle(int x, int y)
{
	/// <summary>
	/// This function plots the pixels (x,y) in 8 different symmetric segments of the circle. 
	/// For whole 360 degree of circle we will divide it in 8-parts each octant of 45 degree. For each pixel (x,y) we plot the following coordinates:
	/// 
	/// (x,y)
	/// 
	/// (x,-y)
	/// 
	/// (-x,y)
	/// 
	/// (-x,-y)
	/// 
	/// (y,x)
	/// 
	/// (y,-x)
	/// 
	/// (-y,x)
	/// 
	/// (-y,-x)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	plot(x, y);
	plot(x, -y);
	plot(-x, y);
	plot(-x, -y);
	plot(y, x);
	plot(-y, x);
	plot(y, -x);
	plot(-y, -x);


}
void midPointCircleAlgo()
{
	/// <summary>
	/// In Bresenham’s algorithm at any point (x, y) we have two option either to choose the next pixel in the east i.e. (x+1, y)
	///  or in the south east i.e. (x+1, y-1).
	/// And this can be decided by using the decision parameter decision as: 
	/// 
	///(i) If d > 0, then(x + 1, y - 1) is to be chosen as the next pixel as it will be closer to the arc.
	/// 
	///(ii) else (x + 1, y) is to be chosen as next pixel.
	/// 
	/// On calculating we get deltaE = 3, and deltaSE = -2*r+5. Every time a pixel is chosen, the value of decision is updated
	/// </summary>
	int x = 0;
	int y = r;
	int decision = 1 - r;//initial value of decision variable. 
	int deltaE = 3;
	int deltaSE = -2 * r + 5;
	PlotCircle(x, y);
	while (y > x)
	{
		if (decision < 0)//East Pixel is chosen
		{
			decision += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else // South East pixel is chosen
		{
			decision += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
		PlotCircle(x, y);
	}

}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);

	midPointCircleAlgo();

	glFlush();
}

void main(int argc, char** argv)
{
	cout << "Enter the coordinates of the center:\n\n" << endl;

	cout << "X-coordinate   : "; cin >> pntX1;
	cout << "\nY-coordinate : "; cin >> pntY1;
	cout << "\nEnter radius : "; cin >> r;

	glutInit(&argc, argv);//glutInit() is used to initialize the GLUT library.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenX, screenY);
	glutInitWindowPosition(100, 150);
	//glutInitDisplayMode() sets the initial display mode. GLUT_RGB: Bit mask to select an RGB mode window.
   // glutInitWindowPosition and   glutInitWindowSize set the initial window position and size respectively.
	glutCreateWindow("Circle Algorithm");
	glutDisplayFunc(myDisplay);
	my_Init();
	glutMainLoop();
	
	
	
	

}
