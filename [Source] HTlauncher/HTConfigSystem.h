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

	// �ʱ�ȭ������ ������ �� �ε��� ���´�.
	HTRESULT		HT_hrLoad( HTtchar* pFileName );

	// �ʱ�ȭ���Ͽ� ������ ���̺��Ѵ�. 
	// TODO : ������ �������Ϳ� ����� ���� ���� ���̴�.
	HTRESULT		HT_hrSave( HTtchar* pFileName );

	// Ŭ�����̸��� �������̸����� �ش� ���� ���´�.
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

	// Ŭ�����̸��� �������̸��� �ش��ϴ� ���� �ٲ۴�.
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
	// Ŭ����(�ɼ� �׷�)���� ��Ʈ������ Ű�� �ؼ� ã������ map�� ���.
	std::map<string,HT_CONFIGCLASS*>	m_mapClasses;

};


#endif	// #ifndef _HTCONFIGSYSTEM_H_
