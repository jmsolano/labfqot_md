#ifndef _VANDERWALLSFORCE_CPP_
#define _VANDERWALLSFORCE_CPP_

#include <cstdlib>
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include "particles.h"
#include "vanderwallsforce.h"

VanDerWallsForce::VanDerWallsForce(Particles &part) {
   p=&part;
}

void VanDerWallsForce::AddForces(void) {
   int n=p->N();
   for ( int i=0 ; i<n ; ++i ) {
      for ( int j=(i+1) ; j<n ; ++j ) {
         ComputeForce(p->x[i],p->x[j],p->a[i],p->a[j]);
      }
   }
   cout << "Warning: Particle ghosts (periodic boundary conditions)"
      " not considered" << endl;
   cout << "Van der Walls force only valid for He-He interactions." << endl;
}

void VanDerWallsForce::ComputeForce(vector<double> &x1,vector<double> &x2,\
      vector<double> &a1, vector<double> &a2) {
   double r=0.0e0;
   double x12[3];
   for ( int i=0 ; i<3 ; ++i ) {
      x12[i]=(x2[i]-x1[i]);
      r+=(x12[i]*x12[i]);
   }
   r=sqrt(r);
   if ( r<=1.0e-12 ) {
      cout << "Distance between particles too small!" << endl;
      for ( int i=0 ; i<3 ; ++i ) { a1[i]=a2[i]=0.0e0; }
      return;
   }
   double D=8.37891e-06;
   double alpha=-6.12094e00;
   double r0=3.06e00; //in Angstroms
   //*
   double oor=1.0e0/r;
   for ( int i=0 ; i<3 ; ++i ) { x12[i]*=oor; }
   double oor4=1.0e0;
   for ( int i=0 ; i<4 ; ++i ) { oor4*=oor; }
   for ( int i=0 ; i<3 ; ++i ) {
      a1[i]+=x12[i]*oor4;
      a2[i]-=x12[i]*oor4;
   }
   // */
}


#endif  /* _VANDERWALLSFORCE_CPP_ */

