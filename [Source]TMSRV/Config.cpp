#include "config.h"

CConfig::CConfig(void)
{
	ZeroMemory(m_szQuiz, sizeof(m_szQuiz));
	ZeroMemory(m_szQuizAnswer, sizeof(m_szQuizAnswer));
	for(int i=0; i<MAX_QUIZCOUNT; i++)
        m_nQuizCorrect[i] = 0;
	m_nQuizTime = 0;
	m_nQuizCount = 0;
	m_clRandom.Init();
	m_clRandom.AddCard(1, 25);
	m_clRandom.AddCard(2, 25);
	m_clRandom.AddCard(3, 25);
	m_clRandom.AddCard(4, 25);
	m_clRandom.Shuffle();
}

CConfig::~CConfig(void)
{

}

bool CConfig::ReadQuiz()
{
	ZeroMemory(m_szQuiz, sizeof(m_szQuiz));
	ZeroMemory(m_szQuizAnswer, sizeof(m_szQuizAnswer));
	for(int i=0; i<MAX_QUIZCOUNT; i++)
        m_nQuizCorrect[i] = 0;
	m_nQuizTime = 0;

	char pData[MAX_QUIZSTRING] = {0,};
	char pAns[MAX_QUIZANSWERSTRING] = {0,}; 

	FILE *fp = fopen(FILE_QUIZ,"rt");
	if ( fp == NULL ) return false;

	if( fscanf(fp, "%d", &m_nQuizTime) == EOF ) 
	{	fclose(fp);
		return false;
	}
	if( fgets(pData, MAX_QUIZSTRING, fp) == NULL)
	{	fclose(fp);
		return false;
	}

	for(WORD w=0; w<MAX_QUIZCOUNT; w++)
	{
		ZeroMemory(pData, sizeof(pData));
		if( fgets(pData, MAX_QUIZSTRING, fp) == NULL) break;
		strncpy(m_szQuiz[w], pData, strlen(pData));

		for(int i=0; i<MAX_QUIZANSWER; i++)
		{
			ZeroMemory(pAns, sizeof(pAns));
			if( fgets(pAns, MAX_QUIZANSWERSTRING, fp) == NULL) { fclose(fp); return true;}
			strncpy(m_szQuizAnswer[w][i], pAns, strlen(pData));
		}

		m_nQuizCount++;

		if( fscanf(fp, "%d", &m_nQuizCorrect[w]) == EOF ) break;
		if( fgets(pData, MAX_QUIZSTRING, fp) == NULL) break;
	}
	fclose(fp);

	return true;
}

void CConfig::GetQuiz(int nQuiz, Msg_Quiz* pQuiz, DWORD* pdwAns)
{
	if(nQuiz<1 || nQuiz>MAX_QUIZCOUNT) return;
	if(pQuiz == NULL) return;

	byte byAns[MAX_QUIZANSWER] = {0, 1, 2, 3};

	srand(timeGetTime());
	strncpy(pQuiz->pszQuiz, m_szQuiz[nQuiz-1], strlen(m_szQuiz[nQuiz-1]));

	for( int i = 0 ; i < MAX_QUIZANSWER ; i++ )
	{
		byte byLoc = m_clRandom.Random() % MAX_QUIZANSWER ;
		if(i==byLoc) continue;
		byte byTemp = byAns[i];
		byAns[i] = byAns[byLoc];
		byAns[byLoc] = byTemp;
	}

	for(i=0; i<MAX_QUIZANSWER; i++)
	{
		if(byAns[i]==(m_nQuizCorrect[nQuiz-1]-1)) break;
	}

	if(i>=4) 
	{	*pdwAns = MAX_QUIZANSWER;
		return;
	}

	*pdwAns = i+1;
	m_nQuizCorrect[nQuiz-1] = i+1;
	char pAns[MAX_QUIZANSWER][MAX_QUIZANSWERSTRING] = {0,};
	memcpy(pAns, m_szQuizAnswer[nQuiz-1], sizeof(pAns));

	for(i=0; i<MAX_QUIZANSWER; i++)
	{
		memcpy(m_szQuizAnswer[nQuiz-1][i], pAns[byAns[i]], MAX_QUIZANSWERSTRING);
		strncpy(pQuiz->pszQuizSelect1[i], m_szQuizAnswer[nQuiz-1][i], strlen(m_szQuizAnswer[nQuiz-1][i]));
	}
}

/*
int CConfig::GetQuizCorrect(int nQuiz)
{
	if(nQuiz<1 || nQuiz>MAX_QUIZCOUNT) return -1;

	return m_nQuizCorrect[nQuiz-1];
}*/
