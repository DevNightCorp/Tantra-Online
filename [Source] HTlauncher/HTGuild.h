#pragma once


#define 	GUILDTYPE_NONE						0			//	길드 회원 아님
#define 	GUILDTYPE_GUILDMASTER				1			//	길드 장
#define 	GUILDTYPE_GUILDMEMBER				2			//	길드 멤버

#define 	GUILDTYPE_CONFIRM_NONE				0			//	아무 단계 아님
#define 	GUILDTYPE_CONFIRM_CREATE			1			//	창설요청
#define 	GUILDTYPE_CONFIRM_JOIN				2			//	가입요청을 함
#define 	GUILDTYPE_CONFIRM_SECEDE			4			//	탈퇴요청
#define 	GUILDTYPE_CONFIRM_DESTROY			5			//	해체요청
#define 	GUILDTYPE_CONFIRM_JOINNOTIFY		6			//	가입을 알린다.
#define 	GUILDTYPE_CONFIRM_EXPEL				7			//	제명시킨다.
#define 	GUILDTYPE_CONFIRM_MAKEBLOG			8			//	홈피 제작
#define 	GUILDTYPE_CONFIRM_ENTERBLOG			9			//	홈피 입장
#define 	GUILDTYPE_CONFIRM_REQALLIANCE		10			//	연합아쉬람 가입요청
#define 	GUILDTYPE_CONFIRM_RECIVEALLIANCE	11			//	가입요청 받음
#define 	GUILDTYPE_CONFIRM_PERSONALBLOG		12			//	개인블로그
#define 	GUILDTYPE_CONFIRM_OTHERBLOG			13			//	딴사람블로그
#define 	GUILDTYPE_CONFIRM_PERSONALBOARD		14			//	게인정보판
#define 	GUILDTYPE_CONFIRM_ERROR				99			//	에러메시지



class HTGuild
{
public:
	HTGuild(void);
	~HTGuild(void);

	//	데이타 삭제
	HTvoid				HT_vGuild_Delete();
	//	초기 데이타 셋팅
	HTvoid				HT_vGuild_Init();
	//	Create Window
	HTvoid				HT_vGuild_CreateWindow();

	//	입력 메세지 처리
	//	AshramInfo
	static void			HT_vGuild_InputCheckForAshramInfo(int iAction, int iTarget, int iTargetID);
	//	AshramMemberList
	static void			HT_vGuild_InputCheckForAshramMemberList(int iAction, int iTarget, int iTargetID);
	//	AshramCago
	static void			HT_vGuild_InputCheckForAshramCago(int iAction, int iTarget, int iTargetID);
	//	Sanction Ashram Cago
	static void			HT_vGuild_InputCheckForSanctionAshramCago(int iAction, int iTarget, int iTargetID);
	//	SetLevel Ashram Cago
	static void			HT_vGuild_InputCheckForSetLevelAshramCago(int iAction, int iTarget, int iTargetID);
	// 앰블럼 제작창
	static void			HT_vGuild_InputCheckForEmblemSelecting(int iAction, int iTarget, int iTargetID);
	HTvoid				HT_vGuild_DialogBoxDrawTab(int iTabNo);			// 해당 텝번호의 윈도우를 그려줍니다. (길드마크 제작창 앰블럼)
	HTvoid				HT_bGuild_DialogBoxDrawEmblem(int iIndex);		// 선택한 엠블럼을 입력받아 윈도우에 그려줍니다. (길드마크 제작창)
	HTvoid				HT_bGuild_DialogBoxEmblemSelect();				// 엠블램 선택 처리
	HTint				HT_bGuild_GetDialogBoxEmblemMaxButton();		// 내부처리용

	//	대화상자 활성화
	HTvoid				HT_vGuild_DialogBoxActive();
	//	대화상자 비활성화
	HTvoid				HT_vGuild_DialogBoxAntiActive();
	//	창설
	HTvoid				HT_vGuild_Create();

	//	가입
	HTRESULT			HT_vGuild_JoinGuild( HTint );
    
