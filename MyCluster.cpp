#include "stdafx.h"
#include "MyCluster.h"


template <typename T>
CMyCluster <typename T>::CMyCluster(void)
{
}

template <typename T>
CMyCluster <typename T>::~CMyCluster(void)
{
}



template <typename T>
void CMyCluster <typename T>:: ConvertData(PATH_MAP mapPath,ALLDATA &cluster,int height,int width,int clusterNO)
{
	FileProcess filePro;
	BODYVEC bodyTmp;
	CLUSTER clusterTmp;
	double *data = new double[3*800];
	for (int i = 0; i != clusterNO; ++i)
	{
		filePro.ReadTxt(mapPath.find(i)->second,data,3,800);
		for (int j = 0; j != height; ++j)
		{
			for (int k = 0; k != width; ++k)
			{
				bodyTmp.push_back(data[j*width + k]);
			}
			clusterTmp.push_back(bodyTmp);
			bodyTmp.clear();
		}
		cluster.push_back(clusterTmp);
		clusterTmp.clear();
	}
}



template <typename T>
void CMyCluster <typename T>:: KMeans(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k)
{
	if (cluster.size() != k)
	{
		return -1;
	}
	//vector<vector<Tuple>> clusterTmp;

	//初始化中心为k类的第一个样本
	for (int i = 0;i < k;++i)
	{
		vector<Tuple> temp;
		means.push_back(cluster[i][0]);
		temp.push_back(cluster[i][0]);
		//clusterTmp.push_back(temp);
	}

	
	T oldVal(0);
	KMeansVal(cluster,means,k,oldVal);
	double newVal(0);
	while (abs(oldVal - newVal) != 0)
	{
		oldVal = newVal;
		KMeansRelocation(cluster,means,k);

		KMeansVal(cluster,means,k,newVal);
		cout<<"修正率:"<<abs(oldVal - newVal)<<"   "<<"当前方差:"<<newVal<<endl;
	}
}


template <typename T>
void CMyCluster <typename T>:: KMeansRelocation(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k,DISTANCEFUN disanceFun)
{
	vector<vector<Tuple>> clusterTmp;
	//初始化中心为k类的第一个样本
	for (int i = 0;i < k;++i)
	{
		vector<Tuple> temp;
		temp.push_back(means[i]);
		clusterTmp.push_back(temp);
	}
	int label(-1);
	//重新分配样本位置
	for (int i = 0;i < cluster.size(); ++i)
	{
		for(int j = 0;j < cluster[i].size();++j)
		{
			switch (disanceFun)
			{
			case DIS_COS:
				CosCluster(means,cluster[i][j],label);
				//clusterTmp[label].push_back(cluster[i][j]);
				break;
			case DIS_EUA:
				EuaCluster(means,cluster[i][j],label);
				//clusterTmp[label].push_back(cluster[i][j]);
			default:
				break;
			}
			clusterTmp[label].push_back(cluster[i][j]);		
		}
		cluster[i].clear();
	}
	//剔除初始化的第一个样本
	for (int i = 0;i < k;++i)
	{
		clusterTmp[i].erase(clusterTmp[i].begin());
	}
	cluster = clusterTmp;
}



template <typename T>
void CMyCluster <typename T>::KMeansVal(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k,T &val,DISTANCEFUN disanceFun)
{
	val = 0;
	for (int i = 0; i != k; ++i)
	{
		T valTmp(0);
		switch (disanceFun)
		{
		case DIS_COS:
			GetCosVar(cluster[i],means[i],valTmp);
			break;
		case DIS_EUA:
			GetEucVar(cluster[i],means[i],valTmp);
			break;
		default:
			break;
		}	
		val += valTmp;
	}
}



template <typename T>
void CMyCluster <typename T>::KMeansMean(vector<vector<Tuple>> &cluster,vector<Tuple> &means,const int k)
{
	for (int i = 0; i != k; ++i)
	{
		GetMeans(cluster[i],means[i]);
	}
}




/*
template <typename T>
void CMyCluster <typename T>:: KMeansRelocation(T* data,ALLDATA clusters,int k)
{
	vector<vector<Tuple>> clusterTmp;
	//初始化中心为k类的第一个样本
	for (int i = 0;i < k;++i)
	{
		vector<Tuple> temp;
		temp.push_back(means[i]);
		clusterTmp.push_back(temp);
	}
	int label(-1);
	//重新分配样本位置
	for (int i = 0;i < cluster.size(); ++i)
	{
		for(int j = 0;j < cluster[i].size();++j)
		{
			switch (disanceFun)
			{
			case DIS_COS:
				CosCluster(means,cluster[i][j],label);
				//clusterTmp[label].push_back(cluster[i][j]);
				break;
			case DIS_EUA:
				EuaCluster(means,cluster[i][j],label);
				//clusterTmp[label].push_back(cluster[i][j]);
			default:
				break;
			}
			clusterTmp[label].push_back(cluster[i][j]);		
		}
		cluster[i].clear();
	}
	//剔除初始化的第一个样本
	for (int i = 0;i < k;++i)
	{
		clusterTmp[i].erase(clusterTmp[i].begin());
	}
	cluster = clusterTmp;
}

*/