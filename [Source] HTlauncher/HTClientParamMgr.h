#ifndef _HTClientParamMgr_H_
#define _HTClientParamMgr_H_

#define HT_NAME_MAX 50
#define HT_DESCRIPT_MAX 50

#define HT_CLI_PARAMTYPE_NONE				0

// 몬스터 ID 영역
#define HT_PARAMTYPE_MONSTER				1
#define HT_PARAMTYPE_MONSTER_START			2001
#define HT_PARAMTYPE_MONSTER_END			2999

//// 몬스터 스킬의 ID 영역
//#define HT_PARAMTYPE_MONSTERSKILL			2
//#define HT_PARAMTYPE_MONSTERSKILL_START		3501
//#define HT_PARAMTYPE_MONSTERSKILL_END		3999
// 몬스터 스킬의 ID 영역
#define HT_PARAMTYPE_MONSTERSKILL			2
#define HT_PARAMTYPE_MONSTERSKILL_START		41001
#define HT_PARAMTYPE_MONSTERSKILL_END		43999

// 캐릭터 스킬의 ID 영역
#define HT_PARAMTYPE_PCSKILL				3
#define HT_PARAMTYPE_PCSKILL_START			3001
#define HT_PARAMTYPE_PCSKILL_END			3499

// 아이템의 ID 영역
#define HT_PARAMTYPE_ITEM					4
#define HT_PARAMTYPE_ITEM_START				4001
#define HT_PARAMTYPE_ITEM_END				9989

// NPC ID 영역
#define HT_PARAMTYPE_NPC					5
#define HT_PARAMTYPE_NPC_START				1001
#define HT_PARAMTYPE_NPC_END				1999
#define HT_NPC_SELLING_ITEM_MAX				49

// Portal
#define HT_PARAMTYPE_PORTAL					6
#define HT_PARAMTYPE_PORTAL_START			101
#define HT_PARAMTYPE_PORTAL_END				1000

// TaskQuest
#define HT_PARAMTYPE_TASKQUEST				7
#define HT_PARAMTYPE_TASKQUEST_START		10001
#define HT_PARAMTYPE_TASKQUEST_END			15000

// AreaIndicate
#define HT_PARAMTYPE_AREAINDICATE			8
#define HT_PARAMTYPE_AREAINDICATE_START		20001
#define HT_PARAMTYPE_AREAINDICATE_END		25000

#define HT_CLI_PARAMTYPE_END				9

// 스킬 중 나가/킨나라
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_START				3001
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_END				3100

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_START			3001
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_1ST_END			3020

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_START			3021
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_2ND_END			3040

#define HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_START			3041
#define HT_PARAMTYPE_PCSKILL_NAGAKIN_3RD_END			3060

// 스킬 중 아수라/락샤사
#define HT_PARAMTYPE_PCSKILL_ASURARAK_START				3101
#define HT_PARAMTYPE_PCSKILL_ASURARAK_END				3200

#define HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_START			3101
#define HT_PARAMTYPE_PCSKILL_ASURARAK_1ST_END			3120

#define HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_START			3121
#define HT_PARAMTYPE_PCSKILL_ASURARAK_2ND_END			3140

#define HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_START			3141
#define HT_PARAMTYPE_PCSKILL_ASURARAK_3RD_END			3160

// 스킬 중 야크샤/간다르바
#define HT_PARAMTYPE_PCSKILL_YAKGAN_START				3201
#define HT_PARAMTYPE_PCSKILL_YAKGAN_END					3300

#define HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_START			3201
#define HT_PARAMTYPE_PCSKILL_YAKGAN_1ST_END				3220

#define HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_START			3221
#define HT_PARAMTYPE_PCSKILL_YAKGAN_2ND_END				3240

#define HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_START			3241
#define HT_PARAMTYPE_PCSKILL_YAKGAN_3RD_END				3260

// 스킬 중 데바/가루다
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_START				3301
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_END				3400

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_START			3301
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_1ST_END			3320

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_START			3321
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_2ND_END			3340

#define HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_START			3341
#define HT_PARAMTYPE_PCSKILL_DEVAGARU_3RD_END			3360

// 아이템 중 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_START							4001
#define HT_PARAMTYPE_ITEM_WEAPON_END							5000

// 아이템 중 한손 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_START					4001
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_END					4300

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_START			4001
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_END				4140

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_NOTMAGIC_START	4001
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_NOTMAGIC_END	4110

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_START		4111
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_NORMAL_MAGIC_END		4140

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_START				4141
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_END				4280

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_NOTMAGIC_START	4141
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_NOTMAGIC_END		4250

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_START		4251
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_RARE_MAGIC_END			4280

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_START			4281
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_END				4290

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_NOTMAGIC_START	4281
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_NOTMAGIC_END	4288

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_START		4289
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_UNIQUE_MAGIC_END		4290

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_START			4291
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_END				4300

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_NOTMAGIC_START	4291
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_NOTMAGIC_END		4298

#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_START		4299
#define HT_PARAMTYPE_ITEM_WEAPON_ONEHAND_QUEST_MAGIC_END		4300

// 아이템 중 양손 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_START					4301
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_END					4600

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_START			4301
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_END				4440

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_NOTMAGIC_START	4301
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_NOTMAGIC_END	4410

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_START		4411
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_NORMAL_MAGIC_END		4440

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_START				4441
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_END				4580

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_NOTMAGIC_START	4441
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_NOTMAGIC_END		4550

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_START		4551
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_RARE_MAGIC_END			4580

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_START			4581
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_END				4590

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_NOTMAGIC_START	4581
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_NOTMAGIC_END	4588

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_START		4589
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_UNIQUE_MAGIC_END		4590

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_START			4591
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_END				4600

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_NOTMAGIC_START	4591
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_NOTMAGIC_END		4598

#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_START		4599
#define HT_PARAMTYPE_ITEM_WEAPON_TWOHAND_QUEST_MAGIC_END		4600

// 아이템 중 투척 무기의 ID 영역
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_START					4601
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_END						4700

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_START				4601
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_END				4645

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_NOTMAGIC_START	4601
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_NOTMAGIC_END		4645

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_START		4646
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_NORMAL_MAGIC_END			4690

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_START				4646
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_END					4690

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_NOTMAGIC_START		4646
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_NOTMAGIC_END		4690

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_START			4696
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_RARE_MAGIC_END			4660

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_START				4691
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_END				4695

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_NOTMAGIC_START	4691
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_NOTMAGIC_END		4695

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_START		4664
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_UNIQUE_MAGIC_END			4665

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_START				4696
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_END				4700

#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_NOTMAGIC_START		4696
#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_NOTMAGIC_END		4700

//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_START		4669
//#define HT_PARAMTYPE_ITEM_WEAPON_THROW_QUEST_MAGIC_END			4670

// 방어구
#define HT_PARAMTYPE_ITEM_DEFENCE_START							5001
#define HT_PARAMTYPE_ITEM_DEFENCE_END							6000

// 방어구 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_START						8201
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_END						8765

// 갑옷
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_START					5001
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_END						5150

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_NORMAL_START			5001
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_NORMAL_END				5070

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_START				5071
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_RARE_END				5140

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_START			5141
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_UNIQUE_END				5145

#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_START				5146
#define HT_PARAMTYPE_ITEM_DEFENCE_ARMOR_QUEST_END				5150

// 갑옷 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_START				8606
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_END					8675

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_NORMAL_START			8606
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_NORMAL_END			8640

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_START			8641
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_RARE_END				8670

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_START			8671
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_ARMOR_UNIQUE_END			8675

// 바지
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_START					5151
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_END						5250

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_NORMAL_START			5151
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_NORMAL_END				5195

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_START				5196
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_RARE_END				5240

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_START			5241
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_UNIQUE_END				5245

#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_START				5246
#define HT_PARAMTYPE_ITEM_DEFENCE_PANTS_QUEST_END				5250

// 바지 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_START				8201
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_END					8305

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_NORMAL_START			8201
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_NORMAL_END			8250

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_START			8251
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_RARE_END				8300

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_START			8301
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_PANTS_UNIQUE_END			8305

// 투구
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_START					5251
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_END					5400

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_NORMAL_START			5251
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_NORMAL_END				5320

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_START				5321
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_RARE_END				5390

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_START			5391
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_UNIQUE_END				5395

#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_START			5396
#define HT_PARAMTYPE_ITEM_DEFENCE_HELMET_QUEST_END				5400

// 투구 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_START				8306
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_END					8405

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_NORMAL_START		8306
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_NORMAL_END			8350

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_START			8351
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_RARE_END			8400

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_START		8401
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_HELMET_UNIQUE_END			8405

// 장갑
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_START					5401
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_END					5500

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_NORMAL_START			5401
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_NORMAL_END				5445

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_START				5446
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_RARE_END				5490

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_START			5491
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_UNIQUE_END				5495

#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_START			5496
#define HT_PARAMTYPE_ITEM_DEFENCE_GLOVES_QUEST_END				5500

// 장갑 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_START				8441
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_END					8525

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_NORMAL_START		8441
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_NORMAL_END			8480

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_START			8481
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_RARE_END			8520

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_UNIQUE_START		8521
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_GLOVES_UNIQUE_END			8525

// 허리띠
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_START					5501
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_END						5600

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_NORMAL_START				5501
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_NORMAL_END				5545

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_START				5546
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_RARE_END					5590

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_START				5591
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_UNIQUE_END				5595

#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_START				5596
#define HT_PARAMTYPE_ITEM_DEFENCE_BELT_QUEST_END				5600

// 신발
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_START					5601
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_END						5700

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_NORMAL_START			5601
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_NORMAL_END				5645

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_START				5646
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_RARE_END				5690

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_START			5691
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_UNIQUE_END				5695

#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_START				5696
#define HT_PARAMTYPE_ITEM_DEFENCE_SHOES_QUEST_END				5700

// 신발 추가
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_START				8526
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_END					8605

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_NORMAL_START			8526
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_NORMAL_END			8570

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_START			8571
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_RARE_END				8600

#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_START			8601
#define HT_PARAMTYPE_ITEM_ADDDEFENCE_SHOES_UNIQUE_END			8605

