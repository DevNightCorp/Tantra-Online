#pragma once

class CTFPercentMixer
{
public:
	CTFPercentMixer(void);
	~CTFPercentMixer(void);
	void Initialize();
	char GetValue(int nPercent); 
	char GetValue2(int nPercent); 
private:
	void Reset();
	void PartReset(int nPercent);
	char m_byValues[101][100];
	short m_snIndex[101];
};
