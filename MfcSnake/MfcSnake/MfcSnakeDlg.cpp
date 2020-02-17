
// MfcSnakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MfcSnake.h"
#include "MfcSnakeDlg.h"
#include "afxdialogex.h"
#include "Snack.h"
#include <iostream>
#include <random>
#include "windows.h"
#include "mmsystem.h" 
#include "CInfoDlg.h"
#pragma comment(lib, "WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;



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


// CMfcSnakeDlg 对话框



CMfcSnakeDlg::CMfcSnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	pen1.CreatePen(PS_SOLID, 4, RGB(174, 221, 129));
}

void CMfcSnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_speed, Box);
	DDX_Control(pDX, IDC_EDIT_score, EDIT_Score);
}

BEGIN_MESSAGE_MAP(CMfcSnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Stop, &CMfcSnakeDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_Start, &CMfcSnakeDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_speed, &CMfcSnakeDlg::OnCbnSelchangeCombospeed)
	ON_WM_WINDOWPOSCHANGING()
	ON_BN_CLICKED(IDC_Music, &CMfcSnakeDlg::OnBnClickedMusic)
END_MESSAGE_MAP()


// CMfcSnakeDlg 消息处理程序

BOOL CMfcSnakeDlg::OnInitDialog()
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

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMfcSnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcSnakeDlg::OnPaint()
{
	// ================================这个就是主要的游戏界面初始化函数==============================
	/*
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
	*/
	

	CRect rect;
	(this->GetDlgItem(IDC_game))->GetWindowRect(&rect);  // 获取控件相对于屏幕的位置
	ScreenToClient(rect); // 转化为相对于客户区的位置
	GetDlgItem(IDC_game)->MoveWindow(rect.left, rect.top + 4, 760, 600, false);

	CDC* pClientDC = GetDC();
	(this->GetDlgItem(IDC_game))->GetWindowRect(&rect);  // 获取控件相对于屏幕的位置
	ScreenToClient(rect); // 转化为相对于客户区的位置
	CPen pen(PS_SOLID, 6, RGB(6, 128, 67));
	CPen pen2(PS_SOLID, 10, RGB(174, 221, 129));
	CPen* oldPen = pClientDC->SelectObject(&pen2);
	pClientDC->Rectangle(rect);
	rect.left -= 5;
	rect.right += 5;
	rect.top -= 5;
	rect.bottom += 5;
	pClientDC->SelectObject(&pen);
	pClientDC->Rectangle(rect);
	pen.DeleteObject();
	pen2.DeleteObject();
	pClientDC->DeleteDC();

	// 画刷初始化
	CBitmap bodybmp, headbmp, beanbmp, bgbmp;
	bgbmp.LoadBitmapW(IDB_BITMAP5);
	beanbmp.LoadBitmapW(IDB_BITMAP4);
	bodybmp.LoadBitmapW(IDB_BITMAP2);
	headbmp.LoadBitmapW(IDB_BITMAP3);
	m_brush[0].CreatePatternBrush(&bodybmp);
	m_brush[1].CreatePatternBrush(&headbmp);
	m_brush[2].CreatePatternBrush(&beanbmp);
	m_brush[3].CreatePatternBrush(&bgbmp);

	// 控件初始化
	Box.SetCurSel(1);
	EDIT_Score.SetReadOnly(1);
	m_showFont1.CreatePointFont(200, L"黑体");
	GetDlgItem(IDC_EDIT_score)->SetFont(&m_showFont1);
	GetDlgItem(IDC_BUTTON_Start)->SetFont(&m_showFont1);
	GetDlgItem(IDC_BUTTON_Stop)->SetFont(&m_showFont1);
	m_showFont2.CreatePointFont(150, L"Consolas");
	GetDlgItem(IDC_Score)->SetFont(&m_showFont2);
	GetDlgItem(IDC_Speed)->SetFont(&m_showFont2);
	m_showFont3.CreatePointFont(100, L"Consolas");
	((CButton*)GetDlgItem(IDC_Music))->SetFont(&m_showFont3);
	((CButton*)GetDlgItem(IDC_Music))->SetCheck(BST_CHECKED);
	PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);

	OnBnClickedButtonStop();

	SnackInit();

	CPaintDC pDC(this);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMfcSnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcSnakeDlg::SnackInit()
{
	// 游戏区
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();

	// 棋盘初始化
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[3]);
	CPen* pOldPen = pdc->SelectObject(&pen1);
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 38; j++) {
			m_map[i][j].left = 0 + j * 20;
			m_map[i][j].right = 20 + j * 20;
			m_map[i][j].top = 0 + i * 20;
			m_map[i][j].bottom = 20 + i * 20;
			pdc->SelectObject(&m_brush[3]);
			pdc->Rectangle(m_map[i][j]);
			//pdc->SelectObject(&pen1);
			//pdc->Rectangle(m_map[i][j]);
		}
	}
	pdc->SelectObject(&pOldBrs);

	// 蛇初始化
	my_snake.init();
	score = 0;
	START = false;
	DEAD = false;
	srand((unsigned)time(NULL));
	drawSnake();
	setBean();


	// 控件初始化
	EDIT_Score.SetWindowTextW(_T("0"));
	SetDlgItemText(IDC_BUTTON_Start, _T("start"));
}

void CMfcSnakeDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	// 重新开始
	gameOver();
	SnackInit();
	this->GetDlgItem(IDC_game)->SetFocus();
}

void CMfcSnakeDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	CString start, pause;
	start = "start";
	pause = "pause";
	if (DEAD == false) {
		if (START) {
			START = false;
			KillTimer(1);
			SetDlgItemText(IDC_BUTTON_Start, start);
		}
		else {
			if (INIT) {
				INIT = false;
				SnackInit();
			}
			START = true;
			SetTimer(1, speed, NULL);
			SetDlgItemText(IDC_BUTTON_Start, pause);
		}
		this->GetDlgItem(IDC_game)->SetFocus();
	}
}

void CMfcSnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// main function about snake
	UpdateData(true);
	if (START && DEAD == false) {
		switch (my_snake.direc)
		{
		case 1:MvUp(); break;
		case 2:MvDown(); break;
		case 3:MvLeft(); break;
		case 4:MvRight(); break;
		default:
			break;
		}
		if (checkLive() == false) {
			DEAD = true;
			CString str;
			str.Format(_T("sorry, your score is %d ~ \n\n Please try again ~ "), score);
			//str = TEXT("sorry, your score is " + str + " ~ \n\n Please try again~");
			
			/*CInfoDlg dlg(NULL, m_showFont1, str);
			CInfoDlg dlg;
			INT_PTR nres = dlg.DoModal();
			if (IDOK == nres) {
				OnBnClickedButtonStop();
			}*/
			
			if (MessageBox(str, TEXT("INFO"), MB_ICONINFORMATION) == IDOK) {
				OnBnClickedButtonStop();
			}
			gameOver();
		} 
		eatBean();
		// drawSnake();
	}

	CDialogEx::OnTimer(nIDEvent);
}

bool CMfcSnakeDlg::setBean()
{
	srand((unsigned)time(NULL));
	bool setB = false;
	bool safe = true;
	while (safe) {
		pos.x = rand() % 30;
		pos.y = rand() % 38;
		for (int i = 0; i < my_snake.len; i++) {
			if (pos.x == my_snake.body[i].x && pos.y == my_snake.body[i].y) {
				safe = false; break;
			}
		}
		if (safe) {
			setB = true;
			safe = false;
		}
		else safe = true;
	}
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[2]);
	pdc->Rectangle(m_map[pos.x][pos.y]);
	pdc->SelectObject(&pen1);
	pdc->Rectangle(m_map[pos.x][pos.y]);
	pdc->SelectObject(&pOldBrs);
	pdc->DeleteDC();
	return setB;
}

void CMfcSnakeDlg::drawSnake()
{
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[0]);
	for (int i = 1; i < my_snake.len; i++) {
		pdc->SelectObject(&m_brush[0]);
		pdc->Rectangle(m_map[my_snake.body[i].x][my_snake.body[i].y]);
		pdc->SelectObject(&pen1);
		pdc->Rectangle(m_map[my_snake.body[i].x][my_snake.body[i].y]);
	}
	pdc->SelectObject(&m_brush[1]);
	pdc->Rectangle(m_map[my_snake.body[0].x][my_snake.body[0].y]);
	pdc->SelectObject(&pen1);
	pdc->Rectangle(m_map[my_snake.body[0].x][my_snake.body[0].y]);
	pdc->SelectObject(&pOldBrs);
	pdc->DeleteDC(); 
}

void CMfcSnakeDlg::MvUp()
{
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();
	// 将最后一个恢复背景色
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[3]);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(&pen1);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(pOldBrs);
	my_snake.UpMove();
	drawSnake();
}

void CMfcSnakeDlg::MvDown()
{
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[3]);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(&pen1);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(pOldBrs);
	my_snake.DownMove();
	drawSnake();
}

