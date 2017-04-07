#include "Maze_Map.h"

Maze_Map::Maze_Map(QString filename)
{
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);

		//讀所有的點資訊
		in >> num_vertex;
		cout << "========================================" << endl;
		cout << "Number of Vertex > " << num_vertex <<endl;
		for(int i = 0; i < num_vertex ; i++)
		{
			Vertex_Info temp;
			in>>temp.x>>temp.y;
			vertices.push_back(temp);
			//cout << "Vertex " << i << ": X >\t" << temp.x << "\tY >> " <<temp.y <<endl;
		}
		
		//讀所有的邊資訊
		in >> num_edge;
		cout << "Number of Edge > " << num_edge <<endl;
		int Vs,Ve,Cl,Cr,o;
		for(int i = 0 ; i < num_edge ; i++)
		{
			Edge_Info temp;
			in >> Vs >> Ve >> Cl >> Cr >> o >> temp.r >> temp.g >> temp.b;
			temp.start = vertices [Vs];
			temp.end = vertices [Ve];
			temp.cellindexl = Cl;
			temp.cellindexr = Cr;
			temp.seen = o == 1 ? true : false;
			edges.push_back(temp);
		}
				
		//讀所有的cell資訊
		in >> num_cell;
		//Test_Name(QString::number(num_cell,10));
		for (int i = 0; i < num_cell; i++) {
			in >> Vs >> Ve >> Cl >> Cr;
			Cell_Info temp;
			temp.footprint = false;
			temp.edges[0] = edges[Vs];
			temp.edges[1] = edges[Ve];
			temp.edges[2] = edges[Cl];
			temp.edges[3] = edges[Cr];
			cells.push_back(temp);
		}
		//Pos 位置資訊
		in >>  player.posX >> player.posY >> player.posZ >> player.posDir >> player.posFov;
		cout << "Pos Info :" << endl;
		cout << "X: " << player.posX <<" Y: "<< player.posY << " Z: " << player.posZ << " Dir: " << player.posDir << " Fov: " << player.posFov <<endl;

		Max_WH = vertices[num_vertex-1].x > vertices[num_vertex-1].y ?
			vertices[num_vertex-1].x :
			vertices[num_vertex-1].y;
		cout << "Max W or H=> " << Max_WH << endl;
		cout << "========================================" << endl;

		file.close();
	}
}
void Maze_Map::Test_Name(QString str)
{
	msgBox.setText(str);
	msgBox.exec();
}
bool Maze_Map::IsEmpty()
{
	if ((int)vertices.size() == 0 || (int)edges.size() == 0)
		return true;
	else
		return false;
}