#include "../include/PSO/PSO.h"
#include "../include/Defs/PSO_defs.h"
#include <random>

using namespace PSON;

vecNN PSO::losuj(vecNN x, vecf C, int n)
{
    float C1,C2,C3,C4;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    for(int i=0; i<n; i++)
    {

    C1=dis(gen);
    C2=dis(gen);
    C3=dis(gen);
    C4=dis(gen);
    C.push_back(C1);
    C.push_back(C2);
    C.push_back(C3);
    C.push_back(C4);

    x.push_back(C);

    C.clear();

    }

    return x;
}


