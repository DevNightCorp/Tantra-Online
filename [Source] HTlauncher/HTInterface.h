#pragma once

// Interface.h
#ifndef _HTINTERFACE_H
#define _HTINTERFACE_H

#define _INTERFACE_VERSION		2005
#define _INTERFACE_SAVE_FILE_NAME	_T("resource\\UI\\Interface.sys")		// ��Ʈ�� ���� ���� ���� �̸�

// Message Procedure Define
typedef void func_t(int, int, int);		// �� UI System���� ����ϴ� �Լ������� (�޽��� ���ν��� �Լ���)

// iAction Type
#define	UI_ACTION_MOUSE_L_DOWN		0		// ���콺 L�ٿ��
#define	UI_ACTION_MOUSE_L_UP		1		// ���콺 L����
#define	UI_ACTION_MOUSEMOVE			2		// ���콺 �����
#define	UI_ACTION_MOUSE_R_DOWN		3		// ���콺 R�ٿ��
#define	UI_ACTION_MOUSE_R_UP		4		// ���콺 R����
#define	UI_ACTION_MOUSE_LBCLK		5		// ���콺 L����Ŭ����
#define	UI_ACTION_MOUSE_RBCLK		6		// ���콺 R����Ŭ����
#define	UI_ACTION_MOUSE_LCLK		7		// ���콺 LŬ��
#define	UI_ACTION_MOUSE_RCLK		8		// ���콺 RŬ��

// iTarget Type
#define	UI_TARGET_BUTTON		0		// ��ư
#define	UI_TARGET_EDITBOX		1		// �����͹ڽ�
#define	UI_TARGET_SCROLLBAR		2		// ��ũ�ѹ�
#define	UI_TARGET_MESSAGEBOX	3		// �޽����ڽ�
#define	UI_TARGET_SLOTBOX		4		// ���Թڽ�
#define	UI_TARGET_TIMER			5		// Ÿ�̸�


// MessageBox STYLE ����
#define	UI_MESSAGEBOX_CONFIRM		0		// Ȯ��â  (Ȯ�� = 2)
#define	UI_MESSAGEBOX_RECONFIRM		1		// ��Ȯ��â (Ȯ�� = 2 / ��� = 3)
#define	UI_MESSAGEBOX_NUMBERINPUT	2		// �����Է�â
#define	UI_MESSAGEBOX_INPUT			3		// �Է�â
#define	UI_MESSAGEBOX_CONFIRM_ENTER_NO 4	// ���ͱ�� �ȸ����� Ȯ��â
#define	UI_MESSAGEBOX_COUPON		5		// �����Է�â


// EditBox STYLE ����
#define	UI_EDITBOX_NORMAL			0		// �Ϲݸ��
#define UI_EDITBOX_SMALLCHARACTER	1		// �ҹ����Է¸��
#define UI_EDITBOX_LARGECHARACTER	2		// �빮���Է¸��
#define UI_EDITBOX_ONLYNUMBER		3		// ���� ���ڸ� �Է°��ɸ��

//EditBox Mode ����
#define	UI_EDITBOX_NORMALMODE		0		// �Ϲݸ��
#define UI_EDITBOX_PASSWORDMODE		1		// �н����� �Է¸��

//Magnet State ����
#define UI_MAGNET_DISTANCE			20		// �ڼ� ����� �߻��Ǵ� �ȼ� �Ÿ�
#define UI_MAGNET_DISTANCE_EXIT		25		// �ڼ� ���·� ���� ������ ���� �� �ִ� �ȼ� �Ÿ�

//
// >> UITexture�� �����ϴ� �ּҴ��� <<
//
typedef struct _UITexture
{
	int					PosX;					// Texture PosX (Local Coordinate)
	int					PosY;					// Texture PosY (Local Coordinate)
	int					SizeX;					// Output Texture Size X
	int					SizeY;					// Output Texture Size Y

	int					TextureID;				// Texture ID
	unsigned short		Layer;					// Layer (Z_ODER)
	HT_COLOR			VertexClr;				// Vertex Color

} UITexture;


// 
// >> UIText�� �����ϴ� �ּҴ��� <<
// 
typedef struct _UIText
{
	HT_FONT_TYPE		Font;					// Font Kinds
	int					FontMode;				// Font Style
	HT_TEXT_FORMATING	TextFormating;			// Text Formating
	CHTString			strTitle;				// String
	HT_RECT				TextPos;				// Font Location (Local Coordinate - RECT)
	HT_COLOR			TextColor;				// Fore Color
	HT_COLOR			TextShadowColor;		// Background Color (Shadow Color)

} UIText;

// 
// >> Expand UIText�� �����ϴ� �ּҴ��� <<
// 
typedef struct _UILongText
{
	HT_FONT_TYPE		Font;					// Font Kinds
	int					FontMode;				// Font Style
	HT_TEXT_FORMATING	TextFormating;			// Text Formating
	HTtchar				strTitle[1000];			// String
	HT_RECT				TextPos;				// Font Location (Local Coordinate - RECT)
	HT_COLOR			TextColor;				// Fore Color
	HT_COLOR			TextShadowColor;		// Background Color (Shadow Color)

} UILongText;

