#include"myDisjointSets.h"
#include<queue>
#include<random>
#include<set>
#include<algorithm>
#include <cstdlib>
#include <iostream>

class myMaze :myDisjointSets {
public:
	myMaze(const int m, const int n) :myDisjointSets(m* n), row(m), column(n)
	{
		size=0;
	};
	void buildMaze(vector<pair<int, int>> & broken_walls)
	{
		int com=row*column*4;
		default_random_engine ran(com);
		int range1 =0; int range2=3;
		uniform_int_distribution<int> wallnum(range1, range2);
		while (size!=column*row)
		{
			int a = ran()%(row*column);
			int row1 =a/column;
			int column1 = a%column;
			int b = 0;
			int wall =wallnum(ran);
			if (wall == 0)
			{
				if (row1 == 0)
				{
					continue;
				}
				else if(row1!=0)
				{
					b=(row1-1)*column+column1;
				}
			}
			else if (wall == 1)
			{
				if (column1==column-1)
				{
					continue;
				}
				else if (column1!=column-1)
				{
					b=row1*column+column1+1;
				}

			}
			else if (wall==2)
			{
				if (row1==(row-1))
				{
					continue;
				}
				else if (row1!=(row-1))
				{
					b = (row1+1)*column+column1;
				}
			}
			else
			{
				if (column1==0)
				{
					continue;
				}
				else if (column1!=0)
				{
					b = row1*column+column1-1;
				}
			}
			
			if (find(a)!=find(b))
			{
				unionSets(find(a), find(b));
				broken_walls.push_back({min(a,b),max(a,b)});
				breakwall[a].push_back(b);
				breakwall[b].push_back(a);
				size = getSetSize(find(a));
			}
			else{
				continue;
			}
		}
	}
	void solveMaze(vector<int>& path)
	{
		unordered_map<int, int> p;
		set<int> marked;
		queue<int> room;
		room.push(0);
		int ex=1;
		int limit=row*column-1;
		while (!room.empty()&& ex!=0)
		{
			for (int i=0; i <= room.size()-1; i=i+1)
			{
				int r = room.front();
				room.pop();
				vector<int> joint = breakwall[r];
				for (int j = ex-1; j<=joint.size()-1; j=j+1)
				{
					int next = joint[j];
					if (next == limit)
					{
						path.push_back(limit);
						while (r!=ex-1&&ex!=0)
						{
							path.push_back(r);
							r = p[r];
						}
						path.push_back(r);
						reverse(path.begin(),path.end());
						return;
					}
					else if (!marked.count(next))
					{
						room.push(next);
						marked.insert(next);
						p[next] = r;
					}
				}
			}
		}
	}
private:
	unordered_map<int, vector<int>> breakwall;
	default_random_engine ran;
	uniform_int_distribution<int> wallnum;
	int row;
	int column;
	int size;
};