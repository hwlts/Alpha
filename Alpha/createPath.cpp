#include "createPath.h"

osg::ref_ptr<osg::AnimationPath> createAnimationPath(osg::Vec3 & center, float radius, float looptime)
{
	//创建一个Path对象
	osg::ref_ptr<osg::AnimationPath>  animationPath = new osg::AnimationPath();

	//设置动画模式为Loop
	animationPath->setLoopMode(osg::AnimationPath::LOOP);

	//关键点数
	int numPoint = 60;

	//每次偏移角度
	float yaw = 0.0f;
	float yaw_delta = 2.0f * osg::PI / (float) (numPoint - 1.0f);

	//倾斜角度
	float roll = osg::inDegrees(45.0f);

	//时间偏移
	float time = 0.0f;
	float time_delta = looptime / ((float)numPoint);

	for (int i = 0; i < numPoint; i++)
	{
		//关键点位置
		osg::Vec3 position(center+osg::Vec3(sinf(yaw)*radius,cosf(yaw)*radius,0.0f));

		//关键点角度
		osg::Quat rotation(osg::Quat(roll,osg::Vec3(0.0,1.0,0.0))*osg::Quat(-(yaw+osg::inDegrees(90.0f)),osg::Vec3(0.0,0.0,1.0)));

		//插入Path，把关键点和时间点压入形成Path
		animationPath->insert(time,osg::AnimationPath::ControlPoint(position,rotation));

		yaw += yaw_delta;
		time += time_delta;
	}

	//返回Path
	return animationPath.get();	
}