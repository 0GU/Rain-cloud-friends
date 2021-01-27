#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
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

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
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
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^

	bool Stage_1[5];//[0]:Perfect Clear [1]:Great Clear [2]:Good Clear
	bool Stage_2[5];
	bool Stage_3[5];
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--

//0�萔�}�N��
#define ZERO_G (0.0f) //�O���t�B�b�N�p
#define ZERO (0)//�O�}�N���ʏ�

//HD�掿�p�萔�}�N��
#define HD_RIGIT (1280.0f)
#define HD_BUTTOM (720.0f)

//�X�N���[���}�N��(��)
#define BACKGROUND_SCROLL_T (0.0f)//��
#define BACKGROUND_SCROLL_B (0.0f)//��
#define SCROLL_DISTANCE (800.0f)//�X�N���[���̓��B�_


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------
class Enemy
{
	
};



//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
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

//�Q�[���V�[���N���X�w�b�_------------------------
#include"SceneStageSelect.h"
#include"SceneGameMain.h"
#include"SceneClear.h"
#include"SceneTitle.h"
#include"SceneOver.h"
#include"SceneEnding.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneTitle
//-----------------------------------------------
