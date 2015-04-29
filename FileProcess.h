#ifndef __FILE_PROCESS__
#define __FILE_PROCESS__

#include <string>
#include <iostream>
#include <fstream>
#include <map>

using std::string;
using std::ofstream;
using std::ifstream;
using std::map;
using std::make_pair;



class FileProcess
{
public:
	FileProcess(void);
	~FileProcess(void);
//	void GetPath(string orginPath,int start,int end,PATH_MAP &path);
	void ReadTxt(const string &path,double *data,int width,int height);
	void WriteTxt(const string &path,double *data,int width,int height);
	//void BatchProcess();
};

#endif