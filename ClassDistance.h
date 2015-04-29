#ifndef   __CLASS_DISTANCE__
#define   __CLASS_DISTANCE__
/***************
*Author: weiyongbo
*Date:   2015.04.01
*Description: 求类间分离性测度
***************/

#include <vector>
using namespace std;
enum DISTANCE_ERROR{
	DISTANCE_SUCCESS,
	DISTANCE_CLASSNOTFIT,
	DISTANCE_MEMERROR,
	DISTANCE_HAVECENTER,
	DISTANCE_NOCENTER
	};

template <typename T>
class CClassDistance
{
public:
	CClassDistance(void);
	~CClassDistance(void);
	typedef vector<T> Tuple;
	//求欧式距离
	DISTANCE_ERROR GetEucDist(const Tuple &sampleA,const Tuple &sampleB,T &distance );
	//求巴氏距离
	DISTANCE_ERROR GetBhaDist(const Tuple &sampleA,const Tuple &sampleB,T &distance );
	//求欧式距离标准差
	DISTANCE_ERROR GetClassSTDEV(const vector<T> &classA,double &stdEV,const DISTANCE_ERROR err);
	//根据质心，决定当前元组属于哪个簇
	DISTANCE_ERROR EuaCluster(const vector<Tuple> &means,const Tuple& sample,int &label);
	//获得当前簇的质心
	DISTANCE_ERROR GetMeans(const vector<Tuple>& cluster,Tuple &mean);	
	//获得给定簇的平方误差
	DISTANCE_ERROR GetEucVar(const vector<Tuple> &cluster,const Tuple &mean,T &var);
	//求余弦距离
	DISTANCE_ERROR GetCosDist(const Tuple &sampleA,const Tuple &sampleB,T &distance );
	DISTANCE_ERROR CosCluster(const vector<Tuple> &means,const Tuple& sample,int &label);
	DISTANCE_ERROR GetCosVar(const vector<Tuple> &cluster,const Tuple &mean,T &var);
private:
	//类A的数据
	//vector<vector <T>> classA;
	//类B的数据
	//vector<vector <T>> classB;
	//类A的中心
	//vector<T> classACenter;
	//类B的中心
	//vector<T> classBCenter;
	//类A的标准差
	//T classASTDEV;
	//类B的标准差
	//T classBSTDEV;
};
#endif

