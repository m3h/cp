#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <vector>
#include <cstring>

using namespace std;

int srcArgNo = 0;
vector<int> destArgNo;

bool optAttributesOnly = false;

ifstream inputFile;
ofstream outputFile;

void setOption( char *option );
void setPermissions( const char *inputFileName, const char *outputFileName);
void closeFiles();
void copy();

int main( int argc, char **argv )
{
	if( argc < 3 ) {	// less than two arguments - must fail

		cout << argv[0] << ": invalid options." << endl;
		cout << "Try \'" << argv[0] << " SOURCE DESTINATION..." << endl;

		exit(EXIT_FAILURE);
	}

	for( int i = 1; i < argc; i++ ) { 	// scan through arguments looking for options
		if( argv[i][0] == '-' ) {
			setOption( argv[i] );
		} else if ( srcArgNo == 0 ) {		// srcArgNo hasn't changed
			srcArgNo = i;
		} else if ( destArgNo.size() == 0 ) {	// srcArgNo has been set,but not destArNo
			destArgNo.push_back(i);
		}
	}

	inputFile.open( argv[srcArgNo], ios::binary );
	if( !inputFile ) {
		cout << "Error opening \'" << argv[1] << "\'. Does it exist?" << endl;
		closeFiles();

		exit(EXIT_FAILURE);
	}

	// copy to each destination
	for( int i = 0; i < destArgNo.size(); i++ )
	{
		outputFile.open( argv[destArgNo[i]], ios::binary );
		if( !outputFile ) {
			cout << "Error opening \'" << argv[destArgNo[i]] << "\'." << endl;
			closeFiles();

			exit(EXIT_FAILURE);
		}

		copy();
		outputFile.close();
		setPermissions( argv[srcArgNo], argv[destArgNo[i]] );
	}

	
	closeFiles();

	exit(EXIT_SUCCESS);
}

void setOption( char *option )
{
	if( strcmp( option, "--attributes-only" ) == 0 ) {

		optAttributesOnly = true;
	}


	return;
}

void copy()
{

	if( optAttributesOnly == false )
	{
		char c;

		while( inputFile.get( c ) ) {
			outputFile.put( c );
		}
	}

}

void setPermissions( const char *inputFileName, const char *outputFileName )
{
	int status = 0;
	struct stat buffer;


	status = stat( inputFileName, &buffer );

	if( status ) {
		cout << "Error getting fileinfo" << endl;
		exit(EXIT_FAILURE); 
	} 


	status = chmod( outputFileName, buffer.st_mode );

	if( status ) {
		cout << "Error writing file permissions" << endl;
		exit(EXIT_FAILURE);
	}

	return;

}

void closeFiles()
{
	inputFile.close();
	outputFile.close();
}
