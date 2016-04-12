#ifndef _PARTICLES_CPP_
#define _PARTICLES_CPP_

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include "particles.h"

Particles::Particles() {

}

Particles::Particles(int n,bool allocxprev) {
   nParticles=n;
   allocExtraXSpace=allocxprev;
   x.resize(nParticles);
   for ( int i=0 ; i<nParticles ; ++i ) {x[i].resize(3);}
   v.resize(nParticles);
   for ( int i=0 ; i<nParticles ; ++i ) {v[i].resize(3);}
   a.resize(nParticles);
   for ( int i=0 ; i<nParticles ; ++i ) {a[i].resize(3);}
   if ( allocExtraXSpace ) {
      x_prev.resize(nParticles);
      for ( int i=0 ; i<nParticles ; ++i ) {x_prev[i].resize(3);}
   } else {
      x_prev.clear();   
   }
   m.resize(nParticles);
   for ( int i=0 ; i<nParticles ; ++i ) { m[i]=1.0e0; }
}

Particles::~Particles() {

}

void Particles::ClearAccelerations(void) {
   for ( int i=0 ; i<nParticles ; ++i ) {
      for ( int j=0 ; j<3 ; ++j ) { a[i][j]=0.0e0; }
   }
}

void Particles::Force2Accel(void) {
   for ( int i=0 ; i<nParticles ; ++i ) {
      for ( int j=0 ; j<3 ; ++j ) { a[i][j]/=m[i]; }
   }
}

#endif  /* _PARTICLES_CPP_ */

