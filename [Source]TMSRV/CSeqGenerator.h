#ifndef __SEQ_GENERATOR_INCLUDE__
#define __SEQ_GENERATOR_INCLUDE__

#include <windows.h>

#define RANDOM_BITMASK			0xC894		// Random ���� XOR ������ Bit-mask
#define RANDOM_KEY_MASK			0x000000FF
#define RANDOM_MODULER			USHRT_MAX
#define RANDOM_VAR_MULTIPLER	8
#define RANDOM_VAR_ADDER		5
#define RANDOM_VAR_DIVIDER		3
#define RANDOM_PREV_ADDER		0xD0F1		// dwPrev ���� ���ؼ� ���...

// Key�� ��������, Init�� �̿��Ͽ� �ʱ�ȭ�� �����ش�.
// �ʱ�ȭ ���� GoNext�� �̿��ؼ� �ѹ��� Seq�� Generate.
// GetCurrent�� �ϸ�, ���� �������� ���� �� �ִ�.

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