#define		_Bad_Network_Packets			1			//	"적합하지 않은 데이터입니다"
#define		_ServerReboot_Cant_Connect		2			//	"서버가 재부팅중입니다. 잠시후에 연결이 가능합니다"
#define		_Invalid_Item_Index				3			//	"존재하지 않는 않는 아이템정보입니다"
#define		_Invalid_Item_Data				4			//	"아이템정보가 부정확합니다"
#define		_Inventory_Space_Lack			5			//	"인벤톨리공간이 부족합니다"
#define		_Not_Find_Others				6			//	"상대방을 찾을수가 없습니다"
#define		_Not_Same_Trimuriti				7			//	"상대방과 주신이 서로 다릅니다"
#define		_Reconnecting_Other_Place		8			//	"다른곳에서 접속하여 접속을 종료합니다."
#define		_Check_Account					9			//	"관리자가 계정을 확인중.."
#define		_Is_Not_Connect					10			//	"이(가) 비접속중입니다"
#define		_Is_In_Zone						11			//	"이(가) 접속중입니다 존-"
#define		_Is_Closed						12			//	"이(가) 접속종료되었습니다"
#define		_Is_Filtered					13			//	"적절치 못한 단어가 사용되었습니다"
#define		_Trimuriti_Select_Want_Level	14			//	"주신변경은 30레벨부터 가능합니다"
#define		_Serverdown_Itemserver			15			//	"캐쉬상점이 잠시 내부수리중입니다"
#define		_Challenge_Result_ZoneBroadcast	16			//	"%s님이 %님과 결투하여 승리하셧습니다"
#define		_Bramanpoint_Contribytion1		17			//	"%s님이 %s신전에 %d 주신포인트를 헌납했습니다. "
#define		_Bramanpoint_Contribytion2		18			//	"%s주신은 주신 포인트가 소멸될 때까지 승리시마다 150점의 주신포인트 보너스를 받습니다."	
#define		_Change_Trimuriti				19			//	"/공지 %s님이 %s주신을 선택했습니다."
//	GetEmptyMobGrid
#define		_Not_Find_Empty_Position		21			//	"생성지역에 너무많은 사용자들이 있습니다"
//	money move
#define		_Money_Move_Wrong_Place			22			//	"해당장소로 루피아를 이동할 수 없습니다"
#define		_Cant_Deposit_That_Much			23			//	"적립장소에 루피아를 더이상 적립할수가 없습니다"
#define		_Same_Place_Rupiah				24			//	"동일장소로 루피아를 이동할 수 없습니다"
//	move zone
#define		_Move_zone_Wait					25			//	"접속중입니다. 잠시만 기다려주십시요"
//	init_regen
#define		_Unknown_Connect_Type			26			//	"알수없는 접속요청입니다"
//	_MSG_TrimuritySelect
#define		_Trimurity_Select_Others		27			//	"타인이 종족은 변경할 수 없습니다"
#define		_Trimurity_Select_Guild			28			//	"길드원은 주신변경을 할수 없습니다"
#define		_Trimuriti_Select_Want_Money	29			//	"주신변경을 위한 루피아가 부족합니다"
#define		_Trimuriti_Select_Want_Resource 30			//	"주신변경을 위한 자원이 부족합니다"
//	_MSG_TrimurityPoint
#define		_Trimurity_Point_Not_Trimuriti	31			//	"주신이 없어 브라만포인트 올릴수가 없습니다"
#define		_Trimurity_Point_Too_High		32			//	"브라만포인트 100이상은 주신포인트를 올릴수가 없습니다"
#define		_Trimurity_Point_Want_Money		33			//	"브라만포인트 상승을 위한 루피아가 부족합니다"
#define		_Trimurity_Point_Want_Resource  34			//	"브라만포인트 상승을 위한 자원이 부족합니다"
//	_MSG_CLASS
#define		_Class_Get_Item_Fail			35			//	"인벤토리 공간이 부족하여 아이템 획득은 실패했습니다"
#define		_Class_Send						36			//	"현재 2차전직은 지원되지 않습니다"
//	_MSG_MobStore
#define		_MobStore_Set_Already			37			//	"이미 개인상점 오픈상태입니다"
#define		_MobStore_No_Mode				38			//	"상대가 개인상점을 오픈하지 않았습니다"
//	Party
#define		_Dropped_Current_Party_First	39			//	"상대방을 초대하기 위해선 먼저 현재의 파티를 탈퇴하십시요"
#define		_Have_Own_Party_Already			40			//	"상대방이 다른 파티에 가입되어 있습니다."
#define		_Not_Connected					41			//	"상대방이 플레이상태가 아닙니다"
#define		_Partys_Full					42			//	"파티인원이 풀입니다"

