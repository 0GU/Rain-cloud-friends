//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/DrawFont.h"
#include"GameL/Audio.h"

#include "GameHead.h"
#include "ObjDoor.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



CObjDoor::CObjDoor(float x, float y, int d_num, int binary)
{
	m_x = x;
	m_y = y;
	num = d_num;
	bin = binary;
}

void CObjDoor::Init()
{
	CObjDoormanager* d = (CObjDoormanager*)Objs::GetObj(OBJ_DOORMANAGER);
	d->SetPos(num, bin, m_x, m_y);
	
	flag = false;

	stay_flag = false;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_RED, OBJ_DOOR, 1);
}

void CObjDoor::Action()
{


	CObjDoormanager* d = (CObjDoormanager*)Objs::GetObj(OBJ_DOORMANAGER);
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_x + block->GetScroll(), m_y + block->GetScrollY());

		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && (hero->GetKey(num) == true || num >= 10 && num <= 19) && hero->GetDown() == true)
		{
			if ((Input::GetVKey(VK_UP) == true || Input::GetConVecStickLY(0) > 0.1f) && flag == false)
			{
				d->MoveDoor(num, bin);
				Audio::Start(29);
			}
		}

		if ((Input::GetVKey(VK_UP) == true || Input::GetConVecStickLY(0) > 0.1f) && flag == false)
		{
			flag = true;
		}

		if ((Input::GetVKey(VK_UP) == false && Input::GetConVecStickLY(0) == false) && flag == true)
		{
			flag = false;
		}
	}
	

}

void CObjDoor::Draw()
{

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = src.m_top + 64.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = -64.0f+m_y + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 0.0f + m_x + block->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = 64.0f + m_y + block->GetScrollY();

	//�`��
	Draw::Draw(37, &src, &dst, c, 0.0f);
}
