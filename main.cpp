#include <iostream>
#include "3rdParty/tinyXML/tinyxml2.h"
#include "src/PSO/PSO.cpp"
#include <fstream>

using namespace std;
using namespace PSON;

double f_kw(double x, double y);

main(int argc, char *argv[])
{
    try{


    PSO SWARM;
    particle PARTICLE;
    int n = 100 ;
    vecd yg;

    char c0[30],c1[30],c2[30],c3[30];
    tinyxml2::XMLDocument model;
    std::fstream ate_file;
    std::ofstream mean_error_file;
    std::string ate_data;
    vecd mean_error;


    /************* generating path for ate with argv[1] **********************/
    std::string path11;
    std::string part11("cd ../../../PUTSLAM/build/bin; python2 ../../scripts/evaluate_ate.py /home/");
    std::string part12("/Datasets/rgbd_dataset_freiburg1_desk/groundtruth.txt graph_trajectory.res --verbose --scale 1 --save_associations ate_association.res --plot ate.png > ate.res");
    std::string str(argv[1]);
    path11=part11+str+part12;
    const char *path1 = path11.c_str();


    mean_error_file.open("mean_error.res");

    /************* opening fileModel.xml **********************/
    model.LoadFile("../../../PUTSLAM/resources/fileModel.xml");
    if (model.ErrorID())
         std::cout << "unable to load config file.\n";


    tinyxml2::XMLElement* varianceDepth = model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->ToElement();



    /**************************************************************************************************************************/
    for(int i=0; i<n; i++)
    {
    PARTICLE.position=SWARM.random();
    PARTICLE.v=SWARM.random();
    PARTICLE.local_min=PARTICLE.position;
    SWARM.swarm.push_back(PARTICLE);


    /************* converting float position to char and setting attributes to fileModel.xml **********************/
    sprintf(c0, "%f", SWARM.swarm[i].position[0]);
    sprintf(c1, "%f", SWARM.swarm[i].position[1]);
    sprintf(c2, "%f", SWARM.swarm[i].position[2]);
    sprintf(c3, "%f", SWARM.swarm[i].position[3]);
    varianceDepth->SetAttribute("c0", c0);
    varianceDepth->SetAttribute("c1", c1);
    varianceDepth->SetAttribute("c2", c2);
    varianceDepth->SetAttribute("c3", c3);

    /************* saving fileModel.xml **********************/
    model.SaveFile("../../../PUTSLAM/resources/fileModel.xml");
    try
    {
    /************* running PUTSLAM and scripts evaluate_ate.py **************************/
    std::system("cd ../../../PUTSLAM/build/bin; ./demoMatching");
    std::system(path1);

    /************* opening ate.res **********************/
    ate_file.open( "../../../PUTSLAM/build/bin/ate.res", std::ios::in | std::ios::out );
    if(!ate_file.good() == true)
         std::cout << "unable to load ate.res file.\n";


    /********** cuting mean error **********************/
    for(int i=0;i<3;i++)
        getline(ate_file,ate_data);
    ate_data.erase(0,34);
    ate_data.erase(8,10);
    ate_file.close();

    SWARM.swarm[i].y.push_back((double)atof(ate_data.c_str()));
    yg.push_back((double)atof(ate_data.c_str()));
    }
    catch(...)
    {

        SWARM.swarm[i].y.push_back(0.5);
        yg.push_back(0.5);
    }
    }


    double global_min_error[2];
    auto globalp=min_element(yg.begin(),yg.end());
    std::cout<<std::distance(std::begin(yg), globalp)<<std::endl;
    global_min_error[0]=*globalp;
    cout<<global_min_error[0]<<endl;
    global_min_error[1]=10;
    for(int i=0; i<n; i++)
        SWARM.global_min.push_back(SWARM.swarm[distance(std::begin(yg), globalp)].position[i]);
    mean_error_file<<"min_error="<<global_min_error[0]<<" C0="<<SWARM.global_min[0]<<" C1="<<SWARM.global_min[1]<<" C2="<<SWARM.global_min[2]<<" C3="<<SWARM.global_min[3]<<endl;

    int j = 0;
    while(j<10)
    {
        yg.clear();
         for(int i=0; i<n; i++)
           SWARM.swarm[i].move_particle(SWARM.swarm[i].local_min,SWARM.global_min,SWARM.swarm[i].position,SWARM.swarm[i].v);
         for(int i=0; i<n; i++)
         {


             /************* converting float position to char and setting attributes to fileModel.xml **********************/
             sprintf(c0, "%f", SWARM.swarm[i].position[0]);
             sprintf(c1, "%f", SWARM.swarm[i].position[1]);
             sprintf(c2, "%f", SWARM.swarm[i].position[2]);
             sprintf(c3, "%f", SWARM.swarm[i].position[3]);
             varianceDepth->SetAttribute("c0", c0);
             varianceDepth->SetAttribute("c1", c1);
             varianceDepth->SetAttribute("c2", c2);
             varianceDepth->SetAttribute("c3", c3);

             /************* saving fileModel.xml **********************/
             model.SaveFile("../../../PUTSLAM/resources/fileModel.xml");

             try
             {
             /************* running PUTSLAM and scripts evaluate_ate.py **************************/
             std::system("cd ../../../PUTSLAM/build/bin; ./demoMatching");
             std::system(path1);

             /************* opening ate.res **********************/
             ate_file.open( "../../../PUTSLAM/build/bin/ate.res", std::ios::in | std::ios::out );
             if(!ate_file.good() == true)
                  std::cout << "unable to load ate.res file.\n";


             /********** cuting mean error **********************/
             for(int i=0;i<3;i++)
                 getline(ate_file,ate_data);
             ate_data.erase(0,34);
             ate_data.erase(8,10);
             ate_file.close();

             SWARM.swarm[i].y.push_back((double)atof(ate_data.c_str()));
             yg.push_back((double)atof(ate_data.c_str()));
             }
             catch(...)
             {

                 SWARM.swarm[i].y.push_back((double)atof(ate_data.c_str()));
                 yg.push_back((double)atof(ate_data.c_str()));

             }

             if(SWARM.swarm[i].y[j+1] < SWARM.swarm[i].y[j])
            {
                SWARM.swarm[i].local_min = SWARM.swarm[i].position;
            }
            else
                SWARM.swarm[i].y[j+1] = SWARM.swarm[i].y[j];
         }
         globalp=min_element(yg.begin(),yg.end());
         global_min_error[1]=*globalp;
         if(global_min_error[1]<global_min_error[0])
         {
             SWARM.global_min.clear();
             std::swap(global_min_error[1],global_min_error[0]);
             SWARM.global_min.push_back(SWARM.swarm[distance(std::begin(yg), globalp)].position[0]);
             mean_error_file<<"min_error="<<global_min_error[0]<<" C0="<<SWARM.global_min[0]<<" C1="<<SWARM.global_min[1]<<" C2="<<SWARM.global_min[2]<<" C3="<<SWARM.global_min[3]<<endl;


         }

cout<<"global_p= "<<global_min_error[0]<<endl;


j++;
    }
/**************************************************************************************************************************/
    cout<<global_min_error[0]<<endl;
    mean_error_file<<"min_error="<<global_min_error[0]<<" C0="<<SWARM.global_min[0]<<" C1="<<SWARM.global_min[1]<<" C2="<<SWARM.global_min[2]<<" C3="<<SWARM.global_min[3]<<endl;



    }
    catch (const std::exception& ex)
    {

        cout<<"something's gone wrong:"<<endl;
        std::cerr << ex.what() << std::endl;

    }

return 0;
}

double f_kw(double x,double y)
{
    double z;

    z = pow(x, 4)+2*pow(x,3)-40*pow(x,2)+12*x-3+pow(y, 4)+2*pow(y,3)-40*pow(y,2)+12*y-3 ;
    //x^4+2x^3-40x^2+12x-3+ y^4+2y^3-40y^2+12y-3

    return z;
}
