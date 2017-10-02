// photo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0151124257_TanZhiren.h"
#include "photo.h"
#include "afxdialogex.h"


// photo �Ի���
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


// photo ��Ϣ�������
IplImage drawpic(IplImage *pImgSrc)//û�е���
{
	IplImage  *pImg8u = NULL;  //Define a pic   �Ҷ�ͼ
	IplImage  *pImg8u_jun = NULL;  //Define a pic   
	IplImage  *pImgCanny = NULL;  //Define a pic ��Ե�����ͼ
	IplImage *pImgDst = NULL;//��ͼ���ϼ�⵽ֱ�ߺ��ͼ
	CvSeq *lines = NULL;
	CvMemStorage *storage = NULL;
	pImg8u = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 1);
	pImg8u_jun = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 1);
	pImgCanny = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 1);     //canny���ӱ�Ե�����ͼ��
	cvSmooth(pImgSrc, pImgSrc, CV_GAUSSIAN, 3, 3);   //��˹�˲�
	cvCvtColor(pImgSrc, pImg8u, CV_RGB2GRAY);
	cvEqualizeHist(pImg8u, pImg8u_jun);
	//canny���Ӽ���Ե
	cvCanny(pImg8u, pImgCanny, 9, 45, 3);
	/*return *pImgCanny;*///�����ظþ䣬��Ϊ�Ҷ�ͼ

	/*���ֱ��*/
	storage = cvCreateMemStorage(0);
	lines = cvHoughLines2(pImgCanny, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 80, 200, 10);
	pImgDst = cvCreateImage(cvGetSize(pImgSrc), IPL_DEPTH_8U, 3);
	cvCvtColor(pImg8u, pImgDst, CV_GRAY2BGR);


	/*��pImgDst�ϻ�����⵽��ֱ��*/
	for (int i = 0; i < lines->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
		//cvLine (pImgDst, line[0], line[1], CV_RGB(255,0,0), 3, 8);
	}
	return *pImgDst;



}

void photo::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cap.open(0);
	SetTimer(1, 100, NULL);
}

void photo::OnBnClickedButton2() //close
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cap.release();
	image = NULL; //ԭʼͼ��
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
	//outvedio = &drawpic(outvedio);//�����θþ䣬��ΪԭʼͼƬ�������κδ���
	image.CopyOf(outvedio);
	//��ȡͼƬ�Ŀ� �߶�  
	cx = image.Width()/2 ;
	cy = image.Height() /2;
	//��ȡPicture Control�ؼ��Ĵ�С  
	GetDlgItem(IDC_KAO)->GetWindowRect(&rect);
	//���ͻ���ѡ�е��ؼ���ʾ�ľ���������  
	ScreenToClient(&rect);
	//�����ƶ����ؼ���ʾ������  
	GetDlgItem(IDC_KAO)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);
	//GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, rect.right, rect.left, TRUE);
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_KAO);//��ȡ�ؼ����  
	pWnd->GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//��ȡpicture��DC  
	image.DrawToHDC(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  


	const int N = 100;
	int result = rand() % N;
	str.Format(_T("C://�ҵıʼ�//��Ƭ//photo%d.jpg"), result);
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
	cimg.CopyOf(img); // ����ͼƬ
	cimg.DrawToHDC(hDC, &rect); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC(pDC);


}

BOOL photo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 256);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 192);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void photo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	//��ȡPicture Control�ؼ��Ĵ�С  
	GetDlgItem(IDC_photo)->GetWindowRect(&outrect);
	//���ͻ���ѡ�е��ؼ���ʾ�ľ���������  
	ScreenToClient(&outrect);
	//�����ƶ����ؼ���ʾ������  
	GetDlgItem(IDC_photo)->MoveWindow(outrect.left, outrect.top, x, y, TRUE);
	CWnd *ppWnd = NULL;
	ppWnd = GetDlgItem(IDC_photo);//��ȡ�ؼ����  
	ppWnd->GetClientRect(&outrect);//��ȡ���ָ��ؼ�����Ĵ�С  
	CDC *ppDc = NULL;
	ppDc = ppWnd->GetDC();//��ȡpicture��DC  
	out.DrawToHDC(ppDc->m_hDC, outrect);//��ͼƬ���Ƶ�picture��ʾ��������  
	ReleaseDC(ppDc);

	CDialogEx::OnTimer(nIDEvent);
}

void photo::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