// 
// >> UI Resource ���� ����ü
//
typedef struct _UIResource
{
	int					XMLID;					// XML ID
	int					RealSizeX;				// Real Output Region Image SizeX
	int					RealSizeY;				// Real Output Region Image SizeY

} UIResource;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Texture Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UITextureControl
{
private:
	// Texture Information
	UITexture			m_Texture;				// �ؽ�ó �⺻ ������
	HTvector3			m_fScale;				// ������ �ؽ�ó �����Ϻ���
	int					m_iWidth;				// ���� �ؽ�ó ������X
	int					m_iHeight;				// ���� �ؽ�ó ������Y
	int					m_iEObjID;				// Engine���� ���� �ο� ���� �ؽ�ó ���� ID��

	// Process
	int					RealSizeX;				// Real Output Region Image SizeX
	int					RealSizeY;				// Real Output Region Image SizeY
	bool				m_bCheckRegion;			// ���� ������ ���콺���� ������ ����
	bool				m_bCheckMouseDown;		// ���� ������ ���콺�ٿ� ������ ����
	bool				m_bCheckMouseRDown;		// ���� ������ ���콺�ٿ� ������ ����

	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����

public:
	unsigned int		m_nIndex;				// ��Ʈ�� ���� �ε���


	UITextureControl();
	virtual ~UITextureControl();

	// ����
	void		CreateUITextureControl(unsigned int nIndex, UITexture oTexture);	// UI Object ����
	UITexture	GetUITextureControl();				// �ؽ�ó ���� ���

	// ���
	void		Render(int iWindowPosX = 0, int iWindowPosY = 0);	
	// ���� �˻�
	bool		CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);
	// �̵�
	void		Move(int iXpos, int iYpos, int iType = 0);				// ���ϴ� ��ġ�� �̵�
	// ����
	void		Show() {m_bDisplay = true;}							// �����ݴϴ�.
	void		Hide() {m_bDisplay = false;}						// ����ϴ�.
	void		EnableOn() {m_bEnable = true;}						// �����ϰ� �մϴ�.
	void		EnableOff() {m_bEnable = false;}					// �������� �ʰ� �մϴ�.
	void		CheckRegion(bool val) {m_bCheckRegion = val;}		// ����� �������� ����
	void		CheckMouseDown(bool val) {m_bCheckMouseDown = val;}	// ����� �������� ����
	void		CheckMouseRDown(bool val) {m_bCheckMouseRDown = val;}	// ����� �������� ����
	void		SetScale(int iSizeX, int iSizeY, int iOSizeX = 1, int iOSizeY = 1);	// ���ϴ� ũ��� ����
	void		SetColor(HT_COLOR clr);						// �ؽ�ó �÷� ����
	void		GetScale(int &iSizeX, int &iSizeY);					// ���� ũ�� ��ȯ

	// ��������
	bool		isRegion() {return m_bCheckRegion;}					// ���� ������ �������ΰ�?
	bool		isMouseDown() {return m_bCheckMouseDown;}			// ���� ������ �������ΰ�?
	bool		isMouseRDown() {return m_bCheckMouseRDown;}			// ���� ������ �������ΰ�?
	bool		isEnableOn() {return m_bEnable;}
	bool		isDisplay() {return m_bDisplay;}
	HTvector3	GetUITextureControlPos();							// ��ġ�� ���´�.
	int			GetTextureID() {return m_Texture.TextureID;}		// �ؽ�ó ���̵� ���´�.
	
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Label Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UILabelControl
{
private:
	// Texture Information
	UIText				m_Text;					// Text ����

	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����

	bool				m_bCheckRegion;			// ���� ������ ���콺���� ������ ����
	bool				m_bCheckMouseDown;		// ���� ������ ���콺�ٿ� ������ ����

	int					TextPosX;				// �ɼ� ����� ���� �ؽ�Ʈ ��ġX
	int					TextPosY;				// �ɼ� ����� ���� �ؽ�Ʈ ��ġY
	int					m_Direction;			// ��ġ���

	void		SetTextArrangement(int iDirection);								// �ش���� ������ ���ϴ� �������� ��ġ�մϴ�.

public:
	unsigned int		m_nIndex;				// ��Ʈ�� ���� �ε���

	UILabelControl();
	virtual ~UILabelControl();

	// ����
	void		CreateUILabelControl(unsigned int nIndex, UIText oText);		// UI Object ����
	// ���
	void		Render(int iWindowPosX = 0, int iWindowPosY = 0);				// Render
	// ���� �˻�
	bool		CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);// ���� ������ ��ġ�Ͽ��°�?
	// �̵�
	void		Move(int iXpos, int iYpos);										// ���ϴ� ��ġ�� �̵�
	// ����
	
	void		SetScale(int SizeX, int SizeY);									// ����� �����մϴ�.
	void		Show() {m_bDisplay = true;}										// ��ư�� �����ݴϴ�.
	void		Hide() {m_bDisplay = false;}									// ��ư�� ����ϴ�.
	void		EnableOn() {m_bEnable = true;}									// ��ư�� �����ϰ� �մϴ�.
	void		EnableOff() {m_bEnable = false;}								// ��ư�� �������� �ʰ� �մϴ�.
	void		CheckRegion(bool val) {m_bCheckRegion = val;}					// ����� �������� ����
	void		CheckMouseDown(bool val) {m_bCheckMouseDown = val;}				// ����� �������� ����
	HT_RECT		GetUILabelControlPos();											// ��ġ�� ���´�.
	CHTString	GetText() {return m_Text.strTitle;}								// ���ڿ��� ��ȯ�Ѵ�. 
	void		SetText(CHTString str);											// ���ڿ��� �����Ѵ�.
	void		SetTextColor(HT_COLOR clr)	{m_Text.TextColor = clr;}			// ���ڿ� ������ �����Ѵ�.
	void		SetTextShadowColor(HT_COLOR clr) {m_Text.TextShadowColor = clr;}// ���ڿ� �׸��� ������ �����Ѵ�.
	void		SetArrangement(int iDirection) {m_Direction = iDirection; SetTextArrangement(iDirection);}		// ���ڿ��� ���ϴ� �������� ��ġ�մϴ�.

	// ��������
	bool		isRegion() {return m_bCheckRegion;}					// ���� ������ �������ΰ�?
	bool		isMouseDown() {return m_bCheckMouseDown;}			// ���� ������ �������ΰ�?

};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Long Label Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UILongLabelControl
{
private:
	// Texture Information
	UILongText			m_Text;					// Text ����

	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����

	bool				m_bCheckRegion;			// ���� ������ ���콺���� ������ ����
	bool				m_bCheckMouseDown;		// ���� ������ ���콺�ٿ� ������ ����

	int					TextPosX;				// �ɼ� ����� ���� �ؽ�Ʈ ��ġX
	int					TextPosY;				// �ɼ� ����� ���� �ؽ�Ʈ ��ġY
	int					m_Direction;			// ��ġ���

	void		SetTextArrangement(int iDirection);								// �ش���� ������ ���ϴ� �������� ��ġ�մϴ�.

public:
	unsigned int		m_nIndex;				// ��Ʈ�� ���� �ε���

	UILongLabelControl();
	virtual ~UILongLabelControl();

	// ����
	void		CreateUILabelControl(unsigned int nIndex, UILongText oText);		// UI Object ����
	// ���
	void		Render(int iWindowPosX = 0, int iWindowPosY = 0);				// Render
	// ���� �˻�
	bool		CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);// ���� ������ ��ġ�Ͽ��°�?
	// �̵�
	void		Move(int iXpos, int iYpos);										// ���ϴ� ��ġ�� �̵�
	// ����
	
	void		SetScale(int SizeX, int SizeY);									// ����� �����մϴ�.
	void		Show() {m_bDisplay = true;}										// ��ư�� �����ݴϴ�.
	void		Hide() {m_bDisplay = false;}									// ��ư�� ����ϴ�.
	void		EnableOn() {m_bEnable = true;}									// ��ư�� �����ϰ� �մϴ�.
	void		EnableOff() {m_bEnable = false;}								// ��ư�� �������� �ʰ� �մϴ�.
	void		CheckRegion(bool val) {m_bCheckRegion = val;}					// ����� �������� ����
	void		CheckMouseDown(bool val) {m_bCheckMouseDown = val;}				// ����� �������� ����
	HT_RECT		GetUILabelControlPos();											// ��ġ�� ���´�.
	HTtchar*	GetText() {return m_Text.strTitle;}								// ���ڿ��� ��ȯ�Ѵ�. 
	void		SetText(HTtchar str[]);											// ���ڿ��� �����Ѵ�.
	void		SetTextColor(HT_COLOR clr)	{m_Text.TextColor = clr;}			// ���ڿ� ������ �����Ѵ�.
	void		SetTextShadowColor(HT_COLOR clr) {m_Text.TextShadowColor = clr;}// ���ڿ� �׸��� ������ �����Ѵ�.
	void		SetArrangement(int iDirection) {m_Direction = iDirection; SetTextArrangement(iDirection);}		// ���ڿ��� ���ϴ� �������� ��ġ�մϴ�.

	// ��������
	bool		isRegion() {return m_bCheckRegion;}					// ���� ������ �������ΰ�?
	bool		isMouseDown() {return m_bCheckMouseDown;}			// ���� ������ �������ΰ�?

};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI ToolTip Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIToolTipControl
{
private:
	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����
	DWORD				m_dToolTipDelayTime;	// ���� ��µǴ� �ð� ����
	DWORD				m_dToolTipStartTime;	// ���� ���۽ð� ����
	unsigned int		m_iLineIndex;			// ���� �ε��� (���ڿ� ����)

	int					m_SizeX;				// ���� ������ X
	int					m_SizeY;				// ���� ������ Y

	UITextureControl*	Body;					// ��׶��� ����
	//UILabelControl*		Text;					// ���� ���� �ؽ�Ʈ

	std::list<UILabelControl*> m_UIToolTipLabelControl;		// ���� ���� �ؽ�Ʈ (�������� ������- Ȯ�� ����)
	

public:
	// [Button]
	unsigned int		m_nIndex;				// ���� ���� �ε���

	// [�Լ�]
	UIToolTipControl();
	virtual ~UIToolTipControl();

	// ����
	void CreateUIToolTipControl(unsigned int nIndex, int iXPos, int iYPos, CHTString str );	// ������ �����մϴ�.
	// ���
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);	// ������ ����մϴ�. (�ؽ�ó)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);	// ������ ����մϴ�. (�ؽ�Ʈ)
	// ���� �˻�
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// ���� �˻�
	// �̵�
	void Move(int iXpos, int iYpos);			// ������ �̵���ŵ�ϴ�.
	// ����
	void SetStartTime();						// ���� �ð� ī��Ʈ�� �����մϴ�.
	void SetText(CHTString str, int nIndex = 1);// ������ ������ �����մϴ�.
	bool CheckOutputTime();						// ������ ����ص� �Ǵ��� ���ξ˸�
	void Show() {m_bDisplay = true; this->SetStartTime();}			// ������ �����ݴϴ�.
	void Hide() {m_bDisplay = false;}			// ������ ����ϴ�.
	void EnableOn() {m_bEnable = true;}			// ������ �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}		// ������ �������� �ʰ� �մϴ�.

	//Ȯ������
	void CreateLabelControl(unsigned int nIndex, UIText oText);			// �� ��Ʈ�� ����
	void DeleteLabelControl(unsigned int nIndex);						// �� ��Ʈ�� ����
	void SetTextLabelControl(unsigned int nIndex, CHTString str);		// �� ��Ʈ���� �ؽ�Ʈ ����
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr);	// �� ��Ʈ���� �ؽ�Ʈ�÷� ����
	void SetTextLabelControlIndex(unsigned int nIndex);					// �ε��� ���� ����


	//void SetToolTipStr(int Index, CHTString str, HT_COLOR clr);		// �ش� ������ ���� ����� ������ �����մϴ�.
	//void AddToolTipStr(int Index);									// Ư�� ��Ʈ�� ���� �ϳ��� �߰��մϴ�.
	//void DelToolTipStr(int Index);									// Ư�� ��Ʈ�� ���� �ϳ��� ���ϴ�.

};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Button Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIButtonControl
{
private:
	
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����
	bool				m_bToolTip;				// true = ���� ��� / false = ���� ������
	bool				m_bEnter;				// true = ���� ��� / false = ���� ������
	int					m_iButtonState;			// 0 = Normal����, 1 = �׻� ���� ����, 2 = �׻� ���� ����, 3 = �����̴� ����, 4 = �ڽ���ư�� (������ TextureID�� -1�� �����Ұ�)

	UITextureControl*	ButtonNormal;			// �Ϲݻ���
	UITextureControl*	ButtonOver;				// ���콺 ��ġ Ÿ�ٽ�
	UITextureControl*	ButtonDown;				// ���콺 ��ư �ٿ��

	DWORD				m_dFlashButtonOnDelayTime;	// Ŀ�� ������ �ð� 0.5���� �ߵ�
	DWORD				m_dFlashButtonOffDelayTime;	// Ŀ�� ������ �ð� 1���� �ߵ�
public:
	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	UIToolTipControl*	ToolTip;				// ��ư ���� ����

	// [Button]
	unsigned int		m_nIndex;				// ��ư ���� �ε���
	int					m_nMode;				// ��¸�� ( 0 = �Ϲ� ��ưó�� ����, 1 = �̻�� )
	int					m_nButtonState;			// ��¸�� ( 0 = �븻, 1 = ����, 2= �ٿ�)
	DWORD				m_dFlashButtonStartTime;	// ������ ��ư ���۽ð�

	// [�Լ�]
	UIButtonControl();
	virtual ~UIButtonControl();

	// ����
	void CreateUIButtonControl(unsigned int nIndex, UITexture oTexture[3] );	// ��ư�� �����մϴ�.
	// ���
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);	// ��ư�� ����մϴ�. (�ؽ�ó)
	void RenderTextureToolTip(int iWindowPosX = 0, int iWindowPosY = 0);	// ������ ����մϴ�. (�ؽ�ó)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);	// ��ư�� ����մϴ�. (�ؽ�Ʈ)

	// ���� �˻�
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// ���� �˻�
	// �̵�
	void Move(int iXpos, int iYpos);				// ��ư�� �̵���ŵ�ϴ�.
	void SetScale(int iSizeX, int iSizeY);			// ���ϴ� ũ��� ����
	// ����
	void Show() {m_bDisplay = true;}				// ��ư�� �����ݴϴ�.
	void Hide() {m_bDisplay = false;}				// ��ư�� ����ϴ�.
	void EnableOn() {m_bEnable = true;}				// ��ư�� �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}			// ��ư�� �������� �ʰ� �մϴ�.

	void SetButtonNormal();
	void SetButtonOver();
	void SetButtonDown();
	
	void SetButtonState(int iCheck) {m_iButtonState = iCheck;}	// ��ư���¸� �����մϴ�.
	void SetToolTipMove(int iXPos, int iYPos);		// ������ �����ġ�� �����մϴ�.
	void SetToolTipStr(CHTString str);				// ������ ������ �����մϴ�.
	void SetToolTipOn() {ToolTip->EnableOn();}		// ������ ������ �մϴ�.
	void SetToolTipOff() {ToolTip->EnableOff();}	// ������ ������ �ʰ� �մϴ�.
	void SetTextLabelControl(unsigned int nIndex, CHTString str) {ToolTip->SetTextLabelControl(nIndex, str);}
	void SetTextLabelControlIndex(unsigned int nIndex) {ToolTip->SetTextLabelControlIndex(nIndex);}
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr) {ToolTip->SetTextColorLabelControl(nIndex, clr);}

	void SetEnterOn() {m_bEnter = true;}			// ����Ű�� ������ ȿ���� �߻���ŵ�ϴ�.
	void SetEnterOff() {m_bEnter = false;}			// ����Ű�� ������ ȿ���� ���ϴ�.


	// ��������
	bool isBackgroundMouseDown() {return this->ButtonNormal->isRegion();}
	bool isEnterOn() {return m_bEnter;}
	bool isEnableOn() {return m_bEnable;}
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI ScrollBar Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIScrollBarControl
{
private:
	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����

	UITextureControl*	Line;					// ���� �ؽ�ó
	UITextureControl*	Image;					// ��ũ�ѹ�

public:
	UIButtonControl*	Arrow1;					// ȭ��ǥ1
	UIButtonControl*	Arrow2;					// ȭ��ǥ2

	unsigned int		m_nPosX;				// ���� X
	unsigned int		m_nPosY;				// ���� Y
	unsigned int		m_nLengthX;				// ���� X
	unsigned int		m_nLengthY;				// ���� Y

	unsigned int		m_nValue;				// ���� ��
	unsigned int		m_nMaxValue;			// �ִ� ��

	unsigned int		m_nIndex;				// ��ư ���� �ε���
	int					m_nType;				// ��¸�� ( 0 = ����, 1 = ���� )

	// [�Լ�]
	UIScrollBarControl();
	virtual ~UIScrollBarControl();

	// ����
	void CreateUIScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType);
	// ���
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);										// ��ư�� ����մϴ�. (�ؽ�ó)
	void RenderTextureToolTip(int iWindowPosX = 0, int iWindowPosY = 0);
	
	// ���� �˻�
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// ���� �˻�
	// �̵�
	void Move(int iXpos, int iYpos);															// ��ũ�ѹٸ� �̵���ŵ�ϴ�.
	void MoveImage(int iXPos, int iYPos);

	void MoveBar(int iXpos, int iYpos);															// ��ũ�ѹ� ��ư�� �̵���ŵ�ϴ�.

	// ����
	void Show() {m_bDisplay = true;}															// ��ũ�ѹٸ� �����ݴϴ�.
	void Hide() {m_bDisplay = false;}															// ��ũ�ѹٸ� ����ϴ�.
	void EnableOn() {m_bEnable = true;}															// ��ũ�ѹٸ� �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}														// ��ũ�ѹٸ� �������� �ʰ� �մϴ�.
	
	void SetMaxValue(int iValue) {m_nMaxValue = iValue; UpdateScrollBar();}
	int	 GetMaxValue() {return m_nMaxValue;}
	void SetValue(int iValue) {m_nValue = iValue; UpdateScrollBar();}
	int	 GetValue() {return m_nValue;}
	void UpdateScrollBar();

	void CheckRegion(bool val) {Image->CheckRegion(val);}		// ����� �������� ����
	void CheckMouseDown(bool val) {Image->CheckMouseDown(val);}	// ����� �������� ����
	//void SetSlotBoxControl(int iTextureID);						// �ش� �ؽ�ó�� �����մϴ�.

	// ��������
	bool		isRegion() {return Image->isRegion();}					// ���� ������ �������ΰ�?
	bool		isMouseDown() {return Image->isMouseDown();}			// ���� ������ �������ΰ�?
	HTvector3	GetUIScrollBarControlPos();							// ��ġ�� ���´�.
	int			GetType() {return m_nType;}							// ��ġ�� ���´�.
	//int			GetUISlotTextureID() {return Image->GetTextureID();}	// �ؽ�ó ���̵� ���´�.

};




// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI SlotBox Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UISlotBoxControl
{
private:
	bool				m_bEnable;				// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;				// true = ��� ���� / false = ��� ����
	bool				m_bFirstMove;			// true = ó�� ������ �õ��� / false = �����̰� �ִ���
	bool				m_bMouseOver;			// true = ���콺�� ������	/ false = ���콺�� �������� ����
	bool				m_bToolTip;				// true = ���� ��� / false = ���� ������
	bool				m_bFixedIcon;			// true = ������ / false = ������ ����

	UITextureControl*	Slot;					// ���� (����)
	UITextureControl*	Fx;						// ��Ÿ�� �ð�ȿ�� �̹���
	UITextureControl*	Enable;					// ��뿩�ο� ���� ȭ�� ǥ�� �̹���
	UITextureControl*	Image;					// ���Կ� �� �ؽ�ó

	UIToolTipControl*	ToolTip;				// ��ư ���� ����

//	int					m_SourWindowNo;

	DWORD				dwDealyTime;					// ������ Ÿ��
	DWORD				dwSetTime;						// ī��Ʈ ���� �ð� ����
	DWORD				dwFrameTime;					// ��Ÿ�� �̹��� ���� ������ �ð�
	DWORD				dwTotalFrameTime;				// ��Ÿ�� �����ð� (���ΰ���)
	int					iCoolTimePos;					// ��Ÿ�� ����ó����
	bool				m_bCoolTime;					// ��Ÿ�� ����

	int					m_AddPosX;						// ���Թڽ����� �߰� �̵��� X��ǥ
	int					m_AddPosY;						// ���Թڽ����� �߰� �̵��� Y��ǥ


public:
	bool				m_bEnableCheck;			// ���Ұ� üũ�� ȭ�鿡 ��¿��� ���� (true = ������ ���, false = ����)
	int					m_nIndex;

		// [�Լ�]
	UISlotBoxControl();
	virtual ~UISlotBoxControl();

	// ����
	void CreateUISlotBoxControl(unsigned int nIndex, UITexture oTexture);// ���Թڽ��� �����մϴ�.
	// ���
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);				// ���Թڽ��� ����մϴ�.
	void RenderTextureToolTip(int iWindowPosX = 0, int iWindowPosY = 0);	// ������ ����մϴ�. (�ؽ�ó)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);	// ��ư�� ����մϴ�. (�ؽ�Ʈ)

	// ���� �˻�
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// ���� �˻�
	// �̵�
	void Move(int iXpos, int iYpos);									// ���Թڽ��� �̵���ŵ�ϴ�.
	void MoveImage(int iXpos, int iYpos);								// ���Թڽ��� �̵���ŵ�ϴ�.

	// ����
	void Show() {m_bDisplay = true;}									// ���Թڽ��� �����ݴϴ�.
	void Hide() {m_bDisplay = false;}									// ���Թڽ��� ����ϴ�.
	void EnableOn() {m_bEnable = true;}									// ���Թڽ��� �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}								// ���Թڽ��� �������� �ʰ� �մϴ�.
	void CheckRegion(bool val) {Slot->CheckRegion(val);}				// ����� �������� ����
	void CheckMouseDown(bool val) {Slot->CheckMouseDown(val);}			// ����� �������� ����
	void CheckMouseRDown(bool val) {Slot->CheckMouseRDown(val);}		// ����� �������� ����
	void CheckFirstMove(bool val) {m_bFirstMove = val;}					// ó�� �������� �õ��ϴ°� ����üũ
	void CheckMouseOver(bool val) {m_bMouseOver = val;}					// ���콺 ���� ��, ���� �ȵ� üũ
	void SetSlotBoxControl(int iTextureID, int iLayer = 2050 );// �ش� �ؽ�ó�� �����մϴ�.
	void SetSlotBoxCoolTime(DWORD DealyTime, DWORD PastTime = 0);		// ���Թڽ��� ��Ÿ�� ����
	void SetSlotBoxCoolTimeCancel();									// ���Թڽ��� ��Ÿ�� ����
	bool isSlotBoxCoolTime();											// ���Թڽ��� ��Ÿ��������?
	bool isEnableOn() {return m_bEnable;}								// ���� ��밡���Ѱ�?
	bool isFirstMove() {return m_bFirstMove;}
	bool isMouseOver() {return m_bMouseOver;}
	bool isFixedIcon() {return m_bFixedIcon;}
	void SetSlotBoxImageFixed(bool bFixedIcon) {m_bFixedIcon = bFixedIcon;}
	bool CheckTime();													// �ð��� üũ�Ͽ� �ð��� �°� �����̹����� �����մϴ�.
	void SetSlotBoxControlPosImage(int iPosX, int iPosY );				// ���Թڽ��� ������ ��ġ �缳��
	void SetSlotBoxControlEnable(bool bEnable);							// ���Թڽ� ��뿩�� ����

	// ���� ����
	void SetTextLabelControl(unsigned int nIndex, CHTString str) {ToolTip->SetTextLabelControl(nIndex, str);}
	void SetTextLabelControlIndex(unsigned int nIndex) {ToolTip->SetTextLabelControlIndex(nIndex);}
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr) {ToolTip->SetTextColorLabelControl(nIndex, clr);}
	void SetToolTipOn() {ToolTip->EnableOn();}		// ������ ������ �մϴ�.
	void SetToolTipOff() {ToolTip->EnableOff();}	// ������ ������ �ʰ� �մϴ�.
	void ToolTipHide();
	void ToolTipShow();

	// ��������
	bool		isRegion() {return Slot->isRegion();}					// ���� ������ �������ΰ�?
	bool		isMouseDown() {return Slot->isMouseDown();}				// ���� ������ �������ΰ�?
	bool		isMouseRDown() {return Slot->isMouseRDown();}			// ���� ������ �������ΰ�?
	HTvector3	GetUISlotBoxControlPos();								// ��ġ�� ���´�.
	HTvector3	GetUISlotImageControlPos();								// ��ġ�� ���´�.
	int			GetUISlotTextureID() {return Image->GetTextureID();}	// �ؽ�ó ���̵� ���´�.
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI EditBox Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIEditBoxControl
{
private:
	bool				m_bEnable;						// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;						// true = ��� ���� / false = ��� ����
	bool				m_bFocus;						// true = ��Ŀ�� ���� / false = ��Ŀ�� ����
	bool				m_bCursor;						// true = Ŀ�� �� / false = Ŀ�� ����


	DWORD				dwDealyTime;					// ������ Ÿ��
	DWORD				dwSetTime;						// ī��Ʈ ���� �ð� ����

	int					m_Xpos;							// Ŀ�� X��ġ
	int					m_YPos;							// Ŀ�� Y��ġ
	int					m_nMode;						// ��� (0 = �Ϲ� ���, 1 = �н����� ��� ���)

	DWORD				m_dEditBoxCursorOnDelayTime;	// ������ �ڽ� Ŀ�� �� �ð� ����
	DWORD				m_dEditBoxCursorOffDelayTime;	// ������ �ڽ� Ŀ�� ���� �ð� ����
	DWORD				m_dEditBoxStartTime;			// ���� �ð�

	UITextureControl*	Body;							// ����Ʈ �ڽ� ��� (����)
	UITextureControl*	Cursor;							// Ŀ�� �ؽ�ó (����)
	UITextureControl*	ShiftRegion;					// ����Ʈ ���� �ؽ�ó (����)
	UILabelControl*		Text;							// Ÿ��Ʋ ��Ʈ��
	
	void OutputText();
	//HWND				g_hEdit;						// ����Ʈ �ڵ�

public:
	CHTString			m_str;							// ����Ʈ�ڽ��� ���� ���ڿ� str
	bool				m_bRegion;						// true = Ŀ�� �� / false = Ŀ�� ����
	int					m_XPibot;						// Ŀ�� X�Ǻ�
	int					m_ImeNo;						// ��Ŀ�� Ȱ��ȭ�� �Է¸��
	int					m_iLimitTextSize;				// ���� ���� ���� ������

	// [�Լ�]
	UIEditBoxControl();
	virtual ~UIEditBoxControl();

	unsigned int		m_nIndex;						// ��ư ���� �ε���
	
	// ����
	void CreateUIEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle = 0);	// �����͹ڽ��� �����մϴ�.

	// ����
	void Show() {m_bDisplay = true;}										// �����͹ڽ��� �����ݴϴ�.
	void Hide() {m_bDisplay = false;}										// �����͹ڽ��� ����ϴ�.
	void EnableOn() {m_bEnable = true;}										// �����͹ڽ��� �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}									// �����͹ڽ��� �������� �ʰ� �մϴ�.
	void SetFocusOn();														// �����͹ڽ��� �Է»��·� ����ϴ�.
	void SetFocusOff();														// �����͹ڽ��� �ԷºҰ� ���·� ����ϴ�.
	void SetCursorOn() {m_bCursor = true;}									// �����͹ڽ��� Ŀ���� ���̴� ����
	void SetCursorOff() {m_bCursor = false;}								// �����͹ڽ��� Ŀ���� �Ⱥ��̴� ����
	void SetStartTime()	;													// Ŀ�� ������ �ð� ���� �Լ�
	bool CheckOutputTime();													// Ŀ���� ����ص� �Ǵ��� ���ξ˸�
	void SetText(CHTString str);											// �ؽ�Ʈ�� �����մϴ�.
	void UpdateText(CHTString strMsg);										// ���� ��Ʈ���� ������ ������Ʈ�մϴ�.
	void SetTextColor(HT_COLOR clr) {Text->SetTextColor(clr);}				// �ؽ�Ʈ ���� ���� 
	void SetTextShadowColor(HT_COLOR clr) {Text->SetTextShadowColor(clr);}	// �ؽ�Ʈ �׸��ڻ��� ����
	CHTString GetText() {return m_str;}										// �ؽ�Ʈ�� ������ �ɴϴ�.
	void SetMode(int iMode = 0) { m_nMode = iMode; }						// ����Ʈ ��带 �����մϴ�.
	void SetLimitText(unsigned int uiSize);									// �Է� ���� ���̸� �����մϴ�.
	void SetFocusOnIME(int iIME);											// 0 = ����, 1 = �ѱ���, 2 = �̻��

	// �̵�
	void Move(int iXpos, int iYpos);										// �����͹ڽ��� �̵���ŵ�ϴ�.
	void MoveCursor(int iXpos, int iYpos);									// Ŀ���� �̵���ŵ�ϴ�.
	
	// ���� �˻� �� ���
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// ���� �˻�
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);			// �����͹ڽ� ����մϴ�. (�ؽ�ó)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);				// �����͹ڽ� ����մϴ�. (�ؽ�Ʈ)
	
	// ��������
	bool isFocusOn() {return m_bFocus;}										// ���� �Է� �����ΰ�?
	bool isCursorOn() {return m_bCursor;}									// ���� �Է� �����ΰ�?
	bool isBackgroundMouseDown() {return Body->isRegion();}					// ���� ������ ���� �ִ°�?
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Timer Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UITimerControl
{
private:
	bool				m_bEnable;						// true = �Է� ó������ / false = �Է� ó������

public:
	bool				m_OnlyOne;						// true = �ѹ��� ����� // false = �ݺ���
	DWORD				dwDealyTime;					// ������ Ÿ��
	DWORD				dwSetTime;						// ī��Ʈ ���� �ð� ����
	unsigned int		m_nIndex;						// Ÿ�̸� ���� �ε���

	UITimerControl();
	virtual ~UITimerControl();
	
	// ����
	void CreateUITimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle = 0);	// Ÿ�̸Ӹ� �����մϴ�.
	void EnableOn() {m_bEnable = true; dwSetTime = timeGetTime();}						// Ÿ�̸Ӹ� �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}												// Ÿ�̸Ӹ� �������� �ʰ� �մϴ�.
	bool CheckTime(); 
	void SetRepeat(bool OnlyOne) {m_OnlyOne = OnlyOne;}									// �ݺ����� ���� ����
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI CheckBox Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UICheckBoxControl
{
private:
	bool				m_bEnable;						// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;						// true = ���� / false = ����������
	
	UITextureControl*	Body;							// üũ�ڽ� �̹��� / ����
	UITextureControl*	Check;							// üũ �̹���

public:
	int					m_nIndex;
	bool				m_bValue;						// üũ ����

	UICheckBoxControl();
	virtual ~UICheckBoxControl();
	
	// ����, ����
	void CreateUICheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue = false, int BorderTextureID = 143, int CheckTextureID = 175, int SizeX = 14, int SizeY = 14);	// üũ�ڽ��� �����մϴ�.
	void EnableOn() {m_bEnable = true;}								// üũ�ڽ� ��밡��
	void EnableOff() {m_bEnable = false;}							// üũ�ڽ� ���Ұ�
	void Show() {m_bDisplay = true;}								// üũ�ڽ� ���
	void Hide() {m_bDisplay = false;}								// üũ�ڽ� ��¾���
	bool GetValue() {return m_bValue;}								// ���� �� ���� �˱�
	void SetValue(bool bValue);										// ���� �� ����

	// �̵�, ���
	void Move(int iXpos, int iYpos);															// �̵�
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// �����˻�
	bool isMouseDown() {return Body->isMouseDown();}
	void CheckMouseDown(bool bCheck) {Body->CheckMouseDown(bCheck);}
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);								// ����

};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Window
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIWindow
{
private:
	unsigned int		m_nMaxTextureControl;
	unsigned int		m_nMaxButtonControl;
	unsigned int		m_nMaxLabelControl;
	unsigned int		m_nMaxEditBoxControl;

	bool				m_bEnable;						// true = �Է� ó������ / false = �Է� ó������
	bool				m_bDisplay;						// true = ��� ���� / false = ��� ����
	bool				m_bFocus;						// ���� Ȱ��ȭ �������� �ƴ��� �����Ѵ�.
	bool				m_bSlotBox;						// true = ���Թڽ� �̵��� / false = �̵�����
	bool				m_bMovingRegionUsing;			// �߰� ������ ���ɿ��� ��� ���� 

	
	UITextureControl*	MovingRegion;					// ������ ���ɿ��� 
	UITextureControl*	TitleBar;						// Ÿ��Ʋ�� ���� ��ü (�����츦 ������ �� �ִ� �κ� - ����)
	UITextureControl*	ScaleBar;						// ������ ���� ��ü (����)
	UIButtonControl*	CloseButton;					// â�ݱ� ��ư (����)
	UILabelControl*		TitleStr;						// Ÿ��Ʋ ��Ʈ��

	// [Add Controls]
	std::list<UITextureControl*> m_UITextureControl;	// Picture Box Controls
	std::list<UIButtonControl*> m_UIButtonControl;		// Button Controls
	std::list<UILabelControl*> m_UILabelControl;		// Label Controls
	std::list<UILongLabelControl*> m_UILongLabelControl;// Long Label Controls
	std::list<UIEditBoxControl*> m_UIEditBoxControl;	// EditBox Controls
	std::list<UISlotBoxControl*> m_UISlotBoxControl;	// SlotBox Controls
	std::list<UIScrollBarControl*> m_UIScrollBarControl;// ScrollBar Controls
	std::list<UITimerControl*> m_UITimerControl;		// Timer Controls
	std::list<UICheckBoxControl*> m_UICheckBoxControl;	// CheckBox Controls


	// [��� ����]
	int					iMouseButtonDownXPos;			// �ش� �����쳻�� ���콺 ��ǥ��X
	int					iMouseButtonDownYPos;			// �ش� �����쳻�� ���콺 ��ǥ��Y
	int					iMouseButtonDownXPosTail;		// �ش� �����쳻�� ���콺 ��ǥ��X (����ǥ�κ��� ����)
	int					iMouseButtonDownYPosTail;		// �ش� �����쳻�� ���콺 ��ǥ��Y (����ǥ�κ��� ����)
	int					m_nMode;						// ��¸�� ( 0 = ����, 1 = �Ϲ�â(����) )
	func_t*				m_ptr;							// ������ �޽���ó���� ���� �Լ� ������

	std::list<unsigned int> m_UIMagnetIndex;				// �ڽ��� �ڼ����� ����ϴ� �ٸ� �������
	bool					m_bMagnet;						// �ڼ���� ��� ����
	bool					m_bMagnetUsingPro;					// ���� ó����
	bool					m_bMagnetUsing;					// ���� �ڼ� �۵�������?
	int						m_iMagnetWindowIndex;			// �ڼ����� �ۿ��ϴ� ������ �ε���

public:
	UITextureControl*	Body;							// ������ ���� ��ü (����)

	// ����
	int BackgroundMove;

	// [Window]
	bool					m_bBackgroundDownEnable;		// ������ ��� Ŭ�� ���ɿ��� ����
	int						m_posX, m_posY;					// �ڼ���� ��ġ ����� ���� ����
	int						AdxPosX, AdxPosY;				// ������ �󸶳� ���������� �׾��� �����ϴ� ����
	int						AdxPosX2, AdxPosY2;

	unsigned int		m_nIndex;						// ������ ���� �ε���
	int					iWindowPosX;					// �ش� ������ ���� ��ǥ��X
	int					iWindowPosY;					// �ش� ������ ���� ��ǥ��Y

	// [�Լ�]
	UIWindow();
	virtual ~UIWindow();

	void CreateUIWindow(unsigned int nIndex, CHTString str, int iPosX, int iPosY, int iSizeX, int iSizeY, HT_COLOR dwColor, func_t* ptr, int nMode = 0);	// �����츦 �����մϴ�.
	func_t* GetMessageProcedure();									// �޽��� ���ν����� �Լ� �����͸� ��ȯ�մϴ�.
	void SetBorderTexture(int iSizeX, int iSizeY, int nType = 0);	// �������� �⺻ �׵θ� �������� �����մϴ�.
	void Render();													// �����츦 ����մϴ�.
	void Render_ToolTip();											// 2�� ���� �Լ� (�������� �ֻ��� �����츦 �����մϴ�.)
	void MoveWindow(int iXpos, int iYpos);							// �����츦 �̵���ŵ�ϴ�.
	void ScaleWindow(int iSizeX, int iSizeY);						// �������� ����� �����մϴ�.
	void Show() {m_bDisplay = true;}								// �����츦 �����ݴϴ�.
	void Hide() {m_bDisplay = false;}								// �����츦 ����ϴ�.
	void EnableOn() {m_bEnable = true;}								// �����츦 �����ϰ� �մϴ�.
	void EnableOff() {m_bEnable = false;}							// �����츦 �������� �ʰ� �մϴ�.
	bool isDisplay() {return m_bDisplay;}							// �������� ���÷��� ���¸� �����մϴ�.
	bool isEnable() {return m_bEnable;}								// �������� ���ۻ��¸� �����մϴ�.

	void SetBackgroundColor(HT_COLOR clr);							// �������� ������ �����մϴ�.
	
	// Magnet
	void SetMagnet(unsigned int nTargetIndex);						// �ڼ���� ���� (0 = ���, -1 = ����ȭ��)
	void MagnetMgr(unsigned int nTargetIndex, bool bInsert);		// Ÿ�� ������ bInsert = true ���� false = ����
	void SetMagnetProcessing();										// Ÿ�� �����쿡 �ٴ��� ó���Ѵ�.
	void SetChildMagnetProcessing();								// �ڽſ��� ���� ��������� ó���Ѵ�.
	bool GetMagnetState() {return m_bMagnetUsing;}					// �ڼ����������� �ƴ����� ��ȯ�Ѵ�.
	void SetMagnetState(bool bState) {m_bMagnetUsing = bState;}		// ���� ���¸� ���� �����մϴ�.

	// Texture
	void CreateTextureControl(unsigned int nIndex, UITexture oTexture);	// ��Ʈ���� �����մϴ�.
	void DeleteTextureControl(unsigned int nIndex);												// ��Ʈ���� �����մϴ�.
	void SetRegionTextureControl(unsigned int nIndex, int iXpos, int iYpos, int iSizeX, int iSizeY);
	void SetTextureControlScale(unsigned int nIndex, int iSizeX = 0, int iSizeY = 0, int iOSizeX = 1, int iOSizeY = 1);
	void SetTextureControlImage(unsigned int nIndex, int iTextureID );				// �ؽ�ó�� �����մϴ�.
	void SetTextureColor(unsigned int nIndex, HT_COLOR clr );						// �ؽ�ó �÷��� �����մϴ�.
	void SetTextureControlDisplay(unsigned int nControlIndex, bool bOn);					// �ؽ�ó ��� �¿��� ���� (true = �� . false = ����)
	HTvector3 GetTextureControlPos(unsigned int nControlIndex);							// �ؽ�ó ��Ʈ�� ��ǥ�� ���ɴϴ�.

	// CheckBox
	void CreateCheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue = false, int BorderTextureID = 143, int CheckTextureID = 175, int SizeX = 14, int SizeY = 14);	// üũ�ڽ��� �����մϴ�.
	void DeleteCheckBoxControl(unsigned int nIndex);												// ��Ʈ���� �����մϴ�.
	void SetCheckBoxControl(unsigned int nIndex, bool bCheck);		// üũ�ڽ��� ���� ����
	bool GetCheckBoxControl(unsigned int nIndex);					// üũ�ڽ��� ���� ����

	// Label
	void CreateLabelControl(unsigned int nIndex, UIText oText);
	void DeleteLabelControl(unsigned int nIndex);
	void SetTextLabelControl(unsigned int nIndex, CHTString str);
	CHTString GetTextLabelControl(unsigned int nIndex);
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetTextShadowColorLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetArrangementLabelControl(unsigned int nIndex, int iDirection);		// ���ڿ��� ���ϴ� �������� ��ġ�մϴ�.

	// LongLabel
	void CreateLongLabelControl(unsigned int nIndex, UILongText oText);
	void DeleteLongLabelControl(unsigned int nIndex);
	void SetTextLongLabelControl(unsigned int nIndex, HTtchar str[]);
	HTtchar* GetTextLongLabelControl(unsigned int nIndex);
	void SetTextColorLongLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetTextShadowColorLongLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetArrangementLongLabelControl(unsigned int nIndex, int iDirection);		// ���ڿ��� ���ϴ� �������� ��ġ�մϴ�.

	// EditBox
	void CreateEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle = 0);
	void DeleteEditBoxControl(unsigned int nIndex);
	void SetTextEditBoxControl(unsigned int nIndex, CHTString str);				// ������ �ڽ��� ���ڸ� �����մϴ�.
	CHTString GetTextEditBoxControl(unsigned int nIndex);						// ������ �ڽ��� ���ڸ� ������ �ɴϴ�.
	void SetEditBoxControlMode(unsigned int nIndex, int iMode = 0);				// ����Ʈ ��带 �����մϴ�.
	void SetEditBoxControlLimitText(unsigned int nIndex, unsigned int uiSize);	// ����Ʈ �ڽ��� ���ڱ��̸� �����մϴ�.
	void SetTextColorEditBoxControl(unsigned int nIndex, HT_COLOR clr);
	void SetTextShadowColorEditBoxControl(unsigned int nIndex, HT_COLOR clr);
	void EditBoxFocusAllOff();
	void EditBoxFocusOff(unsigned int nIndex);
	void EditBoxFocusOn(unsigned int nIndex);
	bool isEditBoxFocusOn(unsigned int nIndex);
	void SetEditBoxFocusOnIME(unsigned int nIndex, int iIME);				// ����Ʈ�ڽ��� ��Ŀ���� ���������� �Է¸�带 ���������մϴ�.

	// SlotBox
	void CreateSlotBoxControl(unsigned int nIndex, UITexture oTexture);
	void DeleteSlotBoxControl(unsigned int nIndex);
	void SetSlotBoxControl(unsigned int nIndex, int TextureID, int iLayer = 2050);
	int	 CheckRegionWithSlotBoxPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// ����ó���� (���� ��ġ�� ������ �����ϴ°�?)
	int	 GetUISlotTextureID(unsigned int nIndex);
	void SetSlotBoxCoolTime(unsigned int nIndex, DWORD DealyTime, DWORD PastTime = 0);	// ���Թڽ��� ��Ÿ�� ����
	void SetSlotBoxCoolTimeCancel(unsigned int nIndex);	// ���Թڽ��� ��Ÿ�� ����
	bool isSlotBoxCoolTime(unsigned int nIndex);		// ���Թڽ��� ��Ÿ��������?
	void SetSlotBoxToolTipOn(unsigned int nControlIndex);// ���Թڽ� ��Ʈ�ѿ��� ������ ����մϴ�.
	void SetSlotBoxToolTipOff(unsigned int nControlIndex);// ���Թڽ� ��Ʈ�ѿ��� ������ ������� �ʽ��ϴ�.
	void SetSlotBoxControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str);// ���Թڽ� ������ �ش� �ؽ�Ʈ ����(���κ�)
	void SetSlotBoxControlTextIndex(unsigned int nControlIndex, unsigned int nIndex);// ���Թڽ� ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
	void SetSlotBoxControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);// ���Թڽ� ���� �ش� ���� �ؽ�Ʈ ���� ����
	void SetSlotBoxControlPosImage(unsigned int nControlIndex, int iPosX = 3, int iPosY = 3);	// ���Թڽ��� ������ ��ġ�� �缳���մϴ�.
	void SetSlotBoxImageFixed(unsigned int nControlIndex, bool bFixedIcon);	// ���Թڽ� ������ ������ ���� ���� ����
	void CancelSlotBoxImageMoving();
	void SetSlotBoxControlEnable(unsigned int nControlIndex, bool bEnable);	// ���Թڽ� ��뿩�� ����


	// ScrollBar
	void CreateScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType);
	void DeleteScrollBarControl(unsigned int nIndex);
	void SetScrollBarValue(unsigned int nIndex, int iValue);
	void SetScrollBarMaxValue(unsigned int nIndex, int iValue);
	int GetScrollBarValue(unsigned int nIndex);

	// Button
	void SetButtonToolTip(unsigned int nControlIndex, CHTString str);
	void SetButtonToolTipOn(unsigned int nControlIndex);
	void SetButtonToolTipOff(unsigned int nControlIndex);
	void SetButtonControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str);
	void SetButtonControlTextIndex(unsigned int nControlIndex, unsigned int nIndex);
	void SetButtonControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);
	void SetButtonEnterOn(unsigned int nControlIndex);				// �ش� ��ư�� ���ͱ���� ŵ�ϴ�.
	void SetButtonEnterOff(unsigned int nControlIndex);				// �ش� ��ư�� ���ͱ���� ���ϴ�.
	void SetButtonEnable(unsigned int nControlIndex, bool bEnable);
	void CreateButtonControl(unsigned int nIndex, UITexture oTexture[3]);
	void DeleteButtonControl(unsigned int nIndex);
	void SetButtonControlState(unsigned int nIndex, int iCheck);
	
	// Input Interface
	int OnLButtonDown(int iXPos, int iYPos);
	int OnLButtonUp(int iXPos, int iYPos);
	bool OnRButtonDown(int iXPos, int iYPos);
	bool OnRButtonUp(int iXPos, int iYPos);
	bool OnKeyDown(WPARAM wParam);
	bool OnKeyUp(WPARAM wParam);
	bool OnChar(WPARAM wParam);
	bool OnMouseWheel(WPARAM wParam);
	bool OnSysCommand(WPARAM wParam);
	void OnMouseMove(int iXPos, int iYPos);
	void OnMouseMoveOnlyTop(int iXPos, int iYPos);
	
	// Timer
	void CreateTimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle = 0);
	void DeleteTimerControl(unsigned int nIndex);
	void EnableOnTimerControl(unsigned int nIndex);
	void EnableOffTimerControl(unsigned int nIndex);

	// Etc...
	void FocusOn();
	void FocusOff();

	// Window Region
	void SetMovingRegion(bool isOn, int iPosX, int iPosY, int iSizeX, int iSizeY);
	bool isBackgroundMouseDown() {return this->Body->isRegion();}
	bool CheckRegionWithPoint(int iXPos, int iYPos);	// ���� ������ ��ġ�Ͽ��°�?
	HTvector3	GetWindowPos();							// ��ġ�� ���´�.
	HTvector3	GetWindowSize();						// ����� ���´�.

};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << MessageBox Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_MESSAGEBOX = 999;	// �޽����ڽ� �ε��� ����
class CHTUIMessageBox
{
private:

public:
	unsigned int	m_nIndex;								// �޽��� �ڽ� �ε���
	unsigned int	m_nWindowIndex;							// ������ �ε���

