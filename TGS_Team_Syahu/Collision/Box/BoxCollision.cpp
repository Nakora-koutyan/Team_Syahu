#include"BoxCollision.h"
#include"../Sphere/SphereCollision.h"

BoxCollision::BoxCollision()
{
	area = { 0.f,0.f };

	collisionType = CollisionType::Box;
}

BoxCollision::~BoxCollision()
{

}

bool BoxCollision::HitBox(const BoxCollision* collision) const
{
	bool ret = false;		//�Ԃ�l

	//�����̓����蔻��͈̔�
	float myX[2] = {};
	float myY[2] = {};

	//����̓����蔻��͈̔�
	float subX[2] = {};
	float subY[2] = {};

	//�����̓����蔻��͈̔͂̌v�Z
	myX[0] = location.x;
	myY[0] = location.y;
	myX[1] = myX[0] + area.width;
	myY[1] = myY[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	subX[0] = collision->GetLocation().x;
	subY[0] = collision->GetLocation().y;
	subX[1] = subX[0] + collision->GetArea().width;
	subY[1] = subY[0] + collision->GetArea().height;

	//�o���̎l�ӂ��������Ă��邩
	if ((myX[0] < subX[1]) &&
		(subX[0] < myX[1]) &&
		(myY[0] < subY[1]) &&
		(subY[0] < myY[1])) 
	{
		ret = true;
	}
	return ret;
}

bool BoxCollision::HitSphere(const SphereCollision* collision) const
{
	bool ret = false;		//�Ԃ�l

	Vector2D min = location;
	Vector2D max = { location.x + area.width,location.y + area.height };

	float sphereX = collision->GetLocation().x;
	float sphereY = collision->GetLocation().y;
	float sphereR = collision->GetRadius();

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
