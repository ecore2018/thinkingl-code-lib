
// LDAPDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLDAPDemoApp: 
// �йش����ʵ�֣������ LDAPDemo.cpp
//

class CLDAPDemoApp : public CWinApp
{
public:
	CLDAPDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLDAPDemoApp theApp;