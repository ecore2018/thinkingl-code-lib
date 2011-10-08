
#include "stdafx.h"
#include "MainFrm.h"
#include "Resource.h"
#include "DigitalImageProcessing.h"
#include "FunctionView.h"

#include "portabledefine.h"

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CFunctionView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// ����/����
//////////////////////////////////////////////////////////////////////

CFunctionView::CFunctionView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CFunctionView::~CFunctionView()
{
}

BEGIN_MESSAGE_MAP(CFunctionView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(TVN_SELCHANGED, ID_FunctionTree, OnFunctionTreeSelChange )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFunctionView ��Ϣ��������

int CFunctionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndFunctionView.Create(dwViewStyle, rectDummy, this, ID_FunctionTree))
	{
		TRACE0("δ�ܴ���������ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ����ͼ��:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* ������*/);

	m_dlgGrayscale.Create( CGrayscaleDialog::IDD, this );
	m_dlgGrayscale.ShowWindow( SW_SHOW );

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	FillClassView();

	return 0;
}

void CFunctionView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFunctionView::FillClassView()
{
	HTREEITEM hRoot = m_wndFunctionView.InsertItem(_T("����"), 0, 0);
	m_wndFunctionView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = m_wndFunctionView.InsertItem(_T("�Ҷ�ͼ"), 1, 1, hRoot);

	HTREEITEM hColorToGray = m_wndFunctionView.InsertItem( _T("��ɫת�ڰ�"), 1, 1, hClass );

	HTREEITEM hAvrRGB = m_wndFunctionView.InsertItem(_T("RGBƽ��(HSI)"), 3, 3, hColorToGray);
	m_wndFunctionView.SetItemData( hAvrRGB, DIP_Grayscale_AvrRGB );

	HTREEITEM hGrayscaleLevel = m_wndFunctionView.InsertItem(_T("�Ҷȵ���"), 3, 3, hClass);
	m_wndFunctionView.SetItemData( hAvrRGB, DIP_Grayscale_AvrRGB );

	m_wndFunctionView.Expand(hRoot, TVE_EXPAND);


// 	hClass = m_wndFunctionView.InsertItem(_T("CFakeApp"), 1, 1, hRoot);
// 	m_wndFunctionView.InsertItem(_T("CFakeApp()"), 3, 3, hClass);
// 	m_wndFunctionView.InsertItem(_T("InitInstance()"), 3, 3, hClass);
// 	m_wndFunctionView.InsertItem(_T("OnAppAbout()"), 3, 3, hClass);
// 
// 	hClass = m_wndFunctionView.InsertItem(_T("CFakeAppDoc"), 1, 1, hRoot);
// 	m_wndFunctionView.InsertItem(_T("CFakeAppDoc()"), 4, 4, hClass);
// 	m_wndFunctionView.InsertItem(_T("~CFakeAppDoc()"), 3, 3, hClass);
// 	m_wndFunctionView.InsertItem(_T("OnNewDocument()"), 3, 3, hClass);
// 
// 	hClass = m_wndFunctionView.InsertItem(_T("CFakeAppView"), 1, 1, hRoot);
// 	m_wndFunctionView.InsertItem(_T("CFakeAppView()"), 4, 4, hClass);
// 	m_wndFunctionView.InsertItem(_T("~CFakeAppView()"), 3, 3, hClass);
// 	m_wndFunctionView.InsertItem(_T("GetDocument()"), 3, 3, hClass);
// 	m_wndFunctionView.Expand(hClass, TVE_EXPAND);
// 
// 	hClass = m_wndFunctionView.InsertItem(_T("CFakeAppFrame"), 1, 1, hRoot);
// 	m_wndFunctionView.InsertItem(_T("CFakeAppFrame()"), 3, 3, hClass);
// 	m_wndFunctionView.InsertItem(_T("~CFakeAppFrame()"), 3, 3, hClass);
// 	m_wndFunctionView.InsertItem(_T("m_wndMenuBar"), 6, 6, hClass);
// 	m_wndFunctionView.InsertItem(_T("m_wndToolBar"), 6, 6, hClass);
// 	m_wndFunctionView.InsertItem(_T("m_wndStatusBar"), 6, 6, hClass);
// 
// 	hClass = m_wndFunctionView.InsertItem(_T("Globals"), 2, 2, hRoot);
// 	m_wndFunctionView.InsertItem(_T("theFakeApp"), 5, 5, hClass);
// 	m_wndFunctionView.Expand(hClass, TVE_EXPAND);
}

void CFunctionView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndFunctionView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CFunctionView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	CRect rcFunDlg;
	this->m_dlgGrayscale.GetWindowRect( rcFunDlg );
	int cyFunDlg = rcFunDlg.Height();

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_dlgGrayscale.SetWindowPos( NULL, rectClient.left, rectClient.bottom - cyFunDlg, rectClient.Width(), cyFunDlg, SWP_NOACTIVATE | SWP_NOZORDER );

	m_wndFunctionView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - cyFunDlg - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CFunctionView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CFunctionView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CFunctionView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CFunctionView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("���ӳ�Ա����..."));
}

