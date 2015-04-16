#include <iostream>
#include "3rdParty/tinyXML/tinyxml2.h"
#include "src/PSO/PSO.cpp"

using namespace std;
using namespace PSON;

main()
{
    try{


    PSO obiekt;
    vecNN x,d;
    vecf C;
    d=obiekt.losuj(x,C);
    for(int i=0; i<100; i++)
    {
        for(int j=0; j<4; j++)
        {
        cout<<d[i][j]<<" ";
        }
    cout<<endl;
    }
        }
    catch(...)
    {

        cout<<"something gone wrong"<<endl;

    }

return 0;
}
