#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�u���b�N���w�i
class CObjStage : public CObj
{
public:
	CObjStage(int map[15][100]);
	~CObjStage() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	void SetScroll(float s) { mx_scroll = s; }
	float GetScroll() { return mx_scroll; }
	void SetScrollY(float sy) { my_scroll = sy; }
	float GetScrollY() { return my_scroll; }
	//�u���b�N�Ƃ̓����蔻��
	void BlockHit(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy, int* bt
	);

	//��l���ƕǂ̌�������
	bool HeroBlockCrossPoint(
		float x, float y, float vx, float vy,
		float* out_px, float* out_py, float* out_len
	);

private:
	void BlockDraw(float x, float y, RECT_F* dst, float c[]);
	int m_map[15][100]; //�}�b�v���

	float mx_scroll;		//���E�X�N���[���p
	float my_scroll;		//�㉺�X�N���[���p

	float Dot(float ax, float ay, float bx, float by);		//����
	float Cross(float ax, float ay, float bx, float by);	//�O��

	//���Ɛ��ƌ�������
	bool LineCrossPoint(
		float a1x, float a1y, float a2x, float a2y,
		float b1x, float b1y, float b2x, float b2y,
		float* out_px, float* out_py
	);
	float m_y1;
	bool black_scroll;
};