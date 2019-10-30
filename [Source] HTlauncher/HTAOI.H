

#ifndef __HTAOI_H__
#define __HTAOI_H__


class HTAOI
{
public:
	HTAOI();
	~HTAOI();

	HTRESULT			HT_AOI_Init();
	BYTE				HT_AOI_Level( HTPoint pCellPoint );
	BYTE				HT_AOI_AttackRange_Level( BYTE, DWORD iID, HTPoint pCell, BYTE bySize );

	BYTE				HT_AOI_OtherChar_Request( HTint x, HTint z );


private:
	BYTE				m_Level1_Size;
	BYTE				m_Level2_Size;
	BYTE				m_Level3_Size;
	BYTE				m_Level4_Size;
	BYTE				m_Level5_Size;
	BYTE				m_Level6_Size;
	BYTE				m_Level7_Size;
	BYTE				m_Level8_Size;
};

#endif
