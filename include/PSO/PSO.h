#ifndef _PSO_h_
#define _PSO_h_
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <cmath>
#include <vector>
#include "../include/Defs/PSO_defs.h"
#include<time.h>

using namespace std;
using namespace PSON;


class particle {
public:
    vecd position,v,local_min,y;
    /* definitions of functions for particle class */
    void move_particle(vecd Local_min, vecd Global_min, vecd Position, vecd V);
    vecd velocity(vecd Local_min, vecd Global_min, vecd Position, vecd V);
    vecd new_position(vecd n_v, vecd Position);

};

class PSO {
public:
    vector<particle> swarm;
    vecd global_min;
    /* definitions of functions for PSO class */
    vecd random();


};


#endif // _PSO_
