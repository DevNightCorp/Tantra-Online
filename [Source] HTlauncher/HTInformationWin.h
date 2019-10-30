#ifndef _HTInformationWin_H
#define _HTInformationWin_H

#define HT_INFORMATIONWIN_NUM_MAX		4	// ��� �� �ִ� �ִ� ����

typedef struct _INFORMATIONWIN
{	
	HTbool		bInformationWin_Dlg;
	HTint		iInductNo;
} INFORMAIONTWIN;

class CHTInformationWin
{
public:
	CHTInformationWin(void);
	~CHTInformationWin(void);

	HTvoid		HT_vInformationWin_SetActive( HTchar* pStr, HTint iInductNo = -1 );
	HTvoid		HT_vInformationWin_SetAntiActive( HTint iDlgNo );
	HTvoid		HT_vInformationWin_SetAntiActiveWithInductNo( HTint iInductNo );

	//	���콺 üũ
	HTRESULT	HT_hrInformationWin_DlgCheck( HTint iDlgNo, HTint iProp );

private:
	HTbool		m_bInformationWin_DlgSw;
	// ���ÿ� �������� ����â�� �� �� �ְ� �ϱ� ���ؼ�.
	INFORMAIONTWIN		m_bInformationWin_Dlg[HT_INFORMATIONWIN_NUM_MAX];
};

#endif // #ifndef _HTInformationWin_H