#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Math>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/TerrainManipulator>

#include<osgDB/ReadFile>
#include<osgDB/WriteFile>

#include<osgUtil/Optimizer>

#include "TravelManipulator.h"
#include "SimpleTraveller.h"
#include "createPath.h"
#include "KeyBoardHandler.h"
#include "PickHandler.h"

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	//捕捉鼠标坐标
	osg::ref_ptr<osgText::Text> updatetext = new osgText::Text();
	CreateHUD *hudText= new CreateHUD();

	root->addChild(hudText->createHUD(updatetext.get()));

	viewer->addEventHandler(new CPickHandler(updatetext.get()));

	//模型加入场景
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:\\OSG_Resource\\FLT\\Sample\\Data\\Vega\\town.flt");
	root->addChild(node.get());
	viewer->setSceneData(root.get());

	//加入坦克的固定路径漫游
	osg::ref_ptr<osg::AnimationPath>  animationPath = new osg::AnimationPath();

	//自定义漫游器加入场景
	SimpleTraveller * st = new SimpleTraveller();
	st->setMnode(root);
	st->setPosition(osg::Vec3(2580,2330,2));
	viewer->setCameraManipulator(st);

	return viewer->run();
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
