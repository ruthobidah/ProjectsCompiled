/* Your Name Here
 * somebody at something dot TLD
 * CS 566
 * September 20XX
 *
 * $Id: Scene.cpp 2075 2010-04-12 08:06:14Z mshafae $
 *
 */

#include "Scene.h"
#include <string>
#include "string.h"
#include <cstring>
#include "Object.h"
#include "Sphere.h"
#include "RGBcolor.h"
#include "ViewPlane.h"
//#include <algorithm>
//#include <vector>
//#include <iterator>

Scene::Scene( string inputFilename, string outputFilename, string depthFilename ) :
	myInputSceneFile( inputFilename ),
	myOutputFile( outputFilename ),
	myDepthFile( depthFilename ),
	myCamera( ),
	myBackgroundColor( 0.0, 0.0, 0.0 ),
	lineNumber(0),
	tokenCount(0),
	length(0),
	i(0),
	j(0)
{
	myNumberOfMaterials = -1;
	materials = NULL;
	myCurrentMaterial = NULL;
	myGroup = NULL;
}

Scene::~Scene( ){
	// Nothing to free.
}

Camera& Scene::camera( ){
	return( myCamera );
}

Pixel& Scene::backgroundColor( ){
	return( myBackgroundColor );
}

int Scene::numberOfMaterials( ){
	return( myNumberOfMaterials );
}

void Scene::setCurrentMaterial( int i ){
	if( i >= myNumberOfMaterials ){
	  throw( "Index out of range" );	
	}else{
		myCurrentMaterial = materials[i];
	}
}

Material* Scene::currentMaterial( ){
	return( myCurrentMaterial );
}

Group* Scene::group( ){
	return( myGroup );
}

string& Scene::inputSceneFile( ){
	return( myInputSceneFile );
}

string& Scene::outputFile( ){
	return( myOutputFile );
}

string& Scene::depthFile( ){
	return( myDepthFile );
}

