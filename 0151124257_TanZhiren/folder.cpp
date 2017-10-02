// folder.cpp : 实现文件
//

#include "stdafx.h"
#include "0151124257_TanZhiren.h"
#include"0151124257_TanZhirenDlg.h"
#include "folder.h"
#include "afxdialogex.h"


// folder 对话框

IMPLEMENT_DYNAMIC(folder, CDialog)

folder::folder(CWnd* pParent /*=NULL*/)
	: CDialog(folder::IDD, pParent)
	, m_floderName(_T(""))
{

}

folder::~folder()
{
}

void folder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_floderName);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(folder, CDialog)
	ON_BN_CLICKED(IDOK, &folder::OnBnClickedOk)
END_MESSAGE_MAP()


// folder 消息处理程序


void folder::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	m_edit.GetWindowText(m_floderName);
	((CMy0151124257_TanZhirenDlg*)GetParent())->folderName=m_floderName;
	CDialog::OnOK();
}
