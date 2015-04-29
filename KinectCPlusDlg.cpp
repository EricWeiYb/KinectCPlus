
// KinectCPlusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KinectCPlus.h"
#include "KinectCPlusDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CKinectCPlusDlg �Ի���



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


// CKinectCPlusDlg ��Ϣ�������

BOOL CKinectCPlusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	AllocConsole();                     // �򿪿���̨��Դ
	//freopen_s("CONOUT$", "w+t", stdout );// ����д
	//freopen_s( "CONIN$", "r+t", stdin );  // �����
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKinectCPlusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	freopen( "CONOUT$", "w+t", stdout );// ����д
	freopen( "CONIN$", "r+t", stdin );  // �����
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
	FreeConsole();                      // �ͷſ���̨��Դ
}
