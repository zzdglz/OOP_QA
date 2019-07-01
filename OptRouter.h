//////////////////////////////////////////////////////////////////////////
// Description: this is the base implementation of a simple maze router
// Author: Œ‚∆æ∑… 
// Date: 20190524
// Note: Modify this file and add OptRouter.cpp file for the
//       implementation of the additional functionalities
//////////////////////////////////////////////////////////////////////////
#ifndef OPT_ROUTER_H_
#define OPT_ROUTER_H_
#include "BaseRouter.h"

class OptRouter:public BaseRouter
{
private:
    vector <int> turn;
    vector < vector<int> > allpaths;
public:
    OptRouter(int r, int c, const Point &source, const Point &target, const PointVector &obs)
        : BaseRouter(r, c, source, target, obs)
    {;
    }
	~OptRouter() {;}
	bool route(void);
    void searchroute(int,int);
	void mazeBacktrace();
	void countturns();
	void minturns();
};

#endif
