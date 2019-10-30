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
//	Billing 
#define		_Billing_Remain_Time			90			//	"유효계정시간이 %d초 남았습니다."
#define		_Billing_Remain_Expire			91			//	"유효계정시간이 만료되었습니다."
/*
#define   _NN_Get_Skill_Point				1
#define   _NN_Weapon_Enchanted				2
#define   _NN_Get_Watching_Town_Mission		3
#define   _NN_Watching_Town_Success			4
#define   _NN_Watching_Town_Awarded			5
#define   _NN_Qest06Complete				6
#define   _NN_Qest07Complete				7
#define   _NN_Qest08Complete				8
#define   _NN_Qest09Complete				9
#define   _NN_Qest10Complete				10
#define   _NN_Qest11Complete				11
#define   _NN_Qest12Complete				12
#define   _NN_Qest13Complete				13
#define   _NN_Qest14Complete				14
#define   _NN_Qest15Complete				15
#define   _NN_Qest16Complete				16
#define   _NN_ServerRebootAfter_1minute		17
#define   _NN_Rerun_Game_For_Auto_Patch		18
#define   _NN_ServerReboot_After_30Sec		19
#define   _NN_ServerReboot_Takes_10min		20
#define   _NN_ServerReboot_After_10Sec		21
#define   _NN_ServerReboot_Now				22
#define   _NN_Bad_Network_Packets			23
#define   _NN_Only_Guild_Master_can			24
#define   _NN_Champions_Cant_Challange		25
#define   _NN_Last_Challange_Cant			26
#define   _NN_Allready_Challanged			27
#define   _NN_Cant_Get_More_Challanger		28
#define   _NN_Need_Sign_Of_Challanger		29
#define   _NN_Challanged					30
#define   _NN_Cant_Create_More_Summons		31
#define   _NN_1_Kind_Summon_in_1_Party		32
#define   _NN_Party_Full_Cant_Summon		33
#define   _NN_SelectCharacter				34
#define   _NN_ServerReboot_Cant_Connect		35
#define   _NN_Version_Not_Match_Rerun		36
#define   _NN_3_Tims_Wrong_Pass				37
#define   _NN_Wait_Checking_Billing			38
#define   _DN_Not_Allowed_Account			39
#define   _NN_Using_Other_Server_Group		40
#define   _NN_Wait_Checking_Billing_t		41
#define   _NN_Not_Allowed_Account_t			42
#define   _NN_Using_Other_Server_Group_t	43
#define   _NN_Cant_Deposit_That_Much		44
#define   _NN_Cant_Withdraw_That_Much		45
#define   _NN_Newbie_zone					46
#define   _NN_Only_Guild_Members			47
#define   _NN_Cant_Summon_Dead_Person		48
#define   _NN_Summon_Not_Allowed_Here		49
#define   _NN_Too_High_Level_To_Summon		50
//	ITEM MOVE
#define   _NN_Same_Place_Rupiah				51
#define   _SN_Summoned_By_S					52
#define   _NN_Level_Up						53
#define   _NN_3_Quarters_Bonus				54
#define   _NN_2_Quarters_Bonus				55
#define   _NN_1_Quarters_Bonus				56
#define   _SS_Champion_And_Challanger		57
#define   _SN_No_Challanger					58
#define   _SN_Winner_Is						59
#define   _NN_Teleport_Gate_Requir			60
#define   _SN_I_Wwill_Enchant_Your_Weapon	61
#define   _NN_Gather_7_Clistals				62
#define   _NN_Equip_Weapon_To_Enchant		63
#define   _NN_Only_Nomal_Weapons			64
#define   _SN_Now_I_Will_Enchant_Your		65
#define   _SN_All_Villagers_Thanks_Your		66
#define   _NN_Give_You_Some_Reward			67
#define   _NN_Guard_This_Village			68
#define   _NN_Monster_Attaking_Us_Help		69
#define   _NN_Thanks_for_Helping_us			70
#define   _NN_Youve_Done_It_Already			71
#define   _NN_Cant_Drop_Here				72
#define   _NN_Guild_Medal_Cant_Be_Droped	73
#define   _NN_Only_To_Equips				74
#define   _NN_Cant_Refine_More				75
#define   _NN_Fail_To_Refine				76
#define   _NN_Fail_To_Level_Up				77
#define   _NN_No_Return_Point				78
#define   _NN_No_Key						79
#define   _NN_Wrong_Trade_Packet1			80
#define   _NN_Only_With_Guild_Master		81
#define   _NN_Already_Trading				82
#define   _NN_Havent_Money_So_Much			83
#define   _NN_Opponent_Havent_Money			84
#define   _NN_Each_Of_You_Havent_Space		85
#define   _NN_You_Have_No_Space_To_Trade	86
#define   _NN_Opponent_Have_No_Space_To		87
#define   _NN_Wrong_Trade_Packet2			88
#define   _NN_Summon						89
#define   _NN_Cant_Use_Killed				90
#define   _NN_Not_Connected					91
#define   _NN_Cant_Use_To_Yourself			92
#define   _NN_Cant_Use_To_Killed			93
#define   _NN_Only_To_Party_Or_Guild		94
#define   _NN_Didnt_Learn_Summon_Skill		95
#define   _NN_Cant_Use_That_Here			96
#define   _NN_Too_High_Level				97
#define   _SN_Summoned_By_S_                98
#define   _NN_Relocate						99
#define   _SN_S_Relocate_To_You				100
#define   _NN_Reply							101
#define   _NN_No_One_To_Reply				102
#define   _SN_S_is_Connected				103
#define   _NN_Only_Guild_Member_Can			104
#define   _NN_Maximum_Point_Now				105
#define   _NN_Maximum_Point_200_Now			106
#define   _NN_Cant_Learn_Other_Class_Skill  107
#define   _NN_Not_Enough_Skill_Point		108
#define   _NN_Already_Learned_It			109
#define   _NN_Need_More_Level_To_Learn		110
#define   _NN_Need_More_Mastery_To_Learn	111
#define   _NN_Only_Merchant_Sells			112
#define   _NN_Not_Enough_Money				113
#define   _NN_Only_Guild_Master_Can_Buy_It	114
#define   _NN_He_Is_Not_Merchant			115
#define   _NN_Only_Merchant_Buy_Yours		116
#define   _NN_Dropped_Current_Party_First	117
#define   _NN_Not_Connected_				118 
#define   _NN_Other_Partys_Member			119
#define   _NN_Have_Own_Party_Already		120
#define   _NN_Dropped_Current_Party_First_	121
#define   _NN_Partys_Full					122
#define   _DN_Billing_Code					123
#define   _DN_Billing_Notice1				124
#define   _DD_Billing_Notice2				125
#define   _NN_Billing_Notice3				126
#define   _NN_Billing_Notice4				127
#define   _NN_Billing_Notice5				128
#define   _NN_Billing_Notice6				129
#define   _NN_Try_Reconnect					130
#define   _NN_No_Account_With_That_Name		131
#define   _NN_Blocked_Account				132
#define   _NN_Wrong_Password				133
#define   _NN_Your_Account_From_Others		134
#define   _NN_Guild_Battle_Notice1			135
#define   _NN_Guild_Battle_Notice2			136
#define   _NN_Guild_Battle_Notice3			137
#define   _NN_Guild_Battle_Notice4			138
#define   _NN_Guild_Battle_Notice5			139
#define   _NN_Guild_Battle_Notice6			140
#define   _NN_Below_lv20_No_Exp_Loss		141
#define   _DN_lose_D_exp					142
#define   _NN_In_Arena_No_Exp_Loss			143
#define   _NN_Only_Guild_Master_Can			144
#define   _NN_Disqualified_By_Guild_Master	145
#define   _NN_Disqualify					146
#define   _NN_Haven_Guild_Medal				147
#define   _NN_Deprivate						148
#define   _NN_CarryFull	                    149
#define   _NN_Equip_Particle                150
#define   _NN_Purify_Particle               151
#define   _NN_Need_1000000_Gold             152
#define	  _NN_Hurry_Helping_them            153
#define   _NN_Party_Only                    154 
#define   _NN_Need_Pure_Divine              155
#define   _NN_Initialize_Skill              156
#define   _NN_Need_10_Particle              157
#define   _NN_Processing_Complete           158
#define   _DD_Billing_Notice7               159
#define   _DN_Billing_Notice8               160
#define   _NN_Disabled_Account              161
#define   _NN_No_Guild_Members	            162
#define   _SN_Zakum_Killed                  163
#define   _NN_Zakum_Initialize              164
#define   _NN_Deny_Whisper                  165 
#define   _NN_Need_5000000_Gold             166
#define   _NN_Cant_Sell_Potion              167
#define   _NN_Guild_Tax_0_to_30             168 
#define   _DD_Set_Guild_Tax                 169
#define   _NN_CantWhenAutoTrade             170
#define   _NN_ItemSold                      171 
#define   _NN_OnlyVillage                   172
#define   _NN_Only_Named_Guild				173
#define   _NN_Only_Once_Per_Day	            174
#define   _SSD_S_get_S_D					175
#define	  _NN_Refine_Success				176
#define	  _DN_Need_D_Sapphire               177
#define   _NN_My_King_Bless1                178
#define   _NN_My_King_Bless2                179
#define	  _NN_Need_Level					180 
#define	  _NN_King1_Killed					181
#define	  _NN_King2_Killed					182
#define	  _DN_get_D_exp                     183
#define   _NN_Kingdom	                    184
#define   _NN_King                          185
#define   _NN_Set_Warp                      186
#define   _DS_S_Challanged                  187
#define	  _NN_Need_Master	                188
#define   _DN_Need_D_Sapphire2	            189
#define   _NN_Need_Guild_Medal	            190
#define	  _NN_Reconnect                     191 
#define	  _NN_Need_1000000_For_Challange    192
#define	  _NN_Battle_In_Progress			193
#define	  _NN_Battle_Started			    194
#define   _SS_S_Killed_By_S                 195
#define   _SS_S_WinBy_S                     196
#define   _SS_S_S_Draw                      197
#define   _SSD_S_get_S						198
#define	  _NN_Leaving_kingdom               199
#define	  _NN_Next_Chance					200
#define	  _NN_Congratulations               201
#define   _NN_Stat_Initialized              202
#define   _DN_Want_Stat_Init	            203
#define	  _DN_D_Costs                       204
#define   _NN_Cant_with_armor               205
#define   _NN_Child_Pay                     206
#define	  _DD_PKPointPlus                   207 
#define	  _DD_PKPointMinus                  208
#define	  _DN_CantKillUser					209
#define   _SS_War_Declared					210
#define   _SS_War_Started					211
#define   _SS_War_Canceled					212
#define   _NN_War_Stop						213
#define   _NN_Cant_Declare_War              214 
#define   _NN_Party_Level_Limit             215  
#define	  _NN_Summon_Guild					216
#define	  _NN_Only_Village					217
#define   _SN_Your_are_at_war	            218
#define   _SN_War_to_S                      219
#define   _SN_War_from_S                    220
#define   _SS_War_declare_canceled          221 
#define   _SD_Zakum_Quest_by_S_N            222
#define	  _NN_Zakum_Quest_empty				223
#define	  _NN_Only_Level1_Armor	            224
#define   _NN_Only_Level2_Armor	            225
#define   _NN_Only_Level3_Armor	            226 
#define   _NN_Only_Level4_Armor				227
#define   _NN_Only_By_Water_Scroll          228
#define   _NN_Party_Leader_Only             229
#define   _NN_NewbieQuest_Already1			230
#define   _NN_NewbieQuest_Cheerup1			231
#define   _NN_NewbieQuest_Complete1			232
#define   _NN_NewbieQuest_Reward1			233
#define   _NN_NewbieQuest_Already2			234
#define	  _NN_NewbieQuest_Cheerup2			235
#define	  _NN_NewbieQuest_Complete2			236
#define   _NN_NewbieQuest_Reward2			237
#define   _NN_NewbieQuest_Already3			238
#define   _NN_NewbieQuest_Cheerup3			239
#define   _NN_NewbieQuest_Complete3			240
#define   _NN_NewbieQuest_Reward3			241
#define   _NN_NewbieQuest_Already4			242
#define   _NN_NewbieQuest_Cheerup4			243
#define	  _NN_NewbieQuest_Complete4			244
#define   _NN_NewbieQuest_Reward4			245
#define   _NN_BR_Start1						246
#define   _NN_BR_Start2						247 
#define   _NN_BR_Start3                     248
#define   _NN_BR_Rewarded					249
#define   _NN_BR_Ready1                     250
#define   _NN_BR_Ready2	                    251      
#define   _NN_BR_Ready3	                    252   
#define   _NN_INCUBATED                     253 
#define	  _NN_Cant_Upgrade_More				254 
#define	  _NN_Mount_Growth					255
#define   _NN_Mount_Not_Match               256
#define	  _NN_Cure_animals					257
#define   _DS_S_cure_price_D				258
#define   _NN_Cured							259
#define   _NN_Cure_failed					260
#define   _NN_Incu_Wait_More				261
#define   _NN_Incu_Proceed					262
#define   _NN_Mount_Level                   263
#define   _NN_Mount_died					264  
#define	  _NN_3rd_village_limit				265
#define	  _NN_Only_Sunday					266 
#define	  _NN_Treasure_Map					267
#define	  _NN_TicketUsed                    268  
#define	  _NN_CombineFailed					269
#define	  _SS_CombineSucceed				270
#define	  _NN_Wrong_Combination             271
#define	  _NN_Item_Arrived					272
#define	  _NN_Cant_get_more_than_2G			273
*/