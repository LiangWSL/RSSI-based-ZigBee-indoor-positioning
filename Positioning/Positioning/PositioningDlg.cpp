
// PositioningDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Positioning.h"
#include "PositioningDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern float ComputerX(float ax,float ay,float bx,float by,float cx,float cy,float az,float bz,float cz);
extern float ComputerY(float ax,float ay,float bx,float by,float cx,float cy,float az,float bz,float cz);
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPositioningDlg �Ի���




IMPLEMENT_DYNAMIC(CPositioningDlg, CDialogEx);

CPositioningDlg::CPositioningDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPositioningDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	m_ax = 0.0f;
	m_ay = 0.0f;
	m_bx = 0.0f;
	m_by = 0.0f;
	m_cx = 0.0f;
	m_cy = 0.0f;
	//  m_A = 0.0f;
	//  m_n = 0.0f;
	m_Edit_A = 0.0f;
	m_Edit_n = 0.0f;
	m_BlindToA = 0.0f;
	m_BlindToB = 0.0f;
	m_BlindToC = 0.0f;
	m_BlindX = 0.0f;
	m_BlindY = 0.0f;
	m_anchorA.RSSI = "000";
	m_anchorB.RSSI = "000";
	m_anchorC.RSSI = "000";
	m_bCommunFlag = false;

}

CPositioningDlg::~CPositioningDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CPositioningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_COMBO_botelv, m_Botelv);
	//  DDX_Control(pDX, IDC_COMBO_duankou, m_Port);
	DDX_Control(pDX, IDC_COMBO_botelv, m_Botelv);
	DDX_Control(pDX, IDC_COMBO_duankou, m_Duankou);
	DDX_Control(pDX, IDC_COMBO_jiaoyanwei, m_Jiaoyanwei);
	DDX_Control(pDX, IDC_COMBO_shujuwei, m_Shujuwei);
	DDX_Control(pDX, IDC_COMBO_tingzhiwei, m_Tingzhiwei);
	DDX_Text(pDX, IDC_EDIT_AX, m_ax);
	DDX_Text(pDX, IDC_EDIT_AY, m_ay);
	DDX_Text(pDX, IDC_EDIT_BX, m_bx);
	DDX_Text(pDX, IDC_EDIT_BY, m_by);
	DDX_Text(pDX, IDC_EDIT_CX, m_cx);
	DDX_Text(pDX, IDC_EDIT_CY, m_cy);
	//  DDX_Text(pDX, IDC_EDIT_A, m_A);
	//  DDX_Text(pDX, IDC_EDIT_n, m_n);
	DDX_Text(pDX, IDC_EDIT_A, m_Edit_A);
	DDX_Text(pDX, IDC_EDIT_n, m_Edit_n);

	DDX_Text(pDX, IDC_EDIT_BlindToA, m_BlindToA);
	DDX_Text(pDX, IDC_EDIT_BlindToB, m_BlindToB);
	DDX_Text(pDX, IDC_EDIT_BlindToC, m_BlindToC);
	DDX_Text(pDX, IDC_EDIT_BlindX, m_BlindX);
	DDX_Text(pDX, IDC_EDIT_BlindY, m_BlindY);
//	DDX_Text(pDX, IDC_EDIT_Temperature, m_temperature);
}

