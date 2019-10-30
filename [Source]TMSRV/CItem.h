#ifndef _CITEM_
#define _CITEM_




// 
#define ITEMPOS_WEAPON      0  // 0-3

#define ITEMPOS_PINPOINT    4
#define ITEMPOS_BUCKSHOT    5
#define ITEMPOS_BUNDLEITEM  6
#define ITEMPOS_ENGINE      7
#define ITEMPOS_VESSEL      8
#define ITEMPOS_HULL        9
#define ITEMPOS_SHELL      10
#define ITEMPOS_SAIL       11

#define ITEMPOS_AMULET     12
#define ITEMPOS_ORB        13
#define ITEMPOS_TELESCOPE  14 
#define ITEMPOS_SEXTANT    15


//#define ITEMPOS_HOLYWATER  17  // ??

// ���� ����Ʈ�� 2���̻��� �������� ������ ���
// ITEMPOS_XXX1, ITEMPOS_XXX2, �� ó���Ѵ�.
// <<���� ���� ����Ʈ�� ȣȯ �� ��� ���� ó��>>
class CItem
{


    public:
	
    CItem();
    ~CItem();
   public:
     STRUCT_ITEM ITEM;
     int  Mode;       
     int  PosX,PosY;
     int  GridCharge;
     int  State;
     int  Rotate;
	 int  Delay;
	 int  Decay;
	 int  Height;
	 int  Money;
	 int  m_iOwner ; // party // �ڽ��� party ID�� �����ϸ� �׳� �ݴ´�.
	 unsigned int m_uiReleaseTime ;   // if( 0 != m_iOwner ) if( timeGetTime() > m_uiReleaseTime )  �ֿ��� �ȴ�.
	 unsigned int m_uiEventTriggerTime ;
};


#endif