void CMfcSnakeDlg::MvLeft()
{
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[3]);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(&pen1);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(pOldBrs);
	my_snake.LeftMove();
	drawSnake();
}

void CMfcSnakeDlg::MvRight()
{
	CDC* pdc = GetDlgItem(IDC_game)->GetWindowDC();
	CBrush* pOldBrs = pdc->SelectObject(&m_brush[3]);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(&pen1);
	pdc->Rectangle(m_map[my_snake.body[my_snake.len - 1].x][my_snake.body[my_snake.len - 1].y]);
	pdc->SelectObject(pOldBrs);
	my_snake.RightMove();
	drawSnake();
}

void CMfcSnakeDlg::eatBean()
{
	if (pos.x == my_snake.body[0].x && pos.y == my_snake.body[0].y) {
		my_snake.len++;
		setBean();
		score = score + (abs(pos.x - my_snake.body[0].x) + abs(pos.y - my_snake.body[0].y));
		CString str;
		str.Format(_T("%d"), score);
		EDIT_Score.SetWindowTextW(str);
	}
}

bool CMfcSnakeDlg::checkLive()
{
	// 判断是否出界
	if (my_snake.body[0].x < 0 || my_snake.body[0].x >= 30 || my_snake.body[0].y < 0 || my_snake.body[0].y >= 38) return false;
	// 判断是否撞到了自己
	for (int i = 1; i < my_snake.len; i++) {
		if (my_snake.body[0].x == my_snake.body[i].x && my_snake.body[0].y == my_snake.body[i].y) return false;
	}
	return true;
}

void CMfcSnakeDlg::gameOver()
{
	KillTimer(1);
	START = false;
}

void CMfcSnakeDlg::OnCbnSelchangeCombospeed()
{
	// TODO: 在此添加控件通知处理程序代码
	//KillTimer(1);
	CString mode;
	Box.GetLBText(Box.GetCurSel(), mode);
	int tmp = 0;
	tmp = mode[0] - '0';
	speed = 300 / tmp;
	SetTimer(1, speed, NULL);
	this->GetDlgItem(IDC_game)->SetFocus();
}

BOOL CMfcSnakeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (START && DEAD == false) {
		if (my_snake.direc != 2 && (pMsg->wParam == VK_UP || pMsg->wParam == 'w' || pMsg->wParam == 'W')) my_snake.direc = 1;
		else if (my_snake.direc != 1 && (pMsg->wParam == VK_DOWN || pMsg->wParam == 's' || pMsg->wParam == 'S')) my_snake.direc = 2;
		else if (my_snake.direc != 4 && (pMsg->wParam == VK_LEFT || pMsg->wParam == 'a' || pMsg->wParam == 'A')) my_snake.direc = 3;
		else if (my_snake.direc != 3 && (pMsg->wParam == VK_RIGHT || pMsg->wParam == 'd' || pMsg->wParam == 'D')) my_snake.direc = 4;
	}
	/*if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_EDIT_score)->m_hWnd)
		{
			return true;
		}
	}*/

	//return CDialogEx::PreTranslateMessage(pMsg);
	return FALSE;
}

void CMfcSnakeDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	// TODO: 在此处添加消息处理程序代码
	// 获取屏幕宽度
	int nMaxX = GetSystemMetrics(SM_CXSCREEN);
	// 获取屏幕高度
	int nMaxY = GetSystemMetrics(SM_CYSCREEN);

	// 判断窗口X坐标有无超过左边桌面。
	if (lpwndpos->x < 0)
	{
		lpwndpos->x = 0;
	}

	// 判断窗口X坐标有无超过右边桌面。
	if (lpwndpos->x + lpwndpos->cx > nMaxX)
	{
		lpwndpos->x = nMaxX - lpwndpos->cx;
	}

	// 判断窗口Y坐标有无超过顶部桌面。
	if (lpwndpos->y < 0)
	{
		lpwndpos->y = 0;
	}

	// 判断窗口Y坐标有无超过底部桌面。
	if (lpwndpos->y + lpwndpos->cy > nMaxY)
	{
		lpwndpos->y = nMaxY - lpwndpos->cy;
	}
}

void CMfcSnakeDlg::OnBnClickedMusic()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_Music))->GetCheck();

	//PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	
	if (state == 0) {
		PlaySound(NULL, NULL, NULL);
		//((CButton*)GetDlgItem(IDC_Music))->SetCheck(BST_UNCHECKED);
	}
	else {
		PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		//((CButton*)GetDlgItem(IDC_Music))->SetCheck(BST_CHECKED);
	}
	
	
	
}
