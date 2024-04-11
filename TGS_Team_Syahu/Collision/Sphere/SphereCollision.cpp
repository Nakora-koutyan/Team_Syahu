#include"SphereCollision.h"
#include"../Box/BoxCollision.h"

SphereCollision::SphereCollision()
{
	radius = 0.f;

	collisionType = CollisionType::Sphere;
}

SphereCollision::~SphereCollision()
{

}

bool SphereCollision::HitSphere(const SphereCollision* collision) const
{
	bool ret = false;		//�Ԃ�l

	float dX = location.x - collision->GetLocation().x;
	float dY = location.y - collision->GetLocation().y;

	//���S�_�̋���
	float distance = dX * dX + dY * dY;

	float dR = radius + collision->GetRadius();

	//2�~�̔��a
	float length = dR * dR;

	//�o���̒��S����̋������傫������������
	if (distance < length)
	{
		ret = true;
	}

	return ret;
}

bool SphereCollision::HitBox(const BoxCollision* collision) const
{

	bool ret = false;		//�Ԃ�l

	Vector2D min = collision->GetMinLocation();
	Vector2D max = collision->GetMaxLocation();

	float sphereX = location.x;
	float sphereY = location.y;
	float sphereR = radius;

	// �l�p�`�̎l�ӂɑ΂��ĉ~�̔��a�������������Ƃ��~���d�Ȃ��Ă�����
	if ((sphereX > min.x - sphereR) &&
		(sphereX < max.x + sphereR) &&
		(sphereY > min.y - sphereR) &&
		(sphereY < max.y + sphereR))
	{
		ret = true;
		float length = sphereR * sphereR;

		//��
		if (sphereR < min.x)
		{
			//����
			if (sphereY < min.y)
			{
				if (MakeHypotenuse(min.x, min.y, sphereX, sphereY) >= length)
				{
					ret = false;
				}
			}
			else
			{
				//����
				if (sphereY > max.y)
				{
					if (MakeHypotenuse(min.x, max.y, sphereX, sphereY) >= length)
					{
						ret = false;
					}
				}
			}
		}
		else
		{
			//�E
			if (sphereX > max.x)
			{
				//�E��
				if (sphereY < min.x)
				{
					if (MakeHypotenuse(max.x, min.y, sphereX, sphereY) >= length)
					{
						ret = false;
					}
				}
				else
				{
					//�E��
					if (sphereY > max.y)
					{
						if (MakeHypotenuse(max.x, max.y, sphereX, sphereY) >= length)
						{
							ret = false;
						}
					}
				}
			}
		}
	}

	return ret;
}
