#include <iostream>
#include "3rdParty/tinyXML/tinyxml2.h"
#include "src/PSO/PSO.cpp"
#include <fstream>

using namespace std;
using namespace PSON;

main(int argc, char *argv[])
{
    try{


    PSO obiektPSO;
    char c0[30],c1[30],c2[30],c3[30];
    tinyxml2::XMLDocument model;
    int n = 100;                        //population's quantity
    std::fstream ate_file;
    std::string ate_data;
    float mean_error;


    /************* opennig ate.res **********************/
    ate_file.open( "../../../PUTSLAM/build/bin/ate.res", std::ios::in | std::ios::out );
    if(!ate_file.good() == true)
         std::cout << "unable to load ate.res file.\n";


    /************* opennig fileModel.xml **********************/
    model.LoadFile("../../../PUTSLAM/resources/fileModel.xml");
    if (model.ErrorID())
         std::cout << "unable to load config file.\n";


    tinyxml2::XMLElement* varianceDepth = model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->ToElement();


    /************* generating path for ate with argv[1] **********************/
    std::string path11;
    std::string part11("cd ../../../PUTSLAM/build/bin; python2 ../../scripts/evaluate_ate.py /home/");
    std::string part12("/Datasets/rgbd_dataset_freiburg1_desk/groundtruth.txt graph_trajectory.res --verbose --scale 1 --save_associations ate_association.res --plot ate.png > ate.res");
    std::string str(argv[1]);
    path11=part11+str+part12;
    const char *path1 = path11.c_str();


    /************* generating path for rpe with argv[1] **********************/
    std::string path21;
    std::string part21("cd ../../../PUTSLAM/build/bin; python2 ../../scripts/evaluate_rpe.py /home/");
    std::string part22("/Datasets/rgbd_dataset_freiburg1_desk/groundtruth.txt graph_trajectory.res --verbose --delta_unit 'f' --fixed_delta --plot rpe.png > rpe.res");
    path21=part21+str+part22;
    const char *path2 = path21.c_str();


    /************* random location and velocity **********************/
    obiektPSO.position=obiektPSO.random(n);
    obiektPSO.v=obiektPSO.random(n);


    /************* converting float position to char and setting attributes to fileModel.xml **********************/
    sprintf(c0, "%f", obiektPSO.position[0][0]);
    sprintf(c1, "%f", obiektPSO.position[0][1]);
    sprintf(c2, "%f", obiektPSO.position[0][2]);
    sprintf(c3, "%f", obiektPSO.position[0][3]);
    varianceDepth->SetAttribute("c0", c0);
    varianceDepth->SetAttribute("c1", c1);
    varianceDepth->SetAttribute("c2", c2);
    varianceDepth->SetAttribute("c3", c3);


    /************* saving fileModel.xml **********************/
    model.SaveFile("../../../PUTSLAM/resources/fileModel.xml");


    /************* running PUTSLAM and scripts evaluate_ate.py, evaluate_rpe.py **********************/
    //std::system("cd ../../../PUTSLAM/build/bin; ./demoMatching");
    std::system(path1);
    std::system(path2);


    /********** cuting mean error ande converting to float *************/
    for(int i=0;i<2;i++)
        getline(ate_file,ate_data);
    ate_data.erase(0,34);
    ate_data.erase(8,10);
    mean_error = (float)atof(ate_data.c_str());
    cout<<mean_error<<endl;



/*   const char* C0=model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->Attribute("c0");
    const char* C1=model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->Attribute("c1");
    const char* C2=model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->Attribute("c2");
    const char* C3=model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->Attribute("c3");

    cout<<C0<<endl;
    cout<<C1<<endl;
    cout<<C2<<endl;
    cout<<C3<<endl;
*/
   /* for(int i=0; i<n; i++)
    {
        for(int j=0; j<4; j++)
        {
        cout<<d[i][j]<<" ";
        }
    cout<<endl;
    }*/


        }
    catch (const std::exception& ex)
    {

        cout<<"something's gone wrong:"<<endl;
        std::cerr << ex.what() << std::endl;

    }

return 0;
}
