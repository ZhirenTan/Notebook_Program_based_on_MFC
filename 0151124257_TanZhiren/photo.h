#pragma once
#include "cv.h"
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include "CvvImage.h"
using namespace std;
using namespace cv;
// photo �Ի���

class photo : public CDialogEx
{
	DECLARE_DYNAMIC(photo)

public:
	photo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~photo();


	void DrawPicToHDCC(IplImage *img, UINT ID);
// �Ի�������
	enum { IDD = IDD_DIALOG1 };
	IplImage *image;
	CRect rect1;
	CStatic* pStc1;
	CDC* pDC1;
	HDC hDC1;
	CString str;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
};
