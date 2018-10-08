
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Positioning.h"
#include "DlgProxy.h"
#include "PositioningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPositioningDlgAutoProxy

IMPLEMENT_DYNCREATE(CPositioningDlgAutoProxy, CCmdTarget)

CPositioningDlgAutoProxy::CPositioningDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CPositioningDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CPositioningDlg)))
		{
			m_pDialog = reinterpret_cast<CPositioningDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CPositioningDlgAutoProxy::~CPositioningDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CPositioningDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CPositioningDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPositioningDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IPositioning ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {4E815C12-68E2-4CAD-87AC-E323D6996D59}
static const IID IID_IPositioning =
{ 0x4E815C12, 0x68E2, 0x4CAD, { 0x87, 0xAC, 0xE3, 0x23, 0xD6, 0x99, 0x6D, 0x59 } };

BEGIN_INTERFACE_MAP(CPositioningDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CPositioningDlgAutoProxy, IID_IPositioning, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {C367FA16-669C-4D4C-BA6B-44157B76C329}
IMPLEMENT_OLECREATE2(CPositioningDlgAutoProxy, "Positioning.Application", 0xc367fa16, 0x669c, 0x4d4c, 0xba, 0x6b, 0x44, 0x15, 0x7b, 0x76, 0xc3, 0x29)


// CPositioningDlgAutoProxy ��Ϣ�������
