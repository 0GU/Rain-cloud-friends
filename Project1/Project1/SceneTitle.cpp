
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include"GameL/WinInputs.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "GameHead.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{
	
}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneTitle::InitScene()
{
	CObjTitle* p = new CObjTitle;
	Objs::InsertObj(p, OBJ_TITLE, 1);

	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/�^�C�g��.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/�摜/title.png", 1, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/��/Animation.png", 2, TEX_SIZE_64);

	//SE���̓o�^
	Audio::LoadAudio(0, L"�f��/BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"�f��/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(2, L"�f��/SE/button02.wav", SOUND_TYPE::EFFECT);

	Audio::Start(0);

}

//�Q�[���^�C�g�����s���\�b�h
void CSceneTitle::Scene()
{
	Input::UpdateXControlerConnected();
}