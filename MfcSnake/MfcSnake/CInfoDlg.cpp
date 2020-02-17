// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MfcSnake.h"
#include "CInfoDlg.h"
#include "afxdialogex.h"


// CInfoDlg 对话框

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_showFont = NULL;
	str = NULL;
	//m_showFont->CreatePointFont(200, L"黑体");
	//str->Format(_T("sorry, your snake is dead ~ \n\n Please try again ~ "));
}

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/, CFont& m_showFont, CString& str)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_showFont(&m_showFont)
	, str(&str)
{
	this->GetDlgItem(IDC_INFO)->SetWindowTextW(str);
	this->GetDlgItem(IDC_INFO)->SetFont(&m_showFont);

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CInfoDlg 消息处理程序
