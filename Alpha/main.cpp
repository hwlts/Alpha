#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Math>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include<osgDB/ReadFile>
#include<osgDB/WriteFile>

#include<osgUtil/Optimizer>

#include "TravelManipulator.h"
#include "SimpleTraveller.h"

class AnimationEventHandler : public osgGA::GUIEventHandler
{
public:
	AnimationEventHandler(osgViewer::Viewer &vr) : viewer(vr) {}

	virtual bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter&)
	{
		//创建动画更新回调对象
		osg::ref_ptr<osg::AnimationPathCallback> animationPathCallback = new osg::AnimationPathCallback();
		osg::ref_ptr<osg::Group> group = dynamic_cast<osg::Group*> (viewer.getSceneData());

		//取得节点的动画属性
		animationPathCallback = dynamic_cast<osg::AnimationPathCallback*> (group->getChild(0)->getUpdateCallback());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				if (ea.getKey() == 'p')
				{
					//暂停
					animationPathCallback->setPause(true);

					return true;
				}
				if (ea.getKey() == 's')
				{
					//开始
					animationPathCallback->setPause(false);

					return true;
				}
				if (ea.getKey() == 'r')
				{
					animationPathCallback->reset();

					return true;
				}
				break;				
			}
		default:
			break;
		}
		return false;
	}

	osgViewer::Viewer viewer;
};

//创建路径
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
		osg::Vec3 postion(center+osg::Vec3(sinf(yaw)*radius,cosf(yaw)*radius,0.0f));
		
		//关键点角度
		osg::Quat rotation(osg::Quat(roll,osg::Vec3(0.0,1.0,0.0))*osg::Quat(-(yaw+osg::inDegrees(90.0f)),osg::Vec3(0.0,0.0,1.0)));

		//插入Path，把关键点和时间点压入形成Path
		animationPath->insert(time,osg::AnimationPath::ControlPoint(postion,rotation));

		yaw += yaw_delta;
		time += time_delta;
	}

	//返回Path
	return animationPath.get();	
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer =  new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root  = new osg::Group();


}
//int main(int argc, char** argv)
//{
//	//创建Viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	//把漫游器加入到场景中
//	viewer->setCameraManipulator(new SimpleTraveller());
//
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	//读取地形模型
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("lz.osg");
//
//	//添加到场景
//	root->addChild(node.get());
//
//	//优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setSceneData(root.get());
//	viewer->realize();
//	viewer->run();
//
//	return 0;
//}
