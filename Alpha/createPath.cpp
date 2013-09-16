#include "createPath.h"

osg::ref_ptr<osg::AnimationPath> createAnimationPath(osg::Vec3 & center, float radius, float looptime)
{
	//����һ��Path����
	osg::ref_ptr<osg::AnimationPath>  animationPath = new osg::AnimationPath();

	//���ö���ģʽΪLoop
	animationPath->setLoopMode(osg::AnimationPath::LOOP);

	//�ؼ�����
	int numPoint = 60;

	//ÿ��ƫ�ƽǶ�
	float yaw = 0.0f;
	float yaw_delta = 2.0f * osg::PI / (float) (numPoint - 1.0f);

	//��б�Ƕ�
	float roll = osg::inDegrees(45.0f);

	//ʱ��ƫ��
	float time = 0.0f;
	float time_delta = looptime / ((float)numPoint);

	for (int i = 0; i < numPoint; i++)
	{
		//�ؼ���λ��
		osg::Vec3 position(center+osg::Vec3(sinf(yaw)*radius,cosf(yaw)*radius,0.0f));

		//�ؼ���Ƕ�
		osg::Quat rotation(osg::Quat(roll,osg::Vec3(0.0,1.0,0.0))*osg::Quat(-(yaw+osg::inDegrees(90.0f)),osg::Vec3(0.0,0.0,1.0)));

		//����Path���ѹؼ����ʱ���ѹ���γ�Path
		animationPath->insert(time,osg::AnimationPath::ControlPoint(position,rotation));

		yaw += yaw_delta;
		time += time_delta;
	}

	//����Path
	return animationPath.get();	
}