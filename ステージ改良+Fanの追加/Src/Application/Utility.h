#pragma once
//�Ǐ]
static Math::Vector3 FollowDir(Math::Vector3 dest, Math::Vector3 src)
{
	return dest - src;
}
static Math::Vector3 FollowDir(Math::Matrix dest, Math::Matrix src)
{
	return dest.Translation() - src.Translation();
}

namespace GimmickBit
{
	/*enum Gimmick
	{
		lever_1 = 1,
		lever_2 = 2,
		lever_3 = 4
	};*/

	static int m_masc = 1;

	static int m_nowGimmickBit;


	static void InitBit() { m_nowGimmickBit = 0x000; }

}


//float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
//{
//	float a, b, rad, deg;
//	a = dest.x - src.x;//�G�Ǝ��@�̋��������߂�
//	b = dest.y - src.y;
//
//	rad = atan2(b, a);//�c���̏���
//	deg = DirectX::XMConvertToDegrees(rad);//rad * 180 / 3.141592;
//
//	//���̒l�̎��͕␳
//	if (deg < 0)
//	{
//		deg += 360;
//	}
//
//	return deg;
//}