	int				m_nMode;								// �޽����ڽ� ��Ÿ��

	CHTUIMessageBox(void);
	~CHTUIMessageBox(void);
	
	void		HT_vMessageBox(unsigned int nIndex, CHTString str, int nMode = 0);		// nMode = 0 Ȯ�ι�ư��, 1 = Ȯ��/��� ��ư, 2 = �̻��...	
	static void HT_hrMessageBox_InputCheck(int iAction, int iTarget, int iTargetID);	// �Է� ó�� �Լ� (UI �Է������)
	void		HT_vCloseMessageBox(int iTargetID);										// �޽����ڽ� ���Ű��� �Լ�
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Status Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_STATUS = _DIALOG_STATUS;	// ����â ������ �ε��� ����
class CHTUIStatus
{

private:
	static void DrawStatusLabel(int x, int y, int id, CHTString str);					// ���ϰ� �۾��ϱ� ���� �Լ�(���� ������)
	void		HT_vNetWork_CSP_REQ_Increase_Chakra(int iBtnNo);						// ��ũ�� ���� ��û ��Ʈ��ũ �Լ�
	
	PS_SCP_CHAR_PARAMS_CHANGE	m_sStatus_CharParms;
	S_SCP_RESP_UPDATE_UI		m_sStatus_CharInfo;

public:
	int					m_MessageBoxType;
	CHTUIStatus(void);
	~CHTUIStatus(void);

