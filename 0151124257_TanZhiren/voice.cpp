// voice.cpp : 实现文件
//

#include "stdafx.h"
#include "0151124257_TanZhiren.h"
#include "voice.h"
#include "afxdialogex.h"
#include <windows.h>
#include<Vfw.h>
// voice 对话框

IMPLEMENT_DYNAMIC(voice, CDialogEx)
HWND g_hWndMCIWnd;
voice::voice(CWnd* pParent /*=NULL*/)
	: CDialogEx(voice::IDD, pParent)
{

}

voice::~voice()
{
}

void voice::Init()
{
	MCIWndClose(g_hWndMCIWnd);//这个是为了打开一个声音的之前关闭以前的声音,应该先加一个判断好了.

	g_hWndMCIWnd = MCIWndCreate(this->m_hWnd, ::AfxGetApp()->m_hInstance, WS_CAPTION, NULL);//创建句柄要说的是最后一个参数,如果是NULL,就新建一个,如果是一个文件的路径,就打开它.但是都要使用下面的MCIWndNew来开内存

	MCIWndNew(g_hWndMCIWnd, _T("waveaudio"));
}
void voice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(voice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &voice::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &voice::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &voice::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &voice::OnBnClickedButton4)
END_MESSAGE_MAP()


// voice 消息处理程序


void voice::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	Init();
	if (MCIWndCanRecord(g_hWndMCIWnd))//判断是否可以录音
	{
		MCIWndRecord(g_hWndMCIWnd);//录音
	}
	else
	{
		AfxMessageBox(_T("error #01"));
	}
}


void voice::OnBnClickedButton2()//暂停
{
	// TODO:  在此添加控件通知处理程序代码
	MCIWndStop(g_hWndMCIWnd);
}


void voice::OnBnClickedButton3()//播放
{
	// TODO:  在此添加控件通知处理程序代码
	if (MCIWndCanPlay(g_hWndMCIWnd))
	{
		MCIWndPlay(g_hWndMCIWnd);
    }
  else
	  AfxMessageBox(_T("没有可播放文件！"));
}


void voice::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	CString m_Path=NULL;
	CFileDialog wav1(FALSE, _T("wav"),NULL, NULL,_T("wav File (*.wav)|*.wav"));//参数问题，大坑
	if (wav1.DoModal() == IDOK)
	{
		m_Path = wav1.GetPathName();
	}
	else
		return;
	if (MCIWndCanSave(g_hWndMCIWnd))
	{

		MCIWndSave(g_hWndMCIWnd, "a");

		CopyFile(_T("a"), m_Path, FALSE);
	}
	else
		AfxMessageBox(_T("保存失败！"));
}
