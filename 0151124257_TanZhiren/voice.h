#pragma once


// voice �Ի���

class voice : public CDialogEx
{
	DECLARE_DYNAMIC(voice)

public:
	voice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~voice();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	void Init();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
