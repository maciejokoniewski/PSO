#ifndef _PSO_h_
#define _PSO_h_
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <cmath>
#include <vector>
#include "../include/Defs/PSO_defs.h"
#include<time.h>

using namespace std;
using namespace PSON;

class PSO {
public:
    vecNN location,v;

    /* definitions of functions for PSO class */
    vecNN random(int n);
    vecf velocity();


};

#endif // _PSO_
