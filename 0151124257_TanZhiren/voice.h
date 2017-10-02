#pragma once


// voice 对话框

class voice : public CDialogEx
{
	DECLARE_DYNAMIC(voice)

public:
	voice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~voice();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	void Init();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
