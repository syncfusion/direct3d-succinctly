// ModelReader.h 

#pragma once

#include <Windows.h>
#include <string>
#include "Model.h"

using namespace DirectX;

class ModelReader
{
 // Reads and returns the data from a text file in the current folder
 // this method also returns the size of the file in bytes
 static char* ReadFile(char* filename, int& filesize);
 
 // Methods for reading an int or float from a string
 static float ReadFloat(std::string str, int &start);
 static int ReadInt(std::string str, int &start);

public:
 static Model* ReadModel(ID3D11Device* device, char* filename);
 
 static std::string ReadLine(char* data, int length, int &start);

};