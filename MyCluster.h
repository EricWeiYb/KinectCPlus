#ifndef __MY_CLUSTER__
#define __MY_CLUSTER__
#include <vector>
#include <map>
#include <string>
#include "ClassDistance.h"
#include "FileProcess.h"

using namespace std;
enum DISTANCEFUN
{
	DIS_COS,//”‡œ“æ‡¿Î
	DIS_EUA,//≈∑ œæ‡¿Î
};



template <typename T>
class CMyCluster : public CClassDistance<typename T>,public FileProcess
{
public:
	CMyCluster(void);
	~CMyCluster(void);
	typedef map<int,string> PATH_MAP;
	typedef vector<double> AXISVEC;
	typedef vector<double> BODYVEC;
	typedef vector<BODYVEC> CLUSTER;
	typedef vector<CLUSTER> ALLDATA;
public:
	void KMeans(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k);
	void ConvertData(PATH_MAP mapPath,ALLDATA &cluster,int height,int width,int clusterNO);
	//void ReadFile(const string &path,vector<vector<Tuple>> &cluster);
private:
	void KMeansRelocation(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k,DISTANCEFUN disanceFun);
	void KMeansVal(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k,T &val,DISTANCEFUN disanceFun);
	void KMeansMean(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k);
};
#endif


