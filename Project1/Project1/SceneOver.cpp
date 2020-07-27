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
CSceneOver::CSceneOver(int stage)
{
	stagenum = stage;
}

//�f�X�g���N�^
CSceneOver::~CSceneOver()
{

}

//�Q�[���I�[�o�[���������\�b�h
void CSceneOver::InitScene()
{
	CObjOver* over = new CObjOver(stagenum);
	Objs::InsertObj(over, OBJ_OVER, 1);

	//SE���̓o�^
	Audio::LoadAudio(0, L"�f��/BGM/Select.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"�f��/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(2, L"�f��/SE/button02.wav", SOUND_TYPE::EFFECT);

	Draw::LoadImageW(L"�f��/��/Animation.png", 3, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/Over(���A����).png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�Q�[���I�[�o�[(��).png", 1, TEX_SIZE_1024);

	
}

//�Q�[���I�[�o�[���s���\�b�h
void CSceneOver::Scene()
{

}