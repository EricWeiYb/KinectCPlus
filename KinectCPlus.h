
// KinectCPlus.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKinectCPlusApp:
// �йش����ʵ�֣������ KinectCPlus.cpp
//

class CKinectCPlusApp : public CWinApp
{
public:
	CKinectCPlusApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKinectCPlusApp theApp;