	void		HT_vStatus_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vStatus_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vStatus_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrStatus_InputCheck(int iAction, int iTarget, int iTargetID);		// �Է� ó�� �Լ� (UI �Է������)
	static void HT_hrStatus_InputCheck2(int iAction, int iTarget, int iTargetID);		// �Է� ó�� �Լ� (UI �Է������)
	
	HTint		HT_nGetTotalPureChakra();		// ���� �� ��ũ�� ���ɴϴ�.
	HTint		HT_nGetTotalChakra();			// �� ��ũ�� ���ɴϴ�.

	void		HT_hrStatus_IncreaseChakra(int iBtnNo);									// ��ũ�� ������ư Ŭ���� ȣ��Ǵ� �Լ�(����ó���� �̰���)
	void		HT_vStatus_ChangeParams( PS_SCP_RESP_UPDATE_UI info );					// �������ͽ� ���Ž� ����

	CHTString	HT_szStatus_GetTrimuriti(int iTrimuriti);								// �ֽ� ��Ʈ�� ���
	CHTString	HT_szStatus_GetCastClass(int iCaste);									// ī��Ʈ ��Ʈ�� ���
	CHTString	HT_szStatus_GetJobName(int iClass1, int iClass2);						// ���� ��Ʈ�� ���
	CHTString	HT_szStatus_GetTribe(int iTribe);										// ���� ��Ʈ�� ���
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << NPC Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_NPCWINDOW = _DIALOG_NPCWINDOW;	// ����â ������ �ε��� ����
class CHTUINPCWindow
{
private:
public:
	int				m_MessageBoxNo;
	int				m_StartPosY;
	int m_iButton;
	CHTUINPCWindow(void);
	~CHTUINPCWindow(void);