BEGIN_MESSAGE_MAP(CPositioningDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_BN_CLICKED(IDC_BTN_Start, &CPositioningDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_Pause, &CPositioningDlg::OnBnClickedBtnPause)
END_MESSAGE_MAP()


// CPositioningDlg ��Ϣ�������

BOOL CPositioningDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_Duankou.SetCurSel(0);
	m_Botelv.SetCurSel(0);
	m_Shujuwei.SetCurSel(3);
	m_Jiaoyanwei.SetCurSel(0);
	m_Tingzhiwei.SetCurSel(0);
	

	m_ax = 0.0;
	m_ay = 0.0;
	m_bx = 5.0;
	m_by = 0.0;
	m_cx = 0.0;
	m_cy = 5.0;
	m_Edit_A  = 45.0;
	m_Edit_n	  = 3.25;

	m_DisShow = "";
	pAedit=(CEdit*)GetDlgItem(IDC_EDIT_BlindToA);//������ȡEdit�༭���ָ��
	pBedit=(CEdit*)GetDlgItem(IDC_EDIT_BlindToB);
	pCedit=(CEdit*)GetDlgItem(IDC_EDIT_BlindToC);
	pBlindXedit = (CEdit*)GetDlgItem(IDC_EDIT_BlindX);
	pBlindYedit = (CEdit*)GetDlgItem(IDC_EDIT_BlindY);
	UpdateData(FALSE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPositioningDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPositioningDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPositioningDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CPositioningDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CPositioningDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CPositioningDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CPositioningDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


//���ڳ�ʼ��
void CPositioningDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bCommunFlag = true;
	UpdateData(TRUE);//��ȡ�Ի������������ֵ
	m_anchorA.x = m_ax;
	m_anchorA.y = m_ay;
	m_anchorB.x = m_bx;
	m_anchorB.y = m_by;
	m_anchorC.x = m_cx;
	m_anchorC.y = m_cy;
	//�˿ں�
	int  comID;
	comID = m_Duankou.GetCurSel();//�õ�ѡ��Ķ˿ںŵ�����
	switch(comID)
	{
	case  0:
		m_PortNum = 1;
		break;
	case  1:
		m_PortNum = 2;
		break;
	case  2:
		m_PortNum = 3;
		break;
	case  3:
		m_PortNum = 4;
		break;
	case  4:
		m_PortNum = 5;
		break;
	case  5:
		m_PortNum = 6;
		break;
	}
	//������
	int  btl;
	btl = m_Botelv.GetCurSel();
	switch(btl)
	{
	case  0:
		m_BotelvNum = 9600;
		break;
	case  1:
		m_BotelvNum = 19200;
		break;
	case  2:
		m_BotelvNum = 115200;
		break;
	}

	//����ʾ���򲻽��в����ʵ���ֵ�ĸ���
	if (m_Port.InitPort(this,m_PortNum,m_BotelvNum,'N',8,1,EV_RXCHAR | EV_RXFLAG,512))
	{
		m_Port.StartMonitoring();
		m_bPortFlag = true;
	}
	else
	{
		AfxMessageBox("���ڳ�ʼ��ʧ��");
		m_bPortFlag = false;
		//	exit(-1);
	}
}
int  a,b,c,temp=0;//��ʾê�ڵ�ı�־λA��B\C��һ�䱨����������λ��

//ÿ�����ڷ�����Ϣ�����ô˺������д���
LRESULT CPositioningDlg::OnCommunication(WPARAM ch, LPARAM port)
{
	if ( true == m_bCommunFlag)
	{
	m_Every_Data +=(char) ch;//���մ��ڷ�����һ���ַ�
	//������λ���ڷ��͵�ʱ���������һ��'\n'����
	//����ÿ�ν��ܵ���������Ȼ��A012��ʽ�����������һ�����з�δ��ʾ
	if (ch == '\n')
	{
		//MessageBox("huiche");
		//exit(0);
		if (5 == m_Every_Data.GetLength())//��ÿ��Э������������ÿ���ڵ���������屣�����ַ����У���ֹ���ղ�����
		{

		//m_Receive_All_Data +=m_Every_Data;
			
		if (-1 !=( m_Every_Data.Find('A')))//���ܵ���A�ڵ���Ϣ
		{
			for (int i = 1; i <= 3; i++)//��ÿ���ڵ������ȡ��
			{
				m_anchorA.RSSI		+= m_Every_Data.GetAt(i);
				temp++;
			}
			m_anchorA.dis = ComputerDistance(atoi(m_anchorA.RSSI));
			m_anchorA.RSSI.Empty();
		}
		else if (-1 !=( m_Every_Data.Find('B')))
		{
			for (int i = 1; i <= 3; i++)//��ÿ���ڵ������ȡ��
			{
				m_anchorB.RSSI		+= m_Every_Data.GetAt(i);
				temp++;
			}
			m_anchorB.dis = ComputerDistance(atoi(m_anchorB.RSSI));
			m_anchorB.RSSI.Empty();
		}
		else if(-1 !=( m_Every_Data.Find('C')))
		{
			for (int i = 1; i <= 3; i++)//��ÿ���ڵ������ȡ��
			{
				m_anchorC.RSSI		+= m_Every_Data.GetAt(i);
				temp++;
			}
			m_anchorC.dis = ComputerDistance(atoi(m_anchorC.RSSI));
			m_anchorC.RSSI.Empty();
		}
		m_Every_Data.Empty();//�����ν��յ�����A�ڵ�������������������B�ڵ�����
		if (temp >= 3)
		{
		
		//����ê�ڵ��ä�ڵ�֮�����Ծ���
		//m_anchorA.dis = ComputerDistance(atoi(m_anchorA.RSSI));
		//m_anchorB.dis = ComputerDistance(atoi(m_anchorB.RSSI));
		//m_anchorC.dis = ComputerDistance(atoi(m_anchorC.RSSI));

		//������Ծ������ä�ڵ������

		m_blindNode.x=ComputerX(m_ax,m_ay,m_bx,m_by,m_cx,m_cy,m_BlindToA,m_BlindToB,m_BlindToC);		
		m_blindNode.y=ComputerY(m_ax,m_ay,m_bx,m_by,m_cx,m_cy,m_BlindToA,m_BlindToB,m_BlindToC);		

		m_BlindToA = m_anchorA.dis;
		m_BlindToB = m_anchorB.dis;
		m_BlindToC = m_anchorC.dis;
		m_BlindX = m_blindNode.x;
		m_BlindY = m_blindNode.y;
		//�������֮�󣬽�����һѭ���Ĳ��������ٴν���ABC��ֵ
		//		UpdateData(FALSE);
		//Ŀ����ֻ������ʾ����ֵ
		m_DisShow.Format("%f",m_BlindToA);
		pAedit->SetWindowText(m_DisShow);
		m_DisShow.Format("%f",m_BlindToB);
		pBedit->SetWindowText(m_DisShow);
		m_DisShow.Format("%f",m_BlindToC);
		pCedit->SetWindowText(m_DisShow);

		m_DisShow.Format("%f",m_BlindX);
		pBlindXedit->SetWindowText(m_DisShow);
		m_DisShow.Format("%f",m_BlindY);
		pBlindYedit->SetWindowText(m_DisShow);

		//m_Receive_All_Data.Empty();
	/*	m_anchorA.RSSI.Empty();
		m_anchorB.RSSI.Empty();
		m_anchorC.RSSI.Empty();*/
		}
	}
}	
	return 0;
	
	}
}

//ê�ڵ���ݽ��յ���ä�ڵ��RSSIֵ��������֮�����Ծ���
float CPositioningDlg::ComputerDistance(int rssi)
{
	float  distance;
//	distance = pow(10.0,(abs((double)(rssi-m_Edit_A)))/(10*m_Edit_n));

	//	double  mi = ((double)(rssi-m_A))/(10*m_n);
	//	distance = pow((double)10.0,mi);
	distance = pow((double)10.0,(((double)(rssi-m_Edit_A)))/(10*m_Edit_n));
	return distance;
}
void  CPositioningDlg::Computer_location(double ax,double ay,double la,double bx,double by, double lb,double cx, double cy, double lc)
{ 

	int i = 0,j = 0,n = 0; 
	int okflag = 0; 
	int err = 0; 
	int aberr = 0; 
	int acerr = 0; 
	int abcerr = 0; 
	int len; 
	int abrequery = 0; 
	int acrequery = 0; 
	int requery1 = 0; 
	int loopnum = 1; 
	int option = 0; 

	double cax,cay,cbx,cby,ccx,ccy; 
	double cax_abeyance1[6000],cay_abeyance1[6000]; 
	double cbx_abeyance1[6000],cby_abeyance1[6000]; 
	double ccx_abeyance1[6000],ccy_abeyance1[6000]; 
	double cabx_abeyance1[10],caby_abeyance1[10],cabx_abeyance2[10],caby_abeyance2[10]; 
	double cacx_abeyance1[10],cacy_abeyance1[10],cacx_abeyance2[10],cacy_abeyance2[10]; 

	//����Բ�������е� 

	//INPUT: z�����������AΪԲ�ģ���Z��A�ľ���Ϊ�뾶��Բ����
	for(m_blindNode.x = ax -la;m_blindNode.x <= ax + la;m_blindNode.x++) //��AΪԲ����A��Z�ľ���Ϊ�뾶��Բ��m_blindNode.x��Բ��x�����߽��㵽�ұ߽���
	{ 
		do 
		{ 
			for(m_blindNode.y = ay -la;m_blindNode.y <= ay + la;m_blindNode.y++) //y����Բ�Ľ���
			{ 
				cax = m_blindNode.x - ax; 
				cax = fabs(cax); 
				cax = pow(cax,2); 
				cay = m_blindNode.y - ay; 
				cay = fabs(cay); 
				cay = pow(cay,2);//������֮��Ĳ�ֵ��������� 
				if(((cax + cay) > (la*la - err))&&((cax + cay) < (la*la + err))) //���������ľ���ƽ��֮�͵��ڸ����ľ���ƽ��ʱ��������ֵ
				{ 
					okflag = 1; 
					cax_abeyance1[i] = m_blindNode.x; 
					cay_abeyance1[i] = m_blindNode.y; 
					n++; 
				} 
			} 
			if(!okflag)err++; 
		} while (okflag == 0); 
		i++; 
		err = 0; 
		okflag = 0; 
	} 
	i = 0; 
	for(m_blindNode.x = bx -lb;m_blindNode.x <= bx + lb;m_blindNode.x++) 
	{ 
		do 
		{ 
			for(m_blindNode.y = by -lb;m_blindNode.y <= by + lb;m_blindNode.y++) 
			{ 
				cbx = m_blindNode.x - bx; 
				cbx = fabs(cbx); 
				cbx = pow(cbx,2); 
				cby = m_blindNode.y - by; 
				cby = fabs(cby); 
				cby = pow(cby,2); 
				if(((cbx + cby) > (lb*lb - err))&&((cbx + cby) < (lb*lb + err))) 
				{ 
					okflag = 1; 
					cbx_abeyance1[i] = m_blindNode.x; 
					cby_abeyance1[i] = m_blindNode.y; 
				} 
			} 
			if(!okflag)err++;       
		} while (okflag == 0); 
		i++; 
		err = 0; 
		okflag = 0; 
	} 
	i = 0; 
	for(m_blindNode.x = cx -lc;m_blindNode.x <= cx + lc;m_blindNode.x++) 
	{ 
		do 
		{ 
			for(m_blindNode.y = cy -lc;m_blindNode.y <= cy + lc;m_blindNode.y++) 
			{ 
				ccx = m_blindNode.x - cx; 
				ccx = fabs(ccx); 
				ccx = pow(ccx,2); 
				ccy = m_blindNode.y - cy; 
				ccy = fabs(ccy); 
				ccy = pow(ccy,2); 
				if(((ccx + ccy) > (lc*lc - err))&&((ccx + ccy) < (lc*lc + err))) 
				{ 
					okflag = 1; 

					ccx_abeyance1[i] = m_blindNode.x; 
					ccy_abeyance1[i] = m_blindNode.y; 
					n++; 
				} 
			} 
			if(!okflag)err++; 
		} while (okflag == 0); 
		i++; 
		err = 0; 
		okflag = 0; 
	}  
	//��ĿǰΪֹ��abeyance�д�ŵ���A,B,C�ڵ�����δ֪�ڵ�Z�Ŀ�������ֵ
	do 
	{ 
		//��ab ���㣬��Ϊ�����ƫ������������ƫ�� 
		aberr =0; 
		do 
		{ 
			for(i = 0;i <= 2*la;i++) 
			{ 
				for(j = 0;j <= 2*lb;j++) 
				{ 
					if(fabs(cax_abeyance1[i] - cbx_abeyance1[j])< 10) //��A��B�ֱ����ʱ�����Z������ֵ��x������ͬʱ
					{ 
						if(fabs(cay_abeyance1[i] - cby_abeyance1[j])< 10) 
						{ 
							cabx_abeyance1[abrequery] = cax_abeyance1[i]; 
							caby_abeyance1[abrequery] = cay_abeyance1[i]; 
							abrequery++; 
						} 
					} 
				} 
			}   
			if(abrequery < loopnum)aberr++; 
		}while(abrequery < loopnum); 
		acerr =0; 
		//��ac ���� 
		do 
		{ 
			for(i = 0;i <= 2*la;i++) 
			{ 
				for(j = 0;j <= 2*lc;j++) 
				{ 
					if(fabs(cax_abeyance1[i] - ccx_abeyance1[j])< 10)
					{ 
						if(fabs(cay_abeyance1[i] - ccy_abeyance1[j])< 10)
						{ 
							cacx_abeyance1[acrequery] = cax_abeyance1[i]; 
							cacy_abeyance1[acrequery] = cay_abeyance1[i]; 
							acrequery++; 
						} 
					} 
				} 
			} 
			if(acrequery < loopnum)acerr++; 
		}while(acrequery < loopnum); 
		//�ҽ���Ľ��� 
		for(i = 0;i < abrequery;i++) 
		{ 
			for(j = 0;j < acrequery;j++) 
			{ 
				if(fabs(cabx_abeyance1[i] - cacx_abeyance1[j]) <10)
				{ 
					requery1 = 1; 
					m_blindNode.x = cabx_abeyance1[i];
					m_blindNode.y = caby_abeyance1[i];
				} 
			} 
		} 
		if(requery1 == 0) 
		{ 
			loopnum++; 
			abcerr++; 
		} 
		if(loopnum == 10) 
		{ 
			AfxMessageBox("chech input figure is right\n"); 
			exit(-1);
		} 
	}while(requery1 ==0); 
}  


void CPositioningDlg::OnBnClickedBtnPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bCommunFlag = false;
	m_Port.ClosePort();
	UpdateData(TRUE);//��ȡ�ؼ���صı���ֵ
}
