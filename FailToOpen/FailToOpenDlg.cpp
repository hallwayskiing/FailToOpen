
// FailToOpenDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FailToOpen.h"
#include "FailToOpenDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFailToOpenDlg 对话框



CFailToOpenDlg::CFailToOpenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FAILTOOPEN_DIALOG, pParent)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFailToOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFailToOpenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CFailToOpenDlg::OnBnClickedButtonOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFailToOpenDlg 消息处理程序

BOOL CFailToOpenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//窗口置顶

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFailToOpenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFailToOpenDlg::OnPaint()
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
HCURSOR CFailToOpenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CFailToOpenDlg::clickTimes = 0;


void CFailToOpenDlg::OnBnClickedButtonOk()
{

	CRect rect; //存储当前窗口
	GetWindowRect(rect); //得到当前窗体的位置及大小

	srand(time(0) + rand());//随机种子

	clickTimes++;

	if (clickTimes > 10)//随机生成100个对话框
	{
		for (int j = 0; j < 100; j++)
		{
			CFailToOpenDlg* newDlg = new CFailToOpenDlg;
			newDlg->Create(IDD_FAILTOOPEN_DIALOG, this);
			newDlg->MoveWindow(rand() % 1600, rand() % 900, rect.Width(), rect.Height(), TRUE);
			newDlg->ShowWindow(SW_SHOW);
		}
	}
	else if (clickTimes > 4)//随机生成1个对话框
	{
		CFailToOpenDlg* newDlg = new CFailToOpenDlg;
		newDlg->Create(IDD_FAILTOOPEN_DIALOG, this);
		newDlg->MoveWindow(rand() % 1600, rand() % 900, rect.Width(), rect.Height(), TRUE);
		newDlg->ShowWindow(SW_SHOW);
	}
	else//随机改变窗口的位置
	{
		MoveWindow(rand() % 1600, rand() % 900, rect.Width(), rect.Height(), TRUE); 
	}
}


void CFailToOpenDlg::OnClose()
{
	/*if (clickTimes <= 4)*/
	{
		ShowWindow(SW_HIDE);

		Sleep(1500);

		CRect rect;
		GetWindowRect(&rect);

		CPoint point;
		GetCursorPos(&point);

		MoveWindow(point.x- rect.Width()/2, point.y-rect.Height()/2, rect.Width(), rect.Height(), TRUE);
		ShowWindow(SW_SHOW);
	}
}



BOOL CFailToOpenDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return true;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'X')
	{
		OnCancel();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
