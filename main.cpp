#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <iomanip>
#include "particles.h"
#include "integrateverlet.h"
#include "vanderwallsforce.h"

int main (int argc, char *argv[])
{
   Particles p(20,true);
   IntegrateVerlet integrator(0.0001);
   VanDerWallsForce vdw(p);
   for ( int i=0 ; i<200 ; ++i ) {
      cout << "step: " << std::setw(5) << i << endl;
      p.ClearAccelerations();
      vdw.AddForces();
      p.Force2Accel();
      integrator.AdvanceStep(p.x,p.x_prev,p.v,p.a);
   }
   for ( int i=0 ; i<p.a.size() ; ++i ) {
      cout << "a: " << p.a[i][0] << " " << p.a[i][1] << " " << p.a[i][2] << endl;
   }
   return EXIT_SUCCESS;
}


