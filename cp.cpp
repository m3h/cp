#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

ifstream inputFile;
ofstream outputFile;

void setPermissions( const char *inputFileName, const char *outputFileName);
void closeFiles();
void copy();

int main( int argc, char **argv )
{
	if( argc < 3 ) {	// less than two operands
		
		cout << argv[0] << ": invalid options." << endl;
		cout << "Try \'" << argv[0] << " SOURCE DESTINATION..." << endl;

		exit(EXIT_FAILURE);
	}

	inputFile.open( argv[1], ios::in|ios::binary );
	if( !inputFile ) {
		cout << "Error opening \'" << argv[1] << "\'. Does it exist?" << endl;
		closeFiles();

		exit(EXIT_FAILURE);
	}

	// copy to each destination
	for( int i = 2; i < argc; i++ )
	{
		outputFile.open( argv[i], ios::out|ios::binary );
		if( !outputFile ) {
			cout << "Error opening \'" << argv[2] << "\'." << endl;
			closeFiles();

			exit(EXIT_FAILURE);
		}

		copy();
		outputFile.close();
		setPermissions( argv[1], argv[i] );
	}

	
	closeFiles();

	exit(EXIT_SUCCESS);
}

void copy()
{

	char c;

	while( inputFile.get( c ) ) {
		outputFile.put( c );

	};

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
