#pragma once
#include "Basedef.h"
#include "TNDeck100.h"

class CConfig
{
private:
	char	m_szQuiz[MAX_QUIZCOUNT][MAX_QUIZSTRING];
	char	m_szQuizAnswer[MAX_QUIZCOUNT][MAX_QUIZANSWER][MAX_QUIZANSWERSTRING];
	int		m_nQuizCorrect[MAX_QUIZCOUNT];
	int		m_nQuizTime;
	int		m_nQuizCount;
	TNDeck100 m_clRandom;
public:
	CConfig(void);
	~CConfig(void);

	void GetQuiz(int nQuiz, Msg_Quiz* pQuiz, DWORD* pdwAns);
	bool ReadQuiz();

	int GetQuizCount() { return m_nQuizTime; }
	int GetMaxQuiz() { return m_nQuizCount; }
};