// 방패
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_START					5701
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_END					5800

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_NORMAL_START			5701
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_NORMAL_END				5745

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_START				5746
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_RARE_END				5790

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_START			5791
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_UNIQUE_END				5795

#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_START			5796
#define HT_PARAMTYPE_ITEM_DEFENCE_SHIELD_QUEST_END				5800

// 부적
#define HT_PARAMTYPE_ITEM_CHARM_START							5801
#define HT_PARAMTYPE_ITEM_CHARM_END								5850

// 악세사리
#define HT_PARAMTYPE_ITEM_ACCESSORY_START						6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_END							6500

// 귀걸이
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_START				6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_END					6100

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_NORMAL_START		6001
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_NORMAL_END			6045

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_START			6046
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_RARE_END			6090

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_START		6091
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_UNIQUE_END			6095

#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_START			6096
#define HT_PARAMTYPE_ITEM_ACCESSORY_EARRING_QUEST_END			6100

// 팔찌
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_START				6101
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_END				6200

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_NORMAL_START		6101
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_NORMAL_END			6145

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_START			6146
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_RARE_END			6190

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_START		6191
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_UNIQUE_END			6195

#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_START		6196
#define HT_PARAMTYPE_ITEM_ACCESSORY_BRACELET_QUEST_END			6200

// 목걸이
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_START				6201
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_END				6300

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_NORMAL_START		6201
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_NORMAL_END			6245

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_START			6246
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_RARE_END			6290

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_START		6291
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_UNIQUE_END			6295

#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_START		6296
#define HT_PARAMTYPE_ITEM_ACCESSORY_NECKLACE_QUEST_END			6300

// 인벤확장
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_START			6301
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_END				6310

#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_NORMAL_START	6301
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_NORMAL_END		6308

#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_START		6309
#define HT_PARAMTYPE_ITEM_ACCESSORY_EXPANDINVEN_QUEST_END		6310

// 반지
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_START					6401
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_END					6500

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_NORMAL_START			6401
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_NORMAL_END				6445

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_START				6446
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_RARE_END				6490

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_START			6491
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_UNIQUE_END				6495

#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_START			6496
#define HT_PARAMTYPE_ITEM_ACCESSORY_RING_QUEST_END				6500

// 제련 재료
#define HT_PARAMTYPE_ITEM_REFINE_START							6501
#define HT_PARAMTYPE_ITEM_REFINE_END							6700

// 메인제련
#define HT_PARAMTYPE_ITEM_REFINE_MAIN_START						6501
#define HT_PARAMTYPE_ITEM_REFINE_MAIN_END						6550

// 첨가 제련재료2
#define HT_PARAMTYPE_ITEM_REFINE_SUB3_START						6526
#define HT_PARAMTYPE_ITEM_REFINE_SUB3_END						6550

// 첨가 제련재료
#define HT_PARAMTYPE_ITEM_REFINE_SUB2_START						6551
#define HT_PARAMTYPE_ITEM_REFINE_SUB2_END						6600

// 보조제련
#define HT_PARAMTYPE_ITEM_REFINE_SUB_START						6601
#define HT_PARAMTYPE_ITEM_REFINE_SUB_END						6700

// 유료화 아이템-지속아이템
#define HT_PARAMTYPE_ITEM_CHARGE_START							6801
#define HT_PARAMTYPE_ITEM_CHARGE_END							7000

#define HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_START				6801
#define HT_PARAMTYPE_ITEM_CHARGE_CONTINUANCE_END				6950

#define HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_START					6951
#define HT_PARAMTYPE_ITEM_CHARGE_FUNCTION_END					7000

// 유료화 아이템 중 소모성 아이템
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE_START					7031
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE_END						7070

#define HT_PARAMTYPE_ITEM_CHARGE_USABLE2_START					6719
#define HT_PARAMTYPE_ITEM_CHARGE_USABLE2_END 					6722

// 소비 아이템 (1)
#define HT_PARAMTYPE_ITEM_USABLE_START							7001
#define HT_PARAMTYPE_ITEM_USABLE_END							7100

// 소비 아이템 (2)
#define HT_PARAMTYPE_ITEM_USABLE2_START							6701
#define HT_PARAMTYPE_ITEM_USABLE2_END							6800

// 루피아
#define HT_PARAMTYPE_ITEM_USABLE_MONEY_START					7081
#define HT_PARAMTYPE_ITEM_USABLE_MONEY_END						7090

// 화살
#define HT_PARAMTYPE_ITEM_USABLE_ARROW_START					7091
#define HT_PARAMTYPE_ITEM_USABLE_ARROW_END						7100

// 수집 아이템
#define HT_PARAMTYPE_ITEM_COLLECT_START							7101
#define HT_PARAMTYPE_ITEM_COLLECT_END							8000

// 퀘스트 전용 아이템
#define HT_PARAMTYPE_ITEM_QUESTONLY_START						8001
#define HT_PARAMTYPE_ITEM_QUESTONLY_END							8200

#define HT_PCSKILL_MAXLEVEL			11

class CHTParamIDCheck
{
public:
	static bool		HT_bIsMonster( const int id );
	static bool		HT_bIsMonsterSkill( const int id );
	static bool		HT_bIsPCSkill( const int id );
	static bool		HT_bIsItem( const int id );

	static bool		HT_bIsPCSkillNagaKin( const int id );
	static bool		HT_bIsPCSkillNagaKin1st( const int id );
	static bool		HT_bIsPCSkillNagaKin2nd( const int id );
	static bool		HT_bIsPCSkillNagaKin3rd( const int id );
	static bool		HT_bIsPCSkillAsuRak( const int id );
	static bool		HT_bIsPCSkillAsuRak1st( const int id );
	static bool		HT_bIsPCSkillAsuRak2nd( const int id );
	static bool		HT_bIsPCSkillAsuRak3rd( const int id );
	static bool		HT_bIsPCSkillYakGan( const int id );
	static bool		HT_bIsPCSkillYakGan1st( const int id );
	static bool		HT_bIsPCSkillYakGan2nd( const int id );
	static bool		HT_bIsPCSkillYakGan3rd( const int id );
	static bool		HT_bIsPCSkillDevGaru( const int id );
	static bool		HT_bIsPCSkillDevGaru1st( const int id );
	static bool		HT_bIsPCSkillDevGaru2nd( const int id );
	static bool		HT_bIsPCSkillDevGaru3rd( const int id );
	
	static bool		HT_bIsItemRare( const int id );
	static bool		HT_bIsItemUnique( const int id );
	static bool		HT_bIsItemQuest( const int id );
	static bool		HT_bIsItemMagic( const int id );

	static bool		HT_bIsItemWeapon( const int id );
	static bool		HT_bIsItemWeaponOneHand( const int id );
	static bool		HT_bIsItemWeaponOneHandNormal( const int id );
	static bool		HT_bIsItemWeaponOneHandNormalNotMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandNormalMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandRare( const int id );
	static bool		HT_bIsItemWeaponOneHandRareNotMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandRareMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandUnique( const int id );
	static bool		HT_bIsItemWeaponOneHandUniqueNotMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandUniqueMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandQuest( const int id );
	static bool		HT_bIsItemWeaponOneHandQuestNotMagic( const int id );
	static bool		HT_bIsItemWeaponOneHandQuestMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHand( const int id );
	static bool		HT_bIsItemWeaponTwoHandNotMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandNormal( const int id );
	static bool		HT_bIsItemWeaponTwoHandNormalNotMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandNormalMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandRare( const int id );
	static bool		HT_bIsItemWeaponTwoHandRareNotMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandRareMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandUnique( const int id );
	static bool		HT_bIsItemWeaponTwoHandUniqueNotMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandUniqueMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandQuest( const int id );
	static bool		HT_bIsItemWeaponTwoHandQuestNotMagic( const int id );
	static bool		HT_bIsItemWeaponTwoHandQuestMagic( const int id );
	static bool		HT_bIsItemWeaponThrow( const int id );
	static bool		HT_bIsItemWeaponThrowNormal( const int id );
	static bool		HT_bIsItemWeaponThrowNormalNotMagic( const int id );
	//static bool		HT_bIsItemWeaponThrowNormalMagic( const int id );
	static bool		HT_bIsItemWeaponThrowRare( const int id );
	static bool		HT_bIsItemWeaponThrowRareNotMagic( const int id );
	//static bool		HT_bIsItemWeaponThrowRareMagic( const int id );
	static bool		HT_bIsItemWeaponThrowUnique( const int id );
	static bool		HT_bIsItemWeaponThrowUniqueNotMagic( const int id );
	//static bool		HT_bIsItemWeaponThrowUniqueMagic( const int id );
	static bool		HT_bIsItemWeaponThrowQuest( const int id );
	static bool		HT_bIsItemWeaponThrowQuestNotMagic( const int id );
	//static bool		HT_bIsItemWeaponThrowQuestMagic( const int id );
	
	static bool		HT_bIsItemDefence( const int id );
	static bool		HT_bIsItemDefenceArmor( const int id );
	static bool		HT_bIsItemDefenceArmorNormal( const int id );
	static bool		HT_bIsItemDefenceArmorRare( const int id );
	static bool		HT_bIsItemDefenceArmorUnique( const int id );
	static bool		HT_bIsItemDefenceArmorQuest( const int id );
	static bool		HT_bIsItemDefencePants( const int id );
	static bool		HT_bIsItemDefencePantsNormal( const int id );
	static bool		HT_bIsItemDefencePantsRare( const int id );
	static bool		HT_bIsItemDefencePantsUnique( const int id );
	static bool		HT_bIsItemDefencePantsQuest( const int id );
	static bool		HT_bIsItemDefenceGloves( const int id );
	static bool		HT_bIsItemDefenceGlovesNormal( const int id );
	static bool		HT_bIsItemDefenceGlovesRare( const int id );
	static bool		HT_bIsItemDefenceGlovesUnique( const int id );
	static bool		HT_bIsItemDefenceGlovesQuest( const int id );
	static bool		HT_bIsItemDefenceHelmet( const int id );
	static bool		HT_bIsItemDefenceHelmetNormal( const int id );
	static bool		HT_bIsItemDefenceHelmetRare( const int id );
	static bool		HT_bIsItemDefenceHelmetUnique( const int id );
	static bool		HT_bIsItemDefenceHelmetQuest( const int id );
	static bool		HT_bIsItemDefenceBelt( const int id );
	static bool		HT_bIsItemDefenceBeltNormal( const int id );
	static bool		HT_bIsItemDefenceBeltRare( const int id );
	static bool		HT_bIsItemDefenceBeltUnique( const int id );
	static bool		HT_bIsItemDefenceBeltQuest( const int id );
	static bool		HT_bIsItemDefenceShoes( const int id );
	static bool		HT_bIsItemDefenceShoesNormal( const int id );
	static bool		HT_bIsItemDefenceShoesRare( const int id );
	static bool		HT_bIsItemDefenceShoesUnique( const int id );
	static bool		HT_bIsItemDefenceShoesQuest( const int id );
	static bool		HT_bIsItemDefenceShield( const int id );
	static bool		HT_bIsItemDefenceShieldNormal( const int id );
	static bool		HT_bIsItemDefenceShieldRare( const int id );
	static bool		HT_bIsItemDefenceShieldUnique( const int id );
	static bool		HT_bIsItemDefenceShieldQuest( const int id );

