#include "DataFile.h"
#include <fstream>
using namespace std;

DataFile::DataFile()
{
	recordCount = 0;
}

DataFile::~DataFile()
{
	Clear();
}

void DataFile::AddRecord(string imageFilename, string name, int age)
{
	Image i = LoadImage(imageFilename.c_str());

	Record* r = new Record;
	r->image = i;
	r->name = name;
	r->age = age;

	records.push_back(r);
	recordCount++;
}

DataFile::Record* DataFile::GetRecord(int index)
{
	std::fstream file;
	
	DataFile::Record* item;

	file.open("npc_data.dat", std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		file.seekg(sizeof(DataFile::Record*) * index, std::ios::beg);

		file.read((char*)&item, sizeof(DataFile::Record*));
	}

	file.close();

	return records[index];
}

void DataFile::Save(string filename)
{
	ofstream outfile(filename, ios::binary);

	int recordCount = records.size();
	outfile.write((char*)&recordCount, sizeof(int));

	for (int i = 0; i < recordCount; i++)
	{		
		Color* imgdata = GetImageData(records[i]->image);
				
		int imageSize = sizeof(Color) * records[i]->image.width * records[i]->image.height;
		int nameSize = records[i]->name.length();
		int ageSize = sizeof(int);

		outfile.write((char*)&records[i]->image.width, sizeof(int));
		outfile.write((char*)&records[i]->image.height, sizeof(int));
		
		outfile.write((char*)&nameSize, sizeof(int));
		outfile.write((char*)&ageSize, sizeof(int));

		outfile.write((char*)imgdata, imageSize);
		outfile.write((char*)records[i]->name.c_str(), nameSize);
		outfile.write((char*)&records[i]->age, ageSize);
	}

	outfile.close();
}

void DataFile::Load(string filename)
{
	Clear();

	ifstream infile(filename, ios::binary);

	recordCount = 0;
	infile.read((char*)&recordCount, sizeof(int));

	for (int i = 0; i < recordCount; i++)
	{		
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, format = 0, imageSize = 0;

		//Gets the width and height of an image
		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));

		//Defines the imageSize
		imageSize = sizeof(Color) * width * height;

		//Gets the size of Name and age
		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));

		//Puts the imageSize into imgData to read the pixel count
		char* imgdata = new char[imageSize];
		infile.read(imgdata, imageSize);

		//Loads image
		Image img = LoadImageEx((Color*)imgdata, width, height); 

		//This is where it makes name
		char* name = new char[nameSize + 1]; 
		name[nameSize] = '\0'; //Adds null terminator to end of name

		int age = 0;
				
		infile.read((char*)name, nameSize); //This is where it gets the name from the file
		infile.read((char*)&age, ageSize);


		

		Record* r = new Record();
		r->image = img;
		r->name = string(name);
		r->age = age;
		records.push_back(r);

		delete [] imgdata;
		delete [] name;
	}

	infile.close();
}

void DataFile::Clear()
{
	for (int i = 0; i < records.size(); i++)
	{
		delete records[i];
	}
	records.clear();
	recordCount = 0;
}