	void		HT_vNPCWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vNPCWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vNPCWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	int			HT_vGetNPCWindow_ButtonNo() {return m_iButton;}								// ��ư���� �����մϴ�.
	static void HT_hrNPCWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// �Է� ó�� �Լ� (UI �Է������)
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Skill Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
typedef struct _SKILL_ICON
{
	HTint						m_iSkillIconNo1[6][4];
	HTint						m_iSkillIconNo2[6][4];
	HTint						m_iSkillIconNo3[6][4];
	HTint						m_iSkillIconNo4[6][4];
	
} _SKILL_ICON;

typedef struct _SKILL_ARROW
{
	HTint						m_iSkillArrow1[6][4];
	HTint						m_iSkillArrow2[6][4];
	HTint						m_iSkillArrow3[6][4];	
	HTint						m_iSkillArrow4[6][4];

} _SKILL_ARROW;

typedef struct _SKILL_INDEX
{
	HTint						m_iSkillIndex1[6][4];
	HTint						m_iSkillIndex2[6][4];
	HTint						m_iSkillIndex3[6][4];	
	HTint						m_iSkillIndex4[6][4];	

} _SKILL_INDEX;

const int UI_WINDOW_SKILL = _DIALOG_SKILL;	// ��ųâ ������ �ε��� ����
class CHTUISkillWindow
{
private:
	CHTString	m_strTitle[4];									// �� �̸� (4���� �̸���)
	CHTString	m_strTribe;										// �� ����

public:
	int							m_SkillTabNo;					// ���� ��ų �� ��ȣ
	_SKILL_ICON					m_oSkillIcon;					// ��ų������ �迭����ü
	_SKILL_ARROW				m_oSkillArrow;					// ��ųȭ��ǥ �迭����ü
	_SKILL_INDEX				m_oSkillIndex;					// ��ų�ε��� �迭����ü
	int							m_ExtraSkillPoint;				// �ܿ� ��ų����Ʈ
	int							m_ExtraTrimutiritiSkillPoint;	// �ܿ� �ֽ� ��ų����Ʈ
	int							m_byLevel;						// ��ų����
	int							m_byPlusLevel;					// �߰����� (ȿ���� ����)
	int							m_iSkillIcon;					// ��ų������ID
	int							m_iSkillArrow;					// ��ų ȭ��ǥ ID
	CHTString					m_strSkillName;					// ��ų�̸�
	CHTString					m_strSkillContents;				// ��ų����
	CHTString					m_strSkillType;					// ��ųŸ�� (�нú� / ��Ƽ��)

	CHTUISkillWindow(void);
	~CHTUISkillWindow(void);

	void		HT_vSkillWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vSkillWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vSkillWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrSkillWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// �Է� ó�� �Լ� (UI �Է������)
	
	bool		HT_vSetSkillInfoblank();					// ��ų���� 0���� ����
	void		HT_vSkillDrawSkill(int iIndex, int iLevel, CHTString strName, CHTString strContemts, CHTString strType);
	void		HT_vSkillDrawTitle(int iIndex);
	void		HT_vSkillSetTitle(int iTribe);
	bool		HT_vGetSkillInfo(int iIndex);
	int			HT_vGetSkillLevel(DWORD iIndex);
	void		HT_vSkillUpdate(int iIndex);
	
	HTint		HT_nGetSkillPoint();						// ��ų ����Ʈ�� ���ɴϴ�.
	HTint		HT_nGetGodSkillPoint();						// �ֽ� ��ų ����Ʈ�� ���ɴϴ�.

	DWORD		HT_vGetSkillIndex(int iSlotNo);				// ���Թ�ȣ�� ��ų �ε����� ���ɴϴ�.
	int			HT_vGetSkillIcon(DWORD iIndex);				// �ε����� ��ų �������� ���ɴϴ�.
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Refine Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_REFINE = _DIALOG_REFINE;	// ����â ������ �ε��� ����
class CHTUIRefineWindow
{
private:

public:
	int			m_SetItemNumber;
	int			m_iWindowIndex[5];
	int			m_iControlIndex[5];

	int			m_iRefineAniNo;				// ���� �ִϸ��̼� �ε��� ��
	int			m_nMessageBoxNo;						// �˾��� �޽��� �ڽ���?

	CHTUIRefineWindow(void);
	~CHTUIRefineWindow(void);

	void		HT_vRefineWindow_WindowHide();												// ����â �����츦 �������� �� �Լ��� ����Ѵ�.
	void		HT_vRefineWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vRefineWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vRefineWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// �Է� ó�� �Լ� (UI �Է������)
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Quest Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define	QUEST_MAX_NUM					60	// ���� 45���� ���
#define QUEST_DESCRIPTION_MAXNUM		60	// ���� 58���� ���

typedef struct _HT_QUEST_DESCRIPTION
{
	BYTE		byIndex;		// ����Ʈ ��ȣ
	CHTString	szTitle;		// ����Ʈ ����
	HTint		nStepNo;		// �ܰ� ����
	HTint		nStepNum[QUEST_DESCRIPTION_MAXNUM];		// �ܰ�
	CHTString	szStepMsg[QUEST_DESCRIPTION_MAXNUM];	// �ܰ躰 UIâ�� ��Ÿ���� ��
} HT_QUEST_DESCRIPTION;


const int UI_WINDOW_QUEST = _DIALOG_QUEST;	// ����Ʈ �ε��� ����
class CHTUIQuestWindow
{
private:
	HT_QUEST_DESCRIPTION		m_sQuestText[QUEST_MAX_NUM];		// ��� ����Ʈ �̸��� �ܰ躰 ���� ���� ����

	CHTString					m_ProgressStr[QUEST_MAX_NUM];		// �������� ����Ʈ�� ����
	CHTString					m_ProgressResultStr[QUEST_MAX_NUM];	// �������� ����Ʈ�� ���󳻿� ����

	CHTString					m_CompleteStr[QUEST_MAX_NUM];		// �Ϸ��� ����Ʈ�� ����
	CHTString					m_CompleteResultStr[QUEST_MAX_NUM];	// �������� ����Ʈ�� ���󳻿� ����
	
	void		vSetInfo(int iTab);									// ȭ�� ���� ����
	int			SetMonsterKillNo(HTint iIndex, HTint StepNo);		// ���� ���ڼ����ִ� �Լ�
	
public:
	int							m_FocusIndex;						// ���� ������ ��� �ε���
	bool						m_bFalshState;						// ���ι� ����Ʈ ��ư ������ üũ
	HTbyte						m_byQuest[MAX_EVENT_FLAG];
	int							m_iLastProgressIndex;				// ������ ������ ����Ʈ �ѹ�
	bool						m_bReQuestItemUsingOne;				// ����Ʈ �ʱ�ȭ �ܵ� ��� ���� üũ

	bool						g_bMoonBang;						// Ư�� ����Ʈ ������ ���� ���� (�ܺο��� ��������)

	CHTUIQuestWindow(void);
	~CHTUIQuestWindow(void);

	void		HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult);		// Ʃ�丮�� ����Ʈ ���� ��û / 2������ ��û
	void		HT_vNetWork_SCP_RESP_Quest_Dialog( PS_SCP_QUEST_DIALOG info );				// ����Ʈ ���� �������� ����
	void		HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] );		// �����κ��� ����Ʈ���� ����
	

	void		HT_vQuestWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vQuestWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vQuestWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrQuestWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// �Է� ó�� �Լ� (UI �Է������)
	void		HT_vQuest_TutorialMsgLoading();												// ����Ʈ �޽��� ������ �ε�
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Merchant Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_MERCHANT = _DIALOG_MERCHANT;	// ����â ������ �ε��� ���� (�Ϲ� ���� ������)
const int UI_WINDOW_MERCHANT_PREMIUM = _DIALOG_MERCHANT_PREMIUM;	// ����â ������ �ε��� ���� (�����̾� ������)

class CHTUIMerchantWindow
{
private:
	
public:
	bool		m_bWindowType;			// True = �����̾� ���� / False = �Ϲ� ����
	CHTString	m_strTopic;				// �����̾��ٷ��� �� ����
	CHTString	m_strTitle[5];			// ��Ʈ�� Ÿ��Ʋ
	int			m_iTabNo;				// �����̾� ������ �� �ε���
	int			m_iScrollValue;			// �����̾� ������ ��ũ�ѹ� ��

	int			m_ItemIndex[60];		// �Ǹ��� ������ ����Ʈ�� �ε��� ���� ����
	int			m_iNPCIndex;			// �ش� NPC �ε���
	int			m_dwBuyItem;			// ������ ������ �ε���
	int			m_dwSellItem;			// ������ ������ �ε���
	int			m_dwBuyItemCount;		// ������ ������ ����
	int			m_ItemCash;				// ������ ������ ���� (���Ǿ� / ĳ��)
	int			m_MyCash;				// ���� ������ �ִ� �� (���Ǿ� / ĳ��)

	int			m_MessageCode;			// �޽��� �ڽ� ������ ���� ���� (���� ó����)

	// [Initialize Functions]
	CHTUIMerchantWindow(void);
	virtual ~CHTUIMerchantWindow(void);

	void		HT_CheckWindowType(bool bType) {m_bWindowType = bType;}							// Ÿ�� ����
	bool		HT_isWindowType() {return m_bWindowType;}										// ������ Ÿ�� ���
	
	void		HT_vMerchantWindow_DrawTab(int iTabNo);											// �ܱ׸���

	void		HT_vMerchantWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vMerchantWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vMerchantWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrMerchantWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// �Է� ó�� �Լ� (UI �Է������)
	
