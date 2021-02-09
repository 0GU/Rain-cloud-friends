//使用するヘッダーファイル
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "ObjDoormanager.h"

//使用するネームスペース
using namespace GameL;

void CObjDoormanager::Init()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				pos[i][j][k] = 0.0f;
			}
		}
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

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	if (binary == 0)
	{
		if ((-(pos[D_num][1][0] - 400)) > -5054 && (-(pos[D_num][1][0] - 800)) < 0)
		{
			block->SetScroll(-(pos[D_num][1][0] - 400));
			Hero->SetX(pos[D_num][1][0] + block->GetScroll());
		}
		else if (!((-(pos[D_num][1][0] - 400)) > -5054))
		{
			block->SetScroll(-5054);
			Hero->SetX(pos[D_num][1][0] + block->GetScroll());
		}
		else
		{
			block->SetScroll(0);
			Hero->SetX(pos[D_num][1][0] + block->GetScroll());
		}
		if (-(pos[D_num][1][1] - 360) < 0 && -(pos[D_num][1][1] - 200) > -560)
		{
			block->SetScrollY(-(pos[D_num][1][1] - 360));
			Hero->SetY(pos[D_num][1][1] + block->GetScrollY());
		}
		else if (!(-(pos[D_num][1][1] - 360) < 0))
		{
			block->SetScrollY(0);
			Hero->SetY(pos[D_num][1][1] + block->GetScrollY());
		}
		else
		{
			block->SetScrollY(-560);
			Hero->SetY(pos[D_num][1][1] + block->GetScrollY());
			for (;;)
			{
				if (Hero->GetY() < 350 && block->GetScrollY() < 0)
				{
					Hero->SetY(Hero->GetY() + 2.0f);
					block->SetScrollY(block->GetScrollY() + 2.0f);
					if (block->GetScrollY() > 0)
					{
						Hero->SetY(Hero->GetY() - block->GetScrollY());

						block->SetScrollY(0);
					}
				}
				else
				{
					break;
				}
			}
		}
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

		if (-(pos[D_num][0][1] - 360) < 0 && -(pos[D_num][0][1] - 200) > -560)
		{
			block->SetScrollY(-(pos[D_num][0][1] - 360));
			Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
		}
		else if (!(-(pos[D_num][0][1] - 360) < 0))
		{
			block->SetScrollY(0);
			Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
		}
		else
		{
			block->SetScrollY(-560);
			Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
			for (;;)
			{
				if (Hero->GetY() < 350 && block->GetScrollY() < 0)
				{
					Hero->SetY(Hero->GetY() + 2.0f);
					block->SetScrollY(block->GetScrollY() + 2.0f);
					if (block->GetScrollY() > 0)
					{
						Hero->SetY(Hero->GetY() - block->GetScrollY());

						block->SetScrollY(0);
					}
				}
				else
				{
					break;
				}
			}
		}


		return;
	}
}