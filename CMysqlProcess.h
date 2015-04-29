#ifndef _CMYSQL_PROCESS_H_
#define _CMYSQL_PROCESS_H_
#pragma once

//#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <mysql.h>
#include <fstream>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
//#include "mysql.h"

//using std::map;
//using std::string;
using namespace std;

#define CONNECT_FAILED    -1
#define USE_DB_FAILED     -2
#define EXECUTE_FAILED    -3
#define EMPTY_RECORDSET   -4

#define IMG_MAX_SIZE 1000000


class MySqlProcess
{
public:
	MySqlProcess();
	~MySqlProcess();

	int connect(char *hostAddress, int port, char *username, char *password,  char *DBName);
	int reconnect();
	int close();
	int exec(char *pSql);
	int exec(const string &sql);
	int real_exec(char *pSql, unsigned int length);
	int real_exec(const string &sql, unsigned int length);
	int fetchrow();
	int fetchrow(map<string, string> *row);
	bool isConnected() {return m_bConnected;}
	char *getErrMsg() {return m_errMsg;}
	int getErrNo() {return m_errNo;}
	my_ulonglong getRowNum() {return m_rowNum;}
	unsigned int getFieldNum() {return m_fieldNum;}
	my_ulonglong getAffectedNum() {return m_affectedNum;}
	my_ulonglong getInsertID() {return m_insertID;}
	//
	void ReadTxt(const string &path,double *data,int width,int height);
public:
	MYSQL_ROW m_row;            //��ǰ������һ��
private:
	void my_err(int line);
private:
	char m_hostAddress[64];    //DB Server �ĵ�ַ
	int m_port;                //DB Server port
	char m_username[64];       //�û���
	char m_password[64];       //����
	char m_DBName[64];         //Database ����

	MYSQL m_conn;
	MYSQL_RES *m_pRes;
	bool m_bConnected;                           //�Ƿ������ӵ����ݿ�
	char m_errMsg[256];                          //������Ϣ
	int m_errNo;                                 //mysql������
	my_ulonglong m_rowNum;                       //���һ��ִ��sql��䷵�صļ�¼��
	unsigned int m_fieldNum;                     //���һ��ִ��sql��䷵�ص��ֶ���
	my_ulonglong m_affectedNum;                  //���һ��ִ��sql���Ӱ��ļ�¼����update��insert��replace��delete�ȣ�
	my_ulonglong m_insertID;                     //���һ��ִ��insert��������ID�����û��AUTO_INCREMENT����Ϊ0
	bool m_bHaveResult;                          //��ǰ������RecordSet�Ƿ�Ϊ��
};
#endif