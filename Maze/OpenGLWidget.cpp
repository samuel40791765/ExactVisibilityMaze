#include "OpenGLWidget.h"
#include <iostream>
#include "maze.h"
#include <gl\gl.h>
#include <gl\GLU.h>
#include <Vector3.h>
#include<qmatrix4x4.h>
#include<qline.h>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
	top_z = 1.5f;
	but_z = -1;

	QDir dir("Pic");
	if(dir.exists())
		pic_path = "Pic/";
	else
		pic_path = "../x64/Release/Pic/";
}
void OpenGLWidget::initializeGL()
{
	glClearColor(0,0,0,1);
	glEnable(GL_TEXTURE_2D);
	loadTexture2D(pic_path + "grass.png",grass_ID);
	loadTexture2D(pic_path + "sky.png",sky_ID);
}
void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(Maze::maze!=NULL && !Maze::maze->IsEmpty())
	{
		//View 1
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0 , 0 , Maze::w/2 , Maze::h);
		glOrtho (-0.1, Maze::maze->Max_WH +0.1, -0.1 , Maze::maze->Max_WH +0.1, 0 , 10);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Mini_Map();

		//View 2
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(Maze::w/2,0,Maze::w/2,Maze::h);
		//gluPerspective(Maze::maze->player.posFov , 1 , 0.01 , 200);
		glBindTexture(GL_TEXTURE_2D, sky_ID);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0); glVertex2f(-1,0);
		glTexCoord2f(0, 1); glVertex2f(1, 0);
		glTexCoord2f(1, 1); glVertex2f(1, 1);
		glTexCoord2f(1, 0); glVertex2f(-1,1);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, grass_ID);

		glBegin(GL_QUADS);

		glTexCoord2f(0, 0); glVertex2f(-1, 0);
		glTexCoord2f(0, 1); glVertex2f(1, 0);
		glTexCoord2f(1, 1); glVertex2f(1, -1);
		glTexCoord2f(1, 0); glVertex2f(-1, -1);
		glEnd();

		
		glDisable(GL_TEXTURE_2D);


		/*gluLookAt(Maze::maze->player.posX,Maze::maze->player.posZ,Maze::maze->player.posY , 
			Maze::maze->player.posX + cos(degree_change(Maze::maze->player.posDir)),Maze::maze->player.posZ, Maze::maze->player.posY + sin(degree_change(Maze::maze->player.posDir)),
			0.0, -1.0, 0.0);*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Map_3D();
	}
}
void OpenGLWidget::resizeGL(int w,int h)
{
}

//Draw Left Part
void OpenGLWidget::Mini_Map()	
{

	glBegin(GL_LINES);
	
		for(int i = 0 ; i < (int)Maze::maze->edges.size() ; i++)
		{
			glColor3f(Maze::maze->edges[i].r , Maze::maze->edges[i].g , Maze::maze->edges[i].b);
			if(Maze::maze->edges[i].seen)
			{
				glVertex2f(Maze::maze->edges[i].start.x , Maze::maze->edges[i].start.y);
				glVertex2f(Maze::maze->edges[i].end.x , Maze::maze->edges[i].end.y);
			}
		}
		
		float len = 25;
		glColor3f(1,1,1);
		//right
		glVertex2f(Maze::maze->player.posX , Maze::maze->player.posY );
		glVertex2f(Maze::maze->player.posX + len / Maze::maze->Max_WH * cos(degree_change(Maze::maze->player.posDir - Maze::maze->player.posFov / 2)),
			Maze::maze->player.posY + len / Maze::maze->Max_WH * sin(degree_change(Maze::maze->player.posDir - Maze::maze->player.posFov / 2)));

		//left
		glVertex2f(Maze::maze->player.posX , Maze::maze->player.posY );
		glVertex2f(Maze::maze->player.posX + len/Maze::maze->Max_WH * cos(degree_change(Maze::maze->player.posDir+Maze::maze->player.posFov/2)) ,
			Maze::maze->player.posY + len/Maze::maze->Max_WH * sin(degree_change(Maze::maze->player.posDir+Maze::maze->player.posFov/2)));
	glEnd();
}
void OpenGLWidget::Map_3D()
{
	glLoadIdentity();
	// 畫右邊區塊的所有東西
	
	QLineF rightfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, 
		Maze::maze->player.posX + 2 * Maze::maze->Max_WH * cos(degree_change(Maze::maze->player.posDir - Maze::maze->player.posFov / 2)),
		Maze::maze->player.posY + 2 * Maze::maze->Max_WH * sin(degree_change(Maze::maze->player.posDir - Maze::maze->player.posFov / 2)));
	
	QLineF leftfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, 
		Maze::maze->player.posX + 2 * Maze::maze->Max_WH * cos(degree_change(Maze::maze->player.posDir + Maze::maze->player.posFov / 2)),
		Maze::maze->player.posY + 2 * Maze::maze->Max_WH * sin(degree_change(Maze::maze->player.posDir + Maze::maze->player.posFov / 2)));



	for (int i = 0; i < (int)Maze::maze->cells.size(); i++) {
		Cell_Info currentcell = Maze::maze->cells[i];
		int xmin = 9999999, xmax = 0;
		int ymin = 9999999, ymax = 0;
		for (int j = 0; j < 4; j++) {
			if (currentcell.edges[j].start.x < xmin)
				xmin = currentcell.edges[j].start.x;
			if (currentcell.edges[j].end.x < xmin)
				xmin = currentcell.edges[j].end.x;
			if (currentcell.edges[j].start.x > xmax)
				xmax = currentcell.edges[j].start.x;
			if (currentcell.edges[j].end.x > xmax)
				xmax = currentcell.edges[j].end.x;

			if (currentcell.edges[j].start.y < ymin)
				ymin = currentcell.edges[j].start.y;
			if (currentcell.edges[j].end.y < ymin)
				ymin = currentcell.edges[j].end.y;
			if (currentcell.edges[j].start.y > ymax)
				ymax = currentcell.edges[j].start.y;
			if (currentcell.edges[j].end.y > ymax)
				ymax = currentcell.edges[j].end.y;
		}

		if ((Maze::maze->player.posX<xmax && Maze::maze->player.posX>xmin) &&
			(Maze::maze->player.posY<ymax && Maze::maze->player.posY>ymin)) {
			draw_Cell(&Maze::maze->cells[i], leftfrustum, rightfrustum);
		}
	}
	
	for (int i = 0; i < Maze::maze->cells.size(); i++)
		Maze::maze->cells[i].footprint = false;

	//glVertex3f(0, 0, 0);
	//glVertex3f(0,10, 0);
	
	// 畫貼圖 & 算 UV
	
	glDisable(GL_TEXTURE_2D);
}
void OpenGLWidget::loadTexture2D(QString str,GLuint &textureID)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	QImage img(str);
	QImage opengl_grass = QGLWidget::convertToGLFormat(img);
	

	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, opengl_grass.width(), opengl_grass.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,opengl_grass.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);
}
float OpenGLWidget::degree_change(float num)
{
	return num /180 * 3.14159f;
}

void OpenGLWidget::draw_Cell(Cell_Info *C, QLineF leftfrustum, QLineF rightfrustum) {
	C->footprint = true;
	for (int i = 0; i < 4; i++) {

		
			QLineF currentEdge = QLineF(C->edges[i].start.x, C->edges[i].start.y,
				C->edges[i].end.x, C->edges[i].end.y);

			QPointF rightInterPoint;
			QPointF leftInterPoint;
			int rightintersect = rightfrustum.intersect(currentEdge, &rightInterPoint);
			int leftintersect = leftfrustum.intersect(currentEdge, &leftInterPoint);
			bool print = false;
			AllocConsole();
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
			//printf("%.2f %.2f\n",Maze::maze->player.posX, Maze::maze->player.posY);
			
			if (Maze::maze->player.posX<C->edges[i].start.x + 0.001 && Maze::maze->player.posX > C->edges[i].start.x - 0.001)
				Maze::maze->player.posX += 0.01;
			
			//way to see if point is inside frustrum http://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
			//both frustrums have intersections with the edge
			if (leftintersect == 1 && rightintersect == 1) {
				print = true;
				//printf("Edge: %f %f %f %f\n", Maze::maze->edges[i].start.x, Maze::maze->edges[i].start.y,
				//Maze::maze->edges[i].end.x, Maze::maze->edges[i].end.y);
				//break;
			}
			//both frustrums do not have intersections with the edge
			else if (leftintersect != 1 && rightintersect != 1) {

				float area = 0.5 *(-leftfrustum.y2()*rightfrustum.x2() + Maze::maze->player.posY*(-leftfrustum.x2() + rightfrustum.x2()) + Maze::maze->player.posX*(leftfrustum.y2() - rightfrustum.y2()) + leftfrustum.x2()*rightfrustum.y2());
				float s = 1 / (2 * area)*(Maze::maze->player.posY*rightfrustum.x2() - Maze::maze->player.posX*rightfrustum.y2() + (rightfrustum.y2() - Maze::maze->player.posY)*C->edges[i].start.x + (Maze::maze->player.posX - rightfrustum.x2())*C->edges[i].start.y);
				float t = 1 / (2 * area)*(Maze::maze->player.posX*leftfrustum.y2() - Maze::maze->player.posY*leftfrustum.x2() + (Maze::maze->player.posY - leftfrustum.y2())*C->edges[i].start.x + (leftfrustum.x2() - Maze::maze->player.posX)*C->edges[i].start.y);
				if ((0 <= s && s <= 1.0f) && (0 <= t && t <= 1.0f) && (s + t <= 1.0f)) {
					print = true;
					leftInterPoint = QPointF(C->edges[i].start.x, C->edges[i].start.y);
					rightInterPoint = QPointF(C->edges[i].end.x, C->edges[i].end.y);
				}
				
				

			}
			//only one frustrum has an intersection
			else if ((leftintersect == 1 && rightintersect != 1) || (rightintersect == 1 && leftintersect != 1)) {
				
				//d=(x−x1)(y2−y1)−(y−y1)(x2−x1) point(x,y)
				if (leftintersect == 1) {
					float area = 0.5 *(-leftfrustum.y2()*rightfrustum.x2() + Maze::maze->player.posY*(-leftfrustum.x2() + rightfrustum.x2()) + Maze::maze->player.posX*(leftfrustum.y2() - rightfrustum.y2()) + leftfrustum.x2()*rightfrustum.y2());
					float sstart = 1 / (2 * area)*(Maze::maze->player.posY*rightfrustum.x2() - Maze::maze->player.posX*rightfrustum.y2() + (rightfrustum.y2() - Maze::maze->player.posY)*C->edges[i].start.x + (Maze::maze->player.posX - rightfrustum.x2())*C->edges[i].start.y);
					float tstart = 1 / (2 * area)*(Maze::maze->player.posX*leftfrustum.y2() - Maze::maze->player.posY*leftfrustum.x2() + (Maze::maze->player.posY - leftfrustum.y2())*C->edges[i].start.x + (leftfrustum.x2() - Maze::maze->player.posX)*C->edges[i].start.y);
					float send = 1 / (2 * area)*(Maze::maze->player.posY*rightfrustum.x2() - Maze::maze->player.posX*rightfrustum.y2() + (rightfrustum.y2() - Maze::maze->player.posY)*C->edges[i].end.x + (Maze::maze->player.posX - rightfrustum.x2())*C->edges[i].end.y);
					float tend = 1 / (2 * area)*(Maze::maze->player.posX*leftfrustum.y2() - Maze::maze->player.posY*leftfrustum.x2() + (Maze::maze->player.posY - leftfrustum.y2())*C->edges[i].end.x + (leftfrustum.x2() - Maze::maze->player.posX)*C->edges[i].end.y);
					
					if ((0 <= sstart && sstart <= 1.0f) && (0 <= tstart && tstart <= 1.0f) && (sstart + tstart <= 1.0f)) {
						print = true;
						rightInterPoint = QPointF(C->edges[i].start.x, C->edges[i].start.y);
					}
					if ((0 <= send && send <= 1.0f) && (0 <= tend && tend <= 1.0f) && (send + tend <= 1.0f)) {
						print = true;
						rightInterPoint = QPointF(C->edges[i].end.x, C->edges[i].end.y);
					}


				}
				else if (rightintersect == 1) {
					//leftintersect=
					float area = 0.5 *(-leftfrustum.y2()*rightfrustum.x2() + Maze::maze->player.posY*(-leftfrustum.x2() + rightfrustum.x2()) + Maze::maze->player.posX*(leftfrustum.y2() - rightfrustum.y2()) + leftfrustum.x2()*rightfrustum.y2());
					float sstart = 1 / (2 * area)*(Maze::maze->player.posY*rightfrustum.x2() - Maze::maze->player.posX*rightfrustum.y2() + (rightfrustum.y2() - Maze::maze->player.posY)*C->edges[i].start.x + (Maze::maze->player.posX - rightfrustum.x2())*C->edges[i].start.y);
					float tstart = 1 / (2 * area)*(Maze::maze->player.posX*leftfrustum.y2() - Maze::maze->player.posY*leftfrustum.x2() + (Maze::maze->player.posY - leftfrustum.y2())*C->edges[i].start.x + (leftfrustum.x2() - Maze::maze->player.posX)*C->edges[i].start.y);
					float send = 1 / (2 * area)*(Maze::maze->player.posY*rightfrustum.x2() - Maze::maze->player.posX*rightfrustum.y2() + (rightfrustum.y2() - Maze::maze->player.posY)*C->edges[i].end.x + (Maze::maze->player.posX - rightfrustum.x2())*C->edges[i].end.y);
					float tend = 1 / (2 * area)*(Maze::maze->player.posX*leftfrustum.y2() - Maze::maze->player.posY*leftfrustum.x2() + (Maze::maze->player.posY - leftfrustum.y2())*C->edges[i].end.x + (leftfrustum.x2() - Maze::maze->player.posX)*C->edges[i].end.y);

					if ((0 <= sstart && sstart <= 1.0f) && (0 <= tstart && tstart <= 1.0f) && (sstart + tstart <= 1.0f)) {
						print = true;
						leftInterPoint = QPointF(C->edges[i].start.x, C->edges[i].start.y);
					}
					if ((0 <= send && send <= 1.0f) && (0 <= tend && tend <= 1.0f) && (send + tend <= 1.0f)) {
						print = true;
						leftInterPoint = QPointF(C->edges[i].end.x, C->edges[i].end.y);
					}

				}

			}
			float newSpace[16] = {
				rightInterPoint.y(),1,rightInterPoint.x(),1 ,
				rightInterPoint.y(),-1,rightInterPoint.x(),1 ,
				leftInterPoint.y(),-1,leftInterPoint.x(),1,
				leftInterPoint.y(),1,leftInterPoint.x(),1

			};
			QMatrix4x4 points = QMatrix4x4(newSpace);

			//rotation info credit: http://www.codinglabs.net/article_world_view_projection_matrix.aspx
			QMatrix4x4 rotation;
			QMatrix4x4 translation;
			rotation.setToIdentity();
			translation.setToIdentity();
			rotation.rotate(180, 1, 0, 0);
			translation.translate(-Maze::maze->player.posY, 0, -Maze::maze->player.posX);
			rotation.rotate(Maze::maze->player.posDir, 0, -1, 0);
			QMatrix4x4 camera = rotation*translation;

			float screenspace[4][4];
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					screenspace[i][j] = 0;
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						screenspace[i][j] += camera(j, k) * points(i, k);
					}
				}
			}

			float len = Maze::maze->Max_WH;
			QLineF front = QLineF(Maze::maze->player.posX + len / Maze::maze->Max_WH * cos(degree_change(Maze::maze->player.posDir - Maze::maze->player.posFov / 2)),
				Maze::maze->player.posY + len / Maze::maze->Max_WH * sin(degree_change(Maze::maze->player.posDir - Maze::maze->player.posFov / 2)),
				Maze::maze->player.posX + len / Maze::maze->Max_WH * cos(degree_change(Maze::maze->player.posDir + Maze::maze->player.posFov / 2)),
				Maze::maze->player.posY + len / Maze::maze->Max_WH * sin(degree_change(Maze::maze->player.posDir + Maze::maze->player.posFov / 2))
			);

			float d = Maze::maze->Max_WH / (float)(5 * 2.0*tan(degree_change(Maze::maze->player.posFov*0.5f)));
			//if (Maze::maze->player.posFov > 90)
			//d *= 2;
			//d = d / (Maze::maze->Max_WH / front.length());
			for (int i = 0; i < 4; i++) {
				screenspace[i][0] *= d / screenspace[i][2];
				screenspace[i][1] *= d / screenspace[i][2];
			}

			if (print && C->edges[i].seen) {
				/*for (int i = 0; i < 4; i++) {
					printf("%.2f %.2f\n", screenspace[i][0], screenspace[i][1]);
				}*/
				float r, g, b;
				r = C->edges[i].r;	g = C->edges[i].g, b = C->edges[i].b;
				if (Maze::maze->grayscale) {
					r = 0.3f*r + 0.59f*g + 0.11*b;
					g = r;
					b = r;
				}
				if (Maze::maze->invertcolors) {
					r = 1.0f - r;
					g = 1.0f - g;
					b = 1.0 - b;
				}
					
				glBegin(GL_QUADS);
				glColor3f(r, g, b);
				glVertex2f(screenspace[0][0], screenspace[0][1]);
				glVertex2f(screenspace[1][0], screenspace[1][1]);
				if ((screenspace[1][0] > 0 && screenspace[2][0] < 0) && (screenspace[1][1] < 0 && screenspace[2][1] > 0)) {
					glVertex2f(screenspace[3][0], screenspace[3][1]);
					glVertex2f(screenspace[2][0], screenspace[2][1]);

				}
				else {
					glVertex2f(screenspace[2][0], screenspace[2][1]);
					glVertex2f(screenspace[3][0], screenspace[3][1]);
				}


				glEnd();
			}
			else if (!print) {
				//Getting rid of the walls that aren't inside the frustrum
			}
			else if(!C->edges[i].seen ){
				if (C->edges[i].cellindexl != -1) {
					if (!Maze::maze->cells[C->edges[i].cellindexl].footprint) {
						if ((rightintersect != 1 && leftintersect != 1) || (rightintersect == 1 && leftintersect == 1)) {
							
							QLineF newrightfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, rightInterPoint.x() + 0.00001f, rightInterPoint.y() + 0.00001f);
							newrightfrustum.setLength(newrightfrustum.length() * 10000);
							QLineF newleftfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, leftInterPoint.x() + 0.00001f, leftInterPoint.y() + 0.00001f);
							newleftfrustum.setLength(newleftfrustum.length() * 10000);
							draw_Cell(&Maze::maze->cells[C->edges[i].cellindexl], newleftfrustum, newrightfrustum);
						}
						else if ((rightintersect == 1 || leftintersect == 1)) {
							if (rightintersect == 1) {
								QLineF newleftfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY,leftInterPoint.x() + 0.00001f,leftInterPoint.y() + 0.00001f);
								newleftfrustum.setLength(newleftfrustum.length() * 10000);
								draw_Cell(&Maze::maze->cells[C->edges[i].cellindexl], newleftfrustum, rightfrustum);
							}
							else if (leftintersect == 1) {
								QLineF newrightfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, rightInterPoint.x() + 0.00001f, rightInterPoint.y() + 0.00001f);
								newrightfrustum.setLength(newrightfrustum.length() * 10000);
								draw_Cell(&Maze::maze->cells[C->edges[i].cellindexl], leftfrustum, newrightfrustum);
							}
						}
						
					}
				}
				if (C->edges[i].cellindexr != -1) {
					if (!Maze::maze->cells[C->edges[i].cellindexr].footprint) {
						if ((rightintersect != 1 && leftintersect != 1) || (rightintersect == 1 && leftintersect == 1)) {
							QLineF newleftfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, leftInterPoint.x() + 0.00001f,leftInterPoint.y() + 0.00001f);
							newleftfrustum.setLength(newleftfrustum.length() * 10000);
							QLineF newrightfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, rightInterPoint.x() + 0.00001f, rightInterPoint.y() + 0.00001f);
							newrightfrustum.setLength(newrightfrustum.length() * 10000);
							draw_Cell(&Maze::maze->cells[C->edges[i].cellindexr], newleftfrustum,newrightfrustum);
						}
						else if ((rightintersect == 1 || leftintersect == 1)) {
							if (rightintersect == 1) {
								QLineF newleftfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, leftInterPoint.x()+0.00001f, leftInterPoint.y() + 0.00001f);
								newleftfrustum.setLength(newleftfrustum.length() * 10000);
								draw_Cell(&Maze::maze->cells[C->edges[i].cellindexr], newleftfrustum, rightfrustum);
							}
							else if (leftintersect == 1) {
								QLineF newrightfrustum = QLineF(Maze::maze->player.posX, Maze::maze->player.posY, rightInterPoint.x() + 0.00001f, rightInterPoint.y() + 0.00001f);
								newrightfrustum.setLength(newrightfrustum.length() * 10000);
								draw_Cell(&Maze::maze->cells[C->edges[i].cellindexr], leftfrustum, newrightfrustum);
							}
							
						}
						
						
					}
				}
			}


		
	}
}