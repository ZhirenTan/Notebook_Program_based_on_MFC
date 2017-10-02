
// 0151124257_TanZhirenDlg.cpp : 实现文件
//
#include "ctime"
#include "stdafx.h"
#include "0151124257_TanZhiren.h"
#include "0151124257_TanZhirenDlg.h"
#include "afxdialogex.h"
#include "photo.h"
#include "voice.h"
#include "Shlwapi.h"
#include "folder.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const DWORD Error_FileOrFolderNotFound = -1;//自定义返回码，表示未找到

const DWORD Return_IsFolder = 1;//自定义返回码，表示树节点对应为文件夹

const DWORD Return_IsFile = 0;//自定义返回码，表示树节点对应为文件

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy0151124257_TanZhirenDlg 对话框



CMy0151124257_TanZhirenDlg::CMy0151124257_TanZhirenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0151124257_TanZhirenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0151124257_TanZhirenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}

BEGIN_MESSAGE_MAP(CMy0151124257_TanZhirenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMy0151124257_TanZhirenDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CMy0151124257_TanZhirenDlg::OnNMRClickTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CMy0151124257_TanZhirenDlg::OnNMDblclkTree1)
	ON_COMMAND(ID_OPEN, &CMy0151124257_TanZhirenDlg::OnOpen)
	ON_COMMAND(ID_DELETE, &CMy0151124257_TanZhirenDlg::OnDelete)
	ON_COMMAND(ID_NEW_TXT, &CMy0151124257_TanZhirenDlg::OnNewTxt)
	ON_COMMAND(ID_NEW_JPG, &CMy0151124257_TanZhirenDlg::OnNewJpg)
	ON_COMMAND(ID_NEW_VOICE, &CMy0151124257_TanZhirenDlg::OnNewVoice)
	ON_COMMAND(ID_NEW_FOLDER, &CMy0151124257_TanZhirenDlg::OnNewFolder)
END_MESSAGE_MAP()


// CMy0151124257_TanZhirenDlg 消息处理程序

BOOL CMy0151124257_TanZhirenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//初始化文件目录
	m_TreeRoot = m_Tree.InsertItem(L"我的笔记");//插入根节点

	ShowFile(L"C:\\我的笔记", m_TreeRoot);//以C:\\我的笔记为根目录进行遍历

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy0151124257_TanZhirenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy0151124257_TanZhirenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy0151124257_TanZhirenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//函数名称：CMyScriptDlg::BrowseFile

//函数功能：遍历给定目录str_Dir下的文件夹及文件，并插入到树形控件中

//输入参数：str_Dir(起始目录)，tree_Root（树形控件的根节点）

//输出参数：无

//返回值  ：无

void CMy0151124257_TanZhirenDlg::ShowFile(CString str_Dir, HTREEITEM tree_Root)

{

	CFileFind FileFind;




	//临时变量，用以记录返回的树节点

	HTREEITEM tree_Temp;




	//判断输入目录最后是否存在'\'，不存在则补充

	if (str_Dir.Right(1) != "\\")

		str_Dir += "\\";

	str_Dir += "*.*";

	BOOL res = FileFind.FindFile(str_Dir);

	while (res)

	{

		tree_Temp = tree_Root;

		res = FileFind.FindNextFileW();

		if (FileFind.IsDirectory() && !FileFind.IsDots())//目录是文件夹

		{

			CString strPath = FileFind.GetFilePath(); //得到路径，做为递归调用的开始

			CString strTitle = FileFind.GetFileName();//得到目录名，做为树控的结点

			tree_Temp = m_Tree.InsertItem(strTitle, 0, 0, tree_Root);

			ShowFile(strPath, tree_Temp);

		}

		else if (!FileFind.IsDirectory() && !FileFind.IsDots())//如果是文件

		{

			CString strPath = FileFind.GetFilePath(); //得到路径，做为递归调用的开始

			CString strTitle = FileFind.GetFileName();//得到文件名，做为树控的结点

			m_Tree.InsertItem(strTitle, 0, 0, tree_Temp);

		}

	}

	FileFind.Close();

}

//响应鼠标的点击



HTREEITEM CMy0151124257_TanZhirenDlg::GetSelectTree()

{

	CPoint pt;

	GetCursorPos(&pt);//得到当前鼠标的位置

	UINT uFlags;

	m_Tree.ScreenToClient(&pt);//将屏幕坐标转换为客户区坐标

	HTREEITEM tree_Item = m_Tree.HitTest(pt,&uFlags);//调用HitTest找到对应点击的树节点

	return tree_Item;

}


DWORD CMy0151124257_TanZhirenDlg::GetFilePathByTreeItem()

{

	//临时变量

	bool IsDirectory;

	CString str_TempDir;

	HTREEITEM tree_CurTreeTemp;

	//获取到当前鼠标选择的树节点

	m_CurTree = GetSelectTree();

	if (m_CurTree == NULL)

	{

		AfxMessageBox(L"获取当前树节点失败！！");

	}

	tree_CurTreeTemp = m_CurTree;




	//获取当前节点的父节点，以便得到文件路径

	m_CurTreeParent = m_Tree.GetParentItem(m_CurTree);

	str_TempDir = m_Tree.GetItemText(m_CurTree);




	//为根节点时不作处理

	if (!str_TempDir.IsEmpty() && m_CurTreeParent != NULL)

	{

		m_CurTreeDir = str_TempDir;

		while (m_CurTreeParent != m_Tree.GetRootItem())//当父节点不为根节点时循环

		{

			//此处就是不断向上层层拼接文件路径的过程，比如123.txt的父节点是test1,然后经过             //一步循环后m_CurTreeDir就为：test1\\123.txt

			str_TempDir = m_Tree.GetItemText(m_CurTreeParent);

			m_CurTreeDir = str_TempDir + L"\\" + m_CurTreeDir;

			tree_CurTreeTemp = m_CurTreeParent;

			m_CurTreeParent = m_Tree.GetParentItem(tree_CurTreeTemp);

		}

		m_CurTreeDir = L"C:\\我的笔记\\" + m_CurTreeDir;

		CFileFind FileFind;

		BOOL res = FileFind.FindFile(m_CurTreeDir);

		if (res == true)

		{

			if (res = FileFind.FindNextFileW());

			{

				if (FileFind.IsDirectory() && !FileFind.IsDots())//如果是文件夹

					return Return_IsFolder;

				else if (!FileFind.IsDirectory() && !FileFind.IsDots())//如果是文件

					return Return_IsFile;

			}

		}


	}

	return Error_FileOrFolderNotFound;

}

