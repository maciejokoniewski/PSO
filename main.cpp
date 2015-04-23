#include <iostream>
#include "3rdParty/tinyXML/tinyxml2.h"
#include "src/PSO/PSO.cpp"
#include <fstream>

using namespace std;
using namespace PSON;

double f_kw(double x);

main(int argc, char *argv[])
{
    try{


    PSO SWARM;
    particle PARTICLE;
    int n = 100 ;
    vecd yg;

    for(int i=0; i<n; i++)
    {
    PARTICLE.position=SWARM.random();
    PARTICLE.v=SWARM.random();
    PARTICLE.local_min=PARTICLE.position;
    SWARM.swarm.push_back(PARTICLE);

    SWARM.swarm[i].y.push_back(f_kw(SWARM.swarm[i].position[0]));
    yg.push_back(f_kw(SWARM.swarm[i].position[0]));
    }


    double global_min_error[2];
    auto globalp=min_element(yg.begin(),yg.end());
    std::cout<<std::distance(std::begin(yg), globalp)<<std::endl;
    global_min_error[0]=*globalp;
    cout<<global_min_error[0]<<endl;
    global_min_error[1]=1.5;
    SWARM.global_min.push_back(SWARM.swarm[distance(std::begin(yg), globalp)].position[0]);

    int j = 0;
    while(j<2000)
    {
        yg.clear();
         for(int i=0; i<n; i++)
           SWARM.swarm[i].move_particle(SWARM.swarm[i].local_min,SWARM.global_min,SWARM.swarm[i].position,SWARM.swarm[i].v);
         for(int i=0; i<n; i++)
         {

             for(int k=0; k<PARTICLE.position.size(); k++)
              {
                 yg.push_back(f_kw(SWARM.swarm[i].position[k]));
                 SWARM.swarm[i].y.push_back(f_kw(SWARM.swarm[i].position[k]));
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

         }

cout<<"global_p= "<<global_min_error[0]<<" dla j="<<j<<" dla x="<<SWARM.global_min[0]<<endl;
for(int i=0; i<n; i++)
cout<<SWARM.swarm[i].position[0]<<endl;


j++;
    }

    cout<<global_min_error[0]<<"   "<<SWARM.global_min[0]<<endl;


/*    char c0[30],c1[30],c2[30],c3[30];
    tinyxml2::XMLDocument model;
    int n = 100;                        //population's quantity
    std::fstream ate_file;
    std::ofstream mean_error_file;
    std::string ate_data;
    vecd mean_error;

    /************* generating path for ate with argv[1] **********************/
/*    std::string path11;
    std::string part11("cd ../../../PUTSLAM/build/bin; python2 ../../scripts/evaluate_ate.py /home/");
    std::string part12("/Datasets/rgbd_dataset_freiburg1_desk/groundtruth.txt graph_trajectory.res --verbose --scale 1 --save_associations ate_association.res --plot ate.png > ate.res");
    std::string str(argv[1]);
    path11=part11+str+part12;
    const char *path1 = path11.c_str();


    /************* generating path for rpe with argv[1] **********************/
/*    std::string path21;
    std::string part21("cd ../../../PUTSLAM/build/bin; python2 ../../scripts/evaluate_rpe.py /home/");
    std::string part22("/Datasets/rgbd_dataset_freiburg1_desk/groundtruth.txt graph_trajectory.res --verbose --delta_unit 'f' --fixed_delta --plot rpe.png > rpe.res");
    path21=part21+str+part22;
    const char *path2 = path21.c_str();


    mean_error_file.open("mean_error.res");


    /************* opening fileModel.xml **********************/
/*    model.LoadFile("../../../PUTSLAM/resources/fileModel.xml");
    if (model.ErrorID())
         std::cout << "unable to load config file.\n";


    tinyxml2::XMLElement* varianceDepth = model.FirstChildElement( "Model" )->FirstChildElement( "varianceDepth" )->ToElement();



    /************* random location and velocity **********************/
    /*obiektPSO.position=obiektPSO.random(n);
    obiektPSO.v=obiektPSO.random(n);
    obiektPSO.local_min=obiektPSO.position;*/

/*for(int i=0; i<10; i++)
{
    /************* converting float position to char and setting attributes to fileModel.xml **********************/
 /*   sprintf(c0, "%f", 0.002);
    sprintf(c1, "%f", 0.045);
    sprintf(c2, "%f", 0.034);
    sprintf(c3, "%f", 0.0001);
    varianceDepth->SetAttribute("c0", c0);
    varianceDepth->SetAttribute("c1", c1);
    varianceDepth->SetAttribute("c2", c2);
    varianceDepth->SetAttribute("c3", c3);


    /************* saving fileModel.xml **********************/
 /*   model.SaveFile("../../../PUTSLAM/resources/fileModel.xml");


    /************* running PUTSLAM and scripts evaluate_ate.py, evaluate_rpe.py **********************/
/*    std::system("cd ../../../PUTSLAM/build/bin; ./demoMatching");
    std::system(path1);
    //std::system(path2);


    /************* opening ate.res **********************/
/*    ate_file.open( "../../../PUTSLAM/build/bin/ate.res", std::ios::in | std::ios::out );
    if(!ate_file.good() == true)
         std::cout << "unable to load ate.res file.\n";


    /********** cuting mean error ande converting to float *************/
/*    for(int i=0;i<3;i++)
        getline(ate_file,ate_data);
    ate_data.erase(0,34);
    ate_data.erase(8,10);
    mean_error.push_back((float)atof(ate_data.c_str()));
    cout<<mean_error[i]<<endl;
    mean_error_file<<mean_error[i]<<endl;

    ate_file.close();
}
   float global_min_error[2];
   auto globalm=min_element(mean_error.begin(),mean_error.end());
   std::cout<<std::distance(std::begin(mean_error), globalm)<<std::endl;
   global_min_error[0]=*globalm;
   //obiektPSO.global_min.push_back(obiektPSO.position[std::distance(std::begin(mean_error), globalm)]);


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

double f_kw(double x)
{
    double y;

    y = pow(x, 4)+2*pow(x,3)-40*pow(x,2)+12*x-3 ;
    //x^4+2x^3-40x^2+12x-3

    return y;
}