	//	길드 초기 정보를 받습니다.
	HTvoid				HT_vNetWork_SCP_INIT_GUILD( MSG_GuildInfo* );
	//	길드 생성을 요청한다.
	HTRESULT			HT_hrNetWork_CSP_REQ_CREATE_GUILD( CHTString strAshramName );
	//	신규 길드원의 정보를 길드원들에게 전송한다.
	HTvoid				HT_vNetWork_SCP_AddGuildMember( MSG_AddGuildMember* info );
	//	길드 해체를 요청한다.
	HTvoid				HT_vNetWork_CSP_Remove_GuildMember();
	HTvoid				HT_vNetWork_SCP_RemoveGuildMember( MSG_RemoveGuildMember* );
	//	길드 참여를 요청한다.
	HTvoid				HT_vNetWork_CSP_REQGuild();
	HTvoid				HT_vNetWork_SCP_REQGuild( MSG_REQGuild* info );
	//	길드 참여 요청 결과를 서버에 전송한다.
	HTvoid				HT_vNetWork_CSP_CNFGuild();
	//	길드원이 접속함
	HTvoid				HT_vNetWork_SCP_GuildMemberin( MSG_GuildMemberin* info );
	//	길드원이 접소을 끊음
	HTvoid				HT_vNetWork_SCP_GuildMemberout( MSG_GuildMemberout* info );
	//	길드마크 생성
	HTvoid				HT_vNetWork_CSP_MSG_GuildUpdateMark( HTbyte byCostType );
	HTvoid				HT_vNetWork_SCP_MSG_GuildUpdateMark( MSG_GuildUpdateMark* );
	//	길드업데이트
	HTvoid				HT_vNetWork_CSP_MSG_GuildUpdate( CHTString strMessage );
	HTvoid				HT_vNetWork_SCP_MSG_GuildUpdate( MSG_GuildUpdate* );
	//	길드 멤버 업데이트
	HTvoid				HT_vNetWork_SCP_MSG_GuildUpdateMember( MSG_GuildUpdateMember* );
	//	길드 랭킹 업데이트
	HTvoid				HT_vNetWork_CSP_MSG_GuildSetRanking( CHTString strTemp );
	HTvoid				HT_vNetWork_SCP_MSG_GuildSetRanking( MSG_GuildSetRanking* );

	//	길드원 리스트 대화상자에 표현하기
	HTvoid				HT_vGuild_Display();

	// 길드 마크 생성창 활성화
	HTvoid				HT_vGuild_AmblemMakeActive();
	//	길드 마크 셋팅
	HTvoid				HT_vGuild_SetEmblemID( DWORD dwEmblemID );
	//	길드 마크 ID 얻어오기
	HTint				HT_iGuild_GetEmblemID()	{	return m_dwGuild_EmblemID;	};
	//	길드 마크 표현 하기 안하기
	HTvoid				HT_vGuild_EmblemOn();
	HTvoid				HT_vGuild_EmblemOff();
	//	길드 마크 표현 처리
	HTvoid				HT_vGuild_EmblemSwitch( CHTString );

	//	주신 마크 표현 하기 안하기
	HTvoid				HT_vTrimutiri_MarkOn();
	HTvoid				HT_vTrimutiri_MarkOff();
	//	주신 마크 표현 처리
	HTvoid				HT_vTrimutiri_MarkSwitch( CHTString );

	HTvoid				HT_vSetGuildMark(HTint iBackBmpNo, HTint iShapeBmpNo, HTint iColorNo);
	HTRESULT			HT_hrGetGuildMark(HTdword dwIdentity, HTint* dwColor, HTint* dwTitle, HTint* dwEmblem);

	//	길드 이름
	CHTString			HT_strGuild_GetGuildName()	{	return m_strGuild_GuildName; };
	//	길드내의 지위
	HTbyte				HT_byGuild_GetAuthority()	{	return m_byGuild_GuilAuthority;	};
	//	길드 ID
	HTint				HT_iGuild_GetGuildID()		{	return m_oGuildInfo.GuildID;	};

