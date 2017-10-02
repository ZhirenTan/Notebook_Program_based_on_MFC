
// 0151124257_TanZhirenDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CMy0151124257_TanZhirenDlg 对话框
class CMy0151124257_TanZhirenDlg : public CDialogEx
{
// 构造
public:
	CMy0151124257_TanZhirenDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0151124257_TANZHIREN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 文件目录树
	CString folderName;//文件夹名字
	HTREEITEM m_TreeRoot;
	CTreeCtrl m_Tree;
	HTREEITEM m_CurTree;//用以记录当前的节点
	HTREEITEM m_CurTreeParent;//用以当前节点的父节点
	CString m_CurTreeDir;//用以记录当前节点的路径
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
