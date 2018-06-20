/*Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
*/


#include <iostream>
#include <string>
#include <cmath>
#include "Group.h"
#include "Sphere.h"
#include "getopt.h"
#include "Scene.h"
#include "Ray.h"
#include "Hit.h"
#include "glm/gtx/string_cast.hpp"
#include "Material.h"
#include "RGBcolor.h"
#include "ViewPlane.h"

using namespace std;

#define PI 3.14159265

Scene *gTheScene;
string gProgramName;

void usage( string message = "" ){
	cerr << message << endl;
	cerr << gProgramName << " -i <inputfile> -o <outputfile> -d <depthfile>" << endl;
	cerr << "          -or-" << endl;
	cerr << gProgramName << " --input <inputfile> --output <outputfile> --depth <depthfile>" << endl;
	
}


std::ostream& operator <<( std::ostream &out, const Pixel &p ){
  p.write( out );
  return( out );
}

void parseCommandLine( int argc, char **argv ){
	int ch;
	string inputFile( "" ), outputFile( "" ), depthFile( "" );
  int resolution;
	static struct option longopts[] = {
    { "input", required_argument, NULL, 'i' },
    { "output", required_argument, NULL, 'o' },
    { "depth", required_argument, NULL, 'd' },
    { "resolution", required_argument, NULL, 'r' },
    { "verbose", required_argument, NULL, 'v' },
    { "help", required_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
	};

	while( (ch = getopt_long(argc, argv, "i:o:d:r:vh", longopts, NULL)) != -1 ){
		switch( ch ){
			case 'i':
				// input file
				inputFile = string(optarg);
				break;
			case 'o':
				// image output file
				outputFile = string(optarg);
				break;
			case 'd':
				// depth output file
				depthFile = string( optarg );
				break;
			case 'r':
        resolution = atoi(optarg);
        break;
      case 'v':
        // set your flag here.
        break;
      case 'h':
        usage( );
        break;
			default:
				// do nothing
				break;
		}
	}
	gTheScene = new Scene( inputFile, outputFile, depthFile );
}

vector<Ray> rayFactory(const Camera& cam, const ViewPlane & myViewPlane, const Group& g){
    vector<Ray> v;
    float width = myViewPlane._width;
    float height = myViewPlane._height;
    float pixelSize = myViewPlane._pixelSize;
    // The starting point is in camera
    /*
    glm::vec3 _up = normalize(cam._up);
    glm::vec3 _gaze =  normalize(cam._direction);
    glm::vec3 _right = cross(_up, _gaze);
    */
    // The starting point is in camera
    //cam + up *1/2 height -right*1/2width
    //glm::vec3 startPT = cam._center + (((height/2.0f))* _up) - (((width/2.0f))*_right);//cam._center + (((height/2.0f) + (pixelSize/2.0f))* _up) - (((width/2.0f) - (pixelSize/2.0f))*_right);
    float rads = cam._fovY * (PI / 180.0f);
    float adj = 0.5f * height / tan(rads);

    glm::vec3 startPT = glm::vec3(
        cam._center.x - (width/2.0) + (pixelSize/2.0) , 
        cam._center.y + (height/2.0) - (pixelSize/2.0),
        cam._center.z - adj
        );
    /*
    glm::vec3 startPT = glm::vec3(
        cam._center.x - (width/2.0) + (pixelSize/2.0) , 
        cam._center.y + (height/2.0) - (pixelSize/2.0),
        cam._center.z
        );
    */
    cerr << "FovY:" << cam._fovY << endl;
    cerr << "adj:" << adj << endl;
    cerr << "startPT: "<< glm::to_string(startPT) << endl;
    for (float i = 0; i < myViewPlane.pixelWidth( ); i++){
        for (float j = 0; j < myViewPlane.pixelHeight( ); j++){
            glm::vec3 rayOrigin = glm::vec3(
                startPT.x + i*pixelSize,
                startPT.x + j*pixelSize,
                startPT.z
                ); 
            // this is the ray factory now
            Ray r(rayOrigin, normalize(rayOrigin-cam._center), int(trunc(i)), int(trunc(j)));
            //cerr << r << endl;
            //r.write(cerr);
            v.push_back(r);
        }
    }
    return v;
}
float max(float a, float b)
{
    if(a > b)
        return a;
    else if(b >= a)
        return b;
}
float min(float a, float b)
{
    if(a < b)
        return a;
    else if(b <= a)
        return b;
}

glm::vec3 computeLight(Hit h, Camera c)
{
  glm::vec3 lightcolor = glm::vec3(1, 1, 1);
  glm::vec3 myColor = glm::vec3(255, 255, 255);
  glm::vec3 specular = glm::vec3(1, 0, 0);
  float shininess = 0.75;
  float nDotL = dot(h.normal, c._direction);
 // cout << "nDotl" << nDotL << endl;
  glm::vec3 half = normalize(c._direction + c._direction);
  float nDotR = dot(h.normal, half);
  cout << "material: " << h.material[0] << "," << h.material[1] 
  << "," << h.material[2] << endl;
  glm::vec3 lambert = h.material * myColor * nDotR;//(nDotR-1);// * max(nDotL, 0.0);
 // cout << "nDotR" << nDotR << endl;
  
  //glm::vec4 phong = specular * lightcolor * pow(max(nDotR, 0.0), shininess);
  //glm::vec3 phong = specular * lightcolor * pow(max(nDotR, 0.0), shininess);

  myColor = glm::vec3(abs(lambert.x), abs(lambert.y), abs(lambert.z));//glm::vec3(abs(255 - lambert.x), lambert.y, lambert.z);//abs(lambert.x - 1/255)
  glm::vec3 retval = myColor;// + phong;
//cout<< "lambert: " << glm::to_string(lambert) << endl;
  //cout<< "phong: "<<glm::to_string(phong) << endl;
//  cout<<"retval : "<< glm::to_string(retval) << endl;
  return retval;
}


int main( int argc, char **argv ){
	string pathStr;
	gProgramName = argv[0];
	float myIntercept;
        float tvalue;
	Camera myCam;
    ViewPlane myViewPlane;
	glm::vec3 myColor = glm::vec3(0, 0, 0); // color
	glm::vec3 myDiffuseColor = glm::vec3(0, 0, 0);
	Group myGroup;
    Hit myHits;
	Material myMaterial;

	parseCommandLine( argc, argv );
	argc -= optind;
	argv += optind;
	if( gTheScene->hasInputSceneFilePath( ) &&
			gTheScene->hasOutputFilePath( ) &&
			gTheScene->hasDepthFilePath( ) ){
		gTheScene->parse( myCam, myColor, myMaterial, myGroup, myViewPlane);
		cout << *gTheScene << endl;	
        cout << "Pixel size: " << myViewPlane._pixelSize << endl;
        cout << "Pixel Width & Height: " << myViewPlane.pixelWidth( ) << " " 
	<< myViewPlane.pixelHeight( ) << endl;

        vector<Ray> myRays = rayFactory(myCam, myViewPlane, myGroup);

        cout << "Number of rays: " << myRays.size( ) << endl;
        
        int rayCount = 0, hit = 0;
        cout << gTheScene->outputFile().c_str() <<endl;
        PNGImage myImage(gTheScene->outputFile( ).c_str( ), myViewPlane.pixelWidth( ),
	 myViewPlane.pixelHeight( ));
        myImage.grayFill(0);
        for(Ray element : myRays) //check rays 
        {
 	    for(int i = 0; i < myGroup._numObjects; i++) {      
	 //cout << "Intercept: " << myGroup.myObjects[0]->intersect(element, myHits ) << endl;
		    if(myGroup.myObjects[i]->intersect(element, myHits, tvalue ))//should check for each intersect for each object in each ray
		    { //the switch case to choose material based on material index can go here
		//if(myGroup._materialIndex){  
			//(myGroup._materialIndex)   
			cout << "material Index: " << myGroup.myObjects[i]->getMaterialIndex() << endl;           
			myHits.material = myMaterial.myRGBcolors[myGroup.myObjects[i]
			->getMaterialIndex()]->getColor(); //set hit material
		//}
		//else
			//myHits.material = myMaterial.myRGBcolors[1]->getColor();
                myHits.pixel_i = element.getX(); //set pixel
                myHits.pixel_j = element.getY(); //set pixel
                glm::vec3 color = computeLight(myHits, myCam);
		        myImage.setPixel(element.getX( ), element.getY( ),
		color.x, color.y, color.z, 255);
		      //  cout << "Hit!!" <<"t: "<<tvalue<< endl;
		        hit++;
		    }
		}
        }
        cout <<"Ray Count: " << myRays.size( ) <<" hit count: " << hit<<endl;
        myImage.save( );

	}else{
		usage( "You specify an input scene file, an output file and a depth file." );
	}


	return( 0 );
}
