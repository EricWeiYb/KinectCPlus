#include "stdafx.h"
#include "ClassDistance.h"


template <typename T>
CClassDistance <typename T>::CClassDistance(void)
{
}

template <typename T>
CClassDistance <typename T>::~CClassDistance(void)
{
}

/*
template <typename T>
int CClassDistance<typename T>::GetClassCenter(const vector<vector <T>>& classA,vector<T> &center)
{
	if(classA.size() < 1)
	{
		return -1;
	}
	center = classA[0];
	for (vector<vector <T>::iterator i = classA,begin(); i < classA.end(); ++i)
	{		
		for (vector<T>::iterator j = (*i),begin(),int k = 0; j < (*i).end(); ++j,++k)
		{
			center[k] += *j;
		}
	}
	int n = center.size();
	for (vector<T>::iterator i = center.begin(); i < center.end(); ++i)
	{
		(*i) /= n;
	}
	classACenter = center;
	return 1;
}
*/

//计算两个元组间的欧几里距离 
template <typename T> 
DISTANCE_ERROR CClassDistance<typename T>::GetEucDist(const Tuple &sampleA,const Tuple &sampleB,T &distance )
{    
	if ((sampleA.size() != sampleB.size()))
	{
		return DISTANCE_CLASSNOTFIT;
	}
	distance = 0;
	for(int i = 0; i != sampleA.size(); ++i)  
	{  
		distance += ((sampleA[i]-sampleB[i]) * (sampleA[i]-sampleB[i]));  
	}  
	distance = sqrt(distance); 
	return DISTANCE_SUCCESS;
}  

template <typename T> 
DISTANCE_ERROR CClassDistance<typename T>::GetBhaDist(const Tuple &sampleA,const Tuple &sampleB,T &distance )
{    
	if ((sampleA.size() != sampleB.size()))
	{
		return DISTANCE_CLASSNOTFIT;
	}
	distance = 0;
	for(int i = 0; i != sampleA.size(); ++i)  
	{  
		distance += (sampleA[i]*sampleB[i]);  
	}  
	distance = sqrt(distance); 
	return DISTANCE_SUCCESS;
}  



//根据质心，决定当前元组属于哪个簇  
template <typename T>
DISTANCE_ERROR CClassDistance<typename T>::EuaCluster(const vector<Tuple> &means,const Tuple& sample,int &label)
{  
	if (means.size() == 0)
	{
		return DISTANCE_MEMERROR;
	}
	//GetEucDist(means[0],sample,dist);  
	T tmp(0);
	T dist(999999);
	label = 0;//标示属于哪一个簇  
	for(int i = 0;i != means.size();++i)
	{  
		if (DISTANCE_SUCCESS == GetEucDist(means[i],sample,tmp))
		{
			if( tmp < dist) 
			{
				dist = tmp;
				label = i;
			} 
		}
		else
		{
			return DISTANCE_CLASSNOTFIT;
		}
	}
	return DISTANCE_SUCCESS;     
} 


//获得当前簇的均值（质心）
template <typename T>
DISTANCE_ERROR CClassDistance<typename T>::GetMeans(const vector<Tuple>& cluster,Tuple &mean)
{  
	if (cluster.size() <= 0 || cluster[0].size() <= 0)
	{
		return DISTANCE_MEMERROR;
	}
	int num = cluster.size();  
	int dimNum = cluster[0].size();
	Tuple t(dimNum, 0);  
	for (int i = 0; i != num; ++i)  
	{  
		for(int j = 0; j != dimNum; ++j)  
		{  
			t[j] += cluster[i][j];  
		}  
	}  
	for(int j = 0;j < dimNum; ++j)  
	{
		t[j] /= num;  
	}
	mean = t;
	return DISTANCE_SUCCESS;    
}  


//获得给定簇的平方误差
template <typename T>
DISTANCE_ERROR CClassDistance<typename T>::GetEucVar(const vector<Tuple> &cluster,const Tuple &mean,T &var)
{  
	if (cluster.empty())
	{
		return DISTANCE_MEMERROR;
	}
	var = 0;  
	for (int i = 0; i != cluster.size(); ++i)  
	{  
		var += GetEucDist(cluster[i],mean);  
	}
	return DISTANCE_SUCCESS; 
} 


//求余弦距离
template <typename T>
DISTANCE_ERROR CClassDistance<typename T>::GetCosDist(const Tuple &sampleA,const Tuple &sampleB,T &distance )
{
	int size = sampleA.size();
	if (sampleA.size() != sampleB.size())
	{
		return DISTANCE_MEMERROR;
	}
	double temp(0);
	double valSumA(0);
	double valSumB(0);
	for (int i = 0; i != size; ++i)
	{
		temp += (sampleA[i]*sampleB[i]);
		//平方和
		valSumA += (sampleA[i]*sampleA[i]);
		valSumB += (sampleB[i]*sampleB[i]);
	}
	distance = temp/((sqrt(valSumA))*(sqrt(valSumB)));
	return DISTANCE_SUCCESS;
}


//根据质心，决定当前元组属于哪个簇  
template <typename T>
DISTANCE_ERROR CClassDistance<typename T>::CosCluster(const vector<Tuple> &means,const Tuple& sample,int &label)
{  
	if (means.size() == 0)
	{
		return DISTANCE_MEMERROR;
	}
	//GetEucDist(means[0],sample,dist);  
	T tmp(0);
	T dist(-9999);
	label = 0;//标示属于哪一个簇  
	for(int i = 0;i != means.size();++i)
	{  
		if (DISTANCE_SUCCESS == GetCosDist(means[i],sample,tmp))
		{
			if( tmp > dist) 
			{
				dist = tmp;
				label = i;
			} 
		}
		else
		{
			return DISTANCE_CLASSNOTFIT;
		}
	}
	return DISTANCE_SUCCESS;     
} 



//获得给定簇的平方误差
template <typename T>
DISTANCE_ERROR CClassDistance<typename T>::GetCosVar(const vector<Tuple> &cluster,const Tuple &mean,T &var)
{  
	if (cluster.empty())
	{
		return DISTANCE_MEMERROR;
	}
	var = 0;  
	for (int i = 0; i != cluster.size(); ++i)  
	{  
		var += GetCosDist(cluster[i],mean);  
	}
	return DISTANCE_SUCCESS; 
}