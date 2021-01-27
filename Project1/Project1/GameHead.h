#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_STAGE_SELECT,
	OBJ_STAGE,
	OBJ_HERO,
	OBJ_ENEMY,
	OBJ_FIRE,
	OBJ_PLANT,
	OBJ_STONE,
	OBJ_CLEAR,
	OBJ_POSE,
	OBJ_TITLE,
	OBJ_CLOUD,
	OBJ_HP,
	OBJ_RAIN,
	OBJ_RESTART,
	OBJ_CHASE_ENEMY,
	OBJ_SINENEMY,
	OBJ_OVER,
	OBJ_MAGIC,
	OBJ_RUSH_ENEMY,
	OBJ_TURTLE,
	OBJ_SWANP,
	OBJ_ENDING,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
	ELEMENT_RESET,
	ELEMENT_IVY,
	ELEMENT_FLOWER,
	ELEMENT_STONE,
	ELEMENT_SWANP,
};
//------------------------------------------------h

//------------------------------------------------h
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ

	bool Stage_1[5];//[0]:Perfect Clear [1]:Great Clear [2]:Good Clear
	bool Stage_2[5];
	bool Stage_3[5];
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--

//0定数マクロ
#define ZERO_G (0.0f) //グラフィック用
#define ZERO (0)//０マクロ通常

//HD画質用定数マクロ
#define HD_RIGIT (1280.0f)
#define HD_BUTTOM (720.0f)

//スクロールマクロ(仮)
#define BACKGROUND_SCROLL_T (0.0f)//上
#define BACKGROUND_SCROLL_B (0.0f)//下
#define SCROLL_DISTANCE (800.0f)//スクロールの到達点


//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------
class Enemy
{
	
};



//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include"ObjStageSelect.h"
#include"ObjStage.h"
#include"ObjHero.h"
#include"ObjEnemy.h"
#include"ObjFire.h"
#include"ObjPlant.h"
#include"ObjGrowPlant.h"
#include"ObjStone.h"
#include"ObjClear.h"
#include"ObjPose.h"
#include"ObjTitle.h"
#include"ObjCloud.h"
#include"ObjHp.h"
#include"ObjRain.h"
#include"ObjRestart.h"
#include"ObjChaseEnemy.h"
#include"ObjSinEnemy.h"
#include"ObjOver.h"
#include"ObjMagic.h"
#include"ObjRushEnemy.h"
#include"ObjEnding.h"
#include"ObjTurtle.h"
#include"ObjSwanp.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include"SceneStageSelect.h"
#include"SceneGameMain.h"
#include"SceneClear.h"
#include"SceneTitle.h"
#include"SceneOver.h"
#include"SceneEnding.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneTitle
//-----------------------------------------------
