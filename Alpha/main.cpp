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

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer =  new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root  = new osg::Group();

	osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("cessna.osg");
	 
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:\\FLT\\Sample\\Data\\Vega\\town.flt");

	const osg::BoundingSphere& bs = cessna->getBound();
	osg::Vec3 position = bs.center() + osg::Vec3(0.0f,0.0f,200.0f);
	float size = 100.0f/bs.radius()*0.3f;

	osg::ref_ptr<osg::AnimationPath> animationPath =  new osg::AnimationPath();
	animationPath = createAnimationPath(position,200.0f,10.0f);

	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();

	mt->setDataVariance(osg::Object::STATIC);

	mt->setMatrix(osg::Matrix::translate(-bs.center())*osg::Matrix::scale(size,size,size)*osg::Matrix::rotate(osg::inDegrees(-180.0f),0.0f,0.0f,1.0f));

	mt->addChild(cessna.get());

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setUpdateCallback(new osg::AnimationPathCallback(animationPath.get(),0.0f,1.0f));
	pat->addChild(mt);

	root->addChild(pat.get());
	root->addChild(node.get());

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->addEventHandler(new KeyBoardHandler());

	viewer->setCameraManipulator(new osgGA::DriveManipulator());

	viewer->realize();

	viewer->run();

	return 0;

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
