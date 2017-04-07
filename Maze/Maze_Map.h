#pragma once
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <iostream>
#include <vector>
using namespace std;
struct Vertex_Info
{
	int x;
	int y;
};
struct Edge_Info{
	Vertex_Info start;
	Vertex_Info end;
	int cellindexl;
	int cellindexr;
	bool seen;
	float r,g,b;
};

struct Cell_Info {
	bool footprint;
	Edge_Info edges[4];
	
};
struct Player_Info{
	float posX,posY,posZ,posDir,posFov;
};
class Maze_Map
{
public:
	Maze_Map(QString);
	void Test_Name(QString);
	bool IsEmpty();

	int Max_WH;
	Player_Info player;
	vector<Vertex_Info> vertices;
	vector<Edge_Info> edges;
	vector<Cell_Info> cells;
	bool invertcolors = false;
	bool grayscale = false;
private:	
	int num_vertex,num_edge,num_cell;	
	QMessageBox msgBox;
};

