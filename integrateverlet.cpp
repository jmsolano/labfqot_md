#ifndef _INTEGRATEVERLET_CPP_
#define _INTEGRATEVERLET_CPP_

#include <cstdlib>
#include "integrateverlet.h"

IntegrateVerlet::IntegrateVerlet() {
   SetStep(0.001); //default value, just in case!
   isFirstIntegration=true; //ensure to have x previous at iteration 0
}

IntegrateVerlet::IntegrateVerlet(double step) {
   IntegrateVerlet();
   SetStep(step);
}

void IntegrateVerlet::SetStep(double step) {
   h=step;
   h2=h*h;
   oneOver2h=0.5e0/h;
}
void IntegrateVerlet::AdvanceStep(\
      vector<vector<double> > &x,vector<vector<double> > &xp,\
      vector<vector<double> > &v,vector<vector<double> > &a) {
   if ( isFirstIntegration ) {
      IntegrateFirst(x,xp,v);
      isFirstIntegration=false; //only done once!
   }
   int nn=x.size();
   double xtmp;
   for ( int i=0 ; i<nn ; ++i ) {
      for ( int j=0 ; j<3 ; ++j ) {
         xtmp=x[i][j];
         x[i][j]=2.0e0*x[i][j]-xp[i][j]+h2*a[i][j];
         v[i][j]=oneOver2h*(x[i][j]-xp[i][j]);
         xp[i][j]=xtmp;
      }
   }
}

void IntegrateVerlet::IntegrateFirst(vector<vector<double> > &x,\
      vector<vector<double> > &xp,vector<vector<double> > &v) {
   int nn=xp.size();
   for ( int i=0 ; i<nn ; ++i ) {
      for ( int j=0 ; j<3 ; ++j ) {
         xp[i][j]=x[i][j]-v[i][j]*h;
      }
   }
}

#endif  /* _INTEGRATEVERLET_CPP_ */

