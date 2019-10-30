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

// 동일 포인트에 2개이상의 아이템이 장착될 경우
// ITEMPOS_XXX1, ITEMPOS_XXX2, 로 처리한다.
// <<장착 가능 포인트가 호환 될 경우 예외 처리>>
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
	 int  m_iOwner ; // party // 자신의 party ID와 동일하면 그냥 줍는다.
	 unsigned int m_uiReleaseTime ;   // if( 0 != m_iOwner ) if( timeGetTime() > m_uiReleaseTime )  주워도 된다.
	 unsigned int m_uiEventTriggerTime ;
};


#endif
