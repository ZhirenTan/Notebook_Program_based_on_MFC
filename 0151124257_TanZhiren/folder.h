#pragma once
#include "afxwin.h"


// folder �Ի���

class folder : public CDialog
{
	DECLARE_DYNAMIC(folder)

public:
	folder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~folder();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_floderName;
	afx_msg void OnBnClickedOk();
	CEdit m_edit;
};
