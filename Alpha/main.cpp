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
	//创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	//把漫游器加入到场景中
	viewer->setCameraManipulator(new SimpleTraveller());

	osg::ref_ptr<osg::Group> root = new osg::Group();

	//读取地形模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("lz.osg");

	//添加到场景
	root->addChild(node.get());

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;
}