void CFunctionView::OnClassAddMemberVariable()
{
	// TODO: �ڴ˴�����������������
}

void CFunctionView::OnClassDefinition()
{
	// TODO: �ڴ˴�����������������
}

void CFunctionView::OnClassProperties()
{
	// TODO: �ڴ˴�����������������
}

void CFunctionView::OnNewFolder()
{
	AfxMessageBox(_T("�½��ļ���..."));
}

void CFunctionView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	m_wndFunctionView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFunctionView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFunctionView.SetFocus();
}

void CFunctionView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndFunctionView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* ����*/);
}


void CFunctionView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ

	CDockablePane::OnLButtonDown(nFlags, point);
}


HRESULT CFunctionView::accSelect(long flagsSelect, VARIANT varChild)
{
	// TODO: �ڴ�����ר�ô����/����û���

	return CDockablePane::accSelect(flagsSelect, varChild);
}


BOOL CFunctionView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: �ڴ�����ר�ô����/����û���

	return CDockablePane::OnChildNotify(message, wParam, lParam, pLResult);
}


BOOL CFunctionView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ�����ר�ô����/����û���
	if ( ID_FunctionTree == wParam )
	{
		LPNMHDR pNMHDR = (LPNMHDR)lParam;
		if ( TVN_SELCHANGED == pNMHDR->code )
		{
			LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

			int dipFunId = pNMTreeView->itemNew.lParam;
			switch( dipFunId )
			{
			case DIP_Grayscale_AvrRGB:

				

				break;

			}
		}
	}


	return CDockablePane::OnNotify(wParam, lParam, pResult);
}


BOOL CFunctionView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ�����ר�ô����/����û���
	if ( TVN_SELCHANGED == wParam )
	{
		int fsdfe = 32;
	}
	tstringstream ssMsg;
	ssMsg << _T( "on command: ") << wParam << _T( " lp: ") << lParam << endl;
	OutputDebugString( ssMsg.str().c_str() );

	return CDockablePane::OnCommand(wParam, lParam);
}

void CFunctionView::OnFunctionTreeSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������



	*pResult = 0;
}


BOOL CFunctionView::Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, DWORD dwTabbedStyle /* = AFX_CBRS_REGULAR_TABS */, DWORD dwControlBarStyle /* = AFX_DEFAULT_DOCKING_PANE_STYLE */, CCreateContext* pContext /* = NULL */)
{
	// TODO: �ڴ�����ר�ô����/����û���

	BOOL bRet = CDockablePane::Create(lpszCaption, pParentWnd, rect, bHasGripper, nID, dwStyle, dwTabbedStyle, dwControlBarStyle, pContext);



	return bRet;
}