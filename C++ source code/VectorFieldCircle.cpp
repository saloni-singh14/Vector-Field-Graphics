#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>

float scale = 1;
int screenX = 900, screenY = 900;
int xMin = (-screenX * 2 / 3), xMax = (screenX * 2 / 3), yMin = (-screenY * 2 / 3), yMax = (screenY * 2 / 3);
GLfloat R = 0, G = 1, B = 1;
int xPos = 0;
void init() {
    glClearColor(0, 0, 0, 1.0);


}
void reshape(int w, int h)
{
    int screenlen = screenX;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-screenlen, screenlen, -screenlen, screenlen);
    glMatrixMode(GL_MODELVIEW);

}
void plot(int pntX, int pntY) {


    GLfloat mycolour[3] = { R,G,B };

    glColor3fv(mycolour);
    glPointSize(1.0);
    glBegin(GL_POINTS);

    glVertex2f(pntX, pntY);

    glEnd();
}
void plotCircle(int x, int y)
{
    plot(x, y);
    plot(x, -y);
    plot(-x, y);
    plot(-x, -y);
    plot(y, x);
    plot(-y, x);
    plot(y, -x);
    plot(-y, -x);


}
void midPointCircleAlgo(int pntX1, int pntY1, int radius)
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
    int r = radius;
    int x = 0;
    int y = r;
    int decision = 1 - r;//initial value of decision variable.
    int deltaE = 3;
    int deltaSE = -2 * r + 5;
    plotCircle(x + pntX1, y + pntY1);
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
            //y--;
            decision += deltaSE;
            deltaE += 2;
            deltaSE += 4;
            y--;
        }
        x++;
        plotCircle(x + pntX1, y + pntY1);
    }

}
void setRGB(float distance)
{
    /// <summary>
    ///Sets the RGB values according to distance variable.
    /// As distance changes, RGB values change to give colorful vector field
    /// </summary>
    /// <param name="distance"></param>
    R = 1 - distance / (sqrt(2) * screenX / 2);
    G = 0.5 - distance / (sqrt(2) * screenX / 2);
    B = distance / (sqrt(2) * screenX / 2);
}
void VectorFieldCircle()
{
    ///This function plots a vector field according to the given function F(x,y) using Bresenham's Circle drawing algorithm
    /// Step variable determines the interval between the starting points(tail) of the vectors. Suppose the x-coordinate of starting point of a vector is x=x1. Next vector is drawn with x-coordinate value x=x1
    int step = 40;
    int x, y;
    /// The following loop runs for x: from xMin to xMax, and for y from yMin to yMax. It then uses Bresenham's algo to plot a circle with center at each x,y in this range, and radius=length of vector
    // Range where vectors are plotted: xMin to xMax, and yMin to yMax
    int x_function, y_function;//correspond to the vector field function along x and y respectively
    for (int i = xMin; i < xMax; i += step)
    {
        for (int j = yMin; j < yMax; j += step)
        {

            x = i;
            y = j;
            float distance = sqrt(x * x + y * y);

            x_function = (int)((step / (sqrt(2) * 2)) * (100 / distance));
            y_function = (int)((step / (sqrt(2) * 2)) * (100 / distance));
            setRGB(distance);
            midPointCircleAlgo(i, j, (int)sqrt((x_function * x_function + y_function * y_function)));
        }
    }

}
void animate(int) {
    glutPostRedisplay();
    int state = 1;
    glutTimerFunc(1000/60, animate, 0);
    if (xPos > xMin + xMax) {
        xPos = xPos % (abs(xMin) + xMax);

    }
    xPos = xPos + 2;
    switch (state) {
    case 1:
        if (scale > -1)
            scale -= 0.02;
        else
            state = -1;
        break;
    case -1:
        if (scale < 1)
            scale += 0.02;
        else
            state = 1;
        break;

    }
}
void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    R = 0, G = 0, B = 0;
    R = 0, G = 1, B = 1;
    VectorFieldCircle();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("window");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, animate, 0);
    init();
    glutMainLoop();

}