//	Guild
#define		_Guild_Name_Length				43			//	"길드이름은 5 ~ 18자 사이여야합니다"
#define		_Guild_Make_Trimuriti			44			//	"길드창설을 위해서는 먼저 주신을 선택해야 합니다"
#define		_Guild_Make_Already				45			//	"이미 가입되어 있는 길드가 있습니다"
#define		_Guild_Make_Want_Money			46			//	"길드생성을 위한 루피아가 부족합니다"
#define		_Guild_Not_Guild_Member			47			//	"길드멤버만 사용할 수 있는 기능입니다"
#define		_Guild_Have_No_Eject_Right		48			//	"길드멤버를 방출할 권한이 없습니다"
#define		_Guild_Have_No_EjectAll_Right	49			//	"모든 길드원을 방출할 권한이 없습니다"
#define		_Guild_Remove_Type_Error		50			//	"적절하지 않은 길드원 방출정보입니다"
#define		_Guild_Have_No_Invite_Right		51			//	"길드원 초청을 할 권한이 없습니다"
#define		_Guild_Not_Fine_Guild			52			//	"길드정보를 찾을수 없습니다"
#define		_Guild_Not_Fine_Requestor		53			//	"길드초청자를 찾을수 없습니다"
#define		_Guild_Update_No_Right			54			//	"길드정보를 변경할 권한이 없습니다"
#define		_Guild_Rank_No_Right			55			//	"길드 직위를 임명할 권한이 없습니다"
#define		_Guild_Rank_Full				56			//	"해당 직위에 임명된 사람이 이미 존재합니다"
#define		_Guild_Mark_No_Right			57			//	"길드마크를 변경할 권한이 없습니다"
#define		_Guild_Mark_Want_Money			58			//	"길드마크를 생성할 루피아가 부족합니다"
#define		_Guild_Add_Fail					59			//	"길드원추가에 실패했습니다"
#define		_Guild_Make_Name_Double			60			//	"동일이름의 길드가 존재합니다" 
//	Addressbook
#define		_Address_Member_Already			61			//	"이미 등록된 케릭터입니다"
#define		_Server_Close_Time				62			//	"서버 종료까지 %d초 남았습니다"
#define		_FAIL_NPC_DISTAN				63			//	"NPC와의 거리가 멉니다"
// RvR
#define		_Brahma							64			//  "브라흐마"
#define		_Vishnu							65			//  "비슈누"
#define     _Siva							66			//  "시바"
#define     _Destroy_Kala					67			//  "[공지]칼라현황> (%d,%d) 근처의 %s 칼라가 파괴되었습니다."
#define		_Drop_kala_Core					68			//  "[공지]칼라현황> %s에게 있던 %s 칼라코어가 (%d,%d) 근처에 떨어졌습니다."
#define		_Register_Kala_Core				69			//  "[공지]칼라현황> %s 주신인 %s이(/가) (%d,%d) 근처에 %s 칼라코어를 등록했습니다."
#define		_PickUp_Kala_Core				70			//	"[공지]칼라현황> %s 주신인 %s이(/가) (%d,%d)근처에서 %s 칼라코어를 주웠습니다."
#define		_Post_Kala_Status				71			//	"[공지]칼라현황> 브라흐마:%d, 비슈누:%d, 시바:%d"
#define		_Brahma_Collect_Four_Kala		72			//	"\n브라흐마 주신이 칼라를 4개 모았습니다. 하나만 더 모으면, 중립 NPC가 브라흐마 편이 됩니다.\n"
#define		_Vishnu_Collect_Four_Kala		73			//	"\n비슈누 주신이 칼라를 4개 모았습니다. 하나만 더 모으면, 중립 NPC가 비슈누 편이 됩니다.\n"
#define		_Siva_Collect_Four_Kala			74			//	"\n시바 주신이 칼라를 4개 모았습니다. 하나만 더 모으면, 중립 NPC가 시바 편이 됩니다.\n"
#define		_Brahma_Collect_Five_Kala		75			//	"\n브라흐마 주신이 칼라를 5개 모았습니다. 공격력 버프 NPC가 브라흐마 편으로 되었습니다.\n"
#define		_Vishnu_Collect_Five_Kala		76			//	"\n비슈누 주신이 칼라를 5개 모았습니다. 공격력 버프 NPC가 비슈누 편으로 되었습니다.\n"
#define		_Siva_Collect_Five_Kala			77			//	"\n시바 주신이 칼라를 5개 모았습니다. 공격력 버프 NPC가 시바 편으로 되었습니다.\n"
#define		_Post_Item_Location				78			//	"(%d,%d) 근처에서 신비한 아이템이 발견되었습니다."
#define		_Drop_Register_Kala_Core		79			//  "신전 근처에 %s 칼라코어가 떨어져서, 자동으로 자신의 주신 제단(%d,%d)으로 옮겨졌습니다."
#define		_PostThatCloseKingRoom			80			//  "조금 후에 이 방이 닫길 것이고 물론 나도 나의 세계로 돌아갈 것이다. 그때까지만 놀아주지"
#define     _NotEnoughGold                  85          //  "사무다바 %d레벨 사용을 위한 필요 루피아(%d)가 부족합니다."
#define     _BlessOfGod                     86          //  "%s님이 %s신의 축복을 받았습니다."
#define     _PickUpItem                     87          //  "%s님이 아이템을 주웠습니다."
#define     _SkillInitialized               88          //  "스킬이 초기화되었습니다."
#define     _SummonFailed                   89          //  "소환에 실패했습니다."
//	Billing 
#define		_Billing_Remain_Time			90			//	"유효계정시간이 %d초 남았습니다."
#define		_Billing_Remain_Expire			91			//	"유효계정시간이 만료되었습니다."
#define     _LackOfInventorySlot            101         //  "인벤토리 공간이 충분하지 않습니다."
#define     _KillOtherTrimuriti				102			//	"%s님이 %s님에게 승리하였습니다."
#define		_HeartRestricted				103			//   심장 차크라 제한에 걸렸습니다.
#define		_OpenTheGateIn10Minutes			104			//	"10분 뒤에 주신 던젼이 열립니다."
#define		_OpenTheGateIn5Minutes			105			//	"5분 뒤에 주신 던젼이 열립니다."
#define		_OpenTheGateIn2Minutes			106			//	"2분 뒤에 주신 던젼이 열립니다."
#define		_OpenTheGateIn1Minutes			107			//	"1분 뒤에 주신 던젼이 열립니다."
#define		_CloseTheGate					108			//	"주신 던젼 문이 닫겼습니다."
#define		_CloseThisZoneIn5Minutes		109			//	"5분 뒤에 주신 던젼이 닫깁니다."
#define		_CloseThisZoneIn2Minutes		110			//	"2분 뒤에 주신 던젼이 닫깁니다."
#define		_CloseThisZoneIn1Minutes		111			//	"1분 뒤에 주신 던젼이 닫깁니다."
#define		_OpenTheGate					112			//	"칼리아 던전의 문이 열렸습니다. 주신 성의 주신상을 클릭하세요."
#define		_PostNextTimeToOpenTheGate1		113			//	"칼리아 던전의 다음 오픈 시간은 23:00 입니다."
#define		_PostNextTimeToOpenTheGate2		114			//	"칼리아 던전의 다음 오픈 시간은 내일 17:00 입니다."
#define		_PostNextTimeToOpenTheGate3		115			//	"칼리아 던전의 다음 오픈 시간은 20:00 입니다."
#define		_NotifyDeath					116			//	"%에 의해 사망하였습니다."
#define		_CantAttackTargetInSealedZone	117			//  "결계지역 안으로 공격할 수 없습니다."
#define		_RestrictToUseaSummonScroll		118			//  "파미르지역에서만 사용할 수 있습니다."
#define		_StartToBattleIn10Minutes		119			//10분 후 두르가 지역의 요새 공격이 시작 됩니다.
#define		_StartToBattleIn5Minutes		120			//5분 후 두르가 지역의 요새 공격이 시작 됩니다.
#define		_StartToBattleIn1Minutes		121			//1분 후 두르가 지역의 요새 공격이 시작 됩니다.
#define		_StartToBattle					122			//두르가 지역의 요새 공격이 시작 되었습니다.
#define		_EndToBattleIn10Minutes			123			//두르가 지역의 요새 공격이 10분 후에 종료 됩니다.
#define		_EndToBattleIn5Minutes			124			//두르가 지역의 요새 공격이 5분 후에 종료 됩니다.
#define		_EndToBattleIn1Minutes			125			//두르가 지역의 요새 공격이 1분 후에 종료 됩니다.
#define		_EndToBattle					126			//두르가 지역의 요새 공격이 종료 되었습니다. 잠시 후 요새를 얻지 못한 플레이어들은 저장 지역으로 이동 됩니다.
#define		_NorthWesternStrongholdIsNotCaptured	127	//북서쪽 요새는 점령되지 않았습니다.
#define		_NorthEasternStrongholdIsNotCaptured	128	//북동쪽 요새는 점령되지 않았습니다.
#define		_SouthWesternStrongholdIsNotCaptured	129	//남서쪽 요새는 점령되지 않았습니다.
#define		_SouthEasternStrongholdIsNotCaptured	130	//남동쪽 요새는 점령되지 않았습니다.
#define		_NorthWesternStrongholdIsOccupied		131 //북서쪽 요새는 %s 아쉬람이 점령하고 있습니다.
#define		_NorthEasternStrongholdIsOccupied		132	//북동쪽 요새는 %s 아쉬람이 점령하고 있습니다.
#define		_SouthWesternStrongholdIsOccupied		133	//남서쪽 요새는 %s 아쉬람이 점령하고 있습니다.
#define		_SouthEasternStrongholdIsOccupied		134	//남동쪽 요새는 %s 아쉬람이 점령하고 있습니다.
#define		_1NorthWesternStronghold		135
#define		_1NorthEasternStronghold		136
#define		_1SouthWesternStronghold		137
#define		_1SouthEasternStronghold		138
#define		_2NorthWesternStronghold		139
#define		_2NorthEasternStronghold		140
#define		_2SouthWesternStronghold		141
#define		_2SouthEasternStronghold		142
#define		_StrongholdIsNotCaptured		143	//%s 요새는 점렴되지 않았습니다.
#define		_StrongholdIsOccupied			144 //%s 요새는 %s 아쉬람이 점렴하고 있습니다.
#define		_StartToBattleIn30Minutes			145
#define		_StartSurvivalEventIn10Minutes	146
#define		_StartSurvivalEventIn5Minutes	147
#define		_StartSurvivalEventIn1Minutes	148
#define		_StartSurvivalEvent				149
#define		_EndSurvivalEvent				150
#define		_WinTheSurvivalEvent			151
#define		_ArenaEntryIsFull				152
#define		_StartSurvivalEventIn30Minutes	153
#define		_LoseTheSurvivalEvent			154
#define		_PostTheSurvivals				155
#define		_PostThePrize					156
#define		_RestrictSummonItem				157
#define		_PostNextTimeToOpenTheGate14		158	//칼리아 던전의 다음 오픈 시간은 내일 14:00 입니다.
#define		_PostNextTimeToOpenTheGate16		159	//칼리아 던전의 다음 오픈 시간은 내일 16:00 입니다.
#define		_Announcement					160	//공지
#define		_CasteSkillIsReseted			161 // 주신 스킬이 초기화되었습니다.
#define		_WeakenTheGuardAtDruga			162 //	드루가 가드들을 지켜주던 축복의 힘이 사라졌습니다.
#define		_PostNextTimeToOpenTheGate12	163 //칼리아 던전의 다음 오픈 시간은 내일 12:00 입니다.
#define		_AddressBookFullMe				164 //	주소록 등록인원이 풀입니다
#define		_AddressBookFullYou				165 //	상대의 주소록 등록인원이 풀입니다
#define		_PostThatThe_mahi_StrongholdIsClosedIn1Minutes	166 //1분 후 마히드루가 던전이 종료될 예정입니다.
#define		_PostThatThe_ave_StrongholdIsClosedIn1Minutes	167 //1분 후 아브드루가 던전이 종료될 예정입니다.
#define		_PostThatThe_danva_StrongholdIsClosedIn1Minutes	168 //1분 후 단바드루가 던전이 종료될 예정입니다.
#define		_PostThatThe_nare_StrongholdIsClosedIn1Minutes	169 //1분 후 나르드루가 던전이 종료될 예정입니다.
#define		_SummonParty									170	//	%s님에 의해서 파티원들이 소환될 것입니다.
#define		_PostVictimForProceedingSurvival	171
#define		_KickedByGM							172		//	운영자에 의해서 강제종료됩니다.
#define		_YutBetBroadcast					173		//	윷놀이 베팅공지야~
#define		_YutNPCName							174		//	윷놀이꾼 사토
#define		_YutPlay1							175		//	윷놀이가 시작되었습니다. 
#define		_YutPlay2							176		//	지금 이 시간부터 모아치기 윷놀이 판을 한 바퀴 돌 때까지 윷가락이 던져집니다. 
#define		_YutPlay3							177		//	모두 윷놀이 판을 주목해 주세요.
#define		_YutPlayGo							178		//	윷나와라 뚝딱 모나와라 뚝딱 으라차!!
#define		_YutPlayDo							179		//	아싸 도가 나왔습니다. 모이치 한칸 전진!!
#define		_YutPlayGae							180		//	아싸 개가 나왔습니다. 모이치 두칸 전진!!
#define		_YutPlayGul							181		//	아싸 걸가 나왔습니다. 모이치 세칸 전진!!
#define		_YutPlayYut							182		//	아싸 윷가 나왔습니다. 모이치 네칸 전진!!
#define		_YutPlayMo							183		//	아싸 모가 나왔습니다. 모이치 다섯칸 전진!!
#define		_Yut_PlayEnd						184		//	윷놀이가 끝났습니다. 잠시동안 배당금을 계산하겠습니다.
#define		_YutTime20							185		//	20분 후 윷놀이가 시작됩니다. 윷놀이 시작 전까지 윷놀이 터의 사토에게 루피아를 적립할 수 있습니다.
#define		_YutTime10							186		//	10분 후 윷놀이가 시작됩니다. 윷놀이 시작 전까지 윷놀이 터의 사토에게 루피아를 적립할 수 있습니다.
#define		_YutTime5							187		//	5분 후 윷놀이가 시작됩니다. 윷놀이 시작 전까지 윷놀이 터의 사토에게 루피아를 적립할 수 있습니다.
#define		_YutTime1							188		//	1분 후 윷놀이가 시작됩니다. 윷놀이 시작 전까지 윷놀이 터의 사토에게 루피아를 적립할 수 있습니다.
#define		_YutPlay							189		//	윷놀이가 시작됩니다. 윷놀이가 끝날 때까지 루피아를 적립할 수 없습니다.
#define		_YutPlayResult						190		//	윷놀이 당첨 주춧돌은 %s입니다.
#define		_YutNetPlay							191		//	3분 후부터 윷놀이 터의 사토에게 루피아를 적립할 수 있습니다.
#define		_YutMoneyClear						192		//	윷놀이 게임이 종료되었습니다. 당첨금은 금일내로 수령하지 않으면 무효화 될 수 있으니 꼭 수령하시기 바람니다.
#define		_DisconnectedToServer				193		//  서버와의 연결이 끊겼습니다.
#define		_HaveNotEnoughGold					194		//  루피아가 부족합니다.
#define		_CompletedToApplySiege				195		//	%s 길드에 대한 공성전 참가 신청이 완료되었습니다.
#define		_AllyGuild							196		//  연합
#define		_YourGuildIsRegistered				197		//	공성전 참가 목록에 등록되어 있습니다.
#define		_YourGuildIsNotRegistered			198		//	공성전에 참가신청을 하지 않았습니다.
#define		_StartToSiegeIn30Minutes			199			//	"30분 뒤에 공성전이 시작됩니다.
#define		_StartToSiegeIn20Minutes			200			//	"20분 뒤에 공성전이 시작됩니다.
#define		_StartToSiegeIn10Minutes			201			//	"10분 뒤에 공성전이 시작됩니다. 재접속 해주십시오!
#define		_StartToSiegeIn5Minutes				202			//	"5분 뒤에 공성전이 시작됩니다.
#define		_StartToSiegeIn1Minutes				203			//	"1분 뒤에 공성전이 시작됩니다.
#define		_StartToSiege						204			//	"공성전이 시작되었습니다.
#define		_EndToSiegeIn30Minutes				205			//	"30분 뒤에 공성전이 종료됩니다.
#define		_EndToSiegeIn20Minutes				206			//	"20분 뒤에 공성전이 종료됩니다.
#define		_EndToSiegeIn10Minutes				207			//	"10분 뒤에 공성전이 종료됩니다.
#define		_EndToSiegeIn5Minutes				208			//	"5분 뒤에 공성전이 종료됩니다.
#define		_EndToSiegeIn1Minutes				209			//	"1분 뒤에 공성전이 종료됩니다.
#define		_EndToSiege							210			//	"공성전이 종료되었습니다.
#define		_PostTheResultOfTheSiege			211			//  <스코어> 수성:%d, 공성1:%d, 공성2:%d, 공성3:%d, 무소속:%d
#define		_PostTheWinnerOfTheSiege			212			//  %s 길드가 비류성 수성에 실패하여 %s 길드가 새로운 성주가 되었습니다.
#define		_PostSuccessToDefense				213			//  %s 길드가 비류성 수성에 성공하였습니다.
#define		_PostTheCastleIsFree				214			//  무소속이 승리하여 비류성은 성주가 없는 빈성이 되었습니다.
#define		_ExpireOfTheTermForSiegeNNotify		215			//  공성전 신청이 마감되었습니다.
#define		_ExpireOfTheTermForSiegeIn60Minutes	216			//	공성전 신청이 1시간 후에 마감됩니다. < 공성전 시작 1시간30분 전>
#define		_ExpireOfTheTermForSiegeIn30Minutes	217			//	공성전 신청이 30분 후에 마감됩니다. <공성전 시작 1시간 전>
#define		_PostTheStateOfCapturingTheSymbol1	218			// XX 공성 연합이 외성의 아디즈(1점)를 획득했습니다
#define		_PostTheStateOfCapturingTheSymbol2	219			// XX 공성 연합이 내성의 아디즈(2점)를 획득했습니다
#define		_PostTheStateOfCapturingTheSymbol3	220			// XX 공성 연합이 중앙성의 아디즈(3점)를 획득했습니다
#define		_PostTheDateForSiege1				221			// 금주의 공성전은 토요일 저녁 9시에 개최됩니다. 자세한 내용은 비류성의 관리인 야스다에게 문의해 주세요.
#define		_PostTheDateForSiege2				222			// 금주의 공성전은 토요일 저녁 10시에 개최됩니다. 자세한 내용은 비류성의 관리인 야스다에게 문의해 주세요.
#define		_PostTheDateForSiege3				223			// 금주의 공성전은 일요일 저녁 9시에 개최됩니다. 자세한 내용은 비류성의 관리인 야스다에게 문의해 주세요.
#define		_PostTheDateForSiege4				224			// 금주의 공성전은 일요일 저녁 10시에 개최됩니다. 자세한 내용은 비류성의 관리인 야스다에게 문의해 주세요.
#define		_PostTheDateForSiege5				225			// 금주의 공성전은 일요일 저녁 11시에 개최됩니다. 자세한 내용은 비류성의 관리인 야스다에게 문의해 주세요.
#define		_Post1stAllyForSiege				226			// %s 아쉬람이 첫 번째 공성 아쉬람으로 결정되었습니다. // 공성 신청시
#define		_Post2ndAllyForSiege				227			// %s 아쉬람이 두 번째 공성 아쉬람으로 결정되었습니다.
#define		_Post3rdAllyForSiege				228			// %s 아쉬람이 세 번째 공성 아쉬람으로 결정되었습니다.
#define		_Independent						229			// 무소속
#define		_ExpireOfTheTermForSiege			230			// 공성전 신청이 마감되었습니다.
#define		_HaveNotEnoughItem					231			// 아이템이 충분히 없습니다.
#define		_HaveNotEnoughMember				232			// 60레벨 이상의 길드원이 최소 20명이 필요합니다.
#define		_NotDefenseGuildMaster				233			// 수성 아쉬람의 길드장이 아닙니다.
#define		_NotGuildMaster						234			// 길드장이 아닙니다.
#define		_NoClanLeader						235			// 공성 연맹장이 없는 상태입니다.
#define		_DefenderName						236			// 수성
#define		_RestrictToUseaItemAt12				237			//  "북두성군에서만 사용할 수 있습니다."
#define		_RestrictToUseaItemAt17				238			//  "비류성에서만 사용할 수 있습니다."
#define		_SuccessToRefine					239			// %s님이(가) 12 제련에 성공하였습니다.
#define		_BeginExpFestival					240			// 지금부터 1시간 동안 만다라 마을에 경험치(50% 보너스) 축제가 시작됩니다.
#define		_LetsJoinExpFestival				241			// 만다라 마을에 경험치(50% 보너스) 축제가 진행중입니다.
#define		_EndExpFestival						242			// 만다라 마을에 경험치(50% 보너스) 축제가 종료되었습니다.
#define		_TheMonsterInvadeTheShambala		243			// 샴발라 지역에 아난가 침공이 시작되었습니다.
#define		_TheMonsterRetreatAtTheShambala		244			// 샴발라 지역에 아난가 침공이 종료되었습니다.
#define		_NotByruCastleMaster				245			// 비류성 성주가 아닙니다.
#define		_NotCertifiedItem					246			//	유료아이템의 인증이 아직 끝나지 않았습니다.
#define		_HaveNotRightsToReleaseAhndakara	247			// 안다카라의 봉인을 해제할 권한이 없습니다.
#define		_IsNotTheOwnerOfTheStronghold		248			// 요새의 주인이 아닙니다.
#define		_HaveNotRights						249			// 권한이 없습니다.
#define		_InvalidQuizAnswerClose				250			// 퀴즈에 대한 응답이 틀려서 접속을 종료합니다.
#define		_InvalidQuizAnswerClose1			251			// 퀴즈에 대한 응답이 틀려서 접속을 종료합니다.
#define		_InvalidQuizAnswerClose2			252			// 퀴즈에 대한 응답이 틀려서 접속을 종료합니다.
#define		_InvenMoneyFull						253			// 루피아의 소지한도를 초과하였습니다.
#define		_QuestInst_Casted					254			// 퀘스트 초기화를 진행할수 있습니다.
#define		_QuestInst_NotCasted				255			// 퀘스트 초기화는 %d시간 %d분후 사용가능합니다.
#define		_BarunaWillBeStartedIn10Minutes		256			// 10분 후 무다던전에서 바루나 기사단의 칼리방 입장이 시작됩니다.
#define		_BarunaWillBeStartedIn5Minutes		257			// 5분 후 무다던전에서 바루나 기사단의 칼리방 입장이 시작됩니다.
#define		_BarunaWillBeStartedIn1Minutes		258			// 1분 후 무다던전에서 바루나 기사단의 칼리방 입장이 시작됩니다.
#define		_BarunaIsOpend						259			// 무다던전에서 바루나 기사단의 칼리방 입장이 시작되었습니다.
#define		_BarunaWillBeClosedIn5Minutes		260			// 5분후 칼리방이 닫히고, 바루나 기사단은 대기실로 이동됩니다.
#define		_BarunaWillBeClosedIn1Minutes		261			// 1분 후 칼리방이 닫히고, 바루나 기사단은 대기실로 이동됩니다.
#define		_BarunaIsClosed						262			// 칼리방이 닫혔습니다. 다음 기회를 이용해 주시기 바랍니다.
#define		_BattleRestartedAtNorthWesternStronghold	263 // 마히드루가 요새 공방전이 다시 시작되었습니다.
#define		_BattleRestartedAtNorthEasternStronghold	264 // 아브드루가 요새 공방전이 다시 시작되었습니다.
#define		_BattleRestartedAtSouthWesternStronghold	265 // 단바드루가 요새 공방전이 다시 시작되었습니다.
#define		_BattleRestartedAtSouthEasternStronghold	266 // 나르드루가 요새 공방전이 다시 시작되었습니다.	
#define		_BarunaGateWasClosed				267			//바루나 기사단의 칼리방 입장이 종료되었습니다
#define		_CantRecoverTP						268			//TP회복을 할 수 없는 상태입니다.
#define		_CantUseAnyPustica					269			//이동 주문서를 사용할 수 없는 상태입니다.
#define		_QuestCastingTimeAlarm1				270			//	선행퀘스트를 %d년 %d월 %d일 %d시 %d분에 완료하였습니다. 
#define		_QuestCastingTimeAlarm2				271			//	현재의 퀘스트는 %d년 %d월 %d일 %d시 %d분이후에 진행이 가능합니다.
/*
수성 아쉬람 연맹(아쉬람 이름으로 표현, 수틀려 수성 연맹) x점 획득
공성 아쉬람1 연맹(아쉬람 명으로 표현, 속쓰려 공성 연맹) x점 획득
공성 아쉬람2 연맹 x점 획득
공성 아쉬람3 연맹 x점 획득
무소속 연합 x점 획득
Xx 아쉬람 연맹이 비류성 공성전의 승자입니다.(무소속 연합이 비류성 공성전의 승자입니다. 다음주 토요일 밤 10시에 비류성을 차지하기 위한 공성전이 시작됩니다)
*/
