
// KinectCPlusDlg.h : 头文件
//

#pragma once
#include <mysql.h>
#include "CMysqlProcess.h"
#include "MyCluster.h"
#include "ClassDistance.h"
#include "KinectProc.h"
//#param error(disable:4996)
#pragma comment(lib,"libmysql.lib")
#include <iostream>
using namespace std;

// CKinectCPlusDlg 对话框
class CKinectCPlusDlg : public CDialogEx
{
// 构造
public:
	CKinectCPlusDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KINECTCPLUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLoaddata();
};
