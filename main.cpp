#include <iostream>
#include <windows.h>
#include <deque>
#include <ctime>
#include <fstream>
using namespace std;


const int H=500;
const int W=150;
struct Pair
{	
	int first;
	int second;
	Pair(int x,int y)
	{
		first=x;
		second=y;
	}
};
struct GRID
{
	short items[H][W];
};
struct PATH
{
	deque<Pair> XY;
};
void generateMap(GRID&);
inline void printMap(GRID const&);
inline void printPath(PATH const&);
inline void printPath(PATH const&,GRID&);
bool pathExist(GRID,int,int,int,int,PATH&);
int main()
{
	int count=1;
	int mass=0;
	do{
	srand(time(0));
	
	GRID grid;
	PATH path;
	generateMap(grid);
	clock_t t = clock();
	while(!pathExist(grid,1,1,W-2,H-2,path))
	{
		generateMap(grid);
		//printMap(grid);
		++count;
	}
	++mass;
	clock_t tm = clock() - t;
	cout << tm << endl;
	printPath(path,grid);
	cout<<count<<endl;
	//cout<<mass<<endl;
	}while(mass<1);
	//cout<<count/(mass*1.0)<<endl;
	system("pause");
	return 0;
}

void printMap(GRID const& grid)
{
	ofstream file("out.txt");
	for (int i=0;i<H;++i)
	{
		for (int k=0;k<W;++k)
		{
			switch(grid.items[i][k])
			{
			case -1:
				//cout<<'#';
				file << '#';
				break;
			case -2:
				//cout<<' ';
				file << ' ';
				break;
			case -3:
				//cout<<'*';
				file << '*';
				break;
			default:
				//cout<<grid.items[i][k];
				file << grid.items[i][k];
			}
		}
		//cout<<endl;
		file << endl;
	}
}

bool pathExist(GRID grid,int x1,int y1,int x2,int y2,PATH &path)
{
	grid.items[y1][x1]=0;
	int dx[4] = {1, 0, -1, 0};  
    int dy[4] = {0, 1, 0, -1};
	int d, x, y, k;
	bool stop;
	d=0;
	clock_t t = clock();
	do {
		stop=true;
		for( y=1;y<H-1;++y)
			for (x=1;x<W-1;++x)
				if (grid.items[y][x]==d)
				{ 
					for(k=0;k<4;++k)
						if (grid.items[y+dy[k]][x+dx[k]]==-2)
						{
							stop=false;
							grid.items[y+dy[k]][x+dx[k]]=d+1;
						}
				}
		++d;
	}while(!stop&&grid.items[y2][x2]==-2);
	if (grid.items[y2][x2]==-2) return false;
	clock_t tm=clock()-t;
	cout<<tm<<endl;
	printMap(grid);
	int len=grid.items[y2][x2];
	x=x2;
	y=y2;
	d=len;
	while(d>0)
	{
		path.XY.push_front(Pair(x,y));
		--d;
		for(k=0; k<4;++k)
			if (grid.items[y + dy[k]][x + dx[k]] == d)
			{
				x=x+dx[k];
				y=y+dy[k];
				break;
			}
	}
	path.XY.push_front(Pair(x1,y1));
	
	return true;
}

void printPath(PATH const& path)
{
	for (auto i = path.XY.begin(); i < path.XY.end(); ++i)
	{
		cout << '(' << i->first << ',' << i->second << ')' << "->";
		ofstream file("out.txt");
		file << '(' << i->first << ',' << i->second << ')' << "->";
	}

}
void printPath(PATH const& path,GRID& grid)
{
	for (auto i=path.XY.begin();i<path.XY.end();++i)
		grid.items[i->second][i->first]=-3;
	printMap(grid);
}
void generateMap(GRID& grid)
{
	for (int i=0; i<H;++i)
	{
		for (int k=0; k<W;++k)
		{
			if (i*k==0 ||i==H-1 ||k==W-1)
				grid.items[i][k]=-1;
			else
				if(rand()%2==0)
				{
				grid.items[i][k]=-1;
				}
				else
				{
					grid.items[i][k]=-2;
				}
		}
	}
	grid.items[1][1]=-2;
	grid.items[H-2][W-2]=-2;
	return;
}
