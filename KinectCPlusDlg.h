
// KinectCPlusDlg.h : ͷ�ļ�
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

// CKinectCPlusDlg �Ի���
class CKinectCPlusDlg : public CDialogEx
{
// ����
public:
	CKinectCPlusDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KINECTCPLUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLoaddata();
};
