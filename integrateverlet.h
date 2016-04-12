#ifndef _INTEGRATEVERLET_H_
#define _INTEGRATEVERLET_H_
#include <vector>
using std::vector;

/* ************************************************************************** */
class IntegrateVerlet {
/* ************************************************************************** */
public:
   IntegrateVerlet();
   IntegrateVerlet(double step);
   void SetStep(double step);
   void AdvanceStep(vector<vector<double> > &x,vector<vector<double> > &xp,\
         vector<vector<double> > &v,vector<vector<double> > &a);
/* ************************************************************************** */
protected:
   double h,h2,oneOver2h;
   bool isFirstIntegration;
   void IntegrateFirst(vector<vector<double> > &x,vector<vector<double> > &xp,\
         vector<vector<double> > &v);
/* ************************************************************************** */
};
/* ************************************************************************** */


#endif  /* _INTEGRATEVERLET_H_ */

