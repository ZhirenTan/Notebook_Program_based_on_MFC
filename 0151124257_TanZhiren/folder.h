#pragma once
#include "afxwin.h"


// folder 对话框

class folder : public CDialog
{
	DECLARE_DYNAMIC(folder)

public:
	folder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~folder();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_floderName;
	afx_msg void OnBnClickedOk();
	CEdit m_edit;
};
