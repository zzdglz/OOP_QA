#include <cstdio>
#include <iostream>
#include "OptRouter.h"
using namespace std;
const static int X[4] = {1,-1,0,0};
const static int Y[4] = {0,0,1,-1};

bool OptRouter::route(void)
{
	if (this->m_sourceIndex < 0 || this->m_targetIndex < 0 || this->m_row <= 0 || this->m_col <= 0)
		return false;

	this->m_path.clear();

	//initialize the cost of the source grid
	m_grids[this->m_sourceIndex] = 0;

    //maze expansion
	if (mazeSearch())
	{
		mazeBacktrace();
		return true;
	}
	else
		return false;
}
void OptRouter::searchroute(int x,int y)
{
    if (compIndex(x,y) == m_sourceIndex)
    {
        this->m_path.push_back(this->compIndex(x,y));
        printf("Found path: ");
	    for (unsigned i = 0; i < this->m_path.size(); ++ i)
	    {
            int index = this->m_path[i];
            int X, Y;
            this->compXYIndex(index, X, Y);
            printf("[%d,%d] ", X, Y);
        }
        this->allpaths.push_back(this->m_path);
        this->m_path.pop_back();
        std::cout << endl;
        return;
    }
    if(this->compIndex(x,y)!=m_targetIndex)
    {
        while(m_grids[m_path[m_path.size()-1]]<=m_grids[compIndex(x,y)])
        {
            this->m_path.pop_back();
        }
        this->m_path.push_back(this->compIndex(x,y));
    }
    int curCost = m_grids[compIndex(x,y)];
    printf("BackTrace grid [%d,%d] cost %d\n", x, y, curCost);
    for (int i = 0; i < 4; ++ i)
    {
        int newX = x+X[i];
        int newY = y+Y[i];
        if (newY >= 0 && newY < this->m_row && newX < this->m_col)
        {
            int newIndex = this->compIndex(newX, newY);
            if (m_grids[newIndex] + 1 == curCost)
            {
                searchroute(newX,newY);
            }
        }
    }
}
void OptRouter::mazeBacktrace()
{
    this->m_path.push_back(m_targetIndex);
    int x,y;
    this->compXYIndex(m_targetIndex, x, y);
    searchroute(x,y);
}
void OptRouter::countturns()
{
    for(int i=0;i<this->allpaths.size();++i)
    {
        int turnnum=0;
        int index=this->allpaths[i].size();
        for(int j=0;j<index-2;++j)
        {
            int x1,y1;
            this->compXYIndex(this->allpaths[i][j],x1,y1);
            int x2,y2;
            this->compXYIndex(this->allpaths[i][j+2],x2,y2);
            if(x1!=x2 && y1!=y2)
            {
                turnnum++;
            }
        }
        turn.push_back(turnnum);
    }
}
void OptRouter::minturns(){
    countturns();
    int minturn=turn[0];
    int minturnnum=0;
    for(int i=0;i<this->turn.size();++i)
    {
        if(this->turn[i]<minturn)
        {
            minturn=this->turn[i];
            minturnnum=i;
        }
    }
    printf("Found minturns path: ");
    for (unsigned i = 0; i < this->allpaths[minturnnum].size(); ++ i)
	    {
            int index = this->allpaths[minturnnum][i];
            int X, Y;
            this->compXYIndex(index, X, Y);
            printf("[%d,%d] ", X, Y);
        }
    for (unsigned i = 0; i < this->allpaths[minturnnum].size(); ++ i)
	    {
            this->allpaths[minturnnum].clear();
        }
    this->allpaths.clear();
}