/*
#include <iostream>  
#include <sstream>  
#include <fstream>  
#include <vector>  
#include <math.h>  
#include <stdlib.h>  
#define k 3//簇的数目  
using namespace std;  
//存放元组的属性信息  
typedef vector<double> Tuple;//存储每条数据记录  

int dataNum;//数据集中数据记录数目  xz
int dimNum;//每条记录的维数  

//计算两个元组间的欧几里距离  
double getDistXY(const Tuple& t1, const Tuple& t2)   
{  
	double sum = 0;  
	for(int i=1; i<=dimNum; ++i)  
	{  
		sum += (t1[i]-t2[i]) * (t1[i]-t2[i]);  
	}  
	return sqrt(sum);  
}  

//根据质心，决定当前元组属于哪个簇  
int clusterOfTuple(Tuple means[],const Tuple& tuple){  
	double dist=getDistXY(means[0],tuple);  
	double tmp;  
	int label=0;//标示属于哪一个簇  
	for(int i=1;i<k;i++){  
		tmp=getDistXY(means[i],tuple);  
		if(tmp<dist) {dist=tmp;label=i;}  
	}  
	return label;     
}  
//获得给定簇集的平方误差  
double getVar(vector<Tuple> clusters[],Tuple means[]){  
	double var = 0;  
	for (int i = 0; i < k; i++)  
	{  
		vector<Tuple> t = clusters[i];  
		for (int j = 0; j< t.size(); j++)  
		{  
			var += getDistXY(t[j],means[i]);  
		}  
	}  
	//cout<<"sum:"<<sum<<endl;  
	return var;  
}  
//获得当前簇的均值（质心）  
Tuple getMeans(const vector<Tuple>& cluster){  

	int num = cluster.size();  
	Tuple t(dimNum+1, 0);  
	for (int i = 0; i < num; i++)  
	{  
		for(int j=1; j<=dimNum; ++j)  
		{  
			t[j] += cluster[i][j];  
		}  
	}  
	for(int j=1; j<=dimNum; ++j)  
		t[j] /= num;  
	return t;  
	//cout<<"sum:"<<sum<<endl;  
}  

void print(const vector<Tuple> clusters[])  
{  
	for(int lable=0; lable<k; lable++)  
	{  
		cout<<"第"<<lable+1<<"个簇："<<endl;  
		vector<Tuple> t = clusters[lable];  
		for(int i=0; i<t.size(); i++)  
		{  
			cout<<i+1<<".(";  
			for(int j=0; j<=dimNum; ++j)  
			{  
				cout<<t[i][j]<<", ";  
			}  
			cout<<")\n";  
		}  
	}  
}  

void KMeans(vector<Tuple>& tuples){  
	vector<Tuple> clusters[k];//k个簇  
	Tuple means[k];//k个中心点  
	int i=0;  
	//一开始随机选取k条记录的值作为k个簇的质心（均值）  
	srand((unsigned int)time(NULL));  
	for(i=0;i<k;){  
		int iToSelect = rand()%tuples.size();  
		if(means[iToSelect].size() == 0)  
		{  
			for(int j=0; j<=dimNum; ++j)  
			{  
				means[i].push_back(tuples[iToSelect][j]);  
			}  
			++i;  
		}  
	}  
	int lable=0;  
	//根据默认的质心给簇赋值  
	for(i=0;i!=tuples.size();++i){  
		lable=clusterOfTuple(means,tuples[i]);  
		clusters[lable].push_back(tuples[i]);  
	}  
	double oldVar=-1;  
	double newVar=getVar(clusters,means);  
	cout<<"初始的的整体误差平方和为："<<newVar<<endl;   
	int t = 0;  
	while(abs(newVar - oldVar) >= 1) //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止  
	{  
		cout<<"第 "<<++t<<" 次迭代开始："<<endl;  
		for (i = 0; i < k; i++) //更新每个簇的中心点  
		{  
			means[i] = getMeans(clusters[i]);  
		}  
		oldVar = newVar;  
		newVar = getVar(clusters,means); //计算新的准则函数值  
		for (i = 0; i < k; i++) //清空每个簇  
		{  
			clusters[i].clear();  
		}  
		//根据新的质心获得新的簇  
		for(i=0; i!=tuples.size(); ++i){  
			lable=clusterOfTuple(means,tuples[i]);  
			clusters[lable].push_back(tuples[i]);  
		}  
		cout<<"此次迭代之后的整体误差平方和为："<<newVar<<endl;   
	}  

	cout<<"The result is:\n";  
	print(clusters);  
}  
int main(){  

	char fname[256];  
	cout<<"请输入存放数据的文件名： ";  
	cin>>fname;  
	cout<<endl<<" 请依次输入: 维数 样本数目"<<endl;  
	cout<<endl<<" 维数dimNum: ";  
	cin>>dimNum;  
	cout<<endl<<" 样本数目dataNum: ";  
	cin>>dataNum;  
	ifstream infile(fname);  
	if(!infile){  
		cout<<"不能打开输入的文件"<<fname<<endl;  
		return 0;  
	}  
	vector<Tuple> tuples;  
	//从文件流中读入数据  
	for(int i=0; i<dataNum && !infile.eof(); ++i)  
	{  
		string str;  
		getline(infile, str);  
		istringstream istr(str);  
		Tuple tuple(dimNum+1, 0);//第一个位置存放记录编号，第2到dimNum+1个位置存放实际元素  
		tuple[0] = i+1;  
		for(int j=1; j<=dimNum; ++j)  
		{  
			istr>>tuple[j];  
		}  
		tuples.push_back(tuple);  
	}  

	cout<<endl<<"开始聚类"<<endl;  
	KMeans(tuples);  
	return 0;  
}  

*/