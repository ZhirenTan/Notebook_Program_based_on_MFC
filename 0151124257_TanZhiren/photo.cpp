// photo.cpp : 实现文件
//

#include "stdafx.h"
#include "0151124257_TanZhiren.h"
#include "photo.h"
#include "afxdialogex.h"


// photo 对话框
IplImage outImage;
Mat frame;
IplImage *outvedio = NULL;
VideoCapture cap;
IMPLEMENT_DYNAMIC(photo, CDialogEx)

photo::photo(CWnd* pParent /*=NULL*/)
	: CDialogEx(photo::IDD, pParent)
{

}

photo::~photo()
{
}

void photo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(photo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &photo::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &photo::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &photo::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &photo::OnBnClickedCancel)
END_MESSAGE_MAP()


// photo 消息处理程序
IplImage drawpic(IplImage *pImgSrc)//没有调用
{
	IplImage  *pImg8u = NULL;  //Define a pic   灰度图
	IplImage  *pImg8u_jun = NULL;  //Define a pic   
	IplImage  *pImgCanny = NULL;  //Define a pic 边缘检测后的图
	IplImage *pImgDst = NULL;//在图像上检测到直线后的图
	CvSeq *lines = NULL;
	CvMemStorage *storage = NULL;
	pImg8u = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 1);
	pImg8u_jun = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 1);
	pImgCanny = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 1);     //canny算子边缘检测后的图像
	cvSmooth(pImgSrc, pImgSrc, CV_GAUSSIAN, 3, 3);   //高斯滤波
	cvCvtColor(pImgSrc, pImg8u, CV_RGB2GRAY);
	cvEqualizeHist(pImg8u, pImg8u_jun);
	//canny算子检测边缘
	cvCanny(pImg8u, pImgCanny, 9, 45, 3);
	/*return *pImgCanny;*///若返回该句，则为灰度图

	/*检测直线*/
	storage = cvCreateMemStorage(0);
	lines = cvHoughLines2(pImgCanny, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 80, 200, 10);
	pImgDst = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 3);
	cvCvtColor(pImg8u, pImgDst, CV_GRAY2BGR);


	/*在pImgDst上画出检测到的直线*/
	for (int i = 0; i < lines->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
		//cvLine (pImgDst, line[0], line[1], CV_RGB(255,0,0), 3, 8);
	}
	return *pImgDst;



}

void photo::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	cap.open(0);
	SetTimer(1, 100, NULL);
}

void photo::OnBnClickedButton2() //close
{
	// TODO:  在此添加控件通知处理程序代码
	cap.release();
	image = NULL; //原始图像
	if (image) cvReleaseImage(&image);
	DrawPicToHDCC(image, IDC_KAO);
	CDialogEx::OnCancel();
}

void photo::OnBnClickedButton3()
{
	// TODO:  
	int cx, cy;
	CvvImage image;
	CRect rect;
	//outvedio = &drawpic(outvedio);//若屏蔽该句，则为原始图片，不做任何处理
	image.CopyOf(outvedio);
	//获取图片的宽 高度  
	cx = image.Width()/2 ;
	cy = image.Height() /2;
	//获取Picture Control控件的大小  
	GetDlgItem(IDC_KAO)->GetWindowRect(&rect);
	//将客户区选中到控件表示的矩形区域内  
	ScreenToClient(&rect);
	//窗口移动到控件表示的区域  
	GetDlgItem(IDC_KAO)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);
	//GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, rect.right, rect.left, TRUE);
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_KAO);//获取控件句柄  
	pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小  
	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//获取picture的DC  
	image.DrawToHDC(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  


	const int N = 100;
	int result = rand() % N;
	str.Format(_T("C://我的笔记//照片//photo%d.jpg"), result);
	USES_CONVERSION;
	char * p = T2A(str.GetBuffer(str.GetLength()));
	cvSaveImage(p, outvedio);
	IplImage* imag = cvLoadImage(p);
	str.ReleaseBuffer();
	ReleaseDC(pDc);
}

void photo::DrawPicToHDCC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img); // 复制图片
	cimg.DrawToHDC(hDC, &rect); // 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);


}

BOOL photo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 256);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 192);
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void photo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int x, y;
	CvvImage out;
	CRect outrect;
	if (!cap.isOpened())
	{
		fprintf(stderr, "Can not open camera.\n");
		return;
	}
	cap >> frame;
	outImage = frame;
	outvedio = &outImage;
	out.CopyOf(outvedio);
	x = out.Width()/2 ;
	y = out.Height() /2;
	//获取Picture Control控件的大小  
	GetDlgItem(IDC_photo)->GetWindowRect(&outrect);
	//将客户区选中到控件表示的矩形区域内  
	ScreenToClient(&outrect);
	//窗口移动到控件表示的区域  
	GetDlgItem(IDC_photo)->MoveWindow(outrect.left, outrect.top, x, y, TRUE);
	CWnd *ppWnd = NULL;
	ppWnd = GetDlgItem(IDC_photo);//获取控件句柄  
	ppWnd->GetClientRect(&outrect);//获取句柄指向控件区域的大小  
	CDC *ppDc = NULL;
	ppDc = ppWnd->GetDC();//获取picture的DC  
	out.DrawToHDC(ppDc->m_hDC, outrect);//将图片绘制到picture表示的区域内  
	ReleaseDC(ppDc);

	CDialogEx::OnTimer(nIDEvent);
}

void photo::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
