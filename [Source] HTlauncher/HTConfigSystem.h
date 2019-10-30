#ifndef _HTCONFIGSYSTEM_H_
#define _HTCONFIGSYSTEM_H_

typedef struct _HT_CONFIGCLASS
{
	std::map<string,HTbool>		mapItemBool;
	std::map<string,HTint>		mapItemInt;
	std::map<string,HTfloat>	mapItemFloat;
	std::map<string,string>		mapItemString;

	std::map<string,string>		mapItemConsoleCommand;
} HT_CONFIGCLASS;

class CHTConfigSystem
{
public:
					CHTConfigSystem();
	virtual			~CHTConfigSystem();

	// 초기화파일의 내용을 쭉 로드해 놓는다.
	HTRESULT		HT_hrLoad( HTtchar* pFileName );

	// 초기화파일에 내용을 세이브한다. 
	// TODO : 윈도우 레지스터에 등록할 수도 있을 것이다.
	HTRESULT		HT_hrSave( HTtchar* pFileName );

	// 클래스이름과 아이템이름으로 해당 값을 얻어온다.
	HTRESULT		HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTint* pValue );
	HTRESULT		HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTfloat* pValue );
	HTRESULT		HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTtchar* pValue );
	HTRESULT		HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTbool* pValue );
	HTRESULT		HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTuint* pValue );

	// 클래스이름과 아이템이름에 해당하는 값을 바꾼다.
	HTRESULT		HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTint iValue );
	HTRESULT		HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTfloat fValue );
	HTRESULT		HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTtchar* pValue );
	HTRESULT		HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTbool bValue );
	HTRESULT		HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTuint nValue );

private:
	// 클래스(옵션 그룹)들을 스트링값을 키로 해서 찾기위해 map을 썼다.
	std::map<string,HT_CONFIGCLASS*>	m_mapClasses;

};


#endif	// #ifndef _HTCONFIGSYSTEM_H_
