
#include "stdafx.h"
         // �� ����� ���Խ�Ų�� (�����ڵ� ó���� ����)
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTInterface.h"


// ��Ʈ �ٹ� ����
#define	UI_FONT_NORMAL		0		// �Ϲ� �۾�ü
#define	UI_FONT_BORD		1		// ����
#define	UI_FONT_BORDER		2		// ������
#define	UI_FONT_SHADOW		3		// �׸���
#define	UI_FONT_NORMAL_NOENTER	4	// �Ϲ� �۾�ü�̳� ������ �ȵǴ� ���� Ư¡

// Texture ID
//#define UI_TEXTURE_NONE						27023	// ��� �̹��� (����ó����) IntroUI
//#define UI_TEXTURE_NONE						23899	// ��� �̹��� (����ó����) MainUI
#define UI_TEXTURE_REGION					0	// ��濵������ ����
#define UI_TEXTURE_HEIGHT_LINE				1	// ���μ� �̹���
#define UI_TEXTURE_WIDTH_LINE				2	// ���μ� �̹���
#define UI_TEXTURE_TITLEBAR					3	// Ÿ��Ʋ��
#define	UI_TEXTURE_SCALEBAR_ON				4	// �����Ϲ�
#define UI_TEXTURE_EDGE_BUTTON_NORMAL		5	// �𼭸� ��ư (�Ϲ�)
#define UI_TEXTURE_EDGE_BUTTON_OVER			6	// �𼭸� ��ư (����)
#define UI_TEXTURE_EDGE_BUTTON_DOWN			7	// �𼭸� ��ư (�ٿ�)
#define UI_TEXTURE_WIDTH_LINE02				8	// �ٹ��̹���
#define UI_TEXTURE_BOX01					9	// �󺧿� ���Ǵ� �ٹ� �̹���
#define UI_TEXTURE_BOX02					10
#define UI_TEXTURE_BOX03					11
#define	UI_TEXTURE_SCALEBAR_OFF				12	// �����Ϲ� Off ���� �̹���
#define UI_TEXTURE_BUTTON04_NORMAL			13	// ����â�� 13*13 ��ư �̹���
#define UI_TEXTURE_BUTTON04_OVER			14
#define UI_TEXTURE_BUTTON04_DOWN			15

#define UI_TEXTURE_IMAGE01_SE				16
#define UI_TEXTURE_IMAGE01_NW				17
#define UI_TEXTURE_IMAGE01_NN				18
#define UI_TEXTURE_IMAGE01_NE				19
#define UI_TEXTURE_IMAGE01_EE				20
#define UI_TEXTURE_IMAGE01_SW				21

#define UI_TEXTURE_CURSOR					22	// Ŀ�� �̹���

// ������ ������ ������ �ּ� ���� ������ ����
#define	UI_MIN_RESIZEX		160
#define UI_MIN_RESIZEY		50

// ���� ����
#define	UI_TOOLTIP_EXTRASIZE_X				20		// �۾� ����� ���� ������ X
#define	UI_TOOLTIP_EXTRASIZE_Y				10		// �۾� ����� ���� ������ Y
#define	UI_TOOLTIP_POS_X					20		// �ش� ��Ʈ�ѷκ��� +-�Ǿ� ��µǴ� ��ġ X
#define	UI_TOOLTIP_POS_Y					20		// �ش� ��Ʈ�ѷκ��� +-�Ǿ� ��µǴ� ��ġ Y

#define	UI_TOOLTIP_MULTILINE_MAX			35		// ��Ƽ���� �� ����
#define	UI_TOOLTIP_HEIGHT_SIZE				14		// �ڰ� ������ ����

// ��Ʈ ���� ����
#define	UI_MAIN_FONT						HT_FONT_GULIM_12

// ������ �ڽ� ���̵� ���� 
#define	ID_EDIT								100
int				g_Pibot;								// �Ǻ� ��ġ
bool			g_Shift;								// ����Ʈ ��������
bool			g_Control;								// ����Ʈ ��������
bool			g_RegionCheck;							// ���� �۵� ����

int				g_EditBoxFocusWindow = 0;				// ��Ŀ�� �����ִ� ������ (���� ����)
int				g_EditBoxFocusControl = 0;				// ��Ŀ�� ���� �ִ� ��Ʈ�� (���� ����)
int				g_EditBoxCursorPosX = 0;
int				g_EditBoxCursorPosY = 0;

// UI ���� Ŭ�������� ����ϴ� ����ü
UIResource	g_oUIResource[300];	

//WNDPROC				PreEditProc;			// ����Ŭ���� �ϱ����� �޽��� �ݹ� �Լ� ����

//
// UI Texture Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UITextureControl::UITextureControl()
{
	m_Texture.Layer = 2000;			// �ؽ�ó �⺻ ������
	m_Texture.PosX = 0;				// �ؽ�ó �⺻ ������
	m_Texture.PosY = 0;				// �ؽ�ó �⺻ ������
	m_Texture.SizeX = 0;			// �ؽ�ó �⺻ ������
	m_Texture.SizeY = 0;			// �ؽ�ó �⺻ ������
	m_Texture.TextureID = 0;		// �ؽ�ó �⺻ ������
	m_Texture.VertexClr = HT_COLOR(1,1,1,0);	// �ؽ�ó �⺻ ������
	m_fScale.x = 0;					// ������ �ؽ�ó �����Ϻ���
	m_fScale.y = 0;					// ������ �ؽ�ó �����Ϻ���
	m_iWidth = 0;					// ���� �ؽ�ó ������X
	m_iHeight = 0;					// ���� �ؽ�ó ������Y
	m_iEObjID = 0;					// Engine���� ���� �ο� ���� �ؽ�ó ���� ID��

	// Process
	RealSizeX = 0;					// Real Output Region Image SizeX
	RealSizeY = 0;					// Real Output Region Image SizeY
	m_bCheckRegion = false;			// ���� ������ ���콺���� ������ ����
	m_bCheckMouseDown = false;		// ���� ������ ���콺�ٿ� ������ ����
	m_bCheckMouseRDown = false;		// ���� ������ ���콺�ٿ� ������ ����

	m_bEnable = false;				// true = �Է� ó������ / false = �Է� ó������
	m_bDisplay = false;				// true = ��� ���� / false = ��� ����

	m_nIndex = 0;
}

UITextureControl::~UITextureControl()
{
	if (m_iEObjID == 0) return;

	g_pEngineHandler->HT_vDestroyObject( m_iEObjID, 18);
}

// �����쿡 ����� �ؽ�ó�� �����մϴ�.
void UITextureControl::CreateUITextureControl(unsigned int nIndex, UITexture oTexture)
{
	// �Է����� ����
	m_Texture = oTexture;
	m_nIndex = nIndex;

	// ID�� 2���� �Ѿ�� Ŭ�󸮼ҽ��� ���̵� ����Ѵ�. �׸��� ������� ������ 32*32�� �ν�

	// Engine�� ��� ��û
	if (m_Texture.TextureID == 0)	
	{
			m_iEObjID = g_pEngineHandler->HT_iCreate2DWindowUISprite( g_oUIResource[m_Texture.TextureID].XMLID, 0, 0, 1, 1, m_Texture.VertexClr );	//�ȼ�23899
	}
	else
	{
		if (m_Texture.TextureID >= 20000)	
            m_iEObjID = g_pEngineHandler->HT_iCreate2DUISprite( m_Texture.TextureID, HTvector3( 0.0f, 0.0f, 0.0f) ); //�̹���
		else
			m_iEObjID = g_pEngineHandler->HT_iCreate2DUISprite( g_oUIResource[m_Texture.TextureID].XMLID, HTvector3( 0.0f, 0.0f, 0.0f) ); //�̹���
	}

	if (m_iEObjID < 0)
	{
		m_iWidth		= g_pEngineHandler->HT_iGetWidth(m_iEObjID);
	}

	// ��Ȯ�� ������ ���� �� ����� ���� ���� ����� �˾ƾ� �Ѵ�.
	m_iWidth		= g_pEngineHandler->HT_iGetWidth(m_iEObjID);
	m_iHeight		= g_pEngineHandler->HT_iGetHeight(m_iEObjID);

	// ����� ������� ����� �Է����� ������, ������� ������ �����ϰ� �����ȴ�.
	if (m_Texture.SizeX <= 0.0f || m_Texture.SizeY <= 0.0f)	
	{
		if (m_Texture.TextureID >= HT_ID_UI_MAIN_START && m_Texture.TextureID <= HT_ID_UI_MAIN_END || 
			m_Texture.TextureID >= HT_ID_UI_INTRO_START && m_Texture.TextureID <= HT_ID_UI_INTRO_END)
		{
			m_Texture.SizeX = 32;
			m_Texture.SizeY = 32;
		}
		else if (m_Texture.TextureID <= 1000)
		{
			m_Texture.SizeX = g_oUIResource[m_Texture.TextureID].RealSizeX;
			m_Texture.SizeY = g_oUIResource[m_Texture.TextureID].RealSizeY;
		}
	}

	this->SetScale(m_Texture.SizeX, m_Texture.SizeY);

	// �׿� �ʱ���� ����
	m_bCheckRegion = false;
	m_bCheckMouseDown = false;
	m_bEnable = true;
	m_bDisplay = true;
}

// ȭ��� �ؽ�ó�� ����մϴ�.
void UITextureControl::Render(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		// ���� ��ǥ���� ������ ��ġ���� ���ؼ� ����Ѵ�.
		HTvector3 fPos;
		fPos.x = ( (float) m_Texture.PosX + (float) iWindowPosX );
		fPos.y = ( (float) m_Texture.PosY + (float) iWindowPosY );
		fPos.z = 0.0f;

		g_pEngineHandler->HT_hrScaleObject(m_iEObjID, m_fScale);
		g_pEngineHandler->HT_hrMoveObject(m_iEObjID, fPos);
		g_pEngineHandler->HT_hrRenderObject(m_iEObjID, m_Texture.Layer);

	}
}

// �ش� ������ ���콺�� �ִ��� �˻��մϴ�.
bool UITextureControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// ���� �˻縦 ���� ���� ��ǥ������ ������.
	int PosX = iWindowPosX + m_Texture.PosX;
	int PosY = iWindowPosY + m_Texture.PosY;

	if(iXPos >= PosX && iXPos <= PosX + m_Texture.SizeX)
		if (iYPos >= PosY && iYPos <= PosY + m_Texture.SizeY)
			return true;
	return false;
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UITextureControl::Move(int iXPos, int iYPos, int iType)
{
	m_Texture.PosX = iXPos;
	m_Texture.PosY = iYPos;
}

// �������� �����մϴ�.
void UITextureControl::SetScale(int iSizeX, int iSizeY, int iOSizeX, int iOSizeY)
{ 
	m_Texture.SizeX = iSizeX;
	m_Texture.SizeY = iSizeY;

	// ������ ���� �缳��
	if (m_Texture.TextureID >= HT_ID_UI_MAIN_START && m_Texture.TextureID <= HT_ID_UI_MAIN_END || 
		m_Texture.TextureID >= HT_ID_UI_INTRO_START && m_Texture.TextureID <= HT_ID_UI_INTRO_END)
	{
		m_fScale.x = ( (float) m_Texture.SizeX / 32.0f);
		m_fScale.y = ( (float) m_Texture.SizeY / 32.0f);
		m_fScale.z = 0.0f;		// �̻��
	}
	else if (m_Texture.TextureID <= 1000)
	{
		m_fScale.x = ( (float) m_Texture.SizeX / (float) g_oUIResource[m_Texture.TextureID].RealSizeX);
		m_fScale.y = ( (float) m_Texture.SizeY / (float) g_oUIResource[m_Texture.TextureID].RealSizeY);
		m_fScale.z = 0.0f;		// �̻��
	}
	else if (iOSizeX != 1 && iOSizeX != 1)
	{
		m_fScale.x = ( (float) m_Texture.SizeX / (float) iOSizeX);
		m_fScale.y = ( (float) m_Texture.SizeY / (float) iOSizeY);
		m_fScale.z = 1.0f;
	}
	else
	{
		m_fScale.x = 1.0f;
		m_fScale.y = 1.0f;
		m_fScale.z = 1.0f;
	}
}

// �����ϰ��� ��ȯ�մϴ�.
void UITextureControl::GetScale(int &iSizeX, int &iSizeY)
{
	iSizeX = m_Texture.SizeX;
	iSizeY = m_Texture.SizeY;
}

// ������ �����մϴ�.
void UITextureControl::SetColor(HT_COLOR clr)
{
	g_pEngineHandler->HT_hrChangeColor( m_iEObjID, clr);
}

// UITextureControl�� ��ġ�� ��ȯ�Ѵ�.
HTvector3 UITextureControl::GetUITextureControlPos()
{
	HTvector3 fPos;
	fPos.x = (float)m_Texture.PosX;
	fPos.y = (float)m_Texture.PosY;
	fPos.z = 0.0f;

	return fPos;
}

// �ؽ�ó ��� ������ ��� �ɴϴ�.
UITexture UITextureControl::GetUITextureControl()
{
	return m_Texture;
}


//
// UI Label Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UILabelControl::UILabelControl()
{
	m_Text.Font = UI_MAIN_FONT;					// Text ����
	m_Text.FontMode = 0;
	m_Text.strTitle = "";
	m_Text.TextColor = HT_COLOR(1,1,1,1);
	m_Text.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP;
	m_Text.TextPos.bottom = 0;
	m_Text.TextPos.left = 0;
	m_Text.TextPos.right = 0;
	m_Text.TextPos.top = 0;
	m_Text.TextShadowColor = HT_COLOR(1,1,1,1);


	m_bEnable = false;				// true = �Է� ó������ / false = �Է� ó������
	m_bDisplay = false;				// true = ��� ���� / false = ��� ����

	m_bCheckRegion = false;			// ���� ������ ���콺���� ������ ����
	m_bCheckMouseDown = false;		// ���� ������ ���콺�ٿ� ������ ����

	TextPosX = 0;					// �ɼ� ����� ���� �ؽ�Ʈ ��ġX
	TextPosY = 0;					// �ɼ� ����� ���� �ؽ�Ʈ ��ġY
	m_Direction = 0;				// ��ġ���
	m_nIndex = 0;				// ��Ʈ�� ���� �ε���
}

UILabelControl::~UILabelControl()
{
}

// �����쿡 ����� �ؽ�ó�� �����մϴ�.
void UILabelControl::CreateUILabelControl(unsigned int nIndex, UIText oText)	// UI Object ����
{
	// �Է����� ����
	m_Text = oText;
	m_nIndex = nIndex;

	m_Direction = 5;

	TextPosX = 0; TextPosY = 0;
	SetArrangement(5);					// ���ڿ��� ��� ��ġ

	// �׿� �ʱ���� ����
	m_bCheckRegion = false;
	m_bCheckMouseDown = false;
	m_bEnable = true;
	m_bDisplay = true;
}

// ���� ���ĵ鿡 ���� �߰� ��ġ ���� ������ ���� �����մϴ�. (���� ��ġ ��� ����� ȣ���ؾ��մϴ�.)
void UILabelControl::SetTextArrangement(int iDirection)	
{
	// ���� ��Ʈ���� ���ڿ� ���̸� ���ؿ´�.
	int strlength = g_pEngineHandler->HT_iGetTextWidth( m_Text.Font, m_Text.strTitle );

	switch (iDirection)
	{
	case 1:	case 4:	case 7:	TextPosX = 0;	break;
	case 2:	case 5: case 8:	TextPosX = ( m_Text.TextPos.right - strlength) / 2;	break;
	case 3:	case 6:	case 9:	TextPosX = ( m_Text.TextPos.right - strlength);	break;
	default: TextPosX = 0; break;
	}

	switch (iDirection)
	{
	case 7:	case 8:	case 9:	TextPosY = 0; break;
	case 4: case 5: case 6:	TextPosY = ( m_Text.TextPos.bottom - 13) / 2;	break;
	case 1:	case 2:	case 3:	TextPosY = ( m_Text.TextPos.bottom - 13);	break;
	default: TextPosY = 0; break;
	}
}

// ȭ��� �ؽ�ó�� ����մϴ�.
void UILabelControl::Render(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		HT_RECT temp;
		
		// �ؽ�Ʈ ��� ��ġ ����
		temp.left = m_Text.TextPos.left + iWindowPosX + TextPosX;
		temp.top =  m_Text.TextPos.top + iWindowPosY + TextPosY;
		temp.right = m_Text.TextPos.left + m_Text.TextPos.right + iWindowPosX;
		temp.bottom = m_Text.TextPos.top + m_Text.TextPos.bottom + iWindowPosY;

		// ���ϴ� ���� ��°���
		switch (m_Text.FontMode)
		{
		case UI_FONT_BORD: // �β���
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_BORDER: // �ܰ���
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left+=2;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--; temp.top--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_SHADOW: // �׸���
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_NORMAL_NOENTER:	// >>�� ���ͱ�� �ȸ����� �Ϲ� ����
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_NORMAL: // �⺻ ���
		default:
			{
				float fTextHeight;
				temp.left++; g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle.HT_szGetString(), HT_COLOR(0,0,0,1), (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
				temp.left--; temp.top++; g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle.HT_szGetString(), HT_COLOR(0,0,0,1), (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
				temp.top--; g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle.HT_szGetString(), m_Text.TextColor, (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
			}
			break;
		}
	}
}

// �ش� ������ ���콺�� �ִ��� �˻��մϴ�.
bool UILabelControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// ���� �˻縦 ���� ���� ��ǥ������ ������.
	int PosX = iWindowPosX + m_Text.TextPos.left;
	int PosY = iWindowPosY + m_Text.TextPos.top;

	if(iXPos >= PosX && iXPos <= PosX + m_Text.TextPos.right)
		if (iYPos >= PosY && iYPos <= PosY + m_Text.TextPos.bottom)
			return true;
	return false;
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UILabelControl::Move(int iXPos, int iYPos)
{
	m_Text.TextPos.left = iXPos;
	m_Text.TextPos.top = iYPos;
}

// �ؽ�Ʈ�� �缳�� �մϴ�.
void UILabelControl::SetText(CHTString str)
{
	m_Text.strTitle = str;
	SetTextArrangement(m_Direction);	// ���ڿ��� ��� ��ġ
}

// UILabelControl�� ��ġ �� ����� ��ȯ�Ѵ�.
HT_RECT UILabelControl::GetUILabelControlPos()
{
	return m_Text.TextPos;
}

// ���� ��� ������ ����� �����մϴ�.
void UILabelControl::SetScale(int iSizeX, int iSizeY)
{
	m_Text.TextPos.right = iSizeX;
	m_Text.TextPos.bottom = iSizeY;
	SetTextArrangement(m_Direction);	// ���ڿ��� ��� ��ġ
}


//
// UI Long Label Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UILongLabelControl::UILongLabelControl()
{
	m_Text.Font = UI_MAIN_FONT;					// Text ����
	m_Text.FontMode = 0;
	m_Text.strTitle[0] = NULL;
	m_Text.TextColor = HT_COLOR(1,1,1,1);
	m_Text.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP;
	m_Text.TextPos.bottom = 0;
	m_Text.TextPos.left = 0;
	m_Text.TextPos.right = 0;
	m_Text.TextPos.top = 0;
	m_Text.TextShadowColor = HT_COLOR(1,1,1,1);


	m_bEnable = false;				// true = �Է� ó������ / false = �Է� ó������
	m_bDisplay = false;				// true = ��� ���� / false = ��� ����

	m_bCheckRegion = false;			// ���� ������ ���콺���� ������ ����
	m_bCheckMouseDown = false;		// ���� ������ ���콺�ٿ� ������ ����

	TextPosX = 0;					// �ɼ� ����� ���� �ؽ�Ʈ ��ġX
	TextPosY = 0;					// �ɼ� ����� ���� �ؽ�Ʈ ��ġY
	m_Direction = 0;				// ��ġ���
	m_nIndex = 0;				// ��Ʈ�� ���� �ε���
}

UILongLabelControl::~UILongLabelControl()
{
}

// �����쿡 ����� �ؽ�ó�� �����մϴ�.
void UILongLabelControl::CreateUILabelControl(unsigned int nIndex, UILongText oText)	// UI Object ����
{
	// �Է����� ����
	m_Text = oText;
	m_nIndex = nIndex;

	TextPosX = 0; TextPosY = 0;
	SetArrangement(5);					// ���ڿ��� ��� ��ġ

	// �׿� �ʱ���� ����
	m_bCheckRegion = false;
	m_bCheckMouseDown = false;
	m_bEnable = true;
	m_bDisplay = true;
}

// ���� ���ĵ鿡 ���� �߰� ��ġ ���� ������ ���� �����մϴ�. (���� ��ġ ��� ����� ȣ���ؾ��մϴ�.)
void UILongLabelControl::SetTextArrangement(int iDirection)	
{
	// ���� ��Ʈ���� ���ڿ� ���̸� ���ؿ´�.
	int strlength = g_pEngineHandler->HT_iGetTextWidth( m_Text.Font, m_Text.strTitle );

	switch (iDirection)
	{
	case 1:	case 4:	case 7:	TextPosX = 0;	break;
	case 2:	case 5: case 8:	TextPosX = ( m_Text.TextPos.right - strlength) / 2;	break;
	case 3:	case 6:	case 9:	TextPosX = ( m_Text.TextPos.right - strlength);	break;
	}

	switch (iDirection)
	{
	case 7:	case 8:	case 9:	TextPosY = 0; break;
	case 4: case 5: case 6:	TextPosY = ( m_Text.TextPos.bottom - 13) / 2;	break;
	case 1:	case 2:	case 3:	TextPosY = ( m_Text.TextPos.bottom - 13);	break;
	}
}

// ȭ��� �ؽ�ó�� ����մϴ�.
void UILongLabelControl::Render(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		HT_RECT temp;
		
		// �ؽ�Ʈ ��� ��ġ ����
		temp.left = m_Text.TextPos.left + iWindowPosX + TextPosX;
		temp.top =  m_Text.TextPos.top + iWindowPosY + TextPosY;
		temp.right = m_Text.TextPos.left + m_Text.TextPos.right + iWindowPosX;
		temp.bottom = m_Text.TextPos.top + m_Text.TextPos.bottom + iWindowPosY;

		// ���ϴ� ���� ��°���
		switch (m_Text.FontMode)
		{
		case UI_FONT_BORD: // �β���
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_BORDER: // �ܰ���
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left+=2;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--; temp.top--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_SHADOW: // �׸���
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_NORMAL: // �⺻ ���
		default:
			{
				float fTextHeight;
				g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle, m_Text.TextColor, (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
			}
			break;
		}
	}
}

// �ش� ������ ���콺�� �ִ��� �˻��մϴ�.
bool UILongLabelControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// ���� �˻縦 ���� ���� ��ǥ������ ������.
	int PosX = iWindowPosX + m_Text.TextPos.left;
	int PosY = iWindowPosY + m_Text.TextPos.top;

	if(iXPos >= PosX && iXPos <= PosX + m_Text.TextPos.right)
		if (iYPos >= PosY && iYPos <= PosY + m_Text.TextPos.bottom)
			return true;
	return false;
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UILongLabelControl::Move(int iXPos, int iYPos)
{
	m_Text.TextPos.left = iXPos;
	m_Text.TextPos.top = iYPos;
}

// �ؽ�Ʈ�� �缳�� �մϴ�.
void UILongLabelControl::SetText(HTtchar str[])
{
	strcpy(m_Text.strTitle, str);
	SetTextArrangement(m_Direction);	// ���ڿ��� ��� ��ġ
}

// UILabelControl�� ��ġ �� ����� ��ȯ�Ѵ�.
HT_RECT UILongLabelControl::GetUILabelControlPos()
{
	return m_Text.TextPos;
}

// ���� ��� ������ ����� �����մϴ�.
void UILongLabelControl::SetScale(int iSizeX, int iSizeY)
{
	m_Text.TextPos.right = iSizeX;
	m_Text.TextPos.bottom = iSizeY;
	SetTextArrangement(m_Direction);	// ���ڿ��� ��� ��ġ
}



//
// UIToolTipControl Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UIToolTipControl::UIToolTipControl()
{
	Body = new UITextureControl;

	m_dToolTipDelayTime = 200;	// ���콺 ������ 0.2���� �ߵ�
	m_iLineIndex = 0;
	m_SizeX = 0;
	m_SizeY = 0;

	m_bEnable = false;
	m_bDisplay = false;
}

UIToolTipControl::~UIToolTipControl()
{
	delete Body;

	if (m_UIToolTipLabelControl.empty()) return;	// �׿� �� ��Ʈ�� ���� �����Ѵ�.
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end();)
	{
		HT_DELETE ( *ZOder );
		ZOder = m_UIToolTipLabelControl.erase( ZOder );
	}
}

// �����쳻�� ������ �����մϴ�.
void UIToolTipControl::CreateUIToolTipControl(unsigned int nIndex, int iXPos, int iYPos, CHTString str )
{
	UITexture oTexture;
	UIText	oText;
	HT_COLOR clr;	// ���� ����
	clr.r = 1.0f / 255.0f; clr.g = 1.0f / 255.0f; clr.b = 1.0f / 255.0f; clr.a = 80.0f / 100.0f;


	// ToolTip�� ������� �ؽ�Ʈ�� ���̿� ���缭 ���ȴ�.
	int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str );
	
	m_SizeX = strlength + UI_TOOLTIP_EXTRASIZE_X;
	m_SizeY = UI_TOOLTIP_HEIGHT_SIZE*m_iLineIndex + UI_TOOLTIP_EXTRASIZE_Y;

	oTexture.PosX = iXPos; oTexture.PosY = iYPos; oTexture.SizeX = m_SizeX; oTexture.SizeY = m_SizeY;
	oTexture.VertexClr = clr; oTexture.Layer = 2300; 
	oTexture.TextureID = UI_TEXTURE_REGION; 

	oText.strTitle = str; oText.Font = UI_MAIN_FONT; oText.FontMode = UI_FONT_NORMAL; oText.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP; /*TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP;*/
	oText.TextPos.left = oTexture.PosX; oText.TextPos.top = oTexture.PosY; oText.TextPos.right = oTexture.SizeX; oText.TextPos.bottom = oTexture.SizeY;
	oText.TextColor.r = 1.0f; oText.TextColor.g = 1.0f; oText.TextColor.b = 1.0f; oText.TextColor.a = 1.0f;
	oText.TextShadowColor.r = 1.0f; oText.TextShadowColor.g = 0.8f; oText.TextShadowColor.b = 0.7f; oText.TextShadowColor.a = 1.0f;
	
	Body->CreateUITextureControl( 0, oTexture );		// ���� ����
	
	// �̸� �ؽ�Ʈ ������ �صд�.
	oText.TextPos.top+=(UI_TOOLTIP_EXTRASIZE_Y/2);
	for (int i = 1; i< UI_TOOLTIP_MULTILINE_MAX; ++i)
	{
		CreateLabelControl(i, oText);
		oText.TextPos.top+=UI_TOOLTIP_HEIGHT_SIZE;
		oText.TextPos.bottom = oText.TextPos.top + UI_TOOLTIP_HEIGHT_SIZE;
	}
}

// ȭ��� ������ ����մϴ�.
void UIToolTipControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true && this->CheckOutputTime() && m_bEnable == true && m_iLineIndex > 0)
	{
		// ���� ����� �ش� ��ũ���� �Ѿ�ٸ� �׸�ŭ - ���־� ����Ѵ�.
		int iSizeX, iSizeY;
		Body->GetScale(iSizeX, iSizeY);

		HTvector3 pos = Body->GetUITextureControlPos();

		// �ػ� ���� �� ��ٸ� �丸ŭ ������ ���
		if (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X > g_cUIManager->m_iScreenX)
			iWindowPosX -= (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X - g_cUIManager->m_iScreenX + UI_TOOLTIP_POS_X);
		// �ػ� ���� �� ��ٸ� �丸ŭ ������ ���
		if (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y > g_cUIManager->m_iScreenY)
			iWindowPosY -= (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y - g_cUIManager->m_iScreenY + UI_TOOLTIP_POS_Y);

		Body->Render(iWindowPosX + UI_TOOLTIP_POS_X, iWindowPosY + UI_TOOLTIP_POS_Y);					// ���� ����
	}
}

// ȭ��� ������ ����մϴ�.
void UIToolTipControl::RenderText(int iWindowPosX, int iWindowPosY)
{ 
	unsigned int index = 0;
	if (m_bDisplay == true && this->CheckOutputTime() == true && m_bEnable == true)
		if (m_UIToolTipLabelControl.empty() != true )	// ��
			for (int i = 1; i <= UI_TOOLTIP_MULTILINE_MAX; ++i)
				for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
				{
					if ((*ZOder)->m_nIndex == i)
					{
						// ���� ����� �ش� ��ũ���� �Ѿ�ٸ� �׸�ŭ - ���־� ����Ѵ�.
						int iSizeX, iSizeY;
						Body->GetScale(iSizeX, iSizeY);
						
						HTvector3 pos = Body->GetUITextureControlPos();

						if (index >= m_iLineIndex) return;

						// �ػ� ���� �� ��ٸ� �丸ŭ ������ ���
						if (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X > g_cUIManager->m_iScreenX)
							iWindowPosX -= (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X - g_cUIManager->m_iScreenX + UI_TOOLTIP_POS_X);
	
						// �ػ� ���� �� ��ٸ� �丸ŭ ������ ���
						if (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y > g_cUIManager->m_iScreenY)
							iWindowPosY -= (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y - g_cUIManager->m_iScreenY + UI_TOOLTIP_POS_Y);

						(*ZOder)->Render(iWindowPosX + UI_TOOLTIP_POS_X, iWindowPosY + UI_TOOLTIP_POS_Y);
						++index;
					}
				}
}


// ���ϴ� ��ġ�� ������ �̵���ŵ�ϴ�.
void UIToolTipControl::Move(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);
	
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		(*ZOder)->Move(iXPos, iYPos);
}

// ��׶��� ������ ������ ���콺�� �ִ��� �˻��մϴ�.
bool UIToolTipControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// �븻 ��ư���θ� üũ��
	return Body->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// ���� �ð� ī��Ʈ�� �����մϴ�.
void UIToolTipControl::SetStartTime()	
{
	m_dToolTipStartTime = timeGetTime();
}

// ������ ����ص� �Ǵ��� ���ξ˸�
bool UIToolTipControl::CheckOutputTime()
{
	DWORD 	ToolTipNowTime = timeGetTime(); //GetTickCount();
	if (m_dToolTipStartTime + m_dToolTipDelayTime <= ToolTipNowTime)
		return true;
	return false;
}


// ������ ������ �����մϴ�.
void UIToolTipControl::SetText(CHTString str, int nIndex)
{
	SetTextLabelControl(nIndex, str);
}


// �� ��Ʈ�� ����
void UIToolTipControl::CreateLabelControl(unsigned int nIndex, UIText oText)
{
	UILabelControl* pUILabelControl = new UILabelControl;
	pUILabelControl->m_nIndex = nIndex;
	pUILabelControl->CreateUILabelControl(nIndex, oText);
	this->m_UIToolTipLabelControl.push_back(pUILabelControl);
}

// �� ��Ʈ�� ����
void UIToolTipControl::DeleteLabelControl(unsigned int nIndex)
{ 
	if (m_UIToolTipLabelControl.empty()) return;	// �׿� �� ��Ʈ�� ���� �����Ѵ�.
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIToolTipLabelControl.erase( ZOder );
			break;
		}
}

// �� ��Ʈ���� �ؽ�Ʈ ����
void UIToolTipControl::SetTextLabelControl(unsigned int nIndex, CHTString str)
{
	int MaxStrLength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str);

	if (nIndex > m_iLineIndex) m_iLineIndex = nIndex;
	if (nIndex > UI_TOOLTIP_MULTILINE_MAX) m_iLineIndex = nIndex = UI_TOOLTIP_MULTILINE_MAX;	// �ƽ����� ����

	// ���� �����ϴ� ��� �� �ؽ�Ʈ ������ ���� ����� ����� ��´�.
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
	{
		/// ToolTip�� ������� �ؽ�Ʈ�� ���̿� ���缭 ���ȴ�.
		int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder)->GetText());
		// ���� ��͵��� ���̻� �þ���ʵ��� ������Ų��.
		if (strlength > 500) strlength = 210;
		if (MaxStrLength <= strlength) MaxStrLength = strlength;
	}

	// ������ �簻�� �� ����
	for(std::list<UILabelControl*>::iterator ZOder2 = m_UIToolTipLabelControl.begin(); ZOder2 != m_UIToolTipLabelControl.end(); ++ZOder2)
		(*ZOder2)->SetScale(MaxStrLength+UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE);	// ���� �缳��

	for(std::list<UILabelControl*>::iterator ZOder3 = m_UIToolTipLabelControl.begin(); ZOder3 != m_UIToolTipLabelControl.end(); ++ZOder3)
		if ((*ZOder3)->m_nIndex == nIndex)
		{
			// Step 1) �ؽ�Ʈ ����� �������Ѵ�.
			Body->SetScale(MaxStrLength + UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE * m_iLineIndex + UI_TOOLTIP_EXTRASIZE_Y);
			// Step 2) �� ������ �����Ѵ�.
			(*ZOder3)->SetText(str);	// �ش� ������ ���� ���ڿ� ����

			int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder3)->GetText());
            if ((*ZOder3)->m_nIndex == 3 && strlength > 500)
				(*ZOder3)->SetArrangement(7);
			else
				(*ZOder3)->SetArrangement(8);

			break;
		}
}

// �� ��Ʈ���� �ؽ�Ʈ ����
void UIToolTipControl::SetTextLabelControlIndex(unsigned int nIndex)
{
	int MaxStrLength = 0;

	m_iLineIndex = nIndex;	// �ε��� �缳��

	for (int i = nIndex+1; i < UI_TOOLTIP_MULTILINE_MAX; ++i) 
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == i)
			(*ZOder)->SetText(" ");
	
	// ���� �����ϴ� ��� �� �ؽ�Ʈ ������ ���� ����� ����� ��´�.
	for(std::list<UILabelControl*>::iterator ZOder2 = m_UIToolTipLabelControl.begin(); ZOder2 != m_UIToolTipLabelControl.end(); ++ZOder2)
	{
		/// ToolTip�� ������� �ؽ�Ʈ�� ���̿� ���缭 ���ȴ�.
		int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder2)->GetText());
		if (strlength > 500) strlength = 210;
		if (MaxStrLength <= strlength) MaxStrLength = strlength;
	}

	// ������ �簻�� �� ����
	for(std::list<UILabelControl*>::iterator ZOder3 = m_UIToolTipLabelControl.begin(); ZOder3 != m_UIToolTipLabelControl.end(); ++ZOder3)
		(*ZOder3)->SetScale(MaxStrLength+UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE);	// ���� �缳��

	// ���� �� ���ڿ��� ������ �����Ѵ�.
	for(std::list<UILabelControl*>::iterator ZOder4 = m_UIToolTipLabelControl.begin(); ZOder4 != m_UIToolTipLabelControl.end(); ++ZOder4)
	{
		int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder4)->GetText());
		if (strlength > 500) 
			(*ZOder4)->SetScale(210+UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE);	// ���� �缳��
	}

	Body->SetScale(MaxStrLength + UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE * m_iLineIndex + UI_TOOLTIP_EXTRASIZE_Y);

}

// �� ��Ʈ���� �ؽ�Ʈ�÷� ����
void UIToolTipControl::SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}



//
// UIButtonControl Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UIButtonControl::UIButtonControl()
{
	ButtonNormal = new UITextureControl;
	ButtonOver	= new UITextureControl;
	ButtonDown	= new UITextureControl;
	ToolTip = new UIToolTipControl;

	m_bEnable = true;
	m_bDisplay = true;
	m_bToolTip = true;
	m_bEnter = false;
	m_iButtonState = 0;
	m_nButtonState = 0;

	m_dFlashButtonOnDelayTime = 700;	// Ŀ�� ������ �ð� 0.75���� �ߵ�
	m_dFlashButtonOffDelayTime = 1000;	// Ŀ�� ������ �ð� 1���� �ߵ�
	m_dFlashButtonStartTime = 0;
}

UIButtonControl::~UIButtonControl()
{
	delete ButtonNormal;
	delete ButtonOver;
	delete ButtonDown;
	delete ToolTip;
}

// �����쳻�� ��ư�� �����մϴ�.
void UIButtonControl::CreateUIButtonControl(unsigned int nIndex, UITexture oTexture[3] )
{
	ButtonNormal->CreateUITextureControl(0, oTexture[0]);// �븻 ���·� ����
	ButtonNormal->Show();
	ButtonOver->CreateUITextureControl(0, oTexture[1]);	// ���� ���·� ����
	ButtonOver->Hide();
	ButtonDown->CreateUITextureControl(0, oTexture[2]);	// �ٿ� ���·� ����
	ButtonDown->Hide();
	ToolTip->CreateUIToolTipControl(0, oTexture[0].PosX, oTexture[0].PosY, _T(" "));	// ���� ��Ʈ�� ����
}

// ȭ��� �����츦 ����մϴ�.
void UIButtonControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		// �ؽ�ó ���� (������ ����� ���⼭ ó��)
		if (m_iButtonState == 3)
		{
			if (m_nButtonState == 0)
			{
				DWORD 	FlashButtonNowTime = timeGetTime();//GetTickCount();
		
				if (m_dFlashButtonStartTime + m_dFlashButtonOnDelayTime >= FlashButtonNowTime)
				{ButtonNormal->Hide(); ButtonOver->Show(); ButtonDown->Hide();}
				else if (m_dFlashButtonStartTime + m_dFlashButtonOffDelayTime >= FlashButtonNowTime)
				{ButtonNormal->Hide(); ButtonOver->Hide(); ButtonDown->Show();}
				else {m_dFlashButtonStartTime = timeGetTime();}
			}
			else if (m_nButtonState == 1)
			{m_dFlashButtonStartTime = timeGetTime();}
		}

		ButtonNormal->Render(iWindowPosX, iWindowPosY);					// ���� ����
		ButtonOver->Render(iWindowPosX, iWindowPosY);
		ButtonDown->Render(iWindowPosX, iWindowPosY);
	}
}


// ȭ��� �����츦 ����մϴ�.
void UIButtonControl::RenderTextureToolTip(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderTexture(iWindowPosX, iWindowPosY);
}

// ȭ��� �ؽ�Ʈ�� ����մϴ�.
void UIButtonControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderText(iWindowPosX, iWindowPosY);
}

// ���ϴ� ��ġ�� �����츦 �̵���ŵ�ϴ�.
void UIButtonControl::Move(int iXPos, int iYPos)
{
	ButtonNormal->Move(iXPos, iYPos);
	ButtonOver->Move(iXPos, iYPos);	
	ButtonDown->Move(iXPos, iYPos);	
	ToolTip->Move(iXPos, iYPos);
}

// ���ϴ� ũ��� ����
void UIButtonControl::SetScale(int iSizeX, int iSizeY)
{
	ButtonNormal->SetScale(iSizeX, iSizeY);
	ButtonOver->SetScale(iSizeX, iSizeY);	
	ButtonDown->SetScale(iSizeX, iSizeY);	
}

// ��׶��� ������ ������ ���콺�� �ִ��� �˻��մϴ�.
bool UIButtonControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// �븻 ��ư���θ� üũ��
	if (ButtonNormal->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
	{ return true; }
	else
	{ return false; }
}

void UIButtonControl::SetButtonNormal()
{
	ToolTip->Hide();m_nButtonState = 0;

	switch (m_iButtonState)
	{
	case 0:	case 3: ButtonNormal->Show(); ButtonOver->Hide(); ButtonDown->Hide(); return;	// �������
	case 1:	ButtonNormal->Hide(); ButtonOver->Show(); ButtonDown->Hide(); return;	// ��������
	case 2: ButtonNormal->Hide(); ButtonOver->Hide(); ButtonDown->Show(); return;	// ��������
	}
}

void UIButtonControl::SetButtonOver()
{
	ToolTip->Show();m_nButtonState = 1;
	ButtonNormal->Hide(); ButtonOver->Show(); ButtonDown->Hide();
}

void UIButtonControl::SetButtonDown()
{
	ToolTip->Hide(); m_nButtonState = 2;
	ButtonNormal->Hide(); ButtonOver->Hide(); ButtonDown->Show();
}

// ������ �ش���ġ�� �̵���ŵ�ϴ�.
void UIButtonControl::SetToolTipMove(int iXPos, int iYPos)
{
	ToolTip->Move(iXPos, iYPos);	
}


// ������ ������ �����մϴ�.
void UIButtonControl::SetToolTipStr(CHTString str)
{
	ToolTip->SetText(str);
}





//
// UIEditBoxControl Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UIEditBoxControl::UIEditBoxControl()
{
	Body = new UITextureControl;
	Cursor = new UITextureControl;
	ShiftRegion = new UITextureControl;
	Text = new UILabelControl;

	m_dEditBoxCursorOnDelayTime = 500;	// Ŀ�� ������ �ð� 0.5���� �ߵ�
	m_dEditBoxCursorOffDelayTime = 1000;	// Ŀ�� ������ �ð� 1���� �ߵ�

	m_Xpos = 0;
	m_XPibot = 0;

	m_bEnable = true;
	m_bDisplay = true;
	m_bFocus = false;
	m_bRegion = false;
	m_ImeNo = 0;	// ó�� �Է¸��� ����
	m_iLimitTextSize = 0;
}

UIEditBoxControl::~UIEditBoxControl()
{
	delete Body;
	delete Text;
	delete Cursor;
	delete ShiftRegion;
}

// ����Ʈ��Ʈ�� ���� (���� ����)
LRESULT CALLBACK NowEditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return NULL;
}

// �����쳻�� ����Ʈ�ڽ��� �����մϴ�.
void UIEditBoxControl::CreateUIEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle)
{
	Body->CreateUITextureControl( 0, oTexture );						// ����Ʈ�ڽ� �ؽ�ó ����

	// Ŀ�� ����
	oTexture.TextureID = 199;											// Ŀ�� �ؽ�ó ����
	oTexture.Layer = 2500;												// Ŀ�� ���̾ƿ� ���� (���� �����쿡�� �ֻ����� �Ѵ�)
	oTexture.PosX += 5;
	oTexture.SizeX = 0;
	oTexture.SizeY = 0;

	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Cursor->CreateUITextureControl( 0, oTexture );						// Ŀ���� �����.

	// ������ �ڽ� ����
	oTexture.TextureID = 0;												// Ŀ�� �ؽ�ó ����
	oTexture.Layer = 2550;												// Ŀ�� ���̾ƿ� ���� (���� �����쿡�� �ֻ����� �Ѵ�)
	oTexture.SizeX = 0;
	oTexture.SizeY = 0;
	
	oTexture.VertexClr = HT_COLOR(0.2f, 0.2f, 0.2f, 0.7f);
	ShiftRegion->CreateUITextureControl( 0, oTexture );						// ���� �ؽ�ó�� �����.

	// �ؽ�Ʈ ����
	oText.TextPos.left += 5; oText.TextPos.right -= 5;
	Text->CreateUILabelControl(0, oText);								// �ؽ�Ʈ ��Ʈ���� �����Ѵ�.
	Text->SetArrangement(4);											// ���ڴ� ���� ��� ���ĸ��� ����
	m_nMode = 0;														// ó���� �Ϲݸ��� ���� ( 1 = �н����� �������)
}


// ��Ŀ�� �½� ���õ� IME ����
void UIEditBoxControl::SetFocusOnIME(int iIME)
{
	if( g_iInationalType == INATIONALTYPE_JAPEN )
		return;


	HIMC hIMC = ImmGetContext(g_hWnd);
	DWORD dwInationallanguageCode;

	if (iIME == 1)
	{
		//	Set Language
		if( g_iInationalType == INATIONALTYPE_KOREA )
			dwInationallanguageCode = IME_CMODE_HANGUL;
		else if( g_iInationalType == INATIONALTYPE_CHINA )
			dwInationallanguageCode = IME_CMODE_CHINESE;
		else if( g_iInationalType == INATIONALTYPE_INDONESIA )
			dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
		else if( g_iInationalType == INATIONALTYPE_PHILIPPINE )
			dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
		else if( g_iInationalType == INATIONALTYPE_JAPEN )
			dwInationallanguageCode = IME_CMODE_JAPANESE;
		else if( g_iInationalType == INATIONALTYPE_TAIWAN )
			dwInationallanguageCode = IME_CMODE_NATIVE;
		else
			dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
	}
	else
	{
		dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
	}

	ImmSetConversionStatus(hIMC, dwInationallanguageCode, 1);
	ImmReleaseContext(g_hWnd, hIMC);
}

// ȭ��� �����츦 ����մϴ�.
void UIEditBoxControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		Body->Render(iWindowPosX, iWindowPosY);					// ���� ����
		
		if (this->isFocusOn())
		{
			this->CheckOutputTime();
			Cursor->Render(iWindowPosX, iWindowPosY);					// Ŀ�� ����
			
			if (m_bRegion == true)
				ShiftRegion->Render(iWindowPosX, iWindowPosY);				// ���� ������ ������
		}
	}
}


// ȭ��� �����츦 ����մϴ�.
void UIEditBoxControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	Text->Render(iWindowPosX, iWindowPosY);
}


// ���ϴ� ��ġ�� �����츦 �̵���ŵ�ϴ�.
void UIEditBoxControl::Move(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);
	Text->Move(iXPos, iYPos);
}

// ��׶��� ������ ������ ���콺�� �ִ��� �˻��մϴ�.
bool UIEditBoxControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	return Body->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// Ŀ�������� �ð� ī��Ʈ�� �����մϴ�.
void UIEditBoxControl::SetStartTime()	
{
	m_dEditBoxStartTime = timeGetTime();//GetTickCount();
}

// Ŀ�� �������� ����ص� �Ǵ��� ���ξ˸�
bool UIEditBoxControl::CheckOutputTime()
{
	DWORD 	EditBoxNowTime = timeGetTime();//GetTickCount();
	
	if (m_dEditBoxStartTime + m_dEditBoxCursorOnDelayTime >= EditBoxNowTime)
		Cursor->Show();
	else if (m_dEditBoxStartTime + m_dEditBoxCursorOffDelayTime >= EditBoxNowTime)
		Cursor->Hide();
	else
		SetStartTime();
	return false;
}

// ����Ʈ�ڽ��� ����� ���ڿ� ���� (�Ǻ����� ���� ����)
void UIEditBoxControl::OutputText()
{
	return;	// ������
}


// ���ڿ� ���� (Ŀ�� ��ġ ���ŵ� ���� �Ѵ�.)
void UIEditBoxControl::SetText(CHTString str)
{
	// ��Ʈ�ѷκ��� �����
	this->UpdateText( str );
}


// ���ڿ� ���� (Ŀ�� ��ġ ���ŵ� ���� �Ѵ�.)
void UIEditBoxControl::UpdateText( CHTString strMsg )
{
	// ��Ʈ�ѷκ��� �����
	CHTString str, str2;

	// ���� ���۷� ���� ���ڿ� ���
	//GetWindowText(g_hEdit, str, 256);
	if( strMsg.HT_bIsEmpty() )
	{
		str = g_strResultText;
		if( g_bShowCompStrSw )	str += g_strCompStr;
	}
	//	Clean�� ������ �� ����.
	else if( strMsg.HT_iStringCompare(_T("CleanBox") ) == 0 )
	{
		str.HT_hrCleanUp();
	}
	else
	{
		str = strMsg;
	}

	// ù���ڰ� 0���� ���۵ǰ� �����Է� ����� 0�� ���ش�.
	char temp[256];
	strcpy(temp, str);
	if (temp[0] == '0' && m_nMode == 2) 
		--str;

	//	���ڼ� ����
	int iStringLen = strlen(str);
	if( iStringLen > m_iLimitTextSize && m_iLimitTextSize != 0 )
	{
		CHTString strTemp;
		strTemp.HT_hrCleanUp();
		strncpy( strTemp, str, m_iLimitTextSize );
		g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( strTemp );

		// �������� �ؽ�Ʈ ��� (m_str)
		str = m_str = strTemp;
		//this->UpdateText(m_str);
	}
	else
	{
		// �������� �ؽ�Ʈ ��� (m_str)
		m_str = str;
	}

	// ��忡 ���� ����� �޸� ����
	switch(m_nMode)	
	{
	case 1:	// �н����� ��� (��ǥ�� ����)
		{
			CHTString passwordstr = "";
	
			for (int i=0; i < ((int) strlen(str)); ++i)
				strcat(passwordstr, "*");

			str = passwordstr;
		}
		break;
	case 2:	// �����Է� ��� (�޸� �ڵ�����)
		{
			CHTString numberstr = "";
			
			//	0�� ���̾� �Է��ߴٸ� 0���� �ʱ�ȭ
			if (atoi(str) == 0 && strlen(str) > 1)
			{
				g_strResultText = "0";
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( g_strResultText.HT_szGetString() );
			}

			//	10�� �̻��� ���ڰ� ������ 999999999
			//	������ ���ڰ� ���ڰ� �ƴϸ� 0���� ó��
			char szNumber[256];
			ZeroMemory( szNumber, 256 );
			HTint iSize = str.HT_nGetSize();
			strncpy( szNumber, str, iSize );

			//	10�� �̻�
			if( iSize > 9 )
			{
				//if (atoi(str) > 1999999999)
				if( szNumber[iSize-1]>'1') 
					g_strResultText = "1999999999";
				else
					if( iSize > 10 ) g_strResultText = "1999999999";
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( g_strResultText.HT_szGetString() );
				m_str = str = g_strResultText;
			}
			//	������ ���ڰ� ���ڰ� �ƴ�
			else if( szNumber[iSize-1]<'0' || szNumber[iSize-1]>'9' )
			{
				g_strResultText = "0";
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( g_strResultText.HT_szGetString() );
				m_str = str = g_strResultText;
			}

			m_str = str;
			numberstr = g_cUIManager->HT_strSetRestMark(atoi(str));
			str = numberstr;
		}
		break;
	}

	// ������ �ؽ�Ʈ ���� ��� (str2)
	str2 = str;

	// CString -> wchar_t ������ ��ȯ�Ͽ� ���� ���� ����
	CComBSTR bstr = str;
	wchar_t *pVal, wcs[256], TailCutStr[256] = L"";
	
	pVal = bstr;
	int iTotalPibot = wcslen(pVal);
	wcscpy(wcs, pVal);
	
	// �Ǻ� ����
	if (g_Pibot > iTotalPibot) 	g_Pibot = iTotalPibot;
	if (g_Pibot < 0) g_Pibot = 0;

	iTotalPibot -= g_Pibot;
	
	// Ŀ�� ��ġ������ ���ڿ� ���� ������ wchar_t -> CString
	wcsncpy(TailCutStr, wcs, iTotalPibot);
	wcstombs(str2, TailCutStr, 256 );

	// ���ڿ��� ó������ �Ǻ������� �ȼ� �Ÿ� ����
	HT_RECT pos = Text->GetUILabelControlPos();
	int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str2 );
	//Cursor->Move((int)pos.left + strlength, (int)pos.top);

	// ������ �Ǻ� ��ġ�� �߽����� �����͹ڽ� ��Ʈ�� ������ ���� �� ���ڿ� �ڸ�
	bool bType = false;
	strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str2 );
	int strlength2 = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str );

	if ( strlength > pos.right - 16)  bType = true;

	if ( bType == true)	// �Ǻ��������� ���ڿ��� ������ ó��
		str = str2;

	// ������ ����� ���ڿ��̳� �Ǻ��� ���� �̳��� ��ġ�� ��쿡�� ������ �߽����� �պκи� �����Ͽ� ���
	int AddPibot = 0;
	if ( bType == false && strlength2 > pos.right - 16 )
	{
		int i = 0;
		char tempstr[256] = _T("");
		strlength2 = 0;

		do  // ���� ������� ���������� ������� ���ڿ� ���� 
		{ 
			i++;
			strncpy(tempstr, str, i);
			strlength2 = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, tempstr ); 

		} while ( strlength2 <= pos.right - 16);

		strcpy(str, tempstr);
	}
	else
	{
		int strtemp = strlength;
		while ( strlength > pos.right - 16) // ���� ������� ���������� ���� ���ڿ� �ڸ�
		{ 
			--str; strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str ); 

			AddPibot += (strtemp - strlength);
			strtemp = strlength;
			if (AddPibot > m_XPibot)	// ����Ʈ ���̿��ٸ� ������ ���� ���̸�ŭ m_XPibot ��ǥ ���� 
			{
				// ����, 0 ���� �۾����ٸ� 0 ����
				AddPibot = m_XPibot;
			}
		}
	}

	
	// ����Ʈ ���� �����̶�� ����Ʈ ���� �Ǻ� ����
	if (g_Shift == true && m_XPibot == -1)
	{
		m_bRegion = true;
		m_XPibot = strlength;
	}
	else if (g_Shift == false && m_XPibot == -2)
	{
		m_bRegion = false;
	}


	g_EditBoxCursorPosX = (int)pos.left + strlength;
	g_EditBoxCursorPosY = (int)pos.top;

	Cursor->Move((int)pos.left + strlength, (int)pos.top);

	Text->SetText(str);

	// ���� �ڽ� (Shift) �׸���
	if (g_Shift == true) 
	{
		ShiftRegion->Move((int)pos.left + m_XPibot - AddPibot, (int)pos.top);
		ShiftRegion->SetScale(strlength - m_XPibot + AddPibot, 16);
	}

	//MoveCursor(hr, 0);
	//OutputText();
}

// �����͹ڽ��� �Է»��·� ����ϴ�.
void UIEditBoxControl::SetFocusOn() 
{ 
	g_cUIManager->CheckEditBoxFocusOn(true);
	m_bFocus = true;
	//SetFocus(g_hEdit);
	SetFocusOnIME(m_ImeNo);	// �Է»��¸� ������ ���·� ����
	g_Pibot = -1;
	m_XPibot = -2;
	g_Shift = false;								// ����Ʈ ��������
	g_Control = false;								// ����Ʈ ��������
	g_RegionCheck = false;	
	//SendMessage(g_hEdit, WM_KEYDOWN, VK_END, 0);
	
	this->SetStartTime();	// Ŀ�� ��� ����
}	

// �����͹ڽ��� �ԷºҰ����·� ����ϴ�.
void UIEditBoxControl::SetFocusOff() 
{
	g_EditBoxFocusWindow = 0; // ��Ŀ�� �����ִ� ������ ����
	g_EditBoxFocusControl = 0;	// ��Ŀ�� ���� �ִ� ��Ʈ�� ����

	g_cUIManager->CheckEditBoxFocusOn(false);
	m_bFocus = false;
	SetFocusOnIME(0);	// �Է»��¸� �������·� ����
	//SetFocus(g_hWnd);
}

// �����͹ڽ��� �ԷºҰ����·� ����ϴ�.
void UIEditBoxControl::SetLimitText(unsigned int uiSize) 
{
	m_iLimitTextSize = uiSize;
	//SendMessage(g_hEdit, EM_LIMITTEXT, (WPARAM) uiSize, 0);
}

// Ŀ���� �̵���ŵ�ϴ�.
void UIEditBoxControl::MoveCursor(int iXpos, int iYpos)
{	
	return;	//������
}




//
// UI Timer Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UITimerControl::UITimerControl() {}
UITimerControl::~UITimerControl() {}
	
// Ÿ�̸Ӹ� �����մϴ�.
void UITimerControl::CreateUITimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle)
{
	dwDealyTime = dwSetTime;
	m_nIndex = nIndex;
	dwSetTime = timeGetTime();
	m_bEnable = false;

	switch(iStyle)
	{
	case 0:	// ��� �ݺ�
		m_OnlyOne = false;
		break;
	case 1:	// �ѹ��� ����
		m_OnlyOne = true;
		break;
	}
}

// �ð��� üũ�մϴ�.
bool UITimerControl::CheckTime()
{
	DWORD nowTime = timeGetTime();
	if (m_bEnable == true && dwSetTime + dwDealyTime <= nowTime)
	{
		if (m_OnlyOne == false) EnableOn(); else EnableOff();
		return true;
	}
	else
	{
		return false;
	}
}



//
// UI CheckBox Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UICheckBoxControl::UICheckBoxControl() 
{
	Body = new UITextureControl;
	Check = new UITextureControl;

	m_bEnable = true;
	m_bDisplay = true;
	m_bValue = false;
}

UICheckBoxControl::~UICheckBoxControl()
{
	delete Body;
	delete Check;
}


// üũ�ڽ��� �����մϴ�.
void UICheckBoxControl::CreateUICheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue, int BorderTextureID, int CheckTextureID, int SizeX, int SizeY)
{
	m_nIndex = nIndex;
	m_bEnable = true;
	m_bDisplay = true;
	m_bValue = bValue;

	UITexture oTexture;	// �ؽ�ó ����
	oTexture.Layer = 1450;
	oTexture.PosX = XPos;
	oTexture.PosY = YPos;
	oTexture.SizeX = SizeX;
	oTexture.SizeY = SizeY;
	oTexture.TextureID = BorderTextureID;
	oTexture.VertexClr = HT_COLOR(1,1,1,1);

	if (BorderTextureID == 0)
	{
		BorderTextureID = 0;
		oTexture.VertexClr = HT_COLOR(1,1,1,0);
	}

	Body->CreateUITextureControl( 0, oTexture );
	
	oTexture.TextureID = CheckTextureID;
	oTexture.VertexClr = HT_COLOR(1,1,1,1);

	Check->CreateUITextureControl( 0, oTexture );
}

// üũ�ڽ� ���� �����մϴ�.
void UICheckBoxControl::SetValue(bool bValue)
{
	m_bValue = bValue;
}

// ȭ��� �����츦 ����մϴ�.
void UICheckBoxControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		Body->Render(iWindowPosX, iWindowPosY);					// ���� ����
		
		if (m_bValue == true)
		{
			Check->Render(iWindowPosX, iWindowPosY);					// üũ�ڽ� ����
		}
	}
}

// ���ϴ� ��ġ�� �����츦 �̵���ŵ�ϴ�.
void UICheckBoxControl::Move(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);
	Check->Move(iXPos, iYPos);
}

// ��׶��� ������ ������ ���콺�� �ִ��� �˻��մϴ�.
bool UICheckBoxControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	return Body->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}


//
// UI Slot Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UISlotBoxControl::UISlotBoxControl()
{
	ToolTip = new UIToolTipControl;
	Slot = new UITextureControl;
	Image = new UITextureControl;
	Fx = new UITextureControl;
	Enable = new UITextureControl;
	
	m_bFirstMove = true;
	m_bMouseOver = false;
	m_bToolTip = true;
	m_bDisplay = true;
	m_bEnable = true;
	m_bFixedIcon = false;
	m_bEnableCheck = false;

	m_AddPosX = 3;	// ���Թڽ��� �߰� �̵��Ͽ� ����� �̹��� X, Y ��ǥ
	m_AddPosY = 3;
}

UISlotBoxControl::~UISlotBoxControl()
{
	delete ToolTip;
	delete Slot;
	delete Image;
	delete Fx;
	delete Enable;
}

// �����쿡 ����� �ؽ�ó�� �����մϴ�.
void UISlotBoxControl::CreateUISlotBoxControl(unsigned int nIndex, UITexture oTexture)
{
	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f);

	if (oTexture.TextureID == 0) 
	{
		oTexture.SizeX = 32;
		oTexture.SizeY = 32;
	}

	Slot->CreateUITextureControl(nIndex, oTexture);
	ToolTip->CreateUIToolTipControl(0, oTexture.PosX, oTexture.PosY, _T("ToolTip"));	// ���� ��Ʈ�� ����
	ToolTip->EnableOn();

	// �̹��� �ʱ�ȭ
	oTexture.PosX+=m_AddPosX;
	oTexture.PosY+=m_AddPosY;
	oTexture.TextureID = 0;
	oTexture.SizeX = 32;
	oTexture.SizeY = 32;
	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Image->CreateUITextureControl(nIndex, oTexture);
	Image->Hide();
	
	// FX �ʱ�ȭ
	oTexture.Layer = 2051;
	oTexture.TextureID = 23661;
	oTexture.SizeX = 32;
	oTexture.SizeY = 32;
	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Fx->CreateUITextureControl(nIndex, oTexture);

	oTexture.Layer = 2051;
	oTexture.TextureID = 0;
	oTexture.SizeX = 32;
	oTexture.SizeY = 32;
	oTexture.VertexClr = HT_COLOR(0.0f, 0.0f, 0.0f, 0.6f);
	Enable->CreateUITextureControl(nIndex, oTexture);
	m_bCoolTime = false;
}

// ȭ��� �ؽ�ó�� ����մϴ�.
void UISlotBoxControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		Slot->Render(iWindowPosX, iWindowPosY);
		Image->Render(iWindowPosX, iWindowPosY);
		
		if (m_bCoolTime)
		{
			CheckTime();
			Fx->Render(iWindowPosX, iWindowPosY);
		}

		if (m_bEnableCheck)
		{
			Enable->Render(iWindowPosX, iWindowPosY);
		}
	}
}

// ȭ��� �����츦 ����մϴ�.
void UISlotBoxControl::RenderTextureToolTip(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderTexture(iWindowPosX, iWindowPosY);
}

// ȭ��� �ؽ�Ʈ�� ����մϴ�.
void UISlotBoxControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderText(iWindowPosX, iWindowPosY);
}

// �ش� ������ ���콺�� �ִ��� �˻��մϴ�.
bool UISlotBoxControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// ���� �˻縦 ���� ���� ��ǥ������ ������.
	return Slot->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UISlotBoxControl::Move(int iXPos, int iYPos)
{
	Slot->Move(iXPos, iYPos);
	Image->Move(iXPos, iYPos);
	Fx->Move(iXPos, iYPos);
	ToolTip->Move(iXPos, iYPos);
	Enable->Move(iXPos, iYPos);
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UISlotBoxControl::MoveImage(int iXPos, int iYPos)
{
	Image->Move(iXPos, iYPos);
}

// UISlotBoxControl�� ��ġ�� ��ȯ�Ѵ�.
HTvector3 UISlotBoxControl::GetUISlotBoxControlPos()
{
	HTvector3 fPos = Slot->GetUITextureControlPos();
	return fPos;
}

// UISlotBoxControl�� ��ġ�� ��ȯ�Ѵ�.
HTvector3 UISlotBoxControl::GetUISlotImageControlPos()
{
	HTvector3 fPos = Image->GetUITextureControlPos();
	return fPos;
}

// �ش� �ؽ�ó�� �缳���մϴ�.
void UISlotBoxControl::SetSlotBoxControl(int iTextureID, int iLayer)
{
	UITexture oTexture;
	HTvector3 fPos = Slot->GetUITextureControlPos();
	
	delete Image;
	Image = new UITextureControl;

	if (iTextureID == 0)
	{
		Image->Hide();
		m_bEnable = false;

		oTexture.TextureID = 0;
		oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f);
		oTexture.PosX = (int) fPos.x + m_AddPosX;
		oTexture.PosY = (int) fPos.y + m_AddPosX;
		oTexture.Layer = iLayer;
		oTexture.SizeX = 32;
		oTexture.SizeY = 32;
	}
	else
	{
		Image->Show();
		m_bEnable = true;
		
		oTexture.TextureID = iTextureID;
		oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
		oTexture.PosX = (int) fPos.x + m_AddPosX;
		oTexture.PosY = (int) fPos.y + m_AddPosX;
		oTexture.Layer = iLayer;
		oTexture.SizeX = 32;
		oTexture.SizeY = 32;
	}

	Image->CreateUITextureControl(m_nIndex, oTexture);
}

// ���Թڽ��� ��Ÿ�� ����
void UISlotBoxControl::SetSlotBoxCoolTime(DWORD DealyTime, DWORD PastTime)
{
	dwSetTime = timeGetTime();
	dwDealyTime = DealyTime - PastTime;
	m_bCoolTime = true;
	m_bEnable = true;

	SetSlotBoxControlEnable(false);

	// ��Ÿ�� �̹��� ����
	// 32 Frame�� �����. 
	dwFrameTime = DWORD( (float)(DealyTime) / 16.0f);
	dwTotalFrameTime = dwSetTime;
	iCoolTimePos = 0;
	HTvector3 pos = Slot->GetUITextureControlPos();
	
	Fx->Move((int)pos.x + m_AddPosX, (int)pos.y + m_AddPosY);
	Fx->SetScale(32,32);

	if (PastTime > 0)
	{
		HTvector3 pos = Slot->GetUITextureControlPos();
		iCoolTimePos = DWORD( (float)(PastTime) / dwFrameTime);
		Fx->Move((int)pos.x + (iCoolTimePos) + m_AddPosX , (int)pos.y + (iCoolTimePos) + m_AddPosY);
		Fx->SetScale(32-(iCoolTimePos*2), 32-(iCoolTimePos*2));
	}

}

// ���Թڽ��� ��Ÿ�� ����
void UISlotBoxControl::SetSlotBoxCoolTimeCancel()
{
	m_bCoolTime = false;
	SetSlotBoxControlEnable(true);
}

// ���Թڽ��� ��Ÿ��������?
bool UISlotBoxControl::isSlotBoxCoolTime()
{
	return m_bCoolTime;
}

// ���Թڽ��� ������ ��ġ �缳��
void UISlotBoxControl::SetSlotBoxControlPosImage(int iPosX, int iPosY )
{
	m_AddPosX = iPosX;
	m_AddPosY = iPosY;

	this->SetSlotBoxControl(GetUISlotTextureID());
}

// ���Թڽ� ��뿩�� ����
void UISlotBoxControl::SetSlotBoxControlEnable(bool bEnable)
{
	HTvector3 pos = Slot->GetUITextureControlPos();

	Enable->Move((int)pos.x + m_AddPosX, (int)pos.y + m_AddPosY);
	Enable->SetScale(32,32);

	if (bEnable == false)
	{
		Enable->Show();
		m_bEnableCheck = true;
	}
	else
	{
		Enable->Hide();
		m_bEnableCheck = false;
	}
}

// �ð��� üũ�մϴ�.
bool UISlotBoxControl::CheckTime()
{
	if (m_bCoolTime == true)
	{
		DWORD nowTime = timeGetTime();
	
		if ( dwSetTime + dwDealyTime <= nowTime )	// ��Ÿ�� �ð��� ������ ��Ÿ�� ���¸� ������.
		{
			m_bCoolTime = false;
			m_bEnable = true;
			SetSlotBoxControlEnable(true);
			return true;
		}
		else
		{
			if (dwTotalFrameTime + dwFrameTime <= nowTime)
			{
				dwTotalFrameTime+=dwFrameTime; // ���� �ð� ����
				iCoolTimePos++;// ���� ������ �̹��� ����
				HTvector3 pos = Slot->GetUITextureControlPos();
				Fx->Move((int)pos.x + (iCoolTimePos) + m_AddPosX, (int)pos.y + (iCoolTimePos) + m_AddPosY);
				Fx->SetScale(32-(iCoolTimePos*2), 32-(iCoolTimePos*2));
			}
			return false;
		}
	}
	return false;
}

// ������ ����ϴ�.
void UISlotBoxControl::ToolTipHide()
{
	ToolTip->Hide();
}

// ������ ���Դϴ�.
void UISlotBoxControl::ToolTipShow()
{
	ToolTip->Show();
}



//
// UI ScrollBar Control Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UIScrollBarControl::UIScrollBarControl()
{
	Arrow1 = new UIButtonControl;					// ȭ��ǥ1
	Arrow2 = new UIButtonControl;					// ȭ��ǥ2
	Image = new UITextureControl;					// ��ũ�ѹ�
	Line = new UITextureControl;					// ���� �ؽ�ó

	m_bEnable = true;
	m_bDisplay = true;

}
UIScrollBarControl::~UIScrollBarControl()
{
	delete Arrow1;
	delete Arrow2;
	delete Image;
	delete Line;
}

// �����쿡 ����� �ؽ�ó�� �����մϴ�.
void UIScrollBarControl::CreateUIScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType)
{  
	Arrow1->CreateUIButtonControl(0, oTArrow1);
	Arrow2->CreateUIButtonControl(0, oTArrow2);
	Image->CreateUITextureControl(0, oTImage);
	Line->CreateUITextureControl(0, oTLine);

	m_nPosX = oTLine.PosX;
	m_nPosY = oTLine.PosY;
	m_nLengthX = oTLine.SizeX;
	m_nLengthY = oTLine.SizeY;

	m_nValue = 0;
	m_nType = iType;
	m_nMaxValue = iMaxValue;
}

// ȭ��� �ؽ�ó�� ����մϴ�.
void UIScrollBarControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		Arrow1->RenderTexture(iWindowPosX, iWindowPosY);
		Arrow2->RenderTexture(iWindowPosX, iWindowPosY);
		Image->Render(iWindowPosX, iWindowPosY);
		Line->Render(iWindowPosX, iWindowPosY);
	}
}

// ȭ��� �����츦 ����մϴ�.
void UIScrollBarControl::RenderTextureToolTip(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		Arrow1->RenderTextureToolTip(iWindowPosX, iWindowPosY);
		Arrow2->RenderTextureToolTip(iWindowPosX, iWindowPosY);
	}
}

// ȭ��� �ؽ�Ʈ�� ����մϴ�.
void UIScrollBarControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	Arrow1->RenderText(iWindowPosX, iWindowPosY);
	Arrow2->RenderText(iWindowPosX, iWindowPosY);
}

// �ش� ������ ���콺�� �ִ��� �˻��մϴ�.
bool UIScrollBarControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// ���� �˻縦 ���� ���� ��ǥ������ ������.
	return Image->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UIScrollBarControl::Move(int iXPos, int iYPos)
{
	Arrow1->Move(iXPos, iYPos);
	Arrow2->Move(iXPos, iYPos);
	Image->Move(iXPos, iYPos);
	Line->Move(iXPos, iYPos);
}

// ���ϴ� ��ġ�� ��Ʈ���� �̵���ŵ�ϴ�.
void UIScrollBarControl::MoveImage(int iXPos, int iYPos)
{
	Image->Move(iXPos, iYPos);
}

// UIScrollBarControl�� ��ġ�� ��ȯ�Ѵ�.
HTvector3 UIScrollBarControl::GetUIScrollBarControlPos()
{
	return Image->GetUITextureControlPos();
}

// ���� ���� �ƽɾ����� ����Ͽ� ��ũ�ѹ� ��ġ�� ������Ʈ �մϴ�.
void UIScrollBarControl::UpdateScrollBar()
{
	float iPersent =  ( (float) (m_nValue) / (float) m_nMaxValue );
	int XPos = 0, YPos = 0;

	switch(m_nType)
	{
	case 0:	// ����
		YPos = int ( (float(m_nLengthY) - 14) * iPersent );
		Image->Move(m_nPosX - 6 , m_nPosY + YPos);
		break;
	case 1: // ����
		XPos = int ( (float(m_nLengthX) - 14) * iPersent );
		Image->Move(m_nPosX + XPos , m_nPosY + YPos - 6);
		break;
	}
}


//
// UIWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

UIWindow::UIWindow()
{
	Body = new UITextureControl;
	ScaleBar = new UITextureControl;
	TitleBar = new UITextureControl;
	CloseButton = new UIButtonControl;
	TitleStr = new UILabelControl;
	MovingRegion = new UITextureControl;

	m_bEnable = true;
	m_bDisplay = false;
	m_bMovingRegionUsing = false;
	m_bMagnet = false;
	m_bMagnetUsing = false;
	m_bBackgroundDownEnable = false;

	m_nMaxTextureControl = 6;
	m_nMaxLabelControl = 0;
	m_nMaxButtonControl = 0;
	m_bMagnetUsingPro = false;
}

UIWindow::~UIWindow()
{
	delete Body;
	delete TitleBar;
	delete ScaleBar;
	delete CloseButton;
	delete TitleStr;
	delete MovingRegion;

	if (m_UITextureControl.empty() != true) // �Ҵ�� �ؽ�ó ��Ʈ�ѵ� �����Ѵ�.
		for(std::list<UITextureControl*>::iterator pUITextureControl = m_UITextureControl.begin(); pUITextureControl != m_UITextureControl.end();)
		{
			HT_DELETE( *pUITextureControl );
			pUITextureControl = m_UITextureControl.erase( pUITextureControl );
		}

	if (m_UIButtonControl.empty() != true)	// �Ҵ�� ��ư ��Ʈ�ѵ鵵 �����Ѵ�.
		for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UIButtonControl.erase( ZOder );
		}

	if (m_UILabelControl.empty() != true)	// �׿� �� ��Ʈ�� ���� �����Ѵ�.
		for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UILabelControl.erase( ZOder );
		}

	if (m_UILongLabelControl.empty() != true)	// �׿� �� ��Ʈ�� ���� �����Ѵ�.
		for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UILongLabelControl.erase( ZOder );
		}

	if (m_UIEditBoxControl.empty() != true)	// �׿� ������ �ڽ� ��Ʈ�� ���� �����Ѵ�
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UIEditBoxControl.erase( ZOder );
		}

	if (m_UISlotBoxControl.empty() != true)	// �׿� ���Թڽ� �����Ѵ�
		for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UISlotBoxControl.erase( ZOder );
		}

	if (m_UIScrollBarControl.empty() != true)	// �׿� ��ũ�ѹٸ� �����Ѵ�
		for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UIScrollBarControl.erase( ZOder );
		}

	if (m_UITimerControl.empty() != true)	// �׿� Ÿ�̸Ӹ� �����Ѵ�.
		for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UITimerControl.erase( ZOder );
		}
	
	if (m_UICheckBoxControl.empty() != true)	// üũ�ڽ�
		for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UICheckBoxControl.erase( ZOder );
		}
}

// ȭ��� ����� �����츦 �����ϴ� �Լ��Դϴ�.
void UIWindow::CreateUIWindow(unsigned int nIndex, CHTString str, int iPosX, int iPosY, int iSizeX, int iSizeY, HT_COLOR dwColor, func_t* ptr, int nMode)
{
	
	UITexture oTexture;
	UIText oText;
	UITexture ot[3];

	m_nMode = nMode; m_nIndex = nIndex;
	iWindowPosX = iPosX; iWindowPosY = iPosY;
	//m_posX = iWindowPosX;
	//m_posY = iWindowPosY;
	m_ptr = ptr;	// �Լ� ������ ����

	oTexture.PosX = 0; oTexture.PosY = 0; oTexture.SizeX = 1; oTexture.SizeY = 1;oTexture.VertexClr = dwColor; oTexture.Layer = 1300; 
	oTexture.TextureID = UI_TEXTURE_REGION; Body->CreateUITextureControl( 0, oTexture );		// ���� ����
	oTexture.TextureID = UI_TEXTURE_REGION; TitleBar->CreateUITextureControl( 0, oTexture );	// Ÿ��Ʋ�� ����
	oTexture.TextureID = UI_TEXTURE_REGION; ScaleBar->CreateUITextureControl( 0, oTexture );	// ũ�������� ����

	//TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP
	oText.strTitle = str; oText.Font = UI_MAIN_FONT; oText.FontMode = UI_FONT_BORDER; oText.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP; /*TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP;*/
	oText.TextPos.left = 20; oText.TextPos.top = 2; oText.TextPos.right = 110; oText.TextPos.bottom = UI_TOOLTIP_HEIGHT_SIZE;
	//oText.TextColor.r = 1.0f; oText.TextColor.g = 1.0f; oText.TextColor.b = 1.0f; oText.TextColor.a = 1.0f;
	oText.TextColor.r = 0.0f; oText.TextColor.g = 0.0f; oText.TextColor.b = 0.0f; oText.TextColor.a = 1.0f;
	oText.TextShadowColor.r = 1.0f; oText.TextShadowColor.g = 0.8f; oText.TextShadowColor.b = 0.7f; oText.TextShadowColor.a = 1.0f;
	TitleStr->CreateUILabelControl(0, oText);

	switch(nMode)	// �����츦 ��� �׸��� ����
	{
	case 0:	// ���� ����
		break;
	case 1:	// ���� �ְ�, �����Ϲ� ������
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; oTexture.Layer = 1310; this->CreateTextureControl( 10001, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; this->CreateTextureControl( 10002, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; oTexture.Layer = 1320; 	this->CreateTextureControl( 10003, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; this->CreateTextureControl(10004, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_TITLEBAR; oTexture.Layer = 1330; 	this->CreateTextureControl(10005, oTexture );	// Ÿ��Ʋ�� �ؽ�ó
		oTexture.TextureID = UI_TEXTURE_SCALEBAR_ON; this->CreateTextureControl(10006, oTexture );		// �����Ϲ�

		ot[0].Layer = 1340; ot[0].TextureID = UI_TEXTURE_EDGE_BUTTON_NORMAL; ot[0].VertexClr = dwColor; 
		ot[0].PosX = iSizeX - 28; ot[0].PosY = 0; ot[0].SizeX = 28; ot[0].SizeY = 25;	ot[2] = ot[1] = ot[0];
		ot[2].TextureID = UI_TEXTURE_EDGE_BUTTON_DOWN;	ot[1].TextureID = UI_TEXTURE_EDGE_BUTTON_OVER;
		CloseButton->CreateUIButtonControl(0, ot);	// �����ư ����
		break;
	case 2:	// ���� �ְ�, �����Ϲ� �����ȵ�
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; oTexture.Layer = 1310; this->CreateTextureControl( 10001, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; this->CreateTextureControl( 10002, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; oTexture.Layer = 1320; 	this->CreateTextureControl( 10003, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; this->CreateTextureControl(10004, oTexture );	// �ܰ��� ��
		oTexture.TextureID = UI_TEXTURE_TITLEBAR; oTexture.Layer = 1330; 	this->CreateTextureControl(10005, oTexture );	// Ÿ��Ʋ�� �ؽ�ó
		oTexture.TextureID = UI_TEXTURE_SCALEBAR_OFF; this->CreateTextureControl(10006, oTexture );		// �����Ϲ�

		ot[0].Layer = 1340; ot[0].TextureID = UI_TEXTURE_EDGE_BUTTON_NORMAL; ot[0].VertexClr = dwColor; 
		ot[0].PosX = iSizeX - 28; ot[0].PosY = 0; ot[0].SizeX = 28; ot[0].SizeY = 25;	ot[2] = ot[1] = ot[0];
		ot[2].TextureID = UI_TEXTURE_EDGE_BUTTON_DOWN;	ot[1].TextureID = UI_TEXTURE_EDGE_BUTTON_OVER;
		CloseButton->CreateUIButtonControl(0, ot);	// �����ư ����
		break;
	}

	// ��Ʈ�� �ڵ� ��ġ
	this->SetMagnet(-1);	// �⺻���� ����ȭ�鿡 ���� �ڼ���� Ȱ��ȭ
	this->SetBorderTexture(iSizeX, iSizeY);
}

// �Լ� �����͸� ��ȯ�մϴ�.
func_t* UIWindow::GetMessageProcedure()
{
	return m_ptr;
}

// �������� ������ �����մϴ�.
void UIWindow::SetBackgroundColor(HT_COLOR clr)
{
	Body->SetColor(clr);
}

// �������� �⺻ �׵θ� �������� �����մϴ�.
void UIWindow::SetBorderTexture(int iSizeX, int iSizeY, int nType)
{
	Body->SetScale(iSizeX, iSizeY);	// ����

	if (m_nMode)
	{
		TitleBar->Move(0,0); TitleBar->SetScale(128, 16); TitleStr->Move(20, 2);// Ÿ��Ʋ��
		ScaleBar->Move(iSizeX - 19, iSizeY - 18); 	ScaleBar->SetScale(19, 18);	// �����Ϲ�
		// �ֺ� ��Ʈ���� ��ġ������ �ٽ� �����Ѵ�.
		this->SetRegionTextureControl( 10001, 0, 32, 3, iSizeY-32);	// �ܰ��� ��
		this->SetRegionTextureControl( 10002, iSizeX-3, 25, 3, iSizeY-25);		// �ܰ��� ��
		this->SetRegionTextureControl( 10003, 128, 0, iSizeX-156, 3);		// �ܰ��� ��
		this->SetRegionTextureControl( 10004, 0, iSizeY-3, iSizeX-1, 3);		// �ܰ��� ��
		this->SetRegionTextureControl( 10005, 0, 0, 128, 32);		// Ÿ��Ʋ��
		this->SetRegionTextureControl( 10006, iSizeX-19, iSizeY-18, 19, 18);		// �����Ϲ�
		CloseButton->Move(iSizeX-28, 0); CloseButton->SetScale(28, 25);	// �����ư
	}
}


// ȭ��� �����츦 ����մϴ�.
void UIWindow::Render()
{
	if (m_bDisplay == true)
	{
		// �ؽ�ó ����
		Body->Render();					// ���� ���� (Ÿ��Ʋ��, ũ�������� ������ �������� �ʴ´�)

		if (m_UITextureControl.empty() != true)	// �ؽ�ó
			for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
				(*ZOder)->Render(iWindowPosX, iWindowPosY);

		if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ�
			for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != m_UIEditBoxControl.end(); ++ZOder2)
				(*ZOder2)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UISlotBoxControl.empty() != true)	// ���Թڽ�
			for(std::list<UISlotBoxControl*>::iterator ZOder3 = m_UISlotBoxControl.begin(); ZOder3 != m_UISlotBoxControl.end(); ++ZOder3)
				(*ZOder3)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UIScrollBarControl.empty() != true)	// ��ũ�ѹ�
			for(std::list<UIScrollBarControl*>::iterator ZOder4 = m_UIScrollBarControl.begin(); ZOder4 != m_UIScrollBarControl.end(); ++ZOder4)
				(*ZOder4)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UIButtonControl.empty() != true)	// ��ư
			for(std::list<UIButtonControl*>::iterator ZOder5 = m_UIButtonControl.begin(); ZOder5 != m_UIButtonControl.end(); ++ZOder5)
				(*ZOder5)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UICheckBoxControl.empty() != true)	// üũ�ڽ�
			for(std::list<UICheckBoxControl*>::iterator ZOder6 = m_UICheckBoxControl.begin(); ZOder6 != m_UICheckBoxControl.end(); ++ZOder6)
				(*ZOder6)->RenderTexture(iWindowPosX, iWindowPosY);

		// ��ư �ؽ�ó ����
		if (m_nMode != 0)
			CloseButton->RenderTexture(iWindowPosX, iWindowPosY);

		g_pEngineHandler->HT_hrRender2DUI(); 	// ���� ����� ���� �������� ����

		// �ؽ�Ʈ ����
		TitleStr->Render(iWindowPosX, iWindowPosY);

		if (m_UILabelControl.empty() != true)	// ��
			for(std::list<UILabelControl*>::iterator ZOder7 = m_UILabelControl.begin(); ZOder7 != m_UILabelControl.end(); ++ZOder7)
				(*ZOder7)->Render(iWindowPosX, iWindowPosY);

		if (m_UILongLabelControl.empty() != true)	// ��
			for(std::list<UILongLabelControl*>::iterator ZOder8 = m_UILongLabelControl.begin(); ZOder8 != m_UILongLabelControl.end(); ++ZOder8)
				(*ZOder8)->Render(iWindowPosX, iWindowPosY);

		if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ�
			for(std::list<UIEditBoxControl*>::iterator ZOder9 = m_UIEditBoxControl.begin(); ZOder9 != m_UIEditBoxControl.end(); ++ZOder9)
				(*ZOder9)->RenderText(iWindowPosX, iWindowPosY);

		if (m_UITimerControl.empty() != true)	// Ÿ�̸� �ð�üũ
			for(std::list<UITimerControl*>::iterator ZOder10 = m_UITimerControl.begin(); ZOder10 != m_UITimerControl.end(); ++ZOder10)
				if ((*ZOder10)->CheckTime())	// ���� ������ �ð��� �Ǿ��ٸ� ���� �Լ� ȣ��
				{
						func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
						ptr(0, 5, (*ZOder10)->m_nIndex);				// �ش� �޽��� ���ν��� ����
				}

	}
}

// ȭ��� �����츦 ����մϴ�.
void UIWindow::Render_ToolTip()
{
	if (m_bDisplay == true)
	{
		// 2�� ��� (�����κ��� ������ �緣���� �ʿ��ϴ�)
		if (m_UIButtonControl.empty() != true || m_UIScrollBarControl.empty() != true || m_UISlotBoxControl.empty() != true)	// ��ư�̳� ��ũ�ѹ�
		{
			// ��ư �ؽ�ó ����
			if (m_nMode != 0)
				CloseButton->RenderTextureToolTip(iWindowPosX, iWindowPosY);

			for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
				(*ZOder)->RenderTextureToolTip(iWindowPosX, iWindowPosY);
			
			for(std::list<UIScrollBarControl*>::iterator ZOder2 = m_UIScrollBarControl.begin(); ZOder2 != m_UIScrollBarControl.end(); ++ZOder2)
				(*ZOder2)->RenderTextureToolTip(iWindowPosX, iWindowPosY);

			for(std::list<UISlotBoxControl*>::iterator ZOder3 = m_UISlotBoxControl.begin(); ZOder3 != m_UISlotBoxControl.end(); ++ZOder3)
				(*ZOder3)->RenderTextureToolTip(iWindowPosX, iWindowPosY);

			g_pEngineHandler->HT_hrRender2DUI(); 	// ���� ����� ���� �������� ����

			for(std::list<UIScrollBarControl*>::iterator ZOder4 = m_UIScrollBarControl.begin(); ZOder4 != m_UIScrollBarControl.end(); ++ZOder4)
				(*ZOder4)->RenderText(iWindowPosX, iWindowPosY);

			for(std::list<UIButtonControl*>::iterator ZOder5 = m_UIButtonControl.begin(); ZOder5 != m_UIButtonControl.end(); ++ZOder5)
				(*ZOder5)->RenderText(iWindowPosX, iWindowPosY);

			for(std::list<UISlotBoxControl*>::iterator ZOder6 = m_UISlotBoxControl.begin(); ZOder6 != m_UISlotBoxControl.end(); ++ZOder6)
				(*ZOder6)->RenderText(iWindowPosX, iWindowPosY);

			if (m_nMode != 0)
				CloseButton->RenderText(iWindowPosX, iWindowPosY);
		}
	}
}

// ���ϴ� ��ġ�� �����츦 �̵���ŵ�ϴ�.
void UIWindow::MoveWindow(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);	// ����� Ÿ��Ʋ�� �̵�
	iWindowPosX = iXPos;
	iWindowPosY = iYPos;
}

// ���ϴ� ũ��� ������ ����� �����մϴ�.
void UIWindow::ScaleWindow(int iSizeX, int iSizeY)
{
	// �⺻ �ؽ�ó���� �����ġ�� �����մϴ�.
	this->SetBorderTexture(iSizeX, iSizeY);
}

// ���� ������ ũ�⸦ ��ȯ�մϴ�.
HTvector3	UIWindow::GetWindowSize()
{
	int iSizeX, iSizeY;
	Body->GetScale(iSizeX, iSizeY);
	HTvector3 pos;
	pos.x = (float) iSizeX;
	pos.y = (float) iSizeY;

	return pos;
}


int UIWindow::OnLButtonDown(int iXPos, int iYPos)
{
	AdxPosX = g_cUIManager->m_MousePosX;
	AdxPosY = g_cUIManager->m_MousePosY;

	if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)	// �ٵ� �������� �˻��ϵ�
	{
		int hr = 0;

		Body->CheckMouseDown(true);

		// �ش� ������ ������ �Ÿ� ���
		HTvector3 Pos = Body->GetUITextureControlPos();
		iMouseButtonDownXPos = ((int)Pos.x - iXPos);
		iMouseButtonDownYPos = ((int)Pos.y - iYPos);

		// Ÿ��Ʋ�� ������ �ٷ� �̵������ϰ� üũ�ϰ�
		if (TitleBar->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY)) 
		{ 	TitleBar->CheckMouseDown(true); hr = -2;	}
		// ���������� �����ִٸ� �̰͵� �˻�
		if (m_bMovingRegionUsing == true && MovingRegion->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY)) 
		{ 	MovingRegion->CheckMouseDown(true); hr = -2;	}
	
		// �׿��� ���, ��Ŀ���� �����ִ� ���¿��ٸ� ������ �����Ѵ�.
		if ( m_bFocus == false) hr = -2;

		// ��ư�� ���ȴٸ� �� ��ü�鿡 ���� ó���� ���ش�.
		if (m_nMode != 0)
			if (CloseButton->m_nButtonState == 1) { CloseButton->SetButtonDown(); hr = -2; }
		
		if (m_UIButtonControl.empty() != true) 	// �׿� ��ư ��Ʈ�� ó��
			for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
				if ((*ZOder)->m_nButtonState == 1 && (*ZOder)->isEnableOn() == true) { (*ZOder)->SetButtonDown(); hr = -2; }

		// üũ�ڽ� ó��
		if (m_UICheckBoxControl.empty() != true) 	// �׿� ��ư ��Ʈ�� ó��
			for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
					{ 	(*ZOder)->CheckMouseDown(true); hr = -2;	}
					

		// ���Թڽ� ó�� (�����ϴ� ��� ������ �˻��Ͽ� ������ �����쿡�� ���Թ������� ����)
		if (m_UISlotBoxControl.empty() != true)
			for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
			{
				if ( (*ZOder)->isEnableOn() == true && (*ZOder)->m_bEnableCheck == false)
				{
					if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY) )
					{
						int index = (*ZOder)->m_nIndex;
						(*ZOder)->CheckMouseDown(true);
						break;
					}
				}
				hr = -2;
			}

		// ��ũ�ѹ� ó�� (�����ϴ� ��� ��ũ�ѹٸ� �˻��Ͽ� ���� �̹����� ���� �����쿡�� �̹��� �������� ����)
		if (m_UIScrollBarControl.empty() != true)
			for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
			{
				if ((*ZOder)->Arrow1->m_nButtonState == 1) { (*ZOder)->Arrow1->SetButtonDown(); hr = -2; }
				if ((*ZOder)->Arrow2->m_nButtonState == 1) { (*ZOder)->Arrow2->SetButtonDown(); hr = -2; }

				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				{
					(*ZOder)->CheckMouseDown(true);
				}
			}

		if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ó��
			for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				{
					// �ٸ� ��� ��Ŀ���� ���ش�.
					for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != m_UIEditBoxControl.end(); ZOder2++)
						if ((*ZOder2)->isFocusOn() == true)
							(*ZOder2)->SetFocusOff();

					g_EditBoxFocusWindow = this->m_nIndex;
					g_EditBoxFocusControl = (*ZOder)->m_nIndex;
					g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder)->m_str );
					g_cImeMgr.InputString();
					//g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );

					(*ZOder)->SetFocusOn();
                    hr = -2;

					//	�����Ͱ� ä�� �����쿡 ������ ä�� ������ �� �پ��ش�.
					if( m_nIndex == _DIALOG_CHATTINGBOX ||
						m_nIndex == _DIALOG_CHATTING2BOX ||
						m_nIndex == _DIALOG_CHATTING3BOX )
					{
						if ((*ZOder)->m_nIndex == 1)
						{
							//	������ �Էµƴ� ���ڿ��� �����.
							g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
							g_cImeMgr.InputString();
						}
					}

					break;
				}

		// ���� �����Ϲ� ��Ʈ�� ���ɻ����� ������ ����̰�, ������������ �õ��ߴٸ� �������� ���氡���ϵ��� �����.
		if (m_nMode == 1 && ScaleBar->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
		{
			// �ش� ������ ������ �Ÿ� ���
			HTvector3 Pos = Body->GetUITextureControlPos();

			int iSizeX, iSizeY;
			Body->GetScale(iSizeX, iSizeY);

			iMouseButtonDownXPosTail = ((int)Pos.x+iSizeX - iXPos);
			iMouseButtonDownYPosTail = ((int)Pos.y+iSizeY - iYPos);

			ScaleBar->CheckMouseDown(true);
			hr =  -2;	
		}

		return hr;
	}

	return 0; 
}

int UIWindow::OnLButtonUp(int iXPos, int iYPos)	
{
	int iCheck = 0;
	Body->CheckMouseDown(false);
	m_bMagnetUsingPro = false;

	if (TitleBar->isMouseDown() == true) { 	TitleBar->CheckMouseDown(false); iCheck = -2;}
	if (MovingRegion->isMouseDown() == true) { MovingRegion->CheckMouseDown(false); iCheck = -2;}

	// [��ư ��Ʈ�� ó����]
	// �����ư�� -1�� ��ȯ���� ������ UIManager���� ���� ó���� �����ϵ��� ���ش�.
	if (m_nMode != 0)
	{
		if (CloseButton->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
		{ 
			CloseButton->SetButtonOver(); 
			
			func_t* ptr = GetMessageProcedure();						// �Լ� �����͸� ���´�.
			ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, -1);												// �ش� �޽��� ���ν��� ����
			
			if (g_cUIManager->m_bSlotBoxMoving)
			{
				iCheck = -1;
			}
			else
			{
				return -1; 
			}
		}
		else
		{ CloseButton->SetButtonNormal(); }
	}

	// üũ�ڽ� ó��
	if (m_UICheckBoxControl.empty() != true) 	// �׿� ��ư ��Ʈ�� ó��
		for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
			if ((*ZOder)->isMouseDown() == true)
			{ 	
				(*ZOder)->CheckMouseDown(false); 

				// ���� ���¿� ���� ��۵ǰ� ó��
				if ((*ZOder)->GetValue() == true) 
					(*ZOder)->SetValue(false);
				else
					(*ZOder)->SetValue(true);

				if (g_cUIManager->m_bSlotBoxMoving)
				{
					iCheck = -2;
					break;
				}
				else
				{
                    return -2;
				}
			}

	
	if (m_UIButtonControl.empty() != true) 	// �׿� ��ư ��Ʈ�� ó��
		for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
			if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ) && (*ZOder)->isEnableOn() == true)
			{ 
				(*ZOder)->SetButtonOver(); 
				unsigned int index = (*ZOder)->m_nIndex;

				func_t* ptr = GetMessageProcedure();						// �Լ� �����͸� ���´�.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, (*ZOder)->m_nIndex);								// �ش� �޽��� ���ν��� ����

				if (g_cUIManager->m_bSlotBoxMoving)
				{
					iCheck = index;
					break;
				}
				else
				{
                    return index;
				}
			}
			else 
			{ (*ZOder)->SetButtonNormal(); }

	// Ÿ��Ʋ�� �� �����Ϲٰ� ���� ��쿡�� UI������ ó���ϸ� �ǹǷ� 3D �������� �Է� �޽����� ������ �ʿ䰡 ����.
	if (ScaleBar->isMouseDown() == true) {	ScaleBar->CheckMouseDown(false); return -2; }

	// ���� �ڽ� ó��
	bool bCheck = false;
	if (m_UISlotBoxControl.empty() != true) 	// �׿� ��ư ��Ʈ�� ó��
		for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		{
			if ((*ZOder)->isMouseDown() == true)
			{ 
				g_cUIManager->m_bSlotBoxMoving = false;
				(*ZOder)->CheckMouseDown(false); 
				(*ZOder)->CheckFirstMove(true);
				(*ZOder)->ToolTipHide();
				
				// �켱������ �� �����쿡 ���Ҵٸ� ���� ���� ����
				// Step1) ���� ���� ��ġ�� �ش� �������� �������� �����Ͽ� �´ٸ� Ǫ���� �ش��������� �Լ� ȣ��
				if ((*ZOder)->GetUISlotTextureID() == 0) return -2; // �󽽷��� ���
				g_cUIManager->CheckRegionWithSlotBoxPoint(m_nIndex, (*ZOder)->m_nIndex, iXPos, iYPos, (*ZOder)->GetUISlotTextureID());
				return -2;
			}

			if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY) )
				bCheck = true;
		}
	if (bCheck == true) return -2;
	
	// ��ũ�ѹ� ó��
	if (m_UIScrollBarControl.empty() != true)
		for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		{
			if (!(*ZOder)->isMouseDown())
			{ 
				// ��ư 1 ó��
				if ((*ZOder)->Arrow1->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
				{ 
					(*ZOder)->Arrow1->SetButtonOver(); 
					int iValue = (*ZOder)->GetValue();
					
					if (iValue > 0 )
					{
						(*ZOder)->SetValue(iValue-1);
						(*ZOder)->UpdateScrollBar();

						func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
						ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// �ش� �޽��� ���ν��� ����
						return -2;
					}
					return -2;
				}
				else 
				{ (*ZOder)->Arrow1->SetButtonNormal(); }

				// ��ư 2 ó��
				if ((*ZOder)->Arrow2->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
				{ 
					(*ZOder)->Arrow2->SetButtonOver(); 
					int iValue = (*ZOder)->GetValue();

					if (iValue < (*ZOder)->GetMaxValue())
					{
						(*ZOder)->SetValue(iValue+1);
						(*ZOder)->UpdateScrollBar();
		
						func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
						ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// �ش� �޽��� ���ν��� ����
						return -2;
					}
					return -2;
				}
				else 
				{ (*ZOder)->Arrow1->SetButtonNormal(); }
			}

			// ������ �̹��� ó��
			if ((*ZOder)->isMouseDown())
			{ 
				(*ZOder)->CheckMouseDown(false); 
				
				return -2; 
			}
		}

	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ����
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				return (*ZOder)->m_nIndex;

	if (iCheck == -2) return -2;

	// ��Ʈ���� �ƴ� ��׶��念���� Ŭ���ߴٸ� 0�� �����Ͽ�, �������� ��(Pick)���� ó���� �����ϰ� �Ѵ�.
	if (m_bBackgroundDownEnable == true)
	{
		if (m_nIndex == _DIALOG_CHATTINGBOX || m_nIndex == _DIALOG_CHATTING2BOX || m_nIndex == _DIALOG_CHATTING3BOX)
		{
			g_cUIManager->HT_HideWindow(_DIALOG_WHISPERLISTWND);
			g_cUIManager->HT_HideWindow(_DIALOG_CHATCONFIG);
		}

		return 0;
	}
	else
	{
		if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)
			return -2;

		return 0;
	}
}

void UIWindow::FocusOn()	// ž ���°� �ɶ� ó�� �Ǵ� �Լ�
{
	//TitleStr->SetText("Focus On");
	m_bFocus = true;
	HT_COLOR clr;
	clr.r = 1.0f; clr.g = 1.0f; clr.b = 1.0f; clr.a = 0.5f;
	TitleStr->SetTextShadowColor(clr);
}

void UIWindow::FocusOff()	// ž���¿��� �������� ó�� �Ǵ� �Լ�
{
	//TitleStr->SetText("Focus Off");
	m_bFocus = false;
	HT_COLOR clr;
	clr.r = 0.3f; clr.g = 0.3f; clr.b = 0.3f; clr.a = 0.5f;
	TitleStr->SetTextShadowColor(clr);
}

// �����͹ڽ� �ش� ��Ʈ���� ��Ŀ�� ��
void UIWindow::EditBoxFocusOn(unsigned int nIndex)	
{
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ�
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->m_nIndex == nIndex)
			{
				// �ٸ� ��� ��Ŀ���� ���ش�.
				for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != m_UIEditBoxControl.end(); ZOder2++)
					if ((*ZOder)->isFocusOn() == true)
						(*ZOder2)->SetFocusOff();

				g_EditBoxFocusWindow = this->m_nIndex;
				g_EditBoxFocusControl = (*ZOder)->m_nIndex;
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder)->m_str );
				g_cImeMgr.InputString();

				(*ZOder)->SetFocusOn();
			}
}

// �����͹ڽ� �ش� ��Ʈ���� ��Ŀ�� ����
void UIWindow::EditBoxFocusOff(unsigned int nIndex)	
{
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ�
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->m_nIndex == nIndex)
			{
				(*ZOder)->SetFocusOff();
				return;
			}
}

// �����͹ڽ� ��� ��Ʈ���� ��Ŀ�� ����
void UIWindow::EditBoxFocusAllOff()
{
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ�
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->isFocusOn() == true) 
				(*ZOder)->SetFocusOff();
}

// ��Ŀ�� Ȱ��ȭ�� �Էµ� ��� �������� (�⺻�� 0 = ����)
void UIWindow::SetEditBoxFocusOnIME(unsigned int nIndex, int iIME)
{
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ�
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->m_nIndex == nIndex)
			{
				(*ZOder)->m_ImeNo = iIME;	// �Է»��¸� ������ ���·� ����

				if ((*ZOder)->isFocusOn() == true)	// ���� �Է»��¶�� �ٷ�����
					(*ZOder)->SetFocusOnIME(iIME);

				break;
			}
}

// ���콺 R��ư �ٿ�
bool UIWindow::OnRButtonDown(int iXPos, int iYPos)
{
	if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)	// �ٵ� �������� �˻��ϵ�
	{
		// ���Թڽ� ó�� (�����ϴ� ��� ������ �˻��Ͽ� ������ �����쿡�� ���Թ������� ����)
		if (m_UISlotBoxControl.empty() != true)
			for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				{
					(*ZOder)->CheckMouseRDown(true);
				}
		return true;
	}

	return false;
}

// ���콺 R��ư ��
bool UIWindow::OnRButtonUp(int iXPos, int iYPos)
{
	if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)	// �ٵ� �������� �˻��ϵ�
	{
		// ���Թڽ� ó�� (�����ϴ� ��� ������ �˻��Ͽ� ������ �����쿡�� ���Թ������� ����)
		if (m_UISlotBoxControl.empty() != true)
			for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY) && (*ZOder)->isMouseRDown() == true)
				{
					(*ZOder)->CheckMouseRDown(false);
					(*ZOder)->ToolTipHide();

					int index = (*ZOder)->GetUISlotTextureID();
					if (index == 0) return false;

					g_cUIManager->m_nSlotBoxWindowIndex = m_nIndex;
					g_cUIManager->m_nSlotBoxControlIndex = (*ZOder)->m_nIndex;
					g_cUIManager->m_nSlotBoxTextureID = index;

					func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
					ptr(UI_ACTION_MOUSE_RCLK, UI_TARGET_SLOTBOX, (*ZOder)->m_nIndex);	// �ش� �޽��� ���ν��� ����
				}
	}

	return false;
}

// Ű���� �ٿ�
bool UIWindow::OnKeyDown(WPARAM wParam)
{
	if (m_bFocus == true)
	{
	// ���� �������� ������ �ڽ��� Ȱ��ȭ �����ϸ� ���� ��Ŵ
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ����
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->isFocusOn())
		{
            switch(wParam)
			{
				//case VK_CONTROL:
				//	g_Control = true;
				//	return true;
				//case VK_SHIFT:	// ����Ʈ �ٿ�� 
				//	g_RegionCheck = true;
				//	g_Shift = true;
				//	(*ZOder)->m_XPibot = -1;
				//	(*ZOder)->UpdateText();
				//	return true;
				case VK_ESCAPE:	// ESCŰ �ٿ��
					g_Shift = false;
					(*ZOder)->m_bRegion = false;
					 (*ZOder)->SetFocusOff(); 
					 return true;
				case VK_RETURN:	// ���ͽ�
					 //SetFocus(g_hWnd);									// �����͹ڽ� ��Ʈ�� ��Ŀ�� ����
					 //(*ZOder)->SetFocusOff();
					 //this->FocusOff();

					if (m_UIButtonControl.empty() != true)	// ��ư�߿��� ����Ű�� �����ϴ� ��ư�� �߰ߵǸ� ���۽�Ŵ
						for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
						if ((*ZOder)->isEnterOn())
						{
							func_t* ptr = GetMessageProcedure();						// �Լ� �����͸� ���´�.
							ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, (*ZOder)->m_nIndex);								// �ش� �޽��� ���ν��� ����
							return true;
						}
						return true;
				case VK_TAB:	// ��Ű �ٿ�� ��Ŀ�� ��ȯ
					g_Shift = false;
					// ���� ��Ŀ���� �������� ���� Ȱ��ȭ���� ���� ��Ŀ���� ã�´�.
					for(std::list<UIEditBoxControl*>::iterator ZOder2 = ZOder; ZOder2 != m_UIEditBoxControl.end(); ZOder2++)
						if ((*ZOder2)->isFocusOn() == false)
						{
							(*ZOder)->SetFocusOff();
							
							g_EditBoxFocusWindow = this->m_nIndex;
							g_EditBoxFocusControl = (*ZOder2)->m_nIndex;
							g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder2)->GetText() );
							g_cImeMgr.InputString();

							(*ZOder2)->SetFocusOn();
							return true;
						}

					// ������ �� ã�Ҵµ� ���ٸ� �ٽ� ó������ ���� ������ �ڽ� �� ���� �ٽ� �����Ѵ�.
					for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != ZOder; ZOder2++)
						if ((*ZOder2)->isFocusOn() == false)
						{
							(*ZOder)->SetFocusOff();

							g_EditBoxFocusWindow = this->m_nIndex;
							g_EditBoxFocusControl = (*ZOder2)->m_nIndex;
							g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder2)->GetText() );
							g_cImeMgr.InputString();

							(*ZOder2)->SetFocusOn();
							return true;
						}


					break;
				//case VK_LEFT:
				//	g_Pibot++;
				//	
				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->UpdateText();
				//	(*ZOder)->SetStartTime();
				//	return true;
				//case VK_RIGHT:
				//	g_Pibot--;

				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				//case VK_END:
				//	g_Pibot = -1;

				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				//case VK_HOME:
				//	g_Pibot = 10000;

				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				//case VK_DELETE:
				//	g_Shift = false;
				//	g_Pibot--;
				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				case VK_UP:
				case VK_DOWN:
				case VK_PRIOR:
				case VK_NEXT:
					break;

				default:
					//if (g_Shift == true)
					(*ZOder)->m_XPibot = -2;
			}
			break;
		}

	switch(wParam)
	{
		case VK_RETURN:	// ���ͽ�
			if (m_UIButtonControl.empty() != true)	// ��ư�߿��� ����Ű�� �����ϴ� ��ư�� �߰ߵǸ� ���۽�Ŵ
			for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
				if ((*ZOder)->isEnterOn())
				{
					func_t* ptr = GetMessageProcedure();						// �Լ� �����͸� ���´�.
					ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, (*ZOder)->m_nIndex);								// �ش� �޽��� ���ν��� ����
					return true;
				}
	}
	}
	return false;
}

// Ű���� ��
bool UIWindow::OnKeyUp(WPARAM wParam)
{
	if (m_bFocus == true)
	{
	// ���� �������� ������ �ڽ��� Ȱ��ȭ �����ϸ� ���� ��Ŵ
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ����
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->isFocusOn())
		{
		}
	}

	return false;
}

// Ű���� ���� ����
bool UIWindow::OnChar(WPARAM wParam)
{/*
	if (m_bFocus == true)
	{
	// ���� �������� ������ �ڽ��� Ȱ��ȭ �����ϸ� ���� ��Ŵ
	if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ����
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->isFocusOn())
		{
            switch(wParam)
			{
				default:
					if (g_Shift == true)
					{
						
						(*ZOder)->UpdateText();
					}
			}
		}
	}
*/
	return false;
}

bool UIWindow::OnMouseWheel(WPARAM wParam)
{
	// ��ũ�ѹ� ó��
	if (!(m_nIndex == _DIALOG_SKILL || m_nIndex == _DIALOG_CHATLOG1 || m_nIndex == _DIALOG_CHATLOG2))
		return false;

	if (m_UIScrollBarControl.empty() != true)
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
	{
		if( (int)wParam > 0 )
		{
			// ��ư 1 ó��
			//(*ZOder)->Arrow1->SetButtonOver(); 
			int iValue = (*ZOder)->GetValue();
			
			if (iValue > 0 )
			{
				(*ZOder)->SetValue(iValue-1);
				(*ZOder)->UpdateScrollBar();
				func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// �ش� �޽��� ���ν��� ����
				return true;
			}
			return true;
		}
		else if( (int)wParam < 0 )
		{
			// ��ư 2 ó��
			//(*ZOder)->Arrow2->SetButtonOver(); 
			int iValue = (*ZOder)->GetValue();

			if (iValue < (*ZOder)->GetMaxValue())
			{
				(*ZOder)->SetValue(iValue+1);
				(*ZOder)->UpdateScrollBar();
				func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// �ش� �޽��� ���ν��� ����
				return true;
			}
			return true;
		}
	}
	return false;
}

// ������ ��� �޽��� ó��
bool UIWindow::OnSysCommand(WPARAM wParam)
{
	//CHTString str = "";

	//switch (LOWORD(wParam))
	//{
	//case ID_EDIT:
	//	switch (HIWORD(wParam))
	//	{
	//	case EN_KILLFOCUS:	// ��Ʈ ���̳� ��Ÿ ���������� ��Ŀ���� �Ҿ���ȴٸ� ���ӻ󿡼��� Ŀ���� ���ش�.
	//		if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ����
	//			for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
	//				if ((*ZOder)->isFocusOn())
	//				{
	//					(*ZOder)->SetFocusOff();
	//					this->FocusOff();
	//					return true;
	//				}
	//	case EN_CHANGE:
	//		// ������ �ڽ��� ���� �Ѵٸ� Ȱ��ȭ �Ǿ� �ִ��� �����Ͽ�, Ȱ��ȭ �Ǿ� �ִٸ� ���� ���ڿ��� �߰� �����Ѵ�.
	//		if (m_UIEditBoxControl.empty() != true)	// ������ �ڽ� ����
	//			for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
	//				if ((*ZOder)->isFocusOn())
	//				{
	//					(*ZOder)->UpdateText();		// ���� ��Ʈ���� ���ŵǸ� ���� ���̴� �����͹ڽ��� �����մϴ�.
	//					return true;
	//				}
	//	}
	//}
	return false;
}

// ��� �������� ���꿡 ���ؼ� ó������� �� �κ�
void UIWindow::OnMouseMove(int iXPos, int iYPos)
{
	//
	// Step 1) ���콺 ���������� ������ ������ ���� ���� ��ư �������¸� �븻�� �ٲ��ִ� ����ó���� �ʿ��ϴ�.
	//
	if (m_nMode != 0)
	{
		if (!CloseButton->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
		{ if (CloseButton->m_nButtonState != 0) CloseButton->SetButtonNormal(); }
		else
		{ if (CloseButton->m_nButtonState == 0) CloseButton->SetButtonOver();}
	}

	if (m_UIButtonControl.empty() != true) 	// �� ���� ��ư���� �ִٸ� ���� ������� ó��
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if (!(*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY )) 
		{ if ((*ZOder)->m_nButtonState != 0) (*ZOder)->SetButtonNormal(); }
		else
		{ 
			if ((*ZOder)->m_nButtonState == 0)
			{
				if (m_bEnable == true) 
				{
					(*ZOder)->SetButtonOver();
				}
				else
				{
					(*ZOder)->SetButtonNormal();
				}
			}
		}

	if (m_bEnable == false)
		return;

	if (m_UIScrollBarControl.empty() != true) 	// ��ũ�ѹ��� ��ư ó��
	{
		for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		{
			if (!(*ZOder)->isMouseDown()) // ��ũ�ѹٸ� ������ �ʰ� ���������� ó��
			{
				if (!(*ZOder)->Arrow1->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY )) 
				{ if ((*ZOder)->Arrow1->m_nButtonState != 0) (*ZOder)->Arrow1->SetButtonNormal(); }
				else
				{ if ((*ZOder)->Arrow1->m_nButtonState == 0) (*ZOder)->Arrow1->SetButtonOver(); }
			
				if (!(*ZOder)->Arrow2->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY )) 
				{ if ((*ZOder)->Arrow2->m_nButtonState != 0) (*ZOder)->Arrow2->SetButtonNormal(); }
				else
				{ if ((*ZOder)->Arrow2->m_nButtonState == 0) (*ZOder)->Arrow2->SetButtonOver(); }
			}
		}
	}

	// ���Թڽ� ��Ʈ���� �������̶�� �̵���Ű�� ����.
	if (m_UISlotBoxControl.empty() != true) 	// �� ���� ��ư���� �ִٸ� ���� ������� ó��
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
	{
		if ((*ZOder)->isMouseDown())
		{
			if ((*ZOder)->isFixedIcon() == false )
			{
				if ((*ZOder)->isFirstMove() == true ) // ó�� �巹�� �� ����� �õ��ϴ� ���̶�� ���̾� �ֻ����� ����
				{
					g_cUIManager->m_bSlotBoxMoving = true;
					g_cUIManager->m_nSlotBoxWindowIndex = m_nIndex;
					g_cUIManager->m_nSlotBoxControlIndex = (*ZOder)->m_nIndex;
					g_cUIManager->m_nSlotBoxTextureID = (*ZOder)->GetUISlotTextureID();

					(*ZOder)->CheckMouseOver(false);
					(*ZOder)->ToolTipHide();
					(*ZOder)->CheckFirstMove(false);
					(*ZOder)->SetSlotBoxControl((*ZOder)->GetUISlotTextureID(), 2060);
				}

				if (g_cUIManager->m_bSlotBoxMoving == false)	// �̵��� �����Ǿ� �ִµ� ���콺�ٿ� ó�� �Ǿ� �ִٸ� �������·� �ǵ�����.
					CancelSlotBoxImageMoving();

				HTvector3 fPos;
				fPos = Body->GetUITextureControlPos(); // �̹��� �̵��ÿ��� ���̾� �ֻ����� �缳��

				(*ZOder)->MoveImage(iXPos - 16 - (int)fPos.x, iYPos - 16 - (int)fPos.y);
				return;
			}
		}


		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ) == false && (*ZOder)->isMouseOver() == true)
		{
			(*ZOder)->CheckMouseOver(false);
			(*ZOder)->ToolTipHide();
			break;
		}

	}

	// ����â ��� ���� üũ (2 Pass �� ���� �� �Ǿ� �ִ� ������ ��� �ݰ�, �ٽ� �� ������ �Ѵ�.
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ) == true && (*ZOder)->isMouseOver() == false)
		{
			int hr = g_cUIManager->HT_CheckRegionWithPoint(iXPos, iYPos); 
			if (hr == m_nIndex) // ���� ���� �տ� �ִ� â���� ���� ������
			{
				if (g_cUIManager->m_bSlotBoxMoving == true)	// ������ �������̶�� �������� �ʴ´�.
					return;

				(*ZOder)->CheckMouseOver(true);
				
				if (g_cObjectInfo)
					g_cObjectInfo->HT_vObjectInfo_InfoCheck( this->m_nIndex, (*ZOder)->m_nIndex );	// ���Թڽ� ���� ���
				
				(*ZOder)->ToolTipShow();
				//g_cUIManager->HT_ShowWindow(m_nIndex);
				return;
			}
		}


	// ���������� ������̰� �������̶�� �����츦 �������ش�.
	if (m_bMovingRegionUsing == true && MovingRegion->isMouseDown())
	{
		AdxPosX = AdxPosX - g_cUIManager->m_MousePosX;
		AdxPosY = AdxPosY - g_cUIManager->m_MousePosY;

//		if (AdxPosY > 100 || AdxPosY < -100) AdxPosY = 0;
//		if (AdxPosX > 100 || AdxPosX < -100) AdxPosX = 0;

		this->MoveWindow(iXPos+iMouseButtonDownXPos, iYPos+iMouseButtonDownYPos);

		// ���� ������ �ڼ� ����� �����쿡 �����ϸ� �ٴ´�. �Ǵ� ���� ���¿��� �����̸� �ڼ������ �����ȴ�.
		if (m_bMagnet == true) 
			this->SetMagnetProcessing();

		// ���ϵ� ������鵵 ó�����ش�. (�ڼ�������� ���� �ֺ� ������鵵 ���� �����δ�.)
		this->SetChildMagnetProcessing();

		AdxPosX = g_cUIManager->m_MousePosX;
		AdxPosY = g_cUIManager->m_MousePosY;
	}
}

// �������� �ش� �������� ���� �̹����� �����մϴ�.
void UIWindow::CancelSlotBoxImageMoving()
{
	if (m_UISlotBoxControl.empty() != true) 	// �� ���� ��ư���� �ִٸ� ���� ������� ó��
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->isMouseDown()) 
		{
			(*ZOder)->CheckMouseDown(false); 
			(*ZOder)->CheckFirstMove(true);
			(*ZOder)->ToolTipHide();
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
}

// ž �����찡 �Ǿ������� ó���ؾ� �� �κ�
void UIWindow::OnMouseMoveOnlyTop(int iXPos, int iYPos)
{
	// ��ũ�ѹٰ� �������̶�� �̵���Ű�� ����. Ÿ�Կ� ���� �����̵����� �����̵����� ó���Ѵ�.
	if (m_UIScrollBarControl.empty() != true) 	// �� ���� ��ư���� �ִٸ� ���� ������� ó��
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->isMouseDown()) 
		{
			HTvector3 fWindowPos = Body->GetUITextureControlPos();

			// ��ũ�ѹٰ� �������� ���������� ���� �����̴� ��ǥ ���� ����
			if ((*ZOder)->GetType() == 0)	// �����̸� �����̵�
			{
				// ��ũ�ѹ� ��ġ ���
				float fPos = ((float)(iYPos - 7) - fWindowPos.y) - (float)(*ZOder)->m_nPosY;
				float fMaxPos = (float)(*ZOder)->m_nMaxValue;
				float fRatio = ((float)(*ZOder)->m_nLengthY - 14.0f) / fMaxPos;

				int iValue = (int)(fPos / fRatio);
				int iPreValue = (*ZOder)->GetValue();

				// ���� �̵������� �Ѿ�� �����Ѵ�.
				if (iValue < 0) iValue = 0;
				if (iValue > (int)fMaxPos) iValue = (int)fMaxPos;
			
				// ���� ��ȭ�� �������� ���� �� ȣ��
				if (iPreValue != iValue)	
				{
					(*ZOder)->SetValue(iValue);
					(*ZOder)->UpdateScrollBar();

					func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
					ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// �ش� �޽��� ���ν��� ����
					return;
				}
			}
			else	// �����̸� �����̵�
			{
				// ��ũ�ѹ� ��ġ ���
				float fPos = ((float)(iXPos - 7) - fWindowPos.x) - (float)(*ZOder)->m_nPosX;
				float fMaxPos = (float)(*ZOder)->m_nMaxValue;
				float fRatio = ((float)(*ZOder)->m_nLengthX - 14.0f) / fMaxPos;

				int iValue = (int)(fPos / fRatio);
				int iPreValue = (*ZOder)->GetValue();

				// ���� �̵������� �Ѿ�� �����Ѵ�.
				if (iValue < 0) iValue = 0;
				if (iValue > (int)fMaxPos) iValue = (int)fMaxPos;
			
				// ���� ��ȭ�� �������� ���� �� ȣ��
				if (iPreValue != iValue)	
				{
					(*ZOder)->SetValue(iValue);
					(*ZOder)->UpdateScrollBar();

					func_t* ptr = GetMessageProcedure();		// �Լ� �����͸� ���´�.
					ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// �ش� �޽��� ���ν��� ����
					return;
				}
				
			}
			return;
		}

	//
	// Step 2) �׿��� ��쿡�� �ӵ������ ���� ž ������ ���� �ۿ����� ������ ������ �����Ѵ�.
	//
	if (Body->CheckRegionWithPoint(iXPos, iYPos) == false && Body->isMouseDown() == false)
		return;

	//
	// Step 3) Ÿ��Ʋ ������ �ٿ����� ��쿡�� �̵��� �����ϴ�.
	//
	if (TitleBar->isMouseDown())	// Ÿ��Ʋ ����ٿ��ϰ�쿡�� ��ü �̵� (����ó���� ���� ���ش� ������ �������� �ڵ�ó��)
	{
		AdxPosX = AdxPosX - g_cUIManager->m_MousePosX;
		AdxPosY = AdxPosY - g_cUIManager->m_MousePosY;

//		if (AdxPosY > 100 || AdxPosY < -100) AdxPosY = 0;
//		if (AdxPosX > 100 || AdxPosX < -100) AdxPosX = 0;

		this->MoveWindow(iXPos+iMouseButtonDownXPos, iYPos+iMouseButtonDownYPos);

		// ���� ������ �ڼ� ����� �����쿡 �����ϸ� �ٴ´�. �Ǵ� ���� ���¿��� �����̸� �ڼ������ �����ȴ�.
		if (m_bMagnet == true) 
			this->SetMagnetProcessing();

		// ���ϵ� ������鵵 ó�����ش�. (�ڼ�������� ���� �ֺ� ������鵵 ���� �����δ�.)
		this->SetChildMagnetProcessing();

		AdxPosX = g_cUIManager->m_MousePosX;
		AdxPosY = g_cUIManager->m_MousePosY;
	}

	//
	// Step 4) �����Ϲ� ������ �ٿ����� ��� ������ ���� ����
	//
	if (ScaleBar->isMouseDown())
	{
		HTvector3 fPos;
		fPos = Body->GetUITextureControlPos();
		// �ּ� �������� �۰� �����Ϸ��� �� ��� �����Ѵ�.
		int RealX, RealY;
		RealX =  iXPos + iMouseButtonDownXPosTail - (int)fPos.x;
		RealY =  iYPos + iMouseButtonDownYPosTail - (int)fPos.y;

		if ( RealX < UI_MIN_RESIZEX) RealX = UI_MIN_RESIZEX;
		if ( RealY < UI_MIN_RESIZEY) RealY = UI_MIN_RESIZEY;

		this->ScaleWindow(RealX, RealY);
	}
}

// �ڽſ��� ���� ������� ó�� (���� ������ �ش�.)
void UIWindow::SetChildMagnetProcessing()
{
	// �ڼ������� ��������� �����ؼ� ������ ��ŭ�� ���������ش�.
	for(std::list<unsigned int>::iterator ZOder = m_UIMagnetIndex.begin(); ZOder != m_UIMagnetIndex.end(); ++ZOder)
		if (g_cUIManager->HT_GetMagnetState((*ZOder)))	// �ش� �������� �ڼ����� ���
		{
			g_cUIManager->HT_MoveWindow((*ZOder), -AdxPosX, -AdxPosY, 1);	// Ÿ����ġ���� �̵��Ѿ縸ŭ �����ؼ� ������Ų��.
			// ��ӵ� �����쿡 ���ؼ� �ٽ� ��� ó���� �ϰ� �ʹٸ� ���ȣ���� �ϸ� �ȴ�. ������ ��Ӱ��谡 ���� �ɰ�� ���� ������ �����Ƿ� ����
		}
}

// �ű״� ó�� �Լ�
void UIWindow::SetMagnetProcessing()
{
	// �ڽ��� ��ġ�� �˰� �����Ƿ� Ÿ�� �������� ��ġ�� ���´�.
	int TposX, TposY; HTvector3 Tpos;

	// �� �������� ����� ���´�.
	HTvector3 WindowSize = this->GetWindowSize();
	HTvector3 WindowPos = this->GetWindowPos();
	
	//m_bMagnetUsing = true;

	bool bCheck = false, bCheck2 = false;
	if (m_iMagnetWindowIndex != -1)	// �����쿡 ��ӵ� ����� �ش� ������ �ܰ��������� �ڼ�ó��
	{
		// �� �������� ����� ���´�.
		g_cUIManager->HT_GetWindowPos(m_iMagnetWindowIndex, TposX, TposY);
		HTvector3 TWindowSize = g_cUIManager->HT_GetWindowSize(m_iMagnetWindowIndex);

		if (WindowPos.x >= TposX + TWindowSize.x && WindowPos.x < TposX + TWindowSize.x + UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.y + WindowSize.y >= TposY && WindowPos.y < TposY + TWindowSize.y) 
		{
			if ( AdxPosX > 0 || m_bMagnetUsingPro == true) 
			{ 
				bCheck2 = true; WindowPos.x = TposX + TWindowSize.x; m_bMagnetUsingPro = true; 

				if (m_bMagnetUsingPro == true)
					AdxPosX = 0;
			}
			else
			{ AdxPosX = 0;}
		}
		else if (WindowPos.x + WindowSize.x <= TposX && WindowPos.x + WindowSize.x > TposX - UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.y + WindowSize.y >= TposY && WindowPos.y < TposY + TWindowSize.y) 
		{
			if ( AdxPosX < 0 || m_bMagnetUsingPro == true) 
			{ 
				bCheck2 = true; WindowPos.x = TposX - WindowSize.x; m_bMagnetUsingPro = true;	

				if (m_bMagnetUsingPro == true)
					AdxPosX = 0;
			}
			else
			{ AdxPosX = 0;}
		}
		else
		{	bCheck = true;	}

		if (WindowPos.y + WindowSize.y <= TposY && WindowPos.y + WindowSize.y > TposY - UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.x + WindowSize.x >= TposX && WindowPos.x < TposX + TWindowSize.x) 
		{
			if ( AdxPosY < 0 || m_bMagnetUsingPro == true) 
			{ 
				bCheck2 = true; WindowPos.y = TposY - WindowSize.y; m_bMagnetUsingPro = true; 

				if (m_bMagnetUsingPro == true)
					AdxPosY = 0;
			
			}
			else
			{ AdxPosY = 0;}
		}
		else if (WindowPos.y >= TposY + TWindowSize.y && WindowPos.y < TposY + TWindowSize.y + UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.x + WindowSize.x >= TposX && WindowPos.x < TposX + TWindowSize.x)  
		{
			if ( AdxPosY > 0 || m_bMagnetUsingPro == true)	
			{ 
				bCheck2 = true; WindowPos.y = TposY + TWindowSize.y; m_bMagnetUsingPro = true; 

				if (m_bMagnetUsingPro == true)
					AdxPosY = 0;
			}
			else
			{ AdxPosY = 0;}
		}
		else
		{
			if (bCheck == true) m_bMagnetUsingPro = false;	
		}
		
		m_bMagnetUsing = bCheck2;

		this->MoveWindow((int)WindowPos.x, (int)WindowPos.y);
		m_posX = (int)WindowPos.x;
		m_posY = (int)WindowPos.y;
		return;
	}
	
	// �Ϲ��� ��쿡�� �ػ� �ܰ����� �ڼ�ó����

	if (WindowPos.x < UI_MAGNET_DISTANCE_EXIT && WindowPos.x >= 1) 
	{
		if ( AdxPosX > 0 || m_bMagnetUsingPro == true) 
		{ 
			bCheck2 = true; WindowPos.x = 1; m_bMagnetUsingPro = true; 
			AdxPosX2 = -1;
		}
	}
	else if (WindowPos.x + WindowSize.x > g_cUIManager->m_iScreenX - UI_MAGNET_DISTANCE_EXIT && WindowPos.x + WindowSize.x <= g_cUIManager->m_iScreenX) 
	{
		if ( AdxPosX < 0 || m_bMagnetUsingPro == true) 
		{ 
			bCheck2 = true; WindowPos.x = g_cUIManager->m_iScreenX - WindowSize.x; m_bMagnetUsingPro = true;
			AdxPosX2 = 1;
		}
	}
	else
	{	
		bCheck = true;	
		AdxPosX2 = 0;
	}

	if (WindowPos.y < UI_MAGNET_DISTANCE_EXIT && WindowPos.y >= 1) 
	{
		if ( AdxPosY > 0 || m_bMagnetUsingPro == true) 
		{ 
			bCheck2 = true; WindowPos.y = 1; m_bMagnetUsingPro = true; 
			AdxPosY2 = -1;
		}
	}
	else if (WindowPos.y + WindowSize.y > g_cUIManager->m_iScreenY - UI_MAGNET_DISTANCE_EXIT - 17 && WindowPos.y + WindowSize.y <= g_cUIManager->m_iScreenY - 17) 
	{
		if ( AdxPosY < 0 || m_bMagnetUsingPro == true)	
		{ 
			bCheck2 = true; WindowPos.y = g_cUIManager->m_iScreenY - WindowSize.y - 17; m_bMagnetUsingPro = true;	
			AdxPosX2 = 1;
		}
	}
	else
	{
		if (bCheck == true) m_bMagnetUsingPro = false;	
		AdxPosY2 = 0;
	}
	
	m_bMagnetUsing = bCheck2;

	this->MoveWindow((int)WindowPos.x, (int)WindowPos.y);
}

// �������� ��뿩�� ����
void UIWindow::SetMovingRegion(bool isOn, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UITexture oTexture;

	if (isOn)
	{
		m_bMovingRegionUsing = true;
		
		delete MovingRegion;
		MovingRegion = new UITextureControl;
		oTexture.Layer = 1400; oTexture.PosX = iPosX; oTexture.PosY = iPosY; oTexture.SizeX = iSizeX; oTexture.SizeY = iSizeY; oTexture.TextureID = 0; oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
		MovingRegion->CreateUITextureControl(0, oTexture);
		return;
	}

	m_bMovingRegionUsing = false;
}

// üũ�ڽ� ��Ʈ�� ����
void UIWindow::CreateCheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue, int BorderTextureID, int CheckTextureID, int SizeX, int SizeY)
{
	UICheckBoxControl* pUICheckBoxControl = new UICheckBoxControl;
	pUICheckBoxControl->m_nIndex = nIndex;
	pUICheckBoxControl->CreateUICheckBoxControl(nIndex, XPos, YPos, bValue, BorderTextureID, CheckTextureID, SizeX, SizeY);
	m_UICheckBoxControl.push_front(pUICheckBoxControl);
}

// üũ�ڽ� ��Ʈ�� ����
void UIWindow::DeleteCheckBoxControl(unsigned int nIndex)
{
	for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UICheckBoxControl.erase( ZOder );
			return;
		}
}

// üũ�ڽ��� ���� ����
void UIWindow::SetCheckBoxControl(unsigned int nIndex, bool bCheck)
{
	for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetValue(bCheck);
		}
}

// üũ�ڽ��� ���� ����
bool UIWindow::GetCheckBoxControl(unsigned int nIndex)
{
	for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			return (*ZOder)->GetValue();
		}
	return NULL;
}



// �ؽ�ó ��Ʈ�� ����
void UIWindow::CreateTextureControl(unsigned int nIndex, UITexture oTexture )
{
	UITextureControl* pUITextureControl = new UITextureControl;
	pUITextureControl->m_nIndex = nIndex;
	pUITextureControl->CreateUITextureControl(nIndex, oTexture);
	m_UITextureControl.push_front(pUITextureControl);
}

// �ؽ�ó ��Ʈ�� ����
void UIWindow::DeleteTextureControl(unsigned int nIndex)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UITextureControl.erase( ZOder );
			break;
		}
}

// �ؽ�ó ��� �¿��� ���� (true = �� . false = ����)
void UIWindow::SetTextureControlDisplay(unsigned int nControlIndex, bool bOn)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			if (bOn == true)
				(*ZOder)->Show();
			else
				(*ZOder)->Hide();
		}
}

// �ؽ�ó�� �����մϴ�.
void UIWindow::SetTextureControlImage(unsigned int nIndex, int iTextureID )
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			bool m_bCheckRegion = (*ZOder)->isRegion();
			bool m_bCheckMouseDown = (*ZOder)->isMouseDown();
			bool m_bCheckMouseRDown = (*ZOder)->isMouseRDown();
			bool m_bEnable = (*ZOder)->isEnableOn();
			bool m_bDisplay = (*ZOder)->isDisplay();

			UITexture oTexture = (*ZOder)->GetUITextureControl();
			oTexture.TextureID = iTextureID;

			HT_DELETE( *ZOder );
			m_UITextureControl.erase( ZOder );

			UITextureControl* pUITextureControl = new UITextureControl;
			pUITextureControl->m_nIndex = nIndex;
			pUITextureControl->CreateUITextureControl(nIndex, oTexture);
			m_UITextureControl.push_front(pUITextureControl);
			
			pUITextureControl->CheckRegion(m_bCheckRegion); 
			pUITextureControl->CheckMouseDown(m_bCheckMouseDown);
			pUITextureControl->CheckMouseRDown(m_bCheckMouseRDown);
			if (m_bEnable) pUITextureControl->EnableOn(); else pUITextureControl->EnableOff();
			if (m_bDisplay) pUITextureControl->Show(); else pUITextureControl->Hide();
			return;
		}
}

// �ؽ�ó ��Ʈ���� ��ǥ�� ���ɴϴ�.
HTvector3 UIWindow::GetTextureControlPos(unsigned int nControlIndex)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			return (*ZOder)->GetUITextureControlPos();
	return NULL;
}

// �ؽ�ó ������ �����մϴ�.
void UIWindow::SetTextureColor(unsigned int nIndex, HT_COLOR clr )
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetColor(clr);
			return;
		}
}

// ���Թڽ� ��Ʈ�� ����
void UIWindow::CreateSlotBoxControl(unsigned int nIndex, UITexture oTexture)
{
	UISlotBoxControl* pUISlotBoxControl = new UISlotBoxControl;
	pUISlotBoxControl->m_nIndex = nIndex;
	pUISlotBoxControl->CreateUISlotBoxControl(nIndex, oTexture);
	m_UISlotBoxControl.push_front(pUISlotBoxControl);
}

// ���Թڽ� ��Ʈ�� ����
void UIWindow::DeleteSlotBoxControl(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UISlotBoxControl.erase( ZOder );
			return;
		}
}

// �ڼ���� ���� (0 = ���, -1 = ����ȭ��)
void UIWindow::SetMagnet(unsigned int nTargetIndex)
{
	m_bMagnetUsing = false;
	m_iMagnetWindowIndex = nTargetIndex;

	if (nTargetIndex == 0)
	{
		m_bMagnet = false;	// ���� ���
		g_cUIManager->MagnetMgr(nTargetIndex, m_nIndex, false);
	}
	else
	{
		m_bMagnet = true;	// ����
		g_cUIManager->MagnetMgr(nTargetIndex, m_nIndex, true);
	}
}

// Ÿ�� ������ bInsert = true ���� false = ����
void UIWindow::MagnetMgr(unsigned int nTargetIndex, bool bInsert)
{
	if (bInsert == true)	// ����
	{
		m_UIMagnetIndex.push_back(nTargetIndex);
	}
	else	// ����
	{
		for(std::list<unsigned int>::iterator ZOder = m_UIMagnetIndex.begin(); ZOder != m_UIMagnetIndex.end(); ++ZOder)
			if ((*ZOder) == nTargetIndex)
			{
				m_UIMagnetIndex.erase(ZOder);
				return;
			}
	}
}


// ���Թڽ� ��Ʈ�� ������
void UIWindow::SetSlotBoxControl(unsigned int nIndex, int TextureID, int iLayer)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ( (*ZOder)->m_nIndex == nIndex )
		{
			(*ZOder)->SetSlotBoxControl(TextureID, iLayer);
			return;
		}
}

// ���Թڽ��� ������ ��ġ�� �缳���մϴ�.
void UIWindow::SetSlotBoxControlPosImage(unsigned int nControlIndex, int iPosX, int iPosY )
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ( (*ZOder)->m_nIndex == nControlIndex )
		{
			(*ZOder)->SetSlotBoxControlPosImage(iPosX, iPosY);
			return;
		}
}

// ����ó���� (���� ��ġ�� ������ �����ϴ°�? �����Ѵٸ� )
int UIWindow::CheckRegionWithSlotBoxPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY )
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
			return (*ZOder)->m_nIndex;
	return 0;
}

// �ش� ������ �ؽ�óID ���
int	UIWindow::GetUISlotTextureID(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->GetUISlotTextureID();
	return 0;
}

// ���Թڽ��� ��Ÿ�� ����
void UIWindow::SetSlotBoxCoolTime(unsigned int nIndex, DWORD DealyTime, DWORD PastTime)
{	
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetSlotBoxCoolTime(DealyTime, PastTime);
			return;
		}
}

// ���Թڽ��� ��Ÿ�� ����
void UIWindow::SetSlotBoxCoolTimeCancel(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetSlotBoxCoolTimeCancel();
			return;
		}
}

// ���Թڽ��� ��Ÿ��������?
bool UIWindow::isSlotBoxCoolTime(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->isSlotBoxCoolTime();
	return false;
}

// ���Թڽ� ��Ʈ�ѿ��� ������ ����մϴ�.
void UIWindow::SetSlotBoxToolTipOn(unsigned int nControlIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetToolTipOn();
			return;
		}
}

// ���Թڽ� ��Ʈ�ѿ��� ������ ������� �ʽ��ϴ�.
void UIWindow::SetSlotBoxToolTipOff(unsigned int nControlIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetToolTipOff();
			return;
		}
}

// ���Թڽ� ������ �ش� �ؽ�Ʈ ����(���κ�)
void UIWindow::SetSlotBoxControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControl(nIndex, str);
			return;
		}
}

// ���Թڽ� ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
void UIWindow::SetSlotBoxControlTextIndex(unsigned int nControlIndex, unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControlIndex(nIndex);
			return;
		}
}

// ���Թڽ� ������ ������ ���� ���� ����
void UIWindow::SetSlotBoxImageFixed(unsigned int nControlIndex, bool bFixedIcon)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetSlotBoxImageFixed(bFixedIcon);
			return;
		}
}

// ���Թڽ� ���� �ش� ���� �ؽ�Ʈ ���� ����
void UIWindow::SetSlotBoxControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextColorLabelControl(nIndex, clr);
			return;
		}
}

// ���Թڽ� ��뿩�� ����
void UIWindow::SetSlotBoxControlEnable(unsigned int nControlIndex, bool bEnable)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetSlotBoxControlEnable(bEnable);
			return;
		}
}


// ��ũ�ѹ� ��Ʈ�� ����
void UIWindow::CreateScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType)
{
	UIScrollBarControl* pUIScrollBarControl = new UIScrollBarControl;
	pUIScrollBarControl->m_nIndex = nIndex;
	pUIScrollBarControl->CreateUIScrollBarControl(nIndex, oTImage, oTLine, oTArrow1, oTArrow2, iMaxValue, iType);
	m_UIScrollBarControl.push_front(pUIScrollBarControl);
}

// ��ũ�ѹ� ��Ʈ�� ����
void UIWindow::DeleteScrollBarControl(unsigned int nIndex)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIScrollBarControl.erase( ZOder );
			return;
		}
}

// �ش� ��ũ�ѹ��� ���� �����մϴ�.
void UIWindow::SetScrollBarValue(unsigned int nIndex, int iValue)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetValue(iValue);
			return;
		}
}

// �ش� ��ũ�ѹ��� �ִ� ���� �����մϴ�.
void UIWindow::SetScrollBarMaxValue(unsigned int nIndex, int iValue)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetMaxValue(iValue);
			return;
		}
}

// �ش� ��ũ�ѹ��� ���� ���ɴϴ�.
int UIWindow::GetScrollBarValue(unsigned int nIndex)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->GetValue();
	return 0;
}

// Ÿ�̸� ��Ʈ�� ����
void UIWindow::CreateTimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle)
{
	UITimerControl* pUITimerControl = new UITimerControl;
	pUITimerControl->m_nIndex = nIndex;
	pUITimerControl->CreateUITimerControl(nIndex, dwSetTime, iStyle);
	m_UITimerControl.push_front(pUITimerControl);
}

// Ÿ�̸� ��Ʈ�� ����
void UIWindow::DeleteTimerControl(unsigned int nIndex)
{
	for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UITimerControl.erase( ZOder );
			break;
		}
}

// Ÿ�̸� ��
void UIWindow::EnableOnTimerControl(unsigned int nIndex)
{
	for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			(*ZOder)->EnableOn();
}

// Ÿ�̸� ����
void UIWindow::EnableOffTimerControl(unsigned int nIndex)
{
		for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			(*ZOder)->EnableOff();
}

// �� ��Ʈ�� ����
void UIWindow::CreateLabelControl(unsigned int nIndex, UIText oText)
{
	UILabelControl* pUILabelControl = new UILabelControl;
	pUILabelControl->m_nIndex = nIndex;
	pUILabelControl->CreateUILabelControl(nIndex, oText);
	m_UILabelControl.push_front(pUILabelControl);
}

// �� ��Ʈ�� ����
void UIWindow::DeleteLabelControl(unsigned int nIndex)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UILabelControl.erase( ZOder );
			break;
		}
}

// �� ��Ʈ���� �ؽ�Ʈ ����
void UIWindow::SetTextLabelControl(unsigned int nIndex, CHTString str)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetText(str);
			break;
		}
}

// �� ��Ʈ���� �ؽ�Ʈ ���
CHTString UIWindow::GetTextLabelControl(unsigned int nIndex)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
	if ((*ZOder)->m_nIndex == nIndex)
		return (*ZOder)->GetText();

	CHTString str = "";
	return str;
}

// �� ��Ʈ���� �ؽ�Ʈ�÷� ����
void UIWindow::SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}

// �� ��Ʈ���� �ؽ�Ʈ�������÷� ����
void UIWindow::SetTextShadowColorLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextShadowColor(clr);
			break;
		}
}

// �� ��Ʈ���� ���� ��ġ�� �����մϴ�.
void UIWindow::SetArrangementLabelControl(unsigned int nIndex, int iDirection)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetArrangement(iDirection);
			break;
		}
}

// �ն� ��Ʈ�� ����
void UIWindow::CreateLongLabelControl(unsigned int nIndex, UILongText oText)
{
	UILongLabelControl* pUILongLabelControl = new UILongLabelControl;
	pUILongLabelControl->m_nIndex = nIndex;
	pUILongLabelControl->CreateUILabelControl(nIndex, oText);
	m_UILongLabelControl.push_front(pUILongLabelControl);
}

// �ն� ��Ʈ�� ����
void UIWindow::DeleteLongLabelControl(unsigned int nIndex)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UILongLabelControl.erase( ZOder );
			break;
		}
}

// �ն� ��Ʈ���� �ؽ�Ʈ ����
void UIWindow::SetTextLongLabelControl(unsigned int nIndex, HTtchar str[])
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetText(str);
			break;
		}
}

// �ն� ��Ʈ���� �ؽ�Ʈ ���
HTtchar* UIWindow::GetTextLongLabelControl(unsigned int nIndex)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
	if ((*ZOder)->m_nIndex == nIndex)
		return (*ZOder)->GetText();

	CHTString str = "";
	return str;
}

// �ն� ��Ʈ���� �ؽ�Ʈ�÷� ����
void UIWindow::SetTextColorLongLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}

// �ն� ��Ʈ���� �ؽ�Ʈ�������÷� ����
void UIWindow::SetTextShadowColorLongLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextShadowColor(clr);
			break;
		}
}

// �ն� ��Ʈ���� ���� ��ġ�� �����մϴ�.
void UIWindow::SetArrangementLongLabelControl(unsigned int nIndex, int iDirection)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetArrangement(iDirection);
			break;
		}
}


// �����͹ڽ� ��Ʈ�� ����
void UIWindow::CreateEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle)
{
	UIEditBoxControl* pUIEditBoxControl = new UIEditBoxControl;
	pUIEditBoxControl->m_nIndex = nIndex;
	pUIEditBoxControl->CreateUIEditBoxControl(nIndex, oTexture, oText, iStyle);
	m_UIEditBoxControl.push_front(pUIEditBoxControl);
}

// �����͹ڽ� ��Ʈ�� ����
void UIWindow::DeleteEditBoxControl(unsigned int nIndex)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIEditBoxControl.erase( ZOder );
			break;
		}
}

// �����͹ڽ� ��Ʈ���� �ؽ�Ʈ ����
void UIWindow::SetTextEditBoxControl(unsigned int nIndex, CHTString str)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetText(str);
			break;
		}
}

// ����Ʈ�ڽ��� ��带 �����մϴ�
void UIWindow::SetEditBoxControlMode(unsigned int nIndex, int iMode)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetMode(iMode);
			break;
		}
}

// �����͹ڽ� ��Ʈ���� �ؽ�Ʈ�÷� ����
void UIWindow::SetTextColorEditBoxControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}

// �����͹ڽ� ��Ʈ���� �ؽ�Ʈ�������÷� ����
void UIWindow::SetTextShadowColorEditBoxControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextShadowColor(clr);
			break;
		}
}

// �����͹ڽ� ��Ʈ�� ��� ����
CHTString UIWindow::GetTextEditBoxControl(unsigned int nIndex)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->GetText();
	return NULL;
}

// �����͹ڽ� ��Ʈ���� �Է±��� ���̸� �����մϴ�.
void UIWindow::SetEditBoxControlLimitText(unsigned int nControlIndex, unsigned int uiSize)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetLimitText(uiSize);
}


// �����͹ڽ� ��Ʈ���� ���� ��Ŀ���� �����ִ��� �����ִ��� �����մϴ�.
bool UIWindow::isEditBoxFocusOn(unsigned int nControlIndex)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			return (*ZOder)->isFocusOn();
	return false;
}

// ��ư ��Ʈ���� ���¸� �����մϴ�.
void UIWindow::SetButtonControlState(unsigned int nIndex, int iCheck)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetButtonState(iCheck);

			if (iCheck == 3)	// ���� �÷��� ��ư�̶�� �ð�üũ
				(*ZOder)->m_dFlashButtonStartTime = timeGetTime();

			switch((*ZOder)->m_nButtonState)
			{
				case 1:	(*ZOder)->SetButtonNormal(); return;
				case 2:	(*ZOder)->SetButtonOver(); return;
				case 3:	(*ZOder)->SetButtonDown(); return;
				default: (*ZOder)->SetButtonNormal(); return;
			}
		}
}


// ��ư ��Ʈ�ѿ��� ���� ������ �����մϴ�.
void UIWindow::SetButtonToolTip(unsigned int nControlIndex, CHTString str)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetToolTipStr(str);
}

// ��ư ��Ʈ�ѿ��� ������ ����մϴ�.
void UIWindow::SetButtonToolTipOn(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetToolTipOn();
}

// ��ư ��Ʈ�ѿ��� ������ ������� �ʽ��ϴ�.
void UIWindow::SetButtonToolTipOff(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetToolTipOff();
}

// ��ư ������ �ش� �ؽ�Ʈ ����(���κ�)
void UIWindow::SetButtonControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControl(nIndex, str);
			break;
		}
}

// ��ư ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
void UIWindow::SetButtonControlTextIndex(unsigned int nControlIndex, unsigned int nIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControlIndex(nIndex);
			break;
		}
}

// ��ư ���� �ش� ���� �ؽ�Ʈ ���� ����
void UIWindow::SetButtonControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextColorLabelControl(nIndex, clr);
			break;
		}
}


// �ش� ��ư�� ���ͱ���� ŵ�ϴ�.
void UIWindow::SetButtonEnterOn(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetEnterOn();
}

// �ش� ��ư�� ���ͱ���� ���ϴ�.
void UIWindow::SetButtonEnterOff(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetEnterOff();
}

// ��ư Ȱ��ȭ ���� ����
void UIWindow::SetButtonEnable(unsigned int nControlIndex, bool bEnable)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			if ( bEnable == true)
			{
				(*ZOder)->EnableOn();
				(*ZOder)->Show();
			}
			else
			{
				(*ZOder)->EnableOff();
				(*ZOder)->Hide();
			}
		}
}


// ��ư ��Ʈ�� ����
void UIWindow::CreateButtonControl(unsigned int nIndex, UITexture oTexture[3])
{
	UIButtonControl* pUIButtonControl = new UIButtonControl;
	pUIButtonControl->m_nIndex = nIndex;
	pUIButtonControl->CreateUIButtonControl(nIndex, oTexture);
	m_UIButtonControl.push_front(pUIButtonControl);
}


// ��ư ��Ʈ�� ����
void UIWindow::DeleteButtonControl(unsigned int nIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIButtonControl.erase( ZOder );
			break;
		}
}


// �ش� �ؽ�ó ��Ʈ���� ������ ����
void UIWindow::SetRegionTextureControl(unsigned int nIndex, int iXpos, int iYpos, int iSizeX, int iSizeY)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->Move(iXpos, iYpos);
			(*ZOder)->SetScale(iSizeX, iSizeY);
			break;
		}
}

// �ش� �ؽ�ó�� �������� �����մϴ�.
void UIWindow::SetTextureControlScale(unsigned int nIndex, int iSizeX, int iSizeY, int iOSizeX, int iOSizeY)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetScale(iSizeX, iSizeY, iOSizeX, iOSizeY);
			break;
		}
}

// �������� ��ġ�� ��ȯ�Ѵ�.
HTvector3 UIWindow::GetWindowPos()
{
	HTvector3 fPos;
	return fPos = Body->GetUITextureControlPos();
}


// ���� �������� ������ ��ġ �Ͽ��°�??
bool UIWindow::CheckRegionWithPoint(int iXPos, int iYPos)
{
	if (Body->CheckRegionWithPoint(iXPos, iYPos))
		return true;
	return false;
}


//
// CHTUIMessageBox Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIMessageBox::CHTUIMessageBox() {}
CHTUIMessageBox::~CHTUIMessageBox() {}

// nMode = 0 Ȯ�ι�ư��, 1 = Ȯ��/��� ��ư, 2 = �̻��...
void CHTUIMessageBox::HT_vMessageBox(unsigned int nIndex, CHTString str, int nMode)
{
	CHTString strMessage;
	// ������ ����
	// ���� �޽��� �ڽ��� �˾��� ���¶�� �˾��� �޽��� �ڽ��� �ݾƹ�����.
	if (g_cUIManager->HT_isShowMessageBox() == true)
	{
		g_cUIManager->HT_FocusOffEditBoxControl(m_nWindowIndex, 1); 
		g_cUIManager->HT_EnableOnWindow(m_nWindowIndex);
		g_cUIManager->HT_DeleteWindow(m_nIndex);
	}

	// �޽����� �˾� �Ǿ����Ƿ� �ش� �����쿡 Enable�� off ���·� ����� �������� �ʰ� �Ѵ�.
	m_nIndex = UI_WINDOW_MESSAGEBOX + nIndex;	// �޽����ڽ��� �� �����쿡 �ϳ��� ���. (���̵� ������ ���� ������ Index�� �߰��Ǿ� �����ȴ�.)
	m_nWindowIndex = nIndex;					// ������ �ε����� ������ �ֽ��ϴ�.
	m_nMode = nMode;

	g_cUIManager->HT_CreateWindow(m_nIndex, _T("Message"), 329, 125, g_cUIManager->UIMessageBoxMgr.HT_hrMessageBox_InputCheck, 2, HT_COLOR(0.0f, 0.0f, 0.0f, 0.8f));
	g_cUIManager->HT_WindowArrangement(m_nIndex, 5);	
	
	switch (nMode) // ��忡 ���� �پ��� �޽����ڽ��� ����� ���ϴ�.
	{
	case UI_MESSAGEBOX_CONFIRM:	// �������� �޽����ڽ��Դϴ�. Ȯ�ι�ư�� �ִ�...
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//Ȯ   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_RECONFIRM: // Ȯ�� ��ư�� ��� ��ư�� �ִ� ��Ȯ��â �̶�� �� �� �ְڽ��ϴ�.
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//Ȯ   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161);
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//��   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_NUMBERINPUT:	// ����ŷ �������Դϴ�. ���ڸ� �Է��� �� �ִ� ��ȯ���� �׻� �����Դϴ�. ��Ҹ� �������� 0���� ó���ϸ� �ǰڽ��ϴ�. 
		g_strResultText = "";
		g_cUIManager->HT_AddEditBoxControl(m_nIndex, 1, 11, 171, 58, 120, 19);
		g_cUIManager->HT_SetModeEditBoxControl(m_nIndex, 1, 2);
		g_cUIManager->HT_FocusOnEditBoxControl(m_nIndex, 1);
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//Ȯ   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//��   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_CONFIRM_ENTER_NO:	// �������� �޽����ڽ��Դϴ�. Ȯ�ι�ư�� �ִ�... ���ͱ���� �ȸ����� ���Դϴ�.
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//Ȯ   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_INPUT: // �Ϲ����� �Է�â�Դϴ�.
		g_strResultText = "";
		g_cUIManager->HT_AddEditBoxControl(m_nIndex, 1, 11, 171, 58, 120, 19);
		g_cUIManager->HT_FocusOnEditBoxControl(m_nIndex, 1);
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//Ȯ   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//��   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_COUPON:		// ���� �Է�â
		g_strResultText = "";
		g_cUIManager->HT_AddEditBoxControl(m_nIndex, 1, 11, 171, 58, 120, 19, 2);
		g_cUIManager->HT_FocusOnEditBoxControl(m_nIndex, 1);
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//Ȯ   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//��   ��
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	}
	g_cUIManager->HT_EnableOffWindow(nIndex);
	g_cUIManager->HT_ShowWindow(m_nIndex);
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIMessageBox::HT_hrMessageBox_InputCheck(int iAction, int iTarget, int iTargetID)
{

	switch(iTargetID)
	{
	case -2:// ��׶��� �ٿ��
		break;
	case -1:// �����ư�̳� ��� ��ư Ŭ���� �޽��� �ڽ� ���ſ� �Բ� ���� ������ �� Ǯ��
	case 2:	// Ȯ��
	case 3:	// ���
		if (g_cUIManager->UIMessageBoxMgr.m_nMode == 2)
		{
			// �켱 �ؽ�Ʈ ������ UI�޴����� ����
			g_cUIManager->m_strMessageBoxText = g_cUIManager->HT_GetTextEditBoxControl(g_cUIManager->UIMessageBoxMgr.m_nIndex , 1);

			if (iTargetID == 2)
			{
				CHTString str = g_cUIManager->HT_GetTextEditBoxControl(g_cUIManager->UIMessageBoxMgr.m_nIndex , 1);
				g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(atoi(str.HT_szGetString()));
			}
			else
			{
				g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(0);
				return;
			}
		}
		else if (g_cUIManager->UIMessageBoxMgr.m_nMode == 5 || g_cUIManager->UIMessageBoxMgr.m_nMode == 3)// �Ϲ� �޽��� �Է¸��
		{
			if (iTargetID == -1 || iTargetID == 3)
			{
				g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(iTargetID);
				return;
			}

			// �켱 �ؽ�Ʈ ������ UI�޴����� ����
			g_cUIManager->m_strMessageBoxText = g_cUIManager->HT_GetTextEditBoxControl(g_cUIManager->UIMessageBoxMgr.m_nIndex , 1);
			g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(0);
		}
		else
		{
			g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(iTargetID);
			return;
		}
		break;
	}
}

void CHTUIMessageBox::HT_vCloseMessageBox(int iTargetID)
{
	g_cUIManager->HT_FocusOffEditBoxControl(m_nIndex, 1); 
	g_cUIManager->HT_EnableOnWindow(m_nWindowIndex);
	g_cUIManager->HT_CallMessageBoxFunction(m_nWindowIndex, iTargetID);	// UI �޴����� �������� �ܺ��Լ��� ȣ���ϰ� �մϴ�.
}



//
// CHTUIStatus Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIStatus::CHTUIStatus() 
{
	m_sStatus_CharParms = HT_NULL;
	m_sStatus_CharParms = new S_SCP_CHAR_PARAMS_CHANGE;
}

CHTUIStatus::~CHTUIStatus() 
{ 
	HT_DELETE( m_sStatus_CharParms ); 
}


void CHTUIStatus::DrawStatusLabel(int x, int y, int id, CHTString str)
{
	int tid = 11;
	if (x == -1)	// Ÿ��Ʋ ������� �ν��Ͽ� ó��
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 8, 3, y+6, 1400, 36, 6);
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 9, 40, y, 1400, 152, 19);
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 8, 192, y+6, 1400, 136, 6);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 152, 19);
		return;
	}

	if (id == 0 ) 
	{
		tid = 10;
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, tid, x, y); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 79, 19);
	}
	else
	{
		if (strcmp(str, "  ") == 0 ) 
		{
			//g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 9, x, y);
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 79, 19);
		}
		else if (strcmp(str, "   ") == 0 ) 
		{
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 152, 19);
		}
		else
		{
			g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, tid, x, y); 
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 79, 19);
		}
	}

}

// ����â�� �����մϴ�.
void CHTUIStatus::HT_vStatus_Init()
{
	CHTString strMessage;

	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_STATUS, _T("Status"), 331, 465, g_cUIStatus->HT_hrStatus_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_STATUS, 5);

	g_cUIManager->HT_CreateWindow(_DIALOG_BACKGROUND, _T("Message"), 10, 10, g_cUIStatus->HT_hrStatus_InputCheck2, 2);

	//g_cUIManager->HT_SetScriptMessage( eMsgShopExplain04, &strMessage, _T(""), _T("") );	//	�����̾� ������ �߰� ��û�� ����Ⱓ�� �þ�ϴ�.
		
	// �⺻ ����
	void (*ptr)(int, int, int, CHTString) = DrawStatusLabel;
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTitle, &strMessage, _T(""), _T("") );	//	ĳ���� ����
	ptr(-1, 30, 1, strMessage);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramLevel, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5,  55, 0, strMessage); ptr(85,  55, 2, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTrimuriti, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(166, 55, 0, strMessage); ptr(246, 55, 3, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTribe, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5,  76, 0, strMessage); ptr(85,  76, 4, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoPointTriburiti, &strMessage, _T(""), _T("") );	//	�ֽ�����Ʈ
	ptr(166, 76, 0, strMessage); ptr(246, 76, 5, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoOccupation, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5,  97, 0, strMessage); ptr(85,  97, 6, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoKarma, &strMessage, _T(""), _T("") );	//	ī �� ��
	ptr(166, 97, 0, strMessage); ptr(246, 97, 28, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoCast, &strMessage, _T(""), _T("") );	//	ī �� Ʈ
	ptr(5, 118, 0, strMessage); ptr(85, 118, 7, _T("   "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoExplainAshram, &strMessage, _T(""), _T("") );	//	�ƽ�����
	ptr(5, 139, 0, strMessage); ptr(85, 139, 8, _T("   ")); 
	
	// �ɷ»���
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoAblitityStatus, &strMessage, _T(""), _T("") );	//	ĳ���� �ɷ»���
	ptr(-1, 166, 1, strMessage); 
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoLifrPower, &strMessage, _T(""), _T("") );	//	�� �� ��
	ptr(5, 191, 0, strMessage); ptr(85, 191, 9, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoPhysicsAP, &strMessage, _T(""), _T("") );	//	�������ݷ�
	ptr(166, 191, 0, strMessage); ptr(246, 191, 10, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTapas, &strMessage, _T(""), _T("") );	//	Ÿ �� ��
	ptr(5, 212, 0, strMessage); ptr(85, 212, 11, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoAttackRate, &strMessage, _T(""), _T("") );	//	���ݼ�����
	ptr(166, 212, 0, strMessage); ptr(246, 212, 12, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoDefencePower, &strMessage, _T(""), _T("") );	//	�� �� ��
	ptr(5, 233, 0, strMessage); ptr(85, 233, 13, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoEvasionRate, &strMessage, _T(""), _T("") );	//	ȸ �� ��
	ptr(166, 233, 0, strMessage); ptr(246, 233, 14, _T("  "));
	
	// ��ũ��
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoChakra, &strMessage, _T(""), _T("") );	//	��ũ��
	ptr(-1, 260, 1, strMessage); 
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoMuscle, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5, 285, 0, strMessage); ptr(85, 285, 15, _T("  ")); ptr(166, 285, 16, _T(" "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoNerve, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5, 306, 0, strMessage); ptr(85, 306, 17, _T("  ")); ptr(166, 306, 18, _T(" "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoRemaindChakra, &strMessage, _T(""), _T("") );	//	�ܿ���ũ��
	ptr(246, 306, 0, strMessage);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoHeart, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5, 327, 0, strMessage); ptr(85, 327, 19, _T("  ")); ptr(166, 327, 20, _T(" ")); ptr(246, 327, 21, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoSoul, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5, 348, 0, strMessage); ptr(85, 348, 22, _T("  ")); ptr(166, 348, 23, _T(" "));

	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 1, 13, 230, 288, 14, 15);	// ���� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 2, 13, 230, 309, 14, 15);	// �Ű� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 3, 13, 230, 330, 14, 15);	// ���� ��ư
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 4, 13, 230, 351, 14, 15);	// ���� ��ư
	
	// ���׷�
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoResistancePower, &strMessage, _T(""), _T("") );	//	���׷�
	ptr(-1, 375, 1, strMessage);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoFire, &strMessage, _T(""), _T("") );	//	ȭ     ��
	ptr(5,  400, 0, strMessage); ptr(85,  400, 24, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoCold, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(166, 400, 0, strMessage); ptr(246, 400, 25, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoElectric, &strMessage, _T(""), _T("") );	//	��     ��
	ptr(5,  421, 0, strMessage); ptr(85,  421, 26, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoPoison, &strMessage, _T(""), _T("") );	//	��
	ptr(166, 421, 0, strMessage); ptr(246, 421, 27, _T("  "));
}


// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUIStatus::HT_vStatus_SetInfo()
{
	CHTString str;
	
	///* �̸�*/ g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 1, g_oMainCharacterInfo.szCharName ); 
	/* ����*/ str.HT_szFormat( "%d", m_sStatus_CharInfo.byLevel ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 2, str);
	/* �ֽ�*/ str = HT_szStatus_GetTrimuriti(g_oMainCharacterInfo.byTrimuriti); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 3, str);
	/* ����*/ str = HT_szStatus_GetTribe(g_oMainCharacterInfo.snTribe);	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 4, str);
	/* �ֽ� ����Ʈ*/str.HT_szFormat( "%d", g_oMainCharacterInfo.nBrahmanPoint ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 5, str);
	/* ����*/	str = HT_szStatus_GetJobName(g_oMainCharacterInfo.byClass1, g_oMainCharacterInfo.byClass2);	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 6, str);
	/* ī��Ʈ*/	str = HT_szStatus_GetCastClass(g_byteMainCharacterCaste);g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 7, str);
	/* �ƽ���*/	str = g_cGuildSystem->HT_strGuild_GetGuildName(); if( str.HT_bIsEmpty() ) HT_g_Script_SetMessage( eMsgCommonNone, &str); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 8, str);
	/* ü��*/	str.HT_szFormat( "%d / %d", g_cMainCharacter->HT_nMainChar_GetResentHP(), g_cMainCharacter->HT_nMainChar_GetMAXHP() ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 9, str);
	/* �������ݷ�*/str.HT_szFormat( "%d - %d", m_sStatus_CharInfo.kDamage.iMin, m_sStatus_CharInfo.kDamage.iMax ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 10, str);
	/* ���*/	str.HT_szFormat( "%d / %d", g_pMainBar->HT_iMainBar_GetCurTP(), g_pMainBar->HT_iMainBar_GetMaxTP() ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 11, str);
	/* ���� ������*/str.HT_szFormat( "%d", m_sStatus_CharInfo.snAttackRate ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 12, str);
	/* ����*/str.HT_szFormat( "%d", m_sStatus_CharInfo.snAC ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 13, str);
	/* ȸ����*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.snDodgeRate ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 14, str);
	/* ����*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMuscle ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 15, str);
	/* plus - ����*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMuscle-m_sStatus_CharInfo.krgChakra[0].snMuscle ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 16, str);
	/* �Ű�*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snNerves ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 17, str);
	/* plus - �Ű�*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snNerves-m_sStatus_CharInfo.krgChakra[0].snNerves ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 18, str);
	/* ����*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snHeart ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 19, str);
	/* plus - ����*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snHeart-m_sStatus_CharInfo.krgChakra[0].snHeart ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 20, str);
	/* ��ũ�� �� ����Ʈ*/str.HT_szFormat( "%d", m_sStatus_CharInfo.snCPRemaining ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 21, str);
	/* ����*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMind ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 22, str);
	/* plus - ����*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMind-m_sStatus_CharInfo.krgChakra[0].snMind );	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 23, str);
	/* �� */	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snFire ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 24, str);
	/* ����*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snCold );	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 25, str);
	/* ����*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snLightning  ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 26, str);
	/* ��*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snPoison ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 27, str);
	/* ī����*/	str.HT_szFormat( "%d", g_oMainCharacterInfo.snKarma ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 28, str);
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIStatus::HT_vStatus_WindowPopup()
{
	g_cUIManager->HT_ShowWindow(UI_WINDOW_STATUS);
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIStatus::HT_hrStatus_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTargetID)
	{
	case -2:// ��׶��� �ٿ��
		break;
	case -1:// �����ư
		g_cUIManager->HT_HideWindow(UI_WINDOW_STATUS);	break;
	case 1:	// ������ư
	case 2:	// �Ű��ư
	case 3:	// �����ư
	case 4:	// ���Ź�ư
		g_cUIStatus->HT_hrStatus_IncreaseChakra(iTargetID);
		break;
	}
}

// �޽��� �ڽ� ó���Լ�
void CHTUIStatus::HT_hrStatus_InputCheck2(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_MESSAGEBOX:
		switch(g_cUIStatus->m_MessageBoxType)
		{
		case 0:	// Ȯ��â �޽����� ó��
			break;
		case 1:	// // ������ ������� ���ǿ� ���� ����� �� �����ϴ�.
			break;
		case 2://  ��ũ�� �ʱ�ȭ �������� ��� ��Ȯ�� �޼��� ����
			if (iTargetID == 2) 
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemControl->m_dwUseItemKeyID, 0X01 );
				g_cUIStatus->HT_vStatus_SetInfo();	// UI ����
			}
			break;
		case 3:// // ��ų �ʱ�ȭ �������� ��� ��Ȯ�� �޼��� ����
			if (iTargetID == 2)
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemControl->m_dwUseItemKeyID, 0X01 );
				g_cUISkillWindow->HT_vSkillWindow_SetInfo();	// UI ����
			}
			break;
		case 4:// �������� ������� ����Ͻðڽ��ϱ�? [Ȯ��/���]
			// �������� ���� ���� ��Ȯ��â ó��
			if (iTargetID == 2)
			{
                if (g_wResentZoneServerID == 11)
					return;

				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemControl->m_dwUseItemKeyID, 0X01 );
				g_cPortal->HT_vPortal_Chaturanga_Enter();	// �������� ����
			} 
			break;
		case 5:// ����Ʈ �ʱ�ȭ ������ ���� ��Ȯ��â ��� 
			//g_cUIQuestWindow->HT_vQuestWindow_SetInfo();
		case 6://(�ٷ��� ������ ����) �ѱ�����
		case 7://(�ٷ��� ������ ����)  // �ؿܹ���
			if (iTargetID == 2)
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use(g_cItemControl->m_dwSelectedUseItemKeyID,/* sLocRoom.nCellPosx,*/ 0x01 );
			}
			break;
		case 8: // ���� ��Ȯ�� â
			if (iTargetID == 2)
				g_pDuelSystem->HT_vDuel_LButtonCheckForReConfirm(13, 1);
			else
				g_pDuelSystem->HT_vDuel_LButtonCheckForReConfirm(13, 0);
			break;
		case 9:
			if (iTargetID == 2)
			{
				g_cNPCControl->HT_vNetWork_CSP_Req_CharacterInitialize(2,6);
				// ���⿡ ����Ʈ �ʱ�ȭ NPC Ȯ��â�� �³� ��Ŷ�� ������ ������.
			}
			break;
		}
		break;
	}
}

// ��ũ�� ������ư �ٿ�� ȣ��Ǵ� �Լ�
void CHTUIStatus::HT_hrStatus_IncreaseChakra(int iBtnNo)
{
	int iResult = 0;

	// ĳ���Ͱ� ��� �ִ� ��쿡 ���ؼ� ��ư Ŭ�� ������
	if(!g_cMainCharacter->HT_vMainChar_GetCharLive())
		return;

	// �ʿ��� ���� ����
	int iHeart = m_sStatus_CharInfo.krgChakra[0].snHeart;
	int iNerve = m_sStatus_CharInfo.krgChakra[1].snNerves;
	int iTribe = g_oMainCharacterInfo.snTribe;
		
	// ���� ���� 400 ����
	if (iBtnNo == 3 && iHeart >= 400) iResult = 1;

	// ���ٳ� ����ٿ� ���ؼ� �Ű� 350 ����
	if ((iTribe == 4 || iTribe == 8) && iBtnNo == 2 && iNerve >= 350) iResult = 1;

	// ���� ��ũ�� �־�� ��
	if (m_sStatus_CharInfo.snCPRemaining <= 0) iResult = 2;

	// ��� ó��
	switch(iResult)
	{
		case 0:	// ���� ����
			g_pEngineHandler->HT_hrStartSFX( &iResult, HT_FX_CHAKRAUPGRADE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
			HT_vNetWork_CSP_REQ_Increase_Chakra(iBtnNo); // ������ ��û (������ ����)
			break;
		case 1: // ��ũ�� ���ѿ� �ɸ�
			g_cUIManager->ChattingNotify(eMsgChakraCannotUpgrade); //	"��ũ�� ���ѿ� �ɷ� ��ũ�� �ø� �� �����ϴ�."
			break;
		default:
			break;
	}
}

HTint CHTUIStatus::HT_nGetTotalPureChakra()
{
	HTint nTotalChakra = m_sStatus_CharInfo.krgChakra[0].snMuscle + 
		m_sStatus_CharInfo.krgChakra[0].snHeart +
		m_sStatus_CharInfo.krgChakra[0].snNerves +
		m_sStatus_CharInfo.krgChakra[0].snMind ;

	return nTotalChakra;
}

HTint CHTUIStatus::HT_nGetTotalChakra()
{
	HTint nTotalChakra = m_sStatus_CharInfo.krgChakra[1].snMuscle + 
		m_sStatus_CharInfo.krgChakra[1].snHeart +
		m_sStatus_CharInfo.krgChakra[1].snNerves +
		m_sStatus_CharInfo.krgChakra[1].snMind ;

	return nTotalChakra;
}


// ��ũ�� Ȯ�� ��û
void CHTUIStatus::HT_vNetWork_CSP_REQ_Increase_Chakra(int iBtnNo)
{
	PS_CSP_REQ_INCREASE_CHAKRA info = HT_NULL;
	info = new S_CSP_REQ_INCREASE_CHAKRA;
	
	info->byChakra = iBtnNo;
	g_pNetWorkMgr->RequestIncreaseChakra( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("V3_Send_Req_IncreaseChakra: No = %d", info->byChakra );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// �������ͽ� ���Ž� ����
void CHTUIStatus::HT_vStatus_ChangeParams( PS_SCP_RESP_UPDATE_UI info )	
{
	m_sStatus_CharInfo.iTitle					= info->iTitle;					// Title
	m_sStatus_CharInfo.snCPRemaining			= info->snCPRemaining;			// ���� ��ũ�� ����Ʈ
	m_sStatus_CharInfo.byLevel					= info->byLevel;				// �� Level
	m_sStatus_CharInfo.krgChakra[0].snMuscle	= info->krgChakra[0].snMuscle;	// ����
	m_sStatus_CharInfo.krgChakra[0].snNerves	= info->krgChakra[0].snNerves;	// �Ű�
	m_sStatus_CharInfo.krgChakra[0].snHeart		= info->krgChakra[0].snHeart;	// ����
	m_sStatus_CharInfo.krgChakra[0].snMind		= info->krgChakra[0].snMind;	// ����
	m_sStatus_CharInfo.krgChakra[1].snMuscle	= info->krgChakra[1].snMuscle;	// �� ����
	m_sStatus_CharInfo.krgChakra[1].snNerves	= info->krgChakra[1].snNerves;	// �� �Ű�
	m_sStatus_CharInfo.krgChakra[1].snHeart		= info->krgChakra[1].snHeart;	// �� ����
	m_sStatus_CharInfo.krgChakra[1].snMind		= info->krgChakra[1].snMind;	// �� ����
	m_sStatus_CharInfo.snAC						= info->snAC;					// AC
	m_sStatus_CharInfo.snAttackRate				= info->snAttackRate;			// Attack Rate
	m_sStatus_CharInfo.snDodgeRate				= info->snDodgeRate;			// Dodge Rate
	m_sStatus_CharInfo.kResist.snCold			= info->kResist.snCold;			// �ݵ� ����
	m_sStatus_CharInfo.kResist.snFire			= info->kResist.snFire;			// �� ����
	m_sStatus_CharInfo.kResist.snLightning		= info->kResist.snLightning;	// ���� ����
	m_sStatus_CharInfo.kResist.snPoison			= info->kResist.snPoison;		// �� ����
	m_sStatus_CharInfo.kDamage.iMin				= info->kDamage.iMin;			// �ּ� ������
	m_sStatus_CharInfo.kDamage.iMax				= info->kDamage.iMax;			// �ִ� ������
	m_sStatus_CharInfo.kDamage.iFire			= info->kDamage.iFire;			// �� ������
	m_sStatus_CharInfo.kDamage.iCold			= info->kDamage.iCold;			// �ݵ� ������
	m_sStatus_CharInfo.kDamage.iLightning		= info->kDamage.iLightning;	// ���� ������
	m_sStatus_CharInfo.kDamage.iPoison			= info->kDamage.iPoison;		// �� ������
	g_oMainCharacterInfo.nBrahmanPoint			= info->iBramanPoint;			// �ֽ� ����Ʈ

	HT_vStatus_SetInfo();	// ������ ����
}


// ���� ��Ʈ�� ���
CHTString CHTUIStatus::HT_szStatus_GetJobName(int iClass1, int iClass2)
{
	CHTString str;

	switch ( iClass1 )
	{
	case CLASS_LEVEL0: HT_g_Script_SetMessage( eMsgCommonJobBasic, &str, _T("") ); break;// �⺻
	case CLASS_LEVEL1:	// 1�� ����
		switch( iClass2 )
		{
			case CLASS_SATVAN	: HT_g_Script_SetMessage( eMsgCommonJobSatvan, &str, _T("") ); break;// ��Ʈ��
			case CLASS_DHVANTA	: HT_g_Script_SetMessage( eMsgCommonJobDhvanta, &str, _T("") ); break;// ���Ÿ
			case CLASS_NIRVANA	: HT_g_Script_SetMessage( eMsgCommonJobNirvana, &str, _T("") ); break;//�ʹٳ�
			case CLASS_MANTRIKA	: HT_g_Script_SetMessage( eMsgCommonJobMantrika, &str, _T("") ); break;//��Ʈ��ī
			default				: HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;// ����
		}	break;
	case CLASS_LEVEL2:	// 2�� ����
		switch( iClass2 )
		{
			case CLASS_SATVAN1	: HT_g_Script_SetMessage( eMsgCommonJobSatvan1, &str, _T("") ); break;// ��Ʈ��
			case CLASS_SATVAN2	: HT_g_Script_SetMessage( eMsgCommonJobSatvan2, &str, _T("") ); break;// �ٳ���
			case CLASS_DHVANTA1	: HT_g_Script_SetMessage( eMsgCommonJobDhvanta1, &str, _T("") ); break;// ���Ÿ
			case CLASS_DHVANTA2	: HT_g_Script_SetMessage( eMsgCommonJobDhvanta2, &str, _T("") ); break;// ī����
			case CLASS_NIRVANA1	: HT_g_Script_SetMessage( eMsgCommonJobNirvana1, &str, _T("") ); break;// ��ī����
			case CLASS_NIRVANA2	: HT_g_Script_SetMessage( eMsgCommonJobNirvana2, &str, _T("") ); break;// ���̵��
			case CLASS_MANTRIKA1: HT_g_Script_SetMessage( eMsgCommonJobMantrika1, &str, _T("") ); break;// �ƺ�ī��
			case CLASS_MANTRIKA2: HT_g_Script_SetMessage( eMsgCommonJobMantrika2, &str, _T("") ); break;// �縶��Ʈ
			default				: HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;// ����
		}	break;
	default:
		HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;//����
		break;
	}
	return str;
}


// ī��Ʈ ��Ʈ�� ���
CHTString CHTUIStatus::HT_szStatus_GetCastClass(int iCaste)
{ 
	CHTString str2;	HTint iLevel = (iCaste + 1) % 3;
	switch (iLevel)
	{
	case 0:	str2 = _T("1"); break;
	case 1:	str2 = _T("3"); break;
	case 2:	str2 = _T("2"); break;
	}
	
	CHTString str;

	if (eTNCaste_Sudra3 <= iCaste && eTNCaste_Sudra1 >= iCaste)	
		HT_g_Script_SetMessage( eMsgCommonCastSudra, &str, str2);//�����
	else if (eTNCaste_Baisha3 <= iCaste && eTNCaste_Baisha1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastVaisha, &str, str2 );//���̻�
	else if (eTNCaste_Cushatri3 <= iCaste && eTNCaste_Cushatri1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastKshatrya, &str, str2 );//ī��Ʈ����
	else if (eTNCaste_Braman3 <= iCaste && eTNCaste_Braman1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastBraman, &str, str2 );//���
	else if (eTNCaste_Avatara3 <= iCaste && eTNCaste_Avatara1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastAvatara, &str, str2);//�ƹ�Ÿ��
	else if (eTNCaste_MahaRaja3 <= iCaste && eTNCaste_MahaRaja1 >= iCaste)	
		HT_g_Script_SetMessage( eMsgCommonCastReserve, &str, str2 );//���϶���
	else	
		HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") );

	return str;
}


// �ֽ� ��Ʈ�� ���
CHTString CHTUIStatus::HT_szStatus_GetTrimuriti(int iTrimuriti)
{
	CHTString strTrimuriti;

	switch(iTrimuriti)
	{
	case TRIMURITI_BRAHMA: HT_g_Script_SetMessage( eMsgCommonTrimuritiBrahma, &strTrimuriti, _T("") ); break; // ����帶
	case TRIMURITI_VISHNU: HT_g_Script_SetMessage( eMsgCommonTrimuritiVishunu, &strTrimuriti, _T("") ); break; // �񽴴�
	case TRIMURITI_SIVA: HT_g_Script_SetMessage( eMsgCommonTrimuritiSiva, &strTrimuriti, _T("") ); break; // �ù�
	default: HT_g_Script_SetMessage( eMsgCommonNone, &strTrimuriti, _T("") ); break;	// ����
	}

	return strTrimuriti;
}

// ���� ��Ʈ�� ���
CHTString CHTUIStatus::HT_szStatus_GetTribe(int iTribe)
{
	CHTString str;

	switch( iTribe )
	{
		case HT_ID_CHARACTER_NAGA		: HT_g_Script_SetMessage( eMsgCommonTribeNaga, &str, _T("") ); break;
		case HT_ID_CHARACTER_ASURA		: HT_g_Script_SetMessage( eMsgCommonTribeAsura, &str, _T("") ); break;
		case HT_ID_CHARACTER_YAKSA		: HT_g_Script_SetMessage( eMsgCommonTribeYaksha, &str, _T("") ); break;
		case HT_ID_CHARACTER_DEVA		: HT_g_Script_SetMessage( eMsgCommonTribeDeva, &str, _T("") ); break;
		case HT_ID_CHARACTER_KIMNARA	: HT_g_Script_SetMessage( eMsgCommonTribeKimnara, &str, _T("") ); break;
		case HT_ID_CHARACTER_RAKSHASA	: HT_g_Script_SetMessage( eMsgCommonTribeRakshasa, &str, _T("") ); break;
		case HT_ID_CHARACTER_GANDHARVA	: HT_g_Script_SetMessage( eMsgCommonTribeGandharva, &str, _T("") ); break;
		case HT_ID_CHARACTER_GARUDA		: HT_g_Script_SetMessage( eMsgCommonTribeGaruda, &str, _T("") ); break;
		default							: HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;
	}
	return str;
}



//
// CHTUINPCWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUINPCWindow::CHTUINPCWindow() {}
CHTUINPCWindow::~CHTUINPCWindow() {}

// ����â�� �����մϴ�.
void CHTUINPCWindow::HT_vNPCWindow_Init()
{
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_NPCWINDOW, _T("NPC Chatting"), 330, 466, g_cUINPCWindow->HT_hrNPCWindow_InputCheck, 2);

	int y = 31;	CHTString str = "";
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 8, 3, y+6, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 9, 40, y, 1400, 152, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 8, 192, y+6, 1400, 135, 6);
	
	// NPC��
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_NPCWINDOW, 1, str, 0, HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 152, 19);
	
	// ����
	g_cUIManager->HT_AddLongLabelControl(UI_WINDOW_NPCWINDOW, 2, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 65, 311, 130);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 11, 8, 52, 1400, 311, 147);
	g_cUIManager->HT_SetArrangementLongLabelControl(UI_WINDOW_NPCWINDOW, 2, 7);
	
	// ���ù�
	m_StartPosY = 200;
	HT_vNPCWindow_SetInfo();

	g_cUIManager->HT_WindowArrangement(UI_WINDOW_NPCWINDOW, 4);
	g_cUIManager->HT_MoveWindow(UI_WINDOW_NPCWINDOW, 50, 0, 1);

}


// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUINPCWindow::HT_vNPCWindow_SetInfo()
{
	for (int i = 1; i <= 10; ++i)
	{
		g_cUIManager->HT_DelLabelControl(UI_WINDOW_NPCWINDOW, i+2);
		g_cUIManager->HT_DelButtonControl(UI_WINDOW_NPCWINDOW, i);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_NPCWINDOW, i+2, "", 0, HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 8, m_StartPosY+(20*(i-1)), 315, 19);
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_NPCWINDOW, i, 0 , 8, m_StartPosY+(20*(i-1)), 9, 9, 1500, 315, 19);
		g_cUIManager->HT_SetButtonToolTipOff(UI_WINDOW_NPCWINDOW, i);
	}

	for (int i = 3; i < 13; ++i)
	{
		g_cUIManager->HT_SetButtonEnable(_DIALOG_NPCWINDOW, i-3, true);
	}
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUINPCWindow::HT_vNPCWindow_WindowPopup()
{
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUINPCWindow::HT_hrNPCWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	g_cUINPCWindow->m_iButton = iTargetID;
	//g_cUINPCWindow->HT_vNPCWindow_SetInfo();

	HTPoint pPt; pPt.x = 0; pPt.y = 0;
	g_cNPCControl->HT_vNPCControl_ButtonCheck_Dialog(pPt);	// �ܺ��Լ� ���� �ӽ÷�..

	switch (iTarget)
	{
	case UI_TARGET_BUTTON:
		switch(iTargetID)
		{
		case -2:// ��׶��� �ٿ��
			break;
		case -1:// �����ư
			g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();
			//g_cUIManager->HT_HideWindow(UI_WINDOW_NPCWINDOW);	
			break;
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		switch(g_cUINPCWindow->m_MessageBoxNo)
		{
		case -1:	// Ȯ��â��
			break;
		case -3:	// �ֽ� ���� ���� ����
			g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount+1);
			break;
		case -2:	// �ֽź��� ���� Ȯ��
			g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount+1);
			break;
		case 0:	// ������ ���� ��Ȯ��
			if (iTargetID == 2) // Ȯ�� ��ư Ŭ���� ��ġ ����.. �׿ܿ��� â����
				g_pNetWorkMgr->ReqSavePosition(g_cNPCControl->m_iNPCIndex);
			break;
		case 1: // �ֽź��� ��Ȯ��
			if (iTargetID == 2) // Ȯ�� ��ư Ŭ���� ��������. �׿ܿ��� â����
			{
				g_cNPCControl->m_bTrimutiri = 1;
				g_cNPCControl->HT_vNetWork_CSP_Req_Select_Trimuriti(g_cNPCControl->m_bTrimutiri);
			}
			else
			{
				g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount+1); // ��ȭ���� ��ȭ �ٲٱ�
			}
			g_cUINPCWindow->m_MessageBoxNo = 0;
				// �ֽź����尡 ���������� �����ϱ� ����
			break;
		case 2: // ���� ��ȣ �Է�â
			{
				if (iTargetID == -1 || iTargetID == 3)
					return;

				CHTString strtemp = g_cUIManager->m_strMessageBoxText;
				char str[16];
				strncpy(str, strtemp.HT_szGetString(), 16);
				g_pEventWindow->HT_vEventWnd_ReqMsgGameEvent( 1, 2, str);
			}
			break;
		}
		break;
	}
}




//
// CHTUISkillWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUISkillWindow::CHTUISkillWindow() {}
CHTUISkillWindow::~CHTUISkillWindow() {}

// ����â�� �����մϴ�.
void CHTUISkillWindow::HT_vSkillWindow_Init()
{
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_SKILL, _T("Skill"), 330, 466, g_cUISkillWindow->HT_hrSkillWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_SKILL, 5);

	int y = 31;	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 8, 3, y+6, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 8, 129, y+6, 1400, 198, 6);

	// ���� ������ ������ ��� ��ų������ ����� ����.
	int m_Tribe = g_oMainCharacterInfo.snTribe;
	int m_Class1 = g_oMainCharacterInfo.byClass1;
	int m_Class2 = g_oMainCharacterInfo.byClass2;

	m_SkillTabNo = 0;	// ó�� �������� 0

	// ������ Ÿ��Ʋ ��Ʈ���� �� �̸� ����	
	HT_vSkillSetTitle(m_Tribe);

	// ó������ �� ����
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 65, 40, y, 65, 65, 1550, 88, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129, y+6, 65, 65, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194, y+6, 65, 65, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, y+6, 65, 65, 1550, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 88, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, y+6, 65, 19);

	// �����̸� ����
	CHTString str;
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 11, 10, 60, 1400, 79, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTribe, &str, _T(""), _T("") );	//	��     ��
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 0, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 10, 60, 79, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 9, 129, 60, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 4002, m_strTribe, 0, HT_COLOR(1.0f, 0.8f, 0.4f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, 60, 152, 19);

	//��ũ�ѹ�
	//g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_SKILL, 1, 313, 78, 320, 24-7);

	// V3 UI���� ���� ����
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<4; j++)
		{
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex1[i][j] = 0;
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex2[i][j] = 0;
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex3[i][j] = 0;
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex4[i][j] = 0;
			
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo1[i][j] = 0;
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo2[i][j] = 0;
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo3[i][j] = 0;
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo4[i][j] = 0;

			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow1[i][j] = 0;
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow2[i][j] = 0;
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow3[i][j] = 0;
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow4[i][j] = 0;
		}
	}
/*
	// �⺻ ����â ����
	for (int i = 1; i < 8; ++i)
	{
		if (HT_vGetSkillInfo(i-1) == false) HT_vSetSkillInfoblank();
		g_cUISkillWindow->HT_vSkillDrawSkill(i, (m_byLevel+m_byPlusLevel), m_strSkillName, m_strSkillContents, m_strSkillType);
	}

	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 6; ++y)
		{
			if (HT_vGetSkillInfo(x+(y*4)) == false) HT_vSetSkillInfoblank();
			g_cUISkillWindow->HT_vSkillDrawSkill(x+(y*4), (m_byLevel+m_byPlusLevel), m_strSkillName, m_strSkillContents, m_strSkillType);
		}
*/
	// �ܿ� ����Ʈ ���
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 11, 10, 440, 1400, 90, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoSkillPoint, &str, _T(""), _T("") );	//	��ų����Ʈ
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 0, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 10, 440, 90, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 169, 102, 440, 1400, 25, 19);
	str.HT_szFormat("%d", m_ExtraSkillPoint); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 4000, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 102, 440, 25, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 11, 160, 440, 1400, 90, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoGodPoint, &str, _T(""), _T("") );	//	�ֽ� ��ų
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 0, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 160, 440, 90, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 169, 252, 440, 1400, 25, 19);
	str.HT_szFormat("%d", m_ExtraTrimutiritiSkillPoint); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 4001, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 252, 440, 25, 19);
}

// �ش� ��ġ�� ��ų������ ��� �ɴϴ�.
bool CHTUISkillWindow::HT_vGetSkillInfo(int iIndex)
{
	// ���� ��ų�� �����ϴ°��� ���� ����
	int iSlidePos = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_SKILL, 1);
	int iRealValue = iSlidePos + iIndex;
	int iXpos = iRealValue % 4;
	int iYpos = iRealValue / 4;
	DWORD dwSkillUseType = 0;

	switch (m_SkillTabNo)
	{
	case 0: if (m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] <= 0) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo1[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow1[iYpos][iXpos];
		break;
	case 1: if (m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] <= 0) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo2[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow2[iYpos][iXpos];
		break;
	case 2: if (m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] <= 0) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo3[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow3[iYpos][iXpos];
		break;
	case 3: 
		if (m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] <= 0 ) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo4[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow4[iYpos][iXpos];
		break;
	default: 
		return false;
	}
	/*
	m_strSkillContents = "...";	// ���� ���Ѷ����� �ڸ�

	// �нú����� �ƴ��� �˾ƿ���
	if( dwSkillUseType == HT_PCSKILLTYPE_PASSIVE )
		m_strSkillType = "Passive";
	else
		m_strSkillType = "Active";
		*/

	return true;
}

// ��ų�ε����� ���ڷ� ��ų ������ ���ɴϴ�.
int CHTUISkillWindow::HT_vGetSkillLevel(DWORD iIndex)
{
	int m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iIndex );
	//int m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( iIndex );

	return (m_byLevel);//+m_byPlusLevel);
}

DWORD CHTUISkillWindow::HT_vGetSkillIndex(int iSlotNo)
{
	// ���� ��ų�� �����ϴ°��� ���� ����
	int iSlidePos = 0;//g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_SKILL, 1);
	int iRealValue = iSlidePos + iSlotNo;// - 1;
	int iXpos = iRealValue % 4;
	int iYpos = iRealValue / 4;
	DWORD dwSkillUseType = 0;

	switch (m_SkillTabNo)
	{
	case 0: if (m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos];
	case 1: if (m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos];
	case 2: if (m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos];
	case 3: if (m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos];
	}
	return 0;
}

int CHTUISkillWindow::HT_vGetSkillIcon(DWORD iIndex)
{
	// ���� ��ų�� �����ϴ°��� ���� ����
	for (int iYpos = 0; iYpos < 6; ++iYpos)
		for (int iXpos = 0; iXpos < 4; ++iXpos)
		{
			if (m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo1[iYpos][iXpos];
			if (m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo2[iYpos][iXpos];
			if (m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo3[iYpos][iXpos];
			if (m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo4[iYpos][iXpos];
		}
	
	return 0;
}

// ��ų���� 0���� ����
bool CHTUISkillWindow::HT_vSetSkillInfoblank()
{
	m_byLevel = 0;
	m_byPlusLevel = 0;
	m_strSkillName = "";
	m_iSkillIcon = 0;
	m_iSkillArrow = 0;
	m_strSkillContents = "";
	m_strSkillType = "";

	return true;
}

// ������ ���� ��ų�� �� ��Ÿ ��Ʈ�� ����
void CHTUISkillWindow::HT_vSkillSetTitle(int iTribe)
{
	CHTString str;

	switch(iTribe)
	{
		case HT_ID_CHARACTER_NAGA :
		case HT_ID_CHARACTER_KIMNARA :
				HT_g_Script_SetMessage( eMsgCommonSkillAttack, &m_strTitle[0], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonSkillDefence, &m_strTitle[1], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonSkillAssistance, &m_strTitle[2], _T("") );	// ���

				HT_g_Script_SetMessage( eMsgCommonTribeNaga, &m_strTribe, _T("") );
				HT_g_Script_SetMessage( eMsgCommonTribeKimnara, &str, _T("") );
				m_strTribe += _T("/") + str;
				break;
		case HT_ID_CHARACTER_ASURA :
		case HT_ID_CHARACTER_RAKSHASA :
				HT_g_Script_SetMessage( eMsgCommonSkillAssassination, &m_strTitle[0], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonSkillArchery, &m_strTitle[1], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonSkillAssistance, &m_strTitle[2], _T("") );	// ���

				HT_g_Script_SetMessage( eMsgCommonTribeAsura, &m_strTribe, _T("") );
				HT_g_Script_SetMessage( eMsgCommonTribeRakshasa, &str, _T("") );
				m_strTribe += _T("/") + str;
				break;
		case HT_ID_CHARACTER_YAKSA :
		case HT_ID_CHARACTER_GANDHARVA :
				HT_g_Script_SetMessage( eMsgCommonSkillAttack, &m_strTitle[0], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonSkillDefence, &m_strTitle[1], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonSkillAssistance, &m_strTitle[2], _T("") );	// ���

				HT_g_Script_SetMessage( eMsgCommonTribeYaksha, &m_strTribe, _T("") );
				HT_g_Script_SetMessage( eMsgCommonTribeGandharva, &str, _T("") );
				m_strTribe += _T("/") + str;
				break;
		case HT_ID_CHARACTER_DEVA :
		case HT_ID_CHARACTER_GARUDA :
				HT_g_Script_SetMessage( eMsgCommonSkillPhysics, &m_strTitle[0], _T("") );
				HT_g_Script_SetMessage( eMsgCommonSkillBlaze, &str, _T("")  );				
				m_strTitle[0] = m_strTitle[0] + _T("/") + str;// ����/ȭ��
				HT_g_Script_SetMessage( eMsgCommonSkillCold, &m_strTitle[1], _T("") );
				HT_g_Script_SetMessage( eMsgCommonSkillLightning, &str, _T("")  );
				m_strTitle[1] = m_strTitle[1] + _T("/") + str;// �ñ�/����
				HT_g_Script_SetMessage( eMsgCommonSkillMagic, &m_strTitle[2], _T("") );	// ����
				HT_g_Script_SetMessage( eMsgCommonTribeDeva, &m_strTribe, _T("")  );
				HT_g_Script_SetMessage( eMsgCommonTribeGaruda, &str, _T("")  );
				m_strTribe += _T("/") + str;				// ����/�����
				break;
	}
	HT_g_Script_SetMessage( eMsgCommonSkillGod, &m_strTitle[3], _T("") );	// �ֽ�
}

// ��ų�������� �� ��Ȱ�� ���ִ� �Լ�
void CHTUISkillWindow::HT_vSkillDrawTitle(int iIndex)
{

	CHTString str;
	
	// ���� ��Ʈ�� ����
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 101); g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 102); g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 103); g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 104);
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 101); g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 102); g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 103); g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 104);

	for (int i = 0; i < 24; ++i)
	{
		g_cUIManager->HT_DelSlotBoxControl(UI_WINDOW_SKILL, i);
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+1000);
		g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, i+1000);
		g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, i+1000);
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+2000);	// ��ų ȭ��ǥ
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+3000);	// ��ų ȭ��ǥ
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+4000);	// ��ų ȭ��ǥ
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+5000);	// ��ų ȭ��ǥ
	}

	// �缳��
	switch (iIndex)
	{
	case 0:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 65, 40, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 31, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19);
		break;
	case 1:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 63, 40, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 65, 129-23, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 31, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19); 
		break;
	case 2:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 63, 40, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 65, 194-23, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 31, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19); 
		break;
	case 3:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 63, 40, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194-23, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 65, 259-23, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259-23, 31, 88, 19);
		break;
	}

}

// ��ų�������� ��ų ����� �ϴ� �Լ�
void CHTUISkillWindow::HT_vSkillDrawSkill(int iIndex, int iLevel, CHTString strName, CHTString strContemts, CHTString strType)
{
//	int y = 80 + ((iIndex-1) * 46); // ��� Y ��ġ ����
//	int x = 0;
	int x = iIndex % 4;
	int y = iIndex / 4;

	y = (y * 60) + 88;
	x = (x * 79) + 10;

	// ���� ��ų ������ ��ų�� �ִ뷹���� �����Ͽ� ���̻� �ø� �� ���ٸ� ��ư�� ������� �ʴ´�.
	DWORD dwIndex = HT_vGetSkillIndex(iIndex);
	if (dwIndex == 0) return;

	BYTE byCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwIndex ); // ���� ��ų ����
	BYTE byMaxLevel = 0;
	HTint iOut;
	HTbyte byteOut;
	BYTE byCharLevel = g_cStatus->HT_byGetLevel();

	CHTString str;
	str.HT_szFormat("%d",byCurLevel);

	// �� ��ų�� ����ϱ� ���� ���� ��µ� �������� �����ݴϴ�.
	g_cUIManager->HT_DelSlotBoxControl(UI_WINDOW_SKILL, iIndex);
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+1000);
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, iIndex+1000);
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, iIndex+1000);
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+2000);	// ��ų ȭ��ǥ
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+3000);	// ��ų ȭ��ǥ
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+4000);	// ��ų ȭ��ǥ
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+5000);	// ��ų ȭ��ǥ

	// ��ų ����� ���� ���Ӱ� �����մϴ�.
	//g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_SKILL, iIndex, 0, 5+x, y); //������(5,80)
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_SKILL, iIndex, 66, 5+x, y); //������(5,80)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+1000, 169, 41+x, y, 1400, 25, 17);//����ǥ��(41,80)
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+1000, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 41+x, y, 25, 17);

	if( byCurLevel == 0 )
		g_pParamMgr->HT_bGetPCSkillMaxLevel( dwIndex, byCurLevel+1, &byMaxLevel );
	else
		g_pParamMgr->HT_bGetPCSkillMaxLevel( dwIndex, byCurLevel, &byMaxLevel );

	if (byCurLevel < byMaxLevel)
        g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, iIndex+1000, 14, 41+x, y+22, 14, 15);//������¹�ư(41,106)

	// �ش� ��ų�� ���� ȭ��ǥ�� �׸��ϴ�.
	if (m_iSkillArrow == 23830)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//ȭ��ǥ ǥ��(41,80)
	}
	else if (m_iSkillArrow == 23831)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//ȭ��ǥ ǥ��(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+3000, 183, 41+x+5-20, y+35+11, 1400);//ȭ��ǥ ǥ��(41,80)
	}
	else if (m_iSkillArrow == 23832)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//ȭ��ǥ ǥ��(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+3000, 183, 41+x+5-20, y+35+11, 1400);//ȭ��ǥ ǥ��(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+4000, 183, 41+x+5+79-20, y+35+11, 1400);//ȭ��ǥ ǥ��(41,80)
	}
	else if (m_iSkillArrow == 23592)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//ȭ��ǥ ǥ��(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+3000, 183, 41+x+5-20, y+35+11, 1400);//ȭ��ǥ ǥ��(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+4000, 183, 41+x+5+79-20, y+35+11, 1400);//ȭ��ǥ ǥ��(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+5000, 183, 41+x+5+79+79-20, y+35+11, 1400);//ȭ��ǥ ǥ��(41,80)
	}

	// ���Թڽ��� �������� ���Դϴ�.
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_SKILL, iIndex, 2, 2); //������(5,80)
	g_cUIManager->HT_SetSlotImage(UI_WINDOW_SKILL, iIndex, m_iSkillIcon); //������(5,80)

	// �нú� ��ų�̰ų� ��ų������ 0�� ��ų �������� �巹�װ� ���� �ʽ��ϴ�.
	DWORD dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwIndex );
	if( dwSkillUseType == HT_PCSKILLTYPE_PASSIVE || byCurLevel == 0)
		g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);

	// �ٸ� ���ǿ� ���� ������ ���̻� �ø� �� ���ٸ� ������ ó�� �մϴ�.
	if( byCurLevel == 0 && g_pParamMgr->HT_bLockID( dwIndex, byCurLevel+1 ) == true )
	{
		// �䱸������ �ȵǸ� ������ ó��
		if( g_pParamMgr->HT_bGetPCSkillReqLevel( &byteOut ) == true && byteOut > 0 )
		{
			if( g_cStatus->HT_byGetLevel() < byteOut ) 
			{
				g_cUIManager->HT_SetSlotBoxControlEnable(UI_WINDOW_SKILL, iIndex, false);
				g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);
			}

		}// �������� ��ų�� ������ ���� ���¶�� ������ ó��
		if( g_pParamMgr->HT_bGetPCSkillReqSkill1( &iOut ) == true && iOut > 0)
		{
			g_pParamMgr->HT_bGetPCSkillReqSkill1_Lvl( &byteOut );
			HTbyte byReqCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iOut );

			if( byReqCurLevel < byteOut ) 
			{
				g_cUIManager->HT_SetSlotBoxControlEnable(UI_WINDOW_SKILL, iIndex, false);
				g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);
			}

		}
		if( g_pParamMgr->HT_bGetPCSkillReqSkill2( &iOut ) == true && iOut > 0 )
		{
			g_pParamMgr->HT_bGetPCSkillReqSkill2_Lvl( &byteOut );
			HTbyte byReqCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iOut );

			if( byReqCurLevel < byteOut ) 
			{
				g_cUIManager->HT_SetSlotBoxControlEnable(UI_WINDOW_SKILL, iIndex, false);
				g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);
			}
		}
		g_pParamMgr->HT_bUnLockID( dwIndex, byCurLevel+1 );
	}

	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 9, 69, y, 1400, 175, 17);//��ų�̸�(69,80)
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+1000, strName, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 69, y, 175, 17);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 9, 69, y+21, 1400, 175, 17);//��ų����(69,101)
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+2000, strContemts, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 69, y+21, 175, 17);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 10, 246, y, 1400, 68, 17);//��ų�������(246,80)    
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+3000, strType, 0, HT_COLOR(1.0f, 0.8f, 0.4f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 246, y, 68, 17);
}

// ��ų�������� ��ų �簻��
void CHTUISkillWindow::HT_vSkillUpdate(int iIndex)
{/*
	CHTString str;
	
	str.HT_szFormat("%d",m_byLevel+m_byPlusLevel);
	g_cUIManager->HT_SetSlotImage(UI_WINDOW_SKILL, iIndex, m_iSkillIcon); //������(5,80)
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex, str);	// ��ų����
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex+1000, m_strSkillName);	// ��ų�̸�
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex+2000, m_strSkillContents);	// ��ų����
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex+3000, m_strSkillType);		// ��ųŸ��
*/	
}


// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUISkillWindow::HT_vSkillWindow_SetInfo()
{/*
	// ���� ��ġ�� �°� ��ų���� �����Ͽ� ���
	for (int i=1; i<8; ++i) 
	{
		if (HT_vGetSkillInfo(i-1) == false) HT_vSetSkillInfoblank();
		HT_vSkillUpdate(i);
	}
*/
	CHTString str;

//	HT_g_vLogFile("_Skill OutPut Start.\n");
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 6; ++y)
		{
			if (HT_vGetSkillInfo(x+(y*4)) == true) 
			{
				HT_vSkillDrawSkill(x+(y*4), (m_byLevel)/*+m_byPlusLevel)*/, m_strSkillName, m_strSkillContents, m_strSkillType);
			}
			else
			{
				HT_vSetSkillInfoblank();
			}

//			str.HT_szFormat("[%s:%d], ", m_strSkillName.HT_szGetString(), m_byLevel);
//			HT_g_vLogFile( str);
		}

//	HT_g_vLogFile("_Skill OutPut End.\n");

	// �ܿ�����Ʈ ����
	//CHTString str;
	str.HT_szFormat("%d", m_ExtraSkillPoint); 
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, 4000, str);
	str.HT_szFormat("%d", m_ExtraTrimutiritiSkillPoint);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, 4001, str);
}

// ��ų ����Ʈ�� ���ɴϴ�.
HTint CHTUISkillWindow::HT_nGetSkillPoint()
{
	return m_ExtraSkillPoint;
}

// �ֽ� ��ų ����Ʈ�� ���ɴϴ�.
HTint CHTUISkillWindow::HT_nGetGodSkillPoint()
{
	return m_ExtraTrimutiritiSkillPoint;
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUISkillWindow::HT_vSkillWindow_WindowPopup()
{
	HT_vSkillWindow_SetInfo();
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUISkillWindow::HT_hrSkillWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iAction)
	{
		case UI_ACTION_MOUSE_L_UP:
			switch(iTarget)
			{
			case UI_TARGET_BUTTON:	// ��ư�� ��� ó��
				switch(iTargetID)
				{
				case -2:// ��׶��� �ٿ��
					break;
				case -1:// �����ư
					g_cUIManager->HT_HideWindow(UI_WINDOW_SKILL);
					break;
				case 101: case 102: case 103: case 104:				// �ܹ�ư Ŭ���� ����
					g_cUISkillWindow->m_SkillTabNo = iTargetID-101;
					g_cUISkillWindow->HT_vSkillDrawTitle(g_cUISkillWindow->m_SkillTabNo);
					g_cUISkillWindow->HT_vSkillWindow_SetInfo();
					break;
				}

				if (iTargetID >= 1000 && iTargetID < 1024)	// ��ư Ŭ���� ��ư ó��
					g_cSkillInventory->HT_vNetWork_CSP_Skill_LearnSkill( iTargetID - 1000 );
				break;
//			case UI_TARGET_SCROLLBAR:	// ��ũ�ѹ��� ��� ó��
//				g_cUISkillWindow->HT_vSkillWindow_SetInfo();
//				break;

			case UI_TARGET_SLOTBOX:
				g_cUIManager->HT_RefuseSlotImageMoving();
				break;
			}
		break;
	}
}



//
// CHTUIRefineWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIRefineWindow::CHTUIRefineWindow() {}
CHTUIRefineWindow::~CHTUIRefineWindow() {}

// ����â�� �����մϴ�.
void CHTUIRefineWindow::HT_vRefineWindow_Init()
{
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_REFINE, _T("Refine"), 330, 238, g_cUIRefineWindow->HT_hrRefineWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_REFINE, 5);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 8, 3, 37, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 39, 31, 1400, 89, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningTitle, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 39, 31, 89, 19);//��      ��
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 8, 129, 37, 1400, 198, 6);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 146, 56, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningTargetItem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 146, 56, 152, 19);//���� ��� ������

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 146, 122, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningItem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 146, 122, 152, 19);//���� ���

	// �ٸ�ź �ؽ�ó �ִϸ��̼� 74- 79
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59);
	g_cUIManager->HT_AddTimerControl(UI_WINDOW_REFINE, 1, 100);
	g_cUIManager->HT_EnableOnTimerControl(UI_WINDOW_REFINE, 1);

	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE,1, 31 ,17, 59);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 16, 164, 1400, 130, 18);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 164, 58, 19);//���Ǿ�

	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 1, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 71, 164, 59, 19);
	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_REFINE, 1, 5);

	// ���� ���� �߰� 62
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,1, 66 ,205, 81);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 1, 2, 2);

	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,2, 66 ,168, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 2, 2, 2);
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,3, 66 ,205, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 3, 2, 2);
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,4, 66 ,242, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 4, 2, 2);

	// ��ư 99, 97, 98
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_REFINE, 1,  159, 56, 201, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 56, 201, 64, 19);//Ȯ     ��
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_REFINE, 2,  159, 156, 201, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 156, 201, 64, 19);//��     ��

	m_iRefineAniNo = 0;
	m_SetItemNumber = 0;
	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;
	g_cUIRefineWindow->m_iWindowIndex[4] = 0;
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUIRefineWindow::HT_vRefineWindow_SetInfo()
{

}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIRefineWindow::HT_vRefineWindow_WindowPopup()
{
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIRefineWindow::HT_vRefineWindow_WindowHide()
{
	for (int i = 1; i < 4; ++i)
	{
		g_cUIManager->HT_SetSlotBoxControlEnable(m_iWindowIndex[i], m_iControlIndex[i], true);
	}

	m_SetItemNumber = 0;
	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;

	g_cUIManager->HT_HideWindow( UI_WINDOW_REFINE );
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIRefineWindow::HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// ��ư�� ��� ó��
		switch(iTargetID)
		{
		case -2:// ��׶��� �ٿ��
			break;
		case -1:// �����ư
		case 2:	// ��ҹ�ư
			// ����â ���� �ִ� ������ �̹����� �����
			g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Delete();
			g_cNPCControl->m_iResent = 0;
			g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
			break;
		case 1:	// Ȯ�ι�ư
			g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Ok();
			//g_cUIManager->HT_HideWindow(UI_WINDOW_REFINE);
			break;
    	}
		break;
	case UI_TARGET_TIMER:	// Ÿ�̸�
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_REFINE, 99); 

		switch(g_cUIRefineWindow->m_iRefineAniNo)
		{
			case 0: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59); break;
			case 1: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 75 ,17, 59); break;
			case 2: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
			case 3: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 4: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
			case 5: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 79 ,17, 59); break;
			case 6: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
			case 7: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 8: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 9: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
			case 10: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 75 ,17, 59); break;
			case 11: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59); break;
            case 12: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 79 ,17, 59); break;
			case 13: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
            case 14: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
          //  case 15: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
		}

		g_cUIRefineWindow->m_iRefineAniNo++;
		if (g_cUIRefineWindow->m_iRefineAniNo > 14) g_cUIRefineWindow->m_iRefineAniNo = 0;
		break;
	case UI_TARGET_MESSAGEBOX:	// �޽��� �ڽ� ó��
		switch(iTargetID)
		{
		case 2:	// Ȯ��
			if (g_cUIRefineWindow->m_nMessageBoxNo == 1) // ��Ȯ��â�̸�...
				g_cNPCControl->HT_vNetWork_CSP_REQ_ITEM_REFINING();	// ���ý���
			break;
		default:
			break;
		}
		break;
	case UI_TARGET_SLOTBOX:
		if (iAction == UI_ACTION_MOUSE_L_UP)
		{
			unsigned int	nWindowIndex = 0, nControlIndex = 0;
			int iTextureID = 0;
			g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);

			if (nWindowIndex == _DIALOG_EQUPINVENTORY || nWindowIndex == _DIALOG_INVENTORY2)	// �κ��丮���� �ű�͸� ó���� �������� �̵� ����
			{
				// ����ϰ� �ִ� �κ��丮 �������� �ű�ٸ� ������ �̵� ����ó��
				if (nControlIndex < _SLOTCURRECT_INVEN) 
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
					return;
				}

				DWORD dwKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(nControlIndex);
				
				g_cUIRefineWindow->m_iWindowIndex[0] = nWindowIndex;
				g_cUIRefineWindow->m_iControlIndex[0] = nControlIndex;

				if (g_cNPCControl->HT_hrNPCControl_ItemWork_LButtonClick( dwKeyID ) == HT_FAIL)
				{
					g_cUIManager->HT_SetSlotBoxControlEnable(nWindowIndex, nControlIndex, true);
					g_cUIManager->HT_RefuseSlotImageMoving();
				}
			}
			else
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
			}
			break;
		}
	}
}


//
// CHTUIMerchantWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIMerchantWindow::CHTUIMerchantWindow() {}
CHTUIMerchantWindow::~CHTUIMerchantWindow() 
{
}

// ����â�� �����մϴ�.
void CHTUIMerchantWindow::HT_vMerchantWindow_Init()
{
	CHTString strMessage;
	// [�Ϲ� ����â]
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_MERCHANT, _T("Merchant"), 248, 412, g_cUIMerchantWindow->HT_hrMerchantWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_MERCHANT, 5);

	//	Slot Inven
	for(int i=0 ; i<6 ; i++ )
		for(int j=0 ; j<10 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( UI_WINDOW_MERCHANT, i+(j*6), 66, 12+(i*37), 25+(j*37) );
			g_cUIManager->HT_SetSlotBoxControlPosImage( UI_WINDOW_MERCHANT, i+(j*6), 2, 2);
		}

	// [�����̾� ����â]
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_MERCHANT_PREMIUM, _T("Merchant"), 539, 555, g_cUIMerchantWindow->HT_hrMerchantWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_MERCHANT_PREMIUM, 5);
	
	// ó�� ���� ��
	m_strTopic = "";
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, m_strTopic, 1, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 7, 65, 508, 35);
	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, 7);

	// ó������ �� ����
	int y = 31;

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 8, 3, y+6, 1400, 534, 6);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 8, 129, y+6, 1400, 198, 6);


	g_cUIManager->HT_SetScriptMessage( eMsgShopBundle, &strMessage, _T(""), _T("") );	//	�ٷ���
	m_strTitle[0] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopCharacter, &strMessage, _T(""), _T("") );	//	ĳ����
	m_strTitle[1] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopConvenience, &strMessage, _T(""), _T("") );	//	���Ǽ�
	m_strTitle[2] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopAbility, &strMessage, _T(""), _T("") );	//	��ɼ�
	m_strTitle[3] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopspeciality, &strMessage, _T(""), _T("") );	//	Ư����
	m_strTitle[4] = strMessage;
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 10, 40, y, 10, 10, 1550, 88, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 10, 129, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 10, 194, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 10, 259, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 10, 324, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 88, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, y+6, 65, 19);

	// ������
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 1, 9, 102, 1400, 3, 438);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 1, 259, 102, 1400, 3, 438);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 1, 513, 102, 1400, 3, 438);

	// ������
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 102, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 189, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 276, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 363, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 450, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 537, 1400, 506, 3);


	// �� �ٹ�
	g_cUIMerchantWindow->HT_vMerchantWindow_DrawTab(0);
	m_iTabNo = 0;

	// ��ũ�ѹ�
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_MERCHANT_PREMIUM , 1, 522, 44, 174, 5);
	m_iScrollValue = 0;

	//	Slot Inven 8, 101
	for(int i=0 ; i<5 ; i++ )
		for(int j=1 ; j<=2 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_MERCHANT_PREMIUM, 200+(i*2)+j, 66, 21+(244*(j-1)), 107+(87*i));
			g_cUIManager->HT_SetSlotBoxControlPosImage( UI_WINDOW_MERCHANT_PREMIUM, 200+(i*2)+j, 2, 2);
			g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 9, 83+(244*(j-1)), 106+(87*i));
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 200+(i*2)+j, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 83+(244*(j-1)), 106+(87*i), 152, 19);
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 300+(i*2)+j, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 64+(244*(j-1)), 127+(87*i), 187, 56);
			g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 300+(i*2)+j, 7);
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 400+(i*2)+j, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 142+(244*(j-1)), 169+(87*i), 132, 19);
			g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 400+(i*2)+j, 7);
		}
}

// ��ų�������� �� ��Ȱ�� ���ִ� �Լ�
void CHTUIMerchantWindow::HT_vMerchantWindow_DrawTab(int iTabNo)
{
	CHTString str;
	
	// ���� ��Ʈ�� ����
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105);
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105);

	// �缳��
	switch (iTabNo)
	{
	case 0:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 65, 40, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);

		HT_g_Script_SetMessage( eMsgExPlanPremiumItem07, &str, _T("") );	//	" �����̾� �ٷ��� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�."		
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 1:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 65, 129-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem04, &str, _T("") );	//	" ĳ���� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 2:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 65, 194-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19);  
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem05, &str, _T("") );	//	" ���Ǽ� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 3:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 65, 259-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259-23, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem06, &str, _T("") );	//	" ��ɼ� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 4:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 65, 324-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324-23, 31, 88, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem08, &str, _T("") );	//	" Ư�� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	}
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUIMerchantWindow::HT_vMerchantWindow_SetInfo()
{
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIMerchantWindow::HT_vMerchantWindow_WindowPopup()
{
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIMerchantWindow::HT_hrMerchantWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// ��ư�� ��� ó��
		switch(iTargetID)
		{
		case -2:// ��׶��� �ٿ��
			break;
		case -1:// �����ư
			g_cUIManager->HT_HideWindow(UI_WINDOW_MERCHANT);
			g_cUIManager->HT_HideWindow(UI_WINDOW_MERCHANT_PREMIUM);
			break;
			// �ܹ�ư Ŭ���� ����
		case 101: case 102: case 103: case 104: case 105:	// �����̾� �����쿡�� ����
			g_cUIMerchantWindow->m_iTabNo = iTargetID-101;
			g_cUIMerchantWindow->HT_vMerchantWindow_DrawTab(g_cUIMerchantWindow->m_iTabNo);
			g_cNPCControl->HT_vNPCControl_PrimiumItemListWin_Active(g_cUIMerchantWindow->m_iTabNo, g_cUIMerchantWindow->m_iScrollValue);
			break;
    	}
		break;
	case UI_TARGET_SLOTBOX:	// ���Թڽ� ����� ó��
		switch(iAction)
		{
		case UI_ACTION_MOUSE_RCLK:	// �ش� �������� RŬ�� ������ ���Ű���
			//g_cUIMerchantWindow->HT_vMerchantWindow_SetBuy(iTargetID);
			break;
		case UI_ACTION_MOUSE_L_UP: // ���콺�� ��� ������ ���
			{
				if (iTargetID == -1 || iTargetID == -2)
					g_cUIManager->HT_RefuseSlotImageMoving();
				
				unsigned int	nWindowIndex = 0, nControlIndex = 0;
				int iTextureID = 0;
				g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);
				if (nWindowIndex != _DIALOG_EQUPINVENTORY || nWindowIndex != _DIALOG_INVENTORY2) // �κ��丮�� ������ ��� �κ��丮�� �̵��� ����
					g_cUIManager->HT_RefuseSlotImageMoving();

				// ���������� �� �� �����Ƿ� ��ȯ _SLOTCURRECT_INVEN
				if (nControlIndex < _SLOTCURRECT_INVEN)
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
					return;
				}

				if (nWindowIndex == _DIALOG_EQUPINVENTORY || nWindowIndex == _DIALOG_INVENTORY2)	// �κ��丮���� ������ ���� ��� �Ǹ� ���� ����
				{

					DWORD KeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(nControlIndex);
					g_cUIMerchantWindow->m_dwSellItem = g_cItemSystem->HT_dwSystem_GetItemIndex(KeyID);
					g_cUIMerchantWindow->m_MessageCode = 4; 

					CHTString str; 
					if (g_iInationalType != INATIONALTYPE_KOREA)
					{
						g_pMessageMgr->HT_bGetMessage( eMsgItemSellQuestionItem, &str );// �������� �Ǹ� �Ͻðڽ��ϱ�?
						CHTString name; g_pParamMgr->HT_bGetItemName( g_cUIMerchantWindow->m_dwSellItem, &name );
						char str2[1024]; sprintf(str2, str, name.HT_szGetString()); strncpy(str, str2, 250);
					}
					else
					{
						// �ѱ� ���������� �ΰ��� Ÿ������ ������ ó�� (���Ǿ�, ĳ��)
						
						int sellrupiah = 0;
						g_pParamMgr->HT_bGetItemSellRupiah(g_cUIMerchantWindow->m_dwSellItem, &sellrupiah);
						CHTString num; num.HT_szFormat("%d", g_cItemSystem->HT_iItemSystem_GetItemCount(KeyID));
						CHTString num2; num2.HT_szFormat("%d", sellrupiah * g_cItemSystem->HT_iItemSystem_GetItemCount(KeyID));

						// �Ϻ� �������� �Ǹ� �� �� ����. (�����Ǿư� -1 �϶�)
						if (sellrupiah == -1)
						{
							g_cUIMerchantWindow->m_MessageCode = 1;
							g_pMessageMgr->HT_bGetMessage( eMsgItemSellFail, &str );			// �������� �Ǹ��� �� �����ϴ�.
							g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
							return;
						}
						
						// ĳ������ ���Ǿ������� ���� �ٸ� �޽��� ���
						if ( !CHTParamIDCheck::HT_bIsChargeNPC(g_cUIMerchantWindow->m_iNPCIndex))
						{
							// %s %s ���� %s ���Ǿƿ� �Ǹ� �Ͻðڽ��ϱ�?
							g_pMessageMgr->HT_bGetMessage( eMsgItemSellMsg1, &str );
							CHTString name; g_pParamMgr->HT_bGetItemName( g_cUIMerchantWindow->m_dwSellItem, &name );
							char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
						}
						else
						{
							// %s %s ���� %s ���Ǿƿ� �Ǹ� �Ͻðڽ��ϱ�?
							g_pMessageMgr->HT_bGetMessage( eMsgItemSellMsg2, &str );
							CHTString name; g_pParamMgr->HT_bGetItemName( g_cUIMerchantWindow->m_dwSellItem, &name );
							char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
						}
					}
					g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 1);
					return;
				}
			}
			break;
		case UI_ACTION_MOUSE_LCLK: // ���콺 ���� ��ư Ŭ��
			g_cUIMerchantWindow->HT_vMerchantWindow_SetBuy(iTargetID);
			break;
		}
		break;
	case UI_TARGET_MESSAGEBOX: // �޽��� �ڽ� ó��
		//if (g_cUIManager->HT_isShowMessageBox(UI_WINDOW_MERCHANT))
		//	g_cUIManager->HT_CloseMessageBox(UI_WINDOW_MERCHANT);

		switch (g_cUIMerchantWindow->m_MessageCode)
		{
			case 1: // ���� ���� Ȯ�� �޽���
				return;
			case 2: // ���� �Է� �޴� �κ�
				g_cUIMerchantWindow->HT_vMerchantWindow_ProcessBuy(iTargetID);
				return;
			case 3: // ������ ���Խ� ��Ȯ�� â
				if (iTargetID == 2) // Ȯ�ν� ������ ���ſ�û
					g_cUIMerchantWindow->HT_vNetWork_CSP_Req_Item_Buy();
				return;
			case 4:	// ������ �ǸŽ� ��Ȯ�� â
				if (iTargetID == 2)
				{
					g_cUIMerchantWindow->HT_vNetWork_CSP_Req_Item_Sell();
				}
				else
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
				}
				return;
			case 5:	// ������ ��ü ��Ȯ��â
				if (iTargetID == 2)
				{}
				else
				{}
				return;
		}
		break;
	case UI_TARGET_SCROLLBAR:	// ��ũ�ѹ� ó��
		{
			g_cUIMerchantWindow->m_iScrollValue = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_MERCHANT_PREMIUM, 1) * 2;
			g_cNPCControl->HT_vNPCControl_PrimiumItemListWin_Active(g_cUIMerchantWindow->m_iTabNo, g_cUIMerchantWindow->m_iScrollValue);
		}
		break;
	}
}

// ���Ÿ���Ʈ�� �����մϴ�.
void CHTUIMerchantWindow::HT_vMerchantWindow_SetBuyList()
{
	// ���� �ܰ� �������� ����
	g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount);

	// ��� �����
	for(int i=0 ; i<6 ; i++ )
		for(int j=0 ; j<10 ; j++ )
		{
			m_ItemIndex[i+(j*6)] = 0;
			g_cUIManager->HT_SetSlotImage( UI_WINDOW_MERCHANT, i+(j*6), 0);
		}


	// ���� ����Ʈ ����
	if( g_pParamMgr->HT_bLockID( m_iNPCIndex ) == true )
	{
		int iCount = g_pParamMgr->HT_iGetNPCSellingItemCount( );
		int idItem = 0;
		for ( int i = 0; i < iCount; ++i )
		{
			if ( g_pParamMgr->HT_bGetNPCSellingItem( i, &idItem ) )
			{
				m_ItemIndex[i] = idItem;
				g_cUIManager->HT_SetSlotImage(UI_WINDOW_MERCHANT, i, g_pEngineHandler->HT_dwGetItemUIID(idItem));
			}
		}
		g_pParamMgr->HT_bUnLockID( m_iNPCIndex );
	}

	// â ����
	g_cUIManager->HT_ShowWindow( UI_WINDOW_MERCHANT );
}

// ���� ����Ʈ���� ������ �����ۿ� ���� ���� ó�� (�Է°��� â ���� ������ ����)
void CHTUIMerchantWindow::HT_vMerchantWindow_SetBuy(int SlotNo)
{
	if (SlotNo >= 200) SlotNo -= 200;	// �����̾� �������� ��� -200 ����

	// Step 1) ������ ������ ���� ���
	if( g_pParamMgr->HT_bLockID( m_ItemIndex[SlotNo] ) == true )
	{
		m_dwBuyItem = m_ItemIndex[SlotNo];
		
		if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
		g_pParamMgr->HT_bGetItemCash( &m_ItemCash );	// �ʿ��� �� ( ĳ��)
		else
		g_pParamMgr->HT_bGetItemRupiah( &m_ItemCash );	// �ʿ��� �� (���Ǿ�)
		//g_pParamMgr->HT_bGetItemMaxCount( &byMaxCount );	// �ִ� ��ø ����

		if (m_iNPCIndex == 1302)	// ����� ���� ������ ��� ����� ������ ���� ������ ���Ѵ�.
		{
			HTbyte byteTex = g_pSiege->HT_bySiege_GetMoneyRate();
			double dTex;

			if (byteTex == 0) { dTex = 0;}
			else { dTex = (double)m_ItemCash * (double)byteTex/100.0f; }
			m_ItemCash += int(dTex);
		}

		g_pParamMgr->HT_bUnLockID( m_ItemIndex[SlotNo] );
	}
	
	// Step 2) �ڽ��� ������ �ִ� �ݾ� ���
	if ( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) )
		m_MyCash = g_cNPCControl->m_nCash;
	else
		m_MyCash = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();

	// ���� �����ϴٸ� �����޽��� ���
	if (m_MyCash < m_ItemCash) 
	{
		if (m_ItemCash <= 0) return;
	
		m_MessageCode = 1; 

		CHTString str;
		if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCashErr, &str );
		}
		else
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonMoneyErr, &str );
		}
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

	// Step 3) ���� ���� �Է�â ���
	m_MessageCode = 2; 
	CHTString str;// = "���ϴ� ������ �Է��ϼ���."; 
	g_pMessageMgr->HT_bGetMessage( eMsgCommonInputYouWantItem, &str ) ;
	g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 2);

}

// ������ ���� �Է� �� ���� ���ű��� ó�� �Լ�
void CHTUIMerchantWindow::HT_vMerchantWindow_ProcessBuy(int iCount)
{
	int m_nEconomy_Work_LimitRupiah = 0, m_iWorkItemMinCount = 0;

	m_dwBuyItemCount = iCount;
	if (m_dwBuyItemCount <= 0) 
	{
		if (m_dwBuyItemCount == 0) return;

		m_MessageCode = 1; 		// ������ ������ ������ �մϴ�.
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgItemUnpackCountErr, &str ); 
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

	// ����ȭ �������� ��� �ּ� ���԰��� �˻�
	if( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) // ����ȭ �������� �Ĵ� NPC�� ���
	{
		m_iWorkItemMinCount = g_cNPCControl->HT_iNPCControl_GetMinCountForChargeItem( m_dwBuyItem );
		if( m_dwBuyItemCount < m_iWorkItemMinCount ) 
		{
			m_MessageCode = 1; 		// �ּ� %d���� �����ؾ� �մϴ�.
			CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMinCountErr, &str );
			//str.HT_szFormat(str, m_iWorkItemMinCount);
			CHTString num; num.HT_szFormat("%d", m_iWorkItemMinCount);
			char str2[1024]; sprintf(str2, str, num.HT_szGetString()); strncpy(str, str2, 250);

			g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
			return;
		}
	}
	// ������ �ݾװ� �ʿ��� �ݾ� �˻� 
	if(CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) // ����ȭ �������� �Ĵ� NPC�� ���
	{
		m_ItemCash = m_nEconomy_Work_LimitRupiah = g_cNPCControl->HT_iNPCControl_CalPurchasingPriceForChargeItem( m_dwBuyItem, m_dwBuyItemCount );
	}
	else
	{
		if (m_dwBuyItem == 7068) // Ư�� ������ ��쿡�� ������ �������� �Ǹ�
			m_dwBuyItemCount = m_dwBuyItemCount * 250;
		if (m_dwBuyItem == 6828) // Ư�� ������ ��쿡�� ������ �������� �Ǹ�
			m_dwBuyItemCount = m_dwBuyItemCount * 240;

		m_ItemCash =  m_ItemCash * m_dwBuyItemCount;
	}

	if( m_ItemCash < 0 || m_MyCash < m_ItemCash )
	{
		CHTString str; 	m_MessageCode = 1;
		if ( !CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonMoneyErr, &str );	// ������ ���Կ� �ʿ��� ���Ǿư� �����մϴ�
		else
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCashErr, &str );	// ������ ���Կ� �ʿ��� ĳ���� �����մϴ�.
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

	// ���� �κ��丮 ������ �����ϴٸ� ���Խ���
	// Step 1) ������ ������ �ִ� ��ø ���� ���
	byte byteMaxCount = 0;
	int byteMaxCount2 = 0;
	if( g_pParamMgr->HT_bLockID( m_dwBuyItem ) == true )
	{
		g_pParamMgr->HT_bGetItemMaxCount( &byteMaxCount );
		g_pParamMgr->HT_bUnLockID( m_dwBuyItem );
	}

	if (CHTParamIDCheck::HT_bIsItemChargeContinuance( m_dwBuyItem ) == true)	// �ð��� ���� �������̶�� 1�� ó���Ѵ�.
	{
		if (m_dwBuyItem == 6828) byteMaxCount=240;
		else
		byteMaxCount = 1;
	}

	// Step 2) ���� �κ��丮 ����� ���
	int BlankSpace = g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck();

	int maxInven;	// ����ϴ� �κ��丮 ���� ���� ����
	if (g_cEquipInventory->m_bUsableInventory == false)	{maxInven = 24;} else {maxInven = 48;}

	// Step 3) �κ��丮 ��� �����Ͽ�, �ش� �����۰� ���� ������ �ִ��� ã��, ��ø�� �������� �����Ͽ� �ش� ������ŭ ���������� �ִ��� Ȯ���Ѵ�.
	int ExtraBlank = 0;

	DWORD KeyID = 0, dwItemIndex = 0;
	for (int i = 0; i < maxInven; ++i) // ����ϴ� �κ��丮��ŭ ����
	{
		KeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation( i + _SLOTCURRECT_INVEN );	// Ű���
		dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( KeyID );				// ���̵� ���
		if (dwItemIndex == m_dwBuyItem)	// �κ��丮 �ӿ� �����Ϸ��� �����۰� ���� �������� ���� �Ѵٸ� ���� ��ø���� ����
		{
			if ((CHTParamIDCheck::HT_bIsItemChargeContinuance( m_dwBuyItem ) == false) || (m_dwBuyItem == 6828) )	// �ð��� ���� �������� �ƴҰ�쿡�� ó��
			{
				int ExtraSpace = g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount( KeyID ) - g_cItemSystem->HT_iItemSystem_GetItemCount( KeyID );
				ExtraBlank += ExtraSpace;
			} 
		}
	}
	ExtraBlank += (BlankSpace * byteMaxCount); // ���������� ���� ������ �ִ밹���� ä������

	// Step 4) ��ø ������ ����� ������ �ִٸ� ���� ����, �׷��� ���ϸ� ���� ����
	if (ExtraBlank < iCount)
	{
		// ���� ������ �����ϸ� �������� ���ϰ� �Ѵ�.
		CHTString strString;
		HT_g_Script_SetMessage( eMsgItemCommonInvenLack, &strString );	// �κ��丮 ������ �����մϴ�.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
		return;
	}


	CHTString str; 	m_MessageCode = 3;
	if ( !(CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) )
	{
		if (g_iInationalType != INATIONALTYPE_KOREA)
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemBuyQuestionItemNum, &str );	// %s���� �����Ͻðڽ��ϱ�?
			CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
			CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
			char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString()); strncpy(str, str2, 250);
		}
		else
		{
			// ĳ������ ���Ǿ������� ���� �ٸ� �޽��� ���
			if ( !CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
			{
				g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMsg1, &str );	// %s %s���� %s ���Ǿƿ� �����Ͻðڽ��ϱ�?
				CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
				CHTString num2; num2.HT_szFormat("%d", m_ItemCash); 
				CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
				char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
			}
			else
			{
				g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMsg2, &str );	// %s %s���� %s ĳ���� �����Ͻðڽ��ϱ�?
				CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
				CHTString num2; num2.HT_szFormat("%d", m_ItemCash); 
				CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
				char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
			}
		}
	}
	else
	{
		g_pMessageMgr->HT_bGetMessage( eMsgPremiumBuyQuestion, &str );	// %s���� %sĳ���� �����Ͻðڽ��ϱ�?
		CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
		CHTString num2; num2.HT_szFormat("%d", m_ItemCash);
		CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
		char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
	}
	g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 1);
	return;
}
/*
// ���� �䱸
HTvoid CHTUIMerchantWindow::HT_vNetWork_CSP_REQ_ITEM_REPAIR()
{
	PS_CSP_REQ_ITEM_REPAIR info = HT_NULL;
	info = new S_CSP_REQ_ITEM_REPAIR;

	info->snNPCIndex = m_iNPCIndex;	// NPC �ε���
	
	// �������� ��ġ�� ��ҿ� ��ġ index
	HT_ITEMSETTING_FLAG sLocRoom;
	sLocRoom.nInventory = sLocRoom.nLocation = -1;
	g_cItemSystem->HT_bItemSystem_GetItemPos( m_dwFixDisjointKeyID, sLocRoom );
	if( sLocRoom.nInventory == -1 || sLocRoom.nLocation == -1 )
	{
		HT_DELETE( info );
		return;
	}

	if( sLocRoom.nLocation == ITEM_LOCATION_NPC )
	{
		info->byPlace =	ITEM_PLACE_CARGO ; 
		info->byIndex = ( sLocRoom.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + sLocRoom.pCellPos.x )
							+ ( sLocRoom.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT );
	}
	else if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byPlace =	ITEM_PLACE_EQUIP ;
		info->byIndex = sLocRoom.nInventory;
	}
	else //if( sLocRoom.nLocation == ITEM_LOCATION_PC )
	{
		info->byPlace =	ITEM_PLACE_INVEN ;
		info->byIndex = ( sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y )
							+ ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
	}

	g_pNetWorkMgr->RequestItemRepair( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemRepair : %d:(%d:%d)", 
													info->snNPCIndex, info->byPlace, info->byIndex );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
 
// ���� ���
HTvoid CHTUIMerchantWindow::HT_vNetWork_SCP_RESP_ITEM_REPAIR( PS_SCP_RESP_ITEM_REPAIR info )
{
	// KeyID ����
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	m_dwFixDisjointKeyID = iKeyID;

	if( info->byResult == 0x00 )
	{
		m_bMessage_Error = HT_FALSE;	// ���� ����

		//---------- �ý���â�� ������ ȹ�� ��� ------------//
		m_iSpendMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - info->nMoney;
		if(m_iSpendMoney < 0 )
			m_iSpendMoney = 0;

		if (info->byDummy == 1)	// ���Ǿ� ���
		{
			// %d���ǾƸ� ����ؼ� %s��(��) �����Ǿ����ϴ�.
			HT_vNPCControl_SetMessage( eMsgItemRepairSuccess );
		}
		else
		{
			HT_vNPCControl_SetMessage( eMsgItemRepairOK );
		}
		        
		// �� ����
		if(info->nMoney > 0)
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->nMoney);
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);

		// ������ �������� �������� �����Ѵ�.
		HTshort sMaxDur = g_cItemSystem->HT_sItemSystem_GetMaxDurability( m_dwFixDisjointKeyID );
		if( 0 <= sMaxDur && sMaxDur < HT_ITEM_INFINITY_DURABILITY )	// ���ѳ������� 255
			g_cItemSystem->HT_dwItemSystem_SetCurDurability( m_dwFixDisjointKeyID, sMaxDur);

		// ���� �������� ���� ���� ǥ��
		g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning( );

		// ��ȭ���� ��ȭ �ٲٱ�
		// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
		// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
		// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
		HT_vNPCControl_GetNextStep(m_nSelectCount);	
	} 
	else 
	{
		// �Ϸ�â�� ������ �޼���
		if( info->byResult == REPLY_ITEM_REPAIR_MONEY_WANT)
            // ������ �ʿ��� ���Ǿư� �����մϴ�. 	
			HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
		else if ( info->byResult == REPLY_ITEM_REPAIR_OUTINDEX )
			// �������� ã�� �� �����ϴ�. 
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		else if( info->byResult == REPLY_ITEM_REPAIR_ENOUGH)
			// ������ �ʿ䰡 ���� �������Դϴ�. 
			HT_vNPCControl_SetMessage( eMsgItemRepairNeedNot );
		else
			// �������� �������� ���߽��ϴ�. 
			HT_vNPCControl_SetMessage( eMsgItemRepairFail );

		m_bMessage_Error = HT_TRUE;	// ���� ����
		// �Ϸ�â ���
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
	}
	// �ý��� â�� ǥ��
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}
*/
void CHTUIMerchantWindow::HT_vNetWork_CSP_Req_Item_Buy()
{
	PS_CSP_REQ_ITEM_BUY info = HT_NULL;
	info = new S_CSP_REQ_ITEM_BUY;

	if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) == TRUE)
	{
		info->snNPCIndex = g_cNPCControl->HT_iGetCashNPC(g_cUIMerchantWindow->m_iTabNo);
	}
	else
	{
		info->snNPCIndex = m_iNPCIndex;
	}
	info->snItemIndex = HTshort(m_dwBuyItem - HT_ITEM_INDEX_START);
	// ������ ����
	info->snItemCount = m_dwBuyItemCount;

	// ���Ǿƴ� ������ �κ����� �ڵ����� ����.
	g_pNetWorkMgr->RequestItemBuy( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemBuy : %d:%d-%d��", 
	//												info->snNPCIndex, info->snItemIndex, info->snItemCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
 
void CHTUIMerchantWindow::HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info )
{
	m_dwBuyItem = info->snItemIndex + HT_ITEM_INDEX_START ;
	int m_iSpendMoney = 0;

	if( info->byResult == 0x00 )
	{
		if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) // �����̾� ������ ���� npc�� ���
		{
			g_cNPCControl->m_iSpendMoney = g_cNPCControl->m_dwNeedValue = g_cNPCControl->m_nCash = info->nMoney;
			m_iSpendMoney = m_ItemCash;	// ĳ�� ���� 
		}
		else
		{
			m_iSpendMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - info->nMoney;
			// ���Ǿ� ����
			if(info->nMoney > 0)
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->nMoney );
			else
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);
		}
		// �ý���â�� ������ ȹ�� ���
		if(m_iSpendMoney < 0 )	m_iSpendMoney = 0;

		// �Ϸ�â�� ������ �޼���
		CHTString str; 	m_MessageCode = 1;
		if ((CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) )
		{
			g_pMessageMgr->HT_bGetMessage( eMsgPremiumBuyOK, &str );	// %s��(��) %sĳ���� �����߽��ϴ�.
			CHTString num; num.HT_szFormat("%d", m_iSpendMoney);
			CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
			char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString()); strncpy(str, str2, 250);
			//g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();

			HTtchar text[1000] ;
			sprintf(text, g_cNPCControl->m_szQuestion, g_cNPCControl->m_nCash); // �Ķ���� �� ����
			g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_NPCWINDOW, 2, text);

		}
		else
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemBuyOneOK, &str );	// %s��(��) %s���ǾƷ� �����߽��ϴ�.
			CHTString num; num.HT_szFormat("%d", m_iSpendMoney);
			CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
			char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString()); strncpy(str, str2, 250);
		}
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );

		return;
 	}
	else
	{
		CHTString str; 	m_MessageCode = 1;
		switch( info->byResult )
		{
			case REPLY_ITEM_BUY_GOLD_WANT :	// �� ����
				if ((CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) )
					g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCashErr, &str );	// ĳ���� �����մϴ�.
				else
					g_pMessageMgr->HT_bGetMessage( eMsgItemCommonMoneyErr, &str );	// ���Ǿư� �����մϴ�.
				break;
			case REPLY_ITEM_BUY_INVENTORY_LACK : // �κ��丮 ���� ����
				g_pMessageMgr->HT_bGetMessage( eMsgItemCommonInvenLack, &str );	// �κ��丮 ������ �����մϴ�.
				break;
			case REPLY_ITEM_BUY_MINCOUNT :
				{
					int m_iWorkItemMinCount = g_cNPCControl->HT_iNPCControl_GetMinCountForChargeItem( m_dwBuyItem );
					g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMinCountErr, &str );	 // �ּ� ���� ���� ����
					CHTString num; num.HT_szFormat("%d", m_iWorkItemMinCount);
					char str2[1024]; sprintf(str2, str, num.HT_szGetString()); strncpy(str, str2, 250);
				}
				break;
			default:
				g_pMessageMgr->HT_bGetMessage( eMsgItemBuyFail, &str );	 // �������� �������� ���߽��ϴ�.
				break;
		}
		
		// �����޽��� ��� 
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

}

// ������ �Ǹ�
void CHTUIMerchantWindow::HT_vNetWork_CSP_Req_Item_Sell()
{
	PS_CSP_REQ_ITEM_SELL info = HT_NULL;
	info = new S_CSP_REQ_ITEM_SELL;

	info->snNPCIndex = m_iNPCIndex;	// NPC �ε���

	unsigned int	nWindowIndex = 0, nControlIndex = 0;
	int iTextureID = 0;
	g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);

	// x, y �� �����Ͽ� �ε��� ���
	if (nControlIndex < 124)	// ù��° ������ ���
	{
		info->byPlace =	ITEM_PLACE_INVEN ; 
		int x = (nControlIndex - 100) % MAX_INVEN_X; 
		int y = (nControlIndex - 100) / MAX_INVEN_X;
		info->byIndex = y + (x * MAX_INVEN_Y);
	}
	else
	{
		info->byPlace =	ITEM_PLACE_INVEN ; 
		int x = (nControlIndex - 124) % MAX_INVEN_X; 
		int y = (nControlIndex - 124) / MAX_INVEN_X;
		info->byIndex = 24 + y + (x * MAX_INVEN_Y);
	}

	g_pNetWorkMgr->RequestItemSell( info );
	
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemSell : %d:(%d:%d)", 
	//													info->snNPCIndex, info->byPlace, info->byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}


// �Ǹ� ���
void CHTUIMerchantWindow::HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info )
{
	// KeyID ����
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	DWORD m_dwFixDisjointKeyID = iKeyID;

	CHTString str; 	m_MessageCode = 1;

	if( info->byResult == 0x00 )
	{
		// ���׼��� 2005. 5. 18 ������ (���ٿ� �����ִ� ��ǰ �ǸŽ� ���ٿ����� ����)
		//DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( iKeyID );
		//if( g_cQuickSlot->HT_bBeUsedKeyID( dwIndex, iKeyID ) )
		//	g_cQuickSlot->HT_vDeleteIconInResentSlotByIndex( dwIndex, iKeyID );

		//---------- �ý���â�� ������ ȹ�� ��� ------------//
		int m_iSpendMoney = info->nMoney - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
		if(m_iSpendMoney < 0 )	m_iSpendMoney = 0;

		g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwFixDisjointKeyID );			// ��ü�� ������ ����
				
		if(info->nMoney > 0)	// �� ����
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->nMoney);
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);

		unsigned int	nWindowIndex = 0, nControlIndex = 0;
		int iTextureID = 0;
		g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);
		g_cUIManager->HT_SetSlotImage(nWindowIndex, nControlIndex, 0);

		g_pMessageMgr->HT_bGetMessage( eMsgItemSellSuccess, &str );	// %d���Ǿƿ� %s��(��) �ǸŵǾ����ϴ�.
		CHTString num; num.HT_szFormat("%d", m_iSpendMoney);
		CHTString name; g_pParamMgr->HT_bGetItemName(m_dwSellItem, &name );
		char str2[1024]; sprintf(str2, str, num.HT_szGetString(), name.HT_szGetString()); strncpy(str, str2, 250);

		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}
    else
	{
		g_cUIManager->HT_RefuseSlotImageMoving();		// �̹��� �������·� �ű�

		// �Ϸ�â�� ������ �޼���
		if( info->byResult == REPLY_ITEM_SELL_INVENTORY_LACK)
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonInvenLack, &str );		// �κ��丮�� ������ �����մϴ�.
		else if(info->byResult == REPLY_ITEM_SELL_NO_INVENTORY)
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonNoInventory, &str );	// PC�κ��丮 �̿��� ������ �ִ� �������Դϴ�.
		else if( info->byResult == REPLY_ITEM_SELL_OUTINDEX )
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCannotFindInfo, &str );// �������� ã�� �� �����ϴ�.
		else
			g_pMessageMgr->HT_bGetMessage( eMsgItemSellFail, &str );			// �������� �Ǹ��� �� �����ϴ�.

		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}
}



/*
//
// CHTUISlotInformationWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUISlotInformationWindow::CHTUISlotInformationWindow() {}
CHTUISlotInformationWindow::~CHTUISlotInformationWindow() {}

// ����â�� �����մϴ�.
void CHTUISlotInformationWindow::HT_vSlotInformationWindow_Init()
{
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_SLOTINFORMATION, _T("Information"), 258, 252, g_cUIManager->g_cUISlotInformationWindow.HT_hrSlotInformationWindow_InputCheck, 2);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, 0, "", 1, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30, 235, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, 1, "", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30+(1*20), 235, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, 2, "", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30+(2*20), 235, 45);
	for (int i=3; i<10; ++i)
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, i, "", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30+(i*20), 235, 19);
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUISlotInformationWindow::HT_vSlotInformationWindow_SetInfo()
{
	for (int i=1; i<20; ++i)
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SLOTINFORMATION, i, "");
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUISlotInformationWindow::HT_vSlotInformationWindow_WindowPopup()
{
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUISlotInformationWindow::HT_hrSlotInformationWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	g_cUIManager->HT_HideWindow(UI_WINDOW_SLOTINFORMATION);
}
*/


//
// CHTUIEmblemWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIEmblemWindow::CHTUIEmblemWindow() {}
CHTUIEmblemWindow::~CHTUIEmblemWindow() {}

// ����â�� �����մϴ�.
void CHTUIEmblemWindow::HT_vEmblemWindow_Init()
{
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUIEmblemWindow::HT_vEmblemWindow_SetInfo()
{
	if (m_Index != 0)	// �ں� �ٹ̱�
	{/*
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 11, m_Back1-1 );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 12, m_Back2-1 );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 13, UI_GUILD_TITLETEX + m_Title - 1 );
		g_cUIManager->HT_SetTextureControlColor( UI_WINDOW_EMBLEM, 11, AMBLEM_COLOR[m_iColor-1]);
		*/
	}

	// �޴��� �ִ� ������ �׸���
	for (int i = 1; i <= 2; ++i)
		for (int j = 1; j <= 6; ++j)
		{
			switch(m_iTabNo)
			{
			case 1:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j*i, 28401 + (j * i) - 1);
				break;
			case 2:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j*i, 28001 + (j * i) - 1);
				break;
			case 3:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j*i, 28601 + (j * i) - 1);
				break;
			}
		}
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIEmblemWindow::HT_vEmblemWindow_WindowPopup()
{

}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIEmblemWindow::HT_hrEmblemWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
}




//
// CHTUIQuestWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIQuestWindow::CHTUIQuestWindow() {}
CHTUIQuestWindow::~CHTUIQuestWindow() {}

// ����â�� �����մϴ�.
void CHTUIQuestWindow::HT_vQuestWindow_Init()
{
	CHTString strMessage;
	// ������ ����
	g_cUIManager->HT_SetScriptMessage( eMsgQuest, &strMessage, _T(""), _T("") );	//	Option
	g_cUIManager->HT_CreateWindow(UI_WINDOW_QUEST, strMessage, 330, 468, g_cUIQuestWindow->HT_hrQuestWindow_InputCheck, 2);//Quest
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_QUEST, 5);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 3, 36, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 40, 30, 1401, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestDiaryQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 30, 152, 19);//����Ʈ ����
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 172, 58, 1400, 152, 19);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 64, 1400, 3, 380);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 168, 64, 1400, 3, 380);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 58, 1400, 166, 6);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 444, 1400, 166, 6);

	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestContinueQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 172, 58, 152, 19);//�������� ����Ʈ
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 1, 309, 83, 80, 20);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 76, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 164, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 82, 1400, 3, 82);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 324, 82, 1400, 3, 82);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 172, 176, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestConditionQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 172, 176, 152, 19);//����Ʈ ����
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 195, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 319, 1400, 322, 6);
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 2, 309, 202, 116, 20);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 201, 1400, 3, 118);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 324, 201, 1400, 3, 118);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 172, 332, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestCompletionQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 172, 332, 152, 19);//�Ϸ� ����Ʈ
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 351, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 444, 1400, 322, 6);
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 3, 309, 358, 85, 20);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 357, 1400, 3, 87);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 324, 357, 1400, 3, 87);

	// ���� ����Ʈ ��ư 4��
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 1, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 82, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 2, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 102, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 3, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 122, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 4, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 142, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 1, 0, 8, 82, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 2, 0, 8, 102, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 3, 0, 8, 122, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 4, 0, 8, 142, 9, 9, 1500, 302, 19);
	
	// �Ϸ� ����Ʈ ��ư 4��
	g_cUIManager->HT_AddLongLabelControl(UI_WINDOW_QUEST, 9, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 206, 285, 80);
	g_cUIManager->HT_SetArrangementLongLabelControl(UI_WINDOW_QUEST, 9, 7);

	// ����Ʈ ���� �ؽ�Ʈ
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 5, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 360, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 6, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 380, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 7, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 400, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 8, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 420, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 5, 0, 8, 360, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 6, 0, 8, 380, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 7, 0, 8, 400, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 8, 0, 8, 420, 9, 9, 1500, 302, 19);

	for (int i = 1; i < 9; ++i)
		g_cUIManager->HT_SetButtonToolTipOff(UI_WINDOW_QUEST, i);

	// ����Ʈ ��Ʈ�� �ε�
	m_FocusIndex = 1;
	HT_vQuest_TutorialMsgLoading();
	m_bFalshState = false;
	g_bMoonBang = false;
	m_bFalshState = false;
	m_bReQuestItemUsingOne = true;
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUIQuestWindow::HT_vQuestWindow_SetInfo()
{
	for (HTint i = 0; i < QUEST_MAX_NUM; ++i)
	{
		m_ProgressResultStr[i] = "";
		m_CompleteResultStr[i] = "";
		m_ProgressStr[i] = "";
		m_CompleteStr[i] = "";
	}

	vSetInfo(1);
	vSetInfo(2);
	vSetInfo(3);
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIQuestWindow::HT_vQuestWindow_WindowPopup()
{

}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIQuestWindow::HT_hrQuestWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// ��ư�� ��� ó��
		switch(iTargetID)
		{
		case -2:// ��׶��� �ٿ��
			break;
		case -1:// �����ư
			//g_cUIManager->HT_HideWindow(UI_WINDOW_QUEST);
			g_cQuest->HT_vQuest_ActiveSw();
			break;
		case 1:	case 2:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:
			g_cUIQuestWindow->m_FocusIndex = iTargetID;
			g_cUIQuestWindow->vSetInfo(2);
			break;
    	}
	case UI_TARGET_SCROLLBAR:
		g_cUIQuestWindow->vSetInfo(iTargetID);	// ȭ�� ����
		break;
	case UI_TARGET_MESSAGEBOX:
		if (iTargetID == 2)
			g_cUIQuestWindow->HT_vNetWork_CSP_REQ_Quest_DIALOG(0x00, 0x00);	// �³�
		else
			g_cUIQuestWindow->HT_vNetWork_CSP_REQ_Quest_DIALOG(0x00, 0x01);	// ����
	}
}

//----------Ʃ�丮�� ����Ʈ ���� ���θ� ������ ����---------//
void CHTUIQuestWindow::HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult)
{
	PS_CSP_QUEST_DIALOG info = HT_NULL;
	info = new S_CSP_QUEST_DIALOG;

	info->snDialog = (HTshort)dwDialogIndex;
	info->byResult = byResult;

	g_pNetWorkMgr->RequestQuestDialog(info);

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqQuestDialog : %d-%d", dwDialogIndex, byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//-------------����Ʈ ���� ���� ����---------------//
void CHTUIQuestWindow::HT_vNetWork_SCP_RESP_Quest_Dialog( PS_SCP_QUEST_DIALOG info )
{
	CHTString str;
	HTint idMessage = eMsgParamNone;
 
	switch( info->wIndex)
	{
	case 1:	// �κ��丮 ������ �����Ͽ� ����Ʈ�� ������ �� �����ϴ�. �κ��丮�� ���� �ٽ� �õ� �ϼ���.
		idMessage = eMsgQuestInvenLack;	break;
	case 2:	// ���󳪰� �����մϴ�.
		idMessage = eMsgQuestPranaLack; break;
	case 5:	// ����Ʈ�� �����ϱ� ���� �������� �����ϴ�.
		idMessage = eMsgQuestNotExistItem; break;
	case 6:	// �ش� �������� �Ǹ��ϰų� Ÿ�ο��� �� �� ���� ����Ʈ�� ������ �Դϴ�.
		idMessage = eMsgQuestQuestOnlyItem; break;
	default:// ����Ʈ�� ������ �� �����ϴ�.
		idMessage = eMsgQuestCannotProgress; break;
	}

	if( idMessage != eMsgParamNone && g_pMessageMgr->HT_bGetMessage( idMessage, &str ) == true )
	{
		//g_cUIManager->HT_MessageBox(UI_WINDOW_QUEST, str, 0);// �Ϸ�â ���
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
	}
}

// �����κ��� ����Ʈ ���� ������ ����Ʈ ����� �����մϴ�.
void CHTUIQuestWindow::HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] )
{
	int ProgressIndex = 0, CompleteIndex = 0;

	// ����Ʈ�� ���ŵǸ� ���ι� ��ư�� ���������� ����, ��, ó�� �޴´ٸ� ����
	bool bcmp = false, bcmpc = false;
	for (int a=0; a<100; ++a)
	{
		if (m_byQuest[a] != byQuest[a])
		{
			bcmp = true;

			if (byQuest[a] == 255)	// ���� ����Ʈ �Ϸ��� üũ
				bcmpc = true;
		}
		m_byQuest[a] = byQuest[a];
	}
	if (bcmp == true && m_bFalshState == true)
	{
		// ����Ʈ â�� ���� �������� ������ ó��
		if (g_cUIManager->HT_isShowWindow( _DIALOG_QUEST ) == false)
			g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 4, 3 );

		// ����Ʈ �Ϸ� ����Ʈ
		// ���������� �Ϸ��� �Ϸ� ����Ʈ �ߵ�
		if( bcmpc == true )
		{
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_QUESTCOMPLETE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
		}
	}
	m_bFalshState = true;

	// ĳ���� ������ ó�� �α��� �� �ʺ��� ����Ʈ ���� ���� ����â�� ����.
	if( byQuest[0] == 1 )
	{
		if( g_cTutorialSystem->HT_bTutorial_TrainendSw() == 0 )
		{
			g_cTutorialSystem->HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( byQuest );
			return;
		}
		else
		{
			CHTString str;
			g_pMessageMgr->HT_bGetMessage( eMsgQuestTutorialStartQuestion, &str );
			// �޽��� �ڽ� ���
			g_cUIManager->HT_MessageBox(UI_WINDOW_QUEST, str, 1);
		}
	}

	for (HTint i = 0; i < QUEST_MAX_NUM; ++i)
	{
		m_ProgressResultStr[i] = "";
		m_ProgressStr[i] = "";
		m_CompleteResultStr[i] = "";
		m_CompleteStr[i] = "";
	}

	for( HTint index = 1; index < 100 ; ++index )	// �ϴ� ����Ʈ�� �ִ� 100���� ����
		if( index < QUEST_MAX_NUM && byQuest[index] != 0 )	// �߰��� ������ ����Ʈ�� ���ٸ� ����Ż��
		{
			switch(byQuest[index])
			{
			case QUEST_STATUS_FAIL:	// ���� ��� (254)
				break;
			case QUEST_STATUS_SUCCESS: // �Ϸ�� ����Ʈ��� �Ϸ�-����Ʈ��Ͽ� ������ �߰��մϴ�.(255)
				for(int nArrayNo = 0; nArrayNo < QUEST_MAX_NUM ; ++nArrayNo )	// ���� ����Ʈ ����
				{
					if( m_sQuestText[nArrayNo].byIndex == index )
					{
						// �ش� ����Ʈ Ÿ��Ʋ ���
						g_cUIQuestWindow->m_CompleteStr[CompleteIndex] = m_sQuestText[nArrayNo].szTitle;
						g_cUIQuestWindow->m_CompleteResultStr[CompleteIndex] = m_sQuestText[nArrayNo].szStepMsg[m_sQuestText[nArrayNo].nStepNo-1];
						CompleteIndex++;

						// ��������� ������ ������ �����
						if (index == 47 && g_wResentZoneServerID == 12)
						{
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1305 );

							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1304 );
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1304 );
						}

						// �й��� ��ſ��� ���� ����� ��ĥ�� 
						if (index == 49)
						{
							g_bMoonBang = true;
						}

						// ����Ʈ�� �Ϸ��ߴٸ� �ϵ��޾��� ����
						if (index == 50)
						{
							if (g_wResentZoneServerID != 12)
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1306 );
						}

						// ���� ������ ���� �Ϸ�������� ����Ʈ �ʱ�ȭ ������ ��� �Ұ�
						if (index == 51)
						{
							m_bReQuestItemUsingOne = false;
						}

						// ����Ʈ�� �Ϸ��ߴٸ� �������� ����
						if (index == 52)
						{
							if (g_wResentZoneServerID == 1)
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1437 );
						}

						// ����Ʈ�� �Ϸ��ߴٸ� ����Ű�� ���� ����
						if (index == 54)
						{
							if (g_wResentZoneServerID == 17)
							{
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1438 );	// ������ ������ ����
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1439 );	// ����Ű�� ������ ����
							}
						}

						// ����Ʈ�� �Ϸ��ߴٸ� ����� ����
						if (index == 55)
						{
							if (g_wResentZoneServerID == 17)
							{
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1440 );	// ������ ������ �������� ������ ����
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1441 );	// ������ ����� �������� ������ ����
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1442 );	// ���ĺζ��� �������� ������ ����
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1443 );	// ���������� �������� ������ ����
							}
						}

						break;
					}	
				}	
				break;
			default: // �������� ����Ʈ��� ������-����Ʈ��Ͽ� ������ �߰��մϴ�. (1~253)
				for(int nArrayNo = 0; nArrayNo < QUEST_MAX_NUM ; ++nArrayNo )
				{
					if( m_sQuestText[nArrayNo].byIndex == index )
					{
						// �ش� ����Ʈ Ÿ��Ʋ ���
						g_cUIQuestWindow->m_ProgressResultStr[ProgressIndex] = m_sQuestText[nArrayNo].szStepMsg[byQuest[index]-1];
						g_cUIQuestWindow->m_ProgressStr[ProgressIndex] = m_sQuestText[nArrayNo].szTitle;

						// ����Ʈ ����� ���ڰŸ���
						//if (m_bFalshState == false)
						//m_iLastProgressIndex = byQuest[index]-1;

						// ���� ��� �κ��̶�� ���� ī��Ʈ
						int iMobNo = SetMonsterKillNo(index, m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1]);
						if (iMobNo != 0)
							sprintf(g_cUIQuestWindow->m_ProgressResultStr[ProgressIndex], g_cUIQuestWindow->m_ProgressResultStr[ProgressIndex], iMobNo - byQuest[MOB_COUNT_QUEST_INDEX_START]);

						// Ư�� NPC
						// 47�� ����Ʈ�� 11�� ���� �������̶�� ���̰�...
						if (index == 47 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 11 && g_wResentZoneServerID == 9)	
						{
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1305 );// ����� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1305 );
						}

						// 47�� ����Ʈ�� 12�� ���� �������̶�� ���̰�...
						if (index == 47 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 12 && g_wResentZoneServerID == 12)	
						{
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1304 );	// ��������� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1304 );
						}

						// 50�� ����Ʈ�� 4�� ���� �������̶�� �ϵ��޾��� ���̰�...
						if (index == 50 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 4 && g_wResentZoneServerID == 12)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1306 );	// �ϵ��޾��갡 ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1306 );
						}

						// 51�� ����Ʈ�� 1�� ���� �̻� ���� �Ѵٸ� ����Ʈ �ʱ�ȭ ������ �ܵ� ��� �Ұ�
						if (index == 51 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 1 )
						{ 
							m_bReQuestItemUsingOne = false;
						}

						// 52�� ����Ʈ�� 10�� ���� �������̶�� �������� ���̰�...
						if (index == 52 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 10 && g_wResentZoneServerID == 1)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1437 );	// �������̰� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1437 );
						}

						// 54�� ����Ʈ�� 10�� ���� �������̶�� ���� ���̰�...
						if (index == 54 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 10 && g_wResentZoneServerID == 17)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1438 );	// ������ ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1438 );
						}

						// 54�� ����Ʈ�� 12�� ���� �������̶�� ����Ű ���̰�...
						if (index == 54 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 12 && g_wResentZoneServerID == 17)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1439 );	// ����Ű�� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1439 );
						}

						//// 54�� ����Ʈ�� 13�� ���� �������̶�� ����Ű�� ���� �Ⱥ��̰�...
						//if (index == 54 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 15 && g_wResentZoneServerID == 17)	
						//{ 
						//	g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1438 );	// ������ ������ ����
						//	g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1439 );	// ����Ű�� ������ ����
						//}

						// 55�� ����Ʈ�� 2�� ���� �������̶�� �߽����� ���������� ���̰�...
						if (index == 55 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 2 && g_wResentZoneServerID == 17)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1440 );	// ������ ������ �������� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1440 );
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1441 );	// ������ ����� �������� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1441 );
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1442 );	// ���ĺζ��� �������� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1442 );
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1443 );	// ���������� �������� ������ ������ �����
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1443 );
						}
					
						ProgressIndex++;
						break;
					}	
				}	
				break;
			}
		}

		// ��ũ�ѹ� �簻��
		g_cUIManager->HT_DelScrollBarControl(UI_WINDOW_QUEST, 1);
		g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 1, 309, 83, 80, ProgressIndex - 4);
		g_cUIManager->HT_DelScrollBarControl(UI_WINDOW_QUEST, 3);
		g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 3, 309, 358, 85, CompleteIndex - 4);

		// ��ư Ȱ��ȭ ���� ����
		for (int i = 1; i< 9; ++i)
			g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, i, false);		// ��ư �ϴ��� ��Ȱ��ȭ

		// Ȱ��ȭ �� ��ư�� ����
		if (ProgressIndex > 0) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 1, true);
		if (ProgressIndex > 1) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 2, true);
		if (ProgressIndex > 2) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 3, true);
		if (ProgressIndex > 3) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 4, true);

		if (CompleteIndex > 0) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 5, true);
		if (CompleteIndex > 1) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 6, true);
		if (CompleteIndex > 2) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 7, true);
		if (CompleteIndex > 3) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 8, true);

		//g_cUIQuestWindow->m_FocusIndex = 1;
		this->vSetInfo(1);	// ȭ�� ����
		this->vSetInfo(3);	// ȭ�� ����
		this->vSetInfo(2);	// ȭ�� ����
}

// ����Ʈ ���� ų ���� ���
int	CHTUIQuestWindow::SetMonsterKillNo(HTint iIndex, HTint StepNo)
{ 
	switch(iIndex)
	{	// ������ �ϵ��ڵ������� ������ ���� ȹ�������� �ٿ���
	case QUEST_TUTORIAL_5: if (StepNo == 3) return 10; break;	// �ɷ��� ����
	case QUEST_BASIC_GRADE:	if (StepNo >= 4 && StepNo <= 10) return 3; break;	// 1�� ����
	case QUEST_MANDARA_9: if (StepNo == 4) return 10; break;	// ���ٶ� ���� ���
	case QUEST_MANDARA_10: if (StepNo == 4) return 10; break;	// ������ �ٶ��� ���� ����
	case QUEST_SHAMBALA_1: if (StepNo == 4) return 30; if (StepNo == 7) return 15; break;	// ��ī��ī & ��ī��ī ī��� ����
	case QUEST_SHAMBALA_4: if (StepNo == 4) return 30; break;	// ���ī ����
	case QUEST_SHAMBALA_14: if (StepNo == 5) return 20; break;	// �Ƴ��� ����
	case QUEST_JINA_1: if (StepNo == 5) return 28; break;	// �ڱ��� ����
	case QUEST_JINA_3: if (StepNo == 5) return 10; if (StepNo == 8) return 15; break;	// ������ & ������ �ż��� ����
	case QUEST_JINA_5: if (StepNo == 8) return 30; break;	// ��ȭ���� ����
	case QUEST_JINA2_3: if (StepNo >= 5 && StepNo <= 56) return 10; break;	// ������ ����Ʈ �߰� (����� �κ�)
	case QUEST_K3_3: if (StepNo == 5 ) return 10; break; // ������� ����	// HTMessage�� �����ؾ��Ѵ�.
	case QUEST_K3_5: if (StepNo == 24 ) return 30; break; // ������ ����	// HTMessage�� �����ؾ��Ѵ�.
	}

	return 0;
}


// ����Ʈ ��Ͽ� ���
void	CHTUIQuestWindow::vSetInfo(int iTab)
{
	switch(iTab)
	{
	case 1:	// ù��° ��ũ�ѹ�
		{
			int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 1);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 1, m_ProgressStr[index]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 2, m_ProgressStr[index+1]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 3, m_ProgressStr[index+2]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 4, m_ProgressStr[index+3]);
			return;
		}
		break;
	case 2:	// �ι�° ��ũ�ѹ�
		break;
	case 3:	// ����° ��ũ�ѹ�
		{
			int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 3);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 5, m_CompleteStr[index]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 6, m_CompleteStr[index+1]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 7, m_CompleteStr[index+2]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 8, m_CompleteStr[index+3]);
			return;
		}
		break;
	}		

	// ���� ����
	if (m_FocusIndex < 5)
	{
		int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 1);
		g_cUIManager->HT_SetTextLongLabelControl(UI_WINDOW_QUEST, 9, g_cUIQuestWindow->m_ProgressResultStr[index + m_FocusIndex - 1]);
	} 
	else
	{
		int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 3);
		g_cUIManager->HT_SetTextLongLabelControl(UI_WINDOW_QUEST, 9, g_cUIQuestWindow->m_CompleteResultStr[index + (m_FocusIndex-4) - 1]);
	}
}

//---------Ʃ�丮�� �޽��� �ε�----------//
void CHTUIQuestWindow::HT_vQuest_TutorialMsgLoading()
{
	if( g_pMessageMgr == HT_NULL )
	{
		MessageBox(NULL, _T("HTQuest"), _T("Cannot Load QuestMessage!"), MB_OK);
		return;
	}

	CHTString strBuf;
	HTint	nArrayNo = 0, iID = 0, i = 0;
	HTshort sIndex = 0, sMaxStep = 0, sSubIndex = 0;

	for( iID = HT_MESSAGETYPE_QUESTMSG_START ; iID <= HT_MESSAGETYPE_QUESTMSG_END ; ++iID ) 
	{ 
		// ����Ʈ ��ȣ, ����Ʈ ���� UIâ�� ������� �� �޼��� ����
		if( g_pMessageMgr->HT_bGetParameter( iID, &sIndex, &sMaxStep, &sSubIndex ) == false )
			return;

		// ����Ʈ ����
		if( g_pMessageMgr->HT_bGetMessage( iID, &strBuf ) == false )
			return;

		m_sQuestText[nArrayNo].byIndex = (byte) sIndex;	// ����Ʈ ��ȣ
		m_sQuestText[nArrayNo].szTitle = strBuf;	// ����Ʈ ����
		m_sQuestText[nArrayNo].nStepNo = sMaxStep;	// �ִ� history �ܰ�
		strBuf.HT_hrCleanUp();
		
		for ( i=0 ; i<sMaxStep ; ++i )
		{
			++iID; // ���� ����Ʈ�� �ش��ϴ� history�� �б� ����
			if( g_pMessageMgr->HT_bGetParameter( iID, &sIndex, &sMaxStep, &sSubIndex ) == false )
				return;
			if( g_pMessageMgr->HT_bGetMessage( iID, &strBuf ) == false )
				return;

			m_sQuestText[nArrayNo].nStepNum[i] = sSubIndex;	// ����Ʈ �ܰ� ��ȣ
			// �ش��ϴ� �޼����� �д´�.
			// �ܰ躰 UIâ�� ��Ÿ���� ��
			m_sQuestText[nArrayNo].szStepMsg[i] = strBuf;
			strBuf.HT_hrCleanUp();
		}
		// �迭 �ε��� ����
		++nArrayNo;
	}	// end of for( iID = HT_MESSAGETYPE_QUESTMSG_START ; iID <= HT_MESSAGETYPE_QUESTMSG_END ; ++iID ) 
}



//
// CHTUIManager Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIManager::CHTUIManager()
{
	bRenderNPC = false;
	m_bBackgroundPos = true;
	m_bCheckRender = true;
	m_bSlotBoxMoving = false;
	
	// �������� �ʱ�ȭ
	g_Shift = false;
	g_Control = false;
	g_Pibot = 0;
	
	m_bDrawInfoWindow = false;
	m_nSlotBoxWindowIndex = 0;	
	m_nSlotBoxControlIndex = 0;
	m_nSlotBoxTextureID = 0;
	m_nSlotBoxTargetControlIndex = 0;
	m_nSlotBoxTargetWindowIndex = 0;

	m_InputState = false;
	m_nAlphaColor = 34;

	m_bBackgroundPos = false;
	bRenderNPC = true;
	m_strMessageBoxText = "";
	
	srand( (unsigned)time( NULL ) );
	
	m_UIList.clear();
}

// �޸� �ݳ�
CHTUIManager::~CHTUIManager()
{
	if (m_UIList.empty()) return;

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end();)
	{
		HT_DELETE( *ZOder );
		ZOder = m_UIList.erase( ZOder );
	}

	m_UIList.clear();
}

// �����츦 �׸����� ������ ZOder ��������� �׸���.
void CHTUIManager::HT_Render()
{
	if (!m_bCheckRender ) return;
	if (m_UIList.empty()) return;

	// ���붧�� ��� ������ ����	
	for(std::list<UIWindow*>::reverse_iterator ZOder = m_UIList.rbegin(); ZOder != m_UIList.rend(); ++ZOder)
		(*ZOder)->Render();

	// 2�� ���� ����
	for(std::list<UIWindow*>::reverse_iterator ZOder2 = m_UIList.rbegin(); ZOder2 != m_UIList.rend(); ++ZOder2)
		(*ZOder2)->Render_ToolTip();

	// NPC, ���� �� Ư�� ������Ʈ ���콺 ������ ����
	if (bRenderNPC == true)
		g_pEngineHandler->HT_hrRenderText(UI_MAIN_FONT, strRenderNPCName.HT_szGetString(), HTvector3(iRenderNPCPos.x, iRenderNPCPos.y, iRenderNPCPos.z), HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.8f ), 5.0f );
}

// ���� ���¸� ŵ�ϴ�.
void CHTUIManager::HT_RenderOn()
{
	m_bCheckRender = true;
}

// ���� ���¸� ���ϴ�.
void CHTUIManager::HT_RenderOff()
{
	m_bCheckRender = false;
}

// ������ ����
void CHTUIManager::HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode)
{
	// ���� �ش� �ε����� �����찡 �����Ѵٸ� �������
	UIWindow* pWindowTemp = this->FindWindowPointer(nIndex);
	if (pWindowTemp != NULL)
	{
		if (g_cUIManager->m_iGameMode == 1)
		{
			CHTString str;
			str.HT_szFormat("������ �����츦 �ٽ� �����Ϸ��� �Ͽ����ϴ�.(Index = %d)", nIndex);
			MessageBox(NULL, str, _T("Tantra V3"), MB_OK);
		}
		return;
	}
	
	int iPosX = 0, iPosY = 0; // ��ġ ����

	HT_COLOR clr;	// ���� ���� (nMode = 0 �̸� ����)
	
	if (nMode == 0)
	{
		clr.r = 1.0f / 255.0f; clr.g = 1.0f / 255.0f; clr.b = 1.0f / 255.0f; clr.a = 0.0f / 100.0f;
	}
	else
	{
		clr.r = 1.0f / 255.0f; clr.g = 1.0f / 255.0f; clr.b = 1.0f / 255.0f; clr.a = (float)m_nAlphaColor / 100.0f;
	}

	UIWindow* pWindow = new UIWindow;
	pWindow->CreateUIWindow(nIndex, str, iPosX, iPosY, iSizeX, iSizeY, clr, ptr, nMode);
	pWindow->BackgroundMove = nMode;
	pWindow->FocusOn();					// ���� ������ ����

	if (m_UIList.empty() == false)
		(m_UIList.front())->FocusOff();				// �ֻ��� ������ ��Ŀ�� ����

	m_UIList.push_front(pWindow);
}

// ������ ���� (��� �÷� ���� ����)
void CHTUIManager::HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode, HT_COLOR clrBackground)
{
	// ���� �ش� �ε����� �����찡 �����Ѵٸ� �������
	UIWindow* pWindowTemp = this->FindWindowPointer(nIndex);
	if (pWindowTemp != NULL)
	{
		if (g_cUIManager->m_iGameMode == 1)
		{
			CHTString str;
			str.HT_szFormat("������ �����츦 �ٽ� �����Ϸ��� �Ͽ����ϴ�.(Index = %d)", nIndex);
			MessageBox(NULL, str, _T("Tantra V3"), MB_OK);
		}
		return;
	}

	int iPosX = 0, iPosY = 0; // ��ġ ����

	UIWindow* pWindow = new UIWindow;
	pWindow->CreateUIWindow(nIndex, str, iPosX, iPosY, iSizeX, iSizeY, clrBackground, ptr, nMode);
	pWindow->FocusOn();					// ���� ������ ����

	if (m_UIList.empty() == false)
		(m_UIList.front())->FocusOff();				// �ֻ��� ������ ��Ŀ�� ����

	m_UIList.push_front(pWindow);

}

// ������ ����
void CHTUIManager::HT_DeleteWindow(unsigned int nIndex)
{	
	if (m_UIList.empty()) return;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIList.erase( ZOder );
			break;
		} 

	if (m_UIList.empty() != true) 
		(m_UIList.front())->FocusOn();
		
	//g_cUIManager->BottomWindow(nIndex);
	//m_UIList.pop_back();
	return;
}

// �ش� �������� ������ �����մϴ�.
void CHTUIManager::HT_SetBackgroundColor(unsigned int nIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->SetBackgroundColor(clr);
}

// �ش� �������� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer, int iSizeX, int iSizeY)
{
	UITexture oTexture;
	HT_COLOR clr; clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;

	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	this->HT_AddTextureControl(nWindowIndex, nControlIndex, oTexture);
}

// �ؽ�ó��Ʈ���� �߰��մϴ�.
void CHTUIManager::HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, HT_COLOR clr, int iSizeX, int iSizeY, int iLayer)
{
	UITexture oTexture;
	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	this->HT_AddTextureControl(nWindowIndex, nControlIndex, oTexture);
}

// �ؽ�ó ��Ʈ���� ��� ��ǥ�� ��ȯ�մϴ�.
HTvector3 CHTUIManager::HT_GetTextureControlPos(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextureControlPos(nControlIndex);

	return NULL;
}

// �ؽ�ó ��� �¿��� ���� (true = �� . false = ����)
void CHTUIManager::HT_SetTextureControlDisplay(unsigned int nWindowIndex, unsigned int nControlIndex, bool bOn)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureControlDisplay(nControlIndex, bOn);
}


// �ؽ�ó�� �����մϴ�.
void CHTUIManager::HT_SetTextureControlImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID )
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureControlImage(nControlIndex, iTextureID);
}

// �ؽ�ó��Ʈ���� �������� �����մϴ�.
void CHTUIManager::HT_SetTextureControlScale(unsigned int nWindowIndex, unsigned int nControlIndex, int iSizeX, int iSizeY, int iOSizeX, int iOSizeY)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureControlScale(nControlIndex, iSizeX ,iSizeY, iOSizeX, iOSizeY);
}

// �ؽ�ó��Ʈ���� ������ �����մϴ�.
void CHTUIManager::HT_SetTextureControlColor(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureColor(nControlIndex, clr);
}

// �ش� �������� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateTextureControl(nControlIndex, oTexture);
}

// �ش� �������� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_DelTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteTextureControl(nControlIndex);
}

// ���Թڽ� ������ ������ ���� ���� ����
void CHTUIManager::HT_SetSlotBoxImageFixed(unsigned int nWindowIndex, unsigned int nControlIndex, bool bFixedIcon)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxImageFixed(nControlIndex, bFixedIcon);
}

// ���Թڽ� ��Ʈ���� �߰��մϴ�.
void CHTUIManager::HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateSlotBoxControl(nControlIndex, oTexture);
}

// ���Թڽ� ��Ʈ���� �߰��մϴ�.
void CHTUIManager::HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer, int iSizeX, int iSizeY)
{
	UITexture oTexture;
	HT_COLOR clr; clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;

	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	this->HT_AddSlotBoxControl(nWindowIndex, nControlIndex, oTexture);
}

// ���Թڽ� ��Ʈ���� ������ ��ġ�� �缳�� �մϴ�.
void CHTUIManager::HT_SetSlotBoxControlPosImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX, int iPosY)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlPosImage(nControlIndex, iPosX, iPosY);
}

// ���Թڽ� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_DelSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteSlotBoxControl(nControlIndex);
}

// �����̹����� � ������ ���Կ� ���ִ��� �����Ͽ� ���� �̹����� �ű�� ó���մϴ�. (����ó����)
bool CHTUIManager::CheckRegionWithSlotBoxPoint(unsigned int nWindowIndex, unsigned int nControlIndex, int iXPos, int iYPos, int iTextureID)
{
	m_nSlotBoxWindowIndex = nWindowIndex;
	m_nSlotBoxControlIndex = nControlIndex;
	m_nSlotBoxTextureID = iTextureID;

	if (m_UIList.empty()) return NULL;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->isDisplay() == true && (*ZOder)->isEnable() == true)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos)) // �ش��ϴ� ��ġ�� �ִ� ��������...
		{
			int nIndex = (*ZOder)->m_nIndex;
			int nTargetControlIndex = (*ZOder)->CheckRegionWithSlotBoxPoint(iXPos, iYPos, (*ZOder)->iWindowPosX, (*ZOder)->iWindowPosY);
			
			// ���ڸ��� �ű�� ����
			if (nIndex == nWindowIndex && nControlIndex == nTargetControlIndex)
			{
				this->HT_SetSlotImage(nWindowIndex, nControlIndex, iTextureID);
				
				func_t* ptr = (*ZOder)->GetMessageProcedure();							// �Լ� �����͸� ���´�.
				ptr(UI_ACTION_MOUSE_LCLK, UI_TARGET_SLOTBOX, nControlIndex);	// ��濡 �������� �� �Լ����� -1�� ȣ���
				return true;
			}
				
			// �ش���ġ�� ������ �����Ѵٸ�... 
			if (nTargetControlIndex) 
			{
				// ����� ó���� ���� ���� ���� ����
				m_nSlotBoxTargetWindowIndex = nIndex;
				m_nSlotBoxTargetControlIndex = nTargetControlIndex;

				// ��� ������ �޽������ν��� ȣ��
				func_t* ptr = (*ZOder)->GetMessageProcedure();	// �ش� ������ �޽������ν��� ���
				ptr(1, 4, nTargetControlIndex);
				return true;
			}
			else // �����쿡 ���Ҵٸ� ������ �ƴ� �����쿡 ���Ҵٸ� -2
			{
				m_nSlotBoxTargetWindowIndex = nWindowIndex;
				m_nSlotBoxTargetControlIndex = nControlIndex;

				UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
				if (pWindow == NULL) return false;

				func_t* ptr = pWindow->GetMessageProcedure();					// �Լ� �����͸� ���´�.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SLOTBOX, -2);		// ��濡 �������� �� �Լ����� -1�� ȣ���
				return true;
			}
		}
	// ��濡 ���������� Ŭ���޽����� Ÿ�پ��̵� -1�� ������.
	m_nSlotBoxTargetWindowIndex = nWindowIndex;
	m_nSlotBoxTargetControlIndex = nControlIndex;

	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow == NULL) return false;

	func_t* ptr = pWindow->GetMessageProcedure();					// �Լ� �����͸� ���´�.
	ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SLOTBOX, -1);		// ��濡 �������� �� �Լ����� -1�� ȣ���
	return true;
}

// ���Թڽ��� ���� ��ġ ������ ����ϴ�.
void CHTUIManager::HT_GetSlotBoxControlSourInfo(unsigned int &nWindowIndex, unsigned int &nControlIndex, int &TextureID)
{
	nWindowIndex = m_nSlotBoxWindowIndex;
	nControlIndex = m_nSlotBoxControlIndex;
	TextureID = m_nSlotBoxTextureID;
}

// ���Թڽ��� �̹����� ���Դϴ�.
void CHTUIManager::HT_SetSlotImage(unsigned int nWindowIndex, unsigned int nControlIndex, int TextureID, int iLayer)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) {pWindow->SetSlotBoxControl(nControlIndex, TextureID, iLayer); return;}
}

// ���Թڽ��� �̹��� �ű�� ����
void CHTUIManager::HT_AcceptSlotImageMoving()
{
	if (m_bSlotBoxMoving == true)
	{
		// ���� ��ġ ���� ���
		this->HT_SetSlotImage(m_nSlotBoxWindowIndex, m_nSlotBoxControlIndex, 0);

		// ��� ��ġ ���� ä��
		this->HT_SetSlotImage(m_nSlotBoxTargetWindowIndex, m_nSlotBoxTargetControlIndex, m_nSlotBoxTextureID);

	}
}

// ���Թڽ��� �̹��� �ű�� ����
void CHTUIManager::HT_RefuseSlotImageMoving()
{
	// ���� ��ġ ���� ���
	this->HT_SetSlotImage(m_nSlotBoxWindowIndex, m_nSlotBoxControlIndex, m_nSlotBoxTextureID);
}

// �ش� ���Թڽ��� ��Ÿ�� ����
void CHTUIManager::HT_SetSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD DealyTime, DWORD PastTime)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxCoolTime(nControlIndex, DealyTime, PastTime);
}

// �ش� ���Թڽ��� ��Ÿ�� ���
void CHTUIManager::HT_SetSlotBoxCoolTimeCancel(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxCoolTimeCancel(nControlIndex);
}

// �ش� ���Թڽ��� ��Ÿ�� ������?
bool CHTUIManager::HT_isSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->isSlotBoxCoolTime(nControlIndex);
	return false;
}

// �ش� �������� ���Թڽ� ��Ʈ�ѿ��� ������ ŵ�ϴ�.
void CHTUIManager::HT_SetSlotBoxToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxToolTipOn(nControlIndex);
}

// �ش� �������� ���Թڽ� ��Ʈ�ѿ��� ������ ���ϴ�.
void CHTUIManager::HT_SetSlotBoxToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxToolTipOff(nControlIndex);
}

// ���Թڽ� ������ �ش� �ؽ�Ʈ ����(���κ�)
void CHTUIManager::HT_SetSlotBoxControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlToolTipText(nControlIndex, nIndex, str);
}

// ���Թڽ� ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
void CHTUIManager::HT_SetSlotBoxControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlTextIndex(nControlIndex, nIndex);
}

// ���Թڽ� ���� �ش� ���� �ؽ�Ʈ ���� ����
void CHTUIManager::HT_SetSlotBoxControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlToolTipTextColor(nControlIndex, nIndex, clr);
}

// ���Թڽ��� ��뿩�� ���� (0=���Ұ�, 1=��밡��)
void CHTUIManager::HT_SetSlotBoxControlEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlEnable(nControlIndex, bEnable);
}



// ��ũ�ѹ� ��Ʈ���� �߰��մϴ�.
void CHTUIManager::HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateScrollBarControl(nControlIndex, oTImage, oTLine, oTArrow1, oTArrow2, iMaxValue, iType);
}

// ��ũ�ѹ� ��Ʈ���� �߰��մϴ�.
void CHTUIManager::HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX, int iPosY, int iLength, int iMaxValue, int iType, int iStyle)
{
	UITexture	oTImage, oTLine, oTArrow1[3], oTArrow2[3];
	
	switch(iStyle)
	{
		case 0: // �⺻ ���� ��ũ�ѹ� �̹��� ����
			switch(iType)
			{
			case 0: // ���� ��ũ�ѹ�
				oTImage.Layer = 1600; oTImage.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTImage.TextureID = 138; oTImage.PosX = iPosX; oTImage.PosY = iPosY+16;
				oTImage.SizeX = 0; oTImage.SizeY = 0;

		
				oTArrow1[0].Layer = oTImage.Layer;	oTArrow1[0].VertexClr = oTImage.VertexClr;	oTArrow1[0].TextureID = 137; oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0; oTArrow1[0].PosX = iPosX; oTArrow1[0].PosY = iPosY;
				oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0;
				oTArrow1[2] = oTArrow1[1] = oTArrow1[0];
				oTArrow1[1].TextureID = 140;	oTArrow1[2].TextureID = 134;
				
				oTArrow2[0].Layer = oTImage.Layer;	oTArrow2[0].VertexClr = oTImage.VertexClr;	oTArrow2[0].TextureID = 136; oTArrow2[0].SizeX = 0; oTArrow2[0].SizeY = 0; oTArrow2[0].PosX = iPosX; oTArrow2[0].PosY = iPosY+iLength-16;
				oTArrow2[2] = oTArrow2[1] = oTArrow2[0];
				oTArrow2[1].TextureID = 139;	oTArrow2[2].TextureID = 133;

				oTLine.Layer = 1590; oTLine.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTLine.TextureID = 1; 
				oTLine.SizeX = 0; oTLine.SizeY = 0;
				oTLine.PosX = iPosX+6; oTLine.PosY = iPosY+16; oTLine.SizeX = 3; oTLine.SizeY = iLength - 32;
				break;
			case 1: // ���� ��ũ�ѹ�
				oTImage.Layer = 1600; oTImage.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTImage.TextureID = 143; oTImage.PosX = iPosX+16; oTImage.PosY = iPosY;
				oTImage.SizeX = 0; oTImage.SizeY = 0;
		
				oTArrow1[0].Layer = oTImage.Layer;	oTArrow1[0].VertexClr = oTImage.VertexClr;	oTArrow1[0].TextureID = 148; oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0; oTArrow1[0].PosX = iPosX; oTArrow1[0].PosY = iPosY;
				oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0;
				oTArrow1[2] = oTArrow1[1] = oTArrow1[0];
				oTArrow1[1].TextureID = 150;	oTArrow1[2].TextureID = 149;
				
				oTArrow2[0].Layer = oTImage.Layer;	oTArrow2[0].VertexClr = oTImage.VertexClr;	oTArrow2[0].TextureID = 145; oTArrow2[0].SizeX = 0; oTArrow2[0].SizeY = 0; oTArrow2[0].PosX = iPosX+iLength-16; oTArrow2[0].PosY = iPosY;
				oTArrow2[2] = oTArrow2[1] = oTArrow2[0];
				oTArrow2[1].TextureID = 146;	oTArrow2[2].TextureID = 147;

				oTLine.Layer = 1590; oTLine.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTLine.TextureID = 2; 
				oTLine.SizeX = 0; oTLine.SizeY = 0;
				oTLine.PosX = iPosX+16; oTLine.PosY = iPosY+6; oTLine.SizeX = iLength - 32; oTLine.SizeY = 3;
				break;
			}
		break;
	}

	if (iMaxValue < 0) iMaxValue = 1;
	HT_AddScrollBarControl(nWindowIndex, nControlIndex, oTImage, oTLine, oTArrow1, oTArrow2, iMaxValue, iType);
}

// ��ũ�ѹ� ��Ʈ�ѿ� ���� �ֽ��ϴ�.
void CHTUIManager::HT_SetScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetScrollBarValue(nControlIndex, iValue);
}

// ��ũ�ѹ� ��Ʈ�ѿ� �ִ� ���� ���� �մϴ�.
void CHTUIManager::HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetScrollBarMaxValue(nControlIndex, iValue);
}

// ��ũ�ѹ� ��Ʈ���� ���� ������ �ɴϴ�.
int CHTUIManager::HT_GetScrollBarValue(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetScrollBarValue(nControlIndex);
	return 0;
}

// ��ũ�ѹ� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_DelScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteScrollBarControl(nControlIndex);
}

// Ÿ�̸� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_AddTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD dwSetTime, int iStyle)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateTimerControl(nControlIndex, dwSetTime, iStyle);
}

// Ÿ�̸� ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_DelTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteTimerControl(nControlIndex);
}

// Ÿ�̸� ��Ʈ���� ���մϴ�.
void CHTUIManager::HT_EnableOnTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->EnableOnTimerControl(nControlIndex);
}

// Ÿ�̸� ��Ʈ�� �����մϴ�.
void CHTUIManager::HT_EnableOffTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->EnableOffTimerControl(nControlIndex);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��)
void CHTUIManager::HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UIText oText;
	oText.Font = UI_MAIN_FONT; oText.FontMode = iFontMode; oText.strTitle = str; 
	oText.TextColor = clr; 
	oText.TextShadowColor = sclr;

	oText.TextPos.left = iPosX;
	oText.TextPos.top = iPosY;
	oText.TextPos.right = iSizeX;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddLabelControl(nWindowIndex, nControlIndex, oText);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��)
void CHTUIManager::HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iStringNo, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	CHTString strMessage;
	g_cUIManager->HT_SetScriptMessage( iStringNo, &strMessage, _T(""), _T("") );	//	Ȯ��

	UIText oText;
	oText.Font = UI_MAIN_FONT; oText.FontMode = iFontMode; oText.strTitle = strMessage; 
	oText.TextColor = clr; 
	oText.TextShadowColor = sclr;

	oText.TextPos.left = iPosX;
	oText.TextPos.top = iPosY;
	oText.TextPos.right = iSizeX;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddLabelControl(nWindowIndex, nControlIndex, oText);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��)
void CHTUIManager::HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UIText oText)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateLabelControl(nControlIndex, oText);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��)
void CHTUIManager::HT_DelLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteLabelControl(nControlIndex);
}

// �ش� �������� ��Ʈ�� ������ �����մϴ�. (��)
void CHTUIManager::HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextLabelControl(nControlIndex, str);
}

// �ش� �������� ��Ʈ�� ������ �����մϴ�. (��)
void CHTUIManager::HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int strindex)
{
	CHTString str; 
	g_pMessageMgr->HT_bGetMessage( strindex, &str );

	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextLabelControl(nControlIndex, str);
}

// �ش� �������� ��Ʈ�� �ؽ�Ʈ�� ���ϴ� �������� ��ġ�մϴ�. (��)
void CHTUIManager::HT_SetArrangementLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetArrangementLabelControl(nControlIndex, iDirection);
}

// �ش� �������� �� ��Ʈ���� ���ϴ� �������� �����մϴ�. (��)
void CHTUIManager::HT_SetTextColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextColorLabelControl(nControlIndex, clr);
}

// �ش� �������� �� ��Ʈ���� ���ϴ� �׸��� �������� �����մϴ�. (��)
void CHTUIManager::HT_SetTextShadowColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextShadowColorLabelControl(nControlIndex, clr);
}

// �ش� �������� �� ��Ʈ���� ���ڸ� ���ɴϴ�. (��)
CHTString CHTUIManager::HT_GetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextLabelControl(nControlIndex);

	CHTString str = ""; return str;
}


// �ش� �������� ��Ʈ���� �����մϴ�. (�ն�)
void CHTUIManager::HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[], int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UILongText oText;
	oText.Font = UI_MAIN_FONT; oText.FontMode = iFontMode; 
	strcpy(oText.strTitle, str); 
	oText.TextColor = clr; 
	oText.TextShadowColor = sclr;

	oText.TextPos.left = iPosX;
	oText.TextPos.top = iPosY;
	oText.TextPos.right = iSizeX;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddLongLabelControl(nWindowIndex, nControlIndex, oText);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (�ն�)
void CHTUIManager::HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UILongText oText)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateLongLabelControl(nControlIndex, oText);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (�ն�)
void CHTUIManager::HT_DelLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteLongLabelControl(nControlIndex);
}

// �ش� �������� ��Ʈ�� ������ �����մϴ�. (�ն�)
void CHTUIManager::HT_SetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[])
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextLongLabelControl(nControlIndex, str);
}

// �ش� �������� ��Ʈ�� �ؽ�Ʈ�� ���ϴ� �������� ��ġ�մϴ�. (�ն�)
void CHTUIManager::HT_SetArrangementLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetArrangementLongLabelControl(nControlIndex, iDirection);
}

// �ش� �������� �ն� ��Ʈ���� ���ϴ� �������� �����մϴ�. (�ն�)
void CHTUIManager::HT_SetTextColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextColorLongLabelControl(nControlIndex, clr);
}

// �ش� �������� �ն� ��Ʈ���� ���ϴ� �׸��� �������� �����մϴ�. (�ն�)
void CHTUIManager::HT_SetTextShadowColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextShadowColorLongLabelControl(nControlIndex, clr);
}

// �ش� �������� �ն� ��Ʈ���� ���ڸ� ���ɴϴ�. (�ն�)
HTtchar* CHTUIManager::HT_GetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextLongLabelControl(nControlIndex);

	return NULL;
}

// �ش� �������� ��Ʈ���� �����մϴ�. (������ �ڽ�)
void CHTUIManager::HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iSizeX, int iSizeY, int iStyle, int iLayer)
{
	UITexture	oTexture;
	UIText		oText;
	HT_COLOR clr; clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;

	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	// ���� TextureID�� 0�̸� ������ ������ �ڽ��� �����Ѵ�.
	if (iTextureID == 0)
	{
		oTexture.TextureID = 0;
		oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}
	
	// ����� ������� ����� �Է����� ������, ������� ������ �����ϰ� �����ȴ�.
	if (iSizeX <= 0 || iSizeY <= 0)	
	{
		iSizeX = g_oUIResource[iTextureID].RealSizeX;
		iSizeY = g_oUIResource[iTextureID].RealSizeY;

		// �� ID = 0 �� ��쿡�� �ӽ÷� ���� ������ (���� �ڵ��� ���� ����)
		if (oTexture.TextureID == 0 )
		{
			iSizeX = 120;
			iSizeY = 15;
		}

		if (oTexture.TextureID >= 20000)
		{
			iSizeX = 32;
			iSizeY = 32;
		}
	}

	oText.Font = UI_MAIN_FONT;
	oText.FontMode = 4;
	oText.strTitle = "";
	oText.TextColor = clr;
	oText.TextShadowColor = clr;
	oText.TextPos.left = iPosX;
	oText.TextPos.right = iSizeX;
	oText.TextPos.top = iPosY;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddEditBoxControl(nWindowIndex, nControlIndex, oTexture, oText, iStyle);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture, UIText oText, int iStyle)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateEditBoxControl(nControlIndex, oTexture, oText, iStyle);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_DelEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteEditBoxControl(nControlIndex);
}

// �ش� ������ ��Ʈ�� ��带 �����մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_SetModeEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iMode)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		pWindow->SetEditBoxControlMode(nControlIndex, iMode);

		if (iMode == 2)		// ���� �Է�(�޸�) ����� ��� ����ó��
		{
			g_cUIManager->HT_SetEditBoxControlLimitText(nWindowIndex, nControlIndex, 10);//fors_debug ����Ǯ���޵ĵط�10E	// ����������� �Է¹���
			g_cUIManager->HT_SetTextEditBoxControl(nWindowIndex, nControlIndex, "");	// ó������ 0���� ����
		}
	}
}

// �ش� �������� ��Ʈ�� ������ �����մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_SetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextEditBoxControl(nControlIndex, str);
}

// �ش� �������� ��Ʈ�� ������ �����մϴ�. (�����͹ڽ�)
CHTString CHTUIManager::HT_GetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextEditBoxControl(nControlIndex);
	return NULL;
}

// �ش� �������� ��Ʈ�� ��Ŀ���� �����մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_FocusOffEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{	
		return pWindow->EditBoxFocusOff(nControlIndex);
	}
}

// �ش� �������� ��Ʈ�� ��Ŀ���� ���մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_FocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		return pWindow->EditBoxFocusOn(nControlIndex);
	}
}

// �ش� �������� ��Ʈ�� ��Ŀ��Ȱ��ȭ�� ������ �Է¸�� ���¸� �����Ͽ� ����ǵ��� �մϴ�.
void CHTUIManager::HT_SetEditBoxFocusOnIME(unsigned int nWindowIndex, unsigned int nControlIndex, int iIME)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		pWindow->SetEditBoxFocusOnIME(nControlIndex, iIME);
		return;
	}
}

// �ش� �������� ��Ʈ�ѿ��� �Է±��̸� �����մϴ�. (�����͹ڽ�)
void CHTUIManager::HT_SetEditBoxControlLimitText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int uiSize)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->SetEditBoxControlLimitText(nControlIndex, uiSize);
}

// �ش� �������� ��Ʈ�� ��Ŀ�� ���θ� ��ȯ�մϴ�. (�����͹ڽ�)
bool CHTUIManager::HT_isFocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->isEditBoxFocusOn(nControlIndex);
	return false;
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��ư)
void CHTUIManager::HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iTextureID2, int iTextureID3, int iLayer, int iSizeX, int iSizeY)
{
	UITexture oTexture[3];
	oTexture[0].Layer = iLayer;
	oTexture[0].PosX = iPosX;
	oTexture[0].PosY = iPosY;
	oTexture[0].SizeX = iSizeX;
	oTexture[0].SizeY = iSizeY;
	oTexture[0].TextureID = iTextureID;

	HT_COLOR clr; 
	if (iTextureID == 0) // ���� ID�� 0���� �ϸ� ������ ��ư�� �����ǰ� �Ѵ�.
	{
		clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 0.0f;
	}
	else
	{
		clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;
	}
	oTexture[0].VertexClr = clr;

	oTexture[2] = oTexture[1] = oTexture[0];
	if (iTextureID2) oTexture[1].TextureID = iTextureID2;
	if (iTextureID3) oTexture[2].TextureID = iTextureID3;

	this->HT_AddButtonControl(nWindowIndex, nControlIndex, oTexture);
}

// �ش� �������� ��ư ��Ʈ�ѿ��� ���� ������ �����մϴ�.
void CHTUIManager::HT_SetButtonToolTip(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonToolTip(nControlIndex, str);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��ư)
void CHTUIManager::HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture[3])
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateButtonControl(nControlIndex, oTexture);
}

// �ش� �������� ��Ʈ���� �����մϴ�. (��ư)
void CHTUIManager::HT_DelButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteButtonControl(nControlIndex);
}

// ��ư Ȱ��ȭ ����
void CHTUIManager::HT_SetButtonEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonEnable(nControlIndex, bEnable);
}

// �ش� ��ư�� ���ͱ���� ŵ�ϴ�.
void CHTUIManager::HT_SetButtonEnterOn(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonEnterOn(nControlIndex);
}

// �ش� ��ư�� ���ͱ���� ���ϴ�.
void CHTUIManager::HT_SetButtonEnterOff(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonEnterOff(nControlIndex);
}

// �ش� �������� ��ư ��Ʈ�ѿ��� ������ ŵ�ϴ�.
void CHTUIManager::HT_SetButtonToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonToolTipOn(nControlIndex);
}

// �ش� �������� ��ư ��Ʈ�ѿ��� ������ ���ϴ�.
void CHTUIManager::HT_SetButtonToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonToolTipOff(nControlIndex);
}

// �ش� �������� ��ư ��Ʈ�ѿ��� ���¸� �����մϴ�.
void CHTUIManager::HT_SetButtonControlState(unsigned int nWindowIndex, unsigned int nControlIndex, int iSetNo)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlState(nControlIndex, iSetNo);
}

// ��ư ������ �ش� �ؽ�Ʈ ����(���κ�)
void CHTUIManager::HT_SetButtonControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlToolTipText(nControlIndex, nIndex, str);
}

// ��ư ������ �ش� ��� ���� �ε��� ���� (�ش� ���α����� �����)
void CHTUIManager::HT_SetButtonControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlTextIndex(nControlIndex, nIndex);
}

// ��ư ���� �ش� ���� �ؽ�Ʈ ���� ����
void CHTUIManager::HT_SetButtonControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlToolTipTextColor(nControlIndex, nIndex, clr);
}

// üũ�ڽ��� �����մϴ�.
void CHTUIManager::HT_AddCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, int XPos, int YPos, bool bValue, int BorderTextureID, int CheckTextureID, int SizeX, int SizeY)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateCheckBoxControl(nIndex, XPos, YPos, bValue, BorderTextureID, CheckTextureID, SizeX, SizeY);
}	

// ��Ʈ���� �����մϴ�.
void CHTUIManager::HT_DelCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteCheckBoxControl(nIndex);
}

// üũ�ڽ��� ���� ����
void CHTUIManager::HT_SetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, bool bCheck)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetCheckBoxControl(nIndex, bCheck);
}

// üũ�ڽ��� ���� ����
bool CHTUIManager::HT_GetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetCheckBoxControl(nIndex);
	return NULL;
}


// �ֻ��� ������ ����
bool CHTUIManager::HT_CloseWindow()
{
	if (m_UIList.empty()) return false;
	
	// ������ ��� �����츦 ������ ������ ������ ������� ����
	if (g_cUIManager->HT_isShowWindow(_DIALOG_DEATHMSG+999) == true) // ���� �������� �ٽ� ��Ȱâ�� ���ִٸ� ����� �ȵȴ�.
		g_cUIManager->HT_ShowWindow(_DIALOG_DEATHMSG+999);
	
	// ����� ��������� �������� �ȵǴ� �͵�
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
	{
		if ((*ZOder)->m_nIndex == _DIALOG_CHATTINGBOX || (*ZOder)->m_nIndex == _DIALOG_MAINBAR ||
			(*ZOder)->m_nIndex == _DIALOG_MAINCHARHP ||	(*ZOder)->m_nIndex == _DIALOG_HQUICKSLOT ||
			(*ZOder)->m_nIndex == _DIALOG_WQUICKSLOT || (*ZOder)->m_nIndex == _DIALOG_PRANABAR || 
			(*ZOder)->m_nIndex == _DIALOG_PARTYWND || (*ZOder)->m_nIndex == _DIALOG_OPENMESSAGE ||
			(*ZOder)->m_nIndex == _DIALOG_DISCONNECTSERVER || (*ZOder)->m_nIndex == _DIALOG_DEATHMSGFOTRESS ||
			(*ZOder)->m_nIndex == _DIALOG_DEATHMSG || (*ZOder)->m_nIndex == _DIALOG_REVIVEWND ||
			(*ZOder)->m_nIndex == _DIALOG_ANSWERUSESAMUDABA || (*ZOder)->m_nIndex == _DIALOG_BUFFSKILL ||
			(*ZOder)->m_nIndex == _DIALOG_INDIVIDUALWND1 || (*ZOder)->m_nIndex == _DIALOG_WEBBROWSER || 
			(*ZOder)->m_nIndex == _DIALOG_MINIMAINBAR || (*ZOder)->m_nIndex == _DIALOG_CHATTING2BOX ||
			(*ZOder)->m_nIndex == _DIALOG_CHATTING3BOX || (*ZOder)->m_nIndex == _DIALOG_INDIVIDUALWND1 ||
			(*ZOder)->m_nIndex == _DIALOG_INDIVIDUALWND2 || (*ZOder)->m_nIndex == _DIALOG_TRADEWND || 
			(*ZOder)->m_nIndex >= 999 )
		{
			continue;
		}
		else
		{
			// �׿��� �������� ������ ���� â���� HideWindow �Լ��� ������ �ȵȴ�. ������ ���� �ݱ� �Լ����� ����Ұ�
			if (g_cUIManager->HT_isShowWindow((*ZOder)->m_nIndex) == true)
			{
				if ( (*ZOder)->m_nIndex == _DIALOG_MINIMAPSMALL || (*ZOder)->m_nIndex == _DIALOG_MINIMAPBIG )
				{
					g_cMiniMap->HT_vMiniMap_ESC_CloseWindow();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_NPCWINDOW)
				{
					g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_EQUPINVENTORY || (*ZOder)->m_nIndex == _DIALOG_INVENTORY2 )
				{
					g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_COMMANDWND)
				{
					g_cCommand->HT_vCommand_WndActiveSw();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_SKILL)
				{
					g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_QUEST)
				{
					g_cQuest->HT_vQuest_ActiveSw();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_CHATROOM)	// �����̶�� ���� ����
				{
					g_cChatRoom->HT_vChatRoom_WindowHide();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_CHATROOM_CREATE)	// �����â���� ESC ������ �ڵ� ����
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();
					g_cUIManager->HT_HideWindow((*ZOder)->m_nIndex);
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_CHATROOM_MSG) // ä�ù��̶�� ��ƿ� ��û
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomGoout();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_REFINE)	// ����â�� ������ �Լ��� �ݴ´�.
				{
					g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
				}
				else
				{
					// �׿� ������ �Լ����� �ݴ´�.
					g_cUIManager->HT_HideWindow((*ZOder)->m_nIndex);
				}

				return true;
			}
		}
	}
	return false;
}

// ���콺 L��ư �ٿ� ó��
bool CHTUIManager::OnLButtonDown(int iXPos, int iYPos)
{
	// ���� ž�����츦 �����ϰ� ������ �� ���� ������ ����
	if (m_UIList.empty()) return false;
	
	if ((m_UIList.front())->isDisplay() == true && (m_UIList.front())->CheckRegionWithPoint(iXPos, iYPos))	
	{
		if ((m_UIList.front())->OnLButtonDown(iXPos, iYPos))
		{
			(m_UIList.front())->FocusOn();
			return true;
		}
	}
	else
	{
		// ���� �ٸ� �����찡 ��Ŀ���� �����ٸ� ž�������� �����͹ڽ� ��Ʈ���� ��� ��Ŀ���� ������.
		(m_UIList.front())->EditBoxFocusAllOff();

		for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
			if ((*ZOder)->isDisplay() == true && (*ZOder)->isEnable() == true)
				if ((*ZOder)->OnLButtonDown(iXPos, iYPos))
				{
					int tindex = (*ZOder)->m_nIndex;
					int tindex2 = (m_UIList.front())->m_nIndex;

					// ó���� �����찡 ž�� �ƴ϶�� ž���� �̵���Ų��.
					if ((*ZOder)->m_nIndex != (m_UIList.front())->m_nIndex) 
						this->TopWindow((*ZOder)->m_nIndex);
					
					return true;
				}
		// ����ȭ�� Ŭ���� ��Ŀ�� ����
		(m_UIList.front())->FocusOff();
	}
	return false;
}

// ���콺 L��ư �� ó��
bool CHTUIManager::OnLButtonUp(int iXPos, int iYPos)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnLButtonUp(iXPos, iYPos))	return true;
	return false;
}

// ���콺 R��ư �ٿ�
bool CHTUIManager::OnRButtonDown(int iXPos, int iYPos)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->CheckRegionWithPoint(iXPos, iYPos) )
	{
		if ((m_UIList.front())->OnRButtonDown(iXPos, iYPos))
		{
			(m_UIList.front())->FocusOn();
			return false;
		}
	}
	else
	{
		// ���� �ٸ� �����찡 ��Ŀ���� �����ٸ� ž�������� �����͹ڽ� ��Ʈ���� ��� ��Ŀ���� ������.
		(m_UIList.front())->EditBoxFocusAllOff();

		for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
			if ((*ZOder)->isDisplay() == true && (*ZOder)->isEnable() == true)
				if ((*ZOder)->OnRButtonDown(iXPos, iYPos))
				{
					// ó���� �����찡 ž�� �ƴ϶�� ž���� �̵���Ų��.
					if ((*ZOder)->m_nIndex != (m_UIList.front())->m_nIndex) 
						this->TopWindow((*ZOder)->m_nIndex);

					return false;
				}
		// ����ȭ�� Ŭ���� ��Ŀ�� ����
		(m_UIList.front())->FocusOff();
	}
	return false;
}

// ���콺 R��ư ��
bool CHTUIManager::OnRButtonUp(int iXPos, int iYPos)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnRButtonUp(iXPos, iYPos))	return true;
	return false;
}

// Ű���� �ٿ�
bool CHTUIManager::OnKeyDown(WPARAM wParam)
{
	// �켱 Ȱ��ȭ �����쿡 ���� ó���մϴ�.
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true)
		if ((m_UIList.front())->OnKeyDown(wParam))	
			return true;

	// ���� Ű�ٿ� ó�� �κ� (���������� ����� Űó�� �κ��� �̰��� �ڵ��մϴ�.)
	switch(wParam)
	{
		//case 'l': case 'L':	// Status â ���
		//	if ( g_cUIManager->HT_isShowWindow( 101 ) ) 
		//		g_cUIManager->HT_HideWindow( 101 ); 
		//	else 
		//		g_cUIManager->HT_ShowWindow( 101 );
		//	break;
		//case 'k': case 'K': // Skill â ���
		//	break;
	case VK_TAB:
		if (g_cGameSystem)	// �������� ���������� ó����
		{

			if ( g_cUIManager->HT_isRenderOn() ) 
				g_cUIManager->HT_RenderOff(); 
			else 
				g_cUIManager->HT_RenderOn();
		}
			break;
		//case '2':
		//	g_cUIManager->HT_SetSlotBoxCoolTime(1, 1, 3200);
		//	break;
		//case '3':
		//	g_cUIManager->HT_SetSlotBoxCoolTimeCancel(1, 1);
		//	break;
		case VK_RETURN: // ä��â�� ��� �ι�° �Է�â�� Ȱ��ȭ �Ǿ� ���� ���� ��쿡�� Ȱ��ȭ ��Ų��.
		{
			HTint iChatDlgNo = 0;
			if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTINGBOX ))		iChatDlgNo = _DIALOG_CHATTINGBOX;
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTING2BOX ))	iChatDlgNo = _DIALOG_CHATTING2BOX;
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTING3BOX ))	iChatDlgNo = _DIALOG_CHATTING3BOX;

			if (g_cUIManager->HT_isShowWindow(iChatDlgNo) == true)
			if (g_cUIManager->HT_isFocusOnEditBoxControl(iChatDlgNo, 2) == false)
			{
				//g_cUIManager->HT_ShowWindow( iChatDlgNo ); // Ȱ��ȭ ������� ����
				g_EditBoxFocusWindow = iChatDlgNo;
				g_EditBoxFocusControl = 2;

				g_cChatting->HT_vChatting_SetFocusOn();
				return true;
			}
		}
	}

	//g_cInterfaceCheck->HT_hrInterfaceKeyboard_Input_KeyDown( wParam );

	// �ش���׾��ٸ� ���� ó���Լ��� �ѱ�
	return false;
}

// ���� �����찡 ��� �����ΰ�?
bool CHTUIManager::HT_isShowWindow(unsigned int nIndex)
{
	if (m_UIList.empty()) return false;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex )
			if ((*ZOder)->isDisplay() == true )
				return true;
			else
				return false;

	return false;
}


// Ű���� ��
bool CHTUIManager::OnKeyUp(WPARAM wParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnKeyUp(wParam)) 
			return true;
	return false;
}

// Ű���� ���� ����
bool CHTUIManager::OnChar(WPARAM wParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnChar(wParam)) 
			return true;
	return false;
}

// ���콺 �� ó��
bool CHTUIManager::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnMouseWheel(wParam)) 
			return true;
	return false;
}


// ������ ��� �޽��� ó��
bool CHTUIManager::OnSysCommand(WPARAM wParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnSysCommand(wParam)) 
			return true;
	return false;
}


// ���콺 �ٿ� ���� ó��
bool CHTUIManager::OnMouseMove(int iXPos, int iYPos)
{
	m_MousePosX = iXPos;
	m_MousePosY = iYPos;

	// Step 1) �����찡 ���ٸ� ������ ���� ���콺 ���� ó���� �ѱ��.
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		(m_UIList.front())->OnMouseMoveOnlyTop(iXPos, iYPos);

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->isDisplay() == true)
			(*ZOder)->OnMouseMove(iXPos, iYPos);

	return false;
}

// �ش� ID�� XMLID�� RealSize ������ ����մϴ�.
void CHTUIManager::RegisterTextureID(unsigned int nIndex, int XMLID, int RealSizeX, int RealSizeY)
{
	g_oUIResource[nIndex].RealSizeX = RealSizeX;
	g_oUIResource[nIndex].RealSizeY = RealSizeY;
	g_oUIResource[nIndex].XMLID = XMLID;
}

// �ش� �����츦 ã�� ������ �����͸� ��ȯ���ݴϴ�.
UIWindow* CHTUIManager::FindWindowPointer(unsigned int nIndex)
{
	if (m_UIList.empty()) return NULL;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex) 
			return (*ZOder);
	return NULL;
}

// �ش� �����츦 ã�� ������ �����͸� ��ȯ���ݴϴ�.
void CHTUIManager::HT_SetWindowBackgroundColor(unsigned int nIndex)
{
	HT_COLOR clr;

	if (m_UIList.empty()) return;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
	{
		// ������ ��������� ��ȭ ����
		if ((*ZOder)->m_nIndex == _DIALOG_MINIMAPSMALL || (*ZOder)->m_nIndex == _DIALOG_MINIMAPBIG)
		{
			clr.r = 1.0f / 255.0f; 
			clr.g = 1.0f / 255.0f; 
			clr.b = 1.0f / 255.0f; 
			clr.a = 10.0f / 100.0f;

			(*ZOder)->Body->SetColor(clr);
		}
		else if ((*ZOder)->BackgroundMove != 0)
		{
			clr.r = 1.0f / 255.0f; 
			clr.g = 1.0f / 255.0f; 
			clr.b = 1.0f / 255.0f; 
			clr.a = (float)nIndex / 100.0f;

			(*ZOder)->Body->SetColor(clr);
		}
	}

	g_cUIManager->HT_SetTextureControlColor( _DIALOG_CHATTINGBOX, 51, clr);
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_CHATTING3BOX, 52, clr);

}

// �ش� �����츦 ž(���� ���� ������)���� �����ϴ�.
void CHTUIManager::TopWindow(unsigned int nIndex)
{
	if (m_UIList.empty()) return;

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex) 
		{
			if ((*ZOder) != (m_UIList.front()))	 // ���� �ٸ� �����찡 ž�� �ȴٸ� ���� ž�������� �����͹ڽ� ��Ʈ���� ��� ��Ŀ���� ������.
				(m_UIList.front())->EditBoxFocusAllOff();

			(m_UIList.front())->FocusOff();			// �ֻ��� ������ ��Ŀ�� ����
			(*ZOder)->FocusOn();					// ���� ������ ����
			m_UIList.push_front(*ZOder);			// �ֻ��� �����쿡 ����
			m_UIList.erase(ZOder);					// ���� ��ġ�� �ִ� ������� ����

			return;									
		}
}

// �ش� �����츦 ����(���� ���� ������)���� �����ϴ�.
void CHTUIManager::BottomWindow(unsigned int nIndex)
{
	if (m_UIList.empty()) return;

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex) 
		{
			if ((*ZOder) == (m_UIList.front()))	 // ���� ž �����찡 �Ʒ��� �������ٸ� ž�������� �����͹ڽ� ��Ʈ���� ��� ��Ŀ���� ������.
				(m_UIList.front())->EditBoxFocusAllOff();

			(*ZOder)->FocusOff();					// ���� ������ ����
			m_UIList.push_back(*ZOder);				// ������ �����쿡 ����
			m_UIList.erase(ZOder);					// ���� ��ġ�� �ִ� ������� ����
			//(m_UIList.front())->FocusOn();			// �ֻ��� ������ ��Ŀ�� ����
	
			return;									
		}
}

// �ش� �����츦 ���ϴ� ��ġ�� �̵���ŵ�ϴ�.
void CHTUIManager::HT_MoveWindow(unsigned int nIndex, int iPosX, int iPosY, int iType)	// iType = 0 �̸� �����̵�, 1�̸� ���� ��ġ���� �߰��̵�
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		if (iType == 0 )	// �Ϲ� Ÿ�� (0)�� ����� ��û�� ��ġ�� �̵�
		{
			//pWindow->m_posX = iPosX;
			//pWindow->m_posY = iPosY;
			pWindow->MoveWindow(iPosX, iPosY);
		}
		else	// �׷��� �ʴٸ� ���� ��ġ���� �߰� �̵�
		{
			HTvector3 pos;
			pos = pWindow->GetWindowPos();
			//pWindow->m_posX = (int)pos.x + iPosX;
			//pWindow->m_posY = (int)pos.y + iPosY;
			pWindow->MoveWindow((int)pos.x + iPosX, (int)pos.y + iPosY);
		}
	}

}

// �ش� �������� ��ġ���� ���ɴϴ�.
void CHTUIManager::HT_GetWindowPos(unsigned int nIndex, int &PosX, int &PosY)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL)
	{
		HTvector3 pos = pWindow->GetWindowPos();
		PosX = (int)pos.x;
		PosY = (int)pos.y;
	}
}

// �ش� �������� ����� ���ɴϴ�.
HTvector3 CHTUIManager::HT_GetWindowSize(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) return pWindow->GetWindowSize();
	
	HTvector3 pos;
	pos.x = 0; pos.y = 0;
	return pos;
}

// �ش� �����츦 �����ݴϴ�.
void CHTUIManager::HT_ShowWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		pWindow->Show();
		this->TopWindow(nIndex);
	}
}

// �ش� �����츦 ����ϴ�.
void CHTUIManager::HT_HideWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		// �ݱ� ���� �޽��� �ڽ��� ����� �ִٸ� �޽����ڽ��� �ݾ��ش�.
		if (g_cUIManager->HT_isShowWindow(UI_WINDOW_MESSAGEBOX + nIndex) == true)
		{
			g_cUIManager->HT_FocusOffEditBoxControl(nIndex, 1); 
			g_cUIManager->HT_EnableOnWindow(nIndex);
			g_cUIManager->HT_DeleteWindow(nIndex+UI_WINDOW_MESSAGEBOX);
		}

		if (m_bSlotBoxMoving == true)	// ���� �̵����̶�� ����ġ�� �缳��
		{
			pWindow->CancelSlotBoxImageMoving();
		}

		pWindow->Hide();
		this->BottomWindow(nIndex);
	}
}


// ���� ������ �������϶� �������·� �ǵ����ϴ�.
void CHTUIManager::HT_CancelSlotBoxImageMoving()
{
	if (m_UIList.empty()) return;
	if (m_bSlotBoxMoving == true)	
		for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		{
			m_bSlotBoxMoving = false;
			(*ZOder)->CancelSlotBoxImageMoving();
		}
}

// �ش� �����츦 �����ϰ� �մϴ�.
void CHTUIManager::HT_EnableOnWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		pWindow->EnableOn(); 
		pWindow->FocusOn();
	}
}

// �ش� �����츦 �������� �ʰ� �մϴ�.
void CHTUIManager::HT_EnableOffWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		pWindow->EnableOff();
		pWindow->FocusOff();
	}
}


// �ش� �������� ��Ŀ���� ŵ�ϴ�.
void CHTUIManager::HT_FocusOnWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->FocusOn();
}

// �ش� �����츦 ��Ŀ���� ���ϴ�.
void CHTUIManager::HT_FocusOffWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->FocusOff();
}


// �ش� �������� �����츦 �̵� ��ŵ�ϴ�.
void CHTUIManager::HT_WindowArrangement(unsigned int nIndex, int iDirection)
{
	HTvector3	Pos;
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) Pos = pWindow->GetWindowSize();

	int iXpos;	// X �� ���
	switch (iDirection)
	{
	case 1:	case 4:	case 7:	iXpos = 0;	break;
	case 2:	case 5: case 8:	iXpos = (m_iScreenX - (int) Pos.x) / 2;	break;
	case 3:	case 6:	case 9:	iXpos = (m_iScreenX - (int) Pos.x);	break;
	}

	int iYpos;	// Y �� ���
	switch (iDirection)
	{
	case 7:	case 8:	case 9:	iYpos = 0; break;
	case 4: case 5: case 6:	iYpos = (m_iScreenY - (int) Pos.y) / 2;	break;
	case 1:	case 2:	case 3:	iYpos = (m_iScreenY - (int) Pos.y);	break;
	}
	
	//pWindow->m_posX = iXpos;
	//pWindow->m_posY = iYpos;
	pWindow->MoveWindow(iXpos, iYpos);
}

// ä��â�� �ý��� �˸� �޽����� �ѷ��ش�.
void CHTUIManager::ChattingNotify(int iMessageID)
{
	CHTString strTemp; 
	HT_g_Script_SetMessage( iMessageID, &strTemp, _T("") );		

	if (g_BasicLoadingInfo)
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
}

// �ش� ������� ���� �޽��� �ڽ��� ���ϴ�. 
void CHTUIManager::HT_MessageBox(unsigned int nWindowIndex, CHTString str, int nStyle)
{
	UIMessageBoxMgr.HT_vMessageBox(nWindowIndex, str, nStyle);
}

// �ش� ������� ���� �޽��� �ڽ��� ���ϴ�. 
void CHTUIManager::HT_MessageBox(unsigned int nWindowIndex, int index, int nStyle)
{
	CHTString str; g_pMessageMgr->HT_bGetMessage( index, &str );
	UIMessageBoxMgr.HT_vMessageBox(nWindowIndex, str, nStyle);
}

// �޽��� �ڽ��� �˾��Ǿ� �ִ��� ����
bool CHTUIManager::HT_isShowMessageBox()
{
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex >= UI_WINDOW_MESSAGEBOX && (*ZOder)->isDisplay() == true)
			return true;
	return false;
}

// �޽����ڽ��� ���� �Լ� ȣ��
void CHTUIManager::HT_CallMessageBoxFunction(unsigned int nWindowIndex, int iTargetID)
{
	// ���� �Ҵ�� �޽����ڽ��� �����Ͽ� �߰�ó���� �� �̿밡���ϵ��� �մϴ�.
	g_cUIManager->HT_DeleteWindow(nWindowIndex+UI_WINDOW_MESSAGEBOX);

	// �ش� ������ �޽��� ���ν����� ȣ���Ͽ� �߰����� ó���� �����ϵ��� ���ݴϴ�.
	UIWindow* pWindow = g_cUIManager->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		func_t* ptr = pWindow->GetMessageProcedure(); // �Լ� �����͸� ���´�.
		pWindow->EnableOn(); // ���� ������ ���¸� ���ɻ��·� ����ϴ�.

		// �ش� �޽��� ���ν��� ����
		ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_MESSAGEBOX, iTargetID);
	}

	//	������ �Էµƴ� ���ڿ��� �����.
	//g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	//g_cImeMgr.InputString();
}

// ������ ������ �߰��� �����츦 ������ �� �ִ� ������ �����մϴ�. ù��° ���ڴ� ������ �ؾ��ϸ�, ������ ������ �������� �����մϴ�.
void CHTUIManager::HT_SetMovingRegion(unsigned int nIndex, bool isOn, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->SetMovingRegion(isOn, iPosX, iPosY, iSizeX, iSizeY);
}

// ��׶��� ���� ������ �� ���� �����ΰ�?
bool CHTUIManager::HT_isBackgroundDownEnable(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) return pWindow->m_bBackgroundDownEnable;
	return false;
}

// ��׶��� ���� ������ �� ���ɿ��� ����
void CHTUIManager::HT_SetBackgroundDownEnable(unsigned int nIndex, bool bEnable)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->m_bBackgroundDownEnable = bEnable;
}

// ���� �˻� (�ش� ���콺 ��ġ�� �����ϴ� ������ ��ȣ ��ȯ)
unsigned int CHTUIManager::HT_CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	if (m_UIList.empty()) return 0;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos) == true)
			return (*ZOder)->m_nIndex;
	return 0;
}

// ���� Ȱ��ȭ�� �����͹ڽ��� ���ڸ� �����մϴ�.
void CHTUIManager::HT_UpdateEditBoxText(CHTString str)
{
	HT_SetTextEditBoxControl(g_EditBoxFocusWindow, g_EditBoxFocusControl, str);
}

// ���� Ȱ��ȭ �� ������ �ڽ��� Ŀ�� ��ġ�� ��ȯ�մϴ�.
HTvector3 CHTUIManager::HT_GetEditBoxCursorPos()
{
	int wposx, wposy;
	g_cUIManager->HT_GetWindowPos(g_EditBoxFocusWindow, wposx, wposy);

	HTvector3 pos;
	pos.x = float(wposx) + float(g_EditBoxCursorPosX);
	pos.y = float(wposy) + float(g_EditBoxCursorPosY);
	return pos;
}

// �Է��� ��������� ȣ�� �Ǵ� �Լ� (���ÿ�)
void CHTUIManager::ActionTarget(int iAction, int iTarget, int iTargetID)	// �Է�Ÿ��, �����Ҵ��, �ش�ID
{
	switch (iTarget)
	{
	case UI_TARGET_BUTTON:
		if (iTargetID == 1)
		{
			g_cUIManager->HT_SetBackgroundColor(1, HT_COLOR(1,1,1,1));
		}
		else if (iTargetID == 2)
		{
			g_cUIManager->HT_SetBackgroundColor(1, HT_COLOR(1,0,0,1));
		}
		else
		{
			g_cUIManager->HT_CloseWindow();
		}
		break;
	case UI_TARGET_SLOTBOX:
		{
			switch(iAction)
			{
			case UI_ACTION_MOUSE_LCLK:
				g_cUIManager->HT_SetSlotBoxCoolTime(1, 1, 1000, 0);
				break;
			}
		}
		break;
	}
	//g_cUIManager->HT_AccptSlotBoxMoving();
	//g_cUIManager->HT_RefuseSlotImageMoving();
	//CHTString str;
	//str.HT_szFormat("%d", g_cUIManager->HT_GetScrollBarValue(1,1));
	//g_cUIManager->HT_SetTextLabelControl(1,1, str);
	return;
}

// �ڼ���� ���� (0 = ���, -1 = ����ȭ��)
void CHTUIManager::HT_SetMagnet(unsigned int nWindowIndex, unsigned int nTargetIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetMagnet(nTargetIndex);
}

// �ش� ������ �ڼ���ɿ� ���� / ���� (����ó����)
void CHTUIManager::MagnetMgr(unsigned int nWindowIndex, unsigned int nTargetIndex, bool bInsert)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->MagnetMgr(nTargetIndex, bInsert);
}

// �ش� �������� �ڼ����¸� �˾ƿ´�.
bool CHTUIManager::HT_GetMagnetState(unsigned int nWindowIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetMagnetState();
	return false;
}

void CHTUIManager::HT_SetScriptMessage( HTint idMessage, CHTString* pszMessage, CHTString strInputItem1, CHTString strInputItem2 )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
	{
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	}
	else
	{
		szString.HT_hrCleanUp();
	}
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		//CHTString szOut1, szOut2, szOut3;

		//// sParam1
		//HT_g_Script_SetParamTextForMessage( sParam1, &szOut1 );
		//// sParam2
		//HT_g_Script_SetParamTextForMessage( sParam2, &szOut2 );
		//// sParam3
		//HT_g_Script_SetParamTextForMessage( sParam3, &szOut3 );

		//pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString(), strInputItem2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString() );
	}
	else
	{
		*pszMessage = szString;
	}
}


//	���Ǿ� ������ �޸� ��ũ ������ �ֵ��� ����
CHTString CHTUIManager::HT_strSetRestMark(HTint iNumber)
{
	CHTString str;
	CHTString strMilliard, strMillion, strThousand, strOne;

	HTint iMilliard = 0, iMillion = 0, iThousand = 0, iOne = 0;

	iMilliard = iNumber/1000000000;
	iMillion = iNumber/1000000 - iMilliard*1000;
	iThousand = iNumber/1000 - iMilliard*1000000 - iMillion*1000;
	iOne = iNumber - iMilliard*1000000000 - iMillion*1000000 - iThousand*1000;

	if (iMilliard!=0)
	{
		if (iMillion<10)							strMillion.HT_szFormat("00%d", iMillion);
		else if (iMillion>=10 && iMillion<100)		strMillion.HT_szFormat("0%d", iMillion);
		else										strMillion.HT_szFormat("%d", iMillion);

		if (iThousand<10)							strThousand.HT_szFormat("00%d", iThousand);
		else if (iThousand>=10 && iThousand<100)	strThousand.HT_szFormat("0%d", iThousand);
		else										strThousand.HT_szFormat("%d", iThousand);

		if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
		else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
		else										strOne.HT_szFormat("%d", iOne);

		str.HT_szFormat( _T("%d"), iMilliard );
		str += _T(",");
		str += strMillion;
		str += _T(",");
		str += strThousand;
		str += _T(",");
		str += strOne;
	}
	else
	{
		if (iMillion!=0)
		{
			if (iThousand<10)							strThousand.HT_szFormat("00%d", iThousand);
			else if (iThousand>=10 && iThousand<100)	strThousand.HT_szFormat("0%d", iThousand);
			else										strThousand.HT_szFormat("%d", iThousand);

			if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
			else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
			else										strOne.HT_szFormat("%d", iOne);

			str.HT_szFormat( _T("%d"), iMillion );
			str += _T(",");
			str += strThousand;
			str += _T(",");
			str += strOne;
		}
		else
		{
			if (iThousand!=0)
			{
				if (iThousand<10)							strThousand.HT_szFormat("00%d", iThousand);
				else if (iThousand>=10 && iThousand<100)	strThousand.HT_szFormat("0%d", iThousand);
				else										strThousand.HT_szFormat("%d", iThousand);

				if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
				else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
				else										strOne.HT_szFormat("%d", iOne);

				str.HT_szFormat( _T("%d"), iThousand );
				str += _T(",");
				str += strOne;
			}
			else
			{
				if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
				else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
				else										strOne.HT_szFormat("%d", iOne);

				str.HT_szFormat( _T("%d"), iOne );
			}
		}
	}
	return str;
	//return _T("");
}

// �ش� �������� �ڼ����¸� ���� �����մϴ�.
void CHTUIManager::HT_SetMagnetState(unsigned int nWindowIndex, bool bState)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->SetMagnetState(bState);
	return;
}


// ȯ�漳�� (UI Image�� ���ؼ��� ����Ѵ�. Icon�� 32*32 �����̹Ƿ� ClientRes ID�� �״�� �̿��Ѵ�.)
void CHTUIManager::HTSetGameEnvironment(int iScreenX, int iScreenY, int iNationalCode, int iConnectingServer, int iGameMode, int iResource)
{
	m_iScreenX = iScreenX;
	m_iScreenY = iScreenY;
	m_iNationalCode = iNationalCode;	
	m_iConnectingServer = iConnectingServer;
	m_iGameMode = iGameMode;

	if (iResource) // MainUI�� ����
	{
	// MainUI (�ϴ� �ӽ÷� �̷��� ó���Ѵ�. �ð��� �Ǹ� ����ȭ ����)

	// �⺻ UI ���� (����, ��, �̹�����)
	this->RegisterTextureID(0, 23899, 1, 1);	//����� (������ ���� ���� ������ ����)
	this->RegisterTextureID(1, 22762, 3, 32);	//UI_HeightLine01_3x32.bmp (������ ������ ���� ����)
	this->RegisterTextureID(2, 22763, 96, 3);	//UI_WidthLine01_96x3.bmp (������ ������ ���� ����)
	this->RegisterTextureID(3, 22764, 128, 32);	//UI_TitleBar01_128x32.bmp (Ÿ��Ʋ)
	
	this->RegisterTextureID(8, 22766, 64, 6);	//UI_WidthLine02_64X6.bmp (�ٹҿ� ���� ����)

	// �ٹ� �ڽ� ���� (�󺧿� ���)
	this->RegisterTextureID(9, 22767, 152, 19);	//UI_Box01_152X19.bmp	�� Ǫ�� �ڽ�
	this->RegisterTextureID(10, 22768, 79, 19);	//UI_Box02_79X19.bmp	���� Ǫ�� �ڽ�
	this->RegisterTextureID(11, 22769, 79, 19);	//UI_Box03_79X19.bmp	���� ���� �ڽ�

	// ���� �̹����� (�������� ������ �̹�����)
	this->RegisterTextureID(16, 22774, 32, 32);	//UI_Picture01_32X32.bmp
	this->RegisterTextureID(17, 22775, 32, 32);	//UI_Picture02_32X32.bmp
	this->RegisterTextureID(18, 22776, 32, 32);	//UI_Picture03_32X32.bmp
	this->RegisterTextureID(19, 22777, 32, 32);	//UI_Picture04_32X32.bmp
	this->RegisterTextureID(20, 22778, 32, 32);	//UI_Picture05_32X32.bmp
	this->RegisterTextureID(21, 22779, 32, 32);	//UI_Picture06_32X32.bmp

	// ���� �̹����� (���ڷε� ���ڵ�)
	this->RegisterTextureID(22, 22780, 23, 23); // 1
	this->RegisterTextureID(23, 22781, 23, 23); // 2
	this->RegisterTextureID(24, 22782, 23, 23); // 3
	this->RegisterTextureID(25, 22783, 23, 23); // 4
	this->RegisterTextureID(26, 22784, 23, 23); // 5
	this->RegisterTextureID(27, 22785, 23, 23); // 6
	this->RegisterTextureID(28, 22786, 23, 23); // 7
	this->RegisterTextureID(29, 22787, 23, 23); // 8
	this->RegisterTextureID(30, 22788, 23, 23); // 9
	this->RegisterTextureID(31, 22789, 39, 39);	// ���� �̹��� �ܰ� �ٹ� �ڽ�
	this->RegisterTextureID(32, 22790, 28, 60);	// ��

	// ������ �׵θ� �ڽ� (���� ��� �׵θ�)
	this->RegisterTextureID(66, 22794, 35, 35);//  	UI_Box06_35X35.bmp

	// �κ��丮 ����â �̹���
	this->RegisterTextureID(67, 22795, 231, 203);//	UI_Box19_231X203.bmp

	// ������� ��, ��, ��, �� ���� �̹���
	this->RegisterTextureID(68, 22796, 25, 25);//  	UI_Box22_25X25.bmp
	this->RegisterTextureID(69, 22797, 25, 25);//  	UI_Box23_25X25.bmp
	this->RegisterTextureID(70, 22798, 25, 25);//  	UI_Box24_25X25.bmp
	this->RegisterTextureID(71, 22799, 25, 25);//  	UI_Box25_25X25.bmp

	// ���� ������ �̹��� (���ǿ�)
	this->RegisterTextureID(72, 22800, 32, 32);//  	UI_Box40_32X32.bmp

	// ���� �ִϸ��̼� �̹����� 
	this->RegisterTextureID(73, 22801, 96, 96);//  	UI_Box47_96X96.bmp
	this->RegisterTextureID(74, 22802, 96, 96);//  	UI_Box41_96X96.bmp
	this->RegisterTextureID(75, 22803, 96, 96);//  	UI_Box42_96X96.bmp
	this->RegisterTextureID(76, 22804, 96, 96);//  	UI_Box43_96X96.bmp
	this->RegisterTextureID(77, 22805, 96, 96);//  	UI_Box44_96X96.bmp
	this->RegisterTextureID(78, 22806, 96, 96);//  	UI_Box45_96X96.bmp
	this->RegisterTextureID(79, 22807, 96, 96);//  	UI_Box46_96X96.bmp

	// Ȩ�� ������ (�����Ұ�)
	this->RegisterTextureID(80, 22808, 32, 32);//  	UI_Box50_32X32.bmp

	// ������ UI ���� �̹���
	this->RegisterTextureID(81, 22809, 256, 256);//  	UI_Box64_256X256.bmp

	// ������ �������� ���� (����, ����, ���, ������, ���)
	this->RegisterTextureID(82, 22810, 32, 32);//  	UI_Box66_32X32.bmp
	this->RegisterTextureID(83, 22811, 32, 32);//  	UI_Box67_32X32.bmp
	this->RegisterTextureID(84, 22812, 32, 32);//  	UI_Box68_32X32.bmp
	this->RegisterTextureID(85, 22813, 32, 32);//  	UI_Box69_32X32.bmp
	this->RegisterTextureID(86, 22814, 32, 32);//  	UI_Box65_32X32.bmp

	// ���� ������ �ٹ� �ڽ� (���ο�)
	this->RegisterTextureID(96, 22827, 13, 62);//		UI_Box57_13X62.bmp

	// ������ �� (������� �����Ұ�)
	this->RegisterTextureID(100, 22831, 16, 59);//		UI_ProgressBar07_16X59.bmp	
	this->RegisterTextureID(101, 22832, 150, 5);//		UI_ProgressBar01_150X5.bmp
	this->RegisterTextureID(102, 22833, 150, 5);//		UI_ProgressBar02_150X5.bmp
	this->RegisterTextureID(103, 22834, 144, 4);//		UI_ProgressBar03_144X4.bmp
	this->RegisterTextureID(104, 22835, 164, 15);//		UI_ProgressBar04_164X15.bmp
	this->RegisterTextureID(105, 22836, 164, 15);//		UI_ProgressBar05_164X15.bmp
	this->RegisterTextureID(106, 22837, 16, 59);//		UI_ProgressBar06_16X59.bmp

	// ���� �� (��,��) �ٹ�
	this->RegisterTextureID(107, 22856, 400, 11);//		UI_Ex01.bmp
	this->RegisterTextureID(108, 22857, 400, 11);//		UI_Ex02.bmp

	this->RegisterTextureID(199, 23895, 7, 16);	 // Ŀ�� �̹���

	// ������ (���� ü��) 
	this->RegisterTextureID(162, 22219, 162, 9);//		UI_ProgressBar08_162X9.bmp

	// ��, ��, ��, �� ȭ��ǥ
	this->RegisterTextureID(163, 22220, 25, 18);//		UI_Target01_25X18.bmp
	this->RegisterTextureID(164, 22247, 18, 25);//		UI_Target02_18X25.bmp
	this->RegisterTextureID(165, 22248, 18, 25);//		UI_Target03_18X25.bmp
	this->RegisterTextureID(166, 22249, 25, 18);//		UI_Target04_25X18.bmp

	// Ǫ���� �ٹҶ��� (����)
	this->RegisterTextureID(167, 22250, 32, 6);//		UI_WidthLine02_32X6.bmp

	// �ٹҹڽ� (������)
	this->RegisterTextureID(169, 22261, 25, 19);//		UI_Box05_25X19.bmp
	// ������ �ٹ� (����)
	this->RegisterTextureID(170, 22294, 38, 11);//		UI_Box30_38X11.bmp
	// ���ι� ������ �׵θ�
	this->RegisterTextureID(171, 22295, 38, 40);//		UI_Box74_38X40.bmp
	// ������ ������ �׵θ�
	this->RegisterTextureID(172, 22296, 39, 39);//		UI_Box59_39X39.bmp
	// ������ �ٹ� (����)
	this->RegisterTextureID(173, 22302, 11, 38);//		UI_Box51_11X38.bmp
	// ������ ��ư �ֺ� �ٹ�
	this->RegisterTextureID(174, 22303, 40, 36);//		UI_Box52_40X36.bmp
	// üũ ��� (üũ�ڽ�)
	this->RegisterTextureID(175, 22304, 7, 9);//		UI_Box20_7X9.bmp

	// ������ ��ũ 
	this->RegisterTextureID(188, 22314, 64, 64);//  	UI_SiegeMark01.bmp	����1
	this->RegisterTextureID(189, 22321, 64, 64);//  	UI_SiegeMark02.bmp	����2
	this->RegisterTextureID(190, 22322, 64, 64);//  	UI_SiegeMark03.bmp	����3
	this->RegisterTextureID(191, 22328, 64, 64);//  	UI_SiegeMark04.bmp	����
	this->RegisterTextureID(192, 22329, 64, 64);//  	UI_SiegeMark05.bmp	���Ҽ�

	// ���� �׵θ� ���� �̹���
	this->RegisterTextureID(193, 22372, 39, 39); // UI_Box75_39X39.bmp ���
	this->RegisterTextureID(194, 22373, 39, 39); // UI_Box76_39X39.bmp �Ķ�
	this->RegisterTextureID(195, 22374, 39, 39); // UI_Box77_39X39.bmp ���
	this->RegisterTextureID(196, 22380, 39, 39); // UI_Box78_39X39.bmp ����
	this->RegisterTextureID(197, 22381, 39, 39); // UI_Box79_39X39.bmp ���

	// -----------
	//  ��ư ����
	// -----------
	// �����ư (������ �ֻ�� �����ʿ� ��ġ�� �⺻ ������ư)
	this->RegisterTextureID(5, 22759, 28, 25);	//UI_Button01_N_28x25.bmp
	this->RegisterTextureID(6, 22760, 28, 25);  //UI_Button01_O_28x25.bmp
	this->RegisterTextureID(7, 22761, 28, 25);  //UI_Button01_D_28x25.bmp
	
	// ������ ������ ���� ��ư
	this->RegisterTextureID(4, 22765, 19, 18);	//UI_Scale01_19X18.bmp
	this->RegisterTextureID(12, 22770, 19, 18);	//UI_Scale02_19X18.bmp
	
	// ���� ��ư (��ų, ����â���� ��ġ ������ ���)
	this->RegisterTextureID(13, 22771, 13, 13);	//UI_Button04_N_13X13.bmp
	this->RegisterTextureID(14, 22772, 13, 13);	//UI_Button04_O_13X13.bmp
	this->RegisterTextureID(15, 22773, 13, 13);	//UI_Button04_D_13X13.bmp

	// ũ������ ���� ��ư (���ι�)
	this->RegisterTextureID(34, 22699, 32, 32);//UI_Button31_N_32X32.bmp
	this->RegisterTextureID(35, 22700, 32, 32);//UI_Button31_O_32X32.bmp
	this->RegisterTextureID(33, 22698, 32, 32);//UI_Button31_D_32X32.bmp
	
	// ����â ��ư (���ι�)
	this->RegisterTextureID(37, 22702, 32, 32);//UI_Button32_N_32X32.bmp
	this->RegisterTextureID(38, 22703, 32, 32);//UI_Button32_O_32X32.bmp
	this->RegisterTextureID(36, 22701, 32, 32);//UI_Button32_D_32X32.bmp
	
	// �κ��丮 ��ư (���ι�)
	this->RegisterTextureID(40, 22705, 32, 32);//UI_Button33_N_32X32.bmp
	this->RegisterTextureID(41, 22706, 32, 32);//UI_Button33_O_32X32.bmp
	this->RegisterTextureID(39, 22704, 32, 32);//UI_Button33_D_32X32.bmp
	
	// ����Ʈ ��ư (���ι�)
	this->RegisterTextureID(43, 22708, 32, 32);//UI_Button34_N_32X32.bmp
	this->RegisterTextureID(44, 22709, 32, 32);//UI_Button34_O_32X32.bmp
	this->RegisterTextureID(42, 22707, 32, 32);//UI_Button34_D_32X32.bmp
	
	// ��ųâ ��ư (���ι�)
	this->RegisterTextureID(46, 22711, 32, 32);//UI_Button35_N_32X32.bmp
	this->RegisterTextureID(47, 22712, 32, 32);//UI_Button35_O_32X32.bmp
	this->RegisterTextureID(45, 22710, 32, 32);//UI_Button35_D_32X32.bmp
	
	// �ɼ�â ��ư (���ι�)
	this->RegisterTextureID(49, 22714, 32, 32);//UI_Button36_N_32X32.bmp
	this->RegisterTextureID(50, 22715, 32, 32);//UI_Button36_O_32X32.bmp
	this->RegisterTextureID(48, 22713, 32, 32);//UI_Button36_D_32X32.bmp
	
	// ���â ��ư (���ι�)
	this->RegisterTextureID(52, 22717, 32, 32);//UI_Button37_N_32X32.bmp
	this->RegisterTextureID(53, 22718, 32, 32);//UI_Button37_O_32X32.bmp
	this->RegisterTextureID(51, 22716, 32, 32);//UI_Button37_D_32X32.bmp
	
	// PK ��ư (���ι�)
	this->RegisterTextureID(55, 22720, 32, 32);//UI_Button38_N_32X32.bmp
	this->RegisterTextureID(56, 22721, 32, 32);//UI_Button38_O_32X32.bmp
	this->RegisterTextureID(54, 22719, 32, 32);//UI_Button38_D_32X32.bmp
	
	// Ǫ�� ���� ��ư
	this->RegisterTextureID(63, 22791, 64, 19);// 	UI_Button03_N_64X19.bmp	
	this->RegisterTextureID(65, 22793, 64, 19);//  	UI_Button03_O_64X19.bmp
	this->RegisterTextureID(64, 22792, 64, 19);//  	UI_Button03_D_64X19.bmp

	// �κ��丮 ���Ǿ� ��� ��ư (���Ǿ� ����ŷ�� ����)
	this->RegisterTextureID(87, 22815, 32, 19);//  	UI_Button16_D_32X19.bmp
	this->RegisterTextureID(88, 22816, 32, 19);//  	UI_Button16_N_32X19.bmp
	this->RegisterTextureID(89, 22817, 32, 19);//  	UI_Button16_O_32X19.bmp

	// �κ��丮 ���� 2 ��ư
	this->RegisterTextureID(90, 22818, 24, 19);//  	UI_Button18_D_24X19.bmp
	this->RegisterTextureID(91, 22819, 24, 19);//  	UI_Button18_N_24X19.bmp
	this->RegisterTextureID(92, 22820, 24, 19);//  	UI_Button18_O_24X19.bmp
	// �κ��丮 ���� 1 ��ư
	this->RegisterTextureID(184, 22821, 24, 19);//  	UI_Button17_D_24X19.bmp
	this->RegisterTextureID(185, 22822, 24, 19);//  	UI_Button17_N_24X19.bmp
	this->RegisterTextureID(186, 22823, 24, 19);//  	UI_Button17_O_24X19.bmp

	// ���� ������ ��ư (���ο�)
	this->RegisterTextureID(93, 22824, 32, 29);//		UI_Button28_D_32X29.bmp
	this->RegisterTextureID(94, 22825, 32, 29);//		UI_Button28_N_32X29.bmp
	this->RegisterTextureID(95, 22826, 32, 29);//		UI_Button28_O_32X29.bmp

	// ä���� �ִ� ���� ��ư (�޽��� �ڽ��� ����)
	this->RegisterTextureID(97, 22828, 72, 19);//		UI_Button14_O_72X19.bmp
	this->RegisterTextureID(98, 22829, 72, 19);//		UI_Button14_D_72X19.bmp
	this->RegisterTextureID(99, 22830, 72, 19);//		UI_Button14_N_72X19.bmp

	// ��ũ�ѹ� ��ư (���� ����)
	this->RegisterTextureID(133, 22838, 14, 16);//		UI_ScrollBar_Button01_D_D14X16.bmp
	this->RegisterTextureID(134, 22839, 14, 16);//		UI_ScrollBar_Button01_D_U14X16.bmp
	this->RegisterTextureID(135, 22840, 14, 14);//		UI_ScrollBar_Button01_D_WB14X14.bmp
	this->RegisterTextureID(136, 22841, 14, 16);//		UI_ScrollBar_Button01_N_D14X16.bmp
	this->RegisterTextureID(137, 22842, 14, 16);//		UI_ScrollBar_Button01_N_U14X16.bmp
	this->RegisterTextureID(138, 22843, 14, 14);//		UI_ScrollBar_Button01_N_WB14X14.bmp
	this->RegisterTextureID(139, 22844, 14, 16);//		UI_ScrollBar_Button01_O_D14X16.bmp
	this->RegisterTextureID(140, 22845, 14, 16);//		UI_ScrollBar_Button01_O_U14X16.bmp
	this->RegisterTextureID(141, 22846, 14, 14);//		UI_ScrollBar_Button01_O_WB14X14.bmp
	this->RegisterTextureID(142, 22847, 14, 14);//		UI_ScrollBar_Button02_D_WB14X14.bmp
	this->RegisterTextureID(143, 22848, 14, 14);//		UI_ScrollBar_Button02_N_WB14X14.bmp
	this->RegisterTextureID(144, 22849, 14, 14);//		UI_ScrollBar_Button02_O_WB14X14.bmp
	this->RegisterTextureID(145, 22850, 16, 14);//		UI_ScrollBar_Button01_N_R16X14.bmp
	this->RegisterTextureID(146, 22851, 16, 14);//		UI_ScrollBar_Button01_O_R16X14.bmp
	this->RegisterTextureID(147, 22852, 16, 14);//		UI_ScrollBar_Button01_D_R16X14.bmp
	this->RegisterTextureID(148, 22853, 16, 14);//		UI_ScrollBar_Button01_N_L16X14.bmp
	this->RegisterTextureID(149, 22854, 16, 14);//		UI_ScrollBar_Button01_D_L16X14.bmp
	this->RegisterTextureID(150, 22855, 16, 14);//		UI_ScrollBar_Button01_O_L16X14.bmp

	// �����Թ� ��ư
	this->RegisterTextureID(57, 22119, 25, 24);//		UI_Button23_N_25X24.bmp
	this->RegisterTextureID(58, 22120, 25, 24);//		UI_Button23_O_25X24.bmp
	this->RegisterTextureID(59, 22121, 25, 24);//		UI_Button23_D_25X24.bmp
	// �����Թ� ��ư (�Ʒ�)
	this->RegisterTextureID(60, 22122, 14, 14);//		UI_Button24_N_14X14.bmp
	this->RegisterTextureID(61, 22134, 14, 14);//		UI_Button24_O_14X14.bmp
	this->RegisterTextureID(62, 22135, 14, 14);//		UI_Button24_D_14X14.bmp
	// �����Թ� ��ư(��)
	this->RegisterTextureID(151, 22136, 14, 14);//		UI_Button25_N_14X14.bmp
	this->RegisterTextureID(152, 22137, 14, 14);//		UI_Button25_O_14X14.bmp
	this->RegisterTextureID(153, 22149, 14, 14);//		UI_Button25_D_14X14.bmp

	// �����Թ� ��ư (����)
	this->RegisterTextureID(154, 22150, 24, 37);//		UI_Button26_N_24X37.bmp
	this->RegisterTextureID(155, 22151, 24, 37);//		UI_Button26_O_24X37.bmp
	this->RegisterTextureID(176, 22172, 24, 37);//		UI_Button26_D_24X37.bmp
	// �����Թ� ��ư (����)
	this->RegisterTextureID(177, 22173, 38, 23);//		UI_Button27_N_38X23.bmp
	this->RegisterTextureID(178, 22174, 38, 23);//		UI_Button27_O_38X23.bmp
	this->RegisterTextureID(179, 22175, 38, 23);//		UI_Button27_D_38X23.bmp

	// ������ ��ư
	this->RegisterTextureID(156, 22203, 32, 29);//		UI_Button28_N_32X29.bmp
	this->RegisterTextureID(157, 22204, 32, 29);//		UI_Button28_O_32X29.bmp
	this->RegisterTextureID(158, 22205, 32, 29);//		UI_Button28_D_32X29.bmp

	// �ݼӼ� ��ư
	this->RegisterTextureID(159, 22206, 64, 19);//		UI_Button39_N_64X19.bmp
	this->RegisterTextureID(160, 22217, 64, 19);//		UI_Button39_O_64X19.bmp
	this->RegisterTextureID(161, 22218, 64, 19);//		UI_Button39_D_64X19.bmp

	// GM �̹��� ��ư(Ʃ�丮�� ����â)
	this->RegisterTextureID(168, 22260, 60, 62);//		UI_Button40_N_60X62.bmp
	this->RegisterTextureID(180, 22305, 60, 62);//		UI_Button40_O_60X62.bmp
	this->RegisterTextureID(181, 22311, 60, 62);//		UI_Button40_D_60X62.bmp
	
	// ��ųâ ȭ��ǥ
	this->RegisterTextureID(182, 22312, 5, 27);//		UI_WidthLine03_5X27.bmp
	this->RegisterTextureID(183, 22313, 79, 16);//		UI_WidthLine03_79X16.bmp

	// ��ư Over, Down�� ��� Normal�� 0
	this->RegisterTextureID(200, 22397, 1, 3); // UI_WidthLine_EX_12_1X11.bmp
	this->RegisterTextureID(201, 22398, 182, 12); // UI_Box01.bmp	���ùڽ� (ä��â)
	this->RegisterTextureID(202, 22399, 291, 39); // UI_Box02.bmp	���ùڽ� (�ּҷ�)

	// ���󳪹�
	this->RegisterTextureID(203, 22400, 1, 3);//		22400	UI_WidthLine03_1X3.bmp

	//ä��â �߰� ��ư
	this->RegisterTextureID(204, 22463, 64, 21);//		22463	UI_Button44_N_64X21.bmp
	this->RegisterTextureID(205, 22464, 64, 21);//		22464	UI_Button44_O_64X21.bmp
	this->RegisterTextureID(206, 22485, 64, 21);//		22485	UI_Button44_D_64X21.bmp
	this->RegisterTextureID(207, 22486, 31, 21);//		22486	UI_Button43_N_31X21.bmp
	this->RegisterTextureID(208, 22501, 31, 21);//		22501	UI_Button43_O_31X21.bmp
	this->RegisterTextureID(209, 22722, 31, 21);//		22722	UI_Button43_D_31X21.bmp
	
	this->RegisterTextureID(210, 22724, 47, 47);//		22724	UI_Button45_N_47X47.bmp
	this->RegisterTextureID(211, 22725, 47, 47);//		22725	UI_Button45_O_47X47.bmp
	this->RegisterTextureID(212, 22726, 47, 47);//		22726	UI_Button45_D_47X47.bmp

	this->RegisterTextureID(213, 23104, 19, 19);	//23104	UI_Button48_N_19X19.bmp
	this->RegisterTextureID(214, 23105, 19, 19);	//23105	UI_Button48_O_19X19.bmp
	this->RegisterTextureID(215, 23106, 19, 19);	//23106	UI_Button48_D_19X19.bmp
	this->RegisterTextureID(216, 23107, 64, 19);	//23107	UI_Button47_N_64X19.bmp
	this->RegisterTextureID(217, 23108, 64, 19);	//23108	UI_Button47_O_64X19.bmp
	this->RegisterTextureID(218, 23109, 64, 19);	//23109	UI_Button47_D_64X19.bmp

	this->RegisterTextureID(219, 23110, 31, 21);		//23110	UI_Button42_N_31X21.bmp
	this->RegisterTextureID(220, 23111, 31, 21);		//23111	UI_Button42_O_31X21.bmp
	this->RegisterTextureID(221, 23112, 31, 21);		//23112	UI_Button42_D_31X21.bmp
	}
	else	// Intro Index�� ����
	{
	// UI �ؽ�ó ���� ��� (���߿� ��Ų���� ������ ���� ���Ϸ� ��������)
	this->RegisterTextureID(0, 27023, 1, 1);
	this->RegisterTextureID(5, 27159, 28, 25);
	this->RegisterTextureID(6, 27160, 28, 25);
	this->RegisterTextureID(7, 27161, 28, 25);
	this->RegisterTextureID(1, 27162, 3, 32);
	this->RegisterTextureID(2, 27163, 96, 3);
	this->RegisterTextureID(3, 27164, 128, 32);
	this->RegisterTextureID(4, 27165, 19, 18);
	this->RegisterTextureID(8, 27166, 64, 6);
	this->RegisterTextureID(9, 27167, 152, 19);
	this->RegisterTextureID(10, 27168, 79, 19);
	this->RegisterTextureID(11, 27169, 79, 19);
	this->RegisterTextureID(12, 27170, 19, 18);
	this->RegisterTextureID(13, 27171, 13, 13);
	this->RegisterTextureID(14, 27172, 13, 13);
	this->RegisterTextureID(15, 27173, 13, 13);
	
	this->RegisterTextureID(16, 27037, 256, 32); // UI_Button Big_1.bmp
	this->RegisterTextureID(17, 27038, 256, 32); // UI_Button Big_2.bmp
	this->RegisterTextureID(18, 27061, 256, 32); // UI_Button Big_3.bmp

	this->RegisterTextureID(19, 27039, 256, 32); // UI_Button large_1.bmp
	this->RegisterTextureID(20, 27040, 256, 32); // UI_Button large_2.bmp
	this->RegisterTextureID(21, 27041, 256, 32); // UI_Button large_3.bmp

	this->RegisterTextureID(22, 27042, 16, 16); // UI_Button right_1.bmp
	this->RegisterTextureID(23, 27043, 16, 16); // UI_Button right_2.bmp
	this->RegisterTextureID(24, 27044, 16, 16); // UI_Button right_3.bmp

	this->RegisterTextureID(25, 27045, 64, 32); // UI_Button small_1.bmp
	this->RegisterTextureID(26, 27046, 64, 32); // UI_Button small_2.bmp
	this->RegisterTextureID(27, 27047, 64, 32); // UI_Button small_3.bmp

	this->RegisterTextureID(28, 27048, 16, 16); // UI_Button up_1.bmp
	this->RegisterTextureID(29, 27049, 16, 16); // UI_Button up_2.bmp
	this->RegisterTextureID(30, 27050, 16, 16); // UI_Button up_3.bmp

	this->RegisterTextureID(31, 27051, 64, 64);	// UI_IN_12.tga
	this->RegisterTextureID(32, 27052, 512, 512);	// UI_IN_Charac_Del_01.tga
	this->RegisterTextureID(33, 27053, 512, 512); // UI_IN_Character_01.tga
	this->RegisterTextureID(34, 27054, 512, 256); // UI_IN_Login_01.tga
	this->RegisterTextureID(35, 27055, 512, 512); // UI_IN_New_Character_01.tga
	this->RegisterTextureID(36, 27056, 512, 512); // UI_IN_Sever_01.tga
	this->RegisterTextureID(37, 27057, 512, 512); // UI_New_Character_03.tga

	this->RegisterTextureID(38, 27058, 16, 16); // UI_Button left_1.bmp
	this->RegisterTextureID(39, 27059, 16, 16); // UI_Button left_2.bmp
	this->RegisterTextureID(40, 27060, 16, 16); // UI_Button left_3.bmp

	this->RegisterTextureID(199, 27022, 7, 16);	 // Ŀ��
	this->RegisterTextureID(100, 26083, 512, 512);	// Tantra V3 Logo800
	this->RegisterTextureID(101, 26084, 1024, 512);	// Tantra V3 Logo1024
	}
}

// UI ���� ������ �����մϴ�.
void CHTUIManager::HT_vSaveDialogPos(CHTString strFilePath)
{
	CHTString	str;
	int			iVersion;
	int			iPosX, iPosY;
	int			iScreenX, iScreenY;

	FILE*	fp;
	fp = fopen(strFilePath, "wb");
	if (!fp) return;

	// �����
	str = _T("HanbitSoft GameDev.Team");	fwrite(&str, sizeof(CHTString), 1, fp);	// ���� ����
	iVersion = _INTERFACE_VERSION;			fwrite(&iVersion, sizeof(int), 1, fp);	// ����
	iScreenX	= m_iScreenX;				fwrite(&iScreenX, sizeof(int), 1, fp);	// �ػ� X
	iScreenY	= m_iScreenY;				fwrite(&iScreenY, sizeof(int), 1, fp);	// �ػ� Y

	// ���� ������ ��ġ ����
	const int START_COUNT_INDEX = 200; 
	for (HTint i=0; i < 95; i++)
	{
		g_cUIManager->HT_GetWindowPos(START_COUNT_INDEX + i, iPosX, iPosY);
		fwrite(&iPosX, sizeof(int), 1, fp);
		fwrite(&iPosY, sizeof(int), 1, fp);
	}

	// �׿� ������ ����
	fwrite( &(g_cQuickSlot->m_bVerSlot), sizeof(HTbool), 1, fp);	// ������ ����

	// �ɼ� ���� ����
	//- ������, ���̵�ǥ��, ����Ʈ, ��������ȭ, ����, ����, ä�ø��, ���ιٰ���ȭ
	//HT_vSystem_InputCheckSystem(int iAction, int iTarget, int iTargetID)
	fwrite( &(g_cSystem->m_iOption0), sizeof(int), 1, fp);	// ������ ����
	fwrite( &(g_cSystem->m_bOption1), sizeof(HTbool), 1, fp);	// ������ ����
	fwrite( &(g_cSystem->m_bOption2), sizeof(HTbool), 1, fp);	// ������ ����
	fwrite( &(g_cSystem->m_bOption3), sizeof(HTbool), 1, fp);	// ������ ����
	fwrite( &(g_cSystem->m_iOption4), sizeof(int), 1, fp);	// ������ ����
	fwrite( &(g_cSystem->m_iOption5), sizeof(int), 1, fp);	// ������ ����

	// ä�� ���� ����
	fwrite( &(g_cChatting->m_iChatWindowStyle), sizeof(int), 1, fp);

	// �߰� ����
	fwrite( &(g_cSystem->m_bOption6), sizeof(HTbool), 1, fp);	// ������ ����

	// ������ �߰� ����
	for (HTint i=95; i < 120; i++)
	{
		g_cUIManager->HT_GetWindowPos(START_COUNT_INDEX + i, iPosX, iPosY);
		fwrite(&iPosX, sizeof(int), 1, fp);
		fwrite(&iPosY, sizeof(int), 1, fp);
	}

	fclose(fp);
}

// UI ���� ������ �ε��մϴ�.
void CHTUIManager::HT_vOpenDialogPos(CHTString strFilePath)
{
	CHTString	str;
	int			iVersion;
	int			iPosX, iPosY;
	int			iScreenX, iScreenY;

	FILE*	fp;
	fp = fopen(strFilePath, "rb");
	if (!fp) return;

	// �����
	fread(&str, sizeof(CHTString), 1, fp);	// ���� ����
	fread(&iVersion, sizeof(int), 1, fp);	// ����
	fread(&iScreenX, sizeof(int), 1, fp);	// �ػ� X
	fread(&iScreenY, sizeof(int), 1, fp);	// �ػ� Y

	if (iVersion != _INTERFACE_VERSION || iScreenX != m_iScreenX || iScreenY != m_iScreenY) 
	{
		fclose(fp);
		return;
	}
	
	// ���� ������ ��ġ ����
	const int START_COUNT_INDEX = 200; 
	for (HTint i=0; i < 95; i++)
	{
		fread(&iPosX, sizeof(int), 1, fp);
		fread(&iPosY, sizeof(int), 1, fp);
		g_cUIManager->HT_MoveWindow(START_COUNT_INDEX + i, iPosX, iPosY);
	}

	// ţ ������ ����� ����, ���� ��ġ �����Ͽ� ���
	bool bFlag = false;	
	fread( &(bFlag), sizeof(HTbool), 1, fp); g_cQuickSlot->m_bVerSlot = bFlag ;
	

	// ������ ����
	if( bFlag == false )
	{
		//	���� �κ��丮�� ��ġ�� ���ؿͼ� �ױ⿡ �˾��Ѵ�.
		g_cUIManager->HT_HideWindow( _DIALOG_HQUICKSLOT );
		g_cUIManager->HT_ShowWindow( _DIALOG_WQUICKSLOT );
	}
	else 
	{
		g_cUIManager->HT_HideWindow( _DIALOG_WQUICKSLOT );
		g_cUIManager->HT_ShowWindow( _DIALOG_HQUICKSLOT );
	}

	// �ɼ� ���� �ε� �� ����
	fread( &(g_cSystem->m_iOption0), sizeof(int), 1, fp);	// ������, 
	fread( &(g_cSystem->m_bOption1), sizeof(HTbool), 1, fp);	// ���̵�ǥ��, 
	fread( &(g_cSystem->m_bOption2), sizeof(HTbool), 1, fp);	// ����Ʈ, 
	fread( &(g_cSystem->m_bOption3), sizeof(HTbool), 1, fp);	// ��������ȭ, 
	fread( &(g_cSystem->m_iOption4), sizeof(int), 1, fp);	// ����, 
	fread( &(g_cSystem->m_iOption5), sizeof(int), 1, fp);	// ����, 

	// �ɼ����� �ε�
	if (g_cSystem->m_bOption1 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 4);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 5);

	if (g_cSystem->m_bOption2 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 6);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 7);

	if (g_cSystem->m_bOption3 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 8);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 9);

	// �ɼ� ���� ����
	if (g_cSystem->m_iOption0 > 100) g_cSystem->m_iOption0 = 20;
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 20, g_cSystem->m_iOption0 );
	g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_SCROLLBAR, 20);
	if (g_cSystem->m_iOption4 > 11) g_cSystem->m_iOption4 = 20;
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 21, g_cSystem->m_iOption4 );
	g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_SCROLLBAR, 21);
	if (g_cSystem->m_iOption5 > 11) g_cSystem->m_iOption5 = 20;
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 22, g_cSystem->m_iOption5 );
	g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_SCROLLBAR, 22);
	
	// ä�� ���� �ε� 
	fread( &(g_cChatting->m_iChatWindowStyle), sizeof(int), 1, fp);

	// ä�û��� ����
	if (g_cChatting->m_iChatWindowStyle < 0 || g_cChatting->m_iChatWindowStyle > 3)
		g_cChatting->m_iChatWindowStyle = 1;
	
	g_cChatting->m_iChatWindowStyle--;
	if (g_cChatting->m_iChatWindowStyle < 0) g_cChatting->m_iChatWindowStyle = 3;
	
	g_cChatting->HT_vChatting_ChangeChatWnd();
	g_cChatting->HT_vChatting_SetFocusOff( false );

	fread( &(g_cSystem->m_bOption6), sizeof(HTbool), 1, fp);	// ����

	// �ɼ����� �ε�
	if (g_cSystem->m_bOption6 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 13);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 14);

	// ������ �߰� �ε�
	for (HTint i=95; i < 120; i++)
	{
		fread(&iPosX, sizeof(int), 1, fp);
		fread(&iPosY, sizeof(int), 1, fp);
		g_cUIManager->HT_MoveWindow(START_COUNT_INDEX + i, iPosX, iPosY);
	}

	//fread( &(m_bChattingMode), sizeof(HTbool), 1, fp);
	//fread( &(m_bMinimapMode), sizeof(HTbool), 1, fp);
	fclose(fp);
}