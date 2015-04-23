#include "../include/PSO/PSO.h"
#include "../include/Defs/PSO_defs.h"
#include <math.h>
#include <random>

using namespace PSON;

/* declarations of functions for PSO class */

//function random draws random numbers from the range 0 to 1 in order to create population of particles
//x is vector of whole population; C is vector which represents one member of population; n is size of population
vecd PSO::random()
{

    vecd C;
    double C1,C2,C3,C4;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10, 10);


    //creating one member
    C1=dis(gen);
    C2=dis(gen);
    C3=dis(gen);
    C4=dis(gen);
    C.push_back(C1);
    //C.push_back(C2);
    //C.push_back(C3);
    //C.push_back(C4);


    return C;
}

//function calculates velocity of each praticle in given iteraion
vecd particle::velocity(vecd Local_min, vecd Global_min, vecd Position, vecd V)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 0.5);
   vecd n_v;
   double r1,r2;
   double x;
   r1=dis(gen);
   r2=dis(gen);
   for(int i=0; i<Position.size(); i++)
   {
       x=V[i]+r1*(Local_min[i]-Position[i])+r2*(Global_min[i]-Position[i]);
       n_v.push_back(x);
   }
    return n_v;
}

vecd particle::new_position(vecd n_v, vecd Position)
{
    vecd n_p;
    double x;
    for(int i=0; i<Position.size(); i++)
    {
        x=Position[i]+n_v[i];
        n_p.push_back(x);
    }

    return n_p;
}

void particle::move_particle(vecd Local_min, vecd Global_min, vecd Position, vecd V)
{
        this->position.clear();
        this->v.clear();
        vecd v,p;
        v=velocity(Local_min,Global_min,Position,V);
        p=new_position(v,Position);
        this->v=v;
        this->position=p;

}
