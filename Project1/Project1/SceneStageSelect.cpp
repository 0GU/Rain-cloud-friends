
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "GameHead.h"

//�R���X�g���N�^
CSceneStageSelect::CSceneStageSelect()
{

}

//�f�X�g���N�^
CSceneStageSelect::~CSceneStageSelect()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneStageSelect::InitScene()
{

	CObjStageSelect* p = new CObjStageSelect();
	Objs::InsertObj(p, OBJ_STAGE_SELECT, 1);

	//SE���̓o�^
	Audio::LoadAudio(0, L"�f��/BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);

	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/Stage�w�i��.png", 0, TEX_SIZE_2048);

	Audio::Start(0);
}

//�Q�[���^�C�g�����s���\�b�h
void CSceneStageSelect::Scene()
{

}