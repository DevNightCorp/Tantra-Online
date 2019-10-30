#ifndef __SEQ_GENERATOR_INCLUDE__
#define __SEQ_GENERATOR_INCLUDE__

#include <windows.h>

#define RANDOM_BITMASK			0xC894		// Random 값에 XOR 연산할 Bit-mask
#define RANDOM_KEY_MASK			0x000000FF
#define RANDOM_MODULER			USHRT_MAX
#define RANDOM_VAR_MULTIPLER	8
#define RANDOM_VAR_ADDER		5
#define RANDOM_VAR_DIVIDER		3
#define RANDOM_PREV_ADDER		0xD0F1		// dwPrev 값에 더해서 계산...

// Key가 정해지면, Init을 이용하여 초기화를 시켜준다.
// 초기화 이후 GoNext를 이용해서 한번씩 Seq를 Generate.
// GetCurrent를 하면, 다음 시퀀스를 얻어올 수 있다.

class CSeqGenerator
{
private:
	WORD m_wCurrent;
	WORD m_wVariable;
	WORD m_wKey;

	WORD GetRandom(WORD wPrev);

public:
	CSeqGenerator();
	~CSeqGenerator();

	void Init(DWORD dwKey);
	BOOL IsInited();
	void GoNext();
	WORD GetCurrent();
};

#endif //__SEQ_GENERATOR_INCLUDE__