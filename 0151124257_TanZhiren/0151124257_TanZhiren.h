
// 0151124257_TanZhiren.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CMy0151124257_TanZhirenApp: 
// �йش����ʵ�֣������ 0151124257_TanZhiren.cpp
//

class CMy0151124257_TanZhirenApp : public CWinApp
{
public:
	CMy0151124257_TanZhirenApp();

// ��д
public:
	virtual BOOL InitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy0151124257_TanZhirenApp theApp;