
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CPositioningDlg;


// CPositioningDlgAutoProxy ����Ŀ��

class CPositioningDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CPositioningDlgAutoProxy)

	CPositioningDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CPositioningDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CPositioningDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CPositioningDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

