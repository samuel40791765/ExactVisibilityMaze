# ExactVisibilityMaze
Project 2: Maze Visibility and Rendering Graphics

Implemented a maze rendering program, not too far removed from those used in computer games of the first-person variety. 

A maze consists of rectangular cells separated by edges. The edges may be either transparent or opaque. The viewer is supposed to see through transparent edges into the neighboring cells, and they should not see through opaque edges. Each edge is assigned a color (which is meaningless for transparent edges).

The maze is described as a 2D structure assumed to lie in the XY plane. To make it 3D, each edge is extruded vertically from the floor to the ceiling. The floor is at z=-1 and the ceiling is at z=1. Each wall should be drawn with its assigned color.

Associated with the maze is a viewer. The viewer has an (x,y,z) location, a viewing direction, and a horizontal field of view. The view direction is measured in degrees of rotation counter-clockwise about the positive z axis. The horizontal field of view is also measured in degrees. For the project, the viewer's z will always be 0.

The maze file format consists of the following information:
	The number of vertices in the maze, nv. Each edge joins two vertices.
	The location of each vertex, specified as it x and y coordinates. The vertices are assumed to be numbered from 0 to nv - 1.
	The number of edges in the maze, ne. Remember, there is an edge between every cell, even if that edge is transparent.
	The data for each edge: the index of its start vertex, the index of its end vertex, the index of the cell to the left, the index of the cell to the right, a 1 if the edge is opaque, or 0 if transparent, and an RGB triple for the color. The left side of an edge is the side that would appear to be on your left if you stood at the start of the edge and looked toward to end. If there is no cell to the left or right, an index of -1 is used. The edges are assumed to be numbered from 0 to ne - 1.
	The number of cells in the maze, nc.
	The data for each cell, which consists of the four indices for the edges of the cell. The indices are given in counter-clockwise order around the cell.
	The view data, consisting of the (x, y, z) viewer location, viewing direction and the horizontal field of view.

project information reference from: http://dgmm.csie.ntust.edu.tw/?ac1=courprojdetail_CG2012F_3&id=5b4177749fb7e&sid=5b41788e92cf4

Images:
![alt text](https://raw.githubusercontent.com/samuel40791765/ExactVisibilityMaze/master/projectimages/pic1.png)
![alt text](https://raw.githubusercontent.com/samuel40791765/ExactVisibilityMaze/master/projectimages/pic2.png)
![alt text](https://raw.githubusercontent.com/samuel40791765/ExactVisibilityMaze/master/projectimages/pic3.png)
