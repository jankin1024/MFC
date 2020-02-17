#pragma once


// CInfoDlg 对话框

class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent =nullptr);   // 标准构造函数
	CInfoDlg(CWnd* pParent /*=nullptr*/, CFont& m_showFont, CString& str);
	virtual ~CInfoDlg();
	CFont* m_showFont = NULL;
	CString* str;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
