@page Algorithm Algorithm Analysis
@tableofcontents

@section line Bresenham's Line Drawing algorithm
Code: Bresenham()
@subsection algo About the algorithm
<ul>
	<li>This algorithm is used for scan converting a line. It was developed by Bresenham.<br></li>
	 <li>It is an efficient method because it involves only integer addition, subtractions, and multiplication operations. There are no floating point computations. These operations can be performed very rapidly so lines can be generated quickly.<br></li>
	<li>The Line Drawing algorithm plots lines on a grid from (X1,Y1) to (X2,Y2).<br></li>
	<li>It uses the sign of the decision parameter to determine which pixel will be drawn.
	Depending on the value of slope(either greater than 1, or less than 1), decision parameter is updated every time a pixel is plotted.</li>
	</ul>
	

  
@subsection Time Timing Analysis
<ol>
	<li>Bresenham() calls Simplify() to swap the coordinates of (X1,Y1) and (X2,Y2) if required according to certain conditions. Swapping is O(1) </li>
	<li>Depending on whether the slope is greater than 1 or less than 1, 
		the loop either iterates through x or y. 
		The time taken on average would be proportional to 0.5*|X2-X1|+0.5*|Y2-Y1|. Let deltax=|X2-X1| and deltay=|Y2-Y1|.</li>

	<li> Time Complexity: O(deltax+deltay)) </li>

		
</ol> 
@section circle Bresenham's Circle Drawing algorithm
@subsection algo2 About the algorithm
Code: midPointCircleAlgo()
<ul>
	<li>Key feature of circle is that it is highly symmetric. So, for whole 360 degree of circle we will divide it in 8-parts each octant of 45 degree. </li>
	 <li>It is an efficient method because it involves only integer addition, subtractions, and multiplication operations. There are no floating point computations. These operations can be performed very rapidly so circle can be generated quickly.<br></li>
	<li>It assumes that the circle is centered on the origin. So for every pixel (x, y) it calculates, we draw a pixel in each of the 8 octants of the circle as shown in PlotCircle()</li>
	<li>It uses the sign of the decision parameter to determine which pixel will be drawn.
	If d > 0, then (x+1, y-1) is to be chosen as the next pixel as it will be closer to the arc.
	Else (x+1, y) is to be chosen as next pixel.</li>
	<li>DeltaE and DeltaSE is used to update the decision parameter</li>
</ul>
	

  
@subsection Times Timing Analysis
<ol>
	<li>Bresenham() calls PlotCircle() to plot symmetric points in every octant. This function is called every time a pixel is chosen. This function takes O(1) time</li>
	<li>(x,y) is initialised as (0,r), where r is radius.</li>
	<li>The loop iterates through x(incrementing it), till y becomes equal to x.This is proportional to |y-x|</li>
	<li> Time Complexity: O(r) (r is radius of circle)</li>
</ol>
@section vectorLine Vector Field using Lines
@subsection algo3 About the algorithm
Code: VectorField()
<ul>
	<li>At a point (x,y), we plot the value of F(x,y) as a vector with tail anchored at (x,y) </li>
	 <li>We use Bresenham's line drawing algorithm with start point (x1,y1) and end point F(x1,y1)+(x,y)<br></li>
	 <li>These vectors are plotted within a range (xMin,yMin) and (xMax,yMax)</li>
	<li>These vectors are plotted at fixed intervals given by 'step'.(For example, if step=10, x and y are increased by 10 after every iteration</li>
</ul>
	

  
@subsection Times2 Timing Analysis
<ol>
	<li>VectorField() calls Bresenham() to draw a line. This function is called every time a vector is plotted. Each call takes O(|deltaX+deltaY|) time. For every (x,y), this time is proportional to F(x,y). If F(x,y)=(f(x),f(y)), deltaX=f(x), deltaY=f(y). Therefore, time taken is proportional f(x)+f(y)</li>
	<li>The loop iterates through x from xMin to xMax, and for each x, y increases from yMin to yMax. Therefore, time taken is proportional to double summation of (f(x)+f(y)) where y increases from yMin to yMax, and x increases from xMin to xMax</li>
	<li> Time Complexity changes according to the function of the vector field. In general it is proportional to the double summation of (f(x)+f(y)) over the ranges of x and y</li>
		
</ol> 

@section vectorCircle Vector Field using Circles
@subsection algo4 About the algorithm
Code: VectorFieldCircle()
<ul>
	<li>At a point (x,y), we plot a circle with center (x,y) and radius equal to length of vector due to vector field function </li>
	 <li>We use Bresenham's circle drawing algorithm with centre (x,y) and radius sqrt(x^2+y^2), where x=f(x) and y=f(y).</li>
	 <li>These vectors are plotted with their centre in the range (xMin,xMax) and (yMin,yMax). This is a nested loop for x and y</li>
	<li>These vectors are plotted at fixed intervals given by 'step'.(For example, if step=10, x and y are increased by 10 after every iteration</li>
</ul>
	

  
@subsection Times3 Timing Analysis
<ol>
	<li>VectorField() calls midPointCircleAlgo() to draw a circle. This function is called every time a vector is plotted. Each call takes O(r) time. Let F(x,y)=(f(x),f(y)). For every (x,y), the radius is proportional to sqrt((f(x))^2+(f(y))^2)</li>
	<li>The loop iterates through x from xMin to xMax, and for each x, y increases from yMin to yMax. Therefore, time taken is proportional to double summation of (sqrt((f(x))^2+(f(y))^2)) where y increases from yMin to yMax, and x increases from xMin to xMax</li>
	<li> Time Complexity changes according to the function of the vector field. In general it is proportional to the double summation of (sqrt((f(x))^2+(f(y))^2)) over the ranges of x and y</li>
</ol> 

@section PolyLines Polylines from Vector Fields
@subsection algo5 About the algorithm
Code: polyline()
<ul>
	<li>At a point (x,y), we plot a vector with tail at (x,y) and head at F(x,y). Further, we plot a vector with tail at F(x,y) and head at corresponding function value </li>
	 <li>We use Bresenham's line drawing algorithm with starting point (x,y) and ending point (x+f(x),y+f(y)) where F(x,y)=(f(x),f(y)).</li>
	 <li>These process is done for n times, where n is fixed.</li>
</ul>
	

  
@subsection Times4 Timing Analysis
<ol>
	<li>VectorField() calls Bresenham() to draw a line. Each call takes O(|deltaX+deltaY|) time. For every (x,y), this time is proportional to F(x,y). If F(x,y)=(f(x),f(y)), deltaX=f(x), deltaY=f(y). Therefore, time taken is proportional to f(x)+f(y)</li>
	<li>A parametric function is used to determine the x and y coordinates</li>
	<li>This process happens n times, n is fixed. </li>
	<li> Time Complexity changes according to the function of the vector field. In general it is proportional to the summation (f(x)+f(y))+(f(f(x))+f(f(y)))+... and so on, where (x,y) is the starting point</li>
</ol> 