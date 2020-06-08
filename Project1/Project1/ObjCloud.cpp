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
	m_vx = 5.0f;
	m_vy = 5.0f;
	m_hp = 1.0f;
	stay_flag = false;
	rain_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_CLOUD, 1);
}

//�A�N�V����
void CObjCloud::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		if (Input::GetVKey('A') == true)
			m_px -= m_vx;
		if (Input::GetVKey('D') == true)
			m_px += m_vx;
		if (Input::GetVKey('W') == true)
			m_py -= m_vy;
		if (Input::GetVKey('S') == true)
			m_py += m_vy;
	}

	if (Input::GetVKey('C') == true && rain_flag == true && m_hp > 0.0f)
	{
		CObjRain* objr = new CObjRain(m_px, m_py+64);
		Objs::InsertObj(objr, OBJ_RAIN, 10);
		rain_flag = false;
		m_hp -= 0.1f;	//hp����
	}
	if (Input::GetVKey('C') == false && rain_flag == false)
	{
		rain_flag = true;
	}

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px, m_py);
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
	Draw::Draw(5, &src, &dst, c, 0.0f);
}