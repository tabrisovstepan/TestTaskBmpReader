#include <iostream>
#include <fstream>
#include <Windows.h>
#include "BitmapReader.h"

int main(int argc, char* argv[])
{	
	if (argc < 2)
	{
		std::cerr << "Missed path to .bmp file!\n";
		return 1;
	}

	std::string path = argv[1];

	bmp::BitmapReader reader;

	try 
	{
		reader.openBMP(path);
		reader.displayBMP();
		reader.closeBMP();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}