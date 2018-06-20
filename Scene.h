/*Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: Scene.h 2764 2017-12-05 05:35:16Z mshafae $
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Camera.h"
#include "Image.h"
#include "Material.h"
#include "Group.h"
#include "ViewPlane.h"

#ifndef _SCENE_H_
#define _SCENE_H_

using namespace std;

class Scene{
	public:
		Scene( string inputFilename = "", string outputFilename = "", string depthFilename = "" );
		~Scene( );

		// Accessors
		Camera& camera( );
		Pixel& backgroundColor( );
		int numberOfMaterials( );
		void setCurrentMaterial( int i );
		Material* currentMaterial( );
		Group* group( );
		string& inputSceneFile( );
		string& outputFile( );
		string& depthFile( );
		
		void setInputSceneFile( string file );
		void setOutputFile( string file );
		void setDepthFile( string file );

		bool hasInputSceneFilePath( );
		bool hasOutputFilePath( );
		bool hasDepthFilePath( );

		bool parse( Camera &myCam, glm::vec3 &myColor, Material &myMaterial, Group &myGroup, ViewPlane & myViewPlane);

		// I/O
		void write( std::ostream &out ) const;

	private:
		string myInputSceneFile;
		string myOutputFile;
		string myDepthFile;
		Camera myCamera;
		Pixel myBackgroundColor;
		int myNumberOfMaterials;
		Material **materials;
		Material *myCurrentMaterial;
		Group *myGroup;
		ifstream inputFileStream;

		// For parsing
		char currentLine[255];
		char currentToken[255];
		int lineNumber;
		int tokenCount;
    int length;
    int i;
    int j;
		void nextToken( );
		void parseCamera( Camera &myCam);
		void parsePerspectiveCamera( );
		void nextOnLine( );
		bool areMoreTokens( );
		void advance( );
		void checkToken( const char *str, const char *stage  );
		void parseBackground( glm::vec3 &myColor);
		float parseFloat( );
    		double parseDouble( );
		int parseInt( );
		// Finish these...
		void parseMaterials( Material &myMaterial);
		void parseMaterialsNew( );
		void parseGroup( Group &myGroup);
		void parseViewPlane( ViewPlane &myViewPlane);
		//void parseLights( );
		
};

std::ostream& operator <<( std::ostream &out, const Scene &s );


#endif
