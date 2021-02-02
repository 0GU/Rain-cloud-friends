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
	for (int i = 0; i < 2; i++)
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

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	if (binary == 0)
	{
		Hero->SetX(pos[D_num][1][0]+block->GetScroll());

		if (pos[D_num][1][1] > 400)
		{
			Hero->SetY(400);
			block->SetScrollY(-(pos[D_num][1][1] - 400));
		}
		else if (pos[D_num][1][1] < 256)
		{
			Hero->SetY(256);
			block->SetScrollY(-(pos[D_num][1][1] - 256));
		}
		else
		{
			Hero->SetY(pos[D_num][1][1] + block->GetScrollY());
		}
		return;
	}
	if (binary == 1)
	{
		Hero->SetX(pos[D_num][0][0] + block->GetScroll());
		if (pos[D_num][0][1]>400)
		{
			Hero->SetY(400);
			block->SetScrollY(-(pos[D_num][0][1] - 400));
		}
		else if (pos[D_num][0][1] < 256)
		{
			Hero->SetY(256);
			block->SetScrollY(-(pos[D_num][0][1] - 256));
		}
		else
		{
			Hero->SetY(pos[D_num][0][1] + block->GetScrollY());
		}

		
		return;
	}
}