	static bool		HT_bIsItemCharm( const int id );

	static bool		HT_bIsItemAccessory( const int id );
	static bool		HT_bIsItemAccessoryEarring( const int id );
	static bool		HT_bIsItemAccessoryEarringNormal( const int id );
	static bool		HT_bIsItemAccessoryEarringRare( const int id );
	static bool		HT_bIsItemAccessoryEarringUnique( const int id );
	static bool		HT_bIsItemAccessoryEarringQuest( const int id );
	static bool		HT_bIsItemAccessoryBracelet( const int id );
	static bool		HT_bIsItemAccessoryBraceletNormal( const int id );
	static bool		HT_bIsItemAccessoryBraceletRare( const int id );
	static bool		HT_bIsItemAccessoryBraceletUnique( const int id );
	static bool		HT_bIsItemAccessoryBraceletQuest( const int id );
	static bool		HT_bIsItemAccessoryNecklace( const int id );
	static bool		HT_bIsItemAccessoryNecklaceNormal( const int id );
	static bool		HT_bIsItemAccessoryNecklaceRare( const int id );
	static bool		HT_bIsItemAccessoryNecklaceUnique( const int id );
	static bool		HT_bIsItemAccessoryNecklaceQuest( const int id );
	static bool		HT_bIsItemAccessoryExpandInven( const int id );
	static bool		HT_bIsItemAccessoryExpandInvenNormal( const int id );
	static bool		HT_bIsItemAccessoryExpandInvenQuest( const int id );
	static bool		HT_bIsItemAccessoryRing( const int id );
	static bool		HT_bIsItemAccessoryRingNormal( const int id );
	static bool		HT_bIsItemAccessoryRingRare( const int id );
	static bool		HT_bIsItemAccessoryRingUnique( const int id );
	static bool		HT_bIsItemAccessoryRingQuest( const int id );

	static bool		HT_bIsItemRefine( const int id );
	static bool		HT_bIsItemRefineMain( const int id );
	static bool		HT_bIsItemRefineSub( const int id );
	static bool		HT_bIsItemRefineSub2( const int id );
	static bool		HT_bIsItemRefineSub3( const int id );
	
	static bool		HT_bIsItemCharge( const int id );
	static bool		HT_bIsItemChargeContinuance( const int id );
	static bool		HT_bIsItemChargeFunction( const int id );

	static bool		HT_bIsItemUsable( const int id );
	static bool		HT_bIsItemUsableMoney( const int id );
	static bool		HT_bIsItemUsableArrow( const int id );

	static bool		HT_bIsItemCollect( const int id );

	static bool		HT_bIsItemQuestOnly( const int id );

	static bool		HT_bIsNPC( const int id );
	static bool		HT_bIsChargeNPC( const int id);
	static bool		HT_bIsPortal( const int id );
	static bool		HT_bIsTaskQuest( const int id );
	static bool		HT_bIsAreaIndicate( const int id );
};

class CHTXMLParser;

struct HTIDLevel
{
	HTIDLevel();
	~HTIDLevel();
	HTIDLevel( const HTIDLevel& oIDLevel );
	int		iID;
	byte	byteLevel;
};

class CHTBaseClientParamTable
{
public:
	CHTBaseClientParamTable();
	virtual ~CHTBaseClientParamTable();

	virtual bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE ) = 0;

	// SetID
	virtual bool		HT_bLockID( const int id, const byte iLevel = 0 ) = 0;
	virtual bool		HT_bUnLockID( const int id, const byte iLevel = 0 ) = 0;

	// Load & Save
	virtual bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) = 0;
	virtual bool		HT_bLoad( CHTFile* pFile/*, CHTString& strTable*/ ) = 0;
	virtual bool		HT_bSave( CHTFile* pFile ) = 0;

	// Monster Param with ID
	virtual bool		HT_bGetMonsterName( const int id, CHTString* pstrName );
	virtual bool		HT_bGetMonsterSize( const int id, byte* pbyteSize );
	virtual bool		HT_bGetMonsterClass( const int id, byte* pbyteClass );
	virtual bool		HT_bGetMonsterFly( const int id, byte* pbFly );
	virtual bool		HT_bGetMonsterReserved7( const int id, byte* pbResrved7 );

	// Monster Param with No ID
	virtual bool		HT_bGetMonsterName( CHTString* pstrName );
	virtual bool		HT_bGetMonsterSize( byte* pbyteSize );
	virtual bool		HT_bGetMonsterClass( byte* pbyteClass );
	virtual bool		HT_bGetMonsterFly( byte* pbFly );
	virtual bool		HT_bGetMonsterReserved7( byte* pbResrved7 );

	// MonsterSkill Param with ID
	virtual bool		HT_bGetMonsterSkillRange( const int id, int* piRange );
	virtual bool		HT_bGetMonsterSkillCastingTime( const int id, int* piCastingTime );

	// MonsterSkill Param without ID
	virtual bool		HT_bGetMonsterSkillRange( int* piRange );
	virtual bool		HT_bGetMonsterSkillCastingTime( int* piCastingTime );

	// PCSkill Param with ID
	virtual bool		HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	virtual bool		HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType );
	virtual bool		HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	virtual bool		HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration );
//	virtual bool		HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	virtual bool		HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime );
	virtual bool		HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	virtual bool		HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime );
	virtual bool		HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	virtual bool		HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange );
	virtual bool		HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	virtual bool		HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	virtual bool		HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	virtual bool		HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	virtual bool		HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	virtual bool		HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	virtual bool		HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	virtual bool		HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	virtual bool		HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	virtual bool		HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	virtual bool		HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	virtual bool		HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	virtual bool		HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	virtual bool		HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	virtual bool		HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	virtual bool		HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	virtual bool		HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	virtual bool		HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	virtual bool		HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	virtual bool		HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	virtual bool		HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	virtual bool		HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	virtual bool		HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	virtual bool		HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	virtual bool		HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	virtual bool		HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	virtual bool		HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	virtual bool		HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	virtual bool		HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	virtual bool		HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	virtual bool		HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	virtual bool		HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	virtual bool		HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	virtual bool		HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	virtual bool		HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount );
	virtual bool		HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	virtual bool		HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	virtual bool		HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	virtual bool		HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	virtual bool		HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	virtual bool		HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass );
	virtual bool		HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	virtual bool		HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	virtual bool		HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	virtual bool		HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );

	// PC Skill Param without ID
	virtual bool		HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel );
	virtual bool		HT_bGetPCSkillType( byte* pbyteType );
	virtual bool		HT_bGetPCSkillCombatPhase( short* psCombatPhase );
	virtual bool		HT_bGetPCSkillDuration( int* piDuration );