	void		HT_vMerchantWindow_SetBuyList();												// ���Ÿ���Ʈ ����
	void		HT_vMerchantWindow_SetBuy(int SlotNo);											// �ش� ������ �����ϱ�
	void		HT_vMerchantWindow_ProcessBuy(int iCount);										// ���� ���� �Է��� ���� �ٽ� ó��.

	void		HT_vNetWork_CSP_Req_Item_Buy();													// ���ſ�û
	void		HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info );						// ��������
	void		HT_vNetWork_CSP_Req_Item_Sell();												// �Ǹſ�û
	void		HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info );					// �Ǹ�����
};

/*
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << MessageBox Processing Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_MESSAGEBOX = _DIALOG_MESSAGEBOX_MGR;	// �޽����ڽ� ó�� ������

class CHTUIMessageBoxWindow
{
private:
public:
	int			m_iMesageNo;
		// [Initialize Functions]
	CHTUIEmblemWindow(void);
	virtual ~CHTUIEmblemWindow(void);

	void		HT_vMessageBoxWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vMessageBoxWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vMEssageBoxWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrMessageBoxWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// �Է� ó�� �Լ� (UI �Է������)
}
*/

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Emblem Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_EMBLEM = _DIALOG_AMBLEM;	// �ں� ���� ������

class CHTUIEmblemWindow
{
private:
public:
	int			m_iTabNo;
	int			m_Index;
	int			m_ScrollBar;

	int			m_GuildMark;
	int			m_Back1;
	int			m_Back2;
	int			m_Title;
	HT_COLOR	m_Color;

	// [Initialize Functions]
	CHTUIEmblemWindow(void);
	virtual ~CHTUIEmblemWindow(void);

	void		HT_vEmblemWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vEmblemWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vEmblemWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrEmblemWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// �Է� ó�� �Լ� (UI �Է������)
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Manager
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class CHTUIManager
{
private:
	std::list<UIWindow*> m_UIList;	// Window ���� ����Ʈ�Դϴ�.

	// �Է� �ܺ� �Լ� ó���� ���� ���� ����
	int m_iAction;
	int m_iTarget;
	int m_iTargetID;

	void		RegisterTextureID(unsigned int nIndex, int XMLID, int RealSizeX, int RealSizeY);	// �ؽ�ó ���
	
public:

	// [ȯ�� ����]
	int m_iScreenX;				// �����ػ� X
	int m_iScreenY;				// �����ػ� Y
	int m_iNationalCode;		// �����ڵ�: 0 = KOREA, 1 = CHINA, 2 = INDONESIA, 3 = PHILIPPINE, 4 = JAPAN, 5 = TAIWAN
	int m_iConnectingServer;	// ���Ӽ���: 0 = TEST SERVER, 1 = MAIN SERVER
	int	m_iGameMode;			// ���Ӹ��: 0 = ���ĸ��, 1 = �����ڸ��

	int m_MousePosX;
	int m_MousePosY;

	int m_nAlphaColor;			// ������ ���� ���� ������
	

	// [Slot Box Info]
	bool				m_bDrawInfoWindow;				// ����â�� �׷����� �ִ������� ����
	unsigned int		m_nSlotBoxWindowIndex;		
	unsigned int		m_nSlotBoxControlIndex;
	unsigned int		m_nSlotBoxTextureID;
	bool				m_bSlotBoxMoving;
	unsigned int		m_nSlotBoxTargetControlIndex;
	unsigned int		m_nSlotBoxTargetWindowIndex;

	// [EditBox Info]
	bool				m_InputState;					// ���� UI�� �Է»������� ���� ����

	bool				m_bBackgroundPos;				// ���콺 ��ġ ��׶��� �� Ʈ��, ������� �޽�
	bool				m_bCheckRender;					// UI ���� �� ���� ����
	bool				HT_isRenderOn() {return m_bCheckRender;}	// �������ΰ�?
	void				HT_RenderOn();					// UI �����ϱ�
	void				HT_RenderOff();					// UI �������� ����

	UIWindow*	FindWindowPointer(unsigned int nIndex);	// �ε������� ���ڷ� �ش� Window Pointer ��ȯ
	void		TopWindow(unsigned int nIndex);			// �ش� �ε��� �����츦 ž(���� ���� ������)���� �����ϴ�.
	void		BottomWindow(unsigned int nIndex);		// �ش� �ε��� �����츦 ����(���� ���� ������)�� �����ϴ�.

	// [NPC & MOB]
	HTvector3					iRenderNPCPos;
	CHTString					strRenderNPCName;
	bool						bRenderNPC;				// ���콺 ������ ���ͳ� NPC �̸� ��� ���� ����

	// [MessageBox]
	CHTString					m_strMessageBoxText;			// �Է� �ؽ�Ʈ ����

	// [Windows]
	CHTUIMessageBox				UIMessageBoxMgr;				// �޽��� �ڽ� ���� Ŭ����

	//CHTUISlotInformationWindow	g_cUISlotInformationWindow;		// ���� ����â (TOOLTIP Ȯ��)

	// [Initialize Functions]
	CHTUIManager(void);
	virtual ~CHTUIManager(void);

	void HTSetGameEnvironment(int iScreenX, int iScreenY, int iNationalCode, int iConnectingServer, int iGameMode, int iResource = 0);


	// [UI OutPut Functions]
	void HT_Render();								// ��� �����츦 ������� ����մϴ�. (������ �ʿ��� �κ� �������� �����մϴ�.)


	// [Window Functions]
	void HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode);
	void HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode, HT_COLOR clrBackground);
	void HT_DeleteWindow(unsigned int nIndex);		// �ش� �����츦 �����մϴ�.
	bool HT_isShowWindow(unsigned int nIndex);		// �ش� �����찡 ���� ������ΰ�?
	bool HT_isBackgroundDownEnable(unsigned int nIndex);	// ��׶��� ���� ������ �� ���� �����ΰ�?
	void HT_SetBackgroundDownEnable(unsigned int nIndex, bool bEnable);	// ��׶��� ���� ������ �� ���ɿ��� ����
	void HT_SetBackgroundColor(unsigned int nIndex, HT_COLOR clr);		// �������� ������ �����մϴ�.

