//�g�p����w�b�_�[�t�@�C��
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjDoormanager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CObjDoormanager::Init()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				pos[i][j][k] = 0.0f;
			}
		}
		Key[i] = false;
	}
}

void CObjDoormanager::Action()
{

}

void CObjDoormanager::Draw()
{
	
}

void CObjDoormanager::SetPos(int D_num, int binary, float x, float y)
{
	CObjDoormanager::pos[D_num][binary][0] = x;
	CObjDoormanager::pos[D_num][binary][1] = y;
	return;
}

void CObjDoormanager::MoveDoor(int D_num, int binary)
{
	CObjHero* Hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	if (binary == 0)
	{
		if ((-(pos[D_num][1][0] - 400)) > -5054&& (-(pos[D_num][1][0] - 800)) < 0)
		{
				block->SetScroll(-(pos[D_num][1][0] - 400));
				Hero->SetX(pos[D_num][1][0] + block->GetScroll());
		}
		else if(!((-(pos[D_num][1][0] - 400)) > -5054))
		{
			block->SetScroll(-5054);
			Hero->SetX(pos[D_num][1][0] + block->GetScroll());
		}
		else
		{
			block->SetScroll(0);
			Hero->SetX(pos[D_num][1][0] + block->GetScroll());
		}
		block->SetScrollY(-(pos[D_num][1][1] - 360));
			Hero->SetY(pos[D_num][1][1] + block->GetScrollY());
		////����X�N���[�����C��
		//if (pos[D_num][1][1] < 200 && block->GetScrollY() < 0)
		//{
		//	Hero->SetY(200);				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		//	block->SetScrollY(-(pos[D_num][1][1] - 200));	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

		//}

		////�����X�N���[�����C��
		//else if (pos[D_num][1][1] > 360 && block->GetScrollY() > -560)
		//{
		//	pos[D_num][1][1] = 360;			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		//	block->SetScrollY(-(pos[D_num][0][1] - 360));	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
		//}
		//else
		//{
		//	Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
		//}

		return;
	}
	if (binary == 1)
	{
		if ((-(pos[D_num][0][0] - 400)) > -5054 && (-(pos[D_num][0][0] - 800)) < 0)
		{
			block->SetScroll(-(pos[D_num][0][0] - 400));
			Hero->SetX(pos[D_num][0][0] + block->GetScroll());
		}
		else if (!((-(pos[D_num][0][0] - 400)) > -5054))
		{
			block->SetScroll(-5054);
			Hero->SetX(pos[D_num][0][0] + block->GetScroll());
		}
		else
		{
			block->SetScroll(0);
			Hero->SetX(pos[D_num][0][0] + block->GetScroll());
		}
		
		block->SetScrollY(-(pos[D_num][0][1] - 360));
		Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
		////����X�N���[�����C��
		//if (pos[D_num][0][1] < 200 && block->GetScrollY() < 0)
		//{
		//	Hero->SetY(200);				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		//	block->SetScrollY(-(pos[D_num][0][1] - 200));	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

		//}


		////�����X�N���[�����C��
		//else if (pos[D_num][0][1] > 360 && block->GetScrollY() > -560)
		//{
		//	pos[D_num][0][1] = 360;			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		//	block->SetScrollY(-(pos[D_num][0][1] - 360));	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����



		//}
		//else
		//{
		//	Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
		//}

		return;
	}
}