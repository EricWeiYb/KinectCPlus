
// KinectCPlusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KinectCPlus.h"
#include "KinectCPlusDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKinectCPlusDlg 对话框



CKinectCPlusDlg::CKinectCPlusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKinectCPlusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKinectCPlusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKinectCPlusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CKinectCPlusDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOADDATA, &CKinectCPlusDlg::OnBnClickedLoaddata)
END_MESSAGE_MAP()


// CKinectCPlusDlg 消息处理程序

BOOL CKinectCPlusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	AllocConsole();                     // 打开控制台资源
	//freopen_s("CONOUT$", "w+t", stdout );// 申请写
	//freopen_s( "CONIN$", "r+t", stdin );  // 申请读
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKinectCPlusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKinectCPlusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKinectCPlusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKinectCPlusDlg::OnBnClickedOk()
{
	MySqlProcess sqlProcess;
	if (0 == sqlProcess.connect("localhost",3306,"root","1234","KINECTBASE"))
	{
		MessageBox("database connection OK!");
	}
	if (0 == sqlProcess.close())
	{
		MessageBox("database close  OK!");
	}
	CDialogEx::OnOK();
}


void CKinectCPlusDlg::OnBnClickedLoaddata()
{
	// TODO: 在此添加控件通知处理程序代码
	freopen( "CONOUT$", "w+t", stdout );// 申请写
	freopen( "CONIN$", "r+t", stdin );  // 申请读
	//MySqlProcess sqlProcess;
	//string path = "C:\\Users\\Administrator\\Desktop\\pose1.txt";
	map<int,string> orginPathMap;
	orginPathMap.insert(make_pair(1,"C:\\Users\\Administrator\\Desktop\\pose1.txt"));
	orginPathMap.insert(make_pair(2,"C:\\Users\\Administrator\\Desktop\\pose2.txt"));
	orginPathMap.insert(make_pair(3,"C:\\Users\\Administrator\\Desktop\\pose3.txt"));
	orginPathMap.insert(make_pair(4,"C:\\Users\\Administrator\\Desktop\\pose4.txt"));
	orginPathMap.insert(make_pair(5,"C:\\Users\\Administrator\\Desktop\\pose5.txt"));
	orginPathMap.insert(make_pair(6,"C:\\Users\\Administrator\\Desktop\\pose6.txt"));
	map<int,string> processPathMap;
	processPathMap.insert(make_pair(1,"C:\\Users\\Administrator\\Desktop\\pose_angle1.txt"));
	processPathMap.insert(make_pair(2,"C:\\Users\\Administrator\\Desktop\\pose_angle2.txt"));
	processPathMap.insert(make_pair(3,"C:\\Users\\Administrator\\Desktop\\pose_angle3.txt"));
	processPathMap.insert(make_pair(4,"C:\\Users\\Administrator\\Desktop\\pose_angle4.txt"));
	processPathMap.insert(make_pair(5,"C:\\Users\\Administrator\\Desktop\\pose_angle5.txt"));
	processPathMap.insert(make_pair(6,"C:\\Users\\Administrator\\Desktop\\pose_angle6.txt"));
	/*
	double* data = new double[800*3];
	//CMyCluster<double> cluster; 
	vector<vector<vector<double>>> clusterVec;
	sqlProcess.ReadTxt(path,data,3,800);
	for (int i = 0; i < 800; ++i)
	{
		for (int j = 0; j< 3; ++j)
		{
			std::cout<<data[i * 3 + j]<<"   "; 
		}	
		std::cout<<std::endl;
	}
	*/
	/*
	for (int i = 1;i <= 6; ++i)
	{

	}
	*/
	//CKinectProc angleProcess;
	//angleProcess.BatchProcess(orginPathMap,processPathMap);
	CMyCluster<double> clust;
	//CMyCluster<double>::ALLDATA cluster;
	vector<vector<vector<double>>> cluster;
	clust.ConvertData(processPathMap,cluster,40,60,6);
	FreeConsole();                      // 释放控制台资源
}
