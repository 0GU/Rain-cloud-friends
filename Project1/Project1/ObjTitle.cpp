// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjTitle.h"

void CObjTitle::Init()
{

}

//�A�N�V����
void CObjTitle::Action()
{
	if (Input::GetVKey('Z') == true)
	{
		Scene::SetScene(new CSceneStageSelect());
	}
}

//�h���[
void CObjTitle::Draw()
{

	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//�^�C�g���w�i
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 900.0f;
	src.m_bottom = 636.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

//	Draw::Draw(0, &src, &dst, c, 0.0f);

	//�^�C�g���w�i
	src.m_top = 250.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 320.0f;

	dst.m_top = 0.0f;
	dst.m_left = 00.0f;
	dst.m_right =200.0f;
	dst.m_bottom = 200.0f;

	//Draw::Draw(1, &src, &dst, c, 0.0f);

}