void CMy0151124257_TanZhirenDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMy0151124257_TanZhirenDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	CPoint ScreenPt;

	GetCursorPos(&ScreenPt);




	//获取到当前鼠标选择的树节点，多重复用函数




	m_CurTree = GetSelectTree();

	if (m_CurTree != NULL)

	{

		m_Tree.SelectItem(m_CurTree); //使右键单击的树节点被选中




		CMenu menu;

		menu.LoadMenuW(IDR_MENU_MYTREE);

		CMenu* pPopup = menu.GetSubMenu(0);//装载第一个子菜单，即菜单的第一列

		pPopup->TrackPopupMenu(TPM_LEFTALIGN, ScreenPt.x, ScreenPt.y, this);//弹出菜单

	}
	*pResult = 0;
}


void CMy0151124257_TanZhirenDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码

	DWORD res = GetFilePathByTreeItem();

	//如果当前选择节点为文件，则将其打开

	if (res == Return_IsFile)

	{

		ShellExecute(NULL, NULL, m_CurTreeDir, NULL, NULL, SW_SHOWNORMAL);

	}

	*pResult = 0;
}


void CMy0151124257_TanZhirenDlg::OnOpen()
{
	// TODO:  在此添加命令处理程序代码
	DWORD res = GetFilePathByTreeItem();

	//如果当前选择节点为文件，则将其打开

	if (res == Return_IsFile)

	{

		ShellExecute(NULL, NULL, m_CurTreeDir, NULL, NULL, SW_SHOWNORMAL);

	}
}

//实现右击删除


void myDeleteDirectory(CString directory_path) //删除一个文件夹下的所有内容  
{
	CFileFind finder;
	CString path;
	path.Format(_T("%s/*.*"), directory_path);
	BOOL bWorking= finder.FindFile(path);
	while(bWorking){
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory() && !finder.IsDots()){//处理文件夹  
		}
		else{//处理文件  
			DeleteFile(finder.GetFilePath());
		}
	}
}
void CMy0151124257_TanZhirenDlg::OnDelete()
{
	// TODO:  在此添加命令处理程序代码

	m_Tree.DeleteItem(m_CurTree);
	SetFileAttributes(m_CurTreeDir, FILE_ATTRIBUTE_NORMAL); //去掉文件的系统和隐藏属性，史诗级大坑
	DeleteFile(m_CurTreeDir);


}

void CMy0151124257_TanZhirenDlg::OnNewTxt()
{
	// TODO:  在此添加命令处理程序代码
	srand(time(NULL));
	int N = 1000;
	int k = rand()%100;
	CFile file;
	CString filepath, filename, s,filetitle;
	HTREEITEM curPosition;
	curPosition = m_Tree.GetSelectedItem();
	filename = "新建文本文档.txt";
	filename.Format(_T("新建文本文档%d.txt"), k);
	m_Tree.InsertItem(filename, 0, 0, m_CurTree, TVI_LAST);

	filetitle=m_Tree.GetItemText(m_CurTree);
	filepath = m_CurTreeDir.Left(m_CurTreeDir.GetLength()-filetitle.GetLength());
	filename = _T("C:\\我的笔记\\")+filetitle+_T("\\") + filename;
	file.Open(filename, CFile::modeCreate | CFile::modeWrite);//建立文件
	s = _T("");
	file.Write(s, s.StringLength(s));
	file.Close();
}


void CMy0151124257_TanZhirenDlg::OnNewJpg()
{
	// TODO:  在此添加命令处理程序代码
	 photo dlg;
	dlg.DoModal();
}


void CMy0151124257_TanZhirenDlg::OnNewVoice()
{
	// TODO:  在此添加命令处理程序代码
	voice dlg1;
	dlg1.DoModal();
}


void CMy0151124257_TanZhirenDlg::OnNewFolder()
{
	// TODO:  在此添加命令处理程序代码
	folder dlg2;
	CString name;
	if (dlg2.DoModal() == IDOK)
	{
		AfxMessageBox(_T("成功命名！"));
	}
	CString filename,str;
	int k = rand() % 100;
	filename = folderName;
	m_Tree.InsertItem(filename, 0, 0, m_CurTree, TVI_LAST);
	CString m_strFolderPath = _T("C:\\我的笔记\\")+folderName;
	if (!PathIsDirectory(m_strFolderPath))
	{
		CString strMsg;
		strMsg.Format(_T("指定路径\"%s\"不存在，是否创建?"), m_strFolderPath);
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
		{
			if (!CreateDirectory(m_strFolderPath, NULL))
			{
				strMsg.Format(_T("创建路径\"%s\"失败！是否继续?"), m_strFolderPath);
				if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
					return;
			}
		}
	}
}
