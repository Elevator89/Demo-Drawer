#include <fstream>
#include <sstream>
#include "FileUtil.h"

std::string GetFileContents0( const std::string& filename )
{
	std::string text;
	std::ifstream file( filename );

	if( !file.is_open() )
		throw 1;

	std::getline( file, text, '\0' );

	file.close();
	return text;
}

std::string GetFileContents( const std::string& filename )
{
	std::ifstream file;
	file.open(filename);

	std::stringstream contentStream;

	contentStream << file.rdbuf();

	file.close();
	return contentStream.str();
}
