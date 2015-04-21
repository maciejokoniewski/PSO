#include "../include/PSO/PSO.h"
#include "../include/Defs/PSO_defs.h"
#include <math.h>
#include <random>

using namespace PSON;

/* declarations of functions for PSO class */

//function random draws random numbers from the range 0 to 1 in order to create population of particles
//x is vector of whole population; C is vector which represents one member of population; n is size of population
vecNN PSO::random(int n)
{
    vecNN x;
    vecf C;
    float C1,C2,C3,C4;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    for(int i=0; i<n; i++)
    {

    //creating one member
    C1=dis(gen);
    C2=dis(gen);
    C3=dis(gen);
    C4=dis(gen);
    C.push_back(C1);
    C.push_back(C2);
    C.push_back(C3);
    C.push_back(C4);

    //adding member to population
    x.push_back(C);

    //freeing place for another member
    C.clear();

    }

    return x;
}

//function calculates velocity of each praticle in given iteraion
vecf PSO::velocity(vecf Local_min, vecf Global_min, vecf Position, vecf V)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1);
   vecf n_v;
   float r1,r2;
   float x;
   r1=dis(gen);
   r2=dis(gen);
   for(int i=0; i<4; i++)
   {
       x=V[i]+r1*(Local_min[i]-Position[i])+r2*(Global_min[i]-Position[i]);
       n_v.push_back(x);
   }
    return n_v;
}

vecf PSO::new_position(vecf n_v, vecf Position)
{
    vecf n_p;
    float x;
    for(int i=0; i<4; i++)
    {
        x=Position[i]+n_v[i];
        n_p.push_back(x);
    }

    return n_p;
}

vecf PSO::LocalMin()
{
    vecf L_M;

    return L_M;

}

vecf PSO::GlobalMin()
{
    vecf G_M;

    return G_M;

}
