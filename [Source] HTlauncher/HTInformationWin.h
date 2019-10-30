#ifndef _HTInformationWin_H
#define _HTInformationWin_H

#define HT_INFORMATIONWIN_NUM_MAX		4	// 띄울 수 있는 최대 개수

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

	//	마우스 체크
	HTRESULT	HT_hrInformationWin_DlgCheck( HTint iDlgNo, HTint iProp );

private:
	HTbool		m_bInformationWin_DlgSw;
	// 동시에 여러개의 공지창이 뜰 수 있게 하기 위해서.
	INFORMAIONTWIN		m_bInformationWin_Dlg[HT_INFORMATIONWIN_NUM_MAX];
};

#endif // #ifndef _HTInformationWin_H