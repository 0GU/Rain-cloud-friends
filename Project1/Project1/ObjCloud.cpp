//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjCloud.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjCloud::CObjCloud(int stage)
{
	reset = stage;
}

//�C�j�V�����C�Y
void CObjCloud::Init()
{
	m_px = 100.0f;
	m_py = 100.0f;
	m_vx = 1.0f;
	m_vy = 1.0f;
}

//�A�N�V����
void CObjCloud::Action()
{
	if (Input::GetVKey('A') == true)
		m_px -= m_vx;
	if (Input::GetVKey('D')== true)
		m_px += m_vx;
	if (Input::GetVKey('W') == true)
		m_py -= m_vy;
	if (Input::GetVKey('S') == true)
		m_py += m_vy;
}

//�h���[
void CObjCloud::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = m_py;
	dst.m_left = m_px;
	dst.m_right = m_px + 64.0f;
	dst.m_bottom = m_py + 64.0f;

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);
}