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
};
//------------------------------------------------h

//------------------------------------------------h
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^

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




//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include"ObjStageSelect.h"
#include"ObjStage.h"
#include"ObjHero.h"
#include"ObjEnemy.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include"SceneStageSelect.h"
#include"SceneGameMain.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneStageSelect

//-----------------------------------------------
