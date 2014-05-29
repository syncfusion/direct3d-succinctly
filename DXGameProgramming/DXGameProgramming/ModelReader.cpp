// ModelReader.cpp

#include "pch.h"
#include "ModelReader.h"
#include <fstream>
#include <vector>

using namespace DirectX;

// Reads a 32 bit float from a substring starting from character index &start
float ModelReader::ReadFloat(std::string str, int &start)
{
std::string t;
while(str.data()[start] != ' ' && str.data()[start] != '/' &&
 str.data()[start] != '\n' && start < (int) str.length()) 

 t.push_back(str.data()[start++]);
 
start++;
// Parse to float and return
return (float)atof(t.data());
}

// Reads an int from a substring starting from the character index &start
int ModelReader::ReadInt(std::string str, int &start)
{
std::string t;
while(str.data()[start] != ' ' && str.data()[start] != '/' &&
 str.data()[start] != '\n' && start < (int) str.length())
 t.push_back(str.data()[start++]);

start++;
// Parse to int and return
return atoi(t.data());
}

char* ModelReader::ReadFile(char* filename, int &filesize)
{
filesize = 0;
std::ifstream filestream;

// Open the file for reading
filestream.open(filename, std::ifstream::in);


// If the file could not be opened, return NULL
if(!filestream.is_open()) return NULL; // The file could not be opened

// Find the file's length
filestream.seekg(0, std::ios::end);
filesize = (int) filestream.tellg();

// Allocate space for the file's data in RAM
char* filedata = new char[filesize]; // Throws bad_alloc if there's problems

// Read the data from the file into the array
filestream.seekg(0, std::ios::beg); // Reset the file back to the start
filestream.read(filedata, filesize); // Read the whole file 
filestream.close();

return filedata;
}

Model* ModelReader::ReadModel(ID3D11Device* device, char* filename)
{
// Read the file
int filesize = 0;
char* filedata = ReadFile(filename, filesize);

// Parse the data into vertices and indices
int startPos = 0;
std::string line;

std::vector<float> vertices;
std::vector<int> vertexIndices;
// Vectors for texture coordinates
std::vector<float> textureCoords;
std::vector<int> textureIndices;

// Vectors for normals
std::vector<float> normals;
std::vector<int> normalIndices;


int index; // The index within the line we're reading

while(startPos < filesize) {
 line = ReadLine(filedata, filesize, startPos);
 if(line.data()[0] == 'v' && line.data()[1] == ' ')
  {
  index = 2;
  // Add to vertex buffer
  vertices.push_back(ReadFloat(line, index)); // Read X
  vertices.push_back(ReadFloat(line, index)); // Read Y
  vertices.push_back(ReadFloat(line, index)); // Read Z
  // If there's a "W" it will be ignored
  }
else if(line.data()[0] == 'f' && line.data()[1] == ' ')
 {
 index = 2;
 // Add triangle to index buffer
 for(int i = 0; i < 3; i++)
  {
  // Read position of vertex
  vertexIndices.push_back(ReadInt(line, index));
     // Read the texture coordinate
   textureIndices.push_back(ReadInt(line, index));   
   // Ignore the normals

  
  // Read and ignore the texture and normal indices:
 // ReadInt(line, index);
  //ReadInt(line, index);

   // Read the normal indices
normalIndices.push_back(ReadInt(line, index)); 

  }
   }

 else if(line.data()[0]=='v'&& line.data()[1] == 't' && line.data()[2] == ' ')
  {
  index = 3;
  // Add to texture
  textureCoords.push_back(ReadFloat(line, index)); // Read U  
  textureCoords.push_back(ReadFloat(line, index)); // Read V  
}

 else if(line.data()[0]=='v' && line.data()[1] == 'n' &&
line.data()[2] == ' ')
  {
  index = 3;
  // Add to normals
  normals.push_back(ReadFloat(line, index)); // Read X
  normals.push_back(ReadFloat(line, index)); // Read Y
  normals.push_back(ReadFloat(line, index)); // Read Z
  }

 }

delete[] filedata; // Deallocate the file data

// Subtract one from the vertex indices to change from base 1
// indexing to base 0:
for(int i = 0; i < (int) vertexIndices.size(); i++)
 {
 vertexIndices[i]--;
 textureIndices[i]--;
 normalIndices[i]--; 
 }
 
// Create a collection of Vertex structures from the faces
std::vector<Vertex> verts;
int j = vertexIndices.size();
int qq = vertices.size();
for(int i = 0; i < (int) vertexIndices.size(); i++)
 {
 Vertex v;
 
 // Create a vertex from the referenced positions
 v.position = XMFLOAT3(
  vertices[vertexIndices[i]*3+0],
  vertices[vertexIndices[i]*3+1],
  vertices[vertexIndices[i]*3+2]); 


 // Set the vertex's normals
 v.normal = XMFLOAT3(
  normals[normalIndices[i]*3+0],
  normals[normalIndices[i]*3+1],
  normals[normalIndices[i]*3+2]);



 // Set the vertex's texture coordinates
 v.uv = XMFLOAT2(
  textureCoords[textureIndices[i]*2+0],
  1.0f-textureCoords[textureIndices[i]*2+1]); // Negate V


 //// Specify random colors for our vertices:
 //v.color = XMFLOAT3(
 // (float)(rand()%10) / 10.0f,
 // (float)(rand()%10) / 10.0f,
 //   (float)(rand()%10) / 10.0f
 // );

 verts.push_back(v); // Push to the verts vector
 }

// Create a an array from the verts vector.
// While we're running through the array reverse
// the winding order of the vertices.
Vertex* vertexArray = new Vertex[verts.size()];
for(int i = 0; i < (int) verts.size(); i+=3)
 {
 vertexArray[i] = verts[i+1];
 vertexArray[i+1] = verts[i];
 vertexArray[i+2] = verts[i+2]; 
  }

// Construct the model
Model* model = new Model(device, vertexArray, verts.size());

// Clear the vectors
vertices.clear();
vertexIndices.clear();
verts.clear();
textureCoords.clear();
textureIndices.clear();
normalIndices.clear();
normals.clear();


// Delete the array/s
delete[] vertexArray;

return model; // Return the model
}

// This method reads and returns a single '\n' delimited line
// from the *data array beginning at the index start. It reads
// the line and advances the start index.
std::string ModelReader::ReadLine(char* data, int length, int &start)
{
std::string str;
int index = 0;
while(data[start] != '\n')
 {
 // Ignore whitespace at the start of the string:
 if((data[start] == ' ' || data[start] == '\t') && index == 0)
  {
  start++;
  if(start == length) break;
  else continue;
  }
 
 index = 1;
 str.push_back(data[start++]);
 if(start == length) break;
 }
start++;

return str;
} 