
// 0151124257_TanZhirenDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMy0151124257_TanZhirenDlg �Ի���
class CMy0151124257_TanZhirenDlg : public CDialogEx
{
// ����
public:
	CMy0151124257_TanZhirenDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0151124257_TANZHIREN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �ļ�Ŀ¼��
	CString folderName;//�ļ�������
	HTREEITEM m_TreeRoot;
	CTreeCtrl m_Tree;
	HTREEITEM m_CurTree;//���Լ�¼��ǰ�Ľڵ�
	HTREEITEM m_CurTreeParent;//���Ե�ǰ�ڵ�ĸ��ڵ�
	CString m_CurTreeDir;//���Լ�¼��ǰ�ڵ��·��
	DWORD CMy0151124257_TanZhirenDlg::GetFilePathByTreeItem();
	HTREEITEM CMy0151124257_TanZhirenDlg::GetSelectTree();
	void ShowFile(CString str_Dir,HTREEITEM tree_Root);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOpen();
	afx_msg void OnDelete();
	afx_msg void OnNewTxt();
	afx_msg void OnNewJpg();
	afx_msg void OnNewVoice();
	afx_msg void OnNewFolder();
};
