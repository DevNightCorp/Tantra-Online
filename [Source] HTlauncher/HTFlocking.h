#ifndef _HTFLOCKING_H_
#define _HTFLOCKING_H_

typedef enum
{
	FLYING_CIRCLE,
	FLYING_RANGE, 
	FLYING_LAST,

} enumFlyingType;

typedef enum
{
	BIRD_STOP,
	BIRD_CHANGE_FLYING_TYPE, 
	BIRD_CHANGE_RANGE, 
	BIRD_LAST,

} enumBirdState;

#define MAX_FLYING_RANGE (500.0f)//1000


/////////////////////////////////////////////////////////////////////
class CHTFlockingUnit
{
public:
	CHTFlockingUnit();
	~CHTFlockingUnit();
    CHTFlockingUnit( const CHTFlockingUnit& B );

    inline void SetId(HTint i){id = i;};
	inline void SetNPC(HTdword npc){dwNPC = npc;};
	inline void SetCurPos(HTvector3 vecPos){vecCurPos = vecPos; };
	inline void SetVel(HTvector3 vecTempVel){vecVel = vecTempVel; };
	inline HTint GetId(void){ return id;};
    inline HTdword GetNPC(void){ return dwNPC;};
	inline HTvector3 GetCurPos(void){ return vecCurPos;};
	inline HTvector3 GetVel(void){ return vecVel;};

    void Update(HTfloat fElapsedTime);

private :
	HTint	        id;
	HTdword	        dwNPC;

    HTvector3       vecCurPos;
    HTvector3       vecVel;
    //        enumBirdState   eBirdState;
    enumFlyingType  eFlyingType;

};


/////////////////////////////////////////////////////////////////////
class CHTFlocking
{
public:
				CHTFlocking();
				~CHTFlocking();

	HTRESULT	HT_hrCreate( HTint iNum );
	HTvoid		HT_vPushOne( HTdword dwNPC, HTvector3& vecBasePos );

	HTRESULT	HT_hrUpdate( HTfloat fElapsedTime );

private :

	struct HTFlockingOne
	{
		HTFlockingOne();
		HTFlockingOne( const HTFlockingOne& B );

		HTint	        id;
		HTdword	        dwNPC;

        HTvector3       vecCurPos;
        HTvector3       vecVel;
//        enumBirdState   eBirdState;
        enumFlyingType  eFlyingType;

	};

	std::vector<CHTFlockingUnit *> m_vectorFlocking;
};
/////////////////////////////////////////////////////////////////////

#endif	// #ifndef _HTFLOCKING_H_