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
		//�����������»ص�����
		osg::ref_ptr<osg::AnimationPathCallback> animationPathCallback = new osg::AnimationPathCallback();
		osg::ref_ptr<osg::Group> group = dynamic_cast<osg::Group*> (viewer.getSceneData());

		//ȡ�ýڵ�Ķ�������
		animationPathCallback = dynamic_cast<osg::AnimationPathCallback*> (group->getChild(0)->getUpdateCallback());

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				if (ea.getKey() == 'p')
				{
					//��ͣ
					animationPathCallback->setPause(true);

					return true;
				}
				if (ea.getKey() == 's')
				{
					//��ʼ
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

//����·��
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
		osg::Vec3 postion(center+osg::Vec3(sinf(yaw)*radius,cosf(yaw)*radius,0.0f));
		
		//�ؼ���Ƕ�
		osg::Quat rotation(osg::Quat(roll,osg::Vec3(0.0,1.0,0.0))*osg::Quat(-(yaw+osg::inDegrees(90.0f)),osg::Vec3(0.0,0.0,1.0)));

		//����Path���ѹؼ����ʱ���ѹ���γ�Path
		animationPath->insert(time,osg::AnimationPath::ControlPoint(postion,rotation));

		yaw += yaw_delta;
		time += time_delta;
	}

	//����Path
	return animationPath.get();	
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer =  new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root  = new osg::Group();


}
//int main(int argc, char** argv)
//{
//	//����Viewer���󣬳��������
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	//�����������뵽������
//	viewer->setCameraManipulator(new SimpleTraveller());
//
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	//��ȡ����ģ��
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("lz.osg");
//
//	//��ӵ�����
//	root->addChild(node.get());
//
//	//�Ż���������
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setSceneData(root.get());
//	viewer->realize();
//	viewer->run();
//
//	return 0;
//}
