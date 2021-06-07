#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>
using namespace std;

float scale = 0.4;
int X1, Y1, X2, Y2; //starting and ending points of the line
int screenX = 640, screenY = 480;
int xMin = (-screenX/2), xMax = (screenX/2), yMin = (-screenY/2), yMax = (screenY/2);//xMin and xMax determine the range where we plot the vector Field. Similarly for yMin and yMax
GLfloat R = 0, G = 1, B = 1;//R,G, and B values for color determination

void plot(int x, int y) {

    /// <param name="pntX"></param>
    /// <param name="pntY"></param>
    /// Plots integer coordinates X and Y 
    /// cout<<x<<" "<<y<<endl;   
    GLfloat mycolour[3] = { R,G,B };

    glColor3fv(mycolour);        // blue using vector of floats
  //glColor3f(1.0, 0.0, 0.0);      // red using floats
 // glColor3ub(0, 255, 0);           // green using unsigned bytes
    glPointSize(1.0);
    glBegin(GL_POINTS);

    glVertex2i(x + screenX / 2, y + screenY / 2);
    glEnd();
}

void my_Init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(2.3f, 2.5f, 0.5f);
    glPointSize(0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenX, 0, screenY);
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

void MyDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.5, 0.5);
    glPointSize(1.0);

    Bresenham(-screenX, 0, screenX, 0);//Plots the X-axis in the window
    Bresenham(0, -screenY, 0, screenY);//Plots the Y-axis in the window
  
    Bresenham(X1, Y1, X2, Y2);
    glFlush();
}

void main(int argc, char** argv)
{
    cout << "Enter the coordinates of the start and end points:\n\n" << endl;
    //Input starting and ending points
    cout << "X-coordinate of start point: "; cin >> X1;
    cout << "\nY-coordinate of start point: "; cin >> Y1;
    cout << "\nX-coordinate of end point: "; cin >> X2;
    cout << "\nY-coordinate of end point: "; cin >> Y2;



    glutInit(&argc, argv);//glutInit() is used to initialize the GLUT library.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenX, screenY);
    glutInitWindowPosition(100, 150);
     //glutInitDisplayMode() sets the initial display mode. GLUT_RGB: Bit mask to select an RGB mode window.
    // glutInitWindowPosition and   glutInitWindowSize set the initial window position and size respectively.
    glutCreateWindow("Bresenham's algorithm");
    glutDisplayFunc(MyDisplay);
    my_Init();
    glutMainLoop();

}