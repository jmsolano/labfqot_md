#ifndef _PARTICLES_H_
#define _PARTICLES_H_
#include <vector>
using std::vector;


/* ************************************************************************** */
class Particles {
/* ************************************************************************** */
public:
   Particles(int n,bool allocxprev=false);
/* ************************************************************************** */
   ~Particles(void);
/* ************************************************************************** */
   vector<double> m;
   vector<vector<double> > x,v,a,x_prev;
   inline int N(void) {return nParticles;}
   void ClearAccelerations(void);
   void Force2Accel(void);
/* ************************************************************************** */
protected:
   int nParticles;
   bool allocExtraXSpace;
   Particles(); //this precludes declaration of particles without a number
/* ************************************************************************** */
};
/* ************************************************************************** */


#endif  /* _PARTICLES_H_ */

