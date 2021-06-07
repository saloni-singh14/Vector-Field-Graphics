#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>

//The ratio which determines the length of vector drawn
float scale = 0.4;
//Determines size of window
int screenX = 900, screenY = 900;
//xMin and xMax determine the range where we plot the vector Field. Similarly for yMin and yMax
int xMin = (-screenX * 2 / 3), xMax = (screenX * 2 / 3), yMin = (-screenY * 2 / 3), yMax = (screenY * 2 / 3);
//Values of R, G and B which combine to determine color of pixels
GLfloat R = 0, G = 1, B = 1;//R,G, and B values for color determination
int xParameter(int);
int yParameter(int);


void display();
void reshape(int, int);
void plot(int, int);
void Simplify(int&, int&, int&, int&);
void Bresenham(int, int, int, int);
void animate(int);
void init() {
    /// <summary>
    /// Brief description of init
    /// </summary>
    glClearColor(0, 0, 0, 1.0);//sets color of window
}
void reshape(int w, int h)
{
    /// <summary>
    /// Short description of reshape
    /// </summary>
    /// <param name="w"></param>
    /// <param name="h"></param>
    int screenlen = screenX;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-screenlen, screenlen, -screenlen, screenlen);
    glMatrixMode(GL_MODELVIEW);

}
void plot(int pntX, int pntY) {

    /// <param name="pntX"></param>
    /// <param name="pntY"></param>
    /// Plots integer coordinates X and Y    
    GLfloat mycolour[3] = { R,G,B };

    glColor3fv(mycolour);
    glPointSize(1.0);
    glBegin(GL_POINTS);

    glVertex2i(pntX, pntY);

    glEnd();
}
void swap(int& x, int& y)
{
    /// <summary>
    /// Exchanges the values of x and y
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    int temp = x;
    x = y;
    y = temp;
    return;
}
void Simplify(int& X1, int& Y1, int& X2, int& Y2)
{
    /// <param name="X1"></param>
  /// <param name="Y1"></param>
  /// <param name="X2"></param>
  /// <param name="Y2"></param>

    /// Simplify swaps start and end points of line according to requirements of Bresenham's algo.
    /// 
    /// Case 1: If slope >0 and |slope|< 1: X1 should be smaller than X2, and if both are equal, Y1<Y2. This is because x is being incremented from X1 to X2 in Bresenham() 
    /// 
    /// Case 2: If slope >0 and |slope|> 1: Y1 should be smaller than Y2, and if both are equal, X1<X2. This is because y is being incremented from Y1 to Y2 in Bresenham()
    /// 
    /// Case 3: If slope<0 and |slope| < 1: X1 should be smaller than X2, and if both are equal, Y1 should be greater than Y2. This is because x is being incremented from X1 to X2 in Bresenham() 
    /// 
    /// Case 4: If slope<0 and |slope| greater than 1: Y1 should be greater than Y2, and if both are equal, X1 should be less than Y2. This is because y is being decremented from Y1 to Y2 in Bresenham()
    //dx=change in x, dy=change in Y
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    //deltay and deltax: absolute values of dx and dy. Slope=dy/dx
    int deltay = (dy > 0) ? dy : -1 * dy;
    int deltax = (dx > 0) ? dx : -1 * dx;
    if (dx * dy >= 0)//Slope>=0
    {
        if (dy <= dx)//|Slope|<=1
        {
            if (X1 > X2)
            {
                //start and end points are swapped to get X1<X2
                /// @see swap()
                swap(X1, X2);
                swap(Y1, Y2);
            }
            else if (X1 == X2 && Y1 > Y2)
            {
                //start and end points are swapped to get Y1<Y2(only when X1==X2)
                swap(X1, X2);
                swap(Y1, Y2);
            }

        }
        else
        {
            if (Y1 > Y2)
            {
                swap(X1, X2);
                swap(Y1, Y2);
            }
            else if (Y1 == Y2 && X1 > X2)
            {
                swap(X1, X2);
                swap(Y1, Y2);
            }

        }
    }
    else //Slope <0
    {
        if (deltay <= deltax)//|Slope|<1
        {
            if (X1 > X2)
            {
                swap(X1, X2);
                swap(Y1, Y2);
            }
            else if (X1 == X2 && Y1 > Y2)
            {
                swap(X1, X2);
                swap(Y1, Y2);
            }

        }
        else//|Slope|>1
        {
            if (Y1 < Y2)
            {
                swap(X1, X2);
                swap(Y1, Y2);
            }
            else if (Y1 == Y2 && X1 > X2)
            {
                swap(X1, X2);
                swap(Y1, Y2);
            }

        }
    }


}
void Bresenham(int X1, int Y1, int X2, int Y2)
{
    /// <param name="X1"></param>
    /// <param name="Y1"></param>
    /// <param name="X2"></param>
    /// <param name="Y2"></param>
    /// Bresenham's algorithm for line drawing. It plots lines on a raster grid and it is optimal as it prevents floating point computations 
    /// After plotting point (x,y), the algorithm uses decision parameter d to decide which pixel has to be drawn next. When Slope<0 the next point is either
    /// East pixel, or North East pixel. For Slope>0, either South or South East pixel is chosen. Decision variable is updated after every choice

    /// Simplify() function swaps the coordinates of start and end points, if required
    Simplify(X1, Y1, X2, Y2);
    // calculate dx & dy
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    //   int slope = (Y2 - Y1) / (X2 - X1);
    if ((X2 - X1) * (Y2 - Y1) >= 0) //Slope is +ve
    {
        if (dy <= dx)//|slope|<=1
        {
            int x, y;

            x = X1;
            y = Y1;
            plot(x, y);
            int d = 2 * dy - dx;// initial value of decision parameter d
            int incrE = 2 * dy;//change in decision variable when East pixel is chosen
            int incrNE = 2 * (dy - dx);//change in decision variable when North East pixel is chosen
            // iterate through value of x
            while (x < X2)
            {
                if (d < 0)// E or East is chosen
                {
                    d = d + incrE;
                }
                else  // NE or North East is chosen
                {
                    d = d + incrNE;
                    y++;
                }
                x++;
                plot(x, y);//point is plotted
            }
        }
        else if (dx < dy) //|slope|>1
        {
            int x, y;

            x = X1;
            y = Y1;
            plot(x, y);
            // initial value of decision parameter d
            int d = 2 * dx - (dy);
            int incrE = 2 * dx;//change in decision variable when East pixel is chosen
            int incrNE = 2 * (dx - dy);//change in decision variable when North East pixel is chosen
            // Plot initial given point
            // iterate through value of Y
            while (y < Y2)
            {
                y++;

                if (d < 0)// E or East is chosen
                    d = d + incrE;
                else // NE or North East is chosen
                {
                    d += incrNE;
                    x++;
                }

                // Plot intermediate points
                plot(x, y);
            }
        }
    }
    else // Slope is negative
    {
        int deltay = (dy > 0) ? dy : -1 * dy;
        int deltax = (dx > 0) ? dx : -1 * dx;
        if (deltay > deltax) //|slope|>1
        {
            int x, y;

            x = X1;
            y = Y1;
            plot(x, y);
            int d = 2 * dx + dy;//initial value of decision variable
            int incrS = 2 * dx;//change in decision variable when South pixel is chosen
            int incrSE = 2 * (dx + dy);//change in decision variable when South East pixel is chosen
            while (y > Y2) {
                if (d < 0) {
                    d = d + incrS;
                }
                else {
                    d = d + incrSE;
                    x++;
                }
                y--;
                plot(x, y);
            }
        }
        else //|slope|<=1
        {
            int x, y;
            x = X1;
            y = Y1;
            plot(x, y);
            int d = 2 * dy + dx;//initial value of decision variable
            int incrE = 2 * dy;//change in decision variable when East pixel is chosen
            int incrSE = 2 * (dy + dx);//change in decision variable when South East pixel is chosen
            while (x < X2) {
                if (d < 0) {
                    d = d + incrSE;
                    y--;
                }
                else {
                    d = d + incrE;
                }
                x++;
                plot(x, y);
            }
        }
    }
    /// @see Simplify()
    /// @see plot()

}
void animate(int)
{
    /// This function uses TimerFunc() available in openGL to delay thread execution and animate the resulting output
    glutPostRedisplay();
    int state = 1;
    glutTimerFunc(1000 / 60, animate, 0);

    int xPos = 0;
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
        if (scale < -1)
            scale += 0.02;
        else
            state = 1;
        break;

    }
}
int yParameter(int t)
{
    /// <summary>
    ///  @returns Parametric form of y-coordinate point according to given function. For example, for circle, it will return radius*sint
    /// </summary>
    /// <param name="t"></param>
    /// <returns></returns>
    return (int)(100.0f * sin(t));
}
int xParameter(int t)
{
    /// <summary>
    /// @returns Parametric form of x coordinate point according to given function. For example, for circle, it will return radius*cost
    /// </summary>
    /// <param name="t"></param>
    /// <returns></returns>
    return (int)(t * 5);
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
void polyLine(int t) {
    /// <summary>
   /// Polyline function plots a polyline using Bresenham(). It plots a vector with tail at x,y using bresenham. xParameter() and yParameter() is used to find the x and y coordinates using parametric equation of function
   /// After a point is plotted between (x,y) and (x1,y1), the same process is repeated at point (x1,y1). This is done 'times' times, where 'times' is an integer variable.
   /// </summary>
   /// <param name="t"></param>
    int x, y, x1, y1;
    int delta = 7;
    int times = 100;
    for (; times > 0; times--)
    {
        x = xParameter(t) * scale;
        y = yParameter(t) * scale;
        x1 = xParameter(t + delta) * scale;
        y1 = yParameter(t + delta) * scale;
        Bresenham(x , y, x1, y1);
        t = t + delta;
        //Bresenham(xParameter(t) * scale, yParameter(t) * scale, xParameter(t + delta) * scale, yParameter(t + delta) * scale);
        //t = t + delta;
    }
    ///@see xParameter()
    ///@see yParameter() 
    ///@see Bresenham()

}

void display() {
    /// <summary>
    /// Display function calls Polyline function and sets initial color. It also calls some other built in funvtions to initalise the parameters of the openGL window
    /// </summary>
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    R = 0.5, G = 0.5, B = 0.5;
    Bresenham(-screenX, 0, screenX, 0);//Plots the X-axis in the window
    Bresenham(0, -screenY, 0, screenY);//Plots the Y-axis in the window
    R = 0, G = 1, B = 1;
    polyLine(-10);
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);//glutInit() is used to initialize the GLUT library.

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //glutInitDisplayMode() sets the initial display mode. GLUT_RGB: Bit mask to select an RGB mode window.

    // glutInitWindowPosition and   glutInitWindowSize set the initial window position and size respectively.
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Vector Field - Bresenham");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutTimerFunc(0, animate, 0);
    init();


    glutMainLoop();

}