bool Scene::hasInputSceneFilePath( void ){
	bool ret = true;
	if( myInputSceneFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Scene::hasOutputFilePath( void ){
	bool ret = true;
	if( myOutputFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Scene::hasDepthFilePath( void ){
	bool ret = true;
	if( myDepthFile == "" ){
		ret = false;
	}
	return( ret );
}


void Scene::setInputSceneFile( string file ){
	myInputSceneFile = file;
}

void Scene::setOutputFile( string file ){
	myOutputFile = file;
}

void Scene::setDepthFile( string file ){
	myDepthFile = file;
}

float Scene::parseFloat( ){
	float ret = (float)atof( currentToken );
	return( ret );
}

double Scene::parseDouble( ){
	double ret = (double)atof( currentToken );
	return( ret );
}

int Scene::parseInt( ){
	int ret = atoi( currentToken );
	return( ret );
}

void Scene::checkToken( const char *str, const char *stage  ){
	if( strcmp( currentToken, str ) != 0 ){
		//if( strcmp( currentToken, "Sphere" ) == 0){ break;}
		cerr << stage << " parse error at line " << lineNumber << " token " << tokenCount << ": " << currentToken << endl;
		cerr << "Current line: " << currentLine << endl;
		cerr << "Expected \'" << str << "\'" << endl;
		exit( 1 );
	}
} 

void Scene::parseCamera( Camera &myCam){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.
	float vec[3];
	glm::vec3 center;
	glm::vec3 direction;
	glm::vec3  up;
	float angleInYDirection;
	bool isPerspective;
 	//float width, height;
	nextToken( );
	//checkToken( "OrthographicCamera", "Camera" );
	if(std::strcmp("OrthographicCamera", currentToken) == 0)
	{
		isPerspective = false;
	}
	else if (std::strcmp("PerspectiveCamera", currentToken) == 0)
	{
		isPerspective = true;
	}
	else
	{
		//Throw Error
		checkToken( "OrthographicCamera|PerspectiveCamera", "Camera" );
	}
	nextToken( );
	checkToken( "{", "Camera" );
	nextToken( );
	checkToken( "center", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	center = glm::vec3(vec[0], vec[1], vec[2]); // center

	nextToken( );
	checkToken( "direction", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	direction = glm::vec3(vec[0], vec[1], vec[2]); // direction
	
	nextToken( );
	checkToken( "up", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	up = glm::vec3(vec[0], vec[1], vec[2]); //up

	if(isPerspective)
	{
		nextToken( );
		checkToken( "angleInYDirection", "Camera" );
		nextToken( );
		angleInYDirection = parseFloat( ); // In degrees (convert to Radians)
	}
	/*nextToken( );
	checkToken( "}", "Camera" );
	nextToken( );
	width = parseInt( ); //width

	nextToken( );
	checkToken( "height", "Camera" );
	nextToken( );
	height = parseInt( ); //height */
	
	nextToken( );
	checkToken( "}", "Camera" );
	if(isPerspective)
	{
		Camera p(center, direction, up, angleInYDirection);
		myCam = p;
	}
	else
	{
		Camera c(center, direction, up);
		myCam = c;
	}
	cerr << "isPerspective Value:" << isPerspective << endl;
	cerr << "angleValue:" << angleInYDirection << endl;

}

void Scene::parseViewPlane( ViewPlane & myViewPlane){

	int width, height, sampleCount;
	float pixelsize;

	nextToken( );
	checkToken( "ViewPlane", "ViewPlane" );
	nextToken( );
	checkToken( "{", "ViewPlane" );
	nextToken( );
	checkToken( "width", "ViewPlane" );
	nextToken( );
	width = parseInt( );
	nextToken( );
	checkToken( "height", "ViewPlane" );
	nextToken( );
	height = parseInt( );
	nextToken( );
	checkToken( "pixelsize", "ViewPlane" );
	nextToken( );
	pixelsize = parseFloat( );
	nextToken( );
	checkToken( "sampleCount", "ViewPlane" );
	nextToken( );
	sampleCount = parseInt( );
	nextToken( );
	checkToken( "}", "ViewPlane" );

	ViewPlane v(width, height, pixelsize, sampleCount);
	myViewPlane = v;

}
/*
void Scene::parseLights( ){

	int numLights, constant_attenuation, linear_attenuation, quadratic_attenuation;
	glm::vec3 position;
	glm::vec4 ambientColor, diffuseColor, specularColor;
	float vec[4];

	nextToken( );
  	checkToken( "Lights", "Lights" );
	nextToken( );
  	checkToken( "{", "Lights" );
	nextToken( );
	checkToken( "numLights", "Lights" );
	nextToken( );
	numLights = parseInt( );
	nextToken( );
	checkToken( "PointLight", "Lights" );
	nextToken( );
	checkToken( "{", "Lights" );
	nextToken( );
	checkToken( "position", "Lights" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	position = glm::vec3(vec[0], vec[1], vec[2]);

	nextToken( );
	checkToken( "ambientColor", "Lights" );
	for( int i = 0; i < 4; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	ambientColor = glm::vec4(vec[0], vec[1], vec[2], vec[3]);

	nextToken( );
	checkToken( "diffuseColor", "Lights" );
	for( int i = 0; i < 4; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	diffuseColor = glm::vec4(vec[0], vec[1], vec[2], vec[3]);

	nextToken( );
	checkToken( "specularColor", "Lights" );
	for( int i = 0; i < 4; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	specularColor = glm::vec4(vec[0], vec[1], vec[2], vec[3]);

	nextToken( );
	checkToken( "constant_attenuation", "Lights" );
	nextToken( );
	constant_attenuation = parseInt( );
	nextToken( );
	checkToken( "linear_attenuation", "Lights" );
	nextToken( );
	linear_attenuation = parseInt( );
	nextToken( );
	checkToken( "quadratic_attenuation", "Lights" );
	nextToken( );
	quadratic_attenuation = parseInt( );

	nextToken( );
	checkToken( "}", "Lights" );
	nextToken( );
	checkToken( "}", "Lights" );
}
*/
void Scene::parseBackground(glm::vec3 &myColor){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.	
	float vec[3];
	glm::vec3 color;
	nextToken( );
	checkToken( "Background", "Background" );
	nextToken( );
	checkToken( "{", "Camera" );
	
	nextToken( );
	checkToken( "color", "Background" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	color = glm::vec3(vec[0], vec[1], vec[2]); // color

	nextToken( );
	checkToken( "}", "Background" );
	myColor = color;
}

void Scene::parseMaterials( Material &myMaterial){
	//cerr << "materials not implemented" << endl;
	float vec[3];
	vector<RGBcolor*> myColorContainer;
	glm::vec3 diffuseColor;
	int numMaterials;
	nextToken();
	checkToken("Materials", "Material");
	nextToken();
	checkToken("{", "Material");

	nextToken();
	checkToken("numMaterials", "Material");
	nextToken();
	numMaterials = parseInt( ); //Num Materials

	for(int i = 0; i < numMaterials; i++){
		nextToken();
		checkToken("PhongMaterial", "Material");
		nextToken();
		checkToken("{", "Material");

		nextToken();
		checkToken("diffuseColor", "Material");
		for( int i = 0; i < 3; i++ ){
			nextToken( );
			vec[i] = parseFloat( );//change later
		} 
		diffuseColor = glm::vec3(vec[0], vec[1], vec[2]); //we need to store color in a vector of vector container or array of vecs
		//or alt do some kind of switch case to assign diffuse color based on index & material index
		std::cout << "DiffuseColor: " << diffuseColor[0] << " , " << diffuseColor[1] << " , " << diffuseColor[2] << std::endl;
		myColorContainer.push_back( new RGBcolor (diffuseColor));		
		nextToken();
		checkToken("}", "xMaterial");
	}
	nextToken();
	checkToken("}", "Material");

	//myDiffuseColor = diffuseColor;
	Material m(myColorContainer);//contrainer of objects*
	myMaterial = m;

}

void Scene::parseGroup( Group &myGroup){
	//cerr << "group not implemented" << endl;
	float vec[3];
	glm::vec3 center;
	int numObjects;
	int materialIndex;
	float radius;
	vector<Object*> myObjectContainer;

	nextToken();
	checkToken("Group", "Group");
	nextToken();
	checkToken("{", "Group");

	nextToken();
	checkToken("numObjects", "Group");
	nextToken();
	numObjects = parseInt(); //Num Objects
	std::cout << "numObjects: " << numObjects << std::endl;

	for(int i = 0; i < numObjects; i++){
	nextToken();
	std::cout << "check current token: " << currentToken << std::endl;
	if (strcmp(currentToken, "MaterialIndex") == 0) {	
	checkToken("MaterialIndex", "Group");
	nextToken();
	materialIndex = parseInt(); 
	std::cout << "material Index: " << materialIndex << std::endl;
	nextToken();
	}
	//Material Index

	
	//nextToken();
	checkToken("Sphere", "Group");
	nextToken();
	checkToken("{", "Group");

	nextToken();
	checkToken("center", "Group");
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );//change later
	}
	center = glm::vec3(vec[0], vec[1], vec[2]); // center
	std::cout << "center: " << center[0] << " , " << center[1] << " , " << center[2] << std::endl;

	nextToken();
	checkToken("radius", "Group");
	nextToken();
	radius = parseFloat();  //radius
	std::cout << "radius: " << radius << std::endl;
	myObjectContainer.push_back( new Sphere (radius, center, materialIndex));

	nextToken();
	checkToken("}", "Material");
	}
	nextToken();
	checkToken("}", "Material");

	//myObjectContainer.push_back( new Sphere (radius, center));//. or ->
	Group g( numObjects, materialIndex, myObjectContainer);//contrainer of objects*
	myGroup = g;
}




bool Scene::parse( Camera &myCam, glm::vec3 &myColor, Material &myMaterial, Group &myGroup, ViewPlane & myVP){	//pass constructors by reference
	bool ret = true;
	lineNumber = 0;
	tokenCount = 0;
	
	inputFileStream.open( myInputSceneFile.c_str( ), ios::in );
	if( inputFileStream.fail( ) ){
		cerr << "Error opening \"" << myInputSceneFile << "\" for reading." << endl;
		exit( 1 );
	}
	parseCamera( myCam);  //call cam const
	parseViewPlane( myVP);
	//parseLights( );
	parseBackground( myColor);
	parseMaterials( myMaterial);
	parseGroup( myGroup);

	inputFileStream.close( );
	
	return( ret );
}

bool Scene::areMoreTokens( ){
	bool ret = false;
	if( j < length ){
		ret = true;
	}
	return( ret );
}

void Scene::advance( ){
	if( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
		while( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
			j++;
		}
		i = j;
	}
}
void Scene::nextOnLine( ){
	//advance( );
	while( currentLine[j] != ' ' && currentLine[j] != '\t' && currentLine[j] != '\n' && currentLine[j] != 0 ){
		j++;
	}
	//cout << "ending: " << i <<  ", " << j << endl;
	currentLine[j] = 0;
	int tmp = i;
	if( i != j ){
		while( i <= j ){
			currentToken[i - tmp] = currentLine[i];
			//cout << "copying: " << (i - tmp) <<  ", " << i << endl;
			i++;
		}
		//cerr << lineNumber << ": " << ++tokenCount << ": '" << currentToken << "'" << endl;
	}
	j++;
	i = j;
}

void Scene::nextToken( ){
	if( !inputFileStream.eof( ) ){
		advance( );
		if( areMoreTokens( ) ){
			nextOnLine( );
		}else{
			do{
				inputFileStream.getline( currentLine, sizeof(currentLine) );
				lineNumber++;
				length = strlen( currentLine );
				//cerr << "new line of length: " << length << endl;
			}while( length <= 0 );
			i = 0;
			j = 0;
			advance( );
			//cerr << "Line: " << currentLine << endl;
			if( areMoreTokens( ) ){
				nextOnLine( );
			}
		}
	}
}


void Scene::write( std::ostream &out ) const {
	out << "Input scene file: " << myInputSceneFile << endl;
	out << "Output file: " << myOutputFile << endl;
	out << "Depth file: " << myDepthFile << endl;
	out << "Camera:" << endl;
	// not implemented yet out << myCamera << endl;
	out << "Background Color: " << myBackgroundColor << endl;
	out << "Number of Materials: " << myNumberOfMaterials << endl;
	out << "Materials:" << endl;
	// not implemented yet copy(materials[0], materials[myNumberOfMaterials], ostream_iterator<Material>(out, "\n" );
	out << "Group:" << endl;
	// not implemented yet out << myGroup << endl;
}

std::ostream& operator <<( std::ostream &out, const Scene &s ){
	s.write( out );
	return( out );
}     

