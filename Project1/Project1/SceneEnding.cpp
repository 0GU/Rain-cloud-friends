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
CSceneEnding::CSceneEnding()
{

}

//�f�X�g���N�^
CSceneEnding::~CSceneEnding()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneEnding::InitScene()
{
	//BGM�Z�b�g
	Audio::LoadAudio(0, L"�f��/BGM/Ending.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::Start(0);
}

//�Q�[���^�C�g�����s���\�b�h
void CSceneEnding::Scene()
{
	Input::UpdateXControlerConnected();
}