	// 길드 창에 길드 마크 및 주신마크 붙여서 출력
	HTvoid				HT_vGuild_DialogBoxActiveOutput();

	//------------------------------------------------------------------------------
	// 아쉬람 연합/탈퇴 및 요새전 관련 함수
	//------------------------------------------------------------------------------

	// 길드 연합 아쉬람에서 픽업 처리
	HTRESULT			HT_hrGuild_PickCheckFromOtherObject( HTint iObjectID );
	
	// 길드 연합/탈퇴 패킷 처리
	HTvoid				HT_vGuildNet_CSP_AshuramGuild( BYTE byType, BYTE byAct, BYTE byResult );
	HTvoid				HT_vGuildNet_SCP_AshuramGuild( Msg_GuildAlliance* info );

	//	요새 소유 아쉬람 패킷 Init
	HTvoid				HT_vGuildNet_SCP_StrongGuildInit( Msg_StrongHoldInit* info );
	//	요새 소유 아쉬람 패킷 Udate
	HTvoid				HT_vGuildNet_SCP_StrongGuildUpdate( Msg_StrongHoldUpdate* info );
	//	나의 요새 소유권
	HTbool				HT_bGuildNet_MyStrongGuild()	{	return m_bMyStrongGuild;	};
	//	내가 소유한 요새의 순서
	HTint				HT_iGuildNet_MyStrongGuildSequence()	{	return m_iMyStrongGuildIndex;	};
	//	연합길드 
	CHTString			HT_strGuild_AlliedGuildName( HTint iGuildIndex );

	//	Ashram Cargo
	//	Request Ashram Item
	HTvoid				HT_vAshram_CSPAshramItem();
	//	Recive Ashram Item
	HTvoid				HT_vAshram_SCPAshramItem( Msg_GuildItem* info );
	//	Request Set Level Ashram Cargo
	HTvoid				HT_vAshram_CSPSetLevelAshramCargo( HTbyte byCargoNo, HTbyte byLevel );
	//	Recive Set Level Ashram Cargo
	HTvoid				HT_vAshram_SCPSetLevelAshramCargo( Msg_GuildCargoUsingLevel* info );
	//	Request GuildCargoTimeExtension
	HTvoid				HT_vAshram_CSPGuildCargoTimeExtension( HTbyte byType );
	//	Recive GuildCargoTimeExtension
	HTvoid				HT_vAshram_SCPGuildCargoTimeExtension( Msg_GuildCargoTimeExtension* info );
	//	Recive GuildItemUpdate
	HTvoid				HT_vAshram_SCPGuildItemUpdate( Msg_GuildItemUpdate* info );
	//	Recive GuildCargoTime
	HTvoid				HT_vAshram_SCPGuildCargoTime( Msg_GuildCargoTime* info );

	//	Return
	//	Get Ashram Cargo Extence Type
	HTbyte				HT_byAshram_GetCargoExtenceType()	{	return m_iPageOfAshramCargo;	};

private:

	//------------------------------------------------------------------------------
	// Data manipulation functions
	//------------------------------------------------------------------------------
	//----------링크드 리스트 구현한 부분---------//
	//----------LL 초기화---------//
	HTvoid HT_LL_vInitList();
	//----------LL 데이타 삽입-헤드 바로 뒤에---------//
	HTvoid HT_LL_hrInsertAfter( S_GUILD_DATA* );
	//----------LL 데이타 지우기_이름으로---------//
	HTvoid HT_LL_hrDeleteNode( CHTString strName );
	//----------LL 데이타 지우기_찿기_이름으로---------//
	S_GUILD_DATA* HT_LL_hrSerchNode( CHTString strName );
	//----------LL 데이타 에서 조사_있는지 없는지 이름으로 조사---------//
	HTRESULT HT_LL_hrExgistCheckName( CHTString strName );
    //----------LL 데이타 전부 지우기---------//
	HTvoid HT_LL_hrDeleteAll();