	// [Texture Control Processing Functions]
	void HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture);	// �ؽ�ó ��Ʈ���� �߰��մϴ�.
	void HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer = 1400, int iSizeX = 0, int iSizeY = 0);	// �ؽ�ó��Ʈ���� �߰��մϴ�.
	void HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, HT_COLOR clr, int iSizeX = 0, int iSizeY = 0, int iLayer = 1400);	// �ؽ�ó��Ʈ���� �߰��մϴ�.
	void HT_SetTextureControlScale(unsigned int nWindowIndex, unsigned int nControlIndex, int iSizeX = 0, int iSizeY = 0, int iOSizeX = 1, int iOSizeY = 1);	// �ؽ�ó��Ʈ���� �߰��մϴ�.
	void HT_SetTextureControlImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID );				// �ؽ�ó�� �����մϴ�.
	void HT_SetTextureControlColor(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr );				// �ؽ�ó�� ������ �����մϴ�.
	void HT_SetTextureControlDisplay(unsigned int nWindowIndex, unsigned int nControlIndex, bool bOn);					// �ؽ�ó ��� �¿��� ���� (true = �� . false = ����)
	void HT_DelTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex);	// ��Ʈ���� �����մϴ�.
	HTvector3 HT_GetTextureControlPos(unsigned int nWindowIndex, unsigned int nControlIndex);	// ��Ʈ���� ��ġ�� ���ɴϴ�.

	
	// [SlotBox Control Processing Functions]
	void HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture);	// ���Թڽ� ��Ʈ���� �߰��մϴ�.
	void HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer = 2000, int iSizeX = 0, int iSizeY = 0);	// ���Թڽ� ��Ʈ���� �߰��մϴ�.
	void HT_DelSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);			// ���Թڽ� ��Ʈ���� �����մϴ�.
	void HT_GetSlotBoxControlSourInfo(unsigned int &nWindowIndex, unsigned int &nControlIndex, int &TextureID);		// ���Թڽ��� �Ű������� ���� ��ġ�� ������ ������ �ɴϴ�.
	void HT_SetSlotImage(unsigned int nWindowIndex, unsigned int nControlIndex, int TextureID, int iLayer = 2050);		// ���ϴ� ���Թڽ��� �̹����� ���Դϴ�.
	bool CheckRegionWithSlotBoxPoint(unsigned int nWindowIndex, unsigned int nControlIndex, int iXPos, int iYPos, int iTargetID);	// �����̹����� � ������ ���Կ� ���ִ��� �����մϴ�. (����ó����)
	void HT_SetSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD DealyTime, DWORD PastTime = 0);	// ���Թڽ��� ��Ÿ�� ����
	void HT_SetSlotBoxCoolTimeCancel(unsigned int nWindowIndex, unsigned int nControlIndex);	// ���Թڽ��� ��Ÿ�� ����
	bool HT_isSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex);		// ���Թڽ��� ��Ÿ��������?
	void HT_AcceptSlotImageMoving();		// ���Թڽ��� �̹��� �ű�� ����
	void HT_RefuseSlotImageMoving();		// ���Թڽ��� �̹��� �ű�� ����
	void HT_SetSlotBoxToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex);// �ش� �������� ���Թڽ� ��Ʈ�ѿ��� ������ ŵ�ϴ�.
	void HT_SetSlotBoxToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex);// �ش� �������� ���Թڽ� ��Ʈ�ѿ��� ������ ���ϴ�.
	void HT_SetSlotBoxControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str);// ���Թڽ� ������ �ش� �ؽ�Ʈ ����(���κ�)
	void HT_SetSlotBoxControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex);// ���Թڽ� ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
	void HT_SetSlotBoxControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);// ���Թڽ� ���� �ش� ���� �ؽ�Ʈ ���� ����
	void HT_SetSlotBoxControlPosImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX = 3, int iPosY = 3);	// ���Թڽ��� ������ ��ġ�� �缳���մϴ�.
	void HT_SetSlotBoxImageFixed(unsigned int nWindowIndex, unsigned int nControlIndex, bool bFixedIcon);	// ���Թڽ� ������ ������ ���� ���� ����
	void HT_CancelSlotBoxImageMoving();						// ���� ������ �������� �������·� �ǵ����ϴ�.
	void HT_SetSlotBoxControlEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable);	// ���Թڽ��� ��뿩�� ���� (0=���Ұ�, 1=��밡��)



	// [ScrollBar Control Processing Functions]
	void HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType = 0);
	void HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX, int iPosY, int iLength, int iMaxValue = 100, int iType = 0, int iStyle = 0);	// ��ũ�ѹ� ��Ʈ���� �߰��մϴ�.
	void HT_SetScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// ��ũ�ѹ� ��Ʈ�ѿ� ���� �ֽ��ϴ�.
	void HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// ��ũ�ѹ� ��Ʈ�ѿ� �ִ� ���� ���� �մϴ�.
	int HT_GetScrollBarValue(unsigned int nWindowIndex, unsigned int nControlIndex);				// ��ũ�ѹ� ��Ʈ���� ���� ������ �ɴϴ�.
	void HT_DelScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex);			// ��ũ�ѹ� ��Ʈ���� �����մϴ�.


	// [Label Control Processing Functions]
	void HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY);	// ���� �߰��մϴ�.
	void HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iStringNo, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY);
	void HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UIText oText);			// ���� �߰��մϴ�.
	void HT_DelLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);							// ���� �����մϴ�.
	void HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);		// ���� ���ڿ��� �����մϴ�.
	void HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int strindex);
	CHTString HT_GetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� �������� ����Ʈ�ѷ� ���� ��Ʈ���� ���ɴϴ�.
	void HT_SetArrangementLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection);		// ���� ���ڿ��� ���ϴ� �������� ��ġ �մϴ�.
	void HT_SetTextColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);
	void HT_SetTextShadowColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);

	// [Long Label Control Processing Functions]
	void HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[], int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY);	// ���� �߰��մϴ�.
	void HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UILongText oText);			// ���� �߰��մϴ�.
	void HT_DelLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);							// ���� �����մϴ�.
	void HT_SetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[]);		// ���� ���ڿ��� �����մϴ�.
	HTtchar* HT_GetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� �������� ����Ʈ�ѷ� ���� ��Ʈ���� ���ɴϴ�.
	void HT_SetArrangementLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection);		// ���� ���ڿ��� ���ϴ� �������� ��ġ �մϴ�.
	void HT_SetTextColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);
	void HT_SetTextShadowColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);


	// [EditBox Control Processing Functions]
	void HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iSizeX = 0, int iSizeY = 0, int iStyle = 0, int iLayer = 1500);	// �����͹ڽ��� �����մϴ�.
	void HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture, UIText oText, int iStyle = 0);	// ������ �ڽ��� �����մϴ�.
	void HT_DelEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);									// ������ �ڽ��� �����մϴ�.
	void HT_SetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);				// �����͹ڽ��� ���ڸ� �����մϴ�.
	void HT_SetTextColorEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);			// �����͹ڽ��� ���ڻ����� �����մϴ�.
	void HT_SetTextShadowColorEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);		// �����͹ڽ��� ���� �׸��ڻ����� �����մϴ�.
	void HT_SetModeEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iMode = 0);				// �����͹ڽ��� ��¸�带 �����մϴ�. ( 0 = �Ϲ�(�⺻) , 1 = *���(�н����� �Է¹��), 2 = �����Է½� �ڵ� �޸� ���Ը�� )
	void HT_FocusOffEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	void HT_FocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	bool HT_isFocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	CHTString HT_GetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);							// �����͹ڽ��� ���� �Էµ� ���ڿ��� ������ �ɴϴ�.
	void HT_SetEditBoxControlLimitText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int uiSize);		// �����͹ڽ��� �Է±��ڱ��̸� �����մϴ�.
	void CheckEditBoxFocusOn(bool bCheck) {	m_InputState = bCheck;}		// ���� �Է»��� ���� ����
	bool HT_isFocusOnEditBoxControl() {return m_InputState;}			// ���� UI ���°� �Է»����ΰ�?
	void HT_SetEditBoxFocusOnIME(unsigned int nWindowIndex, unsigned int nControlIndex, int iIME); // �ش� �������� ��Ʈ�� ��Ŀ��Ȱ��ȭ�� ������ �Է¸�� ���¸� �����Ͽ� ����ǵ��� �մϴ�. 0 = ���� 1 = �ѱ���


	// [Button Control Processing Functions]
	void HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iTextureID2 = 0, int iTextureID3 = 0, int iLayer = 1500, int iSizeX = 0, int iSizeY = 0);	// ��ư�� �����մϴ�.
	void HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture[3]);	// ��ư�� �����մϴ�.
	void HT_SetButtonToolTip(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);	// �ش� ��ư�� ���� ������ �����մϴ�.
	void HT_SetButtonToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� ��ư�� ������ ŵ�ϴ�.
	void HT_SetButtonToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� ��ư�� ������ ���ϴ�.
	void HT_SetButtonEnterOn(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� ��ư�� ���ͱ���� ŵ�ϴ�.
	void HT_SetButtonEnterOff(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� ��ư�� ���ͱ���� ���ϴ�.
	void HT_DelButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex);				// �ش� ��ư�� ��Ʈ���� ���� �մϴ�.
	void HT_SetButtonControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str);	// ��ư ������ �ش� �ؽ�Ʈ ����(���κ�)
	void HT_SetButtonControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex);// ��ư ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
	void HT_SetButtonControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);// ��ư ���� �ش� ���� �ؽ�Ʈ ���� ����
	void HT_SetButtonEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable);
	void HT_SetButtonControlState(unsigned int nWindowIndex, unsigned int nControlIndex, int iSetNo);	// �ش� ������ ��»��¸� �����մϴ�. 0=�븻, 1=�׻�����, 2=�׻���, 3=������

	// [Timer Control Processing Functions]
	void HT_AddTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD dwSetTime, int iStyle = 0);
	void HT_DelTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	void HT_EnableOnTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	void HT_EnableOffTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex);

	// [Cehck Box Control Functions]
	void HT_AddCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, int XPos, int YPos, bool bValue = false, int BorderTextureID = 143, int CheckTextureID = 175, int SizeX = 14, int SizeY = 14);	// üũ�ڽ��� �����մϴ�.
	void HT_DelCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex);				// ��Ʈ���� �����մϴ�.
	void HT_SetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, bool bCheck);	// üũ�ڽ��� ���� ����
	bool HT_GetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex);					// üũ�ڽ��� ���� ����

	// [MessageBox Control Processing Functions]
	void HT_MessageBox(unsigned int nWindowIndex, CHTString str, int nStyle = 0);					// nMode = 0 Ȯ�ι�ư��, 1 = Ȯ��/��� ��ư, 2 = �̻��...	
	void HT_MessageBox(unsigned int nWindowIndex, int index, int nStyle = 0);
	bool HT_isShowMessageBox();																		// �޽��� �ڽ��� ����� �ִ��� �����մϴ�.
	void HT_CallMessageBoxFunction(unsigned int nWindowIndex, int iTargetID);

	// [Window Basic Functions]
	void HT_ShowWindow(unsigned int nIndex);														// �ش� �����츦 �����ݴϴ�.
	void HT_HideWindow(unsigned int nIndex);														// �ش� �����츦 ����ϴ�.
	void HT_EnableOnWindow(unsigned int nIndex);													// �ش� �����츦 �����ϰ� �մϴ�.
	void HT_EnableOffWindow(unsigned int nIndex);													// �ش� �����츦 �������� �ʰ� �մϴ�.
	void HT_FocusOnWindow(unsigned int nIndex);														// �ش� �������� ��Ŀ���� ŵ�ϴ�.
	void HT_FocusOffWindow(unsigned int nIndex);													// �ش� �����츦 ��Ŀ���� ���ϴ�.
	void HT_MoveWindow(unsigned int nIndex, int iPosX, int iPosY, int iType = 0);					// �ش� ��ġ�� �̵��մϴ� [iType = 0 �̵�, 1�̸� ������ġ���� �߰��̵�]
	void HT_WindowArrangement(unsigned int nIndex, int iDirection);									// �ش� �������� �����츦 �̵� ��ŵ�ϴ�. [���� Ű�е��� 1~9�� �������� �̵�_�ػ󵵿� ���� �ڵ�����]
	void HT_GetWindowPos(unsigned int nIndex, int &PosX, int &PosY);								// �ش� �������� ��ġ���� ���ɴϴ�.
	HTvector3 HT_GetWindowSize(unsigned int nIndex);												// �ش� �������� ����� ���ɴϴ�.
	void HT_SetMovingRegion(unsigned int nIndex, bool isOn, int iPosX = 0, int iPosY = 0, int iSizeX = 1, int iSizeY = 1);// ������ ������ �߰��� �����츦 ������ �� �ִ� ������ �����մϴ�. ù��° ���ڴ� ������ �ؾ��ϸ�, ������ ������ �������� �����մϴ�.
	void HT_SetMagnet(unsigned int nWindowIndex, unsigned int nTargetIndex);						// �ڼ���� ���� (0 = ���, -1 = ����ȭ��)
	void MagnetMgr(unsigned int nWindowIndex, unsigned int nTargetIndex, bool bInsert);				// �ش� ������ �ڼ���ɿ� ���� / ���� (����ó����)
	bool HT_GetMagnetState(unsigned int nWindowIndex);												// �ش� �������� �ڼ����¸� �˾ƿ´�.
	CHTString HT_strSetRestMark(HTint iNumber);														// ���Ǿ� ������ �޸� ��ũ ������ �ֵ��� ����
	void HT_SetMagnetState(unsigned int nWindowIndex, bool bState);									// �ش� �������� �ڼ����¸� ���� �����մϴ�. (��ӵ� �����쿡 ���ؼ��� ������ �մϴ�.)
	bool HT_CloseWindow();																			// �ֻ��� �����츦 �����մϴ�. (�ӽÿ� ������)

	// �����͹ڽ� ó�� ����
	void HT_UpdateEditBoxText(CHTString str);
	HTvector3 HT_GetEditBoxCursorPos();

	// [Input Functions]
	bool OnMouseWheel(WPARAM wParam, LPARAM lParam);
	bool OnLButtonDown(int iXPos, int iYPos);
	bool OnLButtonUp(int iXPos, int iYPos);
	bool OnRButtonDown(int iXPos, int iYPos);
	bool OnRButtonUp(int iXPos, int iYPos);
	bool OnKeyDown(WPARAM wParam);
	bool OnKeyUp(WPARAM wParam);
	bool OnChar(WPARAM wParam);
	bool OnMouseMove(int iXPos, int iYPos);
	bool OnSysCommand(WPARAM wParam);

	// UI ���� �� �ҷ�����
	void HT_vSaveDialogPos(CHTString strFilePath);
	void HT_vOpenDialogPos(CHTString strFilePath);

	unsigned int HT_CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// �ش� ��ġ�� ������ ��ȣ ��ȯ (������ 0)
	void HT_SetScriptMessage( HTint idMessage, CHTString* pszMessage, CHTString strInputItem1, CHTString strInputItem2 );
	void HT_SetWindowBackgroundColor(unsigned int nIndex);								// ��� �������� ���� ������ ���� �մϴ�. (0 ~ 100);

	// �ӽÿ� ���𺯼� (v2 -> v3�� �������� �������� �Լ���)
	void ChattingNotify(int iMessageID);								// ä��â�� ���� �˸� (ä��â ����ÿ��� �ùٸ��� ������) �ӽÿ�


	// [Message Procedure]
	static void ActionTarget(int iAction, int iTarget, int iTargetID);	// �Է� ó�� �Լ�
};

#endif