//	virtual bool		HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate );
	virtual bool		HT_bGetPCSkillReadyTime( int* piReadyTime );
	virtual bool		HT_bGetPCSkillCastingTime( int* piCastingTime );
	virtual bool		HT_bGetPCSkillApplyTime( int* piApplyTime );
	virtual bool		HT_bGetPCSkillCoolDownTime( int* piCoolDownTime );
	virtual bool		HT_bGetPCSkillRange( int* piRange );
	virtual bool		HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect );
	virtual bool		HT_bGetPCSkillAllowedTarget( int* piAllowedTarget );
	virtual bool		HT_bGetPCSkillAttackType( byte* pbyteAttackType );
	virtual bool		HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	virtual bool		HT_bGetPCSkillFollowRange( byte* pbyteFollowRange );
	virtual bool		HT_bGetPCSkillPierceRate( byte* pbytePierceRate );
	virtual bool		HT_bGetPCSkillEffect1ID( int* piEffect1ID );
	virtual bool		HT_bGetPCSkillEffect1Function( int* piEffect1Function );
	virtual bool		HT_bGetPCSkillEffect1Duration( int* piEffect1Duration );
	virtual bool		HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 );
	virtual bool		HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 );
	virtual bool		HT_bGetPCSkillEffect2ID( int* piEffect2ID );
	virtual bool		HT_bGetPCSkillEffect2Function( int* piEffect2Function );
	virtual bool		HT_bGetPCSkillEffect2Duration( int* piEffect2Duration );
	virtual bool		HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 );
	virtual bool		HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 );
	virtual bool		HT_bGetPCSkillEffect3ID( int* piEffect3ID );
	virtual bool		HT_bGetPCSkillEffect3Function( int* piEffect3Function );
	virtual bool		HT_bGetPCSkillEffect3Duration( int* piEffect3Duration );
	virtual bool		HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 );
	virtual bool		HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 );
	virtual bool		HT_bGetPCSkillEffect4ID( int* piEffect4ID );
	virtual bool		HT_bGetPCSkillEffect4Function( int* piEffect4Function );
	virtual bool		HT_bGetPCSkillEffect4Duration( int* piEffect4Duration );
	virtual bool		HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 );
	virtual bool		HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 );
	virtual bool		HT_bGetPCSkillEffect5ID( int* piEffect5ID );
	virtual bool		HT_bGetPCSkillEffect5Function( int* piEffect5Function );
	virtual bool		HT_bGetPCSkillEffect5Duration( int* piEffect5Duration );
	virtual bool		HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 );
	virtual bool		HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 );
	virtual bool		HT_bGetPCSkillCostTP( int* piCostTP );
	virtual bool		HT_bGetPCSkillCostHP( int* piCostHP );
	virtual bool		HT_bGetPCSkillidCostItem( int* pidCostItem );
	virtual bool		HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount );
	virtual bool		HT_bGetPCSkillReqWeaponType( int* piReqWeaponType );
	virtual bool		HT_bGetPCSkillidReqItem( int* pidReqItem );
	virtual bool		HT_bGetPCSkillReqLevel( byte* pbyteReqLevel );
	virtual bool		HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti );
	virtual bool		HT_bGetPCSkillReqTribe( int* piReqTribe );
	virtual bool		HT_bGetPCSkillReqClass( int* piReqClass );
	virtual bool		HT_bGetPCSkillReqSkill1( int* pidReqSkill1 );
	virtual bool		HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	virtual bool		HT_bGetPCSkillReqSkill2( int* pidReqSkill2 );
	virtual bool		HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );

	// Item with ID
	virtual bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	virtual bool		HT_bGetItemName( const int id, CHTString* pstrName );
	virtual bool		HT_bGetItemDescription( const int id, CHTString* pstrDescription );
	virtual bool		HT_bGetItemClass( const int id, byte* pbyteClass );
	virtual bool		HT_bGetItemType( const int id, short* psType);
	virtual bool		HT_bGetItemRupiah( const int id, int* piRupiah );
	virtual bool		HT_bGetItemSellRupiah( const int id, int* piSellRupiah );
	virtual bool		HT_bGetItemMaxDurability( const int id, short* psMaxDurability );
	virtual bool		HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount );
	virtual bool		HT_bGetItemCombatPhase( const int id, short* psCombatPhase );
	virtual bool		HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate );
	virtual bool		HT_bGetItemEffect1ID( const int id, int* piEffect1ID );
	virtual bool		HT_bGetItemEffect1Function( const int id, int* piEffect1Function );
	virtual bool		HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration );
	virtual bool		HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 );
	virtual bool		HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 );
	virtual bool		HT_bGetItemEffect2ID( const int id, int* piEffect2ID );
	virtual bool		HT_bGetItemEffect2Function( const int id, int* piEffect2Function );
	virtual bool		HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration );
	virtual bool		HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 );
	virtual bool		HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 );
	virtual bool		HT_bGetItemEffect3ID( const int id, int* piEffect3ID );
	virtual bool		HT_bGetItemEffect3Function( const int id, int* piEffect3Function );
	virtual bool		HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration );
	virtual bool		HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 );
	virtual bool		HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 );
	virtual bool		HT_bGetItemEffect4ID( const int id, int* piEffect4ID );
	virtual bool		HT_bGetItemEffect4Function( const int id, int* piEffect4Function );
	virtual bool		HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration );
	virtual bool		HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 );
	virtual bool		HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 );
	virtual bool		HT_bGetItemEffect5ID( const int id, int* piEffect5ID );
	virtual bool		HT_bGetItemEffect5Function( const int id, int* piEffect5Function );
	virtual bool		HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration );
	virtual bool		HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 );
	virtual bool		HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 );
	virtual bool		HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime );
	virtual bool		HT_bGetItemRange( const int id, byte* pbyteRange );
	virtual bool		HT_bGetItemArmorType( const int id, byte* pbyteArmorType );
	virtual bool		HT_bGetItemAttackType( const int id, byte* pbyteAttackType );
	virtual bool		HT_bGetItemCostTP( const int id, int* piCostTP );
	virtual bool		HT_bGetItemCostHP( const int id, int* piCostHP );
	virtual bool		HT_bGetItemidCostItem( const int id, int* pidCostItem );
	virtual bool		HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti );
	virtual bool		HT_bGetItemLimitTribe( const int id, int* piLimitTribe );
	virtual bool		HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel );
	virtual bool		HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra );
	virtual bool		HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra );
	virtual bool		HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra );
	virtual bool		HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra );
	virtual bool		HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType );	
	virtual bool		HT_bGetItemCash( const int id, int* piCash );
	virtual bool		HT_bGetItemTimeLimit( const int id, short* psTimeLimit );
	//virtual bool		HT_bGetItemFXEffectID( const int id, int* piFXID );
	//virtual bool		HT_bGetItemEventID( const int id, short* psEventID );
	
	// Item without ID
	virtual bool		HT_bGetItemLevel( byte* pbyteLevel );
	virtual bool		HT_bGetItemName( CHTString* pstrName );
	virtual bool		HT_bGetItemDescription( CHTString* pstrDescription );
	virtual bool		HT_bGetItemClass( byte* pbyteClass );
	virtual bool		HT_bGetItemType( short* psType);
	virtual bool		HT_bGetItemRupiah( int* piRupiah );
	virtual bool		HT_bGetItemSellRupiah( int* piSellRupiah );
	virtual bool		HT_bGetItemMaxDurability( short* psMaxDurability );
	virtual bool		HT_bGetItemMaxCount( byte* pbyteMaxCount );
	virtual bool		HT_bGetItemCombatPhase( short* psCombatPhase );
	virtual bool		HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate );
	virtual bool		HT_bGetItemEffect1ID( int* piEffect1ID );
	virtual bool		HT_bGetItemEffect1Function( int* piEffect1Function );
	virtual bool		HT_bGetItemEffect1Duration( int* piEffect1Duration );
	virtual bool		HT_bGetItemEffect1Param1( int* piEffect1Param1 );
	virtual bool		HT_bGetItemEffect1Param2( int* piEffect1Param2 );
	virtual bool		HT_bGetItemEffect2ID( int* piEffect2ID );
	virtual bool		HT_bGetItemEffect2Function( int* piEffect2Function );
	virtual bool		HT_bGetItemEffect2Duration( int* piEffect2Duration );
	virtual bool		HT_bGetItemEffect2Param1( int* piEffect2Param1 );
	virtual bool		HT_bGetItemEffect2Param2( int* piEffect2Param2 );
	virtual bool		HT_bGetItemEffect3ID( int* piEffect3ID );
	virtual bool		HT_bGetItemEffect3Function( int* piEffect3Function );
	virtual bool		HT_bGetItemEffect3Duration( int* piEffect3Duration );
	virtual bool		HT_bGetItemEffect3Param1( int* piEffect3Param1 );
	virtual bool		HT_bGetItemEffect3Param2( int* piEffect3Param2 );
	virtual bool		HT_bGetItemEffect4ID( int* piEffect4ID );
	virtual bool		HT_bGetItemEffect4Function( int* piEffect4Function );
	virtual bool		HT_bGetItemEffect4Duration( int* piEffect4Duration );
	virtual bool		HT_bGetItemEffect4Param1( int* piEffect4Param1 );
	virtual bool		HT_bGetItemEffect4Param2( int* piEffect4Param2 );
	virtual bool		HT_bGetItemEffect5ID( int* piEffect5ID );
	virtual bool		HT_bGetItemEffect5Function( int* piEffect5Function );
	virtual bool		HT_bGetItemEffect5Duration( int* piEffect5Duration );
	virtual bool		HT_bGetItemEffect5Param1( int* piEffect5Param1 );
	virtual bool		HT_bGetItemEffect5Param2( int* piEffect5Param2 );
	virtual bool		HT_bGetItemCoolDownTime( int* piCoolDownTime );
	virtual bool		HT_bGetItemRange( byte* pbyteRange );
	virtual bool		HT_bGetItemArmorType( byte* pbyteArmorType );
	virtual bool		HT_bGetItemAttackType( byte* pbyteAttackType );
	virtual bool		HT_bGetItemCostTP( int* piCostTP );
	virtual bool		HT_bGetItemCostHP( int* piCostHP );
	virtual bool		HT_bGetItemidCostItem( int* pidCostItem );
	virtual bool		HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti );
	virtual bool		HT_bGetItemLimitTribe( int* piLimitTribe );
	virtual bool		HT_bGetItemLimitLevel( byte* pbyteLimitLevel );
	virtual bool		HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra );
	virtual bool		HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra );
	virtual bool		HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra );
	virtual bool		HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra );
	virtual bool		HT_bGetItemRefinableItemType( int* piRefinableItemType );	
	virtual bool		HT_bGetItemCash( int* piCash );
	virtual bool		HT_bGetItemTimeLimit( short* psTimeLimit );
	//virtual bool		HT_bGetItemFXEffectID( int* piFXID );
	//virtual bool		HT_bGetItemEventID( short* psEventID );

	// NPC & Shop with ID
	virtual bool		HT_bGetNPCName( const int id, CHTString* pstrName );
	virtual	bool		HT_bGetNPCSize( const int id, byte* pbyteSize );
	virtual	bool		HT_bGetNPCZone( const int id, byte* pbyteZone );
	virtual	bool		HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ );
	virtual	bool		HT_bGetNPCTrimuriti( const int id, byte* pbyNPCTrimuriti );
	virtual	int			HT_iGetNPCSellingItemCount( const int id );
	virtual	bool		HT_bGetNPCSellingItem( const int id, const int index, int* pidItem );

	// NPC & Shop without ID
	virtual bool		HT_bGetNPCName( CHTString* pstrName );
	virtual	bool		HT_bGetNPCSize( byte* pbyteSize );
	virtual	bool		HT_bGetNPCZone( byte* pbyteZone );
	virtual	bool		HT_bGetNPCPosition( short* psPosX, short* psPosZ );
	virtual	bool		HT_bGetNPCTrimuriti( byte* pbyNPCTrimuriti );
	virtual	int			HT_iGetNPCSellingItemCount();
	virtual	bool		HT_bGetNPCSellingItem( const int index, int* pidItem );

	// Portal
	virtual bool		HT_bGetPortalName( const int id, CHTString* pstrName );
	virtual	bool		HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel );
	virtual	bool		HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
											short* psStartX, short* psStartZ, short* psEndX, short* psEndZ);
	virtual	bool		HT_bGetPortalFee( const int idFromPortal, const int idToPortal, DWORD* pdwFee );
	virtual	bool		HT_bGetPortalLevel( const int idFromPortal, const int idToPortal, DWORD* pdwLevel);

	// TaskQuest with ID
	virtual bool		HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );
	
	virtual bool		HT_bGetTaskSource1( const int id, byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	virtual	bool		HT_bGetTaskSource2( const int id, byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	virtual	bool		HT_bGetTaskSource3( const int id, byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	virtual bool		HT_bGetTaskSource4( const int id, byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	virtual	bool		HT_bGetTaskSource5( const int id, byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	virtual	bool		HT_bGetTaskSource6( const int id, byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	virtual bool		HT_bGetTaskReward1( const int id, byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	virtual	bool		HT_bGetTaskReward2( const int id, byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	virtual	bool		HT_bGetTaskReward3( const int id, byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	virtual	bool		HT_bGetTaskReward4( const int id, byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	virtual	bool		HT_bGetTaskReward5( const int id, byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);
	
	virtual	bool		HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// TaskQuest without ID
	virtual bool		HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	virtual bool		HT_bGetTaskSource1( byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	virtual	bool		HT_bGetTaskSource2( byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	virtual	bool		HT_bGetTaskSource3( byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	virtual bool		HT_bGetTaskSource4( byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	virtual	bool		HT_bGetTaskSource5( byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	virtual	bool		HT_bGetTaskSource6( byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	virtual bool		HT_bGetTaskReward1( byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	virtual	bool		HT_bGetTaskReward2( byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	virtual	bool		HT_bGetTaskReward3( byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	virtual	bool		HT_bGetTaskReward4( byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	virtual	bool		HT_bGetTaskReward5( byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	virtual	bool		HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// AreaIndicate
	virtual bool		HT_bGetAreaFrom( const int id, DWORD* pdwFromID );
	virtual	bool		HT_bGetAreaTo( const int id, DWORD* pdwToID );
	virtual	bool		HT_bGetAreaName( const int id, CHTString* pstrName );
	virtual	bool		HT_bGetAreaName( const DWORD dwFrom, const DWORD dwTo, CHTString* pstrName );


protected:
	unsigned int		m_nItems;

private:
};

class CHTMonsterParamTable : public CHTBaseClientParamTable
{
public:
	CHTMonsterParamTable();
	~CHTMonsterParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );
	bool		HT_bTestSave( CHTFile* pFile );

	// Monster Param with ID
	bool		HT_bGetMonsterName( const int id, CHTString* pstrName );
	bool		HT_bGetMonsterSize( const int id, byte* pbyteSize );
	bool		HT_bGetMonsterClass( const int id, byte* pbyteClass );
	bool		HT_bGetMonsterFly( const int id, byte* pbFly );
	bool		HT_bGetMonsterReserved7( const int id, byte* pbReserved7 );

	// Monster Param with No ID
	bool		HT_bGetMonsterName( CHTString* pstrName );
	bool		HT_bGetMonsterSize( byte* pbyteSize );
	bool		HT_bGetMonsterClass( byte* pbyteClass );
	bool		HT_bGetMonsterFly( byte* pbFly );
	bool		HT_bGetMonsterReserved7( byte* pbReserved7 );

	// MonsterSkill Param with ID
	bool		HT_bGetMonsterSkillRange( const int id, int* piRange );
	bool		HT_bGetMonsterSkillCastingTime( const int id, int* piCastingTime );

	// MonsterSkill Param without ID
	bool		HT_bGetMonsterSkillRange( int* piRange );
	bool		HT_bGetMonsterSkillCastingTime( int* piCastingTime );

private:
	struct HTMonsterParam
	{
		char			szName[HT_NAME_MAX];
		byte			byteSize;
		byte			byteClass;
		byte			bFly;
		byte			byteReserve7;
	};

	struct HTMonsterSkillParam
	{
		int				iRange;
		int				iCastingTime;
	};

	typedef std::map<int,HTMonsterParam*>				HTMonsterParam_Map;
	typedef std::map<int,HTMonsterParam*>::value_type	HTMonsterParam_Value;
	typedef std::map<int,HTMonsterParam*>::iterator		HTMonsterParam_It;

	typedef std::map<int,HTMonsterSkillParam*>				HTMonsterSkillParam_Map;
	typedef std::map<int,HTMonsterSkillParam*>::value_type	HTMonsterSkillParam_Value;
	typedef std::map<int,HTMonsterSkillParam*>::iterator	HTMonsterSkillParam_It;

	HTMonsterParam*		m_pParamMonster;
	HTMonsterParam_Map	m_mapTableMonster;

	HTMonsterSkillParam*	m_pParamMonsterSkill;
	HTMonsterSkillParam_Map m_mapTableMonsterSkill;
};

class CHTPCSkillParamTable : public CHTBaseClientParamTable
{
public:
	CHTPCSkillParamTable();
	~CHTPCSkillParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	// PC Skill Param with ID
	bool		HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration );
//	bool		HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	bool		HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime );
	bool		HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	bool		HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );

	// PC Skill Param without ID
	bool		HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( int* piDuration );
//	bool		HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( byte* pbyteAttackType );
	bool		HT_bGetPCSkillReadyTime( int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( int* piApplyTime );
	bool		HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( int* piCostTP );
	bool		HT_bGetPCSkillCostHP( int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );                                               
	
private:
	struct HTPCSkillParam
	{
//		byte			byteLevel;
		byte			byteMaxLevel;
		byte			byteType;
		short			sCombatPhase;
//		byte			byteSuccessRate;
		int				iDuration;
		int				iCoolDownTime;
		int				iRange;
		int				iAreaOfEffect;
		int				iAllowedTarget;
		byte			byteAttackType;
		int				iReadyTime;
		int				iCastingTime;
		int				iApplyTime;
		byte			byteCastingSuccessRate;
		byte			byteFollowRange;
		byte			bytePierceRate;
		int				iEffect1ID;
		int				iEffect1Function;
		int				iEffect1Duration;
		int				iEffect1Param1;
		int				iEffect1Param2;
		int				iEffect2ID;
		int				iEffect2Function;
		int				iEffect2Duration;
		int				iEffect2Param1;
		int				iEffect2Param2;
		int				iEffect3ID;
		int				iEffect3Function;
		int				iEffect3Duration;
		int				iEffect3Param1;
		int				iEffect3Param2;
		int				iEffect4ID;
		int				iEffect4Function;
		int				iEffect4Duration;
		int				iEffect4Param1;
		int				iEffect4Param2;
		int				iEffect5ID;
		int				iEffect5Function;
		int				iEffect5Duration;
		int				iEffect5Param1;
		int				iEffect5Param2;
		int				iCostTP;
		int				iCostHP;
		int				idCostItem;
		byte			byteCostItemCount;
		int				iReqTrimuriti;			
		int				iReqTribe;
		int				iReqClass;
		int				iReqWeaponType;
		int				idReqItem;
		byte			byteReqLevel;
		int				idReqSkill1;				
		byte			byteReqSkill1_Lvl;		
		int				idReqSkill2;				
		byte			byteReqSkill2_Lvl;
	};

	typedef std::map<int,HTPCSkillParam*>				HTPCSkillParam_Map;
	typedef std::map<int,HTPCSkillParam*>::value_type	HTPCSkillParam_Value;
	typedef std::map<int,HTPCSkillParam*>::iterator	HTPCSkillParam_It;

	HTPCSkillParam*		m_pParam;
	HTPCSkillParam_Map	m_arrmapTable[HT_PCSKILL_MAXLEVEL];	// Level별로 존재한다.
};

class CHTItemParamTable : public CHTBaseClientParamTable
{
public:
	CHTItemParamTable();
	~CHTItemParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

public:
	// Item with ID
	bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	bool		HT_bGetItemName( const int id, CHTString* pstrName );
	bool		HT_bGetItemDescription( const int id, CHTString* pstrDescription );
	bool		HT_bGetItemClass( const int id, byte* pbyteClass );
	bool		HT_bGetItemType( const int id, short* psType);
	bool		HT_bGetItemRupiah( const int id, int* piRupiah );
	bool		HT_bGetItemSellRupiah( const int id, int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( const int id, short* psMaxDurability );
	bool		HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( const int id, short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( const int id, int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( const int id, int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( const int id, int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( const int id, int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( const int id, int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( const int id, int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( const int id, int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( const int id, int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( const int id, int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( const int id, int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime );
	bool		HT_bGetItemRange( const int id, byte* pbyteRange );
	bool		HT_bGetItemArmorType( const int id, byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( const int id, byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( const int id, int* piCostTP );
	bool		HT_bGetItemCostHP( const int id, int* piCostHP );
	bool		HT_bGetItemidCostItem( const int id, int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( const int id, int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType );
	bool		HT_bGetItemCash( const int id, int* piCash );
	bool		HT_bGetItemTimeLimit( const int id, short* psTimeLimit );
	//bool		HT_bGetItemFXEffectID( const int id, int* piFXID );
	//bool		HT_bGetItemEventID( const int id, short* psEventID );
	
	// Item without ID
	bool		HT_bGetItemLevel( byte* pbyteLevel );
	bool		HT_bGetItemName( CHTString* pstrName );
	bool		HT_bGetItemDescription( CHTString* pstrDescription );
	bool		HT_bGetItemClass( byte* pbyteClass );
	bool		HT_bGetItemType( short* psType);
	bool		HT_bGetItemRupiah( int* piRupiah );
	bool		HT_bGetItemSellRupiah( int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( short* psMaxDurability );
	bool		HT_bGetItemMaxCount( byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetItemRange( byte* pbyteRange );
	bool		HT_bGetItemArmorType( byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( int* piCostTP );
	bool		HT_bGetItemCostHP( int* piCostHP );
	bool		HT_bGetItemidCostItem( int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( int* piRefinableItemType );
	bool		HT_bGetItemCash( int* piCash );
	bool		HT_bGetItemTimeLimit( short* psTimeLimit );
	//bool		HT_bGetItemFXEffectID( int* piFXID );
	//bool		HT_bGetItemEventID( short* psEventID );

private:
	struct HTItemParam
	{
		char	szName[HT_NAME_MAX];
		char	szDescription[HT_DESCRIPT_MAX];
		byte	byteLevel;
		byte	byteClass;
		short	sType;
		int		iRupiah;
		int		iSellRupiah;
		short	sMaxDurability;
		byte	byteMaxCount;
		short	sCombatPhase;
		short	sSkillCastingTimeRate;
		int		iEffect1ID;
		int		iEffect1Function;
		int		iEffect1Duration;
		int		iEffect1Param1;
		int		iEffect1Param2;
		int		iEffect2ID;
		int		iEffect2Function;
		int		iEffect2Duration;
		int		iEffect2Param1;
		int		iEffect2Param2;
		int		iEffect3ID;
		int		iEffect3Function;
		int		iEffect3Duration;
		int		iEffect3Param1;
		int		iEffect3Param2;
		int		iEffect4ID;
		int		iEffect4Function;
		int		iEffect4Duration;
		int		iEffect4Param1;
		int		iEffect4Param2;
		int		iEffect5ID;
		int		iEffect5Function;
		int		iEffect5Duration;
		int		iEffect5Param1;
		int		iEffect5Param2;
		int		iCoolDownTime;
		byte	byteRange;
		byte	byteArmorType;
		byte	byteAttackType;
		int		iCostTP;
		int		iCostHP;
		int		idCostItem;
		int		iLimitTrimuriti;
		int		iLimitTribe;
		byte	byteLimitLevel;
		short	sLimitMusclechakra;
		short	sLimitNerveChakra;
		short	sLimitHeartChakra;
		short	sLimitSoulChakra;
		int		iRefinableItemType;
		int		iCash;
		short	sTimeLimit;
//		int		idFX;
		//short	sEventID;
	};

	typedef std::map<int,HTItemParam*>				HTItemParam_Map;
	typedef std::map<int,HTItemParam*>::value_type	HTItemParam_Value;
	typedef std::map<int,HTItemParam*>::iterator	HTItemParam_It;

	HTItemParam_Map				m_mapTable;
	HTItemParam*				m_pParam;
};

class CHTNPCParamTable : public CHTBaseClientParamTable
{
public :
	CHTNPCParamTable();
	~CHTNPCParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bGetNPCName( const int id, CHTString* pstrName );
	bool		HT_bGetNPCSize( const int id, byte* pbyteSize );
	bool		HT_bGetNPCZone( const int id, byte* pbyteZone );
	bool		HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( const int id, byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount( const int id );
	bool		HT_bGetNPCSellingItem( const int id, const int index, int* pidItem );

	bool		HT_bGetNPCName( CHTString* pstrName );
	bool		HT_bGetNPCSize( byte* pbyteSize );
	bool		HT_bGetNPCZone( byte* pbyteZone );
	bool		HT_bGetNPCPosition( short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount();
	bool		HT_bGetNPCSellingItem( const int index, int* pidItem );

private:
	struct HTNPCParam
	{
		char	szName[HT_NAME_MAX];
		byte	byteSize;
		byte	byteZone;
		short	sPosX;
		short	sPosZ;
		int		iNumItem;
		int		arridItem[HT_NPC_SELLING_ITEM_MAX];
		byte	byteNPCTrimuriti;
	};

	typedef std::map<int,HTNPCParam*>				HTNPCParam_Map;
	typedef std::map<int,HTNPCParam*>::value_type	HTNPCParam_Value;
	typedef std::map<int,HTNPCParam*>::iterator		HTNPCParam_It;

	HTNPCParam_Map	m_mapTable;
	HTNPCParam*		m_pParam;
};

class CHTPortalParamTable : public CHTBaseClientParamTable
{
public:
	CHTPortalParamTable();
	~CHTPortalParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE  );

	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bLockID( const int id, const byte iLevel = 0 ) { return false; }
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 ) { return false; }

	bool		HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel );
	bool		HT_bGetPortalName( const int id, CHTString* pstrName );
	bool		HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
									short* psStartX, short* psStartZ, short* psEndX, short* psEndZ);
	bool		HT_bGetPortalFee( const int idFromPortal, const int idToPrtal, DWORD* pdwFee );
	bool		HT_bGetPortalLevel( const int idFromPortal, const int idToPrtal, DWORD* pdwLevel);

private:
	struct HTPortalParam
	{
		char  		szName[HT_NAME_MAX];
		DWORD		dwServerID;
		DWORD		dwZoneLevel;

		short		sStartX;
		short		sStartZ;
		short		sEndX;
		short		sEndZ;

		int			iGoPortal[5];
		DWORD		dwFee[5];
		DWORD		dwLevel[5];
	};

	typedef std::map<DWORD,HTPortalParam*>				HTPortalParam_Map;
	typedef std::map<DWORD,HTPortalParam*>::value_type	HTPortalParam_Value;
	typedef std::map<DWORD,HTPortalParam*>::iterator		HTPortalParam_It;

	HTPortalParam_Map	m_mapTable;
	HTPortalParam*		m_pParam;
};

class CHTTaskQuestParamTable : public CHTBaseClientParamTable
{
public:
	CHTTaskQuestParamTable();
	~CHTTaskQuestParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );

	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );
	// with ID
	bool		HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	bool		HT_bGetTaskSource1( const int id, byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( const int id, byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( const int id, byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( const int id, byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( const int id, byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( const int id, byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( const int id, byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( const int id, byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( const int id, byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( const int id, byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( const int id, byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// without ID
	bool		HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	bool		HT_bGetTaskSource1( byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

private:
	struct HTTaskQuestParam
	{
		short		sNPCID1;
		short		sNPCID2;
		short		sNPCID3;
		short		sNPCID4;
		short		sNPCID5;

		byte		byteSourceType1;
		short		sSourceItemID1;
		int			iSourceCount1;
		byte		byteSourceType2;
		short		sSourceItemID2;
		int			iSourceCount2;
		byte		byteSourceType3;
		short		sSourceItemID3;
		int			iSourceCount3;
		byte		byteSourceType4;
		short		sSourceItemID4;
		int			iSourceCount4;
		byte		byteSourceType5;
		short		sSourceItemID5;
		int			iSourceCount5;
		byte		byteSourceType6;
		short		sSourceItemID6;
		int			iSourceCount6;

		byte		byteRewardPriority1;
		byte		byteRewardType1;
		short		sReward1Rate;
		short		sRewardItemID1;
		int			iRewardCount1;
		byte		byteRewardPriority2;
		byte		byteRewardType2;
		short		sReward2Rate;
		short		sRewardItemID2;
		int			iRewardCount2;
		byte		byteRewardPriority3;
		byte		byteRewardType3;
		short		sReward3Rate;
		short		sRewardItemID3;
		int			iRewardCount3;
		byte		byteRewardPriority4;
		byte		byteRewardType4;
		short		sReward4Rate;
		short		sRewardItemID4;
		int			iRewardCount4;
		byte		byteRewardPriority5;
		byte		byteRewardType5;
		short		sReward5Rate;
		short		sRewardItemID5;
		int			iRewardCount5;

		byte		byteMinLevel;			// 2005. 1. 5 선영범
		byte		byteMaxLevel;

	};

	typedef std::map<DWORD,HTTaskQuestParam*>				HTTaskQuestParam_Map;
	typedef std::map<DWORD,HTTaskQuestParam*>::value_type	HTTaskQuestParam_Value;
	typedef std::map<DWORD,HTTaskQuestParam*>::iterator		HTTaskQuestParam_It;

	HTTaskQuestParam_Map	m_mapTable;
	HTTaskQuestParam*		m_pParam;
};

// 지역표시
class CHTAreaIndicateParamTable : public CHTBaseClientParamTable
{
public:
	CHTAreaIndicateParamTable();
	~CHTAreaIndicateParamTable();

	bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );

	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bLockID( const int id, const byte iLevel = 0 ) { return false; }
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 ) { return false; }

	bool		HT_bGetAreaFrom( const int id, DWORD* pdwFromID );
	bool		HT_bGetAreaTo( const int id, DWORD* pdwToID );
	bool		HT_bGetAreaName( const int id, CHTString* pstrName );
	bool		HT_bGetAreaName( const DWORD dwFrom, const DWORD dwTo, CHTString* pstrName );

private:
	struct HTAreaIndicate
	{
		DWORD		dwFrom;
		DWORD		dwTo;
		char   		szName[HT_NAME_MAX];
	};

	typedef std::map<DWORD,HTAreaIndicate*>					HTAreaIndicate_Map;
	typedef std::map<DWORD,HTAreaIndicate*>::value_type		HTAreaIndicate_Value;
	typedef std::map<DWORD,HTAreaIndicate*>::iterator		HTAreaIndicate_It;

	HTAreaIndicate_Map		m_mapTable;
	HTAreaIndicate*			m_pParam;
};

class CHTClientParamMgr
{
public:
	CHTClientParamMgr();
	~CHTClientParamMgr();

	//bool		HT_bGetAllID( std::vector<HTIDLevel>* pvectorIDLevel, byte byteType = HT_CLI_PARAMTYPE_NONE );
	bool		HT_bGetAllID( int iType, std::vector<HTIDLevel>* pvectorIDLevel );

	// SetID
	bool		HT_bLockID( const int id, const byte iLevel = 0 );
	bool		HT_bUnLockID( const int id, const byte iLevel = 0 );

	// Load & Save
	bool		HT_bLoad( CHTString& strFile );
	bool		HT_bLoadXML( CHTString& strFile );
	bool		HT_bSave( CHTString& strFile );

	// for test
	bool		HT_bTestSave( CHTString& strFile );

	// 언어 설정
	void		HT_vSetLanguage( CHTString szLanguage ) { m_szLanguage = szLanguage; }
private:
	void		HT_vTestMonsterParamWithID( FILE* pFile, const int id );
	void		HT_vTestMonsterParam( FILE* pFile );

	void		HT_vTestMonsterSkillParamWithID( FILE* pFile, const int id );
	void		HT_vTestMonsterSkillParam( FILE* pFile );

	void		HT_vTestPCSkillParamWithID( FILE* pFile, const int id, const byte byteLevel );
	void		HT_vTestPCSkillParam( FILE* pFile );

	void		HT_vTestItemParamWithID( FILE* pFile, const int id );
	void		HT_vTestItemParam( FILE* pFile );

	void		HT_vTestNPCParamWithID( FILE* pFile, const int id );
	void		HT_vTestNPCParam( FILE* pFile );                       

	void		HT_vTestPortalParam( FILE* pFile, const int id );

	void		HT_vTestTaskQuestParamWithID( FILE* pFile, const int id );
	void		HT_vTestTaskQuestParam( FILE* pFile );

	void		HT_vTestAreaIndidcateParam( FILE* pFile, const int id );

public:
	// Monster Param with ID
	bool		HT_bGetMonsterName( const int id, CHTString* pstrName );
	bool		HT_bGetMonsterSize( const int id, byte* pbyteSize );
	bool		HT_bGetMonsterClass( const int id, byte* pbyteClass );
	bool		HT_bGetMonsterFly( const int id, byte* pbFly );
	bool		HT_bGetMonsterReserved7( const int id, byte* pbReserved7 );

	// Monster Param with No ID
	bool		HT_bGetMonsterName( CHTString* pstrName );
	bool		HT_bGetMonsterSize( byte* pbyteSize );
	bool		HT_bGetMonsterClass( byte* pbyteClass );
	bool		HT_bGetMonsterFly( byte* pbFly );
	bool		HT_bGetMonsterReserved7( byte* pbReserved7 );

	// MonsterSkill Param with ID
	bool		HT_bGetMonsterSkillRange( const int id, int* piRange );
	bool		HT_bGetMonsterSkillCastingTime( const int id, int* piCastingTime );

	// MonsterSkill Param without ID
	bool		HT_bGetMonsterSkillRange( int* piRange );
	bool		HT_bGetMonsterSkillCastingTime( int* piCastingTime );

	// PCSkill Param with ID
	bool		HT_bGetPCSkillMaxLevel( const int id, const byte byteLevel, byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( const int id, const byte byteLevel, byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( const int id, const byte byteLevel, short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( const int id, const byte byteLevel, int* piDuration );
//	bool		HT_bGetPCSkillSuccessRate( const int id, const byte byteLevel, byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillReadyTime( const int id, const byte byteLevel, int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( const int id, const byte byteLevel, int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( const int id, const byte byteLevel, int* piApplyTime );
	bool		HT_bGetPCSkillCoolDownTime( const int id, const byte byteLevel, int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( const int id, const byte byteLevel, int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( const int id, const byte byteLevel, int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( const int id, const byte byteLevel, int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( const int id, const byte byteLevel, byte* pbyteAttackType );
	bool		HT_bGetPCSkillCastingSuccessRate( const int id, const byte byteLevel, byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( const int id, const byte byteLevel, byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( const int id, const byte byteLevel, byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( const int id, const byte byteLevel, int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( const int id, const byte byteLevel, int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( const int id, const byte byteLevel, int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( const int id, const byte byteLevel, int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( const int id, const byte byteLevel, int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( const int id, const byte byteLevel, int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( const int id, const byte byteLevel, int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( const int id, const byte byteLevel, int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( const int id, const byte byteLevel, int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( const int id, const byte byteLevel, int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( const int id, const byte byteLevel, int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( const int id, const byte byteLevel, int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( const int id, const byte byteLevel, int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( const int id, const byte byteLevel, int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( const int id, const byte byteLevel, int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( const int id, const byte byteLevel, int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( const int id, const byte byteLevel, int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( const int id, const byte byteLevel, int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( const int id, const byte byteLevel, int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( const int id, const byte byteLevel, int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( const int id, const byte byteLevel, int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( const int id, const byte byteLevel, int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( const int id, const byte byteLevel, int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( const int id, const byte byteLevel, int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( const int id, const byte byteLevel, int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( const int id, const byte byteLevel, int* piCostTP );
	bool		HT_bGetPCSkillCostHP( const int id, const byte byteLevel, int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( const int id, const byte byteLevel, int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( const int id, const byte byteLevel, byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( const int id, const byte byteLevel, int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( const int id, const byte byteLevel, int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( const int id, const byte byteLevel, byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( const int id, const byte byteLevel, int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( const int id, const byte byteLevel, int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( const int id, const byte byteLevel, int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( const int id, const byte byteLevel, int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( const int id, const byte byteLevel, int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( const int id, const byte byteLevel, byte* pbyteReqSkill2_Lvl );
 
	// PC Skill Param without ID
	bool		HT_bGetPCSkillMaxLevel( byte* pbyteMaxLevel );
	bool		HT_bGetPCSkillType( byte* pbyteType );
	bool		HT_bGetPCSkillCombatPhase( short* psCombatPhase );
	bool		HT_bGetPCSkillDuration( int* piDuration );
//	bool		HT_bGetPCSkillSuccessRate( byte* pbyteSuccessRate );
	bool		HT_bGetPCSkillReadyTime( int* piReadyTime );
	bool		HT_bGetPCSkillCastingTime( int* piCastingTime );
	bool		HT_bGetPCSkillApplyTime( int* piApplyTime );
	bool		HT_bGetPCSkillCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetPCSkillRange( int* piRange );
	bool		HT_bGetPCSkillAreaOfEffect( int* piAreaOfEffect );
	bool		HT_bGetPCSkillAllowedTarget( int* piAllowedTarget );
	bool		HT_bGetPCSkillAttackType( byte* pbyteAttackType );
	bool		HT_bGetPCSkillCastingSuccessRate( byte* pbyteCastingSuccessRate );
	bool		HT_bGetPCSkillFollowRange( byte* pbyteFollowRange );
	bool		HT_bGetPCSkillPierceRate( byte* pbytePierceRate );
	bool		HT_bGetPCSkillEffect1ID( int* piEffect1ID );
	bool		HT_bGetPCSkillEffect1Function( int* piEffect1Function );
	bool		HT_bGetPCSkillEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetPCSkillEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetPCSkillEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetPCSkillEffect2ID( int* piEffect2ID );
	bool		HT_bGetPCSkillEffect2Function( int* piEffect2Function );
	bool		HT_bGetPCSkillEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetPCSkillEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetPCSkillEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetPCSkillEffect3ID( int* piEffect3ID );
	bool		HT_bGetPCSkillEffect3Function( int* piEffect3Function );
	bool		HT_bGetPCSkillEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetPCSkillEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetPCSkillEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetPCSkillEffect4ID( int* piEffect4ID );
	bool		HT_bGetPCSkillEffect4Function( int* piEffect4Function );
	bool		HT_bGetPCSkillEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetPCSkillEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetPCSkillEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetPCSkillEffect5ID( int* piEffect5ID );
	bool		HT_bGetPCSkillEffect5Function( int* piEffect5Function );
	bool		HT_bGetPCSkillEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetPCSkillEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetPCSkillEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetPCSkillCostTP( int* piCostTP );
	bool		HT_bGetPCSkillCostHP( int* piCostHP );
	bool		HT_bGetPCSkillidCostItem( int* pidCostItem );
	bool		HT_bGetPCSkillCostItemCount( byte* pbyteCostItemCount );
	bool		HT_bGetPCSkillReqWeaponType( int* piReqWeaponType );
	bool		HT_bGetPCSkillidReqItem( int* pidReqItem );
	bool		HT_bGetPCSkillReqLevel( byte* pbyteReqLevel );
	bool		HT_bGetPCSkillReqTrimuriti( int* piReqTrimuriti );
	bool		HT_bGetPCSkillReqTribe( int* piReqTribe );
	bool		HT_bGetPCSkillReqClass( int* piReqClass );
	bool		HT_bGetPCSkillReqSkill1( int* pidReqSkill1 );
	bool		HT_bGetPCSkillReqSkill1_Lvl( byte* pbyteReqSkill1_Lvl );
	bool		HT_bGetPCSkillReqSkill2( int* pidReqSkill2 );
	bool		HT_bGetPCSkillReqSkill2_Lvl( byte* pbyteReqSkill2_Lvl );

	// Item with ID
	bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	bool		HT_bGetItemName( const int id, CHTString* pstrName );
	bool		HT_bGetItemDescription( const int id, CHTString* pstrDescription );
	bool		HT_bGetItemClass( const int id, byte* pbyteClass );
	bool		HT_bGetItemType( const int id, short* psType);
	bool		HT_bGetItemRupiah( const int id, int* piRupiah );
	bool		HT_bGetItemSellRupiah( const int id, int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( const int id, short* psMaxDurability );
	bool		HT_bGetItemMaxCount( const int id, byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( const int id, short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( const int id, short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( const int id, int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( const int id, int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( const int id, int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( const int id, int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( const int id, int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( const int id, int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( const int id, int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( const int id, int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( const int id, int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( const int id, int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( const int id, int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( const int id, int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( const int id, int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( const int id, int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( const int id, int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( const int id, int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( const int id, int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( const int id, int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( const int id, int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( const int id, int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( const int id, int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( const int id, int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( const int id, int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( const int id, int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( const int id, int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( const int id, int* piCoolDownTime );
	bool		HT_bGetItemRange( const int id, byte* pbyteRange );
	bool		HT_bGetItemArmorType( const int id, byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( const int id, byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( const int id, int* piCostTP );
	bool		HT_bGetItemCostHP( const int id, int* piCostHP );
	bool		HT_bGetItemidCostItem( const int id, int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( const int id, int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( const int id, int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( const int id, byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( const int id, short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( const int id, short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( const int id, short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( const int id, short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( const int id, int* piRefinableItemType );
	bool		HT_bGetItemCash( const int id, int* piCash );
	bool		HT_bGetItemTimeLimit( const int id, short* psTimeLimit );
	//bool		HT_bGetItemFXEffectID( const int id, int* piFXID );
	//bool		HT_bGetItemEventID( const int id, short* psEventID );
	
	// Item without ID
	bool		HT_bGetItemLevel( byte* pbyteLevel );
	bool		HT_bGetItemName( CHTString* pstrName );
	bool		HT_bGetItemDescription( CHTString* pstrDescription );
	bool		HT_bGetItemClass( byte* pbyteClass );
	bool		HT_bGetItemType( short* psType);
	bool		HT_bGetItemRupiah( int* piRupiah );
	bool		HT_bGetItemSellRupiah( int* piSellRupiah );
	bool		HT_bGetItemMaxDurability( short* psMaxDurability );
	bool		HT_bGetItemMaxCount( byte* pbyteMaxCount );
	bool		HT_bGetItemCombatPhase( short* psCombatPhase );
	bool		HT_bGetItemSkillCastingTimeRate( short* psSkillCastingTimeRate );
	bool		HT_bGetItemEffect1ID( int* piEffect1ID );
	bool		HT_bGetItemEffect1Function( int* piEffect1Function );
	bool		HT_bGetItemEffect1Duration( int* piEffect1Duration );
	bool		HT_bGetItemEffect1Param1( int* piEffect1Param1 );
	bool		HT_bGetItemEffect1Param2( int* piEffect1Param2 );
	bool		HT_bGetItemEffect2ID( int* piEffect2ID );
	bool		HT_bGetItemEffect2Function( int* piEffect2Function );
	bool		HT_bGetItemEffect2Duration( int* piEffect2Duration );
	bool		HT_bGetItemEffect2Param1( int* piEffect2Param1 );
	bool		HT_bGetItemEffect2Param2( int* piEffect2Param2 );
	bool		HT_bGetItemEffect3ID( int* piEffect3ID );
	bool		HT_bGetItemEffect3Function( int* piEffect3Function );
	bool		HT_bGetItemEffect3Duration( int* piEffect3Duration );
	bool		HT_bGetItemEffect3Param1( int* piEffect3Param1 );
	bool		HT_bGetItemEffect3Param2( int* piEffect3Param2 );
	bool		HT_bGetItemEffect4ID( int* piEffect4ID );
	bool		HT_bGetItemEffect4Function( int* piEffect4Function );
	bool		HT_bGetItemEffect4Duration( int* piEffect4Duration );
	bool		HT_bGetItemEffect4Param1( int* piEffect4Param1 );
	bool		HT_bGetItemEffect4Param2( int* piEffect4Param2 );
	bool		HT_bGetItemEffect5ID( int* piEffect5ID );
	bool		HT_bGetItemEffect5Function( int* piEffect5Function );
	bool		HT_bGetItemEffect5Duration( int* piEffect5Duration );
	bool		HT_bGetItemEffect5Param1( int* piEffect5Param1 );
	bool		HT_bGetItemEffect5Param2( int* piEffect5Param2 );
	bool		HT_bGetItemCoolDownTime( int* piCoolDownTime );
	bool		HT_bGetItemRange( byte* pbyteRange );
	bool		HT_bGetItemArmorType( byte* pbyteArmorType );
	bool		HT_bGetItemAttackType( byte* pbyteAttackType );
	bool		HT_bGetItemCostTP( int* piCostTP );
	bool		HT_bGetItemCostHP( int* piCostHP );
	bool		HT_bGetItemidCostItem( int* pidCostItem );
	bool		HT_bGetItemLimitTrimuriti( int* piLimitTrimuriti );
	bool		HT_bGetItemLimitTribe( int* piLimitTribe );
	bool		HT_bGetItemLimitLevel( byte* pbyteLimitLevel );
	bool		HT_bGetItemLimitMuscleChakra( short* psLimitMusclechakra );
	bool		HT_bGetItemLimitNerveChakra( short* psLimitNerveChakra );
	bool		HT_bGetItemLimitHeartChakra( short* psLimitHeartChakra );
	bool		HT_bGetItemLimitSoulChakra( short* psLimitSoulChakra );
	bool		HT_bGetItemRefinableItemType( int* piRefinableItemType );
	bool		HT_bGetItemCash(int* piCash );
	bool		HT_bGetItemTimeLimit( short* psTimeLimit );
	//bool		HT_bGetItemFXEffectID( int* piFXID );
	//bool		HT_bGetItemEventID( short* psEventID );

	// NPC & Shop with ID
	bool		HT_bGetNPCName( const int id, CHTString* pstrName );
	bool		HT_bGetNPCSize( const int id, byte* pbyteSize );
	bool		HT_bGetNPCZone( const int id, byte* pbyteZone );
	bool		HT_bGetNPCPosition( const int id, short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( const int id, byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount( const int id );
	bool		HT_bGetNPCSellingItem( const int id, const int index, int* pidItem );

	// NPC & Shop without ID
	bool		HT_bGetNPCName( CHTString* pstrName );
	bool		HT_bGetNPCSize( byte* pbyteSize );
	bool		HT_bGetNPCZone( byte* pbyteZone );
	bool		HT_bGetNPCPosition( short* psPosX, short* psPosZ );
	bool		HT_bGetNPCTrimuriti( byte* pbyTrimuriti );
	int			HT_iGetNPCSellingItemCount();
	bool		HT_bGetNPCSellingItem( const int index, int* pidItem );

	// Portal
	bool		HT_bGetPortalName( const int id, CHTString* pstrName );
	bool		HT_bGetGoingPortal( const int id, const int iNo, int* piGoPortal, DWORD* pdwFee, DWORD* pdwLevel );
	bool		HT_bGetPortalInfo( const int id, DWORD* pdwServerID, DWORD* pdwZoneLevel, 
									short* psStartX, short* psStartZ, short* psEndX, short* psEndZ);
	bool		HT_bGetPortalFee( const int idFromPortal, const int idToPortal, DWORD* pdwFee );
	bool		HT_bGetPortalLevel( const int idFromPortal, const int idToPortal, DWORD* pdwLevel);

	// TaskQuest with ID
	bool		HT_bGetTaskNPCID( const int id, short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );
	
	bool		HT_bGetTaskSource1( const int id,/* short* psNPCID,*/ byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( const int id,/* short* psNPCID,*/ byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( const int id,/* short* psNPCID,*/ byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( const int id,/* short* psNPCID,*/ byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( const int id,/* short* psNPCID,*/ byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( const int id,/* short* psNPCID,*/ byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( const int id,/* short* psNPCID,*/ byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( const int id,/* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// without ID
	bool		HT_bGetTaskNPCID( short* psNPCID1, short* psNPCID2, short* psNPCID3, short* psNPCID4, short* psNPCID5 );

	bool		HT_bGetTaskSource1( /* short* psNPCID,*/byte* pbyteSourceType1, short* psSourceItemID1, int* piSourceCount1);
	bool		HT_bGetTaskSource2( /* short* psNPCID,*/byte* pbyteSourceType2, short* psSourceItemID2, int* piSourceCount2);
	bool		HT_bGetTaskSource3( /* short* psNPCID,*/byte* pbyteSourceType3, short* psSourceItemID3, int* piSourceCount3);
	bool		HT_bGetTaskSource4( /* short* psNPCID,*/byte* pbyteSourceType4, short* psSourceItemID4, int* piSourceCount4);
	bool		HT_bGetTaskSource5( /* short* psNPCID,*/byte* pbyteSourceType5, short* psSourceItemID5, int* piSourceCount5);
	bool		HT_bGetTaskSource6( /* short* psNPCID,*/byte* pbyteSourceType6, short* psSourceItemID6, int* piSourceCount6);

	bool		HT_bGetTaskReward1( /* short* psNPCID,*/byte* pbyteRewardPriority1, byte* pbyteRewardType1, short* psReward1Rate, short* psRewardItemID1, int* piRewardCount1);
	bool		HT_bGetTaskReward2( /* short* psNPCID,*/byte* pbyteRewardPriority2, byte* pbyteRewardType2, short* psReward2Rate, short* psRewardItemID2, int* piRewardCount2);
	bool		HT_bGetTaskReward3( /* short* psNPCID,*/byte* pbyteRewardPriority3, byte* pbyteRewardType3, short* psReward3Rate, short* psRewardItemID3, int* piRewardCount3);
	bool		HT_bGetTaskReward4( /* short* psNPCID,*/byte* pbyteRewardPriority4, byte* pbyteRewardType4, short* psReward4Rate, short* psRewardItemID4, int* piRewardCount4);
	bool		HT_bGetTaskReward5( /* short* psNPCID,*/byte* pbyteRewardPriority5, byte* pbyteRewardType5, short* psReward5Rate, short* psRewardItemID5, int* piRewardCount5);

	bool		HT_bGetTaskLevel( /* short* psNPCID,*/ byte* byteMinLevel, byte* byteMaxLevel);

	// AreaIndicate
	bool		HT_bGetAreaFrom( const int id, DWORD* pdwFromID );
	bool		HT_bGetAreaTo( const int id, DWORD* pdwToID );
	bool		HT_bGetAreaName( const int id, CHTString* pstrName );
	bool		HT_bGetAreaName( const DWORD dwFrom, const DWORD dwTo, CHTString* pstrName );

	// Get ID & Level List
	int			HT_iGetAllCount( const int iType );

	bool		HT_bGetNPCAllID( std::vector<HTIDLevel>* pvectorIDLevel );

	int			HT_iGetPCSkillIDLevelCount( const int iCharType );
	bool		HT_bGetPCSkillIDLevel( const int iCharType, const int index, int* pid, byte* pbyteLevel );

	// Get ID List
	int			HT_iGetPCSkillIDCount( const int iCharType );
	bool		HT_bGetPCSkillIDByIndex( const int iCharType, const int index, int* pid );

private :
	CHTBaseClientParamTable*	HT_pGetParamTable( int id );

private:
	CHTBaseClientParamTable*	m_arrParamTable[HT_CLI_PARAMTYPE_END];
	CHTBaseClientParamTable*	m_pParamTable;

	std::vector<HTIDLevel> m_vectorPCSkillIDLevelNagKin;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelAsuRak;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelDevGar;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelYakGan;
	std::vector<HTIDLevel> m_vectorPCSkillIDLevelEtc;

	std::vector<int> m_vectorPCSkillIDNagKin;
	std::vector<int> m_vectorPCSkillIDAsuRak;
	std::vector<int> m_vectorPCSkillIDDevGar;
	std::vector<int> m_vectorPCSkillIDYakGan;

	std::vector<HTIDLevel> m_vectorNPCIDLevel;

	CHTString					m_szLanguage;
};

#endif	// #ifndef _HTClientParamMgr_H_