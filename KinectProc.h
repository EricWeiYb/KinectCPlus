#ifndef __CKINECT__PROC__
#define __CKINECT__PROC__

#include <math.h>
#include <vector>

#include <iostream>
#include <string>
#include <map>
#include "FileProcess.h"


//ing namespace std;
using std::vector;
using std::ifstream;
using std::cin;
using std::cout;
using std::string;
class CKinectProc:FileProcess
{
public:
	explicit CKinectProc(void);
	~CKinectProc(void);
public:
	typedef map<int,string> PATH_MAP;
	/*
	inline void GetBodyCenter(const vector<vector<double>> &bodyLoc,vector<double> &bodyCenter,const int &size);
	inline void GetAngle(const vector<double> &loc1,const vector<double> &loc2,vector<double> &angle);	
	void SaveData(const vector<vector<double>> &data);
	void BatchAngel(const vector<vector<vector<double>>> &bodyLoc,vector<vector<vector<double>>> &angleData);
	void WriteTxt(const string &path,vector<vector<vector<double>>> &angleData,int width,int height);
	*/
	void GetBodyCenter(double *data,const int height,const int width ,vector<double> &bodyCenter);
	void GetAngle(double *loc1,double *loc2,const int width,vector<double> &angle);
	void BatchAngel(double *data,double *outputData,int height,int width,int channel);
	void BatchProcess(PATH_MAP origin,PATH_MAP process);
private:
	//人体骨骼点个数
	const int skeletonCount;
	//坐标个数
	const int axisCount;
	
};
#endif