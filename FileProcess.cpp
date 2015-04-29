#include "stdafx.h"
#include "FileProcess.h"


FileProcess::FileProcess(void)
{
}


FileProcess::~FileProcess(void)
{
}
/*
void FileProcess::GetPath(string orginPath,int number,PATH_MAP &path)
{
	for ()
	{
	}
}
*/
void FileProcess::ReadTxt(const string &path,double *data,int width,int height)
{
	ifstream file(path);
	if (file.is_open())
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				file>>data[i * width + j];
			}	
		}
	}
	file.close();
}




void FileProcess::WriteTxt(const string &path,double *data,int width,int height)
{
	std::ofstream file(path);
	if (file.is_open())
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				file<<data[i * width + j]<<"   ";
			}	
			file<<std::endl;
		}
	}
	file.close();
}

