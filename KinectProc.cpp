#include "stdafx.h"
#include "KinectProc.h"


CKinectProc::CKinectProc():skeletonCount(20),axisCount(3)
{

}

CKinectProc::~CKinectProc(void)
{
}

void CKinectProc::GetBodyCenter(double *data,const int height,const int width,vector<double> &bodyCenter)
{
	vector<double> bodyTemp(width,0);
	//每个骨骼点
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			bodyTemp[j] += data[i*width + j];
		}
	}
	//求中心
	for (int i = 0;i != width; ++i)
	{
		bodyCenter[i] = (bodyTemp[i]/height);
	}
}


void CKinectProc::GetAngle(double *loc1,double *loc2,const int width,vector<double> &angle)
{
	//检查输入参数
	if (!loc1 || !loc2)
	{
		return ;
	}
	vector<double> loc(width,0);
	double locTemp(0);
	//平方和
	double squareSum(0);
	for (int i = 0; i != width; ++i)
	{
		locTemp = loc1[i] - loc2[i];
		loc[i] = locTemp;
		//求和
		squareSum += (locTemp*locTemp);
	}
	for (int i = 0; i != width; ++i)
	{
		angle[i] = (loc[i]/sqrt(squareSum));
	}

}


void CKinectProc::BatchAngel(double *data,double *outputData,int height,int width,int channel)
{
	int lineWidth = channel * width;
	for (int i = 0; i < height; ++i)
	{
		vector<double> meanVal(channel,0);
		GetBodyCenter(data + i*lineWidth,width,channel,meanVal);
		std::cout<<"BodyNo:"<<i<<".  "<<" body center ok!"<<std::endl;
		for (int j = 0; j < width; ++j)
		{
			vector<double> val(channel,0);
			GetAngle(data + i*lineWidth + j * channel,&meanVal[0],channel,val);
			for (int k = 0; k < channel; ++k)
			{
				outputData[i*lineWidth + j * channel + k] = val[k];
			}
			//val.clear();
		}
		std::cout<<"BodyNo:"<<i<<".  "<<" Angle ok!"<<std::endl;
		//meanVal.clear(); 
	}	
}


void CKinectProc::BatchProcess(PATH_MAP origin,PATH_MAP process)
{
	FileProcess filePro;
	//double *data = new double[800 * 3];
	//double *outData = new double[800 * 3];
	double data[2400]; //= new double[800 * 3];
	double outData[2400]; //= new double[800 * 3];
	for (int i = 1; i <= 6; ++i )
	{		
		filePro.ReadTxt(origin.find(i)->second,data,3,800);
		std::cout<<"No: "<<i<<"read OK!"<<std::endl;
		BatchAngel(data,outData,40,this->skeletonCount,this->axisCount);
		std::cout<<"No: "<<i<<"process OK!"<<std::endl;
		filePro.WriteTxt(process.find(i)->second,outData,3,800);
		std::cout<<"No: "<<i<<"write OK!"<<std::endl;
	}
}


/*
void CKinectProc::GetBodyCenter(const vector<vector<double>> &bodyLoc,vector<double> &bodyCenter,const int &size)
{
	vector<double> bodyTemp(0,size);
	//每个骨骼点
	for (vector<vector<double>>::const_iterator iter = bodyLoc.begin(); iter != bodyLoc.end(); ++iter)
	{
		//double temp(0);
		//每个坐标
		for (vector<double>::const_iterator loc = (*iter).begin(), int i=0; loc != (*iter).end(); ++loc,++i)
		{
			//temp += *loc;
			bodyTemp[i] += *loc;
		}
		//bodyCenter.push_back(temp/size); 
	}
	//求中心
	for (int i = 0;i != size; ++i)
	{
		bodyCenter.push_back(bodyTemp[i]/bodyLoc.size());
	}
}

void CKinectProc::BatchAngel(const vector<vector<vector<double>>> &bodyLoc,vector<vector<vector<double>>> &angleData)
{
	string path = "C:\\Users\\Administrator\\Desktop\\pose_angle1.txt";
	std::ofstream file(path);
	angleData = bodyLoc;
	for (int i = 0; i != bodyLoc.size(); ++i)
	{
		vector<double> bodyCenterTmp;
		//求姿态中心
		GetBodyCenter(bodyLoc[i],bodyCenterTmp,3);
		for (int j = 0; j != bodyLoc[i].size(); ++j)
		{
			vector<double> angle;
			GetAngle(bodyCenterTmp,bodyLoc[i][j],angle);
			angleData[i][j] = angle;

			if (file.is_open())
			{
				for (int k = 0; k != angle.size(); ++k)
				{
					file<<angle[i]<<"   ";
				}
				file<<std::endl;
			}		
		}
	}
	file.close();
}


void CKinectProc::GetAngle(const vector<double> &loc1,const vector<double> &loc2,vector<double> &angle)
{
	int size(0);
	//检查两个参数
	if (loc1.size() != loc2.size())
	{
		return ;
		size = loc1.size();
	}
	vector<double> loc;
	double locTemp(0);
	//平方和
	double squareSum(0);
	for (int i = 0; i != size; ++i)
	{
		locTemp = loc1[i] - loc2[i];
		loc.push_back(locTemp);
		//求和
		squareSum += (locTemp*locTemp);
	}
	for (int i = 0; i != size; ++i)
	{
		angle.push_back(loc[i]/squareSum);
	}
}


void CKinectProc::BatchAngel(const vector<vector<vector<double>>> &bodyLoc,vector<vector<vector<double>>> &angleData)
{
	string path = "C:\\Users\\Administrator\\Desktop\\pose_angle1.txt";
	std::ofstream file(path);
	angleData = bodyLoc;
	for (int i = 0; i != bodyLoc.size(); ++i)
	{
		vector<double> bodyCenterTmp;
		//求姿态中心
		GetBodyCenter(bodyLoc[i],bodyCenterTmp,3);
		for (int j = 0; j != bodyLoc[i].size(); ++j)
		{
			vector<double> angle;
			GetAngle(bodyCenterTmp,bodyLoc[i][j],angle);
			angleData[i][j] = angle;

			if (file.is_open())
			{
				for (int k = 0; k != angle.size(); ++k)
				{
					file<<angle[i]<<"   ";
				}
				file<<std::endl;
			}		
		}
	}
	file.close();
}

*/


/*
void MySqlProcess::ReadTxt(const string &path,double *data,int width,int height)
{
	//double a[800][3];
	ifstream file(path);
	//width = 0;
	//height = 0;
	if (file.is_open())
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j< width; ++j)
			{
				file>>data[i * 3 + j];
				//std::cout<<data[i * 3 + j]<<std::endl;
			}	
		}
	}
	file.close();
}


ifstream file;
if (flag == true)
{
	file.open(path);
}

if (flag ||file.is_open())
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j< width; ++j)
		{
			file>>data[i * 3 + j];
			//std::cout<<data[i * 3 + j]<<std::endl;
		}	
	}
}
file.close();
*/