	//--------------------------------------------------------------------------
	// 메세지 출력
	//--------------------------------------------------------------------------
	HTvoid				HT_vGuild_SetMessage( HTint idMessage, CHTString* pstrMessage );
	HTvoid				HT_vGuild_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	// 앰블럼 제작창
	HTint				m_iTabNo;						// 텝넘버 얻기 (앰블럼)
	HTint				m_iBackIndex;					// 배경이미지 인덱스
	HTint				m_iTitleIndex;					// 타이틀이미지 인덱스
	HTint				m_iBackColor;					// 컬러 인덱스
	HTint				m_iSelectWindow;				// 0 = 일반 아쉬람 만들기 창, 1 = 브라흐마, 2 = 비슈느, 3 = 시바

	BYTE				m_byGuild_ConfirmGrade;			//	확인 단계
	HTbool				m_bGuild_ConfirmDlgBoxSw;		//	확인 버튼 눌렸는지 체크
	CHTString			m_strGuild_GuildName;			//	창설할 길드 이름
	CHTString			m_strGuild_GuildMasterName;		//	길드 마스트 이름
	CHTString			m_strGuild_ListSelectdName;		//	길드 리스트에서 선택된 사람의 이름
	BYTE				m_byGuild_GuilAuthority;		//	길드내의 지위
	DWORD				m_dwGuild_JoinGuildKeyID;		//	길드 가입을 요청할 사람의 KeyID
	HTint				m_iGuild_TempGuildID;			//	길드 가빙 승락을 위한 길드 아이디

	MSG_GuildInfo		m_oGuildInfo;
	
	CHTString			m_strGuild_CharacterName;		//	길드원 접속 및 해제한 캐릭터명
	HTint				m_nGuildConnectMsg;				//  길드원 접속 메시지 알림 체크 플래그 변수

	// 연합 아쉬람 관련
	HTint				m_nAshuramGuildJoinMode;			// 연합 아쉬람 신청 모드
	HTint				m_iAshuramGuildJoin_SendCharKeyID;	// 연합 아쉬람 신청시 상대방 아이디
	CHTString			m_strAshuramGuildJoin_SendCharName;	// 연합 아쉬람 신청시 상대방 이름
	HTint				m_byAshuramGuildJoin_ResponseReason;// 진행 상태

	CHTString			m_strAlliedGuildName[2];				// 연합 길드 이름
	CHTString			m_strEnemyGuildName[2];					// 적대 길드 이름
	
	CHTString			m_strStrongGuildName[4];				// 요새를 보유한 길드 이름
	HTbool				m_bMyStrongGuild;						// 내가 요새를 보우하고 있는지 확인
	HTint				m_iMyStrongGuildIndex;					// 내 길드 인덱스

	//	MessageBox Type
	HTint				m_iGuild_MsgBoxType;


private:
	// 주소록 데이터 리스트
	S_GUILD_DATA*			m_pGuildList_Head;
	S_GUILD_DATA*			m_pGuildList_Tail;
	HTint					m_iGuildCount;

	DWORD					m_dwGuild_EmblemID;
	HTint					m_iEmblem;
	HTint					m_iTitle;
	HTint					m_iColor;

	HTbool					m_bGuild_SlideBarBtn;
	HTint					m_iGuild_SlideBarCurPos;

	CHTString				m_szMsgSting; // 메세지에 사용될 스트링

	//	Ashram Cargo
	HTint					m_iPageOfAshramCargo;
	HTbyte					m_iPrevPageOfAshramCargo;
	//	Ashram Cargo ItemArr
	STRUCT_ITEM				m_arrItemOfAshramCargo[3][MAX_CARGO];
	//	Ashram Cargo Extence Type
	HTbyte					m_byAshramCargoExtenceType;
	//	CargoUse
	HTbool					m_bAshramCargoUseSw;
	//	UseCargoLevel
	HTbyte					m_byUseCargoLevel[3];
};
