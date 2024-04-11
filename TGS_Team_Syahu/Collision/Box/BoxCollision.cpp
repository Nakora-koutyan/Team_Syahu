#include "BoxCollision.h"

BoxCollision::BoxCollision()
{
	area = { 0.f,0.f };

	type = box;
}

BoxCollision::~BoxCollision()
{

}

bool BoxCollision::HitBox(const BoxCollision* collision) const
{
	bool ret = false;		//•Ô‚è’l

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float myX[2] = {};
	float myY[2] = {};

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float subX[2] = {};
	float subY[2] = {};

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	myX[0] = location.x;
	myY[0] = location.y;
	myX[1] = myX[0] + area.width;
	myY[1] = myY[0] + area.height;

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	subX[0] = collision->GetLocation().x;
	subY[0] = collision->GetLocation().y;
	subX[1] = subX[0] + collision->GetArea().width;
	subY[1] = subY[0] + collision->GetArea().height;

	if ((myX[0] <= subX[1]) &&
		(subX[0] <= myX[1]) &&
		(myY[0] <= subY[1]) &&
		(subY[0] <= myY[1])) //“–‚½‚è”»’è
	{
		ret = true;
	}
	return ret;
}
