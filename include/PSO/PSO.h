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
    vecNN position,v,local_min,global_min;

    /* definitions of functions for PSO class */
    vecNN random(int n);
    vecf velocity(vecf Local_min, vecf Global_min, vecf Position, vecf V);
    vecf new_position(vecf n_v, vecf Position);
    vecf LocalMin();
    vecf GlobalMin();

};

#endif // _PSO_
