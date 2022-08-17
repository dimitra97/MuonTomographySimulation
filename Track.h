

//a class to store information about the reconstructed tracks

#include "TObject.h"


#ifndef Track_H
#define Track_H

class Track{

 private:
  double slope;
  double intrc;


 public:

  Track(){slope=0; intrc=0;};
  ~Track(){};
  void SetSlope(double s){ slope=s;};
  void SetIntrc(double i){ intrc=i;};
  double GetSlope(){return slope;};
  double GetIntrc(){return intrc;};


};
#endif



