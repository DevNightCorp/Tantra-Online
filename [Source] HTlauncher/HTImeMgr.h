#pragma once

#include "wapi.h"

class HTImeMgr
{
public:
	HTImeMgr(void);
	~HTImeMgr(void);

private:
	int GetIMEName(void);
	int GetIMECandidate(void);
	int GetIMEComposition(void);
	int ClearComposition(void);
	int ClearCandidateList(void);

//----------------------------------------------------------------------------------------
private:
	HWND m_hWnd; 
	//	Property
	DWORD  m_dwProperty;
	//	Input Lang
	char   m_szInputLang[256];	//渴흙랬츰냔
	DWORD  m_dwInputTextlen;
	DWORD  m_dwCompStrLen;
	DWORD  m_dwCompReadStrLen;
	
	MYCHAR m_szInputTextStr[512];
	MYCHAR m_szCompStr[512];
	MYCHAR m_szCompReadStr[512];	

	//	저장해야될 wParam
	WPARAM m_wParam;
	
	//	CandiList
	//	CandiList Total Count
	DWORD	m_dwCandiCount;
	//	CandiList Selection Noumber
	DWORD	m_dwCandiSelectionNo;
	//	CandiList PageStart Noumber
	DWORD	m_dwPageStartNo;
	//	CandiList PageSize Count
	DWORD	m_dwPageSize;
	// Curry Real CandiList Number (0-10)
	DWORD	m_dwCandidateListNo;
	//	CandidateList String
	MYCHAR	m_szCandidateStr[10][64];

	//	일본어를 위한 전각 반각 모드
	BOOL	m_bEmForJapan;

	//	이후 몇바이트까지는 받지 말아 달라고....요청
	BYTE	m_byLimitRecivewParam;


public:

	int InitInput(HWND hWnd);
	void InitString();
	int InputString();

	int OnChar(WPARAM wParam, LPARAM lParam);
	int OnInputLangChange(WPARAM wParam, LPARAM lParam);
	int OnStartComposition(WPARAM wParam, LPARAM lParam);
	int OnEndComposition(WPARAM wParam, LPARAM lParam);
	int OnComposition(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnImeNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
	int SetIMEPos(HIMC hIMC);

	//	Set Language
	void	vImeMgr_SetLanguage( BOOL bAutoSet, DWORD dwLanguageCode );

	//	Returns
	//	Return Property
	DWORD	dwXInput_Property()						{	return m_dwProperty;			};
	//	Return InputLang
	char*	szXInput_InputLang()					{	return m_szInputLang;			};
	
	//	Set Emm for Japan
	BOOL	bImeMgr_GetEmForJapan()					{	return m_bEmForJapan;			};
	//	Return Emm for Japan
	void	bImeMgr_SetEmForJapan( int iImeIndex );
	//	Set Ime Mode Cancel
	void	vImeMgr_SetImeModeCancel();

	//
	DWORD	dwXInput_LenInputText()					{	return m_dwInputTextlen;		};
	DWORD	dwXInput_LenCompStr()					{	return m_dwCompStrLen;			};
	DWORD	dwXInput_LenCompReadStr()				{	return m_dwCompReadStrLen;		};
	DWORD	dwXInput_CandiCount()					{	return m_dwCandiCount;			};
	DWORD	dwXInput_CandiSelectionNo()				{	return m_dwCandiSelectionNo;	};
	DWORD	dwXInput_PageStartNo()					{	return m_dwPageStartNo;			};
	DWORD	dwXInput_PageSize()						{	return m_dwPageSize;			};
	DWORD	dwXInput_CandidateListNo()				{	return m_dwCandidateListNo;		};

	//
	MYCHAR*	szXInput_InputText()					{	return m_szInputTextStr;		};
	MYCHAR*	szXInput_CompStr()						{	return m_szCompStr;				};
	MYCHAR*	szXInput_CompRead()						{	return m_szCompReadStr;			};

	//	
	WPARAM	wImeMgr_WPARAM();

	void	vHTImeMgr_Setm_szInputTextStr( MYCHAR* szText );

	void	SetIMEWndPos();
	//	이후 몇바이트까지는 받지 말아 달라고....요청
	void	vImeMgr_SetLimitRecivewParam( BYTE byLimitCount );
};
