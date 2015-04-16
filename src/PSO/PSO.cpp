#include "../include/PSO/PSO.h"
#include "../include/Defs/PSO_defs.h"

using namespace PSON;

vecNN PSO::losuj(vecNN x, vecf C)
{
    srand (time(NULL));
    float C1,C2,C3,C4;

    for(int i=0; i<100; i++)
    {

    C1=(float) rand() / (float) (RAND_MAX);
    C2=(float) rand() / (float) (RAND_MAX);
    C3=(float) rand() / (float) (RAND_MAX);
    C4=(float) rand() / (float) (RAND_MAX);
    C.push_back(C1);
    C.push_back(C2);
    C.push_back(C3);
    C.push_back(C4);

    x.push_back(C);

    C.clear();

    }

    return x;
}


