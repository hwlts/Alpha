#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include<osgDB/ReadFile>
#include<osgDB/WriteFile>

#include<osgUtil/Optimizer>

#include "TravelManipulator.h"
#include "SimpleTraveller.h"

int main(int argc, char** argv)
{
	//����Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	//�����������뵽������
	viewer->setCameraManipulator(new SimpleTraveller());

	osg::ref_ptr<osg::Group> root = new osg::Group();

	//��ȡ����ģ��
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("lz.osg");

	//��ӵ�����
	root->addChild(node.get());

